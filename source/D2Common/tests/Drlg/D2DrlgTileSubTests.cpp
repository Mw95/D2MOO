#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <array>
#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <map>
#include <utility>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgOutRoom.h>
#include <Drlg/D2DrlgOutdoors.h>
#include <Drlg/D2DrlgPreset.h>
#include <Drlg/D2DrlgTileSub.h>

#include <Fixtures/DataTbls/Fixtures.h>


DYNAMIC_ARRAY_TYPE(int)


namespace
{
	// Size of the grids of a substitution file (D2LvlSubTxt::pTileTypeGrid, pWallGrid, pFloorGrid and pShadowGrid)
	constexpr auto sub_grid_width = 24;
	constexpr auto sub_grid_height = 8;
	// Size of the grids of the outdoor room in which the tiles are substituted (D2UnkOutdoorStrc2)
	constexpr auto room_grid_size = 16;
	// Size of D2UnkOutdoorStrc::pGrid1
	constexpr auto outdoor_grid_size = 32;
	// Maximum size of a layer of a DS1 file (nWidth + 1) * (nHeight + 1)
	constexpr auto max_ds1_size = 8;
	constexpr auto ds1_layer_size = (max_ds1_size + 1) * (max_ds1_size + 1);

	// Original address of gpLevelFilesList_6FDEA700
	constexpr auto level_files_list_offset = 0x000AA700;


	template<int Width, int Height>
	using GridCells = std::array<int32_t, Width * Height>;

	// Storage for the cells of a D2DrlgGridStrc
	template<int Width, int Height>
	struct GridData
	{
		GridCells<Width, Height> cells;
		std::array<int32_t, Height> row_offsets;
	};

	using SubGridCells = GridCells<sub_grid_width, sub_grid_height>;
	using SubGridData = GridData<sub_grid_width, sub_grid_height>;
	using RoomGridCells = GridCells<room_grid_size, room_grid_size>;
	using RoomGridData = GridData<room_grid_size, room_grid_size>;
	using OutdoorGridCells = GridCells<outdoor_grid_size, outdoor_grid_size>;
	using OutdoorGridData = GridData<outdoor_grid_size, outdoor_grid_size>;
	using Ds1Layer = std::array<int32_t, ds1_layer_size>;


	// Random cell flags using the bits that are evaluated by the substitution functions
	// (0x1: wall, 0x2: floor, 0xFF00 and 0x3F00000: tile style and sequence).
	// The shadow flag 0x8000000 is never set, since shadow tiles would require loaded tile libraries.
	int32_t random_cell_flags()
	{
		int32_t nFlags = random_unsigned_integer(0, 3);
		if (random_unsigned_integer(0, 1))
		{
			nFlags |= random_unsigned_integer(1, 3) << 8;
		}

		if (random_unsigned_integer(0, 1))
		{
			nFlags |= random_unsigned_integer(1, 3) << 20;
		}

		return nFlags;
	}

	int32_t random_sparse_cell_flags()
	{
		return random_unsigned_integer(0, 2) ? 0 : random_cell_flags();
	}

	int32_t random_floor_cell_flags()
	{
		return random_unsigned_integer(0, 1) ? 2 : random_cell_flags();
	}

	int32_t random_tile_type()
	{
		return random_unsigned_integer(0, 2);
	}

	int32_t random_level_prest_id()
	{
		return random_unsigned_integer(0, 7);
	}

	template<int Width, int Height>
	GridCells<Width, Height> random_grid_cells(int32_t(*generator)())
	{
		GridCells<Width, Height> cells{};
		for (auto& cell : cells)
		{
			cell = generator();
		}

		return cells;
	}

	Ds1Layer random_ds1_layer()
	{
		Ds1Layer layer{};
		for (auto& cell : layer)
		{
			cell = random_cell_flags();
		}

		return layer;
	}

	template<int Width, int Height>
	void setup_grid(D2DrlgGridStrc& pGrid, GridData<Width, Height>& data, const GridCells<Width, Height>& cells)
	{
		data.cells = cells;
		for (auto i = 0; i < Height; ++i)
		{
			data.row_offsets[i] = i * Width;
		}

		pGrid.pCellsFlags = data.cells.data();
		pGrid.pCellsRowOffsets = data.row_offsets.data();
		pGrid.nWidth = Width;
		pGrid.nHeight = Height;
	}

	// Sets up a grid whose row offsets are allocated like in DRLGGRID_FillNewCellFlags, so that they can be freed by DRLGGRID_FreeGrid
	void setup_allocated_grid(D2DrlgGridStrc& pGrid, SubGridData& data, const SubGridCells& cells)
	{
		setup_grid(pGrid, data, cells);

		pGrid.pCellsRowOffsets = static_cast<int32_t*>(D2_ALLOC_POOL(nullptr, sizeof(int32_t) * sub_grid_height));
		std::copy(data.row_offsets.begin(), data.row_offsets.end(), pGrid.pCellsRowOffsets);
		pGrid.unk0x10 = 1;
	}

	void free_allocated_grid(D2DrlgGridStrc& pGrid)
	{
		if (pGrid.pCellsRowOffsets)
		{
			D2_FREE_POOL(nullptr, pGrid.pCellsRowOffsets);
			pGrid.pCellsRowOffsets = nullptr;
		}
	}

	// Flattens the dimensions and the cells of a grid, so that grids can be compared by value
	std::vector<int> get_grid_values(const D2DrlgGridStrc& pGrid)
	{
		std::vector<int> values{ pGrid.nWidth, pGrid.nHeight, pGrid.unk0x10, pGrid.pCellsFlags != nullptr, pGrid.pCellsRowOffsets != nullptr };
		if (pGrid.pCellsFlags && pGrid.pCellsRowOffsets)
		{
			for (auto nY = 0; nY < pGrid.nHeight; ++nY)
			{
				for (auto nX = 0; nX < pGrid.nWidth; ++nX)
				{
					values.push_back(pGrid.pCellsFlags[nX + pGrid.pCellsRowOffsets[nY]]);
				}
			}
		}

		return values;
	}

	std::vector<int> get_preset_unit_values(const D2PresetUnitStrc* pPresetUnit)
	{
		std::vector<int> values;
		for (; pPresetUnit; pPresetUnit = pPresetUnit->pNext)
		{
			values.insert(values.end(), { pPresetUnit->nUnitType, pPresetUnit->nIndex, pPresetUnit->nMode, pPresetUnit->nXpos, pPresetUnit->nYpos, pPresetUnit->bSpawned });
		}

		return values;
	}

	// Frees the preset units allocated by DRLGROOM_AllocPresetUnit
	void free_preset_units(D2PresetUnitStrc* pPresetUnit)
	{
		while (pPresetUnit)
		{
			D2PresetUnitStrc* pNext = pPresetUnit->pNext;
			D2_FREE_POOL(nullptr, pPresetUnit);
			pPresetUnit = pNext;
		}
	}

	void check_values_eq(std::vector<int> moo_values, std::vector<int> original_values, const char* context_title)
	{
		// Prepend the sizes, so that empty value lists can be compared as well
		moo_values.insert(moo_values.begin(), static_cast<int>(moo_values.size()));
		original_values.insert(original_values.begin(), static_cast<int>(original_values.size()));

		auto moo_array = DynamicArray<int>{ moo_values.data(), static_cast<int>(moo_values.size()) };
		auto original_array = DynamicArray<int>{ original_values.data(), static_cast<int>(original_values.size()) };
		MOO_CHECK_EQ(moo_array, original_array, context_title);
	}


	// The callbacks of D2UnkOutdoorStrc log their calls, so that the calls of both implementations can be compared
	std::vector<int> callback_calls;

	unsigned int __fastcall test_field_1C(D2DrlgLevelStrc*, int nX, int nY)
	{
		callback_calls.insert(callback_calls.end(), { 0x1C, nX, nY });
		return (static_cast<unsigned int>(nX) + 2 * static_cast<unsigned int>(nY)) % 5 != 0;
	}

	BOOL __fastcall test_field_20(D2DrlgLevelStrc*, int nX, int nY, int nId, int nOffset, char nFlags)
	{
		callback_calls.insert(callback_calls.end(), { 0x20, nX, nY, nId, nOffset, nFlags });
		return (static_cast<unsigned int>(nX) + static_cast<unsigned int>(nY)) % 4 != 0;
	}

	BOOL __fastcall test_field_24(D2DrlgLevelStrc*, int nX, int nY, int a4, int a5, unsigned int a6)
	{
		callback_calls.insert(callback_calls.end(), { 0x24, nX, nY, a4, a5, static_cast<int>(a6) });
		return (static_cast<unsigned int>(nX) + static_cast<unsigned int>(nY) + static_cast<unsigned int>(a4) + static_cast<unsigned int>(a5) + a6) % 6 != 0;
	}

	int __fastcall test_field_28(D2DrlgLevelStrc*, int nStyle, int a3)
	{
		callback_calls.insert(callback_calls.end(), { 0x28, nStyle, a3 });
		// Returns -5 from time to time, which skips the substitution
		return static_cast<int>((static_cast<unsigned int>(nStyle) + static_cast<unsigned int>(a3)) % 7) - 5;
	}

	void __fastcall test_field_2C(D2DrlgLevelStrc*, int nX, int nY)
	{
		callback_calls.insert(callback_calls.end(), { 0x2C, nX, nY });
	}

	void __fastcall test_field_30(D2DrlgLevelStrc*, int nX, int nY)
	{
		callback_calls.insert(callback_calls.end(), { 0x30, nX, nY });
	}

	void __fastcall test_field_34(D2DrlgLevelStrc*, int nX, int nY, int nLevelPrestId, int nRand, BOOL a6)
	{
		callback_calls.insert(callback_calls.end(), { 0x34, nX, nY, nLevelPrestId, nRand, a6 });
	}


