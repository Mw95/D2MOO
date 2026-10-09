#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <memory>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Collision.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Path/IDAStar.h>


TEST_SUITE("IDAStarTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	constexpr int32_t nRoomX = 200;
	constexpr int32_t nRoomY = 200;
	constexpr int32_t nRoomSize = 20;

	// Sets up a room together with its collision grid. A vertical wall can optionally be placed at nWallX,
	// covering all rows except the last one so that a path around it exists.
	const auto setup_room = [](
		D2ActiveRoomStrc& pRoom,
		D2RoomCollisionGridStrc& pCollisionGrid,
		uint16_t* pCollisionMask,
		int32_t nX,
		int32_t nY,
		int32_t nWallX
	) {
		pRoom.tCoords.nSubtileX = nX;
		pRoom.tCoords.nSubtileY = nY;
		pRoom.tCoords.nSubtileWidth = nRoomSize;
		pRoom.tCoords.nSubtileHeight = nRoomSize;
		pRoom.pCollisionGrid = &pCollisionGrid;

		pCollisionGrid.pRoomCoords = pRoom.tCoords;
		pCollisionGrid.pCollisionMask = pCollisionMask;

		if (nWallX >= 0)
		{
			for (int32_t y = 0; y < nRoomSize - 1; ++y)
			{
				pCollisionMask[nWallX + y * nRoomSize] = COLLIDE_WALL;
			}
		}
	};

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA7970")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_IdaStar_6FDA7970, dll_base + 0x00067970);
		
		REPEAT_10();

		SUBCASE("Single room")
		{
			const auto has_wall = random_unsigned_integer(0, 1) != 0;
			const D2PathPointStrc tStartCoord{ static_cast<uint16_t>(nRoomX + random_unsigned_integer(1, 7)), static_cast<uint16_t>(nRoomY + random_unsigned_integer(1, nRoomSize - 2)) };
			const D2PathPointStrc tTargetCoord{ static_cast<uint16_t>(nRoomX + random_unsigned_integer(12, nRoomSize - 2)), static_cast<uint16_t>(nRoomY + random_unsigned_integer(1, nRoomSize - 2)) };

			// Input data
			D2PathInfoStrc moo_pPathInfo{};
			D2ActiveRoomStrc moo_pStartRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_aCollisionMask[nRoomSize * nRoomSize]{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2PathInfoStrc original_pPathInfo{};
			D2ActiveRoomStrc original_pStartRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_aCollisionMask[nRoomSize * nRoomSize]{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [has_wall, tStartCoord, tTargetCoord](
				D2PathInfoStrc& pPathInfo,
				D2ActiveRoomStrc& pStartRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t* pCollisionMask,
				D2DynamicPathStrc& pDynamicPath
			) {
				setup_room(pStartRoom, pCollisionGrid, pCollisionMask, nRoomX, nRoomY, has_wall ? 10 : -1);

				pPathInfo.tStartCoord = tStartCoord;
				pPathInfo.tTargetCoord = tTargetCoord;
				pPathInfo.pStartRoom = &pStartRoom;
				pPathInfo.pTargetRoom = nullptr;
				pPathInfo.field_14 = 1;
				pPathInfo.nMinimumFScoreToEvaluate = 255;
				pPathInfo.nPathType = PATHTYPE_IDASTAR;
				pPathInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
				pPathInfo.nCollisionMask = COLLIDE_WALL;
				pPathInfo.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pPathInfo, moo_pStartRoom, moo_pCollisionGrid, moo_aCollisionMask, moo_pDynamicPath);
			setup_data(original_pPathInfo, original_pStartRoom, original_pCollisionGrid, original_aCollisionMask, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pPathInfo);
			const auto original_result = original(&original_pPathInfo);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}

		SUBCASE("Target in adjacent room")
		{
			const D2PathPointStrc tStartCoord{ static_cast<uint16_t>(nRoomX + random_unsigned_integer(1, nRoomSize - 2)), static_cast<uint16_t>(nRoomY + random_unsigned_integer(1, nRoomSize - 2)) };
			const D2PathPointStrc tTargetCoord{ static_cast<uint16_t>(nRoomX + nRoomSize + random_unsigned_integer(1, nRoomSize - 2)), static_cast<uint16_t>(nRoomY + random_unsigned_integer(1, nRoomSize - 2)) };

			// Input data
			D2PathInfoStrc moo_pPathInfo{};
			D2ActiveRoomStrc moo_pStartRoom{};
			D2RoomCollisionGridStrc moo_pStartCollisionGrid{};
			uint16_t moo_aStartCollisionMask[nRoomSize * nRoomSize]{};
			D2ActiveRoomStrc moo_pTargetRoom{};
			D2RoomCollisionGridStrc moo_pTargetCollisionGrid{};
			uint16_t moo_aTargetCollisionMask[nRoomSize * nRoomSize]{};
			D2ActiveRoomStrc* moo_aAdjacentRooms[1]{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2PathInfoStrc original_pPathInfo{};
			D2ActiveRoomStrc original_pStartRoom{};
			D2RoomCollisionGridStrc original_pStartCollisionGrid{};
			uint16_t original_aStartCollisionMask[nRoomSize * nRoomSize]{};
			D2ActiveRoomStrc original_pTargetRoom{};
			D2RoomCollisionGridStrc original_pTargetCollisionGrid{};
			uint16_t original_aTargetCollisionMask[nRoomSize * nRoomSize]{};
			D2ActiveRoomStrc* original_aAdjacentRooms[1]{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [tStartCoord, tTargetCoord](
				D2PathInfoStrc& pPathInfo,
				D2ActiveRoomStrc& pStartRoom,
				D2RoomCollisionGridStrc& pStartCollisionGrid,
				uint16_t* pStartCollisionMask,
				D2ActiveRoomStrc& pTargetRoom,
				D2RoomCollisionGridStrc& pTargetCollisionGrid,
				uint16_t* pTargetCollisionMask,
				D2ActiveRoomStrc** pAdjacentRooms,
				D2DynamicPathStrc& pDynamicPath
			) {
				setup_room(pStartRoom, pStartCollisionGrid, pStartCollisionMask, nRoomX, nRoomY, -1);
				setup_room(pTargetRoom, pTargetCollisionGrid, pTargetCollisionMask, nRoomX + nRoomSize, nRoomY, 5);

				pAdjacentRooms[0] = &pTargetRoom;
				pStartRoom.ppRoomList = pAdjacentRooms;
				pStartRoom.nNumRooms = 1;

				pPathInfo.tStartCoord = tStartCoord;
				pPathInfo.tTargetCoord = tTargetCoord;
				pPathInfo.pStartRoom = &pStartRoom;
				pPathInfo.pTargetRoom = &pTargetRoom;
				pPathInfo.field_14 = 1;
				pPathInfo.nMinimumFScoreToEvaluate = 255;
				pPathInfo.nPathType = PATHTYPE_IDASTAR;
				pPathInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
				pPathInfo.nCollisionMask = COLLIDE_WALL;
				pPathInfo.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pPathInfo, moo_pStartRoom, moo_pStartCollisionGrid, moo_aStartCollisionMask, moo_pTargetRoom, moo_pTargetCollisionGrid, moo_aTargetCollisionMask, moo_aAdjacentRooms, moo_pDynamicPath);
			setup_data(original_pPathInfo, original_pStartRoom, original_pStartCollisionGrid, original_aStartCollisionMask, original_pTargetRoom, original_pTargetCollisionGrid, original_aTargetCollisionMask, original_aAdjacentRooms, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pPathInfo);
			const auto original_result = original(&original_pPathInfo);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA7D40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_IDAStar_VisitNodes, dll_base + 0x00067D40);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto has_wall = random_unsigned_integer(0, 1) != 0;
			const auto random_direction = random_unsigned_integer(0, 1) != 0;
			const auto seed = random_unsigned_integer();
			// Start and target on the same row, so the first neighbor to visit (index 0) is towards the target
			const auto y = static_cast<uint16_t>(nRoomY + random_unsigned_integer(1, nRoomSize - 2));
			const D2PathPointStrc tStartCoord{ static_cast<uint16_t>(nRoomX + 3), y };
			const D2PathPointStrc tTargetCoord{ static_cast<uint16_t>(nRoomX + 16), y };
			const auto nHeuristicDistanceToTarget = static_cast<uint16_t>(2 * (tTargetCoord.X - tStartCoord.X));
			const int nFScoreCutoff = nHeuristicDistanceToTarget + static_cast<int>(random_unsigned_integer(0, 40));

			// Input data
			// The context is too big to have two of them on the stack
			const auto moo_pContext = std::make_unique<D2PathIDAStarContextStrc>();
			D2PathInfoStrc moo_pPathInfo{};
			D2ActiveRoomStrc moo_pStartRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_aCollisionMask[nRoomSize * nRoomSize]{};
			int moo_aNeighborsSequence[8]{};
			D2SeedStrc moo_pSeed{};
			const auto original_pContext = std::make_unique<D2PathIDAStarContextStrc>();
			D2PathInfoStrc original_pPathInfo{};
			D2ActiveRoomStrc original_pStartRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_aCollisionMask[nRoomSize * nRoomSize]{};
			int original_aNeighborsSequence[8]{};
			D2SeedStrc original_pSeed{};

			const auto setup_data = [has_wall, random_direction, seed, tStartCoord, tTargetCoord, nHeuristicDistanceToTarget](
				D2PathIDAStarContextStrc& pContext,
				D2PathInfoStrc& pPathInfo,
				D2ActiveRoomStrc& pStartRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t* pCollisionMask,
				int* pNeighborsSequence,
				D2SeedStrc& pSeed
			) {
				setup_room(pStartRoom, pCollisionGrid, pCollisionMask, nRoomX, nRoomY, has_wall ? 10 : -1);

				pPathInfo.tStartCoord = tStartCoord;
				pPathInfo.tTargetCoord = tTargetCoord;
				pPathInfo.pStartRoom = &pStartRoom;
				pPathInfo.field_14 = 1;
				pPathInfo.nPathType = PATHTYPE_IDASTAR;
				pPathInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
				pPathInfo.nCollisionMask = COLLIDE_WALL;

				// Same values as the first row of the neighbors sequence table (D2Common.0x6FDD1BE0)
				const int aFirstNeighborsSequence[8] = { 0, 1, 6, 3, 4, 5, 2, 7 };
				for (int i = 0; i < 8; ++i)
				{
					pNeighborsSequence[i] = aFirstNeighborsSequence[i];
				}

				pSeed.nLowSeed = seed;
				pSeed.nHighSeed = 666;

				// Set up the context like PATH_IdaStar_ComputePathWithRooms does
				pContext.nCoord[0].X = nRoomX;
				pContext.nCoord[0].Y = nRoomY;
				pContext.nCoord[1].X = nRoomX + nRoomSize;
				pContext.nCoord[1].Y = nRoomY + nRoomSize;
				pContext.nCoord[2].X = nRoomSize;
				pContext.nCoord[2].Y = nRoomSize;
				pContext.nStride = nRoomSize + 6;
				pContext.nXOffset = -(nRoomX - 3);
				pContext.nYOffset = -(nRoomY - 3);
				pContext.bRandomDirection = random_direction;
				pContext.pSeed = random_direction ? &pSeed : nullptr;

				D2PathIDAStarNodeStrc& tStartNode = pContext.aNodesStorage[0];
				tStartNode.nBestDistanceFromStart = 0;
				tStartNode.nHeuristicDistanceToTarget = nHeuristicDistanceToTarget;
				tStartNode.nFScore = nHeuristicDistanceToTarget;
				tStartNode.tCoord = tStartCoord;
				tStartNode.nEvaluationsCount = -3;
				tStartNode.pNeighborsSequence = pNeighborsSequence;
				tStartNode.nNextNeighborIndex = 0;

				pContext.nNodesCount = 1;
				pContext.pCurrentNode = &tStartNode;
			};

			setup_data(*moo_pContext, moo_pPathInfo, moo_pStartRoom, moo_pCollisionGrid, moo_aCollisionMask, moo_aNeighborsSequence, moo_pSeed);
			setup_data(*original_pContext, original_pPathInfo, original_pStartRoom, original_pCollisionGrid, original_aCollisionMask, original_aNeighborsSequence, original_pSeed);

			// Call both implementations
			const auto moo_result = sut(moo_pContext.get(), nFScoreCutoff, &moo_pPathInfo);
			const auto original_result = original(original_pContext.get(), nFScoreCutoff, &original_pPathInfo);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(*moo_pContext, *original_pContext, "Comparing pContext");
			MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
			MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
}
