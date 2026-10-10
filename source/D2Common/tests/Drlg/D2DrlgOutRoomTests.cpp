#include <D2CommonTestDefines.h>

#ifdef DRLG_OUTROOM_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Fog.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgDrlgVer.h>
#include <Drlg/D2DrlgOutRoom.h>

#include <Fixtures/DataTbls/Fixtures.h>


TEST_SUITE("D2DrlgOutRoomTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD83D20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTROOM_FreeDrlgOutdoorRoom, dll_base + 0x00043D20);
		
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
				pDrlgRoom.pLevel = &pLevel;
				pLevel.pDrlg = &pDrlg;

				// The outdoor room and its data are freed by the tested function
				pDrlgRoom.pOutdoor = D2_CALLOC_STRC_POOL(pDrlg.pMempool, D2DrlgOutdoorRoomStrc);
				pDrlgRoom.pOutdoor->pVertex = D2_CALLOC_STRC_POOL(pDrlg.pMempool, D2DrlgVertexStrc);
				pDrlgRoom.pOutdoor->pWallGrid.pCellsRowOffsets = (int32_t*)D2_CALLOC_POOL(pDrlg.pMempool, sizeof(int32_t));
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			CHECK(moo_pDrlgRoom.pOutdoor == nullptr);
			CHECK(original_pDrlgRoom.pOutdoor == nullptr);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD83D90")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTROOM_FreeDrlgOutdoorRoomData, dll_base + 0x00043D90);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgOutdoorRoomStrc moo_pOutdoor{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgOutdoorRoomStrc original_pOutdoor{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgOutdoorRoomStrc& pOutdoor
			) {
				pDrlgRoom.pLevel = &pLevel;
				pLevel.pDrlg = &pDrlg;
				pDrlgRoom.pOutdoor = &pOutdoor;

				// Only the data of the outdoor room is freed by the tested function
				pOutdoor.pVertex = D2_CALLOC_STRC_POOL(pDrlg.pMempool, D2DrlgVertexStrc);
				pOutdoor.pTileTypeGrid.pCellsRowOffsets = (int32_t*)D2_CALLOC_POOL(pDrlg.pMempool, sizeof(int32_t));
				pOutdoor.pWallGrid.pCellsRowOffsets = (int32_t*)D2_CALLOC_POOL(pDrlg.pMempool, sizeof(int32_t));
				pOutdoor.pFloorGrid.pCellsRowOffsets = (int32_t*)D2_CALLOC_POOL(pDrlg.pMempool, sizeof(int32_t));
				pOutdoor.pDirtPathGrid.pCellsRowOffsets = (int32_t*)D2_CALLOC_POOL(pDrlg.pMempool, sizeof(int32_t));
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pOutdoor);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_pOutdoor);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pOutdoor, original_pOutdoor, "Comparing pOutdoor");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD83DE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTROOM_AllocDrlgOutdoorRoom, dll_base + 0x00043DE0);
		
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
				pDrlgRoom.pLevel = &pLevel;
				pLevel.pDrlg = &pDrlg;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");

			REQUIRE(moo_pDrlgRoom.pOutdoor != nullptr);
			REQUIRE(original_pDrlgRoom.pOutdoor != nullptr);
			MOO_CHECK_EQ(*moo_pDrlgRoom.pOutdoor, *original_pDrlgRoom.pOutdoor, "Comparing pOutdoor");

			// Clean up
			D2_FREE_POOL(moo_pDrlg.pMempool, moo_pDrlgRoom.pOutdoor);
			D2_FREE_POOL(original_pDrlg.pMempool, original_pDrlgRoom.pOutdoor);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD83EC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTROOM_LinkLevelsByLevelCoords, dll_base + 0x00043EC0);
		
		SUBCASE("")
		{
			// Use several seeds to hit both orientations of the level
			for (auto i = 0; i < 16; ++i)
			{
				// Input data
				const auto nLowSeed = random_unsigned_integer();
				const auto nHighSeed = random_unsigned_integer();
				const auto nPosX = (int32_t)random_unsigned_integer(0, 1024);
				const auto nPosY = (int32_t)random_unsigned_integer(0, 1024);
				const auto nHeight = (int32_t)random_unsigned_integer(0, 256);

				D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
				D2DrlgLinkStrc moo_pLink[2]{};
				D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
				D2DrlgLinkStrc original_pLink[2]{};

				const auto setup_data = [nLowSeed, nHighSeed, nPosX, nPosY, nHeight](
					D2DrlgLevelLinkDataStrc& pLevelLinkData,
					D2DrlgLinkStrc (&pLink)[2]
				) {
					pLevelLinkData.pSeed.nLowSeed = nLowSeed;
					pLevelLinkData.pSeed.nHighSeed = nHighSeed;

					// Level 1 is linked to level 0
					pLevelLinkData.nIteration = 1;
					pLevelLinkData.pLink = pLink;
					pLink[1].nLevelLink = 0;

					pLevelLinkData.pLevelCoord[0].nPosX = nPosX;
					pLevelLinkData.pLevelCoord[0].nPosY = nPosY;
					pLevelLinkData.pLevelCoord[0].nHeight = nHeight;
				};

				setup_data(moo_pLevelLinkData, moo_pLink);
				setup_data(original_pLevelLinkData, original_pLink);

				// Call both implementations
				const auto moo_result = sut(&moo_pLevelLinkData);
				const auto original_result = original(&original_pLevelLinkData);
				
				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
			}
		}
	}
	
	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>, "D2Common.0x6FD83F70")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTROOM_LinkLevelsByLevelDef, dll_base + 0x00043F70);
		
		SUBCASE("")
		{
			for (auto i = 0; i < leveldefs_record_count; ++i)
			{
				// Input data
				const auto nLowSeed = random_unsigned_integer();
				const auto nHighSeed = random_unsigned_integer();
				const auto nCurrentLevel = i;

				D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
				D2DrlgLevelLinkDataStrc original_pLevelLinkData{};

				const auto setup_data = [nLowSeed, nHighSeed, nCurrentLevel](
					D2DrlgLevelLinkDataStrc& pLevelLinkData
				) {
					pLevelLinkData.pSeed.nLowSeed = nLowSeed;
					pLevelLinkData.pSeed.nHighSeed = nHighSeed;
					pLevelLinkData.nCurrentLevel = nCurrentLevel;
				};

				setup_data(moo_pLevelLinkData);
				setup_data(original_pLevelLinkData);

				// Call both implementations
				const auto moo_result = sut(&moo_pLevelLinkData);
				const auto original_result = original(&original_pLevelLinkData);
				
				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD84010")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTROOM_LinkLevelsByOffsetCoords, dll_base + 0x00044010);
		
		SUBCASE("")
		{
			// nRand[1] == -1 rolls a new orientation, 0 / 1 toggles or rejects the current one
			for (auto nRand1 = -1; nRand1 <= 1; ++nRand1)
			{
				for (auto nRand0 = 0; nRand0 <= 1; ++nRand0)
				{
					for (auto nLinkedRand0 = 0; nLinkedRand0 <= 1; ++nLinkedRand0)
					{
						// Input data
						const auto nLowSeed = random_unsigned_integer();
						const auto nHighSeed = random_unsigned_integer();
						const auto nPosX = (int32_t)random_unsigned_integer(0, 1024);
						const auto nPosY = (int32_t)random_unsigned_integer(0, 1024);

						D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
						D2DrlgLinkStrc moo_pLink[2]{};
						D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
						D2DrlgLinkStrc original_pLink[2]{};

						const auto setup_data = [nLowSeed, nHighSeed, nPosX, nPosY, nRand1, nRand0, nLinkedRand0](
							D2DrlgLevelLinkDataStrc& pLevelLinkData,
							D2DrlgLinkStrc (&pLink)[2]
						) {
							pLevelLinkData.pSeed.nLowSeed = nLowSeed;
							pLevelLinkData.pSeed.nHighSeed = nHighSeed;

							// Level 1 is linked to level 0
							pLevelLinkData.nIteration = 1;
							pLevelLinkData.pLink = pLink;
							pLink[1].nLevelLink = 0;

							pLevelLinkData.nRand[0][1] = nRand0;
							pLevelLinkData.nRand[1][1] = nRand1;
							pLevelLinkData.nRand[0][0] = nLinkedRand0;

							pLevelLinkData.pLevelCoord[0].nPosX = nPosX;
							pLevelLinkData.pLevelCoord[0].nPosY = nPosY;
						};

						setup_data(moo_pLevelLinkData, moo_pLink);
						setup_data(original_pLevelLinkData, original_pLink);

						// Call both implementations
						const auto moo_result = sut(&moo_pLevelLinkData);
						const auto original_result = original(&original_pLevelLinkData);
						
						// Compare return values
						MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
					}
				}
			}
		}
	}
}

#endif