	// Box positions and sizes are limited, such that all accessed cells lie within the substitution file grids
	D2DrlgSubstGroupStrc random_subst_group()
	{
		D2DrlgSubstGroupStrc pSubstGroup{};
		pSubstGroup.tBox.nPosX = random_unsigned_integer(0, 3);
		pSubstGroup.tBox.nPosY = random_unsigned_integer(0, 3);
		pSubstGroup.tBox.nWidth = random_unsigned_integer(1, 3);
		pSubstGroup.tBox.nHeight = random_unsigned_integer(1, 3);
		pSubstGroup.field_10 = random_unsigned_integer(0, 3);
		pSubstGroup.field_14 = random_unsigned_integer(0, 3);
		return pSubstGroup;
	}

	// Random values of a D2LvlSubTxt record and its substitution file
	struct SubstitutionFileInput
	{
		uint32_t dwCheckAll;
		uint32_t dwBordType;
		uint32_t dwGridSize;
		std::array<uint32_t, 5> nProb;
		std::array<int32_t, 5> nTrials;
		std::array<int32_t, 5> nMax;
		int32_t nSubstMethod;
		int32_t nWallLayers;
		int32_t nFloorLayers;
		std::vector<D2DrlgSubstGroupStrc> substGroups;
		std::vector<D2PresetUnitStrc> presetUnits;
		std::array<SubGridCells, DRLG_MAX_WALL_LAYERS> tileTypeCells;
		std::array<SubGridCells, DRLG_MAX_WALL_LAYERS> wallCells;
		SubGridCells floorCells;
		SubGridCells shadowCells;
	};

	// Storage for the substitution file referenced by a D2LvlSubTxt record
	struct SubstitutionFileData
	{
		D2DrlgFileStrc tDrlgFile;
		std::vector<D2DrlgSubstGroupStrc> tSubstGroups;
		std::vector<D2PresetUnitStrc> tPresetUnits;
		std::array<SubGridData, DRLG_MAX_WALL_LAYERS> tileTypeGrids;
		std::array<SubGridData, DRLG_MAX_WALL_LAYERS> wallGrids;
		SubGridData floorGrid;
		SubGridData shadowGrid;
	};

	SubstitutionFileInput random_substitution_file_input(uint32_t nMinSubstGroups)
	{
		SubstitutionFileInput input{};
		input.dwCheckAll = random_unsigned_integer(0, 1);
		input.dwBordType = random_unsigned_integer(0, 2);
		input.dwGridSize = random_unsigned_integer(1, 4);
		for (auto i = 0; i < 5; ++i)
		{
			input.nProb[i] = random_unsigned_integer(0, 100);
			input.nTrials[i] = random_unsigned_integer(0, 1) ? -1 : static_cast<int32_t>(random_unsigned_integer(1, 5));
			input.nMax[i] = random_unsigned_integer(0, 3);
		}

		input.nSubstMethod = random_unsigned_integer(DRLGSUBST_NONE, DRLGSUBST_RANDOM);
		input.nWallLayers = random_unsigned_integer(0, DRLG_MAX_WALL_LAYERS);
		input.nFloorLayers = random_unsigned_integer(0, 1);

		input.substGroups.resize(random_unsigned_integer(nMinSubstGroups, 3));
		for (auto& substGroup : input.substGroups)
		{
			substGroup = random_subst_group();
		}

		input.presetUnits.resize(random_unsigned_integer(0, 3));
		for (auto& presetUnit : input.presetUnits)
		{
			presetUnit.nUnitType = random_unsigned_integer(0, 5);
			presetUnit.nIndex = random_unsigned_integer(0, 100);
			presetUnit.nMode = random_unsigned_integer(0, 10);
			presetUnit.nXpos = random_unsigned_integer(0, sub_grid_width * 5);
			presetUnit.nYpos = random_unsigned_integer(0, sub_grid_height * 5);
		}

		for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
		{
			input.tileTypeCells[i] = random_grid_cells<sub_grid_width, sub_grid_height>(random_tile_type);
			input.wallCells[i] = random_grid_cells<sub_grid_width, sub_grid_height>(random_sparse_cell_flags);
		}

		input.floorCells = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);
		input.shadowCells = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);
		return input;
	}

	void setup_substitution_record(D2LvlSubTxt& pLvlSubTxtRecord, SubstitutionFileData& pSubstitutionFile, const SubstitutionFileInput& input)
	{
		pLvlSubTxtRecord.dwCheckAll = input.dwCheckAll;
		pLvlSubTxtRecord.dwBordType = input.dwBordType;
		pLvlSubTxtRecord.dwGridSize = input.dwGridSize;
		for (auto i = 0; i < 5; ++i)
		{
			pLvlSubTxtRecord.nProb[i] = input.nProb[i];
			pLvlSubTxtRecord.nTrials[i] = input.nTrials[i];
			pLvlSubTxtRecord.nMax[i] = input.nMax[i];
		}

		pSubstitutionFile.tDrlgFile = {};
		pSubstitutionFile.tDrlgFile.nSubstMethod = input.nSubstMethod;
		pSubstitutionFile.tDrlgFile.nWallLayers = input.nWallLayers;
		pSubstitutionFile.tDrlgFile.nFloorLayers = input.nFloorLayers;

		pSubstitutionFile.tSubstGroups = input.substGroups;
		pSubstitutionFile.tDrlgFile.nSubstGroups = static_cast<int32_t>(pSubstitutionFile.tSubstGroups.size());
		pSubstitutionFile.tDrlgFile.pSubstGroups = pSubstitutionFile.tSubstGroups.empty() ? nullptr : pSubstitutionFile.tSubstGroups.data();

		pSubstitutionFile.tPresetUnits = input.presetUnits;
		for (size_t i = 0; i < pSubstitutionFile.tPresetUnits.size(); ++i)
		{
			pSubstitutionFile.tPresetUnits[i].pNext = i + 1 < pSubstitutionFile.tPresetUnits.size() ? &pSubstitutionFile.tPresetUnits[i + 1] : nullptr;
		}
		pSubstitutionFile.tDrlgFile.pPresetUnit = pSubstitutionFile.tPresetUnits.empty() ? nullptr : pSubstitutionFile.tPresetUnits.data();

		for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
		{
			setup_grid(pLvlSubTxtRecord.pTileTypeGrid[i], pSubstitutionFile.tileTypeGrids[i], input.tileTypeCells[i]);
			setup_grid(pLvlSubTxtRecord.pWallGrid[i], pSubstitutionFile.wallGrids[i], input.wallCells[i]);
		}

		setup_grid(pLvlSubTxtRecord.pFloorGrid, pSubstitutionFile.floorGrid, input.floorCells);
		setup_grid(pLvlSubTxtRecord.pShadowGrid, pSubstitutionFile.shadowGrid, input.shadowCells);

		// The substitution file is already loaded, so DRLGTILESUB_InitializeDrlgFile does not need to load it from an archive
		pLvlSubTxtRecord.pDrlgFile = &pSubstitutionFile.tDrlgFile;
	}

	// Random values of the grids of D2UnkOutdoorStrc2
	struct OutdoorRoomInput
	{
		int32_t nWallLayers;
		std::array<bool, DRLG_MAX_WALL_LAYERS> hasOutdoorRoom;
		std::array<bool, DRLG_MAX_WALL_LAYERS> hasWallsGrid;
		std::array<RoomGridCells, DRLG_MAX_WALL_LAYERS> tileTypeCells;
		std::array<RoomGridCells, DRLG_MAX_WALL_LAYERS> wallsCells;
		RoomGridCells floorCells;
	};

	// Storage for the grids referenced by D2UnkOutdoorStrc2
	struct OutdoorRoomData
	{
		std::array<D2DrlgOutdoorRoomStrc, DRLG_MAX_WALL_LAYERS> tOutdoorRooms;
		std::array<RoomGridData, DRLG_MAX_WALL_LAYERS> tileTypeGrids;
		std::array<D2DrlgGridStrc, DRLG_MAX_WALL_LAYERS> tWallsGrids;
		std::array<RoomGridData, DRLG_MAX_WALL_LAYERS> wallsGrids;
		D2DrlgGridStrc tFloorGrid;
		RoomGridData floorGrid;
	};

	OutdoorRoomInput random_outdoor_room_input()
	{
		OutdoorRoomInput input{};
		input.nWallLayers = random_unsigned_integer(0, DRLG_MAX_WALL_LAYERS);
		for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
		{
			// The first outdoor room and walls grid are always accessed by sub_6FD8B130
			input.hasOutdoorRoom[i] = i == 0 || random_unsigned_integer(0, 1);
			input.hasWallsGrid[i] = i == 0 || random_unsigned_integer(0, 1);
			input.tileTypeCells[i] = random_grid_cells<room_grid_size, room_grid_size>(random_tile_type);
			input.wallsCells[i] = random_grid_cells<room_grid_size, room_grid_size>(random_sparse_cell_flags);
		}

		input.floorCells = random_grid_cells<room_grid_size, room_grid_size>(random_floor_cell_flags);
		return input;
	}

	void setup_outdoor_room(D2UnkOutdoorStrc2& pOutdoorLevel, OutdoorRoomData& pOutdoorRoom, const OutdoorRoomInput& input)
	{
		for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
		{
			setup_grid(pOutdoorRoom.tOutdoorRooms[i].pTileTypeGrid, pOutdoorRoom.tileTypeGrids[i], input.tileTypeCells[i]);
			pOutdoorLevel.pOutdoorRooms[i] = input.hasOutdoorRoom[i] ? &pOutdoorRoom.tOutdoorRooms[i] : nullptr;

			setup_grid(pOutdoorRoom.tWallsGrids[i], pOutdoorRoom.wallsGrids[i], input.wallsCells[i]);
			pOutdoorLevel.pWallsGrids[i] = input.hasWallsGrid[i] ? &pOutdoorRoom.tWallsGrids[i] : nullptr;
		}

		setup_grid(pOutdoorRoom.tFloorGrid, pOutdoorRoom.floorGrid, input.floorCells);
		pOutdoorLevel.pFloorGrid = &pOutdoorRoom.tFloorGrid;
		pOutdoorLevel.field_2C = input.nWallLayers;
	}

	void check_outdoor_room_eq(const OutdoorRoomData& moo_pOutdoorRoom, const OutdoorRoomData& original_pOutdoorRoom)
	{
		check_values_eq(get_grid_values(moo_pOutdoorRoom.tFloorGrid), get_grid_values(original_pOutdoorRoom.tFloorGrid), "Comparing pFloorGrid");
		for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
		{
			check_values_eq(get_grid_values(moo_pOutdoorRoom.tWallsGrids[i]), get_grid_values(original_pOutdoorRoom.tWallsGrids[i]), "Comparing pWallsGrids");
			check_values_eq(get_grid_values(moo_pOutdoorRoom.tOutdoorRooms[i].pTileTypeGrid), get_grid_values(original_pOutdoorRoom.tOutdoorRooms[i].pTileTypeGrid), "Comparing pOutdoorRooms->pTileTypeGrid");
		}
	}


	// Records of LvlSub.txt that share the same dwType
	struct LvlSubTypeRange
	{
		int nType;
		int nFirstRecord;
		int nRecordCount;
	};

	// Returns the record ranges that DATATBLS_GetLvlSubTxtRecord returns for each type.
	// Types whose records are the last ones of the table are excluded, since the iteration over the records of a type
	// stops at the first record of another type and would read past the end of the table.
	std::vector<LvlSubTypeRange> get_lvlsub_type_ranges(const D2LvlSubTxt* pLvlSubTxt, int nRecordCount)
	{
		std::map<int, LvlSubTypeRange> ranges;
		for (auto i = 0; i < nRecordCount;)
		{
			const int nType = pLvlSubTxt[i].dwType;
			auto nCount = 0;
			while (i + nCount < nRecordCount && pLvlSubTxt[i + nCount].dwType == nType)
			{
				++nCount;
			}

			if (i + nCount < nRecordCount)
			{
				ranges[nType] = LvlSubTypeRange{ nType, i, nCount };
			}
			else
			{
				ranges.erase(nType);
			}

			i += nCount;
		}

		std::vector<LvlSubTypeRange> result;
		for (const auto& [nType, range] : ranges)
		{
			result.push_back(range);
		}

		return result;
	}

	void install_lvlsub_records(D2LvlSubTxt* pLvlSubTxt, const LvlSubTypeRange& range, const std::vector<D2LvlSubTxt>& records)
	{
		std::copy(records.begin(), records.end(), pLvlSubTxt + range.nFirstRecord);
	}
}


