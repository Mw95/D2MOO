#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2CMP.h>
#include <D2DataTbls.h>
#include <DataTbls/LevelsIds.h>
#include <DataTbls/MonsterIds.h>
#include <DataTbls/ObjectsIds.h>
#include <Drlg/D2DrlgDrlgGrid.h>
#include <Drlg/D2DrlgDrlgLogic.h>
#include <Drlg/D2DrlgPreset.h>
#include <Drlg/D2DrlgRoomTile.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>


DYNAMIC_ARRAY_TYPE(int)
DYNAMIC_ARRAY_TYPE(D2MapAIPathPositionStrc)
DYNAMIC_ARRAY_TYPE(D2DrlgTileDataStrc)


namespace
{
	uint32_t pack_tile_information(uint32_t nTileStyle, uint32_t nTileSequence)
	{
		D2C_PackedTileInformation nTileInformation{ 0 };
		nTileInformation.nTileStyle = nTileStyle;
		nTileInformation.nTileSequence = nTileSequence;
		return nTileInformation.nPackedValue;
	}

	void free_preset_units(D2PresetUnitStrc* pPresetUnit)
	{
		while (pPresetUnit)
		{
			D2PresetUnitStrc* pNext = pPresetUnit->pNext;
			DRLGPRESET_FreePresetUnit(nullptr, pPresetUnit);
			pPresetUnit = pNext;
		}
	}

	// Frees the preset rooms allocated by DRLGROOM_AllocRoomEx
	void free_preset_rooms(D2DrlgLevelStrc& pLevel)
	{
		D2DrlgRoomStrc* pDrlgRoom = pLevel.pFirstRoomEx;
		while (pDrlgRoom)
		{
			D2DrlgRoomStrc* pNext = pDrlgRoom->pDrlgRoomNext;
			D2_FREE_POOL(nullptr, pDrlgRoom->pMaze);
			D2_FREE_POOL(nullptr, pDrlgRoom);
			pDrlgRoom = pNext;
		}

		pLevel.pFirstRoomEx = nullptr;
		pLevel.nRooms = 0;
	}

	void free_pops(D2DrlgMapStrc& pDrlgMap)
	{
		D2_FREE_POOL(nullptr, pDrlgMap.pPopsIndex);
		D2_FREE_POOL(nullptr, pDrlgMap.pPopsSubIndex);
		D2_FREE_POOL(nullptr, pDrlgMap.pPopsOrientation);
		D2_FREE_POOL(nullptr, pDrlgMap.pPopsLocation);
	}
}


