#include <D2CommonTestDefines.h>

#ifdef DRLG_ROOMTILE_TESTS

#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <array>
#include <cstdarg>
#include <filesystem>
#include <iterator>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2CMP.h>
#include <Fog.h>
#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgRoomTile.h>

#include <Fixtures/DataTbls/Fixtures.h>

// TODO: This has to be defined correctly
BEGIN_VISIT(D2TileLibraryEntryStrc)
END_VISIT()


TEST_SUITE("D2DrlgRoomTileTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88860")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_GetTileCache, dll_base + 0x00048860);

		const auto tile_exists = GENERATE(0, 1);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();
			const auto tile_type = random_unsigned_integer(TILETYPE_FLOOR, TILETYPE_FRONT_WALL_DOWN);
			const auto tile_style = random_unsigned_integer(1, 62);
			const auto tile_sequence = random_unsigned_integer(0, 255);
			const auto rarity1 = random_unsigned_integer(0, 10);
			const auto rarity2 = random_unsigned_integer(0, 10);

			D2C_PackedTileInformation nTileInformation{};
			nTileInformation.nTileStyle = tile_style;
			nTileInformation.nTileSequence = tile_sequence;

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2TileLibraryHashStrc moo_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc moo_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc moo_pTileLibraryHashRefs[2]{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntries[2]{};
			D2TileLibraryHashNodeStrc moo_pFallbackTileLibraryHashNode{};
			D2TileLibraryHashRefStrc moo_pFallbackTileLibraryHashRef{};
			D2TileLibraryEntryStrc moo_pFallbackTileLibraryEntry{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2TileLibraryHashStrc original_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc original_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc original_pTileLibraryHashRefs[2]{};
			D2TileLibraryEntryStrc original_pTileLibraryEntries[2]{};
			D2TileLibraryHashNodeStrc original_pFallbackTileLibraryHashNode{};
			D2TileLibraryHashRefStrc original_pFallbackTileLibraryHashRef{};
			D2TileLibraryEntryStrc original_pFallbackTileLibraryEntry{};
			int nType = tile_type;
			uint32_t nPackedTileInformation = nTileInformation.nPackedValue;

			const auto setup_data = [tile_exists, low_seed, high_seed, tile_type, tile_style, tile_sequence, rarity1, rarity2](
				D2DrlgRoomStrc& pDrlgRoom,
				D2TileLibraryHashStrc& pTileLibraryHash,
				D2TileLibraryHashNodeStrc& pTileLibraryHashNode,
				D2TileLibraryHashRefStrc (&pTileLibraryHashRefs)[2],
				D2TileLibraryEntryStrc (&pTileLibraryEntries)[2],
				D2TileLibraryHashNodeStrc& pFallbackTileLibraryHashNode,
				D2TileLibraryHashRefStrc& pFallbackTileLibraryHashRef,
				D2TileLibraryEntryStrc& pFallbackTileLibraryEntry
			) {
				// The node either matches the requested tile or not, in which case the fallback tile is used
				const int node_style = tile_exists ? tile_style : tile_style + 1;
				const int rarities[2] = { (int)rarity1, (int)rarity2 };

				for (int i = 0; i < 2; ++i)
				{
					pTileLibraryEntries[i].nLightDirection = i;
					pTileLibraryEntries[i].nType = tile_type;
					pTileLibraryEntries[i].nStyle = node_style;
					pTileLibraryEntries[i].nSequence = tile_sequence;
					pTileLibraryEntries[i].nRarity_Frame = rarities[i];

					pTileLibraryHashRefs[i].pTile = &pTileLibraryEntries[i];
				}
				pTileLibraryHashRefs[0].pPrev = &pTileLibraryHashRefs[1];

				pFallbackTileLibraryEntry.nLightDirection = 2;
				pFallbackTileLibraryEntry.nType = TILETYPE_WALL_LEFT_EXIT;
				pFallbackTileLibraryEntry.nRarity_Frame = 1;
				pFallbackTileLibraryHashRef.pTile = &pFallbackTileLibraryEntry;

				pFallbackTileLibraryHashNode.nType = TILETYPE_WALL_LEFT_EXIT;
				pFallbackTileLibraryHashNode.pRef = &pFallbackTileLibraryHashRef;

				pTileLibraryHashNode.nType = tile_type;
				pTileLibraryHashNode.nStyle = node_style;
				pTileLibraryHashNode.nSequence = tile_sequence;
				pTileLibraryHashNode.pRef = &pTileLibraryHashRefs[0];
				pTileLibraryHashNode.pPrev = &pFallbackTileLibraryHashNode;

				// Every bucket contains the node chain, so the lookup does not depend on the hash function of D2CMP
				std::fill(std::begin(pTileLibraryHash.pNodes), std::end(pTileLibraryHash.pNodes), &pTileLibraryHashNode);

				pDrlgRoom.pTiles[0] = &pTileLibraryHash;
				pDrlgRoom.pSeed.nLowSeed = low_seed;
				pDrlgRoom.pSeed.nHighSeed = high_seed;
			};

			setup_data(moo_pDrlgRoom, moo_pTileLibraryHash, moo_pTileLibraryHashNode, moo_pTileLibraryHashRefs, moo_pTileLibraryEntries, moo_pFallbackTileLibraryHashNode, moo_pFallbackTileLibraryHashRef, moo_pFallbackTileLibraryEntry);
			setup_data(original_pDrlgRoom, original_pTileLibraryHash, original_pTileLibraryHashNode, original_pTileLibraryHashRefs, original_pTileLibraryEntries, original_pFallbackTileLibraryHashNode, original_pFallbackTileLibraryHashRef, original_pFallbackTileLibraryEntry);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nType, nPackedTileInformation);
			const auto original_result = original(&original_pDrlgRoom, nType, nPackedTileInformation);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// D2TileLibraryEntryStrc has no fields to compare yet, so compare which of the entries was selected
			int moo_result_index = moo_result ? moo_result->nLightDirection : -1;
			int original_result_index = original_result ? original_result->nLightDirection : -1;
			MOO_CHECK_EQ(moo_result_index, original_result_index, "Comparing selected tile");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD889C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_InitWallTileData, dll_base + 0x000489C0);

		// Doors are excluded, as they would add preset units
		const auto tile_type = GENERATE(
			TILETYPE_WALL_LEFT, TILETYPE_WALL_RIGHT, TILETYPE_WALL_TOP_CORNER_RIGHT, TILETYPE_WALL_TOP_CORNER_LEFT,
			TILETYPE_WALL_TOP_RIGHT, TILETYPE_WALL_BOTTOM_LEFT, TILETYPE_WALL_BOTTOM_RIGHT, TILETYPE_WALL_LEFT_EXIT,
			TILETYPE_WALL_RIGHT_EXIT, TILETYPE_COLUMN, TILETYPE_TREE, TILETYPE_ROOF
		);

		REPEAT_5();

		SUBCASE("")
		{
			// Input data
			const auto room_x = random_unsigned_integer(0, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);
			const auto previous_tile_flags = random_unsigned_integer();

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pWallTiles[2]{};
			D2DrlgTileDataStrc moo_pPreviousTileData{};
			D2DrlgTileDataStrc* moo_ppTileData{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2TileLibraryHashStrc moo_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc moo_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc moo_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc moo_pCachedTileLibraryEntry{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pWallTiles[2]{};
			D2DrlgTileDataStrc original_pPreviousTileData{};
			D2DrlgTileDataStrc* original_ppTileData{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			D2TileLibraryHashStrc original_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc original_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc original_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc original_pCachedTileLibraryEntry{};
			int nX = room_x + random_unsigned_integer(0, 8);
			int nY = room_y + random_unsigned_integer(0, 8);
			uint32_t nPackedTileInformation = random_unsigned_integer();
			int nTileType = tile_type;

			const auto setup_data = [room_x, room_y, tile_flags, previous_tile_flags](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc (&pWallTiles)[2],
				D2DrlgTileDataStrc& pPreviousTileData,
				D2DrlgTileDataStrc*& ppTileData,
				D2TileLibraryEntryStrc& pTileLibraryEntry,
				D2TileLibraryHashStrc& pTileLibraryHash,
				D2TileLibraryHashNodeStrc& pTileLibraryHashNode,
				D2TileLibraryHashRefStrc& pTileLibraryHashRef,
				D2TileLibraryEntryStrc& pCachedTileLibraryEntry
			) {
				pTileLibraryEntry.nFlags = tile_flags;

				// Tile used for the additional TILETYPE_WALL_TOP_CORNER_LEFT wall (every lookup falls back to it)
				pCachedTileLibraryEntry.nType = TILETYPE_WALL_LEFT_EXIT;
				pCachedTileLibraryEntry.nRarity_Frame = 1;
				pCachedTileLibraryEntry.nFlags = tile_flags;
				pTileLibraryHashRef.pTile = &pCachedTileLibraryEntry;
				pTileLibraryHashNode.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryHashNode.pRef = &pTileLibraryHashRef;
				std::fill(std::begin(pTileLibraryHash.pNodes), std::end(pTileLibraryHash.pNodes), &pTileLibraryHashNode);

				pPreviousTileData.dwFlags = previous_tile_flags;
				ppTileData = &pPreviousTileData;

				pTileGrid.pTiles.pWallTiles = pWallTiles;
				pTileGrid.pTiles.nWalls = 2;

				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.pTileGrid = &pTileGrid;
				pDrlgRoom.pTiles[0] = &pTileLibraryHash;
			};

			setup_data(moo_pDrlgRoom, moo_pTileGrid, moo_pWallTiles, moo_pPreviousTileData, moo_ppTileData, moo_pTileLibraryEntry, moo_pTileLibraryHash, moo_pTileLibraryHashNode, moo_pTileLibraryHashRef, moo_pCachedTileLibraryEntry);
			setup_data(original_pDrlgRoom, original_pTileGrid, original_pWallTiles, original_pPreviousTileData, original_ppTileData, original_pTileLibraryEntry, original_pTileLibraryHash, original_pTileLibraryHashNode, original_pTileLibraryHashRef, original_pCachedTileLibraryEntry);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, &moo_ppTileData, nX, nY, nPackedTileInformation, &moo_pTileLibraryEntry, nTileType);
			const auto original_result = original(&original_pDrlgRoom, &original_ppTileData, nX, nY, nPackedTileInformation, &original_pTileLibraryEntry, nTileType);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_ppTileData, original_ppTileData, "Comparing ppTileData");
			MOO_CHECK_EQ(moo_pTileLibraryEntry, original_pTileLibraryEntry, "Comparing pTileLibraryEntry");
			MOO_CHECK_EQ(moo_pTileGrid.nWalls, original_pTileGrid.nWalls, "Comparing pTileGrid.nWalls");
			MOO_CHECK_EQ(moo_pWallTiles[0], original_pWallTiles[0], "Comparing pWallTiles[0]");
			MOO_CHECK_EQ(moo_pWallTiles[1], original_pWallTiles[1], "Comparing pWallTiles[1]");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88AC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_InitializeTileDataFlags, dll_base + 0x00048AC0);

		const auto tile_type = GENERATE(
			TILETYPE_FLOOR, TILETYPE_WALL_LEFT, TILETYPE_WALL_RIGHT, TILETYPE_WALL_TOP_CORNER_RIGHT, TILETYPE_WALL_TOP_CORNER_LEFT,
			TILETYPE_WALL_TOP_RIGHT, TILETYPE_WALL_BOTTOM_LEFT, TILETYPE_WALL_BOTTOM_RIGHT, TILETYPE_WALL_LEFT_DOOR,
			TILETYPE_WALL_RIGHT_DOOR, TILETYPE_WALL_LEFT_EXIT, TILETYPE_WALL_RIGHT_EXIT, TILETYPE_COLUMN, TILETYPE_SHADOW,
			TILETYPE_TREE, TILETYPE_ROOF, TILETYPE_LEFT_WALL_DOWN, TILETYPE_RIGHT_WALL_DOWN, TILETYPE_FULL_WALL_DOWN, TILETYPE_FRONT_WALL_DOWN
		);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto tile_data_flags = random_unsigned_integer();
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgTileDataStrc moo_pTileData{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgTileDataStrc original_pTileData{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			uint32_t nTileFlags = random_unsigned_integer();
			int nType = tile_type;
			int nX = random_unsigned_integer(0, 1000);
			int nY = random_unsigned_integer(0, 1000);

			const auto setup_data = [tile_type, tile_data_flags, tile_flags](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgTileDataStrc& pTileData,
				D2TileLibraryEntryStrc& pTileLibraryEntry
			) {
				pTileLibraryEntry.nFlags = tile_flags;

				pTileData.nTileType = tile_type;
				pTileData.dwFlags = tile_data_flags;
				pTileData.pTile = &pTileLibraryEntry;

				// Doors look up preset units of the level, the Rogue Encampment doesn't have any
				pLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;
				pDrlgRoom.pLevel = &pLevel;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pTileData, moo_pTileLibraryEntry);
			setup_data(original_pDrlgRoom, original_pLevel, original_pTileData, original_pTileLibraryEntry);

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_pTileData, nTileFlags, nType, nX, nY);
			original(&original_pDrlgRoom, &original_pTileData, nTileFlags, nType, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pTileData, original_pTileData, "Comparing pTileData");
		}
	}

	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FD88BE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_AddTilePresetUnits, dll_base + 0x00048BE0);

		// All levels which have tiles with preset units
		const auto level_id = GENERATE(
			LEVEL_BARRACKS, LEVEL_JAILLEV1, LEVEL_JAILLEV2, LEVEL_JAILLEV3, LEVEL_MONASTERYGATE, LEVEL_OUTERCLOISTER,
			LEVEL_INNERCLOISTER, LEVEL_CATHEDRAL, LEVEL_CATACOMBSLEV1, LEVEL_CATACOMBSLEV2, LEVEL_CATACOMBSLEV3,
			LEVEL_CATACOMBSLEV4, LEVEL_HAREMLEV2, LEVEL_PALACECELLARLEV1, LEVEL_PALACECELLARLEV2, LEVEL_PALACECELLARLEV3,
			LEVEL_STONYTOMBLEV1, LEVEL_HALLSOFTHEDEADLEV1, LEVEL_HALLSOFTHEDEADLEV2, LEVEL_CLAWVIPERTEMPLELEV1,
			LEVEL_STONYTOMBLEV2, LEVEL_HALLSOFTHEDEADLEV3, LEVEL_CLAWVIPERTEMPLELEV2, LEVEL_TALRASHASTOMB1,
			LEVEL_TALRASHASTOMB2, LEVEL_TALRASHASTOMB3, LEVEL_TALRASHASTOMB4, LEVEL_TALRASHASTOMB5, LEVEL_TALRASHASTOMB6,
			LEVEL_TALRASHASTOMB7, LEVEL_MAGGOTLAIRLEV1, LEVEL_MAGGOTLAIRLEV2, LEVEL_MAGGOTLAIRLEV3, LEVEL_HARROGATH,
			LEVEL_ID_ACT5_BARRICADE_1, LEVEL_ARREATPLATEAU, LEVEL_TUNDRAWASTELANDS, LEVEL_ROGUEENCAMPMENT
		);

		SUBCASE("")
		{
			for (const auto tile_type : { TILETYPE_WALL_LEFT_DOOR, TILETYPE_WALL_RIGHT_DOOR })
			{
				for (const auto tile_style : { 0, 1, 2, 3, 4, 5, 6, 7, 26, 29 })
				{
					for (auto tile_sequence = 0; tile_sequence < 7; ++tile_sequence)
					{
						// Input data
						const auto room_x = random_unsigned_integer(0, 1000);
						const auto room_y = random_unsigned_integer(0, 1000);
						const auto low_seed = random_unsigned_integer();
						const auto high_seed = random_unsigned_integer();

						D2C_PackedTileInformation nTileInformation{};
						nTileInformation.nTileStyle = tile_style;
						nTileInformation.nTileSequence = tile_sequence;

						D2DrlgRoomStrc moo_pDrlgRoom{};
						D2DrlgLevelStrc moo_pLevel{};
						D2DrlgStrc moo_pDrlg{};
						D2DrlgTileDataStrc moo_pTileData{};
						D2DrlgRoomStrc original_pDrlgRoom{};
						D2DrlgLevelStrc original_pLevel{};
						D2DrlgStrc original_pDrlg{};
						D2DrlgTileDataStrc original_pTileData{};
						uint32_t nPackedTileInformation = nTileInformation.nPackedValue;
						// Keep the units inside of the room (preset offsets are within [-2, 5] subtiles)
						int nX = room_x + random_unsigned_integer(1, 6);
						int nY = room_y + random_unsigned_integer(1, 6);
						int nTileType = tile_type;

						const auto setup_data = [level_id, tile_type, room_x, room_y, low_seed, high_seed](
							D2DrlgRoomStrc& pDrlgRoom,
							D2DrlgLevelStrc& pLevel,
							D2DrlgStrc& pDrlg,
							D2DrlgTileDataStrc& pTileData
						) {
							pTileData.nTileType = tile_type;

							pLevel.nLevelId = level_id;
							pLevel.pDrlg = &pDrlg;

							pDrlgRoom.pLevel = &pLevel;
							pDrlgRoom.nTileXPos = room_x;
							pDrlgRoom.nTileYPos = room_y;
							pDrlgRoom.nTileWidth = 8;
							pDrlgRoom.nTileHeight = 8;
							pDrlgRoom.pSeed.nLowSeed = low_seed;
							pDrlgRoom.pSeed.nHighSeed = high_seed;
						};

						CAPTURE(tile_type);
						CAPTURE(tile_style);
						CAPTURE(tile_sequence);

						setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pTileData);
						setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_pTileData);

						// Call both implementations
						sut(&moo_pDrlgRoom, &moo_pTileData, nPackedTileInformation, nX, nY, nTileType);
						original(&original_pDrlgRoom, &original_pTileData, nPackedTileInformation, nX, nY, nTileType);

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
						MOO_CHECK_EQ(moo_pTileData, original_pTileData, "Comparing pTileData");
						MOO_CHECK_EQ(moo_pDrlgRoom.pPresetUnits, original_pDrlgRoom.pPresetUnits, "Comparing pDrlgRoom.pPresetUnits");
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88DD0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_InitTileData, dll_base + 0x00048DD0);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto room_x = random_unsigned_integer(0, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);
			const auto tile_data_flags = random_unsigned_integer();

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileDataStrc moo_pTileData{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileDataStrc original_pTileData{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			int nX = room_x + random_unsigned_integer(0, 8);
			int nY = room_y + random_unsigned_integer(0, 8);
			uint32_t nPackedTileInformation = random_unsigned_integer();

			const auto setup_data = [room_x, room_y, tile_flags, tile_data_flags](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileDataStrc& pTileData,
				D2TileLibraryEntryStrc& pTileLibraryEntry
			) {
				pTileLibraryEntry.nFlags = tile_flags;

				pTileData.dwFlags = tile_data_flags;

				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
			};

			setup_data(moo_pDrlgRoom, moo_pTileData, moo_pTileLibraryEntry);
			setup_data(original_pDrlgRoom, original_pTileData, original_pTileLibraryEntry);

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_pTileData, nX, nY, nPackedTileInformation, &moo_pTileLibraryEntry);
			original(&original_pDrlgRoom, &original_pTileData, nX, nY, nPackedTileInformation, &original_pTileLibraryEntry);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pTileData, original_pTileData, "Comparing pTileData");
			MOO_CHECK_EQ(moo_pTileLibraryEntry, original_pTileLibraryEntry, "Comparing pTileLibraryEntry");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88E60")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_InitFloorTileData, dll_base + 0x00048E60);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto room_x = random_unsigned_integer(0, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);
			const auto previous_tile_flags = random_unsigned_integer();

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pFloorTiles[1]{};
			D2DrlgTileDataStrc moo_pPreviousTileData{};
			D2DrlgTileDataStrc* moo_ppTileData{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pFloorTiles[1]{};
			D2DrlgTileDataStrc original_pPreviousTileData{};
			D2DrlgTileDataStrc* original_ppTileData{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			int nX = room_x + random_unsigned_integer(0, 8);
			int nY = room_y + random_unsigned_integer(0, 8);
			uint32_t nPackedTileInformation = random_unsigned_integer();

			const auto setup_data = [room_x, room_y, tile_flags, previous_tile_flags](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc (&pFloorTiles)[1],
				D2DrlgTileDataStrc& pPreviousTileData,
				D2DrlgTileDataStrc*& ppTileData,
				D2TileLibraryEntryStrc& pTileLibraryEntry
			) {
				pTileLibraryEntry.nFlags = tile_flags;

				pPreviousTileData.dwFlags = previous_tile_flags;
				ppTileData = &pPreviousTileData;

				pTileGrid.pTiles.pFloorTiles = pFloorTiles;
				pTileGrid.pTiles.nFloors = 1;

				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.pTileGrid = &pTileGrid;
			};

			setup_data(moo_pDrlgRoom, moo_pTileGrid, moo_pFloorTiles, moo_pPreviousTileData, moo_ppTileData, moo_pTileLibraryEntry);
			setup_data(original_pDrlgRoom, original_pTileGrid, original_pFloorTiles, original_pPreviousTileData, original_ppTileData, original_pTileLibraryEntry);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, &moo_ppTileData, nX, nY, nPackedTileInformation, &moo_pTileLibraryEntry);
			const auto original_result = original(&original_pDrlgRoom, &original_ppTileData, nX, nY, nPackedTileInformation, &original_pTileLibraryEntry);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_ppTileData, original_ppTileData, "Comparing ppTileData");
			MOO_CHECK_EQ(moo_pTileLibraryEntry, original_pTileLibraryEntry, "Comparing pTileLibraryEntry");
			MOO_CHECK_EQ(moo_pTileGrid.nFloors, original_pTileGrid.nFloors, "Comparing pTileGrid.nFloors");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88F10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_InitShadowTileData, dll_base + 0x00048F10);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto room_x = random_unsigned_integer(0, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);
			const auto previous_tile_flags = random_unsigned_integer();

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pRoofTiles[1]{};
			D2DrlgTileDataStrc moo_pPreviousTileData{};
			D2DrlgTileDataStrc* moo_ppTileData{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pRoofTiles[1]{};
			D2DrlgTileDataStrc original_pPreviousTileData{};
			D2DrlgTileDataStrc* original_ppTileData{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			int nX = room_x + random_unsigned_integer(0, 8);
			int nY = room_y + random_unsigned_integer(0, 8);
			uint32_t nPackedTileInformation = random_unsigned_integer();

			const auto setup_data = [room_x, room_y, tile_flags, previous_tile_flags](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc (&pRoofTiles)[1],
				D2DrlgTileDataStrc& pPreviousTileData,
				D2DrlgTileDataStrc*& ppTileData,
				D2TileLibraryEntryStrc& pTileLibraryEntry
			) {
				pTileLibraryEntry.nFlags = tile_flags;

				pPreviousTileData.dwFlags = previous_tile_flags;
				ppTileData = &pPreviousTileData;

				pTileGrid.pTiles.pRoofTiles = pRoofTiles;
				pTileGrid.pTiles.nRoofs = 1;

				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.pTileGrid = &pTileGrid;
			};

			setup_data(moo_pDrlgRoom, moo_pTileGrid, moo_pRoofTiles, moo_pPreviousTileData, moo_ppTileData, moo_pTileLibraryEntry);
			setup_data(original_pDrlgRoom, original_pTileGrid, original_pRoofTiles, original_pPreviousTileData, original_ppTileData, original_pTileLibraryEntry);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, &moo_ppTileData, nX, nY, nPackedTileInformation, &moo_pTileLibraryEntry);
			const auto original_result = original(&original_pDrlgRoom, &original_ppTileData, nX, nY, nPackedTileInformation, &original_pTileLibraryEntry);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_ppTileData, original_ppTileData, "Comparing ppTileData");
			MOO_CHECK_EQ(moo_pTileLibraryEntry, original_pTileLibraryEntry, "Comparing pTileLibraryEntry");
			MOO_CHECK_EQ(moo_pTileGrid.nShadows, original_pTileGrid.nShadows, "Comparing pTileGrid.nShadows");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88FD0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_InitTileShadow, dll_base + 0x00048FD0);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto room_x = random_unsigned_integer(0, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pRoofTiles[1]{};
			D2TileLibraryHashStrc moo_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc moo_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc moo_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pRoofTiles[1]{};
			D2TileLibraryHashStrc original_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc original_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc original_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			int nX = room_x + random_unsigned_integer(0, 8);
			int nY = room_y + random_unsigned_integer(0, 8);
			uint32_t nPackedTileInformation = random_unsigned_integer();

			const auto setup_data = [room_x, room_y, tile_flags](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc (&pRoofTiles)[1],
				D2TileLibraryHashStrc& pTileLibraryHash,
				D2TileLibraryHashNodeStrc& pTileLibraryHashNode,
				D2TileLibraryHashRefStrc& pTileLibraryHashRef,
				D2TileLibraryEntryStrc& pTileLibraryEntry
			) {
				// Every lookup falls back to this tile
				pTileLibraryEntry.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryEntry.nRarity_Frame = 1;
				pTileLibraryEntry.nFlags = tile_flags;
				pTileLibraryHashRef.pTile = &pTileLibraryEntry;
				pTileLibraryHashNode.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryHashNode.pRef = &pTileLibraryHashRef;
				std::fill(std::begin(pTileLibraryHash.pNodes), std::end(pTileLibraryHash.pNodes), &pTileLibraryHashNode);

				pTileGrid.pTiles.pRoofTiles = pRoofTiles;
				pTileGrid.pTiles.nRoofs = 1;

				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.pTileGrid = &pTileGrid;
				pDrlgRoom.pTiles[0] = &pTileLibraryHash;
			};

			setup_data(moo_pDrlgRoom, moo_pTileGrid, moo_pRoofTiles, moo_pTileLibraryHash, moo_pTileLibraryHashNode, moo_pTileLibraryHashRef, moo_pTileLibraryEntry);
			setup_data(original_pDrlgRoom, original_pTileGrid, original_pRoofTiles, original_pTileLibraryHash, original_pTileLibraryHashNode, original_pTileLibraryHashRef, original_pTileLibraryEntry);

			// Call both implementations
			sut(&moo_pDrlgRoom, nX, nY, nPackedTileInformation);
			original(&original_pDrlgRoom, nX, nY, nPackedTileInformation);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pTileGrid.nShadows, original_pTileGrid.nShadows, "Comparing pTileGrid.nShadows");
			MOO_CHECK_EQ(moo_pRoofTiles[0], original_pRoofTiles[0], "Comparing pRoofTiles[0]");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD89000")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_LoadInitRoomTiles, dll_base + 0x00049000);

		const auto level_id = GENERATE(LEVEL_ROGUEENCAMPMENT, LEVEL_ARCANESANCTUARY);
		const auto fill_blanks = GENERATE(TRUE, FALSE);
		const auto kill_edge_x = GENERATE(TRUE, FALSE);
		const auto kill_edge_y = GENERATE(TRUE, FALSE);

		REPEAT_5();

		SUBCASE("")
		{
			constexpr int nRoomSize = 4;
			constexpr int nGridSize = nRoomSize + 1;
			constexpr int nCells = nGridSize * nGridSize;

			// Exits and doors are excluded, as they require warps and preset units
			constexpr int tile_types[] = {
				TILETYPE_FLOOR, TILETYPE_WALL_LEFT, TILETYPE_WALL_RIGHT, TILETYPE_WALL_TOP_CORNER_RIGHT, TILETYPE_WALL_TOP_CORNER_LEFT,
				TILETYPE_WALL_TOP_RIGHT, TILETYPE_WALL_BOTTOM_LEFT, TILETYPE_WALL_BOTTOM_RIGHT, TILETYPE_COLUMN, TILETYPE_TREE
			};

			// Input data
			const auto room_x = random_unsigned_integer(0, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);

			std::array<int, nCells> packed_tile_informations{};
			std::array<int, nCells> cell_tile_types{};
			for (int i = 0; i < nCells; ++i)
			{
				D2C_PackedTileInformation nTileInformation{};
				nTileInformation.bIsWall = random_unsigned_integer(0, 1);
				nTileInformation.bIsFloor = random_unsigned_integer(0, 1);
				nTileInformation.bLOS = random_unsigned_integer(0, 1);
				nTileInformation.bLayerAbove = random_unsigned_integer(0, 1);
				nTileInformation.nTileSequence = random_unsigned_integer(0, 3);
				nTileInformation.bUnwalkable = random_unsigned_integer(0, 1);
				nTileInformation.nWallLayer = random_unsigned_integer(0, 3);
				nTileInformation.nTileStyle = random_unsigned_integer(0, 1) ? 30 : random_unsigned_integer(0, 63);
				nTileInformation.bShadow = random_unsigned_integer(0, 1);
				nTileInformation.bHidden = random_unsigned_integer(0, 1);
				packed_tile_informations[i] = nTileInformation.nPackedValue;

				cell_tile_types[i] = nTileInformation.bIsWall ? tile_types[random_unsigned_integer(1, (uint32_t)std::size(tile_types) - 1)] : TILETYPE_FLOOR;
			}

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pWallTiles[2 * nCells]{};
			D2DrlgTileDataStrc moo_pFloorTiles[nCells]{};
			D2DrlgTileDataStrc moo_pRoofTiles[nCells]{};
			D2TileLibraryHashStrc moo_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc moo_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc moo_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2DrlgGridStrc moo_pTilePackedInfoGrid{};
			int moo_pTilePackedInfoGridCells[nCells]{};
			int moo_pTilePackedInfoGridRowOffsets[nGridSize]{};
			D2DrlgGridStrc moo_pTileTypeGrid{};
			int moo_pTileTypeGridCells[nCells]{};
			int moo_pTileTypeGridRowOffsets[nGridSize]{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pWallTiles[2 * nCells]{};
			D2DrlgTileDataStrc original_pFloorTiles[nCells]{};
			D2DrlgTileDataStrc original_pRoofTiles[nCells]{};
			D2TileLibraryHashStrc original_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc original_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc original_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			D2DrlgGridStrc original_pTilePackedInfoGrid{};
			int original_pTilePackedInfoGridCells[nCells]{};
			int original_pTilePackedInfoGridRowOffsets[nGridSize]{};
			D2DrlgGridStrc original_pTileTypeGrid{};
			int original_pTileTypeGridCells[nCells]{};
			int original_pTileTypeGridRowOffsets[nGridSize]{};
			BOOL bFillBlanks = fill_blanks;
			BOOL bKillEdgeX = kill_edge_x;
			BOOL bKillEdgeY = kill_edge_y;

			const auto setup_data = [nGridSize, nCells, nRoomSize, level_id, room_x, room_y, tile_flags, &packed_tile_informations, &cell_tile_types](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc (&pWallTiles)[2 * nCells],
				D2DrlgTileDataStrc (&pFloorTiles)[nCells],
				D2DrlgTileDataStrc (&pRoofTiles)[nCells],
				D2TileLibraryHashStrc& pTileLibraryHash,
				D2TileLibraryHashNodeStrc& pTileLibraryHashNode,
				D2TileLibraryHashRefStrc& pTileLibraryHashRef,
				D2TileLibraryEntryStrc& pTileLibraryEntry,
				D2DrlgGridStrc& pTilePackedInfoGrid,
				int (&pTilePackedInfoGridCells)[nCells],
				int (&pTilePackedInfoGridRowOffsets)[nGridSize],
				D2DrlgGridStrc& pTileTypeGrid,
				int (&pTileTypeGridCells)[nCells],
				int (&pTileTypeGridRowOffsets)[nGridSize]
			) {
				std::copy(packed_tile_informations.begin(), packed_tile_informations.end(), pTilePackedInfoGridCells);
				std::copy(cell_tile_types.begin(), cell_tile_types.end(), pTileTypeGridCells);
				for (int i = 0; i < nGridSize; ++i)
				{
					pTilePackedInfoGridRowOffsets[i] = i * nGridSize;
					pTileTypeGridRowOffsets[i] = i * nGridSize;
				}

				pTilePackedInfoGrid.pCellsFlags = pTilePackedInfoGridCells;
				pTilePackedInfoGrid.pCellsRowOffsets = pTilePackedInfoGridRowOffsets;
				pTilePackedInfoGrid.nWidth = nGridSize;
				pTilePackedInfoGrid.nHeight = nGridSize;

				pTileTypeGrid.pCellsFlags = pTileTypeGridCells;
				pTileTypeGrid.pCellsRowOffsets = pTileTypeGridRowOffsets;
				pTileTypeGrid.nWidth = nGridSize;
				pTileTypeGrid.nHeight = nGridSize;

				// Every lookup falls back to this tile
				pTileLibraryEntry.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryEntry.nRarity_Frame = 1;
				pTileLibraryEntry.nFlags = tile_flags;
				pTileLibraryHashRef.pTile = &pTileLibraryEntry;
				pTileLibraryHashNode.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryHashNode.pRef = &pTileLibraryHashRef;
				std::fill(std::begin(pTileLibraryHash.pNodes), std::end(pTileLibraryHash.pNodes), &pTileLibraryHashNode);

				pTileGrid.pTiles.pWallTiles = pWallTiles;
				pTileGrid.pTiles.nWalls = 2 * nCells;
				pTileGrid.pTiles.pFloorTiles = pFloorTiles;
				pTileGrid.pTiles.nFloors = nCells;
				pTileGrid.pTiles.pRoofTiles = pRoofTiles;
				pTileGrid.pTiles.nRoofs = nCells;

				pLevel.nLevelId = level_id;
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = nRoomSize;
				pDrlgRoom.nTileHeight = nRoomSize;
				pDrlgRoom.pTileGrid = &pTileGrid;
				pDrlgRoom.pTiles[0] = &pTileLibraryHash;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pTileGrid, moo_pWallTiles, moo_pFloorTiles, moo_pRoofTiles, moo_pTileLibraryHash, moo_pTileLibraryHashNode, moo_pTileLibraryHashRef, moo_pTileLibraryEntry, moo_pTilePackedInfoGrid, moo_pTilePackedInfoGridCells, moo_pTilePackedInfoGridRowOffsets, moo_pTileTypeGrid, moo_pTileTypeGridCells, moo_pTileTypeGridRowOffsets);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_pTileGrid, original_pWallTiles, original_pFloorTiles, original_pRoofTiles, original_pTileLibraryHash, original_pTileLibraryHashNode, original_pTileLibraryHashRef, original_pTileLibraryEntry, original_pTilePackedInfoGrid, original_pTilePackedInfoGridCells, original_pTilePackedInfoGridRowOffsets, original_pTileTypeGrid, original_pTileTypeGridCells, original_pTileTypeGridRowOffsets);

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_pTilePackedInfoGrid, &moo_pTileTypeGrid, bFillBlanks, bKillEdgeX, bKillEdgeY);
			original(&original_pDrlgRoom, &original_pTilePackedInfoGrid, &original_pTileTypeGrid, bFillBlanks, bKillEdgeX, bKillEdgeY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pTilePackedInfoGrid, original_pTilePackedInfoGrid, "Comparing pTilePackedInfoGrid");
			MOO_CHECK_EQ(moo_pTileTypeGrid, original_pTileTypeGrid, "Comparing pTileTypeGrid");
			MOO_CHECK_EQ(moo_pTileGrid.nWalls, original_pTileGrid.nWalls, "Comparing pTileGrid.nWalls");
			MOO_CHECK_EQ(moo_pTileGrid.nFloors, original_pTileGrid.nFloors, "Comparing pTileGrid.nFloors");
			MOO_CHECK_EQ(moo_pTileGrid.nShadows, original_pTileGrid.nShadows, "Comparing pTileGrid.nShadows");
			for (int i = 0; i < 2 * nCells; ++i)
			{
				MOO_CHECK_EQ(moo_pWallTiles[i], original_pWallTiles[i], "Comparing pWallTiles");
			}
			for (int i = 0; i < nCells; ++i)
			{
				MOO_CHECK_EQ(moo_pFloorTiles[i], original_pFloorTiles[i], "Comparing pFloorTiles");
				MOO_CHECK_EQ(moo_pRoofTiles[i], original_pRoofTiles[i], "Comparing pRoofTiles");
			}
		}
	}

	TEST_CASE_FIXTURE(LvlWarpTxtFixture<NoopFixture>, "D2Common.0x6FD89360")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_AddWarp, dll_base + 0x00049360);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto room_x = random_unsigned_integer(0, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto level_id = random_unsigned_integer(1, 135);
			const auto warp_id = random_unsigned_integer(0, 7);
			const auto pLvlWarpTxtRecord = &lvlwarp_txt[random_unsigned_integer(0, lvlwarp_record_count - 1)];
			const auto destination_level_id = pLvlWarpTxtRecord->dwLevelId;

			// The direction has to match the warp record, so that it can be found
			int tile_type = random_unsigned_integer(0, 1) ? TILETYPE_WALL_RIGHT_EXIT : TILETYPE_WALL_LEFT_EXIT;
			if (pLvlWarpTxtRecord->szDirection[0] == 'r')
			{
				tile_type = TILETYPE_WALL_RIGHT_EXIT;
			}
			else if (pLvlWarpTxtRecord->szDirection[0] == 'l')
			{
				tile_type = TILETYPE_WALL_LEFT_EXIT;
			}

			D2C_PackedTileInformation nTileInformation{};
			nTileInformation.nTileStyle = warp_id;

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pWarp{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pWarp{};
			// The position can also be on the right or bottom edge of the room, where no warp is added
			int nX = room_x + random_unsigned_integer(0, 8);
			int nY = room_y + random_unsigned_integer(0, 8);
			uint32_t nPackedTileInformation = nTileInformation.nPackedValue;
			int nTileType = tile_type;

			const auto setup_data = [room_x, room_y, level_id, warp_id, destination_level_id](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pWarp
			) {
				pWarp.nLevel = level_id;
				pWarp.nWarp[warp_id] = destination_level_id;

				pDrlg.pWarp = &pWarp;

				pLevel.nLevelId = level_id;
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pWarp);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_pWarp);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nX, nY, nPackedTileInformation, nTileType);
			const auto original_result = original(&original_pDrlgRoom, nX, nY, nPackedTileInformation, nTileType);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pDrlgRoom.pPresetUnits, original_pDrlgRoom.pPresetUnits, "Comparing pDrlgRoom.pPresetUnits");
		}
	}

	TEST_CASE_FIXTURE(LvlWarpTxtFixture<NoopFixture>, "D2Common.0x6FD89410")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_LoadWallWarpTiles, dll_base + 0x00049410);

		// Only sequences 0 and 4 add a warp
		const auto tile_sequence = GENERATE(0, 1, 4, 5);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto room_x = random_unsigned_integer(0, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto tile_x = random_unsigned_integer(0, 7);
			const auto tile_y = random_unsigned_integer(0, 7);
			const auto level_id = random_unsigned_integer(1, 135);
			const auto warp_id = random_unsigned_integer(0, 7);
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);
			const auto pLvlWarpTxtRecord = &lvlwarp_txt[random_unsigned_integer(0, lvlwarp_record_count - 1)];
			const auto destination_level_id = pLvlWarpTxtRecord->dwLevelId;

			// The direction has to match the warp record, so that it can be found
			int tile_type = random_unsigned_integer(0, 1) ? TILETYPE_WALL_RIGHT_EXIT : TILETYPE_WALL_LEFT_EXIT;
			if (pLvlWarpTxtRecord->szDirection[0] == 'r')
			{
				tile_type = TILETYPE_WALL_RIGHT_EXIT;
			}
			else if (pLvlWarpTxtRecord->szDirection[0] == 'l')
			{
				tile_type = TILETYPE_WALL_LEFT_EXIT;
			}

			D2C_PackedTileInformation nTileInformation{};
			nTileInformation.nTileStyle = warp_id;
			nTileInformation.nTileSequence = tile_sequence;

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pWarp{};
			D2RoomTileStrc moo_pRoomTile{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pWallTiles[1]{};
			D2TileLibraryHashStrc moo_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc moo_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc moo_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2DrlgTileDataStrc moo_pTileData{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pWarp{};
			D2RoomTileStrc original_pRoomTile{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pWallTiles[1]{};
			D2TileLibraryHashStrc original_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc original_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc original_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			D2DrlgTileDataStrc original_pTileData{};
			uint32_t nPackedTileInformation = nTileInformation.nPackedValue;
			int nTileType = tile_type;

			const auto setup_data = [room_x, room_y, tile_x, tile_y, level_id, warp_id, tile_flags, pLvlWarpTxtRecord, destination_level_id](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pWarp,
				D2RoomTileStrc& pRoomTile,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc (&pWallTiles)[1],
				D2TileLibraryHashStrc& pTileLibraryHash,
				D2TileLibraryHashNodeStrc& pTileLibraryHashNode,
				D2TileLibraryHashRefStrc& pTileLibraryHashRef,
				D2TileLibraryEntryStrc& pTileLibraryEntry,
				D2DrlgTileDataStrc& pTileData
			) {
				pTileData.nPosX = tile_x;
				pTileData.nPosY = tile_y;

				// Every lookup falls back to this tile
				pTileLibraryEntry.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryEntry.nRarity_Frame = 1;
				pTileLibraryEntry.nFlags = tile_flags;
				pTileLibraryHashRef.pTile = &pTileLibraryEntry;
				pTileLibraryHashNode.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryHashNode.pRef = &pTileLibraryHashRef;
				std::fill(std::begin(pTileLibraryHash.pNodes), std::end(pTileLibraryHash.pNodes), &pTileLibraryHashNode);

				pTileGrid.pTiles.pWallTiles = pWallTiles;
				pTileGrid.pTiles.nWalls = 1;

				pRoomTile.pLvlWarpTxtRecord = pLvlWarpTxtRecord;
				pRoomTile.bEnabled = TRUE;

				pWarp.nLevel = level_id;
				pWarp.nWarp[warp_id] = destination_level_id;

				pDrlg.pWarp = &pWarp;

				pLevel.nLevelId = level_id;
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.pRoomTiles = &pRoomTile;
				pDrlgRoom.pTileGrid = &pTileGrid;
				pDrlgRoom.pTiles[0] = &pTileLibraryHash;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pWarp, moo_pRoomTile, moo_pTileGrid, moo_pWallTiles, moo_pTileLibraryHash, moo_pTileLibraryHashNode, moo_pTileLibraryHashRef, moo_pTileLibraryEntry, moo_pTileData);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_pWarp, original_pRoomTile, original_pTileGrid, original_pWallTiles, original_pTileLibraryHash, original_pTileLibraryHashNode, original_pTileLibraryHashRef, original_pTileLibraryEntry, original_pTileData);

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_pTileData, nPackedTileInformation, nTileType);
			original(&original_pDrlgRoom, &original_pTileData, nPackedTileInformation, nTileType);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pTileData, original_pTileData, "Comparing pTileData");
			MOO_CHECK_EQ(moo_pDrlgRoom.pPresetUnits, original_pDrlgRoom.pPresetUnits, "Comparing pDrlgRoom.pPresetUnits");
			MOO_CHECK_EQ(moo_pRoomTile.pLvlWarpTxtRecord, original_pRoomTile.pLvlWarpTxtRecord, "Comparing pRoomTile.pLvlWarpTxtRecord");
			MOO_CHECK_EQ(moo_pRoomTile.unk0x0C, original_pRoomTile.unk0x0C, "Comparing pRoomTile.unk0x0C");
			MOO_CHECK_EQ(moo_pRoomTile.unk0x10, original_pRoomTile.unk0x10, "Comparing pRoomTile.unk0x10");
			MOO_CHECK_EQ(moo_pTileGrid.nWalls, original_pTileGrid.nWalls, "Comparing pTileGrid.nWalls");
		}
	}

	TEST_CASE_FIXTURE(LvlWarpTxtFixture<NoopFixture>, "D2Common.0x6FD89590")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_LoadFloorWarpTiles, dll_base + 0x00049590);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto room_x = random_unsigned_integer(0, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto room_flags = random_unsigned_integer();
			const auto level_id = random_unsigned_integer(1, 135);
			const auto warp_id = random_unsigned_integer(0, 7);
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);
			const auto pLvlWarpTxtRecord = &lvlwarp_txt[random_unsigned_integer(0, lvlwarp_record_count - 1)];
			const auto destination_level_id = pLvlWarpTxtRecord->dwLevelId;

			// The direction has to match the warp record, so that it can be found
			int tile_type = random_unsigned_integer(0, 1) ? TILETYPE_WALL_RIGHT_EXIT : TILETYPE_WALL_LEFT_EXIT;
			if (pLvlWarpTxtRecord->szDirection[0] == 'r')
			{
				tile_type = TILETYPE_WALL_RIGHT_EXIT;
			}
			else if (pLvlWarpTxtRecord->szDirection[0] == 'l')
			{
				tile_type = TILETYPE_WALL_LEFT_EXIT;
			}

			D2C_PackedTileInformation nTileInformation{};
			nTileInformation.nTileStyle = warp_id;
			nTileInformation.nTileSequence = random_unsigned_integer(0, 7);
			nTileInformation.bHidden = true;

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pWarp{};
			D2RoomTileStrc moo_pRoomTile{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pFloorTiles[4]{};
			D2TileLibraryHashStrc moo_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc moo_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc moo_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pWarp{};
			D2RoomTileStrc original_pRoomTile{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pFloorTiles[4]{};
			D2TileLibraryHashStrc original_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc original_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc original_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			int nX = room_x + random_unsigned_integer(1, 7);
			int nY = room_y + random_unsigned_integer(1, 7);
			uint32_t nPackedTileInformation = nTileInformation.nPackedValue;
			int nTileType = tile_type;

			const auto setup_data = [room_x, room_y, room_flags, level_id, warp_id, tile_flags, pLvlWarpTxtRecord, destination_level_id](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pWarp,
				D2RoomTileStrc& pRoomTile,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc (&pFloorTiles)[4],
				D2TileLibraryHashStrc& pTileLibraryHash,
				D2TileLibraryHashNodeStrc& pTileLibraryHashNode,
				D2TileLibraryHashRefStrc& pTileLibraryHashRef,
				D2TileLibraryEntryStrc& pTileLibraryEntry
			) {
				// Every lookup falls back to this tile
				pTileLibraryEntry.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryEntry.nRarity_Frame = 1;
				pTileLibraryEntry.nFlags = tile_flags;
				pTileLibraryHashRef.pTile = &pTileLibraryEntry;
				pTileLibraryHashNode.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryHashNode.pRef = &pTileLibraryHashRef;
				std::fill(std::begin(pTileLibraryHash.pNodes), std::end(pTileLibraryHash.pNodes), &pTileLibraryHashNode);

				pTileGrid.pTiles.pFloorTiles = pFloorTiles;
				pTileGrid.pTiles.nFloors = 4;

				pRoomTile.pLvlWarpTxtRecord = pLvlWarpTxtRecord;
				pRoomTile.bEnabled = TRUE;

				pWarp.nLevel = level_id;
				pWarp.nWarp[warp_id] = destination_level_id;

				pDrlg.pWarp = &pWarp;

				pLevel.nLevelId = level_id;
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.dwFlags = room_flags;
				pDrlgRoom.pRoomTiles = &pRoomTile;
				pDrlgRoom.pTileGrid = &pTileGrid;
				pDrlgRoom.pTiles[0] = &pTileLibraryHash;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pWarp, moo_pRoomTile, moo_pTileGrid, moo_pFloorTiles, moo_pTileLibraryHash, moo_pTileLibraryHashNode, moo_pTileLibraryHashRef, moo_pTileLibraryEntry);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_pWarp, original_pRoomTile, original_pTileGrid, original_pFloorTiles, original_pTileLibraryHash, original_pTileLibraryHashNode, original_pTileLibraryHashRef, original_pTileLibraryEntry);

			// Call both implementations
			sut(&moo_pDrlgRoom, nX, nY, nPackedTileInformation, nTileType);
			original(&original_pDrlgRoom, nX, nY, nPackedTileInformation, nTileType);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pRoomTile.pLvlWarpTxtRecord, original_pRoomTile.pLvlWarpTxtRecord, "Comparing pRoomTile.pLvlWarpTxtRecord");
			MOO_CHECK_EQ(moo_pRoomTile.unk0x0C, original_pRoomTile.unk0x0C, "Comparing pRoomTile.unk0x0C");
			MOO_CHECK_EQ(moo_pRoomTile.unk0x10, original_pRoomTile.unk0x10, "Comparing pRoomTile.unk0x10");
			MOO_CHECK_EQ(moo_pTileGrid.nFloors, original_pTileGrid.nFloors, "Comparing pTileGrid.nFloors");
			for (int i = 0; i < 4; ++i)
			{
				MOO_CHECK_EQ(moo_pFloorTiles[i], original_pFloorTiles[i], "Comparing pFloorTiles");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD897E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_GetLinkedTileData, dll_base + 0x000497E0);

		const auto floor = GENERATE(TRUE, FALSE);
		const auto link_floor = GENERATE(TRUE, FALSE);
		const auto same_position = GENERATE(true, false);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto near_room_x = random_unsigned_integer(0, 1000);
			const auto near_room_y = random_unsigned_integer(0, 1000);
			const auto tile_x = random_unsigned_integer(0, 7);
			const auto tile_y = random_unsigned_integer(0, 7);
			const auto tile_type = random_unsigned_integer(TILETYPE_FLOOR, TILETYPE_FRONT_WALL_DOWN);
			const auto tile_data_flags = random_unsigned_integer(0, 4) << MAPTILE_WALL_LAYER_BIT;

			D2C_PackedTileInformation nTileInformation{};
			nTileInformation.bShadow = random_unsigned_integer(0, 1);
			nTileInformation.nWallLayer = random_unsigned_integer(0, 3);

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc moo_pNearDrlgRoom{};
			D2DrlgRoomStrc* moo_ppRoomsNear[2]{};
			D2DrlgTileGridStrc moo_pNearTileGrid{};
			D2DrlgTileLinkStrc moo_pNearTileLink{};
			D2DrlgTileDataStrc moo_pNearTileData{};
			D2DrlgRoomStrc* moo_ppDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc original_pNearDrlgRoom{};
			D2DrlgRoomStrc* original_ppRoomsNear[2]{};
			D2DrlgTileGridStrc original_pNearTileGrid{};
			D2DrlgTileLinkStrc original_pNearTileLink{};
			D2DrlgTileDataStrc original_pNearTileData{};
			D2DrlgRoomStrc* original_ppDrlgRoom{};
			BOOL bFloor = floor;
			uint32_t nPackedTileInformation = nTileInformation.nPackedValue;
			int nX = near_room_x + (same_position ? tile_x : tile_x + 1);
			int nY = near_room_y + tile_y;

			const auto setup_data = [link_floor, near_room_x, near_room_y, tile_x, tile_y, tile_type, tile_data_flags](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc& pNearDrlgRoom,
				D2DrlgRoomStrc* (&ppRoomsNear)[2],
				D2DrlgTileGridStrc& pNearTileGrid,
				D2DrlgTileLinkStrc& pNearTileLink,
				D2DrlgTileDataStrc& pNearTileData
			) {
				pNearTileData.nPosX = tile_x;
				pNearTileData.nPosY = tile_y;
				pNearTileData.nTileType = tile_type;
				pNearTileData.dwFlags = tile_data_flags;

				pNearTileLink.bFloor = link_floor;
				pNearTileLink.pMapTile = &pNearTileData;

				pNearTileGrid.pMapLinks = &pNearTileLink;

				pNearDrlgRoom.nTileXPos = near_room_x;
				pNearDrlgRoom.nTileYPos = near_room_y;
				pNearDrlgRoom.nTileWidth = 8;
				pNearDrlgRoom.nTileHeight = 8;
				pNearDrlgRoom.pTileGrid = &pNearTileGrid;

				// The room itself is part of its near rooms, but is skipped
				ppRoomsNear[0] = &pDrlgRoom;
				ppRoomsNear[1] = &pNearDrlgRoom;

				pDrlgRoom.nTileXPos = near_room_x + 8;
				pDrlgRoom.nTileYPos = near_room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.ppRoomsNear = ppRoomsNear;
				pDrlgRoom.nRoomsNear = 2;
			};

			setup_data(moo_pDrlgRoom, moo_pNearDrlgRoom, moo_ppRoomsNear, moo_pNearTileGrid, moo_pNearTileLink, moo_pNearTileData);
			setup_data(original_pDrlgRoom, original_pNearDrlgRoom, original_ppRoomsNear, original_pNearTileGrid, original_pNearTileLink, original_pNearTileData);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, bFloor, nPackedTileInformation, nX, nY, &moo_ppDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom, bFloor, nPackedTileInformation, nX, nY, &original_ppDrlgRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_ppDrlgRoom, original_ppDrlgRoom, "Comparing ppDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD89930")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_AddLinkedTileData, dll_base + 0x00049930);

		// Doors and exits are excluded, as they require preset units and warps
		const auto tile_type = GENERATE(
			TILETYPE_FLOOR, TILETYPE_WALL_LEFT, TILETYPE_WALL_RIGHT, TILETYPE_WALL_TOP_CORNER_RIGHT, TILETYPE_WALL_TOP_CORNER_LEFT,
			TILETYPE_WALL_TOP_RIGHT, TILETYPE_WALL_BOTTOM_LEFT, TILETYPE_WALL_BOTTOM_RIGHT, TILETYPE_COLUMN, TILETYPE_SHADOW,
			TILETYPE_TREE, TILETYPE_ROOF
		);
		// 0: No existing link, 1: Existing floor link, 2: Existing wall link
		const auto existing_link = GENERATE(0, 1, 2);

		REPEAT_5();

		SUBCASE("")
		{
			// Input data
			const auto room_x = random_unsigned_integer(0, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileLinkStrc moo_pTileLink{};
			D2DrlgTileDataStrc moo_pWallTiles[2]{};
			D2DrlgTileDataStrc moo_pFloorTiles[1]{};
			D2DrlgTileDataStrc moo_pRoofTiles[1]{};
			D2TileLibraryHashStrc moo_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc moo_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc moo_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileLinkStrc original_pTileLink{};
			D2DrlgTileDataStrc original_pWallTiles[2]{};
			D2DrlgTileDataStrc original_pFloorTiles[1]{};
			D2DrlgTileDataStrc original_pRoofTiles[1]{};
			D2TileLibraryHashStrc original_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc original_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc original_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			int nTileType = tile_type;
			uint32_t nPackedTileInformation = random_unsigned_integer();
			int nX = room_x + random_unsigned_integer(0, 8);
			int nY = room_y + random_unsigned_integer(0, 8);

			const auto setup_data = [existing_link, room_x, room_y, tile_flags](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileLinkStrc& pTileLink,
				D2DrlgTileDataStrc (&pWallTiles)[2],
				D2DrlgTileDataStrc (&pFloorTiles)[1],
				D2DrlgTileDataStrc (&pRoofTiles)[1],
				D2TileLibraryHashStrc& pTileLibraryHash,
				D2TileLibraryHashNodeStrc& pTileLibraryHashNode,
				D2TileLibraryHashRefStrc& pTileLibraryHashRef,
				D2TileLibraryEntryStrc& pTileLibraryEntry
			) {
				// Every lookup falls back to this tile
				pTileLibraryEntry.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryEntry.nRarity_Frame = 1;
				pTileLibraryEntry.nFlags = tile_flags;
				pTileLibraryHashRef.pTile = &pTileLibraryEntry;
				pTileLibraryHashNode.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryHashNode.pRef = &pTileLibraryHashRef;
				std::fill(std::begin(pTileLibraryHash.pNodes), std::end(pTileLibraryHash.pNodes), &pTileLibraryHashNode);

				if (existing_link)
				{
					pTileLink.bFloor = existing_link == 1;
					pTileGrid.pMapLinks = &pTileLink;
				}

				pTileGrid.pTiles.pWallTiles = pWallTiles;
				pTileGrid.pTiles.nWalls = 2;
				pTileGrid.pTiles.pFloorTiles = pFloorTiles;
				pTileGrid.pTiles.nFloors = 1;
				pTileGrid.pTiles.pRoofTiles = pRoofTiles;
				pTileGrid.pTiles.nRoofs = 1;

				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.pTileGrid = &pTileGrid;
				pDrlgRoom.pTiles[0] = &pTileLibraryHash;
			};

			setup_data(moo_pDrlgRoom, moo_pTileGrid, moo_pTileLink, moo_pWallTiles, moo_pFloorTiles, moo_pRoofTiles, moo_pTileLibraryHash, moo_pTileLibraryHashNode, moo_pTileLibraryHashRef, moo_pTileLibraryEntry);
			setup_data(original_pDrlgRoom, original_pTileGrid, original_pTileLink, original_pWallTiles, original_pFloorTiles, original_pRoofTiles, original_pTileLibraryHash, original_pTileLibraryHashNode, original_pTileLibraryHashRef, original_pTileLibraryEntry);

			// Call both implementations
			sut(nullptr, &moo_pDrlgRoom, nTileType, nPackedTileInformation, nX, nY);
			original(nullptr, &original_pDrlgRoom, nTileType, nPackedTileInformation, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pTileGrid.nWalls, original_pTileGrid.nWalls, "Comparing pTileGrid.nWalls");
			MOO_CHECK_EQ(moo_pTileGrid.nFloors, original_pTileGrid.nFloors, "Comparing pTileGrid.nFloors");
			MOO_CHECK_EQ(moo_pTileGrid.nShadows, original_pTileGrid.nShadows, "Comparing pTileGrid.nShadows");
			MOO_CHECK_EQ(moo_pTileGrid.pMapLinks->bFloor, original_pTileGrid.pMapLinks->bFloor, "Comparing pTileGrid.pMapLinks->bFloor");
			MOO_CHECK_EQ(moo_pTileGrid.pMapLinks->pMapTile, original_pTileGrid.pMapLinks->pMapTile, "Comparing pTileGrid.pMapLinks->pMapTile");
			MOO_CHECK_EQ(moo_pWallTiles[0], original_pWallTiles[0], "Comparing pWallTiles[0]");
			MOO_CHECK_EQ(moo_pWallTiles[1], original_pWallTiles[1], "Comparing pWallTiles[1]");
			MOO_CHECK_EQ(moo_pFloorTiles[0], original_pFloorTiles[0], "Comparing pFloorTiles[0]");
			MOO_CHECK_EQ(moo_pRoofTiles[0], original_pRoofTiles[0], "Comparing pRoofTiles[0]");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD89AF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_LinkedTileDataManager, dll_base + 0x00049AF0);

		const auto tile_type = GENERATE(
			TILETYPE_FLOOR, TILETYPE_WALL_LEFT, TILETYPE_WALL_RIGHT, TILETYPE_WALL_TOP_CORNER_RIGHT, TILETYPE_WALL_TOP_CORNER_LEFT,
			TILETYPE_WALL_TOP_RIGHT, TILETYPE_WALL_BOTTOM_LEFT, TILETYPE_WALL_BOTTOM_RIGHT, TILETYPE_WALL_LEFT_DOOR,
			TILETYPE_WALL_RIGHT_DOOR, TILETYPE_WALL_LEFT_EXIT, TILETYPE_WALL_RIGHT_EXIT, TILETYPE_COLUMN, TILETYPE_SHADOW,
			TILETYPE_TREE, TILETYPE_ROOF, TILETYPE_LEFT_WALL_DOWN, TILETYPE_RIGHT_WALL_DOWN, TILETYPE_FULL_WALL_DOWN
		);
		// The linked tile data is always a wall (floors would be remapped with an invalid index)
		const auto tile_data_type = GENERATE(
			TILETYPE_WALL_LEFT, TILETYPE_WALL_RIGHT, TILETYPE_WALL_TOP_CORNER_RIGHT, TILETYPE_WALL_TOP_CORNER_LEFT,
			TILETYPE_WALL_TOP_RIGHT, TILETYPE_WALL_BOTTOM_LEFT, TILETYPE_WALL_BOTTOM_RIGHT, TILETYPE_WALL_LEFT_DOOR,
			TILETYPE_WALL_RIGHT_DOOR, TILETYPE_COLUMN, TILETYPE_SHADOW, TILETYPE_TREE
		);
		const auto layer_above = GENERATE(true, false);

		SUBCASE("")
		{
			// Input data
			const auto room1_x = random_unsigned_integer(0, 1000);
			const auto room1_y = random_unsigned_integer(0, 1000);
			const auto room2_x = random_unsigned_integer(0, 1000);
			const auto room2_y = random_unsigned_integer(0, 1000);
			const auto tile_x = random_unsigned_integer(0, 7);
			const auto tile_y = random_unsigned_integer(0, 7);
			const auto tile_data_flags = random_unsigned_integer();
			const auto next_tile_data_flags = random_unsigned_integer();
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);

			D2C_PackedTileInformation nTileInformation{ random_unsigned_integer() };
			nTileInformation.bLayerAbove = layer_above;

			D2DrlgRoomStrc moo_pDrlgRoom1{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pWallTiles[2]{};
			D2DrlgRoomStrc moo_pDrlgRoom2{};
			D2DrlgTileDataStrc moo_pTileData{};
			D2DrlgTileDataStrc moo_pNextTileData{};
			D2TileLibraryHashStrc moo_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc moo_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc moo_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2DrlgRoomStrc original_pDrlgRoom1{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pWallTiles[2]{};
			D2DrlgRoomStrc original_pDrlgRoom2{};
			D2DrlgTileDataStrc original_pTileData{};
			D2DrlgTileDataStrc original_pNextTileData{};
			D2TileLibraryHashStrc original_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc original_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc original_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			int nTileType = tile_type;
			uint32_t nPackedTileInformation = nTileInformation.nPackedValue;
			// Coordinates on the borders of the rooms are handled differently
			int nX = (random_unsigned_integer(0, 1) ? room1_x : room2_x) + random_unsigned_integer(0, 1);
			int nY = (random_unsigned_integer(0, 1) ? room1_y : room2_y) + random_unsigned_integer(0, 1);

			const auto setup_data = [tile_data_type, room1_x, room1_y, room2_x, room2_y, tile_x, tile_y, tile_data_flags, next_tile_data_flags, tile_flags](
				D2DrlgRoomStrc& pDrlgRoom1,
				D2DrlgLevelStrc& pLevel,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc (&pWallTiles)[2],
				D2DrlgRoomStrc& pDrlgRoom2,
				D2DrlgTileDataStrc& pTileData,
				D2DrlgTileDataStrc& pNextTileData,
				D2TileLibraryHashStrc& pTileLibraryHash,
				D2TileLibraryHashNodeStrc& pTileLibraryHashNode,
				D2TileLibraryHashRefStrc& pTileLibraryHashRef,
				D2TileLibraryEntryStrc& pTileLibraryEntry
			) {
				// Every lookup falls back to this tile
				pTileLibraryEntry.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryEntry.nRarity_Frame = 1;
				pTileLibraryEntry.nFlags = tile_flags;
				pTileLibraryHashRef.pTile = &pTileLibraryEntry;
				pTileLibraryHashNode.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryHashNode.pRef = &pTileLibraryHashRef;
				std::fill(std::begin(pTileLibraryHash.pNodes), std::end(pTileLibraryHash.pNodes), &pTileLibraryHashNode);

				// Hidden when the TILETYPE_WALL_TOP_CORNER_RIGHT tile data gets remapped
				pNextTileData.dwFlags = next_tile_data_flags;

				pTileData.nPosX = tile_x;
				pTileData.nPosY = tile_y;
				pTileData.nTileType = tile_data_type;
				pTileData.dwFlags = tile_data_flags;
				pTileData.pTile = &pTileLibraryEntry;
				pTileData.unk0x20 = &pNextTileData;

				// Added when the tile data gets remapped to TILETYPE_WALL_TOP_CORNER_RIGHT
				pTileGrid.pTiles.pWallTiles = pWallTiles;
				pTileGrid.pTiles.nWalls = 2;

				// Doors look up preset units of the level, the Rogue Encampment doesn't have any
				pLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;

				pDrlgRoom1.pLevel = &pLevel;
				pDrlgRoom1.nTileXPos = room1_x;
				pDrlgRoom1.nTileYPos = room1_y;
				pDrlgRoom1.nTileWidth = 8;
				pDrlgRoom1.nTileHeight = 8;
				pDrlgRoom1.pTileGrid = &pTileGrid;
				pDrlgRoom1.pTiles[0] = &pTileLibraryHash;

				pDrlgRoom2.nTileXPos = room2_x;
				pDrlgRoom2.nTileYPos = room2_y;
				pDrlgRoom2.nTileWidth = 8;
				pDrlgRoom2.nTileHeight = 8;
				pDrlgRoom2.pTiles[0] = &pTileLibraryHash;
			};

			setup_data(moo_pDrlgRoom1, moo_pLevel, moo_pTileGrid, moo_pWallTiles, moo_pDrlgRoom2, moo_pTileData, moo_pNextTileData, moo_pTileLibraryHash, moo_pTileLibraryHashNode, moo_pTileLibraryHashRef, moo_pTileLibraryEntry);
			setup_data(original_pDrlgRoom1, original_pLevel, original_pTileGrid, original_pWallTiles, original_pDrlgRoom2, original_pTileData, original_pNextTileData, original_pTileLibraryHash, original_pTileLibraryHashNode, original_pTileLibraryHashRef, original_pTileLibraryEntry);

			// Call both implementations
			sut(nullptr, &moo_pDrlgRoom1, &moo_pDrlgRoom2, &moo_pTileData, nTileType, nPackedTileInformation, nX, nY);
			original(nullptr, &original_pDrlgRoom1, &original_pDrlgRoom2, &original_pTileData, nTileType, nPackedTileInformation, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom1, original_pDrlgRoom1, "Comparing pDrlgRoom1");
			MOO_CHECK_EQ(moo_pDrlgRoom2, original_pDrlgRoom2, "Comparing pDrlgRoom2");
			MOO_CHECK_EQ(moo_pTileData, original_pTileData, "Comparing pTileData");
			MOO_CHECK_EQ(moo_pTileGrid.nWalls, original_pTileGrid.nWalls, "Comparing pTileGrid.nWalls");
			MOO_CHECK_EQ(moo_pWallTiles[0], original_pWallTiles[0], "Comparing pWallTiles[0]");
			MOO_CHECK_EQ(moo_pWallTiles[1], original_pWallTiles[1], "Comparing pWallTiles[1]");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD89CC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_GetCreateLinkedTileData, dll_base + 0x00049CC0);

		// Doors and exits are excluded, as they require preset units and warps
		const auto tile_type = GENERATE(
			TILETYPE_FLOOR, TILETYPE_WALL_LEFT, TILETYPE_WALL_RIGHT, TILETYPE_WALL_TOP_CORNER_RIGHT, TILETYPE_WALL_TOP_CORNER_LEFT,
			TILETYPE_WALL_TOP_RIGHT, TILETYPE_WALL_BOTTOM_LEFT, TILETYPE_WALL_BOTTOM_RIGHT, TILETYPE_COLUMN, TILETYPE_SHADOW,
			TILETYPE_TREE, TILETYPE_ROOF
		);
		const auto link_floor = GENERATE(TRUE, FALSE);
		const auto same_position = GENERATE(true, false);

		REPEAT_5();
		
		SUBCASE("")
		{
			// Linked wall tile data of the near room (TILETYPE_WALL_TOP_CORNER_RIGHT would require a second linked tile data)
			constexpr int near_wall_tile_types[] = {
				TILETYPE_WALL_LEFT, TILETYPE_WALL_RIGHT, TILETYPE_WALL_TOP_CORNER_LEFT, TILETYPE_WALL_TOP_RIGHT,
				TILETYPE_WALL_BOTTOM_LEFT, TILETYPE_WALL_BOTTOM_RIGHT, TILETYPE_COLUMN, TILETYPE_SHADOW, TILETYPE_TREE
			};

			// Input data
			const auto room_x = random_unsigned_integer(8, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto tile_x = random_unsigned_integer(0, 7);
			const auto tile_y = random_unsigned_integer(0, 7);
			const auto near_tile_type = link_floor ? TILETYPE_FLOOR : near_wall_tile_types[random_unsigned_integer(0, (uint32_t)std::size(near_wall_tile_types) - 1)];
			const auto tile_flags = random_unsigned_integer(0, 0xFFFF);

			D2C_PackedTileInformation nTileInformation{ random_unsigned_integer() };

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pWallTiles[2]{};
			D2DrlgTileDataStrc moo_pFloorTiles[1]{};
			D2DrlgTileDataStrc moo_pRoofTiles[1]{};
			D2DrlgRoomStrc* moo_ppRoomsNear[2]{};
			D2DrlgRoomStrc moo_pNearDrlgRoom{};
			D2DrlgTileGridStrc moo_pNearTileGrid{};
			D2DrlgTileLinkStrc moo_pNearTileLink{};
			D2DrlgTileDataStrc moo_pNearTileData{};
			D2TileLibraryHashStrc moo_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc moo_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc moo_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pWallTiles[2]{};
			D2DrlgTileDataStrc original_pFloorTiles[1]{};
			D2DrlgTileDataStrc original_pRoofTiles[1]{};
			D2DrlgRoomStrc* original_ppRoomsNear[2]{};
			D2DrlgRoomStrc original_pNearDrlgRoom{};
			D2DrlgTileGridStrc original_pNearTileGrid{};
			D2DrlgTileLinkStrc original_pNearTileLink{};
			D2DrlgTileDataStrc original_pNearTileData{};
			D2TileLibraryHashStrc original_pTileLibraryHash{};
			D2TileLibraryHashNodeStrc original_pTileLibraryHashNode{};
			D2TileLibraryHashRefStrc original_pTileLibraryHashRef{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			int nTileType = tile_type;
			uint32_t nPackedTileInformation = nTileInformation.nPackedValue;
			// The near room is located directly left of the room
			int nX = room_x - 8 + (same_position ? tile_x : tile_x + 1);
			int nY = room_y + tile_y;

			const auto setup_data = [link_floor, room_x, room_y, tile_x, tile_y, near_tile_type, tile_flags](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc (&pWallTiles)[2],
				D2DrlgTileDataStrc (&pFloorTiles)[1],
				D2DrlgTileDataStrc (&pRoofTiles)[1],
				D2DrlgRoomStrc* (&ppRoomsNear)[2],
				D2DrlgRoomStrc& pNearDrlgRoom,
				D2DrlgTileGridStrc& pNearTileGrid,
				D2DrlgTileLinkStrc& pNearTileLink,
				D2DrlgTileDataStrc& pNearTileData,
				D2TileLibraryHashStrc& pTileLibraryHash,
				D2TileLibraryHashNodeStrc& pTileLibraryHashNode,
				D2TileLibraryHashRefStrc& pTileLibraryHashRef,
				D2TileLibraryEntryStrc& pTileLibraryEntry
			) {
				// Every lookup falls back to this tile
				pTileLibraryEntry.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryEntry.nRarity_Frame = 1;
				pTileLibraryEntry.nFlags = tile_flags;
				pTileLibraryHashRef.pTile = &pTileLibraryEntry;
				pTileLibraryHashNode.nType = TILETYPE_WALL_LEFT_EXIT;
				pTileLibraryHashNode.pRef = &pTileLibraryHashRef;
				std::fill(std::begin(pTileLibraryHash.pNodes), std::end(pTileLibraryHash.pNodes), &pTileLibraryHashNode);

				pNearTileData.nPosX = tile_x;
				pNearTileData.nPosY = tile_y;
				pNearTileData.nTileType = near_tile_type;
				pNearTileData.pTile = &pTileLibraryEntry;

				pNearTileLink.bFloor = link_floor;
				pNearTileLink.pMapTile = &pNearTileData;

				pNearTileGrid.pMapLinks = &pNearTileLink;

				pNearDrlgRoom.nTileXPos = room_x - 8;
				pNearDrlgRoom.nTileYPos = room_y;
				pNearDrlgRoom.nTileWidth = 8;
				pNearDrlgRoom.nTileHeight = 8;
				pNearDrlgRoom.pTileGrid = &pNearTileGrid;
				pNearDrlgRoom.pTiles[0] = &pTileLibraryHash;

				// The room itself is part of its near rooms, but is skipped
				ppRoomsNear[0] = &pDrlgRoom;
				ppRoomsNear[1] = &pNearDrlgRoom;

				// Used if no linked tile data is found in the near rooms
				pTileGrid.pTiles.pWallTiles = pWallTiles;
				pTileGrid.pTiles.nWalls = 2;
				pTileGrid.pTiles.pFloorTiles = pFloorTiles;
				pTileGrid.pTiles.nFloors = 1;
				pTileGrid.pTiles.pRoofTiles = pRoofTiles;
				pTileGrid.pTiles.nRoofs = 1;

				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.pTileGrid = &pTileGrid;
				pDrlgRoom.pTiles[0] = &pTileLibraryHash;
				pDrlgRoom.ppRoomsNear = ppRoomsNear;
				pDrlgRoom.nRoomsNear = 2;
			};

			setup_data(moo_pDrlgRoom, moo_pTileGrid, moo_pWallTiles, moo_pFloorTiles, moo_pRoofTiles, moo_ppRoomsNear, moo_pNearDrlgRoom, moo_pNearTileGrid, moo_pNearTileLink, moo_pNearTileData, moo_pTileLibraryHash, moo_pTileLibraryHashNode, moo_pTileLibraryHashRef, moo_pTileLibraryEntry);
			setup_data(original_pDrlgRoom, original_pTileGrid, original_pWallTiles, original_pFloorTiles, original_pRoofTiles, original_ppRoomsNear, original_pNearDrlgRoom, original_pNearTileGrid, original_pNearTileLink, original_pNearTileData, original_pTileLibraryHash, original_pTileLibraryHashNode, original_pTileLibraryHashRef, original_pTileLibraryEntry);

			// Call both implementations
			sut(nullptr, &moo_pDrlgRoom, nTileType, nPackedTileInformation, nX, nY);
			original(nullptr, &original_pDrlgRoom, nTileType, nPackedTileInformation, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pNearTileData, original_pNearTileData, "Comparing pNearTileData");
			MOO_CHECK_EQ(moo_pTileGrid.nWalls, original_pTileGrid.nWalls, "Comparing pTileGrid.nWalls");
			MOO_CHECK_EQ(moo_pTileGrid.nFloors, original_pTileGrid.nFloors, "Comparing pTileGrid.nFloors");
			MOO_CHECK_EQ(moo_pTileGrid.nShadows, original_pTileGrid.nShadows, "Comparing pTileGrid.nShadows");
			MOO_CHECK_EQ(moo_pWallTiles[0], original_pWallTiles[0], "Comparing pWallTiles[0]");
			MOO_CHECK_EQ(moo_pWallTiles[1], original_pWallTiles[1], "Comparing pWallTiles[1]");
			MOO_CHECK_EQ(moo_pFloorTiles[0], original_pFloorTiles[0], "Comparing pFloorTiles[0]");
			MOO_CHECK_EQ(moo_pRoofTiles[0], original_pRoofTiles[0], "Comparing pRoofTiles[0]");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD89E30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_CountAllTileTypes, dll_base + 0x00049E30);

		const auto check_coordinates_validity = GENERATE(TRUE, FALSE);
		const auto kill_edge_x = GENERATE(TRUE, FALSE);
		const auto kill_edge_y = GENERATE(TRUE, FALSE);

		REPEAT_5();
		
		SUBCASE("")
		{
			constexpr int nMaxRoomSize = 8;
			constexpr int nMaxGridSize = nMaxRoomSize + 1;
			constexpr int nMaxCells = nMaxGridSize * nMaxGridSize;

			// Input data
			const auto room_x = random_unsigned_integer(0, 1000);
			const auto room_y = random_unsigned_integer(0, 1000);
			const auto room_width = random_unsigned_integer(1, nMaxRoomSize);
			const auto room_height = random_unsigned_integer(1, nMaxRoomSize);
			const auto walls = random_unsigned_integer(0, 100);
			const auto floors = random_unsigned_integer(0, 100);
			const auto roofs = random_unsigned_integer(0, 100);

			std::array<int, nMaxCells> packed_tile_informations{};
			for (auto& packed_tile_information : packed_tile_informations)
			{
				packed_tile_information = random_unsigned_integer();
			}

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgGridStrc moo_pTileInfoGrid{};
			int moo_pTileInfoGridCells[nMaxCells]{};
			int moo_pTileInfoGridRowOffsets[nMaxGridSize]{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgGridStrc original_pTileInfoGrid{};
			int original_pTileInfoGridCells[nMaxCells]{};
			int original_pTileInfoGridRowOffsets[nMaxGridSize]{};
			BOOL bCheckCoordinatesValidity = check_coordinates_validity;
			BOOL bKillEdgeX = kill_edge_x;
			BOOL bKillEdgeY = kill_edge_y;

			const auto setup_data = [nMaxGridSize, room_x, room_y, room_width, room_height, walls, floors, roofs, &packed_tile_informations](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgGridStrc& pTileInfoGrid,
				int (&pTileInfoGridCells)[nMaxCells],
				int (&pTileInfoGridRowOffsets)[nMaxGridSize]
			) {
				std::copy(packed_tile_informations.begin(), packed_tile_informations.end(), pTileInfoGridCells);
				for (int i = 0; i < nMaxGridSize; ++i)
				{
					pTileInfoGridRowOffsets[i] = i * (room_width + 1);
				}

				pTileInfoGrid.pCellsFlags = pTileInfoGridCells;
				pTileInfoGrid.pCellsRowOffsets = pTileInfoGridRowOffsets;
				pTileInfoGrid.nWidth = room_width + 1;
				pTileInfoGrid.nHeight = room_height + 1;

				pTileGrid.pTiles.nWalls = walls;
				pTileGrid.pTiles.nFloors = floors;
				pTileGrid.pTiles.nRoofs = roofs;

				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = room_width;
				pDrlgRoom.nTileHeight = room_height;
				pDrlgRoom.pTileGrid = &pTileGrid;
			};

			setup_data(moo_pDrlgRoom, moo_pTileGrid, moo_pTileInfoGrid, moo_pTileInfoGridCells, moo_pTileInfoGridRowOffsets);
			setup_data(original_pDrlgRoom, original_pTileGrid, original_pTileInfoGrid, original_pTileInfoGridCells, original_pTileInfoGridRowOffsets);

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_pTileInfoGrid, bCheckCoordinatesValidity, bKillEdgeX, bKillEdgeY);
			original(&original_pDrlgRoom, &original_pTileInfoGrid, bCheckCoordinatesValidity, bKillEdgeX, bKillEdgeY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pTileInfoGrid, original_pTileInfoGrid, "Comparing pTileInfoGrid");
			MOO_CHECK_EQ(moo_pTileGrid.pTiles.nWalls, original_pTileGrid.pTiles.nWalls, "Comparing pTileGrid.pTiles.nWalls");
			MOO_CHECK_EQ(moo_pTileGrid.pTiles.nFloors, original_pTileGrid.pTiles.nFloors, "Comparing pTileGrid.pTiles.nFloors");
			MOO_CHECK_EQ(moo_pTileGrid.pTiles.nRoofs, original_pTileGrid.pTiles.nRoofs, "Comparing pTileGrid.pTiles.nRoofs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD89F00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_CountWallWarpTiles, dll_base + 0x00049F00);

		const auto kill_edge_x = GENERATE(TRUE, FALSE);
		const auto kill_edge_y = GENERATE(TRUE, FALSE);

		REPEAT_10();
		
		SUBCASE("")
		{
			constexpr int nMaxRoomSize = 8;
			constexpr int nMaxGridSize = nMaxRoomSize + 1;
			constexpr int nMaxCells = nMaxGridSize * nMaxGridSize;

			// Input data
			const auto room_width = random_unsigned_integer(1, nMaxRoomSize);
			const auto room_height = random_unsigned_integer(1, nMaxRoomSize);
			const auto walls = random_unsigned_integer(0, 100);
			const auto floors = random_unsigned_integer(0, 100);

			std::array<int, nMaxCells> packed_tile_informations{};
			std::array<int, nMaxCells> tile_types{};
			for (int i = 0; i < nMaxCells; ++i)
			{
				packed_tile_informations[i] = random_unsigned_integer();
				tile_types[i] = random_unsigned_integer(TILETYPE_FLOOR, TILETYPE_FRONT_WALL_DOWN);
			}

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgGridStrc moo_pTileInfoGrid{};
			int moo_pTileInfoGridCells[nMaxCells]{};
			int moo_pTileInfoGridRowOffsets[nMaxGridSize]{};
			D2DrlgGridStrc moo_pTileTypeGrid{};
			int moo_pTileTypeGridCells[nMaxCells]{};
			int moo_pTileTypeGridRowOffsets[nMaxGridSize]{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgGridStrc original_pTileInfoGrid{};
			int original_pTileInfoGridCells[nMaxCells]{};
			int original_pTileInfoGridRowOffsets[nMaxGridSize]{};
			D2DrlgGridStrc original_pTileTypeGrid{};
			int original_pTileTypeGridCells[nMaxCells]{};
			int original_pTileTypeGridRowOffsets[nMaxGridSize]{};
			BOOL bKillEdgeX = kill_edge_x;
			BOOL bKillEdgeY = kill_edge_y;

			const auto setup_data = [nMaxGridSize, room_width, room_height, walls, floors, &packed_tile_informations, &tile_types](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgGridStrc& pTileInfoGrid,
				int (&pTileInfoGridCells)[nMaxCells],
				int (&pTileInfoGridRowOffsets)[nMaxGridSize],
				D2DrlgGridStrc& pTileTypeGrid,
				int (&pTileTypeGridCells)[nMaxCells],
				int (&pTileTypeGridRowOffsets)[nMaxGridSize]
			) {
				std::copy(packed_tile_informations.begin(), packed_tile_informations.end(), pTileInfoGridCells);
				std::copy(tile_types.begin(), tile_types.end(), pTileTypeGridCells);
				for (int i = 0; i < nMaxGridSize; ++i)
				{
					pTileInfoGridRowOffsets[i] = i * (room_width + 1);
					pTileTypeGridRowOffsets[i] = i * (room_width + 1);
				}

				pTileInfoGrid.pCellsFlags = pTileInfoGridCells;
				pTileInfoGrid.pCellsRowOffsets = pTileInfoGridRowOffsets;
				pTileInfoGrid.nWidth = room_width + 1;
				pTileInfoGrid.nHeight = room_height + 1;

				pTileTypeGrid.pCellsFlags = pTileTypeGridCells;
				pTileTypeGrid.pCellsRowOffsets = pTileTypeGridRowOffsets;
				pTileTypeGrid.nWidth = room_width + 1;
				pTileTypeGrid.nHeight = room_height + 1;

				pTileGrid.pTiles.nWalls = walls;
				pTileGrid.pTiles.nFloors = floors;

				pDrlgRoom.nTileWidth = room_width;
				pDrlgRoom.nTileHeight = room_height;
				pDrlgRoom.pTileGrid = &pTileGrid;
			};

			setup_data(moo_pDrlgRoom, moo_pTileGrid, moo_pTileInfoGrid, moo_pTileInfoGridCells, moo_pTileInfoGridRowOffsets, moo_pTileTypeGrid, moo_pTileTypeGridCells, moo_pTileTypeGridRowOffsets);
			setup_data(original_pDrlgRoom, original_pTileGrid, original_pTileInfoGrid, original_pTileInfoGridCells, original_pTileInfoGridRowOffsets, original_pTileTypeGrid, original_pTileTypeGridCells, original_pTileTypeGridRowOffsets);

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_pTileInfoGrid, &moo_pTileTypeGrid, bKillEdgeX, bKillEdgeY);
			original(&original_pDrlgRoom, &original_pTileInfoGrid, &original_pTileTypeGrid, bKillEdgeX, bKillEdgeY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pTileInfoGrid, original_pTileInfoGrid, "Comparing pTileInfoGrid");
			MOO_CHECK_EQ(moo_pTileTypeGrid, original_pTileTypeGrid, "Comparing pTileTypeGrid");
			MOO_CHECK_EQ(moo_pTileGrid.pTiles.nWalls, original_pTileGrid.pTiles.nWalls, "Comparing pTileGrid.pTiles.nWalls");
			MOO_CHECK_EQ(moo_pTileGrid.pTiles.nFloors, original_pTileGrid.pTiles.nFloors, "Comparing pTileGrid.pTiles.nFloors");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD89FA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_InitRoomGrids, dll_base + 0x00049FA0);

		REPEAT_20();
		
		SUBCASE("")
		{
			// Input data
			const auto init_seed = random_unsigned_integer();
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [init_seed, low_seed, high_seed](
				D2DrlgRoomStrc& pDrlgRoom
			) {
				// Maze and preset rooms require their whole level to be generated, so only the seed initialization is tested
				pDrlgRoom.nType = DRLGTYPE_OUTDOOR;
				pDrlgRoom.dwInitSeed = init_seed;
				pDrlgRoom.pSeed.nLowSeed = low_seed;
				pDrlgRoom.pSeed.nHighSeed = high_seed;
			};

			setup_data(moo_pDrlgRoom);
			setup_data(original_pDrlgRoom);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD89FD0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_AddRoomMapTiles, dll_base + 0x00049FD0);

		REPEAT_20();
		
		SUBCASE("")
		{
			// Input data
			const auto room_flags = random_unsigned_integer();

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [room_flags](
				D2DrlgRoomStrc& pDrlgRoom
			) {
				// Maze and preset rooms require their whole level to be generated, so only the flag update is tested
				pDrlgRoom.nType = DRLGTYPE_OUTDOOR;
				pDrlgRoom.dwFlags = room_flags;
			};

			setup_data(moo_pDrlgRoom);
			setup_data(original_pDrlgRoom);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8A010")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_AllocTileGrid, dll_base + 0x0004A010);

		const auto has_tile_grid = GENERATE(0, 1);
		
		SUBCASE("")
		{
			// Input data
			const auto shadows = random_unsigned_integer(0, 100);

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgTileGridStrc original_pTileGrid{};

			const auto setup_data = [has_tile_grid, shadows](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgTileGridStrc& pTileGrid
			) {
				pLevel.pDrlg = &pDrlg;
				pDrlgRoom.pLevel = &pLevel;

				if (has_tile_grid)
				{
					pTileGrid.nShadows = shadows;
					pDrlgRoom.pTileGrid = &pTileGrid;
				}
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pTileGrid);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_pTileGrid);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pDrlgRoom.pTileGrid->nShadows, original_pDrlgRoom.pTileGrid->nShadows, "Comparing pDrlgRoom.pTileGrid->nShadows");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8A050")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_AllocTileData, dll_base + 0x0004A050);

		const auto has_roof_tiles = GENERATE(0, 1);

		REPEAT_10();
		
		SUBCASE("")
		{
			// Input data
			const auto walls = random_unsigned_integer(0, 5);
			const auto floors = random_unsigned_integer(0, 5);
			const auto roofs = random_unsigned_integer(0, 5);

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pRoofTiles[5]{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pRoofTiles[5]{};

			const auto setup_data = [has_roof_tiles, walls, floors, roofs](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc (&pRoofTiles)[5]
			) {
				pTileGrid.pTiles.nWalls = walls;
				pTileGrid.pTiles.nFloors = floors;
				pTileGrid.pTiles.nRoofs = roofs;

				// Roof tiles may already have been allocated by DRLGROOMTILE_ReallocRoofTileGrid
				if (has_roof_tiles)
				{
					pRoofTiles[0].nTileType = TILETYPE_SHADOW;
					pTileGrid.pTiles.pRoofTiles = pRoofTiles;
				}

				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.pTileGrid = &pTileGrid;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pTileGrid, moo_pRoofTiles);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_pTileGrid, original_pRoofTiles);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pTileGrid.pTiles.pWallTiles, original_pTileGrid.pTiles.pWallTiles, "Comparing pTileGrid.pTiles.pWallTiles");
			MOO_CHECK_EQ(moo_pTileGrid.pTiles.pFloorTiles, original_pTileGrid.pTiles.pFloorTiles, "Comparing pTileGrid.pTiles.pFloorTiles");
			MOO_CHECK_EQ(moo_pTileGrid.pTiles.pRoofTiles, original_pTileGrid.pTiles.pRoofTiles, "Comparing pTileGrid.pTiles.pRoofTiles");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8A130")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_ReallocRoofTileGrid, dll_base + 0x0004A130);

		REPEAT_20();
		
		SUBCASE("")
		{
			// Input data
			const auto roofs = random_unsigned_integer(1, 10);
			const auto shadows = random_unsigned_integer(0, roofs);

			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileGridStrc original_pTileGrid{};
			int nAdditionalRoofs = random_unsigned_integer(0, 10);

			const auto setup_data = [roofs, shadows](
				D2DrlgTileGridStrc& pTileGrid
			) {
				// The roof tiles get reallocated, so they have to be allocated from the memory pool
				pTileGrid.pTiles.pRoofTiles = (D2DrlgTileDataStrc*)D2_CALLOC_POOL(nullptr, sizeof(D2DrlgTileDataStrc) * roofs);
				pTileGrid.pTiles.nRoofs = roofs;
				pTileGrid.nShadows = shadows;
			};

			setup_data(moo_pTileGrid);
			setup_data(original_pTileGrid);

			// Call both implementations
			sut(nullptr, &moo_pTileGrid, nAdditionalRoofs);
			original(nullptr, &original_pTileGrid, nAdditionalRoofs);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTileGrid, original_pTileGrid, "Comparing pTileGrid");
			MOO_CHECK_EQ(moo_pTileGrid.pTiles.nRoofs, original_pTileGrid.pTiles.nRoofs, "Comparing pTileGrid.pTiles.nRoofs");
			// Only the initially allocated roof tiles have defined values
			for (int i = 0; i < (int)roofs; ++i)
			{
				MOO_CHECK_EQ(moo_pTileGrid.pTiles.pRoofTiles[i], original_pTileGrid.pTiles.pRoofTiles[i], "Comparing pTileGrid.pTiles.pRoofTiles");
			}

			D2_FREE_POOL(nullptr, moo_pTileGrid.pTiles.pRoofTiles);
			D2_FREE_POOL(nullptr, original_pTileGrid.pTiles.pRoofTiles);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8A1B0 (#10017)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_GetNumberOfShadowsFromRoom, dll_base + 0x0004A1B0);

		REPEAT_10();
		
		SUBCASE("")
		{
			// Input data
			const auto shadows = random_unsigned_integer(0, 1000);

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileGridStrc original_pTileGrid{};

			const auto setup_data = [shadows](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileGridStrc& pTileGrid
			) {
				pTileGrid.nShadows = shadows;
				pDrlgRoom.pTileGrid = &pTileGrid;
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom, moo_pTileGrid);
			setup_data(original_pRoom, original_pDrlgRoom, original_pTileGrid);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8A1D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_FreeTileGrid, dll_base + 0x0004A1D0);

		const auto has_tile_grid = GENERATE(true, false);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [has_tile_grid](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				pLevel.pDrlg = &pDrlg;
				pDrlgRoom.pLevel = &pLevel;

				if (has_tile_grid)
				{
					// Everything gets freed, so it has to be allocated from the memory pool
					D2DrlgTileGridStrc* pTileGrid = D2_CALLOC_STRC_POOL(nullptr, D2DrlgTileGridStrc);
					pTileGrid->pTiles.pWallTiles = D2_CALLOC_STRC_POOL(nullptr, D2DrlgTileDataStrc);
					pTileGrid->pTiles.nWalls = 1;
					pTileGrid->pTiles.pFloorTiles = D2_CALLOC_STRC_POOL(nullptr, D2DrlgTileDataStrc);
					pTileGrid->pTiles.nFloors = 1;
					pTileGrid->pTiles.pRoofTiles = D2_CALLOC_STRC_POOL(nullptr, D2DrlgTileDataStrc);
					pTileGrid->pTiles.nRoofs = 1;

					pTileGrid->pMapLinks = D2_CALLOC_STRC_POOL(nullptr, D2DrlgTileLinkStrc);
					pTileGrid->pMapLinks->pNext = D2_CALLOC_STRC_POOL(nullptr, D2DrlgTileLinkStrc);

					pTileGrid->pAnimTiles = D2_CALLOC_STRC_POOL(nullptr, D2DrlgAnimTileGridStrc);
					pTileGrid->pAnimTiles->ppMapTileData = (D2DrlgTileDataStrc**)D2_CALLOC_POOL(nullptr, sizeof(D2DrlgTileDataStrc*));

					pDrlgRoom.pTileGrid = pTileGrid;
				}
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8A2E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_FreeRoom, dll_base + 0x0004A2E0);

		const auto has_room = GENERATE(0, 1);
		const auto keep_room = GENERATE(TRUE, FALSE);

		REPEAT_5();
		
		SUBCASE("")
		{
			// Input data
			const auto room_flags = random_unsigned_integer();
			const auto freed_rooms = random_unsigned_integer(0, 1000);

			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2RoomTileStrc moo_pRoomTile{};
			D2DrlgTileDataStrc moo_pWarpTileData{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2RoomTileStrc original_pRoomTile{};
			D2DrlgTileDataStrc original_pWarpTileData{};
			BOOL bKeepRoom = keep_room;

			const auto setup_data = [has_room, room_flags, freed_rooms](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2RoomTileStrc& pRoomTile,
				D2DrlgTileDataStrc& pWarpTileData
			) {
				pRoomTile.unk0x0C = &pWarpTileData;
				pRoomTile.unk0x10 = &pWarpTileData;

				pDrlg.nFreedRooms = freed_rooms;

				pLevel.pDrlg = &pDrlg;

				// Maze and preset rooms have additional data which would have to be freed
				pDrlgRoom.nType = DRLGTYPE_OUTDOOR;
				pDrlgRoom.dwFlags = has_room ? (room_flags | DRLGROOMFLAG_HAS_ROOM) : (room_flags & ~DRLGROOMFLAG_HAS_ROOM);
				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.pRoomTiles = &pRoomTile;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pRoomTile, moo_pWarpTileData);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_pRoomTile, original_pWarpTileData);

			// Call both implementations
			sut(&moo_pDrlgRoom, bKeepRoom);
			original(&original_pDrlgRoom, bKeepRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pDrlg.nFreedRooms, original_pDrlg.nFreedRooms, "Comparing pDrlg.nFreedRooms");
			MOO_CHECK_EQ(moo_pRoomTile.unk0x0C, original_pRoomTile.unk0x0C, "Comparing pRoomTile.unk0x0C");
			MOO_CHECK_EQ(moo_pRoomTile.unk0x10, original_pRoomTile.unk0x10, "Comparing pRoomTile.unk0x10");
		}
	}
	
	TEST_CASE_FIXTURE(LvlTypesTxtFixture<NoopFixture>, "D2Common.0x6FD8A380" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOMTILE_LoadDT1FilesForRoom, dll_base + 0x0004A380);
		
		SUBCASE("")
		{
			for (auto i = 0; i < lvltypes_record_count; ++i)
			{
				// Input data
				const auto room_flags = random_unsigned_integer();

				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgLevelStrc original_pLevel{};

				const auto setup_data = [i, room_flags](
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgLevelStrc& pLevel
				) {
					pLevel.nLevelType = i;

					pDrlgRoom.pLevel = &pLevel;
					pDrlgRoom.dwFlags = room_flags;
					// No tile files of the level type, only the global tile files get loaded
					pDrlgRoom.dwDT1Mask = 0;
				};

				setup_data(moo_pDrlgRoom, moo_pLevel);
				setup_data(original_pDrlgRoom, original_pLevel);

				// Call both implementations
				sut(&moo_pDrlgRoom);
				original(&original_pDrlgRoom);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			}
		}
	}
}

#endif