TEST_SUITE("D2DrlgTileSubTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(LvlSubTxtFixture<NoopFixture>, "D2Common.0x6FD8A460" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_AddSecondaryBorder, dll_base + 0x0004A460);

		const auto type_ranges = get_lvlsub_type_ranges(lvlsub_txt.get(), lvlsub_record_count);
		REQUIRE_FALSE(type_ranges.empty());

		REPEAT_5();

		SUBCASE("")
		{
			for (const auto& type_range : type_ranges)
			{
				// Input data
				const auto level_id = random_unsigned_integer(LEVEL_BLOODMOOR - 1, LEVEL_TAMOEHIGHLAND + 1);
				const auto outdoor_flags = random_unsigned_integer(0, 15);
				const auto low_seed = random_unsigned_integer();
				const auto high_seed = random_unsigned_integer();
				// Keeps the area of the possible positions at most 256, which is the size of the coordinate buffer
				const auto width = random_unsigned_integer(0, 15);
				const auto height = random_unsigned_integer(0, 15);
				const auto level_prest_id = random_unsigned_integer(0, 3);
				const auto field_14 = static_cast<int32_t>(random_unsigned_integer(0, 4)) - 1;
				const auto use_field_24 = random_unsigned_integer(0, 1);
				const auto grid1_cells = random_grid_cells<outdoor_grid_size, outdoor_grid_size>(random_level_prest_id);
				const auto lvlsub_records = lvlsub_txt.get() + type_range.nFirstRecord;

				std::vector<SubstitutionFileInput> substitution_files(type_range.nRecordCount);
				for (auto& substitution_file : substitution_files)
				{
					substitution_file = random_substitution_file_input(0);
				}

				D2UnkOutdoorStrc moo_a1{};
				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgStrc moo_pDrlg{};
				D2DrlgOutdoorInfoStrc moo_pOutdoors{};
				std::array<int32_t, 4> moo_field_4{};
				D2DrlgGridStrc moo_pGrid1{};
				OutdoorGridData moo_pGrid1Data{};
				std::vector<D2LvlSubTxt> moo_pLvlSubTxtRecords(type_range.nRecordCount);
				std::vector<SubstitutionFileData> moo_pSubstitutionFiles(type_range.nRecordCount);
				D2UnkOutdoorStrc original_a1{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgStrc original_pDrlg{};
				D2DrlgOutdoorInfoStrc original_pOutdoors{};
				std::array<int32_t, 4> original_field_4{};
				D2DrlgGridStrc original_pGrid1{};
				OutdoorGridData original_pGrid1Data{};
				std::vector<D2LvlSubTxt> original_pLvlSubTxtRecords(type_range.nRecordCount);
				std::vector<SubstitutionFileData> original_pSubstitutionFiles(type_range.nRecordCount);

				const auto setup_data = [&type_range, level_id, outdoor_flags, low_seed, high_seed, width, height, level_prest_id, field_14, use_field_24, &grid1_cells, lvlsub_records, &substitution_files](
					D2UnkOutdoorStrc& a1,
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgOutdoorInfoStrc& pOutdoors,
					std::array<int32_t, 4>& field_4,
					D2DrlgGridStrc& pGrid1,
					OutdoorGridData& pGrid1Data,
					std::vector<D2LvlSubTxt>& pLvlSubTxtRecords,
					std::vector<SubstitutionFileData>& pSubstitutionFiles
				) {
					pOutdoors.dwFlags = outdoor_flags;

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = level_id;
					pLevel.pSeed.nLowSeed = low_seed;
					pLevel.pSeed.nHighSeed = high_seed;
					pLevel.pOutdoors = &pOutdoors;

					field_4[2] = width;
					field_4[3] = height;

					setup_grid(pGrid1, pGrid1Data, grid1_cells);

					for (auto i = 0; i < type_range.nRecordCount; ++i)
					{
						pLvlSubTxtRecords[i] = lvlsub_records[i];
						setup_substitution_record(pLvlSubTxtRecords[i], pSubstitutionFiles[i], substitution_files[i]);
					}

					a1.pLevel = &pLevel;
					a1.field_4 = field_4.data();
					a1.pGrid1 = &pGrid1;
					a1.nLevelPrestId = level_prest_id;
					a1.field_14 = field_14;
					a1.nLvlSubId = type_range.nType;
					a1.field_1C = test_field_1C;
					a1.field_20 = test_field_20;
					a1.field_24 = use_field_24 ? test_field_24 : nullptr;
					a1.field_28 = test_field_28;
					a1.field_2C = test_field_2C;
					a1.field_30 = test_field_30;
					a1.field_34 = test_field_34;
				};

				setup_data(moo_a1, moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_field_4, moo_pGrid1, moo_pGrid1Data, moo_pLvlSubTxtRecords, moo_pSubstitutionFiles);
				setup_data(original_a1, original_pLevel, original_pDrlg, original_pOutdoors, original_field_4, original_pGrid1, original_pGrid1Data, original_pLvlSubTxtRecords, original_pSubstitutionFiles);

				// Call both implementations
				callback_calls.clear();
				install_lvlsub_records(lvlsub_txt.get(), type_range, moo_pLvlSubTxtRecords);
				sut(&moo_a1);
				const auto moo_callback_calls = std::exchange(callback_calls, {});

				install_lvlsub_records(lvlsub_txt.get(), type_range, original_pLvlSubTxtRecords);
				original(&original_a1);
				const auto original_callback_calls = std::exchange(callback_calls, {});

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
				MOO_CHECK_EQ(moo_pLevel.pSeed, original_pLevel.pSeed, "Comparing pLevel->pSeed");
				check_values_eq(moo_callback_calls, original_callback_calls, "Comparing callback calls");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8A750")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_TestReplaceSubPreset, dll_base + 0x0004A750);

		const auto use_field_24 = GENERATE(0, 1);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto grid_size = random_unsigned_integer(1, 4);
			const auto wall_layers = random_unsigned_integer(0, 1);
			const auto floor_layers = random_unsigned_integer(0, 1);
			const auto subst_group = random_subst_group();
			const auto floor_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);
			const auto wall_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_sparse_cell_flags);
			const auto grid1_cells = random_grid_cells<outdoor_grid_size, outdoor_grid_size>(random_level_prest_id);
			const auto level_prest_id = random_unsigned_integer(0, 3);
			const auto field_14 = static_cast<int32_t>(random_unsigned_integer(0, 4)) - 1;

			D2UnkOutdoorStrc moo_a3{};
			D2DrlgGridStrc moo_pGrid1{};
			OutdoorGridData moo_pGrid1Data{};
			D2DrlgSubstGroupStrc moo_pSubstGroup{};
			D2LvlSubTxt moo_pLvlSubTxtRecord{};
			D2DrlgFileStrc moo_pDrlgFile{};
			SubGridData moo_pFloorGridData{};
			SubGridData moo_pWallGridData{};
			D2UnkOutdoorStrc original_a3{};
			D2DrlgGridStrc original_pGrid1{};
			OutdoorGridData original_pGrid1Data{};
			D2DrlgSubstGroupStrc original_pSubstGroup{};
			D2LvlSubTxt original_pLvlSubTxtRecord{};
			D2DrlgFileStrc original_pDrlgFile{};
			SubGridData original_pFloorGridData{};
			SubGridData original_pWallGridData{};
			int a1 = random_unsigned_integer(0, 15);
			int a2 = random_unsigned_integer(0, 15);

			const auto setup_data = [use_field_24, grid_size, wall_layers, floor_layers, &subst_group, &floor_cells, &wall_cells, &grid1_cells, level_prest_id, field_14](
				D2UnkOutdoorStrc& a3,
				D2DrlgGridStrc& pGrid1,
				OutdoorGridData& pGrid1Data,
				D2DrlgSubstGroupStrc& pSubstGroup,
				D2LvlSubTxt& pLvlSubTxtRecord,
				D2DrlgFileStrc& pDrlgFile,
				SubGridData& pFloorGridData,
				SubGridData& pWallGridData
			) {
				pDrlgFile.nWallLayers = wall_layers;
				pDrlgFile.nFloorLayers = floor_layers;

				pLvlSubTxtRecord.dwGridSize = grid_size;
				pLvlSubTxtRecord.pDrlgFile = &pDrlgFile;
				setup_grid(pLvlSubTxtRecord.pFloorGrid, pFloorGridData, floor_cells);
				setup_grid(pLvlSubTxtRecord.pWallGrid[0], pWallGridData, wall_cells);

				pSubstGroup = subst_group;

				setup_grid(pGrid1, pGrid1Data, grid1_cells);

				a3.pGrid1 = &pGrid1;
				a3.nLevelPrestId = level_prest_id;
				a3.field_14 = field_14;
				a3.field_1C = test_field_1C;
				a3.field_20 = test_field_20;
				a3.field_24 = use_field_24 ? test_field_24 : nullptr;
			};

			setup_data(moo_a3, moo_pGrid1, moo_pGrid1Data, moo_pSubstGroup, moo_pLvlSubTxtRecord, moo_pDrlgFile, moo_pFloorGridData, moo_pWallGridData);
			setup_data(original_a3, original_pGrid1, original_pGrid1Data, original_pSubstGroup, original_pLvlSubTxtRecord, original_pDrlgFile, original_pFloorGridData, original_pWallGridData);

			// Call both implementations
			callback_calls.clear();
			const auto moo_result = sut(a1, a2, &moo_a3, &moo_pSubstGroup, &moo_pLvlSubTxtRecord);
			const auto moo_callback_calls = std::exchange(callback_calls, {});

			const auto original_result = original(a1, a2, &original_a3, &original_pSubstGroup, &original_pLvlSubTxtRecord);
			const auto original_callback_calls = std::exchange(callback_calls, {});

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			MOO_CHECK_EQ(moo_pSubstGroup, original_pSubstGroup, "Comparing pSubstGroup");
			MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
			check_values_eq(moo_callback_calls, original_callback_calls, "Comparing callback calls");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8A8E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_ReplaceSubPreset, dll_base + 0x0004A8E0);

		const auto use_field_28 = GENERATE(0, 1);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto grid_size = random_unsigned_integer(1, 4);
			const auto wall_layers = random_unsigned_integer(0, 1);
			const auto floor_layers = random_unsigned_integer(0, 1);
			const auto subst_group = random_subst_group();
			const auto floor_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);
			const auto wall_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_sparse_cell_flags);
			const auto level_prest_id = random_unsigned_integer(0, 3);
			const auto field_14 = static_cast<int32_t>(random_unsigned_integer(0, 4)) - 1;

			D2UnkOutdoorStrc moo_a3{};
			D2DrlgSubstGroupStrc moo_pSubstGroup{};
			D2LvlSubTxt moo_pLvlSubTxtRecord{};
			D2DrlgFileStrc moo_pDrlgFile{};
			SubGridData moo_pFloorGridData{};
			SubGridData moo_pWallGridData{};
			D2UnkOutdoorStrc original_a3{};
			D2DrlgSubstGroupStrc original_pSubstGroup{};
			D2LvlSubTxt original_pLvlSubTxtRecord{};
			D2DrlgFileStrc original_pDrlgFile{};
			SubGridData original_pFloorGridData{};
			SubGridData original_pWallGridData{};
			int a1 = random_unsigned_integer(0, 15);
			int a2 = random_unsigned_integer(0, 15);
			// Offset of the alternative substitution within the substitution file grids
			int a6 = random_unsigned_integer(0, 12);

			const auto setup_data = [use_field_28, grid_size, wall_layers, floor_layers, &subst_group, &floor_cells, &wall_cells, level_prest_id, field_14](
				D2UnkOutdoorStrc& a3,
				D2DrlgSubstGroupStrc& pSubstGroup,
				D2LvlSubTxt& pLvlSubTxtRecord,
				D2DrlgFileStrc& pDrlgFile,
				SubGridData& pFloorGridData,
				SubGridData& pWallGridData
			) {
				pDrlgFile.nWallLayers = wall_layers;
				pDrlgFile.nFloorLayers = floor_layers;

				pLvlSubTxtRecord.dwGridSize = grid_size;
				pLvlSubTxtRecord.pDrlgFile = &pDrlgFile;
				setup_grid(pLvlSubTxtRecord.pFloorGrid, pFloorGridData, floor_cells);
				setup_grid(pLvlSubTxtRecord.pWallGrid[0], pWallGridData, wall_cells);

				pSubstGroup = subst_group;

				a3.nLevelPrestId = level_prest_id;
				a3.field_14 = field_14;
				a3.field_28 = use_field_28 ? test_field_28 : nullptr;
				a3.field_2C = test_field_2C;
				a3.field_30 = test_field_30;
				a3.field_34 = test_field_34;
			};

			setup_data(moo_a3, moo_pSubstGroup, moo_pLvlSubTxtRecord, moo_pDrlgFile, moo_pFloorGridData, moo_pWallGridData);
			setup_data(original_a3, original_pSubstGroup, original_pLvlSubTxtRecord, original_pDrlgFile, original_pFloorGridData, original_pWallGridData);

			// Call both implementations
			callback_calls.clear();
			sut(a1, a2, &moo_a3, &moo_pSubstGroup, &moo_pLvlSubTxtRecord, a6);
			const auto moo_callback_calls = std::exchange(callback_calls, {});

			original(a1, a2, &original_a3, &original_pSubstGroup, &original_pLvlSubTxtRecord, a6);
			const auto original_callback_calls = std::exchange(callback_calls, {});

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			MOO_CHECK_EQ(moo_pSubstGroup, original_pSubstGroup, "Comparing pSubstGroup");
			MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
			check_values_eq(moo_callback_calls, original_callback_calls, "Comparing callback calls");
		}
	}

	TEST_CASE_FIXTURE(LvlSubTxtFixture<NoopFixture>, "D2Common.0x6FD8AA80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD8AA80, dll_base + 0x0004AA80);

		const auto type_ranges = get_lvlsub_type_ranges(lvlsub_txt.get(), lvlsub_record_count);
		REQUIRE_FALSE(type_ranges.empty());

		REPEAT_5();

		SUBCASE("no substitution type")
		{
			// Input data
			D2UnkOutdoorStrc2 moo_a1{};
			D2UnkOutdoorStrc2 original_a1{};

			const auto setup_data = [](
				D2UnkOutdoorStrc2& a1
			) {
				a1.nSubWaypoint_Shrine = -1;
			};

			setup_data(moo_a1);
			setup_data(original_a1);

			// Call both implementations
			sut(&moo_a1);
			original(&original_a1);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
		}

		SUBCASE("substitutions")
		{
			for (const auto& type_range : type_ranges)
			{
				// Input data
				const auto record_count = std::min(type_range.nRecordCount, 8);
				const auto sub_theme = random_unsigned_integer(0, 4);
				const auto sub_theme_picked = random_unsigned_integer(1, (1u << record_count) - 1);
				const auto tile_width = random_unsigned_integer(4, room_grid_size);
				const auto tile_height = random_unsigned_integer(4, room_grid_size);
				const auto low_seed = random_unsigned_integer();
				const auto high_seed = random_unsigned_integer();
				const auto outdoor_room = random_outdoor_room_input();
				const auto lvlsub_records = lvlsub_txt.get() + type_range.nFirstRecord;

				std::vector<SubstitutionFileInput> substitution_files(type_range.nRecordCount);
				for (auto& substitution_file : substitution_files)
				{
					substitution_file = random_substitution_file_input(0);
				}

				D2UnkOutdoorStrc2 moo_a1{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgStrc moo_pDrlg{};
				OutdoorRoomData moo_pOutdoorRoom{};
				std::vector<D2LvlSubTxt> moo_pLvlSubTxtRecords(type_range.nRecordCount);
				std::vector<SubstitutionFileData> moo_pSubstitutionFiles(type_range.nRecordCount);
				D2UnkOutdoorStrc2 original_a1{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgStrc original_pDrlg{};
				OutdoorRoomData original_pOutdoorRoom{};
				std::vector<D2LvlSubTxt> original_pLvlSubTxtRecords(type_range.nRecordCount);
				std::vector<SubstitutionFileData> original_pSubstitutionFiles(type_range.nRecordCount);

				const auto setup_data = [&type_range, sub_theme, sub_theme_picked, tile_width, tile_height, low_seed, high_seed, &outdoor_room, lvlsub_records, &substitution_files](
					D2UnkOutdoorStrc2& a1,
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					OutdoorRoomData& pOutdoorRoom,
					std::vector<D2LvlSubTxt>& pLvlSubTxtRecords,
					std::vector<SubstitutionFileData>& pSubstitutionFiles
				) {
					pLevel.pDrlg = &pDrlg;

					pDrlgRoom.pLevel = &pLevel;
					pDrlgRoom.nTileWidth = tile_width;
					pDrlgRoom.nTileHeight = tile_height;
					pDrlgRoom.pSeed.nLowSeed = low_seed;
					pDrlgRoom.pSeed.nHighSeed = high_seed;

					for (auto i = 0; i < type_range.nRecordCount; ++i)
					{
						pLvlSubTxtRecords[i] = lvlsub_records[i];
						setup_substitution_record(pLvlSubTxtRecords[i], pSubstitutionFiles[i], substitution_files[i]);
					}

					setup_outdoor_room(a1, pOutdoorRoom, outdoor_room);
					a1.pDrlgRoom = &pDrlgRoom;
					a1.nSubWaypoint_Shrine = type_range.nType;
					a1.nSubTheme = sub_theme;
					a1.nSubThemePicked = sub_theme_picked;
				};

				setup_data(moo_a1, moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pOutdoorRoom, moo_pLvlSubTxtRecords, moo_pSubstitutionFiles);
				setup_data(original_a1, original_pDrlgRoom, original_pLevel, original_pDrlg, original_pOutdoorRoom, original_pLvlSubTxtRecords, original_pSubstitutionFiles);

				// Call both implementations
				install_lvlsub_records(lvlsub_txt.get(), type_range, moo_pLvlSubTxtRecords);
				sut(&moo_a1);

				install_lvlsub_records(lvlsub_txt.get(), type_range, original_pLvlSubTxtRecords);
				original(&original_a1);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
				MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
				check_outdoor_room_eq(moo_pOutdoorRoom, original_pOutdoorRoom);
				check_values_eq(get_preset_unit_values(moo_pDrlgRoom.pPresetUnits), get_preset_unit_values(original_pDrlgRoom.pPresetUnits), "Comparing pDrlgRoom->pPresetUnits");

				// Clean up the allocated preset units
				free_preset_units(moo_pDrlgRoom.pPresetUnits);
				free_preset_units(original_pDrlgRoom.pPresetUnits);
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8ACE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD8ACE0, dll_base + 0x0004ACE0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto substitution_file = random_substitution_file_input(1);
			const auto subst_group = random_subst_group();
			const auto outdoor_room = random_outdoor_room_input();

			D2UnkOutdoorStrc2 moo_a4{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			OutdoorRoomData moo_pOutdoorRoom{};
			D2DrlgSubstGroupStrc moo_pSubstGroup{};
			D2LvlSubTxt moo_pLvlSubTxtRecord{};
			SubstitutionFileData moo_pSubstitutionFile{};
			D2UnkOutdoorStrc2 original_a4{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			OutdoorRoomData original_pOutdoorRoom{};
			D2DrlgSubstGroupStrc original_pSubstGroup{};
			D2LvlSubTxt original_pLvlSubTxtRecord{};
			SubstitutionFileData original_pSubstitutionFile{};
			int nX = random_unsigned_integer(0, room_grid_size - subst_group.tBox.nWidth);
			int nY = random_unsigned_integer(0, room_grid_size - subst_group.tBox.nHeight);
			// Offset of the alternative substitution within the substitution file grids
			int a7 = random_unsigned_integer(0, 12);

			const auto setup_data = [&substitution_file, &subst_group, &outdoor_room](
				D2UnkOutdoorStrc2& a4,
				D2DrlgRoomStrc& pDrlgRoom,
				OutdoorRoomData& pOutdoorRoom,
				D2DrlgSubstGroupStrc& pSubstGroup,
				D2LvlSubTxt& pLvlSubTxtRecord,
				SubstitutionFileData& pSubstitutionFile
			) {
				setup_substitution_record(pLvlSubTxtRecord, pSubstitutionFile, substitution_file);

				pSubstGroup = subst_group;

				setup_outdoor_room(a4, pOutdoorRoom, outdoor_room);
				a4.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_a4, moo_pDrlgRoom, moo_pOutdoorRoom, moo_pSubstGroup, moo_pLvlSubTxtRecord, moo_pSubstitutionFile);
			setup_data(original_a4, original_pDrlgRoom, original_pOutdoorRoom, original_pSubstGroup, original_pLvlSubTxtRecord, original_pSubstitutionFile);

			// Call both implementations
			sut(nullptr, nX, nY, &moo_a4, &moo_pSubstGroup, &moo_pLvlSubTxtRecord, a7);
			original(nullptr, nX, nY, &original_a4, &original_pSubstGroup, &original_pLvlSubTxtRecord, a7);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
			MOO_CHECK_EQ(moo_pSubstGroup, original_pSubstGroup, "Comparing pSubstGroup");
			MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			check_outdoor_room_eq(moo_pOutdoorRoom, original_pOutdoorRoom);
			check_values_eq(get_preset_unit_values(moo_pDrlgRoom.pPresetUnits), get_preset_unit_values(original_pDrlgRoom.pPresetUnits), "Comparing pDrlgRoom->pPresetUnits");

			// Clean up the allocated preset units
			free_preset_units(moo_pDrlgRoom.pPresetUnits);
			free_preset_units(original_pDrlgRoom.pPresetUnits);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B010")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD8B010, dll_base + 0x0004B010);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto subst_group = random_subst_group();
			const auto sub_floor_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);
			const auto sub_wall_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_sparse_cell_flags);
			const auto floor_cells = random_grid_cells<room_grid_size, room_grid_size>(random_floor_cell_flags);
			const auto wall_layers = random_unsigned_integer(0, DRLG_MAX_WALL_LAYERS);

			std::array<bool, DRLG_MAX_WALL_LAYERS> has_walls_grid{};
			std::array<RoomGridCells, DRLG_MAX_WALL_LAYERS> walls_cells{};
			for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
			{
				has_walls_grid[i] = random_unsigned_integer(0, 1);
				walls_cells[i] = random_grid_cells<room_grid_size, room_grid_size>(random_sparse_cell_flags);
			}

			D2UnkOutdoorStrc2 moo_a3{};
			D2DrlgGridStrc moo_pFloorGrid{};
			RoomGridData moo_pFloorGridData{};
			std::array<D2DrlgGridStrc, DRLG_MAX_WALL_LAYERS> moo_pWallsGrids{};
			std::array<RoomGridData, DRLG_MAX_WALL_LAYERS> moo_pWallsGridData{};
			D2DrlgSubstGroupStrc moo_pSubstGroup{};
			D2LvlSubTxt moo_pLvlSubTxtRecord{};
			SubGridData moo_pSubFloorGridData{};
			SubGridData moo_pSubWallGridData{};
			D2UnkOutdoorStrc2 original_a3{};
			D2DrlgGridStrc original_pFloorGrid{};
			RoomGridData original_pFloorGridData{};
			std::array<D2DrlgGridStrc, DRLG_MAX_WALL_LAYERS> original_pWallsGrids{};
			std::array<RoomGridData, DRLG_MAX_WALL_LAYERS> original_pWallsGridData{};
			D2DrlgSubstGroupStrc original_pSubstGroup{};
			D2LvlSubTxt original_pLvlSubTxtRecord{};
			SubGridData original_pSubFloorGridData{};
			SubGridData original_pSubWallGridData{};
			int a1 = random_unsigned_integer(0, room_grid_size - subst_group.tBox.nWidth);
			int a2 = random_unsigned_integer(0, room_grid_size - subst_group.tBox.nHeight);

			const auto setup_data = [&subst_group, &sub_floor_cells, &sub_wall_cells, &floor_cells, wall_layers, &has_walls_grid, &walls_cells](
				D2UnkOutdoorStrc2& a3,
				D2DrlgGridStrc& pFloorGrid,
				RoomGridData& pFloorGridData,
				std::array<D2DrlgGridStrc, DRLG_MAX_WALL_LAYERS>& pWallsGrids,
				std::array<RoomGridData, DRLG_MAX_WALL_LAYERS>& pWallsGridData,
				D2DrlgSubstGroupStrc& pSubstGroup,
				D2LvlSubTxt& pLvlSubTxtRecord,
				SubGridData& pSubFloorGridData,
				SubGridData& pSubWallGridData
			) {
				setup_grid(pLvlSubTxtRecord.pFloorGrid, pSubFloorGridData, sub_floor_cells);
				setup_grid(pLvlSubTxtRecord.pWallGrid[0], pSubWallGridData, sub_wall_cells);

				pSubstGroup = subst_group;

				setup_grid(pFloorGrid, pFloorGridData, floor_cells);
				a3.pFloorGrid = &pFloorGrid;

				for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
				{
					setup_grid(pWallsGrids[i], pWallsGridData[i], walls_cells[i]);
					a3.pWallsGrids[i] = has_walls_grid[i] ? &pWallsGrids[i] : nullptr;
				}

				a3.field_2C = wall_layers;
			};

			setup_data(moo_a3, moo_pFloorGrid, moo_pFloorGridData, moo_pWallsGrids, moo_pWallsGridData, moo_pSubstGroup, moo_pLvlSubTxtRecord, moo_pSubFloorGridData, moo_pSubWallGridData);
			setup_data(original_a3, original_pFloorGrid, original_pFloorGridData, original_pWallsGrids, original_pWallsGridData, original_pSubstGroup, original_pLvlSubTxtRecord, original_pSubFloorGridData, original_pSubWallGridData);

			// Call both implementations
			const auto moo_result = sut(a1, a2, &moo_a3, &moo_pSubstGroup, &moo_pLvlSubTxtRecord);
			const auto original_result = original(a1, a2, &original_a3, &original_pSubstGroup, &original_pLvlSubTxtRecord);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			MOO_CHECK_EQ(moo_pSubstGroup, original_pSubstGroup, "Comparing pSubstGroup");
			MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B130")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD8B130, dll_base + 0x0004B130);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto subst_group = random_subst_group();
			const auto wall_layers = random_unsigned_integer(0, 1);
			const auto floor_layers = random_unsigned_integer(0, 1);
			const auto sub_tile_type_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_tile_type);
			const auto sub_floor_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);
			const auto sub_wall_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_sparse_cell_flags);
			const auto tile_type_cells = random_grid_cells<room_grid_size, room_grid_size>(random_tile_type);
			const auto floor_cells = random_grid_cells<room_grid_size, room_grid_size>(random_floor_cell_flags);
			const auto wall_cells = random_grid_cells<room_grid_size, room_grid_size>(random_sparse_cell_flags);

			D2UnkOutdoorStrc2 moo_a3{};
			D2DrlgOutdoorRoomStrc moo_pOutdoorRoom{};
			RoomGridData moo_pTileTypeGridData{};
			D2DrlgGridStrc moo_pFloorGrid{};
			RoomGridData moo_pFloorGridData{};
			D2DrlgGridStrc moo_pWallGrid{};
			RoomGridData moo_pWallGridData{};
			D2DrlgSubstGroupStrc moo_pSubstGroup{};
			D2LvlSubTxt moo_pLvlSubTxtRecord{};
			D2DrlgFileStrc moo_pDrlgFile{};
			SubGridData moo_pSubTileTypeGridData{};
			SubGridData moo_pSubFloorGridData{};
			SubGridData moo_pSubWallGridData{};
			D2UnkOutdoorStrc2 original_a3{};
			D2DrlgOutdoorRoomStrc original_pOutdoorRoom{};
			RoomGridData original_pTileTypeGridData{};
			D2DrlgGridStrc original_pFloorGrid{};
			RoomGridData original_pFloorGridData{};
			D2DrlgGridStrc original_pWallGrid{};
			RoomGridData original_pWallGridData{};
			D2DrlgSubstGroupStrc original_pSubstGroup{};
			D2LvlSubTxt original_pLvlSubTxtRecord{};
			D2DrlgFileStrc original_pDrlgFile{};
			SubGridData original_pSubTileTypeGridData{};
			SubGridData original_pSubFloorGridData{};
			SubGridData original_pSubWallGridData{};
			int a1 = random_unsigned_integer(0, room_grid_size - subst_group.tBox.nWidth);
			int a2 = random_unsigned_integer(0, room_grid_size - subst_group.tBox.nHeight);

			const auto setup_data = [&subst_group, wall_layers, floor_layers, &sub_tile_type_cells, &sub_floor_cells, &sub_wall_cells, &tile_type_cells, &floor_cells, &wall_cells](
				D2UnkOutdoorStrc2& a3,
				D2DrlgOutdoorRoomStrc& pOutdoorRoom,
				RoomGridData& pTileTypeGridData,
				D2DrlgGridStrc& pFloorGrid,
				RoomGridData& pFloorGridData,
				D2DrlgGridStrc& pWallGrid,
				RoomGridData& pWallGridData,
				D2DrlgSubstGroupStrc& pSubstGroup,
				D2LvlSubTxt& pLvlSubTxtRecord,
				D2DrlgFileStrc& pDrlgFile,
				SubGridData& pSubTileTypeGridData,
				SubGridData& pSubFloorGridData,
				SubGridData& pSubWallGridData
			) {
				pDrlgFile.nWallLayers = wall_layers;
				pDrlgFile.nFloorLayers = floor_layers;

				pLvlSubTxtRecord.pDrlgFile = &pDrlgFile;
				setup_grid(pLvlSubTxtRecord.pTileTypeGrid[0], pSubTileTypeGridData, sub_tile_type_cells);
				setup_grid(pLvlSubTxtRecord.pFloorGrid, pSubFloorGridData, sub_floor_cells);
				setup_grid(pLvlSubTxtRecord.pWallGrid[0], pSubWallGridData, sub_wall_cells);

				pSubstGroup = subst_group;

				setup_grid(pOutdoorRoom.pTileTypeGrid, pTileTypeGridData, tile_type_cells);
				setup_grid(pFloorGrid, pFloorGridData, floor_cells);
				setup_grid(pWallGrid, pWallGridData, wall_cells);

				a3.pOutdoorRooms[0] = &pOutdoorRoom;
				a3.pFloorGrid = &pFloorGrid;
				a3.pWallsGrids[0] = &pWallGrid;
			};

			setup_data(moo_a3, moo_pOutdoorRoom, moo_pTileTypeGridData, moo_pFloorGrid, moo_pFloorGridData, moo_pWallGrid, moo_pWallGridData, moo_pSubstGroup, moo_pLvlSubTxtRecord, moo_pDrlgFile, moo_pSubTileTypeGridData, moo_pSubFloorGridData, moo_pSubWallGridData);
			setup_data(original_a3, original_pOutdoorRoom, original_pTileTypeGridData, original_pFloorGrid, original_pFloorGridData, original_pWallGrid, original_pWallGridData, original_pSubstGroup, original_pLvlSubTxtRecord, original_pDrlgFile, original_pSubTileTypeGridData, original_pSubFloorGridData, original_pSubWallGridData);

			// Call both implementations
			const auto moo_result = sut(a1, a2, &moo_a3, &moo_pSubstGroup, &moo_pLvlSubTxtRecord);
			const auto original_result = original(a1, a2, &original_a3, &original_pSubstGroup, &original_pLvlSubTxtRecord);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			MOO_CHECK_EQ(moo_pSubstGroup, original_pSubstGroup, "Comparing pSubstGroup");
			MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B290")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_DoSubstitutions, dll_base + 0x0004B290);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto substitution_file = random_substitution_file_input(0);
			const auto outdoor_room = random_outdoor_room_input();
			const auto sub_theme = random_unsigned_integer(0, 4);
			// Keeps the area of the possible positions at most 256, which is the size of the coordinate buffer
			const auto tile_width = random_unsigned_integer(4, room_grid_size);
			const auto tile_height = random_unsigned_integer(4, room_grid_size);
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();

			D2UnkOutdoorStrc2 moo_pOutdoorLevel{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			OutdoorRoomData moo_pOutdoorRoom{};
			D2LvlSubTxt moo_pLvlSubTxtRecord{};
			SubstitutionFileData moo_pSubstitutionFile{};
			D2UnkOutdoorStrc2 original_pOutdoorLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			OutdoorRoomData original_pOutdoorRoom{};
			D2LvlSubTxt original_pLvlSubTxtRecord{};
			SubstitutionFileData original_pSubstitutionFile{};

			const auto setup_data = [&substitution_file, &outdoor_room, sub_theme, tile_width, tile_height, low_seed, high_seed](
				D2UnkOutdoorStrc2& pOutdoorLevel,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				OutdoorRoomData& pOutdoorRoom,
				D2LvlSubTxt& pLvlSubTxtRecord,
				SubstitutionFileData& pSubstitutionFile
			) {
				setup_substitution_record(pLvlSubTxtRecord, pSubstitutionFile, substitution_file);

				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileWidth = tile_width;
				pDrlgRoom.nTileHeight = tile_height;
				pDrlgRoom.pSeed.nLowSeed = low_seed;
				pDrlgRoom.pSeed.nHighSeed = high_seed;

				setup_outdoor_room(pOutdoorLevel, pOutdoorRoom, outdoor_room);
				pOutdoorLevel.pDrlgRoom = &pDrlgRoom;
				pOutdoorLevel.nSubTheme = sub_theme;
			};

			setup_data(moo_pOutdoorLevel, moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pOutdoorRoom, moo_pLvlSubTxtRecord, moo_pSubstitutionFile);
			setup_data(original_pOutdoorLevel, original_pDrlgRoom, original_pLevel, original_pDrlg, original_pOutdoorRoom, original_pLvlSubTxtRecord, original_pSubstitutionFile);

			// Call both implementations
			sut(&moo_pOutdoorLevel, &moo_pLvlSubTxtRecord);
			original(&original_pOutdoorLevel, &original_pLvlSubTxtRecord);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pOutdoorLevel, original_pOutdoorLevel, "Comparing pOutdoorLevel");
			MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			check_outdoor_room_eq(moo_pOutdoorRoom, original_pOutdoorRoom);
			check_values_eq(get_preset_unit_values(moo_pDrlgRoom.pPresetUnits), get_preset_unit_values(original_pDrlgRoom.pPresetUnits), "Comparing pDrlgRoom->pPresetUnits");

			// Clean up the allocated preset units
			free_preset_units(moo_pDrlgRoom.pPresetUnits);
			free_preset_units(original_pDrlgRoom.pPresetUnits);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B640")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_InitializeDrlgFile, dll_base + 0x0004B640);

		auto& original_gpLevelFilesList = *reinterpret_cast<D2LevelFileListStrc**>(dll_base + level_files_list_offset);

		REPEAT_10();

		SUBCASE("already initialized")
		{
			// Input data
			D2LvlSubTxt moo_pLvlSubTxtRecord{};
			D2DrlgFileStrc moo_pDrlgFile{};
			D2LvlSubTxt original_pLvlSubTxtRecord{};
			D2DrlgFileStrc original_pDrlgFile{};
			HD2ARCHIVE hArchive{};

			const auto setup_data = [](
				D2LvlSubTxt& pLvlSubTxtRecord,
				D2DrlgFileStrc& pDrlgFile
			) {
				pLvlSubTxtRecord.pDrlgFile = &pDrlgFile;
			};

			setup_data(moo_pLvlSubTxtRecord, moo_pDrlgFile);
			setup_data(original_pLvlSubTxtRecord, original_pDrlgFile);

			// Call both implementations
			sut(hArchive, &moo_pLvlSubTxtRecord);
			original(hArchive, &original_pLvlSubTxtRecord);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
			CHECK(moo_pLvlSubTxtRecord.pDrlgFile == &moo_pDrlgFile);
			CHECK(original_pLvlSubTxtRecord.pDrlgFile == &original_pDrlgFile);
		}

		SUBCASE("load from level files list")
		{
			// Input data
			const auto ds1_width = random_unsigned_integer(1, max_ds1_size);
			const auto ds1_height = random_unsigned_integer(1, max_ds1_size);
			const auto wall_layers = random_unsigned_integer(0, DRLG_MAX_WALL_LAYERS);
			const auto floor_layers = random_unsigned_integer(0, DRLG_MAX_FLOOR_LAYERS);
			const auto has_shadow_layer = random_unsigned_integer(0, 1);

			std::array<Ds1Layer, DRLG_MAX_WALL_LAYERS> wall_layer_cells{};
			std::array<Ds1Layer, DRLG_MAX_WALL_LAYERS> tile_type_layer_cells{};
			for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
			{
				wall_layer_cells[i] = random_ds1_layer();
				tile_type_layer_cells[i] = random_ds1_layer();
			}
			const auto floor_layer_cells = random_ds1_layer();
			const auto shadow_layer_cells = random_ds1_layer();

			D2LvlSubTxt moo_pLvlSubTxtRecord{};
			D2LevelFileListStrc moo_pLevelFile{};
			D2DrlgFileStrc moo_pDrlgFile{};
			std::array<Ds1Layer, DRLG_MAX_WALL_LAYERS> moo_pWallLayers{};
			std::array<Ds1Layer, DRLG_MAX_WALL_LAYERS> moo_pTileTypeLayers{};
			Ds1Layer moo_pFloorLayer{};
			Ds1Layer moo_pShadowLayer{};
			D2LvlSubTxt original_pLvlSubTxtRecord{};
			D2LevelFileListStrc original_pLevelFile{};
			D2DrlgFileStrc original_pDrlgFile{};
			std::array<Ds1Layer, DRLG_MAX_WALL_LAYERS> original_pWallLayers{};
			std::array<Ds1Layer, DRLG_MAX_WALL_LAYERS> original_pTileTypeLayers{};
			Ds1Layer original_pFloorLayer{};
			Ds1Layer original_pShadowLayer{};
			HD2ARCHIVE hArchive{};

			const auto setup_data = [ds1_width, ds1_height, wall_layers, floor_layers, has_shadow_layer, &wall_layer_cells, &tile_type_layer_cells, &floor_layer_cells, &shadow_layer_cells](
				D2LvlSubTxt& pLvlSubTxtRecord,
				D2LevelFileListStrc& pLevelFile,
				D2DrlgFileStrc& pDrlgFile,
				std::array<Ds1Layer, DRLG_MAX_WALL_LAYERS>& pWallLayers,
				std::array<Ds1Layer, DRLG_MAX_WALL_LAYERS>& pTileTypeLayers,
				Ds1Layer& pFloorLayer,
				Ds1Layer& pShadowLayer
			) {
				pWallLayers = wall_layer_cells;
				pTileTypeLayers = tile_type_layer_cells;
				pFloorLayer = floor_layer_cells;
				pShadowLayer = shadow_layer_cells;

				pDrlgFile.nWidth = ds1_width;
				pDrlgFile.nHeight = ds1_height;
				pDrlgFile.nWallLayers = wall_layers;
				pDrlgFile.nFloorLayers = floor_layers;
				for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
				{
					pDrlgFile.pWallLayer[i] = pWallLayers[i].data();
					pDrlgFile.pTileTypeLayer[i] = pTileTypeLayers[i].data();
				}
				pDrlgFile.pFloorLayer[0] = pFloorLayer.data();
				pDrlgFile.pShadowLayer = has_shadow_layer ? pShadowLayer.data() : nullptr;
				// Files without substitution groups trigger a warning
				pDrlgFile.nSubstGroups = 1;

				strcpy_s(pLvlSubTxtRecord.szFile, "Tiles\\Act1\\Outdoors\\TestSubstitution.ds1");

				// The file is already loaded, so DRLGPRESET_LoadDrlgFile takes it from the level files list instead of parsing it from an archive
				strcpy_s(pLevelFile.szPath, pLvlSubTxtRecord.szFile);
				pLevelFile.nRefCount = 1;
				pLevelFile.pFile = &pDrlgFile;
			};

			setup_data(moo_pLvlSubTxtRecord, moo_pLevelFile, moo_pDrlgFile, moo_pWallLayers, moo_pTileTypeLayers, moo_pFloorLayer, moo_pShadowLayer);
			setup_data(original_pLvlSubTxtRecord, original_pLevelFile, original_pDrlgFile, original_pWallLayers, original_pTileTypeLayers, original_pFloorLayer, original_pShadowLayer);

			// Each implementation has its own level files list
			moo_pLevelFile.pNext = gpLevelFilesList_6FDEA700;
			gpLevelFilesList_6FDEA700 = &moo_pLevelFile;
			original_pLevelFile.pNext = original_gpLevelFilesList;
			original_gpLevelFilesList = &original_pLevelFile;

			// Call both implementations
			sut(hArchive, &moo_pLvlSubTxtRecord);
			original(hArchive, &original_pLvlSubTxtRecord);

			// Restore the level files lists
			gpLevelFilesList_6FDEA700 = moo_pLevelFile.pNext;
			original_gpLevelFilesList = original_pLevelFile.pNext;

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
			CHECK(moo_pLvlSubTxtRecord.pDrlgFile == &moo_pDrlgFile);
			CHECK(original_pLvlSubTxtRecord.pDrlgFile == &original_pDrlgFile);
			CHECK(moo_pLevelFile.nRefCount == original_pLevelFile.nRefCount);
			for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
			{
				check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pWallGrid[i]), get_grid_values(original_pLvlSubTxtRecord.pWallGrid[i]), "Comparing pLvlSubTxtRecord->pWallGrid");
				check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pTileTypeGrid[i]), get_grid_values(original_pLvlSubTxtRecord.pTileTypeGrid[i]), "Comparing pLvlSubTxtRecord->pTileTypeGrid");
			}
			check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pFloorGrid), get_grid_values(original_pLvlSubTxtRecord.pFloorGrid), "Comparing pLvlSubTxtRecord->pFloorGrid");
			check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pShadowGrid), get_grid_values(original_pLvlSubTxtRecord.pShadowGrid), "Comparing pLvlSubTxtRecord->pShadowGrid");

			// Clean up the row offsets allocated by DRLGGRID_FillNewCellFlags
			for (auto pLvlSubTxtRecord : { &moo_pLvlSubTxtRecord, &original_pLvlSubTxtRecord })
			{
				for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
				{
					free_allocated_grid(pLvlSubTxtRecord->pWallGrid[i]);
					free_allocated_grid(pLvlSubTxtRecord->pTileTypeGrid[i]);
				}
				free_allocated_grid(pLvlSubTxtRecord->pFloorGrid);
				free_allocated_grid(pLvlSubTxtRecord->pShadowGrid);
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B770")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_FreeDrlgFile, dll_base + 0x0004B770);

		auto& original_gpLevelFilesList = *reinterpret_cast<D2LevelFileListStrc**>(dll_base + level_files_list_offset);

		REPEAT_5();

		SUBCASE("not loaded")
		{
			// Input data
			D2LvlSubTxt moo_pLvlSubTxtRecord{};
			D2LvlSubTxt original_pLvlSubTxtRecord{};

			// Call both implementations
			sut(&moo_pLvlSubTxtRecord);
			original(&original_pLvlSubTxtRecord);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
		}

		SUBCASE("still referenced")
		{
			// Input data
			const auto wall_layers = random_unsigned_integer(0, DRLG_MAX_WALL_LAYERS);

			std::array<SubGridCells, DRLG_MAX_WALL_LAYERS> wall_cells{};
			std::array<SubGridCells, DRLG_MAX_WALL_LAYERS> tile_type_cells{};
			for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
			{
				wall_cells[i] = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);
				tile_type_cells[i] = random_grid_cells<sub_grid_width, sub_grid_height>(random_tile_type);
			}
			const auto floor_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);
			const auto shadow_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);

			D2LvlSubTxt moo_pLvlSubTxtRecord{};
			D2LevelFileListStrc moo_pLevelFile{};
			D2DrlgFileStrc moo_pDrlgFile{};
			std::array<SubGridData, DRLG_MAX_WALL_LAYERS> moo_pWallGridData{};
			std::array<SubGridData, DRLG_MAX_WALL_LAYERS> moo_pTileTypeGridData{};
			SubGridData moo_pFloorGridData{};
			SubGridData moo_pShadowGridData{};
			D2LvlSubTxt original_pLvlSubTxtRecord{};
			D2LevelFileListStrc original_pLevelFile{};
			D2DrlgFileStrc original_pDrlgFile{};
			std::array<SubGridData, DRLG_MAX_WALL_LAYERS> original_pWallGridData{};
			std::array<SubGridData, DRLG_MAX_WALL_LAYERS> original_pTileTypeGridData{};
			SubGridData original_pFloorGridData{};
			SubGridData original_pShadowGridData{};

			const auto setup_data = [wall_layers, &wall_cells, &tile_type_cells, &floor_cells, &shadow_cells](
				D2LvlSubTxt& pLvlSubTxtRecord,
				D2LevelFileListStrc& pLevelFile,
				D2DrlgFileStrc& pDrlgFile,
				std::array<SubGridData, DRLG_MAX_WALL_LAYERS>& pWallGridData,
				std::array<SubGridData, DRLG_MAX_WALL_LAYERS>& pTileTypeGridData,
				SubGridData& pFloorGridData,
				SubGridData& pShadowGridData
			) {
				pDrlgFile.nWallLayers = wall_layers;

				// The file is still referenced by another record, so it is not freed
				pLevelFile.nRefCount = 2;
				pLevelFile.pFile = &pDrlgFile;

				for (auto i = 0; i < wall_layers; ++i)
				{
					setup_allocated_grid(pLvlSubTxtRecord.pWallGrid[i], pWallGridData[i], wall_cells[i]);
					setup_allocated_grid(pLvlSubTxtRecord.pTileTypeGrid[i], pTileTypeGridData[i], tile_type_cells[i]);
				}
				setup_allocated_grid(pLvlSubTxtRecord.pFloorGrid, pFloorGridData, floor_cells);
				setup_allocated_grid(pLvlSubTxtRecord.pShadowGrid, pShadowGridData, shadow_cells);
				pLvlSubTxtRecord.pDrlgFile = &pDrlgFile;
			};

			setup_data(moo_pLvlSubTxtRecord, moo_pLevelFile, moo_pDrlgFile, moo_pWallGridData, moo_pTileTypeGridData, moo_pFloorGridData, moo_pShadowGridData);
			setup_data(original_pLvlSubTxtRecord, original_pLevelFile, original_pDrlgFile, original_pWallGridData, original_pTileTypeGridData, original_pFloorGridData, original_pShadowGridData);

			// Each implementation has its own level files list
			moo_pLevelFile.pNext = gpLevelFilesList_6FDEA700;
			gpLevelFilesList_6FDEA700 = &moo_pLevelFile;
			original_pLevelFile.pNext = original_gpLevelFilesList;
			original_gpLevelFilesList = &original_pLevelFile;

			// Call both implementations
			sut(&moo_pLvlSubTxtRecord);
			original(&original_pLvlSubTxtRecord);

			// Restore the level files lists
			gpLevelFilesList_6FDEA700 = moo_pLevelFile.pNext;
			original_gpLevelFilesList = original_pLevelFile.pNext;

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
			CHECK(moo_pLvlSubTxtRecord.pDrlgFile == &moo_pDrlgFile);
			CHECK(original_pLvlSubTxtRecord.pDrlgFile == &original_pDrlgFile);
			CHECK(moo_pLevelFile.nRefCount == original_pLevelFile.nRefCount);
			for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
			{
				check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pWallGrid[i]), get_grid_values(original_pLvlSubTxtRecord.pWallGrid[i]), "Comparing pLvlSubTxtRecord->pWallGrid");
				check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pTileTypeGrid[i]), get_grid_values(original_pLvlSubTxtRecord.pTileTypeGrid[i]), "Comparing pLvlSubTxtRecord->pTileTypeGrid");
			}
			check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pFloorGrid), get_grid_values(original_pLvlSubTxtRecord.pFloorGrid), "Comparing pLvlSubTxtRecord->pFloorGrid");
			check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pShadowGrid), get_grid_values(original_pLvlSubTxtRecord.pShadowGrid), "Comparing pLvlSubTxtRecord->pShadowGrid");
		}

		SUBCASE("last reference")
		{
			// Input data
			const auto wall_layers = random_unsigned_integer(0, DRLG_MAX_WALL_LAYERS);
			const auto subst_groups = random_unsigned_integer(1, 3);

			std::array<SubGridCells, DRLG_MAX_WALL_LAYERS> wall_cells{};
			std::array<SubGridCells, DRLG_MAX_WALL_LAYERS> tile_type_cells{};
			for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
			{
				wall_cells[i] = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);
				tile_type_cells[i] = random_grid_cells<sub_grid_width, sub_grid_height>(random_tile_type);
			}
			const auto floor_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);
			const auto shadow_cells = random_grid_cells<sub_grid_width, sub_grid_height>(random_cell_flags);

			// The level file and the drlg file are freed, so they have to be allocated with the same allocator
			D2LvlSubTxt moo_pLvlSubTxtRecord{};
			D2LevelFileListStrc* moo_pLevelFile = D2_CALLOC_STRC_POOL(nullptr, D2LevelFileListStrc);
			D2DrlgFileStrc* moo_pDrlgFile = D2_CALLOC_STRC_POOL(nullptr, D2DrlgFileStrc);
			std::array<SubGridData, DRLG_MAX_WALL_LAYERS> moo_pWallGridData{};
			std::array<SubGridData, DRLG_MAX_WALL_LAYERS> moo_pTileTypeGridData{};
			SubGridData moo_pFloorGridData{};
			SubGridData moo_pShadowGridData{};
			D2LvlSubTxt original_pLvlSubTxtRecord{};
			D2LevelFileListStrc* original_pLevelFile = D2_CALLOC_STRC_POOL(nullptr, D2LevelFileListStrc);
			D2DrlgFileStrc* original_pDrlgFile = D2_CALLOC_STRC_POOL(nullptr, D2DrlgFileStrc);
			std::array<SubGridData, DRLG_MAX_WALL_LAYERS> original_pWallGridData{};
			std::array<SubGridData, DRLG_MAX_WALL_LAYERS> original_pTileTypeGridData{};
			SubGridData original_pFloorGridData{};
			SubGridData original_pShadowGridData{};

			const auto setup_data = [wall_layers, subst_groups, &wall_cells, &tile_type_cells, &floor_cells, &shadow_cells](
				D2LvlSubTxt& pLvlSubTxtRecord,
				D2LevelFileListStrc& pLevelFile,
				D2DrlgFileStrc& pDrlgFile,
				std::array<SubGridData, DRLG_MAX_WALL_LAYERS>& pWallGridData,
				std::array<SubGridData, DRLG_MAX_WALL_LAYERS>& pTileTypeGridData,
				SubGridData& pFloorGridData,
				SubGridData& pShadowGridData
			) {
				pDrlgFile.nWallLayers = wall_layers;
				pDrlgFile.nSubstGroups = subst_groups;
				pDrlgFile.pSubstGroups = static_cast<D2DrlgSubstGroupStrc*>(D2_CALLOC_POOL(nullptr, sizeof(D2DrlgSubstGroupStrc) * subst_groups));

				pLevelFile.nRefCount = 1;
				pLevelFile.pFile = &pDrlgFile;

				for (auto i = 0; i < wall_layers; ++i)
				{
					setup_allocated_grid(pLvlSubTxtRecord.pWallGrid[i], pWallGridData[i], wall_cells[i]);
					setup_allocated_grid(pLvlSubTxtRecord.pTileTypeGrid[i], pTileTypeGridData[i], tile_type_cells[i]);
				}
				setup_allocated_grid(pLvlSubTxtRecord.pFloorGrid, pFloorGridData, floor_cells);
				setup_allocated_grid(pLvlSubTxtRecord.pShadowGrid, pShadowGridData, shadow_cells);
				pLvlSubTxtRecord.pDrlgFile = &pDrlgFile;
			};

			setup_data(moo_pLvlSubTxtRecord, *moo_pLevelFile, *moo_pDrlgFile, moo_pWallGridData, moo_pTileTypeGridData, moo_pFloorGridData, moo_pShadowGridData);
			setup_data(original_pLvlSubTxtRecord, *original_pLevelFile, *original_pDrlgFile, original_pWallGridData, original_pTileTypeGridData, original_pFloorGridData, original_pShadowGridData);

			// Each implementation has its own level files list
			D2LevelFileListStrc* moo_pPreviousLevelFiles = gpLevelFilesList_6FDEA700;
			moo_pLevelFile->pNext = moo_pPreviousLevelFiles;
			gpLevelFilesList_6FDEA700 = moo_pLevelFile;
			D2LevelFileListStrc* original_pPreviousLevelFiles = original_gpLevelFilesList;
			original_pLevelFile->pNext = original_pPreviousLevelFiles;
			original_gpLevelFilesList = original_pLevelFile;

			// Call both implementations
			sut(&moo_pLvlSubTxtRecord);
			original(&original_pLvlSubTxtRecord);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
			CHECK(moo_pLvlSubTxtRecord.pDrlgFile == nullptr);
			CHECK(original_pLvlSubTxtRecord.pDrlgFile == nullptr);
			// The level files have been freed and removed from the lists
			CHECK(gpLevelFilesList_6FDEA700 == moo_pPreviousLevelFiles);
			CHECK(original_gpLevelFilesList == original_pPreviousLevelFiles);
			for (auto i = 0; i < DRLG_MAX_WALL_LAYERS; ++i)
			{
				check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pWallGrid[i]), get_grid_values(original_pLvlSubTxtRecord.pWallGrid[i]), "Comparing pLvlSubTxtRecord->pWallGrid");
				check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pTileTypeGrid[i]), get_grid_values(original_pLvlSubTxtRecord.pTileTypeGrid[i]), "Comparing pLvlSubTxtRecord->pTileTypeGrid");
			}
			check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pFloorGrid), get_grid_values(original_pLvlSubTxtRecord.pFloorGrid), "Comparing pLvlSubTxtRecord->pFloorGrid");
			check_values_eq(get_grid_values(moo_pLvlSubTxtRecord.pShadowGrid), get_grid_values(original_pLvlSubTxtRecord.pShadowGrid), "Comparing pLvlSubTxtRecord->pShadowGrid");
		}
	}

	TEST_CASE_FIXTURE(LvlSubTxtFixture<NoopFixture>, "D2Common.0x6FD8B7E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_PickSubThemes, dll_base + 0x0004B7E0);

		const auto type_ranges = get_lvlsub_type_ranges(lvlsub_txt.get(), lvlsub_record_count);
		REQUIRE_FALSE(type_ranges.empty());

		REPEAT_5();

		SUBCASE("no sub type or theme")
		{
			for (const auto& [sub_type, sub_theme] : { std::pair{ -1, 0 }, std::pair{ 0, -1 }, std::pair{ -1, -1 } })
			{
				// Input data
				const auto low_seed = random_unsigned_integer();
				const auto high_seed = random_unsigned_integer();

				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				int nSubType = sub_type;
				int nSubTheme = sub_theme;

				const auto setup_data = [low_seed, high_seed](
					D2DrlgRoomStrc& pDrlgRoom
				) {
					pDrlgRoom.pSeed.nLowSeed = low_seed;
					pDrlgRoom.pSeed.nHighSeed = high_seed;
				};

				setup_data(moo_pDrlgRoom);
				setup_data(original_pDrlgRoom);

				// Call both implementations
				const auto moo_result = sut(&moo_pDrlgRoom, nSubType, nSubTheme);
				const auto original_result = original(&original_pDrlgRoom, nSubType, nSubTheme);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			}
		}

		SUBCASE("sub type and theme")
		{
			for (const auto& type_range : type_ranges)
			{
				for (auto sub_theme = 0; sub_theme < 5; ++sub_theme)
				{
					// Input data
					const auto low_seed = random_unsigned_integer();
					const auto high_seed = random_unsigned_integer();
					const auto dt1_mask = random_unsigned_integer();

					D2DrlgRoomStrc moo_pDrlgRoom{};
					D2DrlgRoomStrc original_pDrlgRoom{};
					int nSubType = type_range.nType;
					int nSubTheme = sub_theme;

					const auto setup_data = [low_seed, high_seed, dt1_mask](
						D2DrlgRoomStrc& pDrlgRoom
					) {
						pDrlgRoom.pSeed.nLowSeed = low_seed;
						pDrlgRoom.pSeed.nHighSeed = high_seed;
						pDrlgRoom.dwDT1Mask = dt1_mask;
					};

					setup_data(moo_pDrlgRoom);
					setup_data(original_pDrlgRoom);

					// Call both implementations
					const auto moo_result = sut(&moo_pDrlgRoom, nSubType, nSubTheme);
					const auto original_result = original(&original_pDrlgRoom, nSubType, nSubTheme);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
				}
			}
		}
	}
}