TEST_SUITE("D2DrlgPresetTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	// D2Common.0x6FDEA700
	const auto original_gpLevelFilesList = reinterpret_cast<D2LevelFileListStrc**>(dll_base + 0x000AA700);


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD859A0 (#11222)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_CountPresetObjectsByAct, dll_base + 0x000459A0);

		SUBCASE("")
		{
			for (auto i = 0; i < 5; ++i)
			{
				uint8_t nAct = i;

				// Call both implementations
				const auto moo_result = sut(nAct);
				const auto original_result = original(nAct);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD859E0 (#11223)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetObjectIndexFromObjPreset, dll_base + 0x000459E0);

		SUBCASE("")
		{
			for (auto i = 0; i < 5; ++i)
			{
				for (auto j = 0; j < 150; ++j)
				{
					uint8_t nAct = i;
					int nUnitId = j;

					// Call both implementations
					const auto moo_result = sut(nAct, nUnitId);
					const auto original_result = original(nAct, nUnitId);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD85A10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_ParseDS1File, dll_base + 0x00045A10);

		SUBCASE("")
		{
			// Build a version 18 DS1 file with a substitution group, preset units and a map AI path
			const auto nWidth = 4;
			const auto nHeight = 3;
			const auto nArea = (nWidth + 1) * (nHeight + 1);

			std::vector<uint8_t> ds1_file;
			const auto write_int32 = [&ds1_file](int32_t nValue) {
				const auto pBytes = reinterpret_cast<const uint8_t*>(&nValue);
				ds1_file.insert(ds1_file.end(), pBytes, pBytes + sizeof(nValue));
			};
			const auto write_layer = [&write_int32, nArea]() {
				for (auto i = 0; i < nArea; ++i)
				{
					write_int32(random_unsigned_integer());
				}
			};

			write_int32(18);							// nVersion
			write_int32(nWidth);						// nWidth
			write_int32(nHeight);						// nHeight
			write_int32(ACT_II);						// nAct
			write_int32(DRLGSUBST_RANDOM);				// nSubstMethod
			write_int32(1);								// nStrings
			const char szString[] = "DATA\\GLOBAL\\TILES\\ACT2\\TOWN\\Ground.dt1";
			ds1_file.insert(ds1_file.end(), szString, szString + sizeof(szString));
			write_int32(1);								// nWallLayers
			write_int32(1);								// nFloorLayers
			write_layer();								// Wall layer 0
			write_layer();								// Tile type layer 0
			write_layer();								// Floor layer 0
			write_layer();								// Shadow layer
			write_layer();								// Substitution group tags
			write_int32(3);								// nUnits
			write_int32(UNIT_OBJECT);					// Object from the act preset table
			write_int32(5);
			write_int32(10);
			write_int32(12);
			write_int32(1);
			write_int32(UNIT_OBJECT);					// Object with direct index
			write_int32(160);
			write_int32(3);
			write_int32(4);
			write_int32(0);
			write_int32(UNIT_TILE);						// Tile
			write_int32(2);
			write_int32(7);
			write_int32(8);
			write_int32(0);
			write_int32(0);								// Skipped
			write_int32(2);								// nSubstGroups
			for (auto i = 0; i < 2; ++i)
			{
				write_int32(i);							// nPosX
				write_int32(i + 1);						// nPosY
				write_int32(2);							// nWidth
				write_int32(1);							// nHeight
				write_int32(i * 7);						// field_14
			}
			write_int32(2);								// Number of map AI paths
			write_int32(2);								// Path of the unit at (10, 12)
			write_int32(10);
			write_int32(12);
			for (auto i = 0; i < 2; ++i)
			{
				write_int32(10 + i);					// nX
				write_int32(12 + 2 * i);				// nY
				write_int32(i + 1);						// nMapAIAction
			}
			write_int32(1);								// Path without unit, gets skipped
			write_int32(99);
			write_int32(99);
			write_int32(1);
			write_int32(2);
			write_int32(3);

			const char* szFileName = "D2DrlgPresetTests.ds1";
			const auto file_path = working_directory / szFileName;
			{
				std::ofstream file(file_path, std::ios::binary);
				file.write(reinterpret_cast<const char*>(ds1_file.data()), ds1_file.size());
			}

			// The file is read through Fog/Storm, which has to be able to access loose files
			HSFILE hFile = nullptr;
			const auto can_open_file = FOG_FOpenFile(szFileName, &hFile);
			if (can_open_file)
			{
				FOG_FCloseFile(hFile);
			}
			else
			{
				std::filesystem::remove(file_path);
				WARN_MESSAGE(can_open_file, "Could not open the DS1 file through Fog/Storm, skipping test");
				return;
			}

			// Input data
			D2DrlgFileStrc moo_pDrlgFile{};
			D2DrlgFileStrc original_pDrlgFile{};
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(&moo_pDrlgFile, hArchive, szFileName);
			original(&original_pDrlgFile, hArchive, szFileName);

			std::filesystem::remove(file_path);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgFile, original_pDrlgFile, "Comparing pDrlgFile");

			// Clean up
			const auto free_drlg_file_data = [](
				D2DrlgFileStrc& pDrlgFile
			) {
				D2_FREE(pDrlgFile.pDS1File);
				D2_FREE_POOL(nullptr, pDrlgFile.pSubstGroups);
				free_preset_units(pDrlgFile.pPresetUnit);
			};

			free_drlg_file_data(moo_pDrlgFile);
			free_drlg_file_data(original_pDrlgFile);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86050")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_LoadDrlgFile, dll_base + 0x00046050);

		SUBCASE("File already loaded")
		{
			// Input data
			const char* szFile = "DATA\\GLOBAL\\TILES\\ACT1\\TOWN\\townN1.ds1";

			D2DrlgFileStrc* moo_ppDrlgFile{};
			D2LevelFileListStrc moo_pOtherLevelFile{};
			D2LevelFileListStrc moo_pLevelFile{};
			D2DrlgFileStrc moo_pDrlgFile{};
			D2DrlgFileStrc* original_ppDrlgFile{};
			D2LevelFileListStrc original_pOtherLevelFile{};
			D2LevelFileListStrc original_pLevelFile{};
			D2DrlgFileStrc original_pDrlgFile{};
			HD2ARCHIVE hArchive{};

			const auto setup_data = [szFile](
				D2LevelFileListStrc& pOtherLevelFile,
				D2LevelFileListStrc& pLevelFile,
				D2DrlgFileStrc& pDrlgFile
			) {
				strcpy_s(pOtherLevelFile.szPath, "DATA\\GLOBAL\\TILES\\ACT1\\TOWN\\townE1.ds1");
				pOtherLevelFile.nRefCount = 1;
				pOtherLevelFile.pNext = &pLevelFile;

				pDrlgFile.nWidth = 8;
				pDrlgFile.nHeight = 8;

				strcpy_s(pLevelFile.szPath, szFile);
				pLevelFile.nRefCount = 1;
				pLevelFile.pFile = &pDrlgFile;
			};

			setup_data(moo_pOtherLevelFile, moo_pLevelFile, moo_pDrlgFile);
			setup_data(original_pOtherLevelFile, original_pLevelFile, original_pDrlgFile);

			gpLevelFilesList_6FDEA700 = &moo_pOtherLevelFile;
			*original_gpLevelFilesList = &original_pOtherLevelFile;

			// Call both implementations
			sut(&moo_ppDrlgFile, hArchive, szFile);
			original(&original_ppDrlgFile, hArchive, szFile);

			gpLevelFilesList_6FDEA700 = nullptr;
			*original_gpLevelFilesList = nullptr;

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_ppDrlgFile, original_ppDrlgFile, "Comparing ppDrlgFile");
			MOO_CHECK_EQ(moo_pOtherLevelFile, original_pOtherLevelFile, "Comparing pOtherLevelFile");
			MOO_CHECK_EQ(moo_pLevelFile, original_pLevelFile, "Comparing pLevelFile");

			// Check specific values
			CHECK_EQ(moo_ppDrlgFile, &moo_pDrlgFile);
			CHECK_EQ(original_ppDrlgFile, &original_pDrlgFile);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86190")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreeDrlgFile, dll_base + 0x00046190);

		const char* szFile = "DATA\\GLOBAL\\TILES\\ACT1\\TOWN\\townN1.ds1";

		SUBCASE("File is still referenced")
		{
			// Input data
			D2DrlgFileStrc* moo_ppDrlgFile{};
			D2LevelFileListStrc moo_pLevelFile{};
			D2DrlgFileStrc moo_pDrlgFile{};
			D2DrlgFileStrc* original_ppDrlgFile{};
			D2LevelFileListStrc original_pLevelFile{};
			D2DrlgFileStrc original_pDrlgFile{};

			const auto setup_data = [szFile](
				D2DrlgFileStrc*& ppDrlgFile,
				D2LevelFileListStrc& pLevelFile,
				D2DrlgFileStrc& pDrlgFile
			) {
				strcpy_s(pLevelFile.szPath, szFile);
				pLevelFile.nRefCount = 2;
				pLevelFile.pFile = &pDrlgFile;

				ppDrlgFile = &pDrlgFile;
			};

			setup_data(moo_ppDrlgFile, moo_pLevelFile, moo_pDrlgFile);
			setup_data(original_ppDrlgFile, original_pLevelFile, original_pDrlgFile);

			gpLevelFilesList_6FDEA700 = &moo_pLevelFile;
			*original_gpLevelFilesList = &original_pLevelFile;

			// Call both implementations
			sut(&moo_ppDrlgFile);
			original(&original_ppDrlgFile);

			gpLevelFilesList_6FDEA700 = nullptr;
			*original_gpLevelFilesList = nullptr;

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_ppDrlgFile, original_ppDrlgFile, "Comparing ppDrlgFile");
			MOO_CHECK_EQ(moo_pLevelFile, original_pLevelFile, "Comparing pLevelFile");
		}

		SUBCASE("Last reference")
		{
			// Input data
			D2DrlgFileStrc* moo_ppDrlgFile{};
			D2LevelFileListStrc moo_pOtherLevelFile{};
			D2DrlgFileStrc* original_ppDrlgFile{};
			D2LevelFileListStrc original_pOtherLevelFile{};

			// The freed file is the second entry of the list
			const auto setup_data = [szFile](
				D2DrlgFileStrc*& ppDrlgFile,
				D2LevelFileListStrc& pOtherLevelFile
			) {
				ppDrlgFile = D2_CALLOC_STRC_POOL(nullptr, D2DrlgFileStrc);
				ppDrlgFile->pPresetUnit = D2_CALLOC_STRC_POOL(nullptr, D2PresetUnitStrc);
				ppDrlgFile->pPresetUnit->nUnitType = UNIT_OBJECT;

				D2LevelFileListStrc* pLevelFile = D2_CALLOC_STRC_POOL(nullptr, D2LevelFileListStrc);
				strcpy_s(pLevelFile->szPath, szFile);
				pLevelFile->nRefCount = 1;
				pLevelFile->pFile = ppDrlgFile;

				strcpy_s(pOtherLevelFile.szPath, "DATA\\GLOBAL\\TILES\\ACT1\\TOWN\\townE1.ds1");
				pOtherLevelFile.nRefCount = 1;
				pOtherLevelFile.pNext = pLevelFile;
			};

			setup_data(moo_ppDrlgFile, moo_pOtherLevelFile);
			setup_data(original_ppDrlgFile, original_pOtherLevelFile);

			gpLevelFilesList_6FDEA700 = &moo_pOtherLevelFile;
			*original_gpLevelFilesList = &original_pOtherLevelFile;

			// Call both implementations
			sut(&moo_ppDrlgFile);
			original(&original_ppDrlgFile);

			gpLevelFilesList_6FDEA700 = nullptr;
			*original_gpLevelFilesList = nullptr;

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_ppDrlgFile, original_ppDrlgFile, "Comparing ppDrlgFile");
			MOO_CHECK_EQ(moo_pOtherLevelFile, original_pOtherLevelFile, "Comparing pOtherLevelFile");

			// Check specific values
			CHECK_EQ(moo_ppDrlgFile, nullptr);
			CHECK_EQ(moo_pOtherLevelFile.pNext, nullptr);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86310")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_CopyPresetUnit, dll_base + 0x00046310);

		const auto unit_type = random_unsigned_integer(0, 5);
		const auto index = random_unsigned_integer(0, 500);
		const auto mode = random_unsigned_integer(0, 10);
		const auto x = random_unsigned_integer(0, 1000);
		const auto y = random_unsigned_integer(0, 1000);
		const auto spawned = random_unsigned_integer(0, 1);

		SUBCASE("Without map AI")
		{
			// Input data
			D2PresetUnitStrc moo_pPresetUnit{};
			D2PresetUnitStrc original_pPresetUnit{};
			int nX = random_unsigned_integer(0, 1000);
			int nY = random_unsigned_integer(0, 1000);

			const auto setup_data = [unit_type, index, mode, x, y, spawned](
				D2PresetUnitStrc& pPresetUnit
			) {
				pPresetUnit.nUnitType = unit_type;
				pPresetUnit.nIndex = index;
				pPresetUnit.nMode = mode;
				pPresetUnit.nXpos = x;
				pPresetUnit.nYpos = y;
				pPresetUnit.bSpawned = spawned;
			};

			setup_data(moo_pPresetUnit);
			setup_data(original_pPresetUnit);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pPresetUnit, nX, nY);
			const auto original_result = original(nullptr, &original_pPresetUnit, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPresetUnit, original_pPresetUnit, "Comparing pPresetUnit");

			// Clean up
			DRLGPRESET_FreePresetUnit(nullptr, moo_result);
			DRLGPRESET_FreePresetUnit(nullptr, original_result);
		}

		SUBCASE("With map AI")
		{
			// Input data
			D2MapAIPathPositionStrc positions[3]{};
			for (auto& position : positions)
			{
				position.nMapAIAction = random_unsigned_integer(0, 10);
				position.nX = random_unsigned_integer(0, 1000);
				position.nY = random_unsigned_integer(0, 1000);
			}

			D2PresetUnitStrc moo_pPresetUnit{};
			D2MapAIStrc moo_pMapAI{};
			D2MapAIPathPositionStrc moo_pPositions[3]{};
			D2PresetUnitStrc original_pPresetUnit{};
			D2MapAIStrc original_pMapAI{};
			D2MapAIPathPositionStrc original_pPositions[3]{};
			int nX = random_unsigned_integer(0, 1000);
			int nY = random_unsigned_integer(0, 1000);

			const auto setup_data = [unit_type, index, mode, x, y, spawned, &positions](
				D2PresetUnitStrc& pPresetUnit,
				D2MapAIStrc& pMapAI,
				D2MapAIPathPositionStrc(&pPositions)[3]
			) {
				std::memcpy(pPositions, positions, sizeof(positions));
				pMapAI.nPathNodes = 3;
				pMapAI.pPosition = pPositions;

				pPresetUnit.nUnitType = unit_type;
				pPresetUnit.nIndex = index;
				pPresetUnit.nMode = mode;
				pPresetUnit.nXpos = x;
				pPresetUnit.nYpos = y;
				pPresetUnit.bSpawned = spawned;
				pPresetUnit.pMapAI = &pMapAI;
			};

			setup_data(moo_pPresetUnit, moo_pMapAI, moo_pPositions);
			setup_data(original_pPresetUnit, original_pMapAI, original_pPositions);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pPresetUnit, nX, nY);
			const auto original_result = original(nullptr, &original_pPresetUnit, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			MOO_CHECK_EQ(moo_result->pMapAI, original_result->pMapAI, "Comparing result map AI");
			auto moo_result_positions = DynamicArray<D2MapAIPathPositionStrc>{ moo_result->pMapAI->pPosition, moo_result->pMapAI->nPathNodes };
			auto original_result_positions = DynamicArray<D2MapAIPathPositionStrc>{ original_result->pMapAI->pPosition, original_result->pMapAI->nPathNodes };
			MOO_CHECK_EQ(moo_result_positions, original_result_positions, "Comparing result map AI positions");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPresetUnit, original_pPresetUnit, "Comparing pPresetUnit");
			MOO_CHECK_EQ(moo_pMapAI, original_pMapAI, "Comparing pMapAI");
			auto moo_positions = DynamicArray<D2MapAIPathPositionStrc>{ moo_pPositions, 3 };
			auto original_positions = DynamicArray<D2MapAIPathPositionStrc>{ original_pPositions, 3 };
			MOO_CHECK_EQ(moo_positions, original_positions, "Comparing pPositions");

			// Clean up
			DRLGPRESET_FreePresetUnit(nullptr, moo_result);
			DRLGPRESET_FreePresetUnit(nullptr, original_result);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86430")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreePresetUnit, dll_base + 0x00046430);

		SUBCASE("Without map AI")
		{
			// Input data
			D2PresetUnitStrc* moo_pPresetUnit{};
			D2PresetUnitStrc* original_pPresetUnit{};

			const auto setup_data = [](
				D2PresetUnitStrc*& pPresetUnit
			) {
				pPresetUnit = D2_CALLOC_STRC_POOL(nullptr, D2PresetUnitStrc);
				pPresetUnit->nUnitType = UNIT_OBJECT;
				pPresetUnit->nIndex = 1;
			};

			setup_data(moo_pPresetUnit);
			setup_data(original_pPresetUnit);

			// Call both implementations
			sut(nullptr, moo_pPresetUnit);
			original(nullptr, original_pPresetUnit);

			// Input data can not be compared since it was freed
		}

		SUBCASE("With map AI")
		{
			// Input data
			D2PresetUnitStrc* moo_pPresetUnit{};
			D2PresetUnitStrc* original_pPresetUnit{};

			const auto setup_data = [](
				D2PresetUnitStrc*& pPresetUnit
			) {
				pPresetUnit = D2_CALLOC_STRC_POOL(nullptr, D2PresetUnitStrc);
				pPresetUnit->nUnitType = UNIT_MONSTER;
				pPresetUnit->nIndex = 1;
				pPresetUnit->pMapAI = D2_CALLOC_STRC_POOL(nullptr, D2MapAIStrc);
				pPresetUnit->pMapAI->nPathNodes = 2;
				pPresetUnit->pMapAI->pPosition = (D2MapAIPathPositionStrc*)D2_CALLOC_POOL(nullptr, sizeof(D2MapAIPathPositionStrc) * 2);
			};

			setup_data(moo_pPresetUnit);
			setup_data(original_pPresetUnit);

			// Call both implementations
			sut(nullptr, moo_pPresetUnit);
			original(nullptr, original_pPresetUnit);

			// Input data can not be compared since it was freed
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86480 (#10020)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_CreateCopyOfMapAI, dll_base + 0x00046480);

		SUBCASE("")
		{
			// Input data
			D2MapAIPathPositionStrc positions[4]{};
			for (auto& position : positions)
			{
				position.nMapAIAction = random_unsigned_integer(0, 10);
				position.nX = random_unsigned_integer(0, 1000);
				position.nY = random_unsigned_integer(0, 1000);
			}

			D2MapAIStrc moo_pMapAI{};
			D2MapAIPathPositionStrc moo_pPositions[4]{};
			D2MapAIStrc original_pMapAI{};
			D2MapAIPathPositionStrc original_pPositions[4]{};

			const auto setup_data = [&positions](
				D2MapAIStrc& pMapAI,
				D2MapAIPathPositionStrc(&pPositions)[4]
			) {
				std::memcpy(pPositions, positions, sizeof(positions));
				pMapAI.nPathNodes = 4;
				pMapAI.pPosition = pPositions;
			};

			setup_data(moo_pMapAI, moo_pPositions);
			setup_data(original_pMapAI, original_pPositions);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pMapAI);
			const auto original_result = original(nullptr, &original_pMapAI);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			auto moo_result_positions = DynamicArray<D2MapAIPathPositionStrc>{ moo_result->pPosition, moo_result->nPathNodes };
			auto original_result_positions = DynamicArray<D2MapAIPathPositionStrc>{ original_result->pPosition, original_result->nPathNodes };
			MOO_CHECK_EQ(moo_result_positions, original_result_positions, "Comparing result positions");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMapAI, original_pMapAI, "Comparing pMapAI");

			// Clean up
			DRLGPRESET_FreeMapAI(nullptr, moo_result);
			DRLGPRESET_FreeMapAI(nullptr, original_result);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD864F0 (#10021)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_ChangeMapAI, dll_base + 0x000464F0);

		SUBCASE("")
		{
			// Input data
			D2MapAIStrc* moo_ppMapAI1{};
			D2MapAIStrc* moo_ppMapAI2{};
			D2MapAIStrc moo_pMapAI{};
			D2MapAIPathPositionStrc moo_pPosition{};
			D2MapAIStrc* original_ppMapAI1{};
			D2MapAIStrc* original_ppMapAI2{};
			D2MapAIStrc original_pMapAI{};
			D2MapAIPathPositionStrc original_pPosition{};

			const auto setup_data = [](
				D2MapAIStrc*& ppMapAI1,
				D2MapAIStrc*& ppMapAI2,
				D2MapAIStrc& pMapAI,
				D2MapAIPathPositionStrc& pPosition
			) {
				pPosition.nMapAIAction = 1;
				pPosition.nX = 10;
				pPosition.nY = 20;

				pMapAI.nPathNodes = 1;
				pMapAI.pPosition = &pPosition;

				ppMapAI1 = &pMapAI;
				ppMapAI2 = nullptr;
			};

			setup_data(moo_ppMapAI1, moo_ppMapAI2, moo_pMapAI, moo_pPosition);
			setup_data(original_ppMapAI1, original_ppMapAI2, original_pMapAI, original_pPosition);

			// Call both implementations
			const auto moo_result = sut(&moo_ppMapAI1, &moo_ppMapAI2);
			const auto original_result = original(&original_ppMapAI1, &original_ppMapAI2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_ppMapAI1, original_ppMapAI1, "Comparing ppMapAI1");
			MOO_CHECK_EQ(moo_ppMapAI2, original_ppMapAI2, "Comparing ppMapAI2");

			// Check specific values
			CHECK_EQ(moo_ppMapAI1, nullptr);
			CHECK_EQ(moo_ppMapAI2, &moo_pMapAI);
			CHECK_EQ(original_ppMapAI2, &original_pMapAI);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86500 (#10022)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreeMapAI, dll_base + 0x00046500);

		SUBCASE("")
		{
			// Input data
			D2MapAIStrc* moo_pMapAI{};
			D2MapAIStrc* original_pMapAI{};

			const auto setup_data = [](
				D2MapAIStrc*& pMapAI
			) {
				pMapAI = D2_CALLOC_STRC_POOL(nullptr, D2MapAIStrc);
				pMapAI->nPathNodes = 2;
				pMapAI->pPosition = (D2MapAIPathPositionStrc*)D2_CALLOC_POOL(nullptr, sizeof(D2MapAIPathPositionStrc) * 2);
			};

			setup_data(moo_pMapAI);
			setup_data(original_pMapAI);

			// Call both implementations
			sut(nullptr, moo_pMapAI);
			original(nullptr, original_pMapAI);

			// Input data can not be compared since it was freed
		}
	}

	TEST_CASE_FIXTURE(MonStatsTxtFixture<SuperUniquesTxtFixture<NoopFixture>>, "D2Common.0x6FD86540")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_AddPresetUnitToDrlgMap, dll_base + 0x00046540);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto seed = random_unsigned_integer();
			const auto x = random_unsigned_integer(0, 200);
			const auto y = random_unsigned_integer(0, 200);
			const auto monstats_count = monstats_record_count;
			const auto superuniques_count = superuniques_record_count;

			D2DrlgMapStrc moo_pDrlgMap{};
			D2SeedStrc moo_pSeed{};
			D2DrlgFileStrc moo_pDrlgFile{};
			D2PresetUnitStrc moo_pPresetUnits[12]{};
			D2MapAIStrc moo_pMapAI{};
			D2MapAIPathPositionStrc moo_pPositions[2]{};
			D2DrlgMapStrc original_pDrlgMap{};
			D2SeedStrc original_pSeed{};
			D2DrlgFileStrc original_pDrlgFile{};
			D2PresetUnitStrc original_pPresetUnits[12]{};
			D2MapAIStrc original_pMapAI{};
			D2MapAIPathPositionStrc original_pPositions[2]{};

			const auto setup_data = [seed, x, y, monstats_count, superuniques_count](
				D2DrlgMapStrc& pDrlgMap,
				D2SeedStrc& pSeed,
				D2DrlgFileStrc& pDrlgFile,
				D2PresetUnitStrc(&pPresetUnits)[12],
				D2MapAIStrc& pMapAI,
				D2MapAIPathPositionStrc(&pPositions)[2]
			) {
				pSeed.nLowSeed = seed;
				pSeed.nHighSeed = 666;

				// Units which can be skipped based on the seed and units which are always added
				const int units[12][2] =
				{
					{ UNIT_MONSTER, 0 },
					{ UNIT_MONSTER, MONSTER_ACT2VENDOR1 },
					{ UNIT_MONSTER, MONSTER_LIGHTNINGSPIRE },
					{ UNIT_MONSTER, monstats_count },
					{ UNIT_MONSTER, monstats_count + superuniques_count + SUPERUNIQUE_THE_TORMENTOR },
					{ UNIT_MONSTER, monstats_count + superuniques_count + SUPERUNIQUE_TAINTBREEDER },
					{ UNIT_MONSTER, monstats_count + superuniques_count + SUPERUNIQUE_RIFTWRAITH_THE_CANNIBAL },
					{ UNIT_OBJECT, OBJECT_FLOORTRAP },
					{ UNIT_OBJECT, OBJECT_TOMBFLOORTRAP },
					{ UNIT_OBJECT, 581 },
					{ UNIT_OBJECT, 1 },
					{ UNIT_TILE, 2 },
				};

				for (auto i = 0; i < 12; ++i)
				{
					pPresetUnits[i].nUnitType = units[i][0];
					pPresetUnits[i].nIndex = units[i][1];
					pPresetUnits[i].nXpos = 3 * i;
					pPresetUnits[i].nYpos = 2 * i + 1;
					pPresetUnits[i].pNext = i + 1 < 12 ? &pPresetUnits[i + 1] : nullptr;
				}

				for (auto i = 0; i < 2; ++i)
				{
					pPositions[i].nMapAIAction = 1;
					pPositions[i].nX = 5 + i;
					pPositions[i].nY = 7 + i;
				}

				pMapAI.nPathNodes = 2;
				pMapAI.pPosition = pPositions;
				pPresetUnits[10].pMapAI = &pMapAI;

				pDrlgFile.pPresetUnit = &pPresetUnits[0];

				pDrlgMap.pDrlgCoord.nPosX = x;
				pDrlgMap.pDrlgCoord.nPosY = y;
				pDrlgMap.pFile = &pDrlgFile;
			};

			setup_data(moo_pDrlgMap, moo_pSeed, moo_pDrlgFile, moo_pPresetUnits, moo_pMapAI, moo_pPositions);
			setup_data(original_pDrlgMap, original_pSeed, original_pDrlgFile, original_pPresetUnits, original_pMapAI, original_pPositions);

			// Call both implementations
			sut(nullptr, &moo_pDrlgMap, &moo_pSeed);
			original(nullptr, &original_pDrlgMap, &original_pSeed);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
			MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");

			// Clean up
			free_preset_units(moo_pDrlgMap.pPresetUnit);
			free_preset_units(original_pDrlgMap.pPresetUnit);
		}
	}

	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FD867A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_SpawnHardcodedPresetUnits, dll_base + 0x000467A0);

		const auto nWidth = 8;
		const auto nHeight = 8;
		const auto nFloorLayerSize = (nWidth + 1) * (nHeight + 1);

		BOOL bInited = TRUE;
		int nLevelPrest = 0;
		int nLevelId = 0;
		int nPickedFile = 0;
		uint32_t dwRoomFlags = 0;

		SUBCASE("Map not initialized")
		{
			bInited = FALSE;
			nLevelPrest = LVLPREST_ACT1_WILD_BORDER_1;
			nLevelId = LEVEL_BLOODMOOR;
			nPickedFile = 3;
		}

		SUBCASE("Navi in Bloodmoor")
		{
			nLevelPrest = LVLPREST_ACT1_WILD_BORDER_1;
			nLevelId = LEVEL_BLOODMOOR;
			nPickedFile = 3;
		}

		SUBCASE("River without automap reveal")
		{
			nLevelPrest = LVLPREST_ACT1_RIVER_UPPER;
			nLevelId = LEVEL_COLDPLAINS;
		}

		SUBCASE("Upper river")
		{
			nLevelPrest = LVLPREST_ACT1_RIVER_UPPER;
			nLevelId = LEVEL_COLDPLAINS;
			dwRoomFlags = DRLGROOMFLAG_AUTOMAP_REVEAL;
		}

		SUBCASE("Lower river")
		{
			nLevelPrest = LVLPREST_ACT1_RIVER_LOWER;
			nLevelId = LEVEL_COLDPLAINS;
			dwRoomFlags = DRLGROOMFLAG_AUTOMAP_REVEAL;
		}

		// Input data
		const auto x = random_unsigned_integer(0, 200);
		const auto y = random_unsigned_integer(0, 200);

		D2DrlgRoomStrc moo_pDrlgRoom{};
		D2DrlgPresetRoomStrc moo_pMaze{};
		D2DrlgMapStrc moo_pDrlgMap{};
		D2DrlgFileStrc moo_pDrlgFile{};
		int moo_pFloorLayer[nFloorLayerSize]{};
		D2LvlPrestTxt moo_pLvlPrestTxtRecord{};
		D2DrlgLevelStrc moo_pLevel{};
		D2DrlgStrc moo_pDrlg{};
		D2DrlgRoomStrc original_pDrlgRoom{};
		D2DrlgPresetRoomStrc original_pMaze{};
		D2DrlgMapStrc original_pDrlgMap{};
		D2DrlgFileStrc original_pDrlgFile{};
		int original_pFloorLayer[nFloorLayerSize]{};
		D2LvlPrestTxt original_pLvlPrestTxtRecord{};
		D2DrlgLevelStrc original_pLevel{};
		D2DrlgStrc original_pDrlg{};

		const auto setup_data = [=](
			D2DrlgRoomStrc& pDrlgRoom,
			D2DrlgPresetRoomStrc& pMaze,
			D2DrlgMapStrc& pDrlgMap,
			D2DrlgFileStrc& pDrlgFile,
			int(&pFloorLayer)[nFloorLayerSize],
			D2LvlPrestTxt& pLvlPrestTxtRecord,
			D2DrlgLevelStrc& pLevel,
			D2DrlgStrc& pDrlg
		) {
			// River start in the first row and a river curve below it
			pFloorLayer[2] = pack_tile_information(2, 24);
			pFloorLayer[(nWidth + 1) + 2] = pack_tile_information(4, 0);
			pFloorLayer[(nWidth + 1) * 5] = pack_tile_information(4, 8);

			pDrlgFile.nWidth = nWidth;
			pDrlgFile.nHeight = nHeight;
			pDrlgFile.nFloorLayers = 1;
			pDrlgFile.pFloorLayer[0] = pFloorLayer;

			pLvlPrestTxtRecord.dwDef = nLevelPrest;

			pDrlgMap.nLevelPrest = nLevelPrest;
			pDrlgMap.nPickedFile = nPickedFile;
			pDrlgMap.pLvlPrestTxtRecord = &pLvlPrestTxtRecord;
			pDrlgMap.pFile = &pDrlgFile;
			pDrlgMap.pDrlgCoord.nPosX = x;
			pDrlgMap.pDrlgCoord.nPosY = y;
			pDrlgMap.pDrlgCoord.nWidth = nWidth;
			pDrlgMap.pDrlgCoord.nHeight = nHeight;
			pDrlgMap.bInited = bInited;

			pMaze.nLevelPrest = nLevelPrest;
			pMaze.pMap = &pDrlgMap;

			pLevel.pDrlg = &pDrlg;
			pLevel.nLevelId = nLevelId;

			pDrlgRoom.pLevel = &pLevel;
			pDrlgRoom.nType = DRLGTYPE_PRESET;
			pDrlgRoom.pMaze = &pMaze;
			pDrlgRoom.dwFlags = dwRoomFlags;
			pDrlgRoom.nTileXPos = x;
			pDrlgRoom.nTileYPos = y;
			pDrlgRoom.nTileWidth = nWidth;
			pDrlgRoom.nTileHeight = nHeight;
		};

		setup_data(moo_pDrlgRoom, moo_pMaze, moo_pDrlgMap, moo_pDrlgFile, moo_pFloorLayer, moo_pLvlPrestTxtRecord, moo_pLevel, moo_pDrlg);
		setup_data(original_pDrlgRoom, original_pMaze, original_pDrlgMap, original_pDrlgFile, original_pFloorLayer, original_pLvlPrestTxtRecord, original_pLevel, original_pDrlg);

		// Call both implementations
		sut(&moo_pDrlgRoom);
		original(&original_pDrlgRoom);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");

		// Clean up
		free_preset_units(moo_pDrlgMap.pPresetUnit);
		free_preset_units(original_pDrlgMap.pPresetUnit);
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86AC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_AddPresetRiverObjects, dll_base + 0x00046AC0);

		const auto nWidth = 8;
		const auto nHeight = 8;

		SUBCASE("")
		{
			for (auto nOffset : { -1, 0, 3 })
			{
				// Input data
				const auto x = random_unsigned_integer(0, 200);
				const auto y = random_unsigned_integer(0, 200);

				D2DrlgMapStrc moo_pDrlgMap{};
				D2DrlgGridStrc moo_pDrlgGrid{};
				int moo_pCellsFlags[nWidth * nHeight]{};
				int moo_pCellsRowOffsets[nHeight]{};
				D2DrlgMapStrc original_pDrlgMap{};
				D2DrlgGridStrc original_pDrlgGrid{};
				int original_pCellsFlags[nWidth * nHeight]{};
				int original_pCellsRowOffsets[nHeight]{};
				int nOffsetX = nOffset;

				const auto setup_data = [x, y, nWidth, nHeight, nOffsetX](
					D2DrlgMapStrc& pDrlgMap,
					D2DrlgGridStrc& pDrlgGrid,
					int(&pCellsFlags)[nWidth * nHeight],
					int(&pCellsRowOffsets)[nHeight]
				) {
					for (auto i = 0; i < nHeight; ++i)
					{
						pCellsRowOffsets[i] = i * nWidth;
					}

					// River curves which make the function skip rows
					const auto nX = nOffsetX < 0 ? 0 : nOffsetX;
					pCellsFlags[1 * nWidth + nX] = pack_tile_information(4, 0);
					pCellsFlags[5 * nWidth + nX] = pack_tile_information(4, 5);
					pCellsFlags[6 * nWidth + nX] = pack_tile_information(4, 39);

					pDrlgGrid.pCellsFlags = pCellsFlags;
					pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
					pDrlgGrid.nWidth = nWidth;
					pDrlgGrid.nHeight = nHeight;

					pDrlgMap.pDrlgCoord.nPosX = x;
					pDrlgMap.pDrlgCoord.nPosY = y;
					pDrlgMap.pDrlgCoord.nWidth = nWidth;
					pDrlgMap.pDrlgCoord.nHeight = nHeight;
				};

				setup_data(moo_pDrlgMap, moo_pDrlgGrid, moo_pCellsFlags, moo_pCellsRowOffsets);
				setup_data(original_pDrlgMap, original_pDrlgGrid, original_pCellsFlags, original_pCellsRowOffsets);

				// Call both implementations
				sut(&moo_pDrlgMap, nullptr, nOffsetX, &moo_pDrlgGrid);
				original(&original_pDrlgMap, nullptr, nOffsetX, &original_pDrlgGrid);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
				MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");

				// Clean up
				free_preset_units(moo_pDrlgMap.pPresetUnit);
				free_preset_units(original_pDrlgMap.pPresetUnit);
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86C80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreePresetRoomData, dll_base + 0x00046C80);

		SUBCASE("Without preset room data")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom
			) {
				pDrlgRoom.nType = DRLGTYPE_PRESET;
			};

			setup_data(moo_pDrlgRoom);
			setup_data(original_pDrlgRoom);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}

		SUBCASE("With preset room data")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgMapStrc moo_pDrlgMap{};
			D2DrlgFileStrc moo_pDrlgFile{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgMapStrc original_pDrlgMap{};
			D2DrlgFileStrc original_pDrlgFile{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgMapStrc& pDrlgMap,
				D2DrlgFileStrc& pDrlgFile,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				pDrlgFile.nWallLayers = 1;
				pDrlgFile.nFloorLayers = 1;

				pDrlgMap.pFile = &pDrlgFile;

				D2DrlgPresetRoomStrc* pMaze = D2_CALLOC_STRC_POOL(nullptr, D2DrlgPresetRoomStrc);
				pMaze->pMap = &pDrlgMap;
				DRLGGRID_InitializeGridCells(nullptr, &pMaze->pWallGrid[0], 9, 9);
				DRLGGRID_InitializeGridCells(nullptr, &pMaze->pTileTypeGrid[0], 9, 9);
				DRLGGRID_InitializeGridCells(nullptr, &pMaze->pFloorGrid[0], 9, 9);
				DRLGGRID_InitializeGridCells(nullptr, &pMaze->pCellGrid, 9, 9);
				pMaze->nTombStoneTiles = 6;
				pMaze->pTombStoneTiles = (D2CoordStrc*)D2_CALLOC_POOL(nullptr, sizeof(D2CoordStrc) * 6);

				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nType = DRLGTYPE_PRESET;
				pDrlgRoom.pMaze = pMaze;
			};

			setup_data(moo_pDrlgRoom, moo_pDrlgMap, moo_pDrlgFile, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pDrlgMap, original_pDrlgFile, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");

			// Check specific values
			CHECK_EQ(moo_pDrlgRoom.pMaze, nullptr);
			CHECK_EQ(original_pDrlgRoom.pMaze, nullptr);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86CE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreeDrlgGrids, dll_base + 0x00046CE0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgPresetRoomStrc moo_pMaze{};
			D2DrlgMapStrc moo_pDrlgMap{};
			D2DrlgFileStrc moo_pDrlgFile{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgPresetRoomStrc original_pMaze{};
			D2DrlgMapStrc original_pDrlgMap{};
			D2DrlgFileStrc original_pDrlgFile{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgPresetRoomStrc& pMaze,
				D2DrlgMapStrc& pDrlgMap,
				D2DrlgFileStrc& pDrlgFile
			) {
				pDrlgFile.nWallLayers = 2;
				pDrlgFile.nFloorLayers = 2;

				pDrlgMap.pFile = &pDrlgFile;

				pMaze.pMap = &pDrlgMap;
				for (auto i = 0; i < 2; ++i)
				{
					DRLGGRID_InitializeGridCells(nullptr, &pMaze.pWallGrid[i], 9, 9);
					DRLGGRID_InitializeGridCells(nullptr, &pMaze.pTileTypeGrid[i], 9, 9);
					DRLGGRID_InitializeGridCells(nullptr, &pMaze.pFloorGrid[i], 9, 9);
				}
				DRLGGRID_InitializeGridCells(nullptr, &pMaze.pCellGrid, 9, 9);

				pDrlgRoom.nType = DRLGTYPE_PRESET;
				pDrlgRoom.pMaze = &pMaze;
			};

			setup_data(moo_pDrlgRoom, moo_pMaze, moo_pDrlgMap, moo_pDrlgFile);
			setup_data(original_pDrlgRoom, original_pMaze, original_pDrlgMap, original_pDrlgFile);

			// Call both implementations
			sut(nullptr, &moo_pDrlgRoom);
			original(nullptr, &original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pMaze, original_pMaze, "Comparing pMaze");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86D60")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreeDrlgGridsFromPresetRoom, dll_base + 0x00046D60);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgPresetRoomStrc moo_pMaze{};
			D2DrlgMapStrc moo_pDrlgMap{};
			D2DrlgFileStrc moo_pDrlgFile{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgPresetRoomStrc original_pMaze{};
			D2DrlgMapStrc original_pDrlgMap{};
			D2DrlgFileStrc original_pDrlgFile{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgPresetRoomStrc& pMaze,
				D2DrlgMapStrc& pDrlgMap,
				D2DrlgFileStrc& pDrlgFile,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				pDrlgFile.nWallLayers = 2;
				pDrlgFile.nFloorLayers = 1;

				pDrlgMap.pFile = &pDrlgFile;

				pMaze.pMap = &pDrlgMap;
				for (auto i = 0; i < 2; ++i)
				{
					DRLGGRID_InitializeGridCells(nullptr, &pMaze.pWallGrid[i], 9, 9);
					DRLGGRID_InitializeGridCells(nullptr, &pMaze.pTileTypeGrid[i], 9, 9);
				}
				DRLGGRID_InitializeGridCells(nullptr, &pMaze.pFloorGrid[0], 9, 9);
				DRLGGRID_InitializeGridCells(nullptr, &pMaze.pCellGrid, 9, 9);

				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nType = DRLGTYPE_PRESET;
				pDrlgRoom.pMaze = &pMaze;
			};

			setup_data(moo_pDrlgRoom, moo_pMaze, moo_pDrlgMap, moo_pDrlgFile, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pMaze, original_pDrlgMap, original_pDrlgFile, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pMaze, original_pMaze, "Comparing pMaze");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86D80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_AllocPresetRoomData, dll_base + 0x00046D80);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nType = DRLGTYPE_PRESET;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pDrlgRoom.pMaze, original_pDrlgRoom.pMaze, "Comparing pMaze");

			// Check specific values
			CHECK_NE(moo_pDrlgRoom.pMaze, nullptr);
			CHECK_NE(original_pDrlgRoom.pMaze, nullptr);

			// Clean up
			D2_FREE_POOL(nullptr, moo_pDrlgRoom.pMaze);
			D2_FREE_POOL(nullptr, original_pDrlgRoom.pMaze);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86DC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_InitPresetRoomData, dll_base + 0x00046DC0);

		bool bHasMazeGrid = false;
		uint32_t dwPopulate = 0;
		uint32_t dwLevelFlags = 0;

		SUBCASE("With maze grid")
		{
			bHasMazeGrid = true;
			dwPopulate = 1;
		}

		SUBCASE("Without maze grid")
		{
			dwPopulate = 1;
			dwLevelFlags = DRLGLEVELFLAG_AUTOMAP_REVEAL;
		}

		SUBCASE("Not populated")
		{
			bHasMazeGrid = true;
		}

		// Input data
		const auto seed = random_unsigned_integer();
		const auto x = random_unsigned_integer(0, 200);
		const auto y = random_unsigned_integer(0, 200);
		const auto width = random_unsigned_integer(1, 8);
		const auto height = random_unsigned_integer(1, 8);
		const auto level_prest = random_unsigned_integer(0, 1000);

		D2DrlgLevelStrc moo_pLevel{};
		D2DrlgStrc moo_pDrlg{};
		D2DrlgMapStrc moo_pDrlgMap{};
		D2LvlPrestTxt moo_pLvlPrestTxtRecord{};
		D2DrlgCoordStrc moo_pDrlgCoord{};
		D2DrlgGridStrc moo_a7{};
		D2DrlgLevelStrc original_pLevel{};
		D2DrlgStrc original_pDrlg{};
		D2DrlgMapStrc original_pDrlgMap{};
		D2LvlPrestTxt original_pLvlPrestTxtRecord{};
		D2DrlgCoordStrc original_pDrlgCoord{};
		D2DrlgGridStrc original_a7{};
		uint32_t dwDT1Mask = random_unsigned_integer();
		int dwRoomFlags = random_unsigned_integer(0, 0xF) << 4;
		int dwPresetFlags = random_unsigned_integer(0, 3);

		const auto setup_data = [seed, x, y, width, height, level_prest, dwPopulate, dwLevelFlags](
			D2DrlgLevelStrc& pLevel,
			D2DrlgStrc& pDrlg,
			D2DrlgMapStrc& pDrlgMap,
			D2LvlPrestTxt& pLvlPrestTxtRecord,
			D2DrlgCoordStrc& pDrlgCoord,
			D2DrlgGridStrc& a7
		) {
			pLevel.pDrlg = &pDrlg;
			pLevel.dwFlags = dwLevelFlags;
			pLevel.pSeed.nLowSeed = seed;
			pLevel.pSeed.nHighSeed = 666;

			pLvlPrestTxtRecord.dwDef = level_prest;
			pLvlPrestTxtRecord.dwPopulate = dwPopulate;

			pDrlgMap.nLevelPrest = level_prest;
			pDrlgMap.pLvlPrestTxtRecord = &pLvlPrestTxtRecord;

			pDrlgCoord.nPosX = x;
			pDrlgCoord.nPosY = y;
			pDrlgCoord.nWidth = width;
			pDrlgCoord.nHeight = height;

			a7.nWidth = 3;
			a7.nHeight = 2;
		};

		setup_data(moo_pLevel, moo_pDrlg, moo_pDrlgMap, moo_pLvlPrestTxtRecord, moo_pDrlgCoord, moo_a7);
		setup_data(original_pLevel, original_pDrlg, original_pDrlgMap, original_pLvlPrestTxtRecord, original_pDrlgCoord, original_a7);

		D2DrlgGridStrc* moo_pMazeGrid = bHasMazeGrid ? &moo_a7 : nullptr;
		D2DrlgGridStrc* original_pMazeGrid = bHasMazeGrid ? &original_a7 : nullptr;

		// Call both implementations
		const auto moo_result = sut(&moo_pLevel, &moo_pDrlgMap, &moo_pDrlgCoord, dwDT1Mask, dwRoomFlags, dwPresetFlags, moo_pMazeGrid);
		const auto original_result = original(&original_pLevel, &original_pDrlgMap, &original_pDrlgCoord, dwDT1Mask, dwRoomFlags, dwPresetFlags, original_pMazeGrid);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		MOO_CHECK_EQ(moo_result->pMaze, original_result->pMaze, "Comparing result pMaze");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
		MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
		MOO_CHECK_EQ(moo_a7, original_a7, "Comparing a7");

		// Clean up
		free_preset_rooms(moo_pLevel);
		free_preset_rooms(original_pLevel);
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86E50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_InitPresetRoomGrids, dll_base + 0x00046E50);

		SUBCASE("")
		{
			// Input data
			const auto nMapWidth = 16;
			const auto nMapHeight = 16;
			const auto nLayerSize = (nMapWidth + 1) * (nMapHeight + 1);

			const auto x = random_unsigned_integer(0, 200);
			const auto y = random_unsigned_integer(0, 200);

			int wall_layers[2][nLayerSize]{};
			int tile_type_layers[2][nLayerSize]{};
			int floor_layer[nLayerSize]{};
			int shadow_layer[nLayerSize]{};
			for (auto i = 0; i < nLayerSize; ++i)
			{
				wall_layers[0][i] = random_unsigned_integer() & 0x3FFFFFF;
				wall_layers[1][i] = random_unsigned_integer() & 0x3FFFFFF;
				tile_type_layers[0][i] = random_unsigned_integer(0, 20);
				tile_type_layers[1][i] = random_unsigned_integer(0, 20);
				floor_layer[i] = random_unsigned_integer() & 0x3FFFFFF;
				shadow_layer[i] = random_unsigned_integer() & 0x3FFFFFF;
			}

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgPresetRoomStrc moo_pMaze{};
			D2DrlgMapStrc moo_pDrlgMap{};
			D2DrlgFileStrc moo_pDrlgFile{};
			int moo_pWallLayers[2][nLayerSize]{};
			int moo_pTileTypeLayers[2][nLayerSize]{};
			int moo_pFloorLayer[nLayerSize]{};
			int moo_pShadowLayer[nLayerSize]{};
			D2PresetUnitStrc moo_pPresetUnits[3]{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgPresetRoomStrc original_pMaze{};
			D2DrlgMapStrc original_pDrlgMap{};
			D2DrlgFileStrc original_pDrlgFile{};
			int original_pWallLayers[2][nLayerSize]{};
			int original_pTileTypeLayers[2][nLayerSize]{};
			int original_pFloorLayer[nLayerSize]{};
			int original_pShadowLayer[nLayerSize]{};
			D2PresetUnitStrc original_pPresetUnits[3]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [&, x, y](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgPresetRoomStrc& pMaze,
				D2DrlgMapStrc& pDrlgMap,
				D2DrlgFileStrc& pDrlgFile,
				int(&pWallLayers)[2][nLayerSize],
				int(&pTileTypeLayers)[2][nLayerSize],
				int(&pFloorLayer)[nLayerSize],
				int(&pShadowLayer)[nLayerSize],
				D2PresetUnitStrc(&pPresetUnits)[3],
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				std::memcpy(pWallLayers, wall_layers, sizeof(wall_layers));
				std::memcpy(pTileTypeLayers, tile_type_layers, sizeof(tile_type_layers));
				std::memcpy(pFloorLayer, floor_layer, sizeof(floor_layer));
				std::memcpy(pShadowLayer, shadow_layer, sizeof(shadow_layer));

				pDrlgFile.nWidth = nMapWidth;
				pDrlgFile.nHeight = nMapHeight;
				pDrlgFile.nWallLayers = 2;
				pDrlgFile.nFloorLayers = 1;
				for (auto i = 0; i < 2; ++i)
				{
					pDrlgFile.pWallLayer[i] = pWallLayers[i];
					pDrlgFile.pTileTypeLayer[i] = pTileTypeLayers[i];
				}
				pDrlgFile.pFloorLayer[0] = pFloorLayer;
				pDrlgFile.pShadowLayer = pShadowLayer;

				// Units 0 and 2 are inside of the room, unit 1 is outside
				pPresetUnits[0].nUnitType = UNIT_OBJECT;
				pPresetUnits[0].nXpos = (x + 9) * 5 + 1;
				pPresetUnits[0].nYpos = (y + 5) * 5 + 2;
				pPresetUnits[0].pNext = &pPresetUnits[1];
				pPresetUnits[1].nUnitType = UNIT_MONSTER;
				pPresetUnits[1].nXpos = x * 5;
				pPresetUnits[1].nYpos = y * 5;
				pPresetUnits[1].pNext = &pPresetUnits[2];
				pPresetUnits[2].nUnitType = UNIT_TILE;
				pPresetUnits[2].nXpos = (x + 15) * 5 + 4;
				pPresetUnits[2].nYpos = (y + 11) * 5 + 4;

				pDrlgMap.pFile = &pDrlgFile;
				pDrlgMap.pDrlgCoord.nPosX = x;
				pDrlgMap.pDrlgCoord.nPosY = y;
				pDrlgMap.pDrlgCoord.nWidth = nMapWidth;
				pDrlgMap.pDrlgCoord.nHeight = nMapHeight;
				pDrlgMap.pPresetUnit = &pPresetUnits[0];

				pMaze.pMap = &pDrlgMap;

				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nType = DRLGTYPE_PRESET;
				pDrlgRoom.pMaze = &pMaze;
				pDrlgRoom.nTileXPos = x + 8;
				pDrlgRoom.nTileYPos = y + 4;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
			};

			setup_data(moo_pDrlgRoom, moo_pMaze, moo_pDrlgMap, moo_pDrlgFile, moo_pWallLayers, moo_pTileTypeLayers, moo_pFloorLayer, moo_pShadowLayer, moo_pPresetUnits, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pMaze, original_pDrlgMap, original_pDrlgFile, original_pWallLayers, original_pTileTypeLayers, original_pFloorLayer, original_pShadowLayer, original_pPresetUnits, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pMaze, original_pMaze, "Comparing pMaze");
			MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");

			auto moo_wall_layers = DynamicArray<int>{ &moo_pWallLayers[0][0], 2 * nLayerSize };
			auto original_wall_layers = DynamicArray<int>{ &original_pWallLayers[0][0], 2 * nLayerSize };
			MOO_CHECK_EQ(moo_wall_layers, original_wall_layers, "Comparing pWallLayers");
			auto moo_floor_layer = DynamicArray<int>{ moo_pFloorLayer, nLayerSize };
			auto original_floor_layer = DynamicArray<int>{ original_pFloorLayer, nLayerSize };
			MOO_CHECK_EQ(moo_floor_layer, original_floor_layer, "Comparing pFloorLayer");
			auto moo_shadow_layer = DynamicArray<int>{ moo_pShadowLayer, nLayerSize };
			auto original_shadow_layer = DynamicArray<int>{ original_pShadowLayer, nLayerSize };
			MOO_CHECK_EQ(moo_shadow_layer, original_shadow_layer, "Comparing pShadowLayer");

			// Check specific values
			CHECK_EQ(moo_pDrlgRoom.pPresetUnits, &moo_pPresetUnits[2]);
			CHECK_EQ(moo_pDrlgMap.pPresetUnit, &moo_pPresetUnits[1]);

			// Clean up
			DRLGPRESET_FreeDrlgGrids(nullptr, &moo_pDrlgRoom);
			DRLGPRESET_FreeDrlgGrids(nullptr, &original_pDrlgRoom);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD870F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetTombStoneTileCoords, dll_base + 0x000470F0);

		SUBCASE("")
		{
			for (auto nType : { DRLGTYPE_MAZE, DRLGTYPE_PRESET, DRLGTYPE_OUTDOOR })
			{
				// Input data
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgPresetRoomStrc moo_pMaze{};
				D2CoordStrc moo_pTombStoneTiles[3]{};
				D2CoordStrc* moo_ppTombStoneTiles{};
				int moo_pnTombStoneTiles{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgPresetRoomStrc original_pMaze{};
				D2CoordStrc original_pTombStoneTiles[3]{};
				D2CoordStrc* original_ppTombStoneTiles{};
				int original_pnTombStoneTiles{};

				const auto setup_data = [nType](
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgPresetRoomStrc& pMaze,
					D2CoordStrc(&pTombStoneTiles)[3]
				) {
					for (auto i = 0; i < 3; ++i)
					{
						pTombStoneTiles[i].nX = 10 * i + 2;
						pTombStoneTiles[i].nY = 5 * i + 2;
					}

					pMaze.pTombStoneTiles = pTombStoneTiles;
					pMaze.nTombStoneTiles = 3;

					pDrlgRoom.nType = nType;
					pDrlgRoom.pMaze = &pMaze;
				};

				setup_data(moo_pDrlgRoom, moo_pMaze, moo_pTombStoneTiles);
				setup_data(original_pDrlgRoom, original_pMaze, original_pTombStoneTiles);

				// Call both implementations
				sut(&moo_pDrlgRoom, &moo_ppTombStoneTiles, &moo_pnTombStoneTiles);
				original(&original_pDrlgRoom, &original_ppTombStoneTiles, &original_pnTombStoneTiles);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
				MOO_CHECK_EQ(moo_ppTombStoneTiles, original_ppTombStoneTiles, "Comparing ppTombStoneTiles");
				MOO_CHECK_EQ(moo_pnTombStoneTiles, original_pnTombStoneTiles, "Comparing pnTombStoneTiles");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87130")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_AddPresetRoomMapTiles, dll_base + 0x00047130);

		int nLevelId = 0;

		SUBCASE("Burial grounds")
		{
			nLevelId = LEVEL_BURIALGROUNDS;
		}

		SUBCASE("Other level")
		{
			nLevelId = LEVEL_BLOODMOOR;
		}

		// Input data
		// No floor or wall layers are used, since loading tiles requires the tile libraries of D2CMP.
		// The wall grid is only used to look for tomb stones.
		const auto nWidth = 8;
		const auto nHeight = 8;
		const auto nGridSize = (nWidth + 1) * (nHeight + 1);

		const auto x = random_unsigned_integer(0, 200);
		const auto y = random_unsigned_integer(0, 200);

		D2DrlgRoomStrc moo_pDrlgRoom{};
		D2DrlgPresetRoomStrc moo_pMaze{};
		int moo_pWallCellsFlags[nGridSize]{};
		int moo_pWallCellsRowOffsets[nHeight + 1]{};
		int moo_pCellsFlags[nGridSize]{};
		int moo_pCellsRowOffsets[nHeight + 1]{};
		D2DrlgMapStrc moo_pDrlgMap{};
		D2DrlgFileStrc moo_pDrlgFile{};
		D2LvlPrestTxt moo_pLvlPrestTxtRecord{};
		D2DrlgLevelStrc moo_pLevel{};
		D2DrlgStrc moo_pDrlg{};
		D2DrlgRoomStrc original_pDrlgRoom{};
		D2DrlgPresetRoomStrc original_pMaze{};
		int original_pWallCellsFlags[nGridSize]{};
		int original_pWallCellsRowOffsets[nHeight + 1]{};
		int original_pCellsFlags[nGridSize]{};
		int original_pCellsRowOffsets[nHeight + 1]{};
		D2DrlgMapStrc original_pDrlgMap{};
		D2DrlgFileStrc original_pDrlgFile{};
		D2LvlPrestTxt original_pLvlPrestTxtRecord{};
		D2DrlgLevelStrc original_pLevel{};
		D2DrlgStrc original_pDrlg{};

		const auto setup_data = [=](
			D2DrlgRoomStrc& pDrlgRoom,
			D2DrlgPresetRoomStrc& pMaze,
			int(&pWallCellsFlags)[nGridSize],
			int(&pWallCellsRowOffsets)[nHeight + 1],
			int(&pCellsFlags)[nGridSize],
			int(&pCellsRowOffsets)[nHeight + 1],
			D2DrlgMapStrc& pDrlgMap,
			D2DrlgFileStrc& pDrlgFile,
			D2LvlPrestTxt& pLvlPrestTxtRecord,
			D2DrlgLevelStrc& pLevel,
			D2DrlgStrc& pDrlg
		) {
			for (auto i = 0; i < nHeight + 1; ++i)
			{
				pWallCellsRowOffsets[i] = i * (nWidth + 1);
				pCellsRowOffsets[i] = i * (nWidth + 1);
			}

			// 7 tomb stones, but only the first 6 are stored
			for (auto i = 0; i < 7; ++i)
			{
				pWallCellsFlags[(i % 4) * (nWidth + 1) + i] = pack_tile_information(10, 23 + i % 5);
			}
			pWallCellsFlags[7 * (nWidth + 1) + 7] = pack_tile_information(10, 28);

			pMaze.pWallGrid[0].pCellsFlags = pWallCellsFlags;
			pMaze.pWallGrid[0].pCellsRowOffsets = pWallCellsRowOffsets;
			pMaze.pWallGrid[0].nWidth = nWidth + 1;
			pMaze.pWallGrid[0].nHeight = nHeight + 1;
			pMaze.pCellGrid.pCellsFlags = pCellsFlags;
			pMaze.pCellGrid.pCellsRowOffsets = pCellsRowOffsets;
			pMaze.pCellGrid.nWidth = nWidth + 1;
			pMaze.pCellGrid.nHeight = nHeight + 1;
			pMaze.nLevelPrest = LVLPREST_ACT1_WILD_BORDER_1;
			pMaze.pMap = &pDrlgMap;

			pDrlgMap.nLevelPrest = LVLPREST_ACT1_WILD_BORDER_1;
			pDrlgMap.pLvlPrestTxtRecord = &pLvlPrestTxtRecord;
			pDrlgMap.pFile = &pDrlgFile;
			pDrlgMap.pDrlgCoord.nPosX = x;
			pDrlgMap.pDrlgCoord.nPosY = y;
			pDrlgMap.pDrlgCoord.nWidth = nWidth;
			pDrlgMap.pDrlgCoord.nHeight = nHeight;

			pDrlgFile.nWidth = nWidth;
			pDrlgFile.nHeight = nHeight;

			pLvlPrestTxtRecord.dwDef = LVLPREST_ACT1_WILD_BORDER_1;

			pLevel.pDrlg = &pDrlg;
			pLevel.nLevelId = nLevelId;

			pDrlgRoom.pLevel = &pLevel;
			pDrlgRoom.nType = DRLGTYPE_PRESET;
			pDrlgRoom.pMaze = &pMaze;
			pDrlgRoom.nTileXPos = x;
			pDrlgRoom.nTileYPos = y;
			pDrlgRoom.nTileWidth = nWidth;
			pDrlgRoom.nTileHeight = nHeight;
		};

		setup_data(moo_pDrlgRoom, moo_pMaze, moo_pWallCellsFlags, moo_pWallCellsRowOffsets, moo_pCellsFlags, moo_pCellsRowOffsets, moo_pDrlgMap, moo_pDrlgFile, moo_pLvlPrestTxtRecord, moo_pLevel, moo_pDrlg);
		setup_data(original_pDrlgRoom, original_pMaze, original_pWallCellsFlags, original_pWallCellsRowOffsets, original_pCellsFlags, original_pCellsRowOffsets, original_pDrlgMap, original_pDrlgFile, original_pLvlPrestTxtRecord, original_pLevel, original_pDrlg);

		// Call both implementations
		sut(&moo_pDrlgRoom);
		original(&original_pDrlgRoom);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		MOO_CHECK_EQ(moo_pMaze, original_pMaze, "Comparing pMaze");
		MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		MOO_CHECK_EQ(moo_pMaze.nTombStoneTiles, original_pMaze.nTombStoneTiles, "Comparing nTombStoneTiles");
		if (moo_pMaze.pTombStoneTiles && original_pMaze.pTombStoneTiles)
		{
			auto moo_tomb_stone_tiles = DynamicArray<int>{ reinterpret_cast<int*>(moo_pMaze.pTombStoneTiles), 2 * moo_pMaze.nTombStoneTiles };
			auto original_tomb_stone_tiles = DynamicArray<int>{ reinterpret_cast<int*>(original_pMaze.pTombStoneTiles), 2 * original_pMaze.nTombStoneTiles };
			MOO_CHECK_EQ(moo_tomb_stone_tiles, original_tomb_stone_tiles, "Comparing pTombStoneTiles");
		}

		// Clean up
		const auto free_room_data = [](
			D2DrlgRoomStrc& pDrlgRoom
		) {
			if (pDrlgRoom.pLogicalRoomInfo)
			{
				D2_FREE_POOL(nullptr, pDrlgRoom.pLogicalRoomInfo->pCoordList);
				D2_FREE_POOL(nullptr, pDrlgRoom.pLogicalRoomInfo);
			}

			if (pDrlgRoom.pMaze->pTombStoneTiles)
			{
				D2_FREE_POOL(nullptr, pDrlgRoom.pMaze->pTombStoneTiles);
			}

			D2_FREE_POOL(nullptr, pDrlgRoom.pTileGrid);
		};

		free_room_data(moo_pDrlgRoom);
		free_room_data(original_pDrlgRoom);
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87560")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_BuildArea, dll_base + 0x00047560);

		SUBCASE("")
		{
			for (auto bSingleRoomValue : { FALSE, TRUE })
			{
				// Input data
				const auto seed = random_unsigned_integer();
				const auto x = random_unsigned_integer(0, 200);
				const auto y = random_unsigned_integer(0, 200);
				const auto outdoors = random_unsigned_integer(0, 1);
				const auto level_prest = random_unsigned_integer(0, 1000);

				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgStrc moo_pDrlg{};
				D2DrlgWarpStrc moo_pDrlgWarp{};
				D2DrlgMapStrc moo_pDrlgMap{};
				D2LvlPrestTxt moo_pLvlPrestTxtRecord{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgStrc original_pDrlg{};
				D2DrlgWarpStrc original_pDrlgWarp{};
				D2DrlgMapStrc original_pDrlgMap{};
				D2LvlPrestTxt original_pLvlPrestTxtRecord{};
				int nFlags = random_unsigned_integer(0, 0xF);
				BOOL bSingleRoom = bSingleRoomValue;

				const auto setup_data = [seed, x, y, outdoors, level_prest](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgWarpStrc& pDrlgWarp,
					D2DrlgMapStrc& pDrlgMap,
					D2LvlPrestTxt& pLvlPrestTxtRecord
				) {
					// Vis and warp arrays come from the warp list instead of LevelDefs.txt
					pDrlgWarp.nLevel = LEVEL_BLOODMOOR;
					for (auto i = 0; i < 8; ++i)
					{
						pDrlgWarp.nVis[i] = i % 3 ? LEVEL_COLDPLAINS : 0;
						pDrlgWarp.nWarp[i] = i % 2 ? -1 : i;
					}

					pDrlg.pWarp = &pDrlgWarp;

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_BLOODMOOR;
					pLevel.pSeed.nLowSeed = seed;
					pLevel.pSeed.nHighSeed = 666;

					// No files are loaded since neither scan nor pops are used
					pLvlPrestTxtRecord.dwDef = level_prest;
					pLvlPrestTxtRecord.dwPopulate = 1;
					pLvlPrestTxtRecord.dwOutdoors = outdoors;
					pLvlPrestTxtRecord.dwDt1Mask = 0x3;

					pDrlgMap.nLevelPrest = level_prest;
					pDrlgMap.pLvlPrestTxtRecord = &pLvlPrestTxtRecord;
					pDrlgMap.pDrlgCoord.nPosX = x;
					pDrlgMap.pDrlgCoord.nPosY = y;
					pDrlgMap.pDrlgCoord.nWidth = 20;
					pDrlgMap.pDrlgCoord.nHeight = 12;
				};

				setup_data(moo_pLevel, moo_pDrlg, moo_pDrlgWarp, moo_pDrlgMap, moo_pLvlPrestTxtRecord);
				setup_data(original_pLevel, original_pDrlg, original_pDrlgWarp, original_pDrlgMap, original_pLvlPrestTxtRecord);

				// Call both implementations
				const auto moo_result = sut(&moo_pLevel, &moo_pDrlgMap, nFlags, bSingleRoom);
				const auto original_result = original(&original_pLevel, &original_pDrlgMap, nFlags, bSingleRoom);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");

				// Compare all created rooms
				MOO_CHECK_EQ(moo_pLevel.nRooms, original_pLevel.nRooms, "Comparing nRooms");
				for (auto moo_pDrlgRoom = moo_pLevel.pFirstRoomEx, original_pDrlgRoom = original_pLevel.pFirstRoomEx;
					moo_pDrlgRoom && original_pDrlgRoom;
					moo_pDrlgRoom = moo_pDrlgRoom->pDrlgRoomNext, original_pDrlgRoom = original_pDrlgRoom->pDrlgRoomNext)
				{
					MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing created rooms");
				}

				// Clean up
				free_preset_rooms(moo_pLevel);
				free_preset_rooms(original_pLevel);
			}
		}
	}

	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FD87760")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_BuildPresetArea, dll_base + 0x00047760);

		const auto nMapWidth = 16;
		const auto nMapHeight = 16;
		const auto nLayerSize = (nMapWidth + 1) * (nMapHeight + 1);
		const auto nGridWidth = nMapWidth / 8 + 1;
		const auto nGridHeight = nMapHeight / 8 + 1;

		uint32_t dwScan = 0;
		uint32_t dwPops = 0;

		SUBCASE("Without scan")
		{
		}

		SUBCASE("With scan")
		{
			dwScan = 1;
		}

		SUBCASE("With pops")
		{
			dwPops = 3;
		}

		SUBCASE("With scan and pops")
		{
			dwScan = 1;
			dwPops = 3;
		}

		// The DS1 file is taken from the list of loaded files, so no archive is needed
		const char* szFile = "DATA\\GLOBAL\\TILES\\ACT1\\WILD\\test.ds1";

		for (auto bSingleRoomValue : { FALSE, TRUE })
		{
			// Input data
			const auto seed = random_unsigned_integer();
			const auto x = random_unsigned_integer(0, 200);
			const auto y = random_unsigned_integer(0, 200);

			int wall_layer[nLayerSize]{};
			int tile_type_layer[nLayerSize]{};
			for (auto i = 0; i < nLayerSize; ++i)
			{
				wall_layer[i] = random_unsigned_integer() & 0x0FFFFFFF;
			}

			// Exits of different kinds: Scan flags, pops and tile infos
			const int exits[][4] =
			{
				// nX, nY, nTileStyle, nTileSequence
				{ 1, 1, 3, 0 },
				{ 9, 2, 5, 4 },
				{ 12, 14, 7, 1 },
				{ 2, 9, 10, 2 },
				{ 4, 11, 10, 2 },
				{ 6, 3, 14, 5 },
				{ 3, 6, 30, 1 },
				{ 13, 4, 31, 2 },
				{ 8, 8, 32, 0 },
				{ 14, 10, 33, 0 },
			};

			for (const auto& exit_tile : exits)
			{
				const auto nIndex = exit_tile[1] * (nMapWidth + 1) + exit_tile[0];
				wall_layer[nIndex] = pack_tile_information(exit_tile[2], exit_tile[3]);
				tile_type_layer[nIndex] = nIndex % 2 ? TILETYPE_WALL_RIGHT_EXIT : TILETYPE_WALL_LEFT_EXIT;
			}

			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pDrlgWarp{};
			D2DrlgGridStrc moo_pDrlgGrid{};
			int moo_pCellsFlags[nGridWidth * nGridHeight]{};
			int moo_pCellsRowOffsets[nGridHeight]{};
			D2DrlgMapStrc moo_pDrlgMap{};
			D2LvlPrestTxt moo_pLvlPrestTxtRecord{};
			D2LevelFileListStrc moo_pLevelFile{};
			D2DrlgFileStrc moo_pDrlgFile{};
			int moo_pWallLayer[nLayerSize]{};
			int moo_pTileTypeLayer[nLayerSize]{};
			D2PresetUnitStrc moo_pPresetUnits[3]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pDrlgWarp{};
			D2DrlgGridStrc original_pDrlgGrid{};
			int original_pCellsFlags[nGridWidth * nGridHeight]{};
			int original_pCellsRowOffsets[nGridHeight]{};
			D2DrlgMapStrc original_pDrlgMap{};
			D2LvlPrestTxt original_pLvlPrestTxtRecord{};
			D2LevelFileListStrc original_pLevelFile{};
			D2DrlgFileStrc original_pDrlgFile{};
			int original_pWallLayer[nLayerSize]{};
			int original_pTileTypeLayer[nLayerSize]{};
			D2PresetUnitStrc original_pPresetUnits[3]{};
			int nFlags = random_unsigned_integer(0, 0xF);
			BOOL bSingleRoom = bSingleRoomValue;

			const auto setup_data = [&, seed, x, y](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pDrlgWarp,
				D2DrlgGridStrc& pDrlgGrid,
				int(&pCellsFlags)[nGridWidth * nGridHeight],
				int(&pCellsRowOffsets)[nGridHeight],
				D2DrlgMapStrc& pDrlgMap,
				D2LvlPrestTxt& pLvlPrestTxtRecord,
				D2LevelFileListStrc& pLevelFile,
				D2DrlgFileStrc& pDrlgFile,
				int(&pWallLayer)[nLayerSize],
				int(&pTileTypeLayer)[nLayerSize],
				D2PresetUnitStrc(&pPresetUnits)[3]
			) {
				// Vis and warp arrays come from the warp list instead of LevelDefs.txt
				pDrlgWarp.nLevel = LEVEL_BLOODMOOR;
				for (auto i = 0; i < 8; ++i)
				{
					pDrlgWarp.nVis[i] = i % 3 ? LEVEL_COLDPLAINS : 0;
					pDrlgWarp.nWarp[i] = i % 2 ? -1 : i;
				}

				pDrlg.pWarp = &pDrlgWarp;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_BLOODMOOR;
				pLevel.pSeed.nLowSeed = seed;
				pLevel.pSeed.nHighSeed = 666;

				for (auto i = 0; i < nGridHeight; ++i)
				{
					pCellsRowOffsets[i] = i * nGridWidth;
				}

				pDrlgGrid.pCellsFlags = pCellsFlags;
				pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
				pDrlgGrid.nWidth = nGridWidth;
				pDrlgGrid.nHeight = nGridHeight;

				std::memcpy(pWallLayer, wall_layer, sizeof(wall_layer));
				std::memcpy(pTileTypeLayer, tile_type_layer, sizeof(tile_type_layer));

				// Waypoint and other objects
				const int units[3][3] =
				{
					// nUnitType, nIndex, nXpos
					{ UNIT_OBJECT, 119, 52 },
					{ UNIT_OBJECT, 1, 7 },
					{ UNIT_TILE, 2, 61 },
				};

				for (auto i = 0; i < 3; ++i)
				{
					pPresetUnits[i].nUnitType = units[i][0];
					pPresetUnits[i].nIndex = units[i][1];
					pPresetUnits[i].nXpos = units[i][2];
					pPresetUnits[i].nYpos = 45 - 10 * i;
					pPresetUnits[i].pNext = i + 1 < 3 ? &pPresetUnits[i + 1] : nullptr;
				}

				pDrlgFile.nWidth = nMapWidth;
				pDrlgFile.nHeight = nMapHeight;
				pDrlgFile.nWallLayers = 1;
				pDrlgFile.nFloorLayers = 0;
				pDrlgFile.pWallLayer[0] = pWallLayer;
				pDrlgFile.pTileTypeLayer[0] = pTileTypeLayer;
				pDrlgFile.pPresetUnit = &pPresetUnits[0];

				strcpy_s(pLevelFile.szPath, szFile);
				pLevelFile.nRefCount = 1;
				pLevelFile.pFile = &pDrlgFile;

				pLvlPrestTxtRecord.dwScan = dwScan;
				pLvlPrestTxtRecord.dwPops = dwPops;
				strcpy_s(pLvlPrestTxtRecord.szFile[1], szFile);

				pDrlgMap.nPickedFile = 1;
				pDrlgMap.pLvlPrestTxtRecord = &pLvlPrestTxtRecord;
				pDrlgMap.pDrlgCoord.nPosX = x;
				pDrlgMap.pDrlgCoord.nPosY = y;
				pDrlgMap.pDrlgCoord.nWidth = nMapWidth;
				pDrlgMap.pDrlgCoord.nHeight = nMapHeight;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pDrlgWarp, moo_pDrlgGrid, moo_pCellsFlags, moo_pCellsRowOffsets, moo_pDrlgMap, moo_pLvlPrestTxtRecord, moo_pLevelFile, moo_pDrlgFile, moo_pWallLayer, moo_pTileTypeLayer, moo_pPresetUnits);
			setup_data(original_pLevel, original_pDrlg, original_pDrlgWarp, original_pDrlgGrid, original_pCellsFlags, original_pCellsRowOffsets, original_pDrlgMap, original_pLvlPrestTxtRecord, original_pLevelFile, original_pDrlgFile, original_pWallLayer, original_pTileTypeLayer, original_pPresetUnits);

			gpLevelFilesList_6FDEA700 = &moo_pLevelFile;
			*original_gpLevelFilesList = &original_pLevelFile;

			// Call both implementations
			sut(&moo_pLevel, &moo_pDrlgGrid, nFlags, &moo_pDrlgMap, bSingleRoom);
			original(&original_pLevel, &original_pDrlgGrid, nFlags, &original_pDrlgMap, bSingleRoom);

			gpLevelFilesList_6FDEA700 = nullptr;
			*original_gpLevelFilesList = nullptr;

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
			MOO_CHECK_EQ(moo_pLevelFile, original_pLevelFile, "Comparing pLevelFile");

			auto moo_cells_flags = DynamicArray<int>{ moo_pCellsFlags, nGridWidth * nGridHeight };
			auto original_cells_flags = DynamicArray<int>{ original_pCellsFlags, nGridWidth * nGridHeight };
			MOO_CHECK_EQ(moo_cells_flags, original_cells_flags, "Comparing pDrlgGrid cells");

			MOO_CHECK_EQ(moo_pLevel.nTileInfo, original_pLevel.nTileInfo, "Comparing nTileInfo");
			auto moo_tile_info = DynamicArray<int>{ reinterpret_cast<int*>(moo_pLevel.pTileInfo), 3 * moo_pLevel.nTileInfo };
			auto original_tile_info = DynamicArray<int>{ reinterpret_cast<int*>(original_pLevel.pTileInfo), 3 * original_pLevel.nTileInfo };
			MOO_CHECK_EQ(moo_tile_info, original_tile_info, "Comparing pTileInfo");

			MOO_CHECK_EQ(moo_pDrlgMap.nPops, original_pDrlgMap.nPops, "Comparing nPops");
			if (dwPops)
			{
				auto moo_pops_index = DynamicArray<int>{ moo_pDrlgMap.pPopsIndex, moo_pDrlgMap.nPops };
				auto original_pops_index = DynamicArray<int>{ original_pDrlgMap.pPopsIndex, original_pDrlgMap.nPops };
				MOO_CHECK_EQ(moo_pops_index, original_pops_index, "Comparing pPopsIndex");
				auto moo_pops_sub_index = DynamicArray<int>{ moo_pDrlgMap.pPopsSubIndex, moo_pDrlgMap.nPops };
				auto original_pops_sub_index = DynamicArray<int>{ original_pDrlgMap.pPopsSubIndex, original_pDrlgMap.nPops };
				MOO_CHECK_EQ(moo_pops_sub_index, original_pops_sub_index, "Comparing pPopsSubIndex");
				auto moo_pops_location = DynamicArray<int>{ reinterpret_cast<int*>(moo_pDrlgMap.pPopsLocation), 4 * moo_pDrlgMap.nPops };
				auto original_pops_location = DynamicArray<int>{ reinterpret_cast<int*>(original_pDrlgMap.pPopsLocation), 4 * original_pDrlgMap.nPops };
				MOO_CHECK_EQ(moo_pops_location, original_pops_location, "Comparing pPopsLocation");
			}

			// Clean up
			const auto free_map_data = [](
				D2DrlgMapStrc& pDrlgMap
			) {
				if (pDrlgMap.pPopsIndex)
				{
					free_pops(pDrlgMap);
				}

				free_preset_units(pDrlgMap.pPresetUnit);
			};

			free_map_data(moo_pDrlgMap);
			free_map_data(original_pDrlgMap);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87E10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_SetPickedFileInDrlgMap, dll_base + 0x00047E10);

		SUBCASE("")
		{
			// Input data
			D2DrlgMapStrc moo_pDrlgMap{};
			D2DrlgMapStrc original_pDrlgMap{};
			int nPickedFile = random_unsigned_integer(0, 5);

			const auto setup_data = [](
				D2DrlgMapStrc& pDrlgMap
			) {
				pDrlgMap.nPickedFile = 0;
			};

			setup_data(moo_pDrlgMap);
			setup_data(original_pDrlgMap);

			// Call both implementations
			sut(&moo_pDrlgMap, nPickedFile);
			original(&original_pDrlgMap, nPickedFile);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
			MOO_CHECK_EQ(moo_pDrlgMap.nPickedFile, original_pDrlgMap.nPickedFile, "Comparing nPickedFile");
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD87E20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_AllocDrlgMap, dll_base + 0x00047E20);

		SUBCASE("")
		{
			for (auto i = 0; i < lvlprest_record_count; ++i)
			{
				// Input data
				const auto seed = random_unsigned_integer();
				const auto x = random_unsigned_integer(0, 200);
				const auto y = random_unsigned_integer(0, 200);
				const auto width = random_unsigned_integer(1, 64);
				const auto height = random_unsigned_integer(1, 64);

				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgStrc moo_pDrlg{};
				D2DrlgMapStrc moo_pCurrentMap{};
				D2DrlgCoordStrc moo_pDrlgCoord{};
				D2SeedStrc moo_pSeed{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgStrc original_pDrlg{};
				D2DrlgMapStrc original_pCurrentMap{};
				D2DrlgCoordStrc original_pDrlgCoord{};
				D2SeedStrc original_pSeed{};
				int nLvlPrestId = i;

				const auto setup_data = [seed, x, y, width, height](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgMapStrc& pCurrentMap,
					D2DrlgCoordStrc& pDrlgCoord,
					D2SeedStrc& pSeed
				) {
					pLevel.pDrlg = &pDrlg;
					pLevel.pCurrentMap = &pCurrentMap;

					pDrlgCoord.nPosX = x;
					pDrlgCoord.nPosY = y;
					pDrlgCoord.nWidth = width;
					pDrlgCoord.nHeight = height;

					pSeed.nLowSeed = seed;
					pSeed.nHighSeed = 666;
				};

				setup_data(moo_pLevel, moo_pDrlg, moo_pCurrentMap, moo_pDrlgCoord, moo_pSeed);
				setup_data(original_pLevel, original_pDrlg, original_pCurrentMap, original_pDrlgCoord, original_pSeed);

				// Call both implementations
				const auto moo_result = sut(&moo_pLevel, nLvlPrestId, &moo_pDrlgCoord, &moo_pSeed);
				const auto original_result = original(&original_pLevel, nLvlPrestId, &original_pDrlgCoord, &original_pSeed);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
				MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");

				// Check specific values
				CHECK_EQ(moo_pLevel.pCurrentMap, moo_result);
				CHECK_EQ(moo_result->pNext, &moo_pCurrentMap);

				// Clean up
				D2_FREE_POOL(nullptr, moo_result);
				D2_FREE_POOL(nullptr, original_result);
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD87F00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetSizeX, dll_base + 0x00047F00);

		SUBCASE("")
		{
			for (auto i = 0; i < lvlprest_record_count; ++i)
			{
				int nLvlPrestId = i;

				// Call both implementations
				const auto moo_result = sut(nLvlPrestId);
				const auto original_result = original(nLvlPrestId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD87F10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetSizeY, dll_base + 0x00047F10);

		SUBCASE("")
		{
			for (auto i = 0; i < lvlprest_record_count; ++i)
			{
				int nLvlPrestId = i;

				// Call both implementations
				const auto moo_result = sut(nLvlPrestId);
				const auto original_result = original(nLvlPrestId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87F20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreeDrlgMap, dll_base + 0x00047F20);

		SUBCASE("")
		{
			// Input data
			D2DrlgMapStrc* moo_pDrlgMap{};
			D2DrlgMapStrc* original_pDrlgMap{};

			// A list of two maps, the first one with preset units and pops
			const auto setup_data = [](
				D2DrlgMapStrc*& pDrlgMap
			) {
				D2DrlgMapStrc* pNextDrlgMap = D2_CALLOC_STRC_POOL(nullptr, D2DrlgMapStrc);
				DRLGGRID_InitializeGridCells(nullptr, &pNextDrlgMap->pMapGrid, 3, 3);

				pDrlgMap = D2_CALLOC_STRC_POOL(nullptr, D2DrlgMapStrc);
				pDrlgMap->pNext = pNextDrlgMap;

				D2PresetUnitStrc* pPresetUnit = D2_CALLOC_STRC_POOL(nullptr, D2PresetUnitStrc);
				pPresetUnit->nUnitType = UNIT_MONSTER;
				pPresetUnit->pMapAI = D2_CALLOC_STRC_POOL(nullptr, D2MapAIStrc);
				pPresetUnit->pMapAI->nPathNodes = 1;
				pPresetUnit->pMapAI->pPosition = D2_CALLOC_STRC_POOL(nullptr, D2MapAIPathPositionStrc);
				pPresetUnit->pNext = D2_CALLOC_STRC_POOL(nullptr, D2PresetUnitStrc);
				pDrlgMap->pPresetUnit = pPresetUnit;

				pDrlgMap->nPops = 2;
				pDrlgMap->pPopsIndex = (int32_t*)D2_CALLOC_POOL(nullptr, sizeof(int32_t) * 2);
				pDrlgMap->pPopsSubIndex = (int32_t*)D2_CALLOC_POOL(nullptr, sizeof(int32_t) * 2);
				pDrlgMap->pPopsOrientation = (int32_t*)D2_CALLOC_POOL(nullptr, sizeof(int32_t) * 2);
				pDrlgMap->pPopsLocation = (D2DrlgCoordStrc*)D2_CALLOC_POOL(nullptr, sizeof(D2DrlgCoordStrc) * 2);
			};

			setup_data(moo_pDrlgMap);
			setup_data(original_pDrlgMap);

			// Call both implementations
			sut(nullptr, moo_pDrlgMap);
			original(nullptr, original_pDrlgMap);

			// Input data can not be compared since it was freed
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD881A0 (#10008)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetLevelPrestIdFromRoomEx, dll_base + 0x000481A0);

		SUBCASE("")
		{
			// Input data
			const auto level_prest = random_unsigned_integer(0, 1000);

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgPresetRoomStrc moo_pMaze{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgPresetRoomStrc original_pMaze{};

			const auto setup_data = [level_prest](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgPresetRoomStrc& pMaze
			) {
				pMaze.nLevelPrest = level_prest;

				pDrlgRoom.nType = DRLGTYPE_PRESET;
				pDrlgRoom.pMaze = &pMaze;
			};

			setup_data(moo_pDrlgRoom, moo_pMaze);
			setup_data(original_pDrlgRoom, original_pMaze);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD881B0 (#10009)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetPickedLevelPrestFilePathFromRoomEx, dll_base + 0x000481B0);

		SUBCASE("")
		{
			for (auto i = 0; i < 6; ++i)
			{
				// Input data
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgPresetRoomStrc moo_pMaze{};
				D2DrlgMapStrc moo_pDrlgMap{};
				D2LvlPrestTxt moo_pLvlPrestTxtRecord{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgPresetRoomStrc original_pMaze{};
				D2DrlgMapStrc original_pDrlgMap{};
				D2LvlPrestTxt original_pLvlPrestTxtRecord{};
				const auto picked_file = i;

				const auto setup_data = [picked_file](
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgPresetRoomStrc& pMaze,
					D2DrlgMapStrc& pDrlgMap,
					D2LvlPrestTxt& pLvlPrestTxtRecord
				) {
					for (auto j = 0; j < 6; ++j)
					{
						sprintf_s(pLvlPrestTxtRecord.szFile[j], "DATA\\GLOBAL\\TILES\\ACT1\\TOWN\\town%d.ds1", j);
					}

					pDrlgMap.nPickedFile = picked_file;
					pDrlgMap.pLvlPrestTxtRecord = &pLvlPrestTxtRecord;

					pMaze.pMap = &pDrlgMap;

					pDrlgRoom.nType = DRLGTYPE_PRESET;
					pDrlgRoom.pMaze = &pMaze;
				};

				setup_data(moo_pDrlgRoom, moo_pMaze, moo_pDrlgMap, moo_pLvlPrestTxtRecord);
				setup_data(original_pDrlgRoom, original_pMaze, original_pDrlgMap, original_pLvlPrestTxtRecord);

				// Call both implementations
				const auto moo_result = sut(&moo_pDrlgRoom);
				const auto original_result = original(&original_pDrlgRoom);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				CHECK_EQ(std::string(moo_result), std::string(original_result));

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD881D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_UpdatePops, dll_base + 0x000481D0);

		// Room 0 is the room the position belongs to, it uses map 0 with the pops 0 and 1.
		// Room 1 is an adjacent room, it uses map 1 with pop 2.
		const auto setup_data = [](
			D2DrlgRoomStrc(&pDrlgRooms)[2],
			D2DrlgRoomStrc*(&ppRoomsNear)[2],
			D2DrlgPresetRoomStrc(&pMazes)[2],
			D2DrlgMapStrc(&pDrlgMaps)[2],
			D2LvlPrestTxt& pLvlPrestTxtRecord,
			int(&pPopsIndex)[3],
			int(&pPopsSubIndex)[3],
			int(&pPopsOrientation)[3],
			D2DrlgCoordStrc(&pPopsLocation)[3],
			D2ActiveRoomStrc& pRoom,
			D2DrlgTileGridStrc(&pTileGrids)[2],
			D2DrlgTileDataStrc(&pWallTiles)[3],
			D2TileLibraryEntryStrc& pTile
		) {
			pLvlPrestTxtRecord.dwPopPad = 2;

			const int pops[3][7] =
			{
				// nIndex, nSubIndex, nOrientation, nPosX, nPosY, nWidth, nHeight
				{ 1, 10, 0, 2, 2, 2, 2 },
				{ 2, 11, 0, 6, 2, 1, 3 },
				{ 1, 10, 1234, 2, 2, 2, 2 },
			};

			for (auto i = 0; i < 3; ++i)
			{
				pPopsIndex[i] = pops[i][0];
				pPopsSubIndex[i] = pops[i][1];
				pPopsOrientation[i] = pops[i][2];
				pPopsLocation[i].nPosX = pops[i][3];
				pPopsLocation[i].nPosY = pops[i][4];
				pPopsLocation[i].nWidth = pops[i][5];
				pPopsLocation[i].nHeight = pops[i][6];
			}

			pDrlgMaps[0].pLvlPrestTxtRecord = &pLvlPrestTxtRecord;
			pDrlgMaps[0].nPops = 2;
			pDrlgMaps[0].pPopsIndex = &pPopsIndex[0];
			pDrlgMaps[0].pPopsSubIndex = &pPopsSubIndex[0];
			pDrlgMaps[0].pPopsOrientation = &pPopsOrientation[0];
			pDrlgMaps[0].pPopsLocation = &pPopsLocation[0];
			pDrlgMaps[1].pLvlPrestTxtRecord = &pLvlPrestTxtRecord;
			pDrlgMaps[1].nPops = 1;
			pDrlgMaps[1].pPopsIndex = &pPopsIndex[2];
			pDrlgMaps[1].pPopsSubIndex = &pPopsSubIndex[2];
			pDrlgMaps[1].pPopsOrientation = &pPopsOrientation[2];
			pDrlgMaps[1].pPopsLocation = &pPopsLocation[2];

			// Wall tiles of room 0, room 1 doesn't have any
			pTile.nStyle = 10;

			pWallTiles[0].nPosX = 1;
			pWallTiles[0].nPosY = 1;
			pWallTiles[0].dwFlags = 0x200 | 0x8;
			pWallTiles[0].unk0x24 = 4 | 1;
			pWallTiles[1].nPosX = 2;
			pWallTiles[1].nPosY = 2;
			pWallTiles[1].pTile = &pTile;
			pWallTiles[1].nRed = 128;
			pWallTiles[2].nPosX = 3;
			pWallTiles[2].nPosY = 3;
			pWallTiles[2].dwFlags = 0x100;

			pTileGrids[0].pTiles.pWallTiles = pWallTiles;
			pTileGrids[0].pTiles.nWalls = 3;

			for (auto i = 0; i < 2; ++i)
			{
				pMazes[i].pMap = &pDrlgMaps[i];

				pDrlgRooms[i].nType = DRLGTYPE_PRESET;
				pDrlgRooms[i].pMaze = &pMazes[i];
				pDrlgRooms[i].pRoom = &pRoom;
				pDrlgRooms[i].pTileGrid = &pTileGrids[i];

				ppRoomsNear[i] = &pDrlgRooms[i];
			}

			pDrlgRooms[0].ppRoomsNear = ppRoomsNear;
			pDrlgRooms[0].nRoomsNear = 2;
		};

		SUBCASE("Position outside of pops")
		{
			for (auto bOtherRoomValue : { FALSE, TRUE })
			{
				// Input data
				D2DrlgRoomStrc moo_pDrlgRooms[2]{};
				D2DrlgRoomStrc* moo_ppRoomsNear[2]{};
				D2DrlgPresetRoomStrc moo_pMazes[2]{};
				D2DrlgMapStrc moo_pDrlgMaps[2]{};
				D2LvlPrestTxt moo_pLvlPrestTxtRecord{};
				int moo_pPopsIndex[3]{};
				int moo_pPopsSubIndex[3]{};
				int moo_pPopsOrientation[3]{};
				D2DrlgCoordStrc moo_pPopsLocation[3]{};
				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgTileGridStrc moo_pTileGrids[2]{};
				D2DrlgTileDataStrc moo_pWallTiles[3]{};
				D2TileLibraryEntryStrc moo_pTile{};
				D2DrlgRoomStrc original_pDrlgRooms[2]{};
				D2DrlgRoomStrc* original_ppRoomsNear[2]{};
				D2DrlgPresetRoomStrc original_pMazes[2]{};
				D2DrlgMapStrc original_pDrlgMaps[2]{};
				D2LvlPrestTxt original_pLvlPrestTxtRecord{};
				int original_pPopsIndex[3]{};
				int original_pPopsSubIndex[3]{};
				int original_pPopsOrientation[3]{};
				D2DrlgCoordStrc original_pPopsLocation[3]{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgTileGridStrc original_pTileGrids[2]{};
				D2DrlgTileDataStrc original_pWallTiles[3]{};
				D2TileLibraryEntryStrc original_pTile{};
				int nX = 0;
				int nY = 0;
				BOOL bOtherRoom = bOtherRoomValue;

				setup_data(moo_pDrlgRooms, moo_ppRoomsNear, moo_pMazes, moo_pDrlgMaps, moo_pLvlPrestTxtRecord, moo_pPopsIndex, moo_pPopsSubIndex, moo_pPopsOrientation, moo_pPopsLocation, moo_pRoom, moo_pTileGrids, moo_pWallTiles, moo_pTile);
				setup_data(original_pDrlgRooms, original_ppRoomsNear, original_pMazes, original_pDrlgMaps, original_pLvlPrestTxtRecord, original_pPopsIndex, original_pPopsSubIndex, original_pPopsOrientation, original_pPopsLocation, original_pRoom, original_pTileGrids, original_pWallTiles, original_pTile);

				// Call both implementations
				sut(&moo_pDrlgRooms[0], nX, nY, bOtherRoom);
				original(&original_pDrlgRooms[0], nX, nY, bOtherRoom);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlgRooms[0], original_pDrlgRooms[0], "Comparing pDrlgRoom");
				MOO_CHECK_EQ(moo_pDrlgRooms[1], original_pDrlgRooms[1], "Comparing adjacent pDrlgRoom");
				auto moo_pops_orientation = DynamicArray<int>{ moo_pPopsOrientation, 3 };
				auto original_pops_orientation = DynamicArray<int>{ original_pPopsOrientation, 3 };
				MOO_CHECK_EQ(moo_pops_orientation, original_pops_orientation, "Comparing pPopsOrientation");
				auto moo_wall_tiles = DynamicArray<D2DrlgTileDataStrc>{ moo_pWallTiles, 3 };
				auto original_wall_tiles = DynamicArray<D2DrlgTileDataStrc>{ original_pWallTiles, 3 };
				MOO_CHECK_EQ(moo_wall_tiles, original_wall_tiles, "Comparing pWallTiles");
			}
		}

		// NOTE: We're checking successful repetitions here, because a single run could fail due to the function calling GetTickCount()
		SUBCASE("Position inside of pop")
		{
			for (auto bOtherRoomValue : { FALSE, TRUE })
			{
				const auto repetitions = 100;
				auto success_count = 0;

				for (auto i = 0; i < repetitions; ++i)
				{
					// Input data
					D2DrlgRoomStrc moo_pDrlgRooms[2]{};
					D2DrlgRoomStrc* moo_ppRoomsNear[2]{};
					D2DrlgPresetRoomStrc moo_pMazes[2]{};
					D2DrlgMapStrc moo_pDrlgMaps[2]{};
					D2LvlPrestTxt moo_pLvlPrestTxtRecord{};
					int moo_pPopsIndex[3]{};
					int moo_pPopsSubIndex[3]{};
					int moo_pPopsOrientation[3]{};
					D2DrlgCoordStrc moo_pPopsLocation[3]{};
					D2ActiveRoomStrc moo_pRoom{};
					D2DrlgTileGridStrc moo_pTileGrids[2]{};
					D2DrlgTileDataStrc moo_pWallTiles[3]{};
					D2TileLibraryEntryStrc moo_pTile{};
					D2DrlgRoomStrc original_pDrlgRooms[2]{};
					D2DrlgRoomStrc* original_ppRoomsNear[2]{};
					D2DrlgPresetRoomStrc original_pMazes[2]{};
					D2DrlgMapStrc original_pDrlgMaps[2]{};
					D2LvlPrestTxt original_pLvlPrestTxtRecord{};
					int original_pPopsIndex[3]{};
					int original_pPopsSubIndex[3]{};
					int original_pPopsOrientation[3]{};
					D2DrlgCoordStrc original_pPopsLocation[3]{};
					D2ActiveRoomStrc original_pRoom{};
					D2DrlgTileGridStrc original_pTileGrids[2]{};
					D2DrlgTileDataStrc original_pWallTiles[3]{};
					D2TileLibraryEntryStrc original_pTile{};
					int nX = 12;
					int nY = 12;
					BOOL bOtherRoom = bOtherRoomValue;

					setup_data(moo_pDrlgRooms, moo_ppRoomsNear, moo_pMazes, moo_pDrlgMaps, moo_pLvlPrestTxtRecord, moo_pPopsIndex, moo_pPopsSubIndex, moo_pPopsOrientation, moo_pPopsLocation, moo_pRoom, moo_pTileGrids, moo_pWallTiles, moo_pTile);
					setup_data(original_pDrlgRooms, original_ppRoomsNear, original_pMazes, original_pDrlgMaps, original_pLvlPrestTxtRecord, original_pPopsIndex, original_pPopsSubIndex, original_pPopsOrientation, original_pPopsLocation, original_pRoom, original_pTileGrids, original_pWallTiles, original_pTile);

					// Call both implementations
					sut(&moo_pDrlgRooms[0], nX, nY, bOtherRoom);
					original(&original_pDrlgRooms[0], nX, nY, bOtherRoom);

					// Compare potentially modified input data
					std::string diff_description;
					auto moo_pops_orientation = DynamicArray<int>{ moo_pPopsOrientation, 3 };
					auto original_pops_orientation = DynamicArray<int>{ original_pPopsOrientation, 3 };
					const auto are_pops_orientations_equal = moo_check_eq(moo_pops_orientation, original_pops_orientation, "Comparing pPopsOrientation", diff_description);
					auto moo_wall_tiles = DynamicArray<D2DrlgTileDataStrc>{ moo_pWallTiles, 3 };
					auto original_wall_tiles = DynamicArray<D2DrlgTileDataStrc>{ original_pWallTiles, 3 };
					const auto are_wall_tiles_equal = moo_check_eq(moo_wall_tiles, original_wall_tiles, "Comparing pWallTiles", diff_description);

					if (are_pops_orientations_equal && are_wall_tiles_equal)
					{
						++success_count;
					}
				}

				CHECK(success_count > 95 * repetitions / 100);
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88450")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_TogglePopsVisibility, dll_base + 0x00048450);

		SUBCASE("")
		{
			for (auto nCellFlagsValue : { FALSE, TRUE })
			{
				// Input data
				const auto x = random_unsigned_integer(0, 200);
				const auto y = random_unsigned_integer(0, 200);

				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgTileGridStrc moo_pTileGrid{};
				D2DrlgTileDataStrc moo_pWallTiles[6]{};
				D2TileLibraryEntryStrc moo_pTiles[2]{};
				D2DrlgCoordStrc moo_pDrlgCoord{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgTileGridStrc original_pTileGrid{};
				D2DrlgTileDataStrc original_pWallTiles[6]{};
				D2TileLibraryEntryStrc original_pTiles[2]{};
				D2DrlgCoordStrc original_pDrlgCoord{};
				int nPopSubIndex = 7;
				int nTick = random_unsigned_integer(1000, 1000000);
				BOOL nCellFlags = nCellFlagsValue;

				const auto setup_data = [x, y, nPopSubIndex](
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgTileGridStrc& pTileGrid,
					D2DrlgTileDataStrc(&pWallTiles)[6],
					D2TileLibraryEntryStrc(&pTiles)[2],
					D2DrlgCoordStrc& pDrlgCoord
				) {
					pTiles[0].nStyle = nPopSubIndex;
					pTiles[1].nStyle = nPopSubIndex + 1;

					const int tiles[6][5] =
					{
						// nPosX, nPosY, dwFlags, nTile, nRed
						{ 2, 3, 0x200 | 0x8, -1, 0 },	// Pop tile inside of the area
						{ 7, 7, 0x200, 1, 0 },			// Pop tile outside of the area, its style gets checked
						{ 3, 3, 0, 0, 0 },				// Tile with matching style inside of the area
						{ 4, 4, 0, 0, 128 },			// Tile with matching style inside of the area
						{ 4, 5, 0x100, 0, 255 },		// Ignored tile
						{ 5, 4, 0, 1, 64 },				// Tile with other style
					};

					for (auto i = 0; i < 6; ++i)
					{
						pWallTiles[i].nPosX = tiles[i][0];
						pWallTiles[i].nPosY = tiles[i][1];
						pWallTiles[i].dwFlags = tiles[i][2];
						pWallTiles[i].pTile = tiles[i][3] >= 0 ? &pTiles[tiles[i][3]] : nullptr;
						pWallTiles[i].nRed = tiles[i][4];
						pWallTiles[i].nGreen = 100;
						pWallTiles[i].nBlue = 100;
						pWallTiles[i].unk0x24 = 5;
					}

					pTileGrid.pTiles.pWallTiles = pWallTiles;
					pTileGrid.pTiles.nWalls = 6;

					pDrlgRoom.pTileGrid = &pTileGrid;
					pDrlgRoom.nTileXPos = x;
					pDrlgRoom.nTileYPos = y;
					pDrlgRoom.nTileWidth = 8;
					pDrlgRoom.nTileHeight = 8;

					pDrlgCoord.nPosX = x + 3;
					pDrlgCoord.nPosY = y + 4;
					pDrlgCoord.nWidth = 2;
					pDrlgCoord.nHeight = 1;
				};

				setup_data(moo_pDrlgRoom, moo_pTileGrid, moo_pWallTiles, moo_pTiles, moo_pDrlgCoord);
				setup_data(original_pDrlgRoom, original_pTileGrid, original_pWallTiles, original_pTiles, original_pDrlgCoord);

				// Call both implementations
				sut(&moo_pDrlgRoom, nPopSubIndex, &moo_pDrlgCoord, nTick, nCellFlags);
				original(&original_pDrlgRoom, nPopSubIndex, &original_pDrlgCoord, nTick, nCellFlags);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
				MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
				auto moo_wall_tiles = DynamicArray<D2DrlgTileDataStrc>{ moo_pWallTiles, 6 };
				auto original_wall_tiles = DynamicArray<D2DrlgTileDataStrc>{ original_pWallTiles, 6 };
				MOO_CHECK_EQ(moo_wall_tiles, original_wall_tiles, "Comparing pWallTiles");
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>>, "D2Common.0x6FD88610")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_InitLevelData, dll_base + 0x00048610);

		SUBCASE("")
		{
			const auto pLevelDefs = leveldefs_txt.get();

			for (auto i = 0; i < lvlprest_record_count; ++i)
			{
				const auto level_id = (int)lvlprest_txt[i].dwLevelId;
				if (level_id <= 0 || level_id >= levels_record_count)
				{
					continue;
				}

				// Input data
				const auto seed = random_unsigned_integer();
				const auto difficulty = random_unsigned_integer(0, 2);
				const auto depend_level_id = pLevelDefs[level_id].dwDepend;
				const auto depend_x = random_unsigned_integer(0, 200);
				const auto depend_y = random_unsigned_integer(0, 200);

				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgStrc moo_pDrlg{};
				D2DrlgLevelStrc moo_pDependLevel{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgStrc original_pDrlg{};
				D2DrlgLevelStrc original_pDependLevel{};

				const auto setup_data = [level_id, seed, difficulty, depend_level_id, depend_x, depend_y](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgLevelStrc& pDependLevel
				) {
					// The level the position depends on is already part of the drlg
					if (depend_level_id)
					{
						pDependLevel.pDrlg = &pDrlg;
						pDependLevel.nLevelId = depend_level_id;
						pDependLevel.nPosX = depend_x;
						pDependLevel.nPosY = depend_y;

						pDrlg.pLevel = &pDependLevel;
					}

					pDrlg.nDifficulty = difficulty;

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = level_id;
					pLevel.nDrlgType = DRLGTYPE_PRESET;
					pLevel.pSeed.nLowSeed = seed;
					pLevel.pSeed.nHighSeed = 666;
				};

				setup_data(moo_pLevel, moo_pDrlg, moo_pDependLevel);
				setup_data(original_pLevel, original_pDrlg, original_pDependLevel);

				// Call both implementations
				sut(&moo_pLevel);
				original(&original_pLevel);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				MOO_CHECK_EQ(moo_pLevel.pPreset, original_pLevel.pPreset, "Comparing pPreset");
				MOO_CHECK_EQ(moo_pLevel.pSeed, original_pLevel.pSeed, "Comparing pSeed");
				MOO_CHECK_EQ(moo_pLevel.pLevelCoords, original_pLevel.pLevelCoords, "Comparing pLevelCoords");

				// Clean up
				D2_FREE_POOL(nullptr, moo_pLevel.pPreset);
				D2_FREE_POOL(nullptr, original_pLevel.pPreset);
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD886F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GenerateLevel, dll_base + 0x000486F0);

		int nDirection = 0;

		SUBCASE("Random direction")
		{
			nDirection = -1;
		}

		SUBCASE("Fixed direction")
		{
			nDirection = 0;
		}

		// Loading the DS1 files would require the archives, so scan and pops are disabled for all presets
		for (auto i = 0; i < lvlprest_record_count; ++i)
		{
			lvlprest_txt[i].dwScan = 0;
			lvlprest_txt[i].dwPops = 0;
		}

		for (auto i = 0; i < lvlprest_record_count; ++i)
		{
			const auto level_id = (int)lvlprest_txt[i].dwLevelId;

			// Only the first preset of a level is used by the function
			auto is_first_preset_of_level = level_id != 0;
			for (auto j = 0; j < i && is_first_preset_of_level; ++j)
			{
				is_first_preset_of_level = (int)lvlprest_txt[j].dwLevelId != level_id;
			}

			if (!is_first_preset_of_level)
			{
				continue;
			}

			// Input data
			const auto seed = random_unsigned_integer();
			const auto x = random_unsigned_integer(0, 200);
			const auto y = random_unsigned_integer(0, 200);

			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pDrlgWarp{};
			D2DrlgPresetInfoStrc moo_pPreset{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pDrlgWarp{};
			D2DrlgPresetInfoStrc original_pPreset{};

			const auto setup_data = [level_id, seed, x, y, nDirection](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pDrlgWarp,
				D2DrlgPresetInfoStrc& pPreset
			) {
				// Vis and warp arrays come from the warp list instead of LevelDefs.txt
				pDrlgWarp.nLevel = level_id;
				for (auto j = 0; j < 8; ++j)
				{
					pDrlgWarp.nVis[j] = j % 3 ? level_id + 1 : 0;
					pDrlgWarp.nWarp[j] = j % 2 ? -1 : j;
				}

				// No automap callbacks, so no other levels have to be initialized
				pDrlg.pWarp = &pDrlgWarp;

				pPreset.nDirection = nDirection;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nDrlgType = DRLGTYPE_PRESET;
				pLevel.pSeed.nLowSeed = seed;
				pLevel.pSeed.nHighSeed = 666;
				pLevel.nPosX = x;
				pLevel.nPosY = y;
				pLevel.nWidth = 16;
				pLevel.nHeight = 16;
				pLevel.pPreset = &pPreset;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pDrlgWarp, moo_pPreset);
			setup_data(original_pLevel, original_pDrlg, original_pDrlgWarp, original_pPreset);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ(moo_pPreset, original_pPreset, "Comparing pPreset");
			MOO_CHECK_EQ(moo_pPreset.nDirection, original_pPreset.nDirection, "Comparing nDirection");
			MOO_CHECK_EQ(moo_pPreset.pDrlgMap, original_pPreset.pDrlgMap, "Comparing pDrlgMap");
			MOO_CHECK_EQ(moo_pLevel.pSeed, original_pLevel.pSeed, "Comparing pSeed");
			MOO_CHECK_EQ(moo_pLevel.nRooms, original_pLevel.nRooms, "Comparing nRooms");

			// Clean up
			free_preset_rooms(moo_pLevel);
			free_preset_rooms(original_pLevel);
			D2_FREE_POOL(nullptr, moo_pPreset.pDrlgMap);
			D2_FREE_POOL(nullptr, original_pPreset.pDrlgMap);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88810")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_ResetDrlgMap, dll_base + 0x00048810);

		SUBCASE("Keep preset")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgPresetInfoStrc moo_pPreset{};
			D2DrlgMapStrc moo_pDrlgMap{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgPresetInfoStrc original_pPreset{};
			D2DrlgMapStrc original_pDrlgMap{};
			BOOL bKeepPreset = TRUE;

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgPresetInfoStrc& pPreset,
				D2DrlgMapStrc& pDrlgMap
			) {
				pPreset.pDrlgMap = &pDrlgMap;
				pPreset.nDirection = 2;

				pLevel.pDrlg = &pDrlg;
				pLevel.pPreset = &pPreset;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pPreset, moo_pDrlgMap);
			setup_data(original_pLevel, original_pDrlg, original_pPreset, original_pDrlgMap);

			// Call both implementations
			sut(&moo_pLevel, bKeepPreset);
			original(&original_pLevel, bKeepPreset);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ(moo_pPreset, original_pPreset, "Comparing pPreset");

			// Check specific values
			CHECK_EQ(moo_pLevel.pPreset, &moo_pPreset);
			CHECK_EQ(moo_pPreset.pDrlgMap, nullptr);
			CHECK_EQ(original_pPreset.pDrlgMap, nullptr);
		}

		SUBCASE("Free preset")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgMapStrc moo_pDrlgMap{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgMapStrc original_pDrlgMap{};
			BOOL bKeepPreset = FALSE;

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgMapStrc& pDrlgMap
			) {
				pLevel.pDrlg = &pDrlg;
				pLevel.pPreset = D2_CALLOC_STRC_POOL(nullptr, D2DrlgPresetInfoStrc);
				pLevel.pPreset->pDrlgMap = &pDrlgMap;
				pLevel.pPreset->nDirection = 2;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pDrlgMap);
			setup_data(original_pLevel, original_pDrlg, original_pDrlgMap);

			// Call both implementations
			sut(&moo_pLevel, bKeepPreset);
			original(&original_pLevel, bKeepPreset);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");

			// Check specific values
			CHECK_EQ(moo_pLevel.pPreset, nullptr);
			CHECK_EQ(original_pLevel.pPreset, nullptr);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88850")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_MapTileType, dll_base + 0x00048850);

		SUBCASE("")
		{
			for (auto i = 0; i < 42; ++i)
			{
				int nId = i;

				// Call both implementations
				const auto moo_result = sut(nId);
				const auto original_result = original(nId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
}
