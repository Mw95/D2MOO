#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2DataTbls.h>
#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgMaze.h>
#include <Drlg/D2DrlgPreset.h>

#include <Fixtures/DataTbls/Fixtures.h>


TEST_SUITE("D2DrlgMazeTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78E50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_GetFreeLocationForRoomEast, dll_base + 0x00038E50);

		SUBCASE("")
		{
			REPEAT_5()

			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};

			const auto setup_data = [level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CAVELEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_CAVE;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				// The top left room already has a map, so the bottom left room is expected
				pPresetRooms[0].dwFlags = DRLGPRESETROOMFLAG_HAS_MAP_DS1;

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel);
			const auto original_result = original(&original_pLevel);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78F70")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PickRoomPreset, dll_base + 0x00038F70);

		SUBCASE("")
		{
			const BOOL bResetFlag = GENERATE(FALSE, TRUE);
			const uint32_t maze_rooms = GENERATE(1, 10);

			const int level_types[] = {
				LVLTYPE_ACT1_CAVE,
				LVLTYPE_ACT1_CRYPT,
				LVLTYPE_ACT1_BARRACKS,
				LVLTYPE_ACT1_JAIL,
				LVLTYPE_ACT1_CATACOMBS,
				LVLTYPE_ACT2_SEWER,
				LVLTYPE_ACT2_HAREM,
				LVLTYPE_ACT2_BASEMENT,
				LVLTYPE_ACT2_TOMB,
				LVLTYPE_ACT2_LAIR,
				LVLTYPE_ACT2_ARCANE,
				LVLTYPE_ACT3_KURAST,
				LVLTYPE_ACT3_SPIDER,
				LVLTYPE_ACT3_DUNGEON,
				LVLTYPE_ACT3_SEWER,
				LVLTYPE_ACT4_LAVA,
				LVLTYPE_ACT5_ICE_CAVES,
				LVLTYPE_ACT5_TEMPLE,
				LVLTYPE_ACT5_BAAL,
				LVLTYPE_ACT5_LAVA,
			};

			// Level ids with special handling, and one without
			const int level_ids[] = {
				LEVEL_CAVELEV1,
				LEVEL_PALACECELLARLEV1,
				LEVEL_PALACECELLARLEV3,
				LEVEL_SPIDERCAVE,
				LEVEL_SPIDERCAVERN,
			};

			// Directions of the orths of the room: the 4 basic directions and a diagonal one that is ignored
			const int orth_directions[] = { ALTDIR_WEST, ALTDIR_NORTH, ALTDIR_EAST, ALTDIR_SOUTH, ALTDIR_NORTHWEST };

			for (const int level_type : level_types)
			{
				for (const int level_id : level_ids)
				{
					for (int orth_mask = 0; orth_mask < (1 << 5); ++orth_mask)
					{
						const auto preset_flags = random_unsigned_integer();

						// Input data
						D2DrlgRoomStrc moo_pDrlgRoom{};
						D2DrlgLevelStrc moo_pLevel{};
						D2DrlgStrc moo_pDrlg{};
						D2LvlMazeTxt moo_pMaze{};
						D2DrlgPresetRoomStrc moo_pPresetRoom{};
						D2DrlgOrthStrc moo_pDrlgOrths[5]{};
						D2DrlgRoomStrc original_pDrlgRoom{};
						D2DrlgLevelStrc original_pLevel{};
						D2DrlgStrc original_pDrlg{};
						D2LvlMazeTxt original_pMaze{};
						D2DrlgPresetRoomStrc original_pPresetRoom{};
						D2DrlgOrthStrc original_pDrlgOrths[5]{};

						const auto setup_data = [level_type, level_id, orth_mask, maze_rooms, preset_flags, &orth_directions](
							D2DrlgRoomStrc& pDrlgRoom,
							D2DrlgLevelStrc& pLevel,
							D2DrlgStrc& pDrlg,
							D2LvlMazeTxt& pMaze,
							D2DrlgPresetRoomStrc& pPresetRoom,
							D2DrlgOrthStrc (&pDrlgOrths)[5]
						) {
							// Only used by ice caves
							pDrlg.nDifficulty = 1;
							pMaze.dwRooms[1] = maze_rooms;

							pLevel.pDrlg = &pDrlg;
							pLevel.nLevelId = level_id;
							pLevel.nLevelType = level_type;
							pLevel.pMaze = &pMaze;

							pPresetRoom.dwFlags = preset_flags;

							pDrlgRoom.pLevel = &pLevel;
							pDrlgRoom.pMaze = &pPresetRoom;

							for (int i = 0; i < 5; ++i)
							{
								if (orth_mask & (1 << i))
								{
									pDrlgOrths[i].nDirection = orth_directions[i];
									pDrlgOrths[i].pNext = pDrlgRoom.pDrlgOrth;
									pDrlgRoom.pDrlgOrth = &pDrlgOrths[i];
								}
							}
						};

						setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pMaze, moo_pPresetRoom, moo_pDrlgOrths);
						setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_pMaze, original_pPresetRoom, original_pDrlgOrths);

						// Call both implementations
						sut(&moo_pDrlgRoom, bResetFlag);
						original(&original_pDrlgRoom, bResetFlag);

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD79240")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_GetFreeLocationForRoomWest, dll_base + 0x00039240);

		SUBCASE("")
		{
			REPEAT_5()

			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};

			const auto setup_data = [level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CAVELEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_CAVE;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				// The top right room already has a map, so the bottom right room is expected
				pPresetRooms[1].dwFlags = DRLGPRESETROOMFLAG_HAS_MAP_DS1;

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel);
			const auto original_result = original(&original_pLevel);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD79360")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_GetFreeLocationForRoomNorth, dll_base + 0x00039360);

		SUBCASE("")
		{
			REPEAT_5()

			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};

			const auto setup_data = [level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CAVELEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_CAVE;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				// The bottom left room already has a map, so the bottom right room is expected
				pPresetRooms[2].dwFlags = DRLGPRESETROOMFLAG_HAS_MAP_DS1;

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel);
			const auto original_result = original(&original_pLevel);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(LvlMazeTxtFixture<LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>>, "D2Common.0x6FD79480")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_InitLevelData, dll_base + 0x00039480);

		SUBCASE("")
		{
			const auto difficulty = GENERATE(0, 1, 2);

			for (int i = 0; i < lvlmaze_record_count; ++i)
			{
				const int level_id = lvlmaze_txt[i].dwLevelId;
				const int depend_level_id = leveldefs_txt[level_id].dwDepend;
				const int depend_pos_x = random_unsigned_integer(0, 1000);
				const int depend_pos_y = random_unsigned_integer(0, 1000);

				// Input data
				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgStrc moo_pDrlg{};
				D2DrlgLevelStrc moo_pDependLevel{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgStrc original_pDrlg{};
				D2DrlgLevelStrc original_pDependLevel{};

				const auto setup_data = [difficulty, level_id, depend_level_id, depend_pos_x, depend_pos_y](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgLevelStrc& pDependLevel
				) {
					pDrlg.nDifficulty = difficulty;

					// The position of a level depending on another level is relative to it
					pDependLevel.pDrlg = &pDrlg;
					pDependLevel.nLevelId = depend_level_id;
					pDependLevel.nPosX = depend_pos_x;
					pDependLevel.nPosY = depend_pos_y;
					pDrlg.pLevel = &pDependLevel;

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = level_id;
				};

				setup_data(moo_pLevel, moo_pDrlg, moo_pDependLevel);
				setup_data(original_pLevel, original_pDrlg, original_pDependLevel);

				// Call both implementations
				sut(&moo_pLevel);
				original(&original_pLevel);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD794A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_GenerateLevel, dll_base + 0x000394A0);

		SUBCASE("")
		{
			// Act 4 lava mazes only consist of basic lava presets.
			// Those must not need any DS1 file to be loaded when building the preset areas.
			for (int level_prest = LVLPREST_ACT4_LAVA_X + 1; level_prest < LVLPREST_ACT4_LAVA_X + 16; ++level_prest)
			{
				REQUIRE(lvlprest_txt[level_prest].dwScan == 0);
				REQUIRE(lvlprest_txt[level_prest].dwPops == 0);
			}

			const auto difficulty = GENERATE(0, 1, 2);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pWarp{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pWarp{};
			D2LvlMazeTxt original_pMaze{};

			const auto setup_data = [difficulty, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pWarp,
				D2LvlMazeTxt& pMaze
			) {
				// A lava maze level which is not the River of Flame, which would need the Chaos Sanctum level
				const int level_id = LEVEL_CITYOFTHEDAMNED;

				// Level without any vis, so that building the preset areas does not need any warp
				pWarp.nLevel = level_id;

				pDrlg.nDifficulty = difficulty;
				pDrlg.pWarp = &pWarp;

				pMaze.dwRooms[0] = 8;
				pMaze.dwRooms[1] = 12;
				pMaze.dwRooms[2] = 16;
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;
				pMaze.dwMerge = 500;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nLevelType = LVLTYPE_ACT4_LAVA;
				pLevel.pSeed.nLowSeed = level_seed;
				pLevel.pMaze = &pMaze;

				// Big enough for all the rooms of the maze
				pLevel.nPosX = 0;
				pLevel.nPosY = 0;
				pLevel.nWidth = 512;
				pLevel.nHeight = 512;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pWarp, moo_pMaze);
			setup_data(original_pLevel, original_pDrlg, original_pWarp, original_pMaze);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD79E10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_SetPickedFileAndPresetId, dll_base + 0x00039E10);

		SUBCASE("")
		{
			const auto preset_flags = random_unsigned_integer();

			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgPresetRoomStrc moo_pPresetRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgPresetRoomStrc original_pPresetRoom{};
			int nLevelPrest = random_unsigned_integer(1, 1000);
			int nPickedFile = static_cast<int>(random_unsigned_integer(0, 4)) - 1;
			BOOL bResetFlag = GENERATE(FALSE, TRUE);

			const auto setup_data = [preset_flags](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgPresetRoomStrc& pPresetRoom
			) {
				pPresetRoom.dwFlags = preset_flags;
				pDrlgRoom.pMaze = &pPresetRoom;
			};

			setup_data(moo_pDrlgRoom, moo_pPresetRoom);
			setup_data(original_pDrlgRoom, original_pPresetRoom);

			// Call both implementations
			sut(&moo_pDrlgRoom, nLevelPrest, nPickedFile, bResetFlag);
			original(&original_pDrlgRoom, nLevelPrest, nPickedFile, bResetFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Commo.0x6FD79E40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_ReplaceRoomPreset, dll_base + 0x00039E40);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};
			// The first matching room already has a map, so only the second matching room may be replaced
			int nLevelPrestId1 = GENERATE(LVLPREST_ACT2_SEWER_N, LVLPREST_ACT2_SEWER_E, LVLPREST_ACT2_SEWER_W);
			int nLevelPrestId2 = LVLPREST_ACT2_SEWER_NEXT_N;
			int nPickedFile = GENERATE(-1, 0);
			BOOL bResetFlag = GENERATE(FALSE, TRUE);

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				const int level_prests[4] = { LVLPREST_ACT2_SEWER_N, LVLPREST_ACT2_SEWER_E, LVLPREST_ACT2_SEWER_N, LVLPREST_ACT2_SEWER_S };

				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = level_prests[i];
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				pPresetRooms[0].dwFlags = DRLGPRESETROOMFLAG_HAS_MAP_DS1;

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pRooms, original_pPresetRooms);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, nLevelPrestId1, nLevelPrestId2, nPickedFile, bResetFlag);
			const auto original_result = original(&original_pLevel, nLevelPrestId1, nLevelPrestId2, nPickedFile, bResetFlag);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD79EA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_AddAdjacentMazeRoom, dll_base + 0x00039EA0);

		SUBCASE("")
		{
			const auto level_seed = random_unsigned_integer();
			const auto room_seed = random_unsigned_integer();

			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgPresetRoomStrc moo_pPresetRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[3]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[3]{};
			D2DrlgOrthStrc moo_pDrlgOrth{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgPresetRoomStrc original_pPresetRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[3]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[3]{};
			D2DrlgOrthStrc original_pDrlgOrth{};
			int nDirection = GENERATE(0, 1, 2, 3, 4, 5, 6, 7);
			int bMergeRooms = GENERATE(FALSE, TRUE);

			const auto setup_data = [level_seed, room_seed](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgPresetRoomStrc& pPresetRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[3],
				D2DrlgPresetRoomStrc (&pPresetRooms)[3],
				D2DrlgOrthStrc& pDrlgOrth
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;
				pMaze.dwMerge = 500;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CAVELEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_CAVE;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = 8;
				pDrlgRoom.nTileYPos = 8;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.nType = DRLGTYPE_PRESET;
				pDrlgRoom.pMaze = &pPresetRoom;
				pDrlgRoom.pSeed.nLowSeed = room_seed;

				// Other rooms of the level: east, north west and south east (with a map) of the room
				const int room_positions[3][2] = { { 16, 8 }, { 0, 0 }, { 16, 16 } };
				for (int i = 0; i < 3; ++i)
				{
					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = room_positions[i][0];
					pRooms[i].nTileYPos = room_positions[i][1];
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pSeed.nLowSeed = room_seed + i + 1;
					pRooms[i].pDrlgRoomNext = (i + 1 < 3) ? &pRooms[i + 1] : nullptr;
				}
				pPresetRooms[2].dwFlags = DRLGPRESETROOMFLAG_HAS_MAP_DS1;

				// The room is already connected to the room east of it
				pDrlgOrth.pDrlgRoom = &pRooms[0];
				pDrlgOrth.nDirection = ALTDIR_EAST;
				pDrlgOrth.bInit = TRUE;
				pDrlgOrth.pBox = &pRooms[0].pDrlgCoord;
				pDrlgRoom.pDrlgOrth = &pDrlgOrth;

				pDrlgRoom.pDrlgRoomNext = &pRooms[0];
				pLevel.pFirstRoomEx = &pDrlgRoom;
				pLevel.nRooms = 4;
			};

			setup_data(moo_pDrlgRoom, moo_pPresetRoom, moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms, moo_pDrlgOrth);
			setup_data(original_pDrlgRoom, original_pPresetRoom, original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms, original_pDrlgOrth);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nDirection, bMergeRooms);
			const auto original_result = original(&original_pDrlgRoom, nDirection, bMergeRooms);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7A110")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_InitBasicMazeLayout, dll_base + 0x0003A110);

		SUBCASE("")
		{
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pFirstRoomEx{};
			D2DrlgPresetRoomStrc moo_pPresetRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pFirstRoomEx{};
			D2DrlgPresetRoomStrc original_pPresetRoom{};
			int nRoomsPerDirection = GENERATE(2, 3, 4, 5);

			const auto setup_data = [level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc& pFirstRoomEx,
				D2DrlgPresetRoomStrc& pPresetRoom
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;
				pMaze.dwMerge = 500;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_JAILLEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_JAIL;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				pFirstRoomEx.pLevel = &pLevel;
				pFirstRoomEx.nTileXPos = 64;
				pFirstRoomEx.nTileYPos = 64;
				pFirstRoomEx.nTileWidth = 8;
				pFirstRoomEx.nTileHeight = 8;
				pFirstRoomEx.nType = DRLGTYPE_PRESET;
				pFirstRoomEx.pMaze = &pPresetRoom;

				pLevel.pFirstRoomEx = &pFirstRoomEx;
				pLevel.nRooms = 1;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pFirstRoomEx, moo_pPresetRoom);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pFirstRoomEx, original_pPresetRoom);

			// Call both implementations
			sut(&moo_pLevel, nRoomsPerDirection);
			original(&original_pLevel, nRoomsPerDirection);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7A340")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_LinkMazeRooms, dll_base + 0x0003A340);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom1{};
			D2DrlgRoomStrc moo_pDrlgRoom2{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pBlockingRoom{};
			D2DrlgOrthStrc moo_pDrlgOrth{};
			D2DrlgCoordStrc moo_pOrthBox{};
			D2DrlgRoomStrc original_pDrlgRoom1{};
			D2DrlgRoomStrc original_pDrlgRoom2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pBlockingRoom{};
			D2DrlgOrthStrc original_pDrlgOrth{};
			D2DrlgCoordStrc original_pOrthBox{};
			int nDirection = GENERATE(0, 1, 2, 3, 4, 5, 6, 7);

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom1,
				D2DrlgRoomStrc& pDrlgRoom2,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pBlockingRoom,
				D2DrlgOrthStrc& pDrlgOrth,
				D2DrlgCoordStrc& pOrthBox
			) {
				// The room to link, not added to the level yet
				pDrlgRoom1.pLevel = &pLevel;
				pDrlgRoom1.nTileWidth = 8;
				pDrlgRoom1.nTileHeight = 8;

				pDrlgRoom2.pLevel = &pLevel;
				pDrlgRoom2.nTileXPos = 8;
				pDrlgRoom2.nTileYPos = 8;
				pDrlgRoom2.nTileWidth = 8;
				pDrlgRoom2.nTileHeight = 8;

				// Area west of the room is used by an orth
				pOrthBox.nPosX = 0;
				pOrthBox.nPosY = 8;
				pOrthBox.nWidth = 8;
				pOrthBox.nHeight = 8;
				pDrlgOrth.nDirection = ALTDIR_WEST;
				pDrlgOrth.pBox = &pOrthBox;
				pDrlgRoom2.pDrlgOrth = &pDrlgOrth;

				// Area south of the room is used by another room of the level
				pBlockingRoom.pLevel = &pLevel;
				pBlockingRoom.nTileXPos = 8;
				pBlockingRoom.nTileYPos = 16;
				pBlockingRoom.nTileWidth = 8;
				pBlockingRoom.nTileHeight = 8;

				pDrlgRoom2.pDrlgRoomNext = &pBlockingRoom;
				pLevel.pFirstRoomEx = &pDrlgRoom2;
				pLevel.nRooms = 2;
			};

			setup_data(moo_pDrlgRoom1, moo_pDrlgRoom2, moo_pLevel, moo_pBlockingRoom, moo_pDrlgOrth, moo_pOrthBox);
			setup_data(original_pDrlgRoom1, original_pDrlgRoom2, original_pLevel, original_pBlockingRoom, original_pDrlgOrth, original_pOrthBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom1, &moo_pDrlgRoom2, nDirection);
			const auto original_result = original(&original_pDrlgRoom1, &original_pDrlgRoom2, nDirection);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom1, original_pDrlgRoom1, "Comparing pDrlgRoom1");
			MOO_CHECK_EQ(moo_pDrlgRoom2, original_pDrlgRoom2, "Comparing pDrlgRoom2");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7A450")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_MergeMazeRooms, dll_base + 0x0003A450);

		SUBCASE("")
		{
			const uint32_t preset_flags = GENERATE(0, DRLGPRESETROOMFLAG_HAS_MAP_DS1);
			const uint32_t merge = GENERATE(0, 500, 1000);
			const auto room_seed = random_unsigned_integer();

			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgPresetRoomStrc moo_pPresetRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[5]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[5]{};
			D2DrlgOrthStrc moo_pDrlgOrth{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgPresetRoomStrc original_pPresetRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[5]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[5]{};
			D2DrlgOrthStrc original_pDrlgOrth{};

			const auto setup_data = [preset_flags, merge, room_seed](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgPresetRoomStrc& pPresetRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[5],
				D2DrlgPresetRoomStrc (&pPresetRooms)[5],
				D2DrlgOrthStrc& pDrlgOrth
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;
				pMaze.dwMerge = merge;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CAVELEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_CAVE;
				pLevel.pMaze = &pMaze;

				pPresetRoom.dwFlags = preset_flags;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = 8;
				pDrlgRoom.nTileYPos = 8;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.nType = DRLGTYPE_PRESET;
				pDrlgRoom.pMaze = &pPresetRoom;

				// Rooms west, east (with a map), north (already connected), south and north west (diagonal) of the room
				const int room_positions[5][2] = { { 0, 8 }, { 16, 8 }, { 8, 0 }, { 8, 16 }, { 0, 0 } };
				for (int i = 0; i < 5; ++i)
				{
					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = room_positions[i][0];
					pRooms[i].nTileYPos = room_positions[i][1];
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pSeed.nLowSeed = room_seed + i;
					pRooms[i].pDrlgRoomNext = (i + 1 < 5) ? &pRooms[i + 1] : nullptr;
				}
				pPresetRooms[1].dwFlags = DRLGPRESETROOMFLAG_HAS_MAP_DS1;

				pDrlgOrth.pDrlgRoom = &pRooms[2];
				pDrlgOrth.nDirection = ALTDIR_NORTH;
				pDrlgOrth.bInit = TRUE;
				pDrlgOrth.pBox = &pRooms[2].pDrlgCoord;
				pDrlgRoom.pDrlgOrth = &pDrlgOrth;

				pDrlgRoom.pDrlgRoomNext = &pRooms[0];
				pLevel.pFirstRoomEx = &pDrlgRoom;
				pLevel.nRooms = 6;
			};

			setup_data(moo_pDrlgRoom, moo_pPresetRoom, moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms, moo_pDrlgOrth);
			setup_data(original_pDrlgRoom, original_pPresetRoom, original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms, original_pDrlgOrth);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7A570")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_GetRandomRoomExFromLevel, dll_base + 0x0003A570);

		SUBCASE("")
		{
			REPEAT_10()

			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pRooms[5]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pRooms[5]{};

			const auto setup_data = [level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc (&pRooms)[5]
			) {
				pLevel.pSeed.nLowSeed = level_seed;

				for (int i = 0; i < 5; ++i)
				{
					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = i * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].pDrlgRoomNext = (i + 1 < 5) ? &pRooms[i + 1] : nullptr;
				}

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 5;
			};

			setup_data(moo_pLevel, moo_pRooms);
			setup_data(original_pLevel, original_pRooms);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel);
			const auto original_result = original(&original_pLevel);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7A5D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_BuildBasicMaze, dll_base + 0x0003A5D0);

		SUBCASE("")
		{
			const auto difficulty = GENERATE(0, 1, 2);
			// Normal level, staff tomb level and boss tomb level
			const int level_id = GENERATE(LEVEL_TALRASHASTOMB1, LEVEL_TALRASHASTOMB2, LEVEL_TALRASHASTOMB3);
			const auto level_seed = random_unsigned_integer();
			const auto room_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pFirstRoomEx{};
			D2DrlgPresetRoomStrc moo_pPresetRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pFirstRoomEx{};
			D2DrlgPresetRoomStrc original_pPresetRoom{};

			const auto setup_data = [difficulty, level_id, level_seed, room_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc& pFirstRoomEx,
				D2DrlgPresetRoomStrc& pPresetRoom
			) {
				pDrlg.nDifficulty = difficulty;
				pDrlg.nStaffTombLevel = LEVEL_TALRASHASTOMB2;
				pDrlg.nBossTombLevel = LEVEL_TALRASHASTOMB3;

				pMaze.dwRooms[0] = 6;
				pMaze.dwRooms[1] = 8;
				pMaze.dwRooms[2] = 10;
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;
				pMaze.dwMerge = 500;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nLevelType = LVLTYPE_ACT2_TOMB;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				pFirstRoomEx.pLevel = &pLevel;
				pFirstRoomEx.nTileXPos = 128;
				pFirstRoomEx.nTileYPos = 128;
				pFirstRoomEx.nTileWidth = 8;
				pFirstRoomEx.nTileHeight = 8;
				pFirstRoomEx.nType = DRLGTYPE_PRESET;
				pFirstRoomEx.pMaze = &pPresetRoom;
				pFirstRoomEx.pSeed.nLowSeed = room_seed;

				pLevel.pFirstRoomEx = &pFirstRoomEx;
				pLevel.nRooms = 1;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pFirstRoomEx, moo_pPresetRoom);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pFirstRoomEx, original_pPresetRoom);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7A830")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct5LavaPresets, dll_base + 0x0003A830);

		SUBCASE("")
		{
			REPEAT_10()

			const auto level_seed = random_unsigned_integer();
			const auto room_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pFirstRoomEx{};
			D2DrlgPresetRoomStrc moo_pPresetRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pFirstRoomEx{};
			D2DrlgPresetRoomStrc original_pPresetRoom{};

			const auto setup_data = [level_seed, room_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc& pFirstRoomEx,
				D2DrlgPresetRoomStrc& pPresetRoom
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_HELL1;
				pLevel.nLevelType = LVLTYPE_ACT5_LAVA;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				pFirstRoomEx.pLevel = &pLevel;
				pFirstRoomEx.nTileXPos = 64;
				pFirstRoomEx.nTileYPos = 64;
				pFirstRoomEx.nTileWidth = 8;
				pFirstRoomEx.nTileHeight = 8;
				pFirstRoomEx.nType = DRLGTYPE_PRESET;
				pFirstRoomEx.pMaze = &pPresetRoom;
				pFirstRoomEx.pSeed.nLowSeed = room_seed;

				pLevel.pFirstRoomEx = &pFirstRoomEx;
				pLevel.nRooms = 1;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pFirstRoomEx, moo_pPresetRoom);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pFirstRoomEx, original_pPresetRoom);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7A9B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_FillBlankMazeSpaces, dll_base + 0x0003A9B0);

		SUBCASE("")
		{
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pIgnoreRoomEx{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[2]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pIgnoreRoomEx{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[2]{};
			int nLevelPrest = LVLPREST_ACT4_LAVA_X;

			const auto setup_data = [level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pIgnoreRoomEx,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[2]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_RIVEROFFLAME;
				pLevel.nLevelType = LVLTYPE_ACT4_LAVA;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				// Two rooms next to each other, and a third one south of them whose surroundings must not be filled
				const int room_positions[2][2] = { { 8, 8 }, { 16, 8 } };
				for (int i = 0; i < 2; ++i)
				{
					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = room_positions[i][0];
					pRooms[i].nTileYPos = room_positions[i][1];
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
				}

				pIgnoreRoomEx.pLevel = &pLevel;
				pIgnoreRoomEx.nTileXPos = 8;
				pIgnoreRoomEx.nTileYPos = 32;
				pIgnoreRoomEx.nTileWidth = 8;
				pIgnoreRoomEx.nTileHeight = 8;

				pRooms[0].pDrlgRoomNext = &pRooms[1];
				pRooms[1].pDrlgRoomNext = &pIgnoreRoomEx;
				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 3;
			};

			setup_data(moo_pLevel, moo_pIgnoreRoomEx, moo_pDrlg, moo_pMaze, moo_pRooms);
			setup_data(original_pLevel, original_pIgnoreRoomEx, original_pDrlg, original_pMaze, original_pRooms);

			// Call both implementations
			sut(&moo_pLevel, nLevelPrest, &moo_pIgnoreRoomEx);
			original(&original_pLevel, nLevelPrest, &original_pIgnoreRoomEx);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ(moo_pIgnoreRoomEx, original_pIgnoreRoomEx, "Comparing pIgnoreRoomEx");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7AAC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct2TombPrev_Act5BaalPrev, dll_base + 0x0003AAC0);

		SUBCASE("")
		{
			REPEAT_5()

			const int level_type = GENERATE(LVLTYPE_ACT2_TOMB, LVLTYPE_ACT5_BAAL);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[2]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[2]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[2]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[2]{};

			const auto setup_data = [level_type, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[2],
				D2DrlgPresetRoomStrc (&pPresetRooms)[2]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;
				pMaze.dwMerge = 500;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_type == LVLTYPE_ACT2_TOMB ? LEVEL_TALRASHASTOMB1 : LEVEL_THEWORLDSTONEKEEPLEV1;
				pLevel.nLevelType = level_type;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				// The first room, and a room south east of it that is next to the rooms placed east and south of the first room
				const int room_positions[2][2] = { { 64, 64 }, { 72, 72 } };
				for (int i = 0; i < 2; ++i)
				{
					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = room_positions[i][0];
					pRooms[i].nTileYPos = room_positions[i][1];
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pSeed.nLowSeed = level_seed + i + 1;
				}

				pRooms[0].pDrlgRoomNext = &pRooms[1];
				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 2;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7ABC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceArcaneSanctuary, dll_base + 0x0003ABC0);

		SUBCASE("")
		{
			REPEAT_5()

			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pFirstRoomEx{};
			D2DrlgPresetRoomStrc moo_pPresetRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pFirstRoomEx{};
			D2DrlgPresetRoomStrc original_pPresetRoom{};

			const auto setup_data = [level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc& pFirstRoomEx,
				D2DrlgPresetRoomStrc& pPresetRoom
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;
				pMaze.dwMerge = 500;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_ARCANESANCTUARY;
				pLevel.nLevelType = LVLTYPE_ACT2_ARCANE;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				pFirstRoomEx.pLevel = &pLevel;
				pFirstRoomEx.nTileXPos = 256;
				pFirstRoomEx.nTileYPos = 256;
				pFirstRoomEx.nTileWidth = 8;
				pFirstRoomEx.nTileHeight = 8;
				pFirstRoomEx.nType = DRLGTYPE_PRESET;
				pFirstRoomEx.pMaze = &pPresetRoom;

				pLevel.pFirstRoomEx = &pFirstRoomEx;
				pLevel.nRooms = 1;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pFirstRoomEx, moo_pPresetRoom);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pFirstRoomEx, original_pPresetRoom);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7AFD0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAdjacentPresetRoom, dll_base + 0x0003AFD0);

		SUBCASE("")
		{
			const auto level_seed = random_unsigned_integer();
			const auto room_seed = random_unsigned_integer();

			// Input data
			D2DrlgRoomStrc moo_pParentRoomEx{};
			D2DrlgPresetRoomStrc moo_pPresetRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[3]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[3]{};
			D2DrlgOrthStrc moo_pDrlgOrth{};
			D2DrlgRoomStrc original_pParentRoomEx{};
			D2DrlgPresetRoomStrc original_pPresetRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[3]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[3]{};
			D2DrlgOrthStrc original_pDrlgOrth{};
			int nDirection = GENERATE(ALTDIR_WEST, ALTDIR_NORTH, ALTDIR_EAST, ALTDIR_SOUTH, ALTDIR_NORTHWEST, ALTDIR_NORTHEAST, ALTDIR_SOUTHEAST, ALTDIR_SOUTHWEST);
			int bMergeRooms = GENERATE(FALSE, TRUE);

			const auto setup_data = [level_seed, room_seed](
				D2DrlgRoomStrc& pParentRoomEx,
				D2DrlgPresetRoomStrc& pPresetRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[3],
				D2DrlgPresetRoomStrc (&pPresetRooms)[3],
				D2DrlgOrthStrc& pDrlgOrth
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;
				pMaze.dwMerge = 500;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CAVELEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_CAVE;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				pParentRoomEx.pLevel = &pLevel;
				pParentRoomEx.nTileXPos = 8;
				pParentRoomEx.nTileYPos = 8;
				pParentRoomEx.nTileWidth = 8;
				pParentRoomEx.nTileHeight = 8;
				pParentRoomEx.nType = DRLGTYPE_PRESET;
				pParentRoomEx.pMaze = &pPresetRoom;

				// Other rooms of the level: east, north west and south east (with a map) of the room
				const int room_positions[3][2] = { { 16, 8 }, { 0, 0 }, { 16, 16 } };
				for (int i = 0; i < 3; ++i)
				{
					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = room_positions[i][0];
					pRooms[i].nTileYPos = room_positions[i][1];
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pSeed.nLowSeed = room_seed + i;
					pRooms[i].pDrlgRoomNext = (i + 1 < 3) ? &pRooms[i + 1] : nullptr;
				}
				pPresetRooms[2].dwFlags = DRLGPRESETROOMFLAG_HAS_MAP_DS1;

				// The room is already connected to the room east of it
				pDrlgOrth.pDrlgRoom = &pRooms[0];
				pDrlgOrth.nDirection = ALTDIR_EAST;
				pDrlgOrth.bInit = TRUE;
				pDrlgOrth.pBox = &pRooms[0].pDrlgCoord;
				pParentRoomEx.pDrlgOrth = &pDrlgOrth;

				pParentRoomEx.pDrlgRoomNext = &pRooms[0];
				pLevel.pFirstRoomEx = &pParentRoomEx;
				pLevel.nRooms = 4;
			};

			setup_data(moo_pParentRoomEx, moo_pPresetRoom, moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms, moo_pDrlgOrth);
			setup_data(original_pParentRoomEx, original_pPresetRoom, original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms, original_pDrlgOrth);

			// Call both implementations
			const auto moo_result = sut(&moo_pParentRoomEx, nDirection, bMergeRooms);
			const auto original_result = original(&original_pParentRoomEx, nDirection, bMergeRooms);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pParentRoomEx, original_pParentRoomEx, "Comparing pParentRoomEx");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7B230")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_ScanReplaceSpecialPreset, dll_base + 0x0003B230);

		SUBCASE("")
		{
			const auto has_matching_room = GENERATE(0, 1);
			const auto rand_value = GENERATE(0, 1, 2, 3);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			int moo_pRand{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			int original_pRand{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};
			D2MazeLevelIdStrc pMazeInit{ LVLPREST_ACT1_CAVE_N, LVLPREST_ACT1_CAVE_PREV_N, -1, ALTDIR_SOUTH };

			const auto setup_data = [has_matching_room, rand_value, level_seed](
				D2DrlgLevelStrc& pLevel,
				int& pRand,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pRand = rand_value;

				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CAVELEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_CAVE;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				// The first matching room already has a map
				const int matching_level_prests[4] = { LVLPREST_ACT1_CAVE_N, LVLPREST_ACT1_CAVE_E, LVLPREST_ACT1_CAVE_N, LVLPREST_ACT1_CAVE_W };
				const int other_level_prests[4] = { LVLPREST_ACT1_CAVE_S, LVLPREST_ACT1_CAVE_E, LVLPREST_ACT1_CAVE_S, LVLPREST_ACT1_CAVE_W };

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = has_matching_room ? matching_level_prests[i] : other_level_prests[i];
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}
				pPresetRooms[0].dwFlags = DRLGPRESETROOMFLAG_HAS_MAP_DS1;

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pRand, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pRand, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel, &pMazeInit, &moo_pRand);
			original(&original_pLevel, &pMazeInit, &original_pRand);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ(moo_pRand, original_pRand, "Comparing pRand");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7B330")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_ScanReplaceSpecialAct2SewersPresets, dll_base + 0x0003B330);

		SUBCASE("")
		{
			REPEAT_5()

			// Sewer levels with special presets, and a level without any
			const int level_id = GENERATE(LEVEL_SEWERSLEV1, LEVEL_SEWERSLEV2, LEVEL_SEWERSLEV3, LEVEL_ANCIENTTUNNELS, LEVEL_CAVELEV1);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};

			const auto setup_data = [level_id, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;
				pMaze.dwMerge = 500;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nLevelType = LVLTYPE_ACT2_SEWER;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				const int level_prests[4] = { LVLPREST_ACT2_SEWER_N, LVLPREST_ACT2_SEWER_E, LVLPREST_ACT2_SEWER_S, LVLPREST_ACT2_SEWER_W };

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = level_prests[i];
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pSeed.nLowSeed = level_seed + i + 1;
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7B660")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_AddSpecialPreset, dll_base + 0x0003B660);

		SUBCASE("")
		{
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};
			int nDirection = GENERATE(ALTDIR_WEST, ALTDIR_NORTH, ALTDIR_EAST, ALTDIR_SOUTH);
			int nLvlPrestId = LVLPREST_ACT1_CAVE_PREV_N;
			int nFile = GENERATE(-1, 0);

			const auto setup_data = [level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CAVELEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_CAVE;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				// The first room already has a map, so the preset must be added next to another room
				pPresetRooms[0].dwFlags = DRLGPRESETROOMFLAG_HAS_MAP_DS1;

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel, nDirection, nLvlPrestId, nFile);
			original(&original_pLevel, nDirection, nLvlPrestId, nFile);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7B710")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_CheckIfMayPlaceAdjacentPresetRoom, dll_base + 0x0003B710);

		SUBCASE("")
		{
			const uint32_t preset_flags = GENERATE(0, DRLGPRESETROOMFLAG_HAS_MAP_DS1);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgPresetRoomStrc moo_pPresetRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[2]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[2]{};
			D2DrlgOrthStrc moo_pDrlgOrth{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgPresetRoomStrc original_pPresetRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[2]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[2]{};
			D2DrlgOrthStrc original_pDrlgOrth{};
			int nDirection = GENERATE(ALTDIR_WEST, ALTDIR_NORTH, ALTDIR_EAST, ALTDIR_SOUTH, ALTDIR_NORTHWEST, ALTDIR_NORTHEAST, ALTDIR_SOUTHEAST, ALTDIR_SOUTHWEST);

			const auto setup_data = [preset_flags, level_seed](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgPresetRoomStrc& pPresetRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[2],
				D2DrlgPresetRoomStrc (&pPresetRooms)[2],
				D2DrlgOrthStrc& pDrlgOrth
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CAVELEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_CAVE;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				pPresetRoom.dwFlags = preset_flags;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = 8;
				pDrlgRoom.nTileYPos = 8;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.nType = DRLGTYPE_PRESET;
				pDrlgRoom.pMaze = &pPresetRoom;

				// Other rooms of the level: east (already connected) and north west of the room
				const int room_positions[2][2] = { { 16, 8 }, { 0, 0 } };
				for (int i = 0; i < 2; ++i)
				{
					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = room_positions[i][0];
					pRooms[i].nTileYPos = room_positions[i][1];
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 2) ? &pRooms[i + 1] : nullptr;
				}

				pDrlgOrth.pDrlgRoom = &pRooms[0];
				pDrlgOrth.nDirection = ALTDIR_EAST;
				pDrlgOrth.bInit = TRUE;
				pDrlgOrth.pBox = &pRooms[0].pDrlgCoord;
				pDrlgRoom.pDrlgOrth = &pDrlgOrth;

				pDrlgRoom.pDrlgRoomNext = &pRooms[0];
				pLevel.pFirstRoomEx = &pDrlgRoom;
				pLevel.nRooms = 3;
			};

			setup_data(moo_pDrlgRoom, moo_pPresetRoom, moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms, moo_pDrlgOrth);
			setup_data(original_pDrlgRoom, original_pPresetRoom, original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms, original_pDrlgOrth);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nDirection);
			const auto original_result = original(&original_pDrlgRoom, nDirection);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7B8B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct2TombStuff, dll_base + 0x0003B8B0);

		SUBCASE("")
		{
			const int level_id = GENERATE(
				LEVEL_STONYTOMBLEV1,
				LEVEL_STONYTOMBLEV2,
				LEVEL_HALLSOFTHEDEADLEV1,
				LEVEL_HALLSOFTHEDEADLEV2,
				LEVEL_HALLSOFTHEDEADLEV3,
				LEVEL_CLAWVIPERTEMPLELEV2,
				LEVEL_TALRASHASTOMB1,
				LEVEL_TALRASHASTOMB2,
				LEVEL_TALRASHASTOMB3
			);
			// The first room of the level is the preset warp room
			const int prev_level_prest = GENERATE(LVLPREST_ACT2_TOMB_PREV_NSW, LVLPREST_ACT2_TOMB_PREV_NEW, LVLPREST_ACT2_TOMB_PREV_NSE, LVLPREST_ACT2_TOMB_PREV_SEW);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[3]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[3]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[3]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[3]{};

			const auto setup_data = [level_id, prev_level_prest, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[3],
				D2DrlgPresetRoomStrc (&pPresetRooms)[3]
			) {
				pDrlg.nStaffTombLevel = LEVEL_TALRASHASTOMB1;
				pDrlg.nBossTombLevel = LEVEL_TALRASHASTOMB2;

				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nLevelType = LVLTYPE_ACT2_TOMB;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				// Warp room, with a room north and a room east of it
				const int room_positions[3][2] = { { 64, 64 }, { 64, 56 }, { 72, 64 } };
				const int level_prests[3] = { prev_level_prest, LVLPREST_ACT2_TOMB_S, LVLPREST_ACT2_TOMB_W };
				for (int i = 0; i < 3; ++i)
				{
					pPresetRooms[i].nLevelPrest = level_prests[i];
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = room_positions[i][0];
					pRooms[i].nTileYPos = room_positions[i][1];
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 3) ? &pRooms[i + 1] : nullptr;
				}
				pPresetRooms[0].dwFlags = DRLGPRESETROOMFLAG_HAS_MAP_DS1;

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 3;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7BC40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_InitRoomFixedPreset, dll_base + 0x0003BC40);

		SUBCASE("")
		{
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgPresetRoomStrc moo_pPresetRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pBlockingRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgPresetRoomStrc original_pPresetRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pBlockingRoom{};
			int nDirection = GENERATE(ALTDIR_WEST, ALTDIR_NORTH, ALTDIR_EAST, ALTDIR_SOUTH, ALTDIR_NORTHWEST, ALTDIR_NORTHEAST, ALTDIR_SOUTHEAST, ALTDIR_SOUTHWEST);
			int nLvlPrestId = LVLPREST_ACT1_CAVE_NEXT_N;
			int nFile = GENERATE(-1, 0);
			int bUseInitPreset = GENERATE(FALSE, TRUE);

			const auto setup_data = [level_seed](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgPresetRoomStrc& pPresetRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc& pBlockingRoom
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CAVELEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_CAVE;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = 8;
				pDrlgRoom.nTileYPos = 8;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.nType = DRLGTYPE_PRESET;
				pDrlgRoom.pMaze = &pPresetRoom;

				// Area east of the room is already used
				pBlockingRoom.pLevel = &pLevel;
				pBlockingRoom.nTileXPos = 16;
				pBlockingRoom.nTileYPos = 8;
				pBlockingRoom.nTileWidth = 8;
				pBlockingRoom.nTileHeight = 8;

				pDrlgRoom.pDrlgRoomNext = &pBlockingRoom;
				pLevel.pFirstRoomEx = &pDrlgRoom;
				pLevel.nRooms = 2;
			};

			setup_data(moo_pDrlgRoom, moo_pPresetRoom, moo_pLevel, moo_pDrlg, moo_pMaze, moo_pBlockingRoom);
			setup_data(original_pDrlgRoom, original_pPresetRoom, original_pLevel, original_pDrlg, original_pMaze, original_pBlockingRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nDirection, nLvlPrestId, nFile, bUseInitPreset);
			const auto original_result = original(&original_pDrlgRoom, nDirection, nLvlPrestId, nFile, bUseInitPreset);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7BCD0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct2LairStuff, dll_base + 0x0003BCD0);

		SUBCASE("")
		{
			REPEAT_5()

			const auto level_id = GENERATE(LEVEL_MAGGOTLAIRLEV1, LEVEL_MAGGOTLAIRLEV3);
			const auto has_matching_rooms = GENERATE(0, 1);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};

			const auto setup_data = [level_id, has_matching_rooms, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nLevelType = LVLTYPE_ACT2_LAIR;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				const int level_prests[4] = { LVLPREST_ACT2_LAIR_N, LVLPREST_ACT2_LAIR_E, LVLPREST_ACT2_LAIR_S, LVLPREST_ACT2_LAIR_W };

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = has_matching_rooms ? level_prests[i] : LVLPREST_NONE;
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7BE60")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct3DungeonStuff, dll_base + 0x0003BE60);

		SUBCASE("")
		{
			REPEAT_5()

			const auto has_matching_rooms = GENERATE(0, 1);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};

			const auto setup_data = [has_matching_rooms, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_FLAYERDUNGEONLEV1;
				pLevel.nLevelType = LVLTYPE_ACT3_DUNGEON;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				const int level_prests[4] = { LVLPREST_ACT3_DUNGEON_N, LVLPREST_ACT3_DUNGEON_E, LVLPREST_ACT3_DUNGEON_S, LVLPREST_ACT3_DUNGEON_W };

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = has_matching_rooms ? level_prests[i] : LVLPREST_NONE;
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7C000")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct3SewerStuff, dll_base + 0x0003C000);

		SUBCASE("")
		{
			REPEAT_5()

			const auto has_matching_rooms = GENERATE(0, 1);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};

			const auto setup_data = [has_matching_rooms, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_SEWERSA3LEV2;
				pLevel.nLevelType = LVLTYPE_ACT3_SEWER;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				const int level_prests[4] = { LVLPREST_ACT3_SEWER_N, LVLPREST_ACT3_SEWER_E, LVLPREST_ACT3_SEWER_S, LVLPREST_ACT3_SEWER_W };

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = has_matching_rooms ? level_prests[i] : LVLPREST_NONE;
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7C1A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct3MephistoStuff, dll_base + 0x0003C1A0);

		SUBCASE("")
		{
			REPEAT_5()

			const auto level_id = GENERATE(LEVEL_DURANCEOFHATELEV1, LEVEL_DURANCEOFHATELEV2, LEVEL_DURANCEOFHATELEV3);
			const auto has_matching_rooms = GENERATE(0, 1);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};

			const auto setup_data = [level_id, has_matching_rooms, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nLevelType = LVLTYPE_ACT3_KURAST;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				const int level_prests[4] = { LVLPREST_ACT3_MEPHISTO_N, LVLPREST_ACT3_MEPHISTO_E, LVLPREST_ACT3_MEPHISTO_S, LVLPREST_ACT3_MEPHISTO_W };

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = has_matching_rooms ? level_prests[i] : LVLPREST_NONE;
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7C380")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct5TempleStuff, dll_base + 0x0003C380);

		SUBCASE("")
		{
			REPEAT_5()

			const auto level_id = GENERATE(LEVEL_HALLSOFANGUISH, LEVEL_HALLSOFDEATHSCALLING, LEVEL_HALLSOFVAUGHT);
			const auto has_matching_rooms = GENERATE(0, 1);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};

			const auto setup_data = [level_id, has_matching_rooms, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nLevelType = LVLTYPE_ACT5_TEMPLE;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				const int level_prests[4] = { LVLPREST_ACT5_TEMPLE_NE, LVLPREST_ACT5_TEMPLE_NW, LVLPREST_ACT5_TEMPLE_SW, LVLPREST_ACT5_TEMPLE_SE_UP };

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = has_matching_rooms ? level_prests[i] : LVLPREST_NONE;
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7C500")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct5BaalStuff, dll_base + 0x0003C500);

		SUBCASE("")
		{
			REPEAT_5()

			const auto level_id = GENERATE(LEVEL_THEWORLDSTONEKEEPLEV1, LEVEL_THEWORLDSTONEKEEPLEV2);
			const auto has_matching_rooms = GENERATE(0, 1);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};

			const auto setup_data = [level_id, has_matching_rooms, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nLevelType = LVLTYPE_ACT5_BAAL;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				const int level_prests[4] = { LVLPREST_ACT5_BAAL_N, LVLPREST_ACT5_BAAL_E, LVLPREST_ACT5_BAAL_S, LVLPREST_ACT5_BAAL_W };

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = has_matching_rooms ? level_prests[i] : LVLPREST_NONE;
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7C660")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct1Barracks, dll_base + 0x0003C660);

		SUBCASE("")
		{
			REPEAT_5()

			// Direction of the Outer Cloister preset, which decides where the barracks entrance is
			const int outer_cloister_direction = GENERATE(0, 1, 2);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc moo_pOuterCloisterLevel{};
			D2DrlgPresetInfoStrc moo_pOuterCloisterPreset{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pOuterCloisterLevel{};
			D2DrlgPresetInfoStrc original_pOuterCloisterPreset{};

			const auto setup_data = [outer_cloister_direction, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4],
				D2DrlgLevelStrc& pOuterCloisterLevel,
				D2DrlgPresetInfoStrc& pOuterCloisterPreset
			) {
				pOuterCloisterPreset.nDirection = outer_cloister_direction;

				pOuterCloisterLevel.pDrlg = &pDrlg;
				pOuterCloisterLevel.nLevelId = LEVEL_OUTERCLOISTER;
				pOuterCloisterLevel.nPosX = 200;
				pOuterCloisterLevel.nPosY = 300;
				pOuterCloisterLevel.nWidth = 48;
				pOuterCloisterLevel.nHeight = 40;
				pOuterCloisterLevel.pPreset = &pOuterCloisterPreset;

				pDrlg.pLevel = &pOuterCloisterLevel;

				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_BARRACKS;
				pLevel.nLevelType = LVLTYPE_ACT1_BARRACKS;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				const int level_prests[4] = { LVLPREST_ACT1_BARRACKS_N, LVLPREST_ACT1_BARRACKS_E, LVLPREST_ACT1_BARRACKS_S, LVLPREST_ACT1_BARRACKS_W };

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = level_prests[i];
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms, moo_pOuterCloisterLevel, moo_pOuterCloisterPreset);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms, original_pOuterCloisterLevel, original_pOuterCloisterPreset);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7CA20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_SetRoomSize, dll_base + 0x0003CA20);

		SUBCASE("")
		{
			const auto size_x = random_unsigned_integer(1, 64);
			const auto size_y = random_unsigned_integer(1, 64);

			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2LvlMazeTxt original_pMaze{};

			const auto setup_data = [size_x, size_y](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2LvlMazeTxt& pMaze
			) {
				pMaze.dwSizeX = size_x;
				pMaze.dwSizeY = size_y;

				pLevel.pMaze = &pMaze;

				pDrlgRoom.pLevel = &pLevel;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pMaze);
			setup_data(original_pDrlgRoom, original_pLevel, original_pMaze);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7CA40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct4Lava, dll_base + 0x0003CA40);

		SUBCASE("")
		{
			REPEAT_5()

			// Nothing is done in act 5
			const auto act = GENERATE(ACT_IV, ACT_V);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc moo_pChaosSanctumLevel{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pChaosSanctumLevel{};

			const auto setup_data = [act, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4],
				D2DrlgLevelStrc& pChaosSanctumLevel
			) {
				pChaosSanctumLevel.pDrlg = &pDrlg;
				pChaosSanctumLevel.nLevelId = LEVEL_CHAOSSANCTUM;
				pChaosSanctumLevel.nPosX = 200;
				pChaosSanctumLevel.nPosY = 100;
				pChaosSanctumLevel.nWidth = 56;
				pChaosSanctumLevel.nHeight = 48;

				pDrlg.nAct = act;
				pDrlg.pLevel = &pChaosSanctumLevel;

				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_RIVEROFFLAME;
				pLevel.nLevelType = LVLTYPE_ACT4_LAVA;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				const int level_prests[4] = { LVLPREST_ACT4_LAVA_W, LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_E };

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = level_prests[i];
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms, moo_pChaosSanctumLevel);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms, original_pChaosSanctumLevel);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7CCB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_PlaceAct5IceStuff, dll_base + 0x0003CCB0);

		SUBCASE("")
		{
			REPEAT_5()

			// Ice cave levels with special presets, and a level without any
			const auto level_id = GENERATE(LEVEL_CRYSTALIZEDCAVERNLEV1, LEVEL_CRYSTALIZEDCAVERNLEV2, LEVEL_GLACIALCAVESLEV1, LEVEL_CELLAROFPITY);
			const auto has_matching_rooms = GENERATE(0, 1);
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgRoomStrc moo_pRooms[4]{};
			D2DrlgPresetRoomStrc moo_pPresetRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2LvlMazeTxt original_pMaze{};
			D2DrlgRoomStrc original_pRooms[4]{};
			D2DrlgPresetRoomStrc original_pPresetRooms[4]{};

			const auto setup_data = [level_id, has_matching_rooms, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2LvlMazeTxt& pMaze,
				D2DrlgRoomStrc (&pRooms)[4],
				D2DrlgPresetRoomStrc (&pPresetRooms)[4]
			) {
				pMaze.dwRooms[0] = 12;
				pMaze.dwRooms[1] = 12;
				pMaze.dwRooms[2] = 12;
				pMaze.dwSizeX = 8;
				pMaze.dwSizeY = 8;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nLevelType = LVLTYPE_ACT5_ICE_CAVES;
				pLevel.pMaze = &pMaze;
				pLevel.pSeed.nLowSeed = level_seed;

				const int level_prests[4] = { LVLPREST_ACT5_ICE_N, LVLPREST_ACT5_ICE_E, LVLPREST_ACT5_ICE_S, LVLPREST_ACT5_ICE_W };

				// 2x2 grid of maze rooms
				for (int i = 0; i < 4; ++i)
				{
					pPresetRooms[i].nLevelPrest = has_matching_rooms ? level_prests[i] : LVLPREST_NONE;
					pPresetRooms[i].nPickedFile = -1;

					pRooms[i].pLevel = &pLevel;
					pRooms[i].nTileXPos = (i % 2) * 8;
					pRooms[i].nTileYPos = (i / 2) * 8;
					pRooms[i].nTileWidth = 8;
					pRooms[i].nTileHeight = 8;
					pRooms[i].nType = DRLGTYPE_PRESET;
					pRooms[i].pMaze = &pPresetRooms[i];
					pRooms[i].pDrlgRoomNext = (i + 1 < 4) ? &pRooms[i + 1] : nullptr;
				}

				pLevel.pFirstRoomEx = &pRooms[0];
				pLevel.nRooms = 4;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pMaze, moo_pRooms, moo_pPresetRooms);
			setup_data(original_pLevel, original_pDrlg, original_pMaze, original_pRooms, original_pPresetRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7CEA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_RollAct_1_2_3_BasicPresets, dll_base + 0x0003CEA0);

		SUBCASE("")
		{
			REPEAT_5()

			// Level types and the level preset the basic presets of the level type are based on.
			// The last level type has no basic presets.
			const int level_types[][2] = {
				{ LVLTYPE_ACT1_CAVE, LVLPREST_ACT1_DOE_ENTRANCE },
				{ LVLTYPE_ACT1_CRYPT, LVLPREST_ACT1_GRAVEYARD },
				{ LVLTYPE_ACT1_BARRACKS, LVLPREST_ACT1_BARRACKS_COURT_CONNECT },
				{ LVLTYPE_ACT1_JAIL, LVLPREST_ACT1_BARRACKS_FORGE_N },
				{ LVLTYPE_ACT1_CATACOMBS, LVLPREST_ACT1_CATHEDRAL },
				{ LVLTYPE_ACT2_SEWER, LVLPREST_ACT2_TOWN },
				{ LVLTYPE_ACT2_TOMB, LVLPREST_ACT2_DESERT_RUINS_ELDER },
				{ LVLTYPE_ACT3_KURAST, LVLPREST_ACT3_TEMPLE_6 },
				{ LVLTYPE_ACT3_DUNGEON, LVLPREST_ACT3_SPIDER_CHEST_NE },
				{ LVLTYPE_ACT3_SEWER, LVLPREST_ACT3_DUNGEON_TREASURE_2 },
				{ LVLTYPE_ACT4_LAVA, LVLPREST_ACT4_LAVA_X },
			};

			// The Den of Evil is ignored
			const int level_id = GENERATE(LEVEL_CAVELEV1, LEVEL_DENOFEVIL);

			for (const auto& level_type : level_types)
			{
				const auto level_seed = random_unsigned_integer();

				// Input data
				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgRoomStrc moo_pRooms[12]{};
				D2DrlgPresetRoomStrc moo_pPresetRooms[12]{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgRoomStrc original_pRooms[12]{};
				D2DrlgPresetRoomStrc original_pPresetRooms[12]{};

				const auto setup_data = [&level_type, level_id, level_seed](
					D2DrlgLevelStrc& pLevel,
					D2DrlgRoomStrc (&pRooms)[12],
					D2DrlgPresetRoomStrc (&pPresetRooms)[12]
				) {
					pLevel.nLevelId = level_id;
					pLevel.nLevelType = level_type[0];
					pLevel.pSeed.nLowSeed = level_seed;

					for (int i = 0; i < 12; ++i)
					{
						// Basic presets of the level type, the first ones also exist twice
						pPresetRooms[i].nLevelPrest = level_type[1] + 1 + (i % 10);
						pPresetRooms[i].nPickedFile = -1;

						pRooms[i].pLevel = &pLevel;
						pRooms[i].pMaze = &pPresetRooms[i];
						pRooms[i].pDrlgRoomNext = (i + 1 < 12) ? &pRooms[i + 1] : nullptr;
					}

					// Room already having a map, which must be ignored
					pPresetRooms[1].dwFlags = DRLGPRESETROOMFLAG_HAS_MAP_DS1;

					pLevel.pFirstRoomEx = &pRooms[0];
					pLevel.nRooms = 12;
				};

				setup_data(moo_pLevel, moo_pRooms, moo_pPresetRooms);
				setup_data(original_pLevel, original_pRooms, original_pPresetRooms);

				// Call both implementations
				sut(&moo_pLevel);
				original(&original_pLevel);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7D130")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_RollBasicPresets, dll_base + 0x0003D130);

		SUBCASE("")
		{
			// Building the areas of presets without scan and pops does not need any DS1 file to be loaded.
			// Prefer basic act 1 cave presets, for which the picked file is rolled using the level's builds.
			const auto can_be_built = [this](int level_prest) {
				const D2LvlPrestTxt& record = lvlprest_txt[level_prest];
				return record.dwDef == static_cast<uint32_t>(level_prest) && record.dwScan == 0 && record.dwPops == 0 && record.dwFiles > 0;
			};

			std::vector<int> level_prests;
			for (int level_prest = LVLPREST_ACT1_DOE_ENTRANCE + 1; level_prest < LVLPREST_ACT1_DOE_ENTRANCE + 16; ++level_prest)
			{
				if (can_be_built(level_prest))
				{
					level_prests.push_back(level_prest);
				}
			}

			for (int level_prest = 1; level_prest < lvlprest_record_count && level_prests.size() < 2; ++level_prest)
			{
				if (can_be_built(level_prest))
				{
					level_prests.push_back(level_prest);
				}
			}

			REQUIRE(level_prests.size() >= 2);

			// Picked file to roll, and one to use as is
			const int picked_files[2] = { -1, 0 };
			const auto level_seed = random_unsigned_integer();

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pWarp{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pWarp{};

			const auto setup_data = [&level_prests, &picked_files, level_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pWarp
			) {
				// Level without any vis, so that building the preset areas does not need any warp
				pWarp.nLevel = LEVEL_CAVELEV1;

				pDrlg.pWarp = &pWarp;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CAVELEV1;
				pLevel.nLevelType = LVLTYPE_ACT1_CAVE;
				pLevel.pSeed.nLowSeed = level_seed;

				// The rooms are freed by the function, so they must be allocated the same way the game does
				D2DrlgRoomStrc* pRooms[2] = {};
				for (int i = 0; i < 2; ++i)
				{
					pRooms[i] = D2_CALLOC_STRC_POOL(pDrlg.pMempool, D2DrlgRoomStrc);
					pRooms[i]->pLevel = &pLevel;
					pRooms[i]->nTileXPos = 8 * i;
					pRooms[i]->nTileYPos = 0;
					pRooms[i]->nTileWidth = 8;
					pRooms[i]->nTileHeight = 8;
					pRooms[i]->nType = DRLGTYPE_PRESET;
					pRooms[i]->pMaze = D2_CALLOC_STRC_POOL(pDrlg.pMempool, D2DrlgPresetRoomStrc);
					pRooms[i]->pMaze->nLevelPrest = level_prests[i];
					pRooms[i]->pMaze->nPickedFile = picked_files[i];
				}

				// Connect both rooms
				for (int i = 0; i < 2; ++i)
				{
					D2DrlgOrthStrc* pDrlgOrth = D2_CALLOC_STRC_POOL(pDrlg.pMempool, D2DrlgOrthStrc);
					pDrlgOrth->pDrlgRoom = pRooms[1 - i];
					pDrlgOrth->nDirection = i == 0 ? ALTDIR_EAST : ALTDIR_WEST;
					pDrlgOrth->bInit = TRUE;
					pDrlgOrth->pBox = &pRooms[1 - i]->pDrlgCoord;
					pRooms[i]->pDrlgOrth = pDrlgOrth;
				}

				pRooms[0]->pDrlgRoomNext = pRooms[1];
				pLevel.pFirstRoomEx = pRooms[0];
				pLevel.nRooms = 2;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pWarp);
			setup_data(original_pLevel, original_pDrlg, original_pWarp);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7D3D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_ResetMazeRecord, dll_base + 0x0003D3D0);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2LvlMazeTxt moo_pMaze{};
			D2DrlgLevelStrc original_pLevel{};
			D2LvlMazeTxt original_pMaze{};
			BOOL bKeepMazeRecord = GENERATE(FALSE, TRUE);

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2LvlMazeTxt& pMaze
			) {
				pLevel.pMaze = &pMaze;
			};

			setup_data(moo_pLevel, moo_pMaze);
			setup_data(original_pLevel, original_pMaze);

			// Call both implementations
			sut(&moo_pLevel, bKeepMazeRecord);
			original(&original_pLevel, bKeepMazeRecord);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
}
