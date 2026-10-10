#include <D2CommonTestDefines.h>

#ifdef ASTAR_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <Path/AStar.h>


TEST_SUITE("AStarTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA69E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AStar_ComputePath, dll_base + 0x000669E0);
		
		SUBCASE("")
		{
			// Input data
			const auto start_x = static_cast<uint16_t>(random_unsigned_integer(10, 65525));
			const auto start_y = static_cast<uint16_t>(random_unsigned_integer(10, 65525));
			const auto target_x = static_cast<uint16_t>(random_unsigned_integer(10, 65525));
			const auto target_y = static_cast<uint16_t>(random_unsigned_integer(10, 65525));

			D2PathInfoStrc moo_pPathInfo{};
			D2ActiveRoomStrc moo_pStartRoom{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2PathInfoStrc original_pPathInfo{};
			D2ActiveRoomStrc original_pStartRoom{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [start_x, start_y, target_x, target_y](
				D2PathInfoStrc& pPathInfo,
				D2ActiveRoomStrc& pStartRoom,
				D2DynamicPathStrc& pDynamicPath
			) {
				// An all-zero room never resolves to a valid room for any coordinate
				// (its bounding box is empty), so every collision check made while
				// exploring neighbors will deterministically report a collision.
				pPathInfo.tStartCoord = { start_x, start_y };
				pPathInfo.tTargetCoord = { target_x, target_y };
				pPathInfo.pStartRoom = &pStartRoom;
				// pDynamicPath->pTargetUnit must be null so that the "enough room at
				// target" pre-check short-circuits without touching collision data.
				pPathInfo.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pPathInfo, moo_pStartRoom, moo_pDynamicPath);
			setup_data(original_pPathInfo, original_pStartRoom, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pPathInfo);
			const auto original_result = original(&original_pPathInfo);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA6D10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AStar_PushToVisitedCache, dll_base + 0x00066D10);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2PathFoWallContextStrc moo_pContext{};
			D2PathFoWallNodeStrc moo_pNode{};
			D2PathFoWallContextStrc original_pContext{};
			D2PathFoWallNodeStrc original_pNode{};

			const auto setup_data = [x, y](
				D2PathFoWallContextStrc& pContext,
				D2PathFoWallNodeStrc& pNode
			) {
				pNode.tPoint.X = x;
				pNode.tPoint.Y = y;
			};

			setup_data(moo_pContext, moo_pNode);
			setup_data(original_pContext, original_pNode);

			// Call both implementations
			const auto moo_result = sut(&moo_pContext, &moo_pNode);
			const auto original_result = original(&original_pContext, &original_pNode);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pContext, original_pContext, "Comparing pContext");
			MOO_CHECK_EQ(moo_pNode, original_pNode, "Comparing pNode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA6D50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AStar_ExploreChildren, dll_base + 0x00066D50);
		
		SUBCASE("")
		{
			// Input data
			const auto x = static_cast<uint16_t>(random_unsigned_integer(10, 65525));
			const auto y = static_cast<uint16_t>(random_unsigned_integer(10, 65525));

			D2PathInfoStrc moo_pPathInfo{};
			D2ActiveRoomStrc moo_pStartRoom{};
			D2PathFoWallContextStrc moo_pContext{};
			D2PathFoWallNodeStrc moo_a3{};
			D2PathInfoStrc original_pPathInfo{};
			D2ActiveRoomStrc original_pStartRoom{};
			D2PathFoWallContextStrc original_pContext{};
			D2PathFoWallNodeStrc original_a3{};
			D2PathPointStrc tTargetCoord{};

			const auto setup_data = [x, y](
				D2PathInfoStrc& pPathInfo,
				D2ActiveRoomStrc& pStartRoom,
				D2PathFoWallContextStrc& pContext,
				D2PathFoWallNodeStrc& a3
			) {
				// An all-zero room never resolves to a valid room for any coordinate
				// (its bounding box is empty), so every collision check made while
				// exploring neighbors will deterministically report a collision.
				pPathInfo.pStartRoom = &pStartRoom;
				a3.tPoint = { x, y };
			};

			setup_data(moo_pPathInfo, moo_pStartRoom, moo_pContext, moo_a3);
			setup_data(original_pPathInfo, original_pStartRoom, original_pContext, original_a3);

			// Call both implementations
			const auto moo_result = sut(&moo_pPathInfo, &moo_pContext, &moo_a3, tTargetCoord);
			const auto original_result = original(&original_pPathInfo, &original_pContext, &original_a3, tTargetCoord);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
			MOO_CHECK_EQ(moo_pContext, original_pContext, "Comparing pContext");
			MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA7230")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AStar_Heuristic, dll_base + 0x00067230);
		
		SUBCASE("")
		{
			D2PathPointStrc tPoint1{ static_cast<uint16_t>(random_unsigned_integer(0, 65535)), static_cast<uint16_t>(random_unsigned_integer(0, 65535)) };
			D2PathPointStrc tPoint2{ static_cast<uint16_t>(random_unsigned_integer(0, 65535)), static_cast<uint16_t>(random_unsigned_integer(0, 65535)) };
			
			// Call both implementations
			const auto moo_result = sut(tPoint1, tPoint2);
			const auto original_result = original(tPoint1, tPoint2);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA7280")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AStar_GetNodeFromPendingCache, dll_base + 0x00067280);
		
		SUBCASE("")
		{
			// Input data
			D2PathFoWallContextStrc moo_pContext{};
			D2PathFoWallContextStrc original_pContext{};
			D2PathPointStrc tPathPoint{ static_cast<uint16_t>(random_unsigned_integer(0, 65535)), static_cast<uint16_t>(random_unsigned_integer(0, 65535)) };

			const auto setup_data = [tPathPoint](
				D2PathFoWallContextStrc& pContext
			) {
				// Fill every cache bucket with a node matching tPathPoint, so the
				// lookup succeeds regardless of which bucket the point hashes to.
				for (size_t i = 0; i < D2PathFoWallContextStrc::CACHE_SIZE; ++i)
				{
					pContext.aNodesStorage[i].tPoint = tPathPoint;
					pContext.aPendingCache[i] = &pContext.aNodesStorage[i];
				}
			};

			setup_data(moo_pContext);
			setup_data(original_pContext);

			// Call both implementations
			const auto moo_result = sut(&moo_pContext, tPathPoint);
			const auto original_result = original(&original_pContext, tPathPoint);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pContext, original_pContext, "Comparing pContext");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA72D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AStar_FindPointInVisitedCache, dll_base + 0x000672D0);
		
		SUBCASE("")
		{
			// Input data
			D2PathFoWallContextStrc moo_pContext{};
			D2PathFoWallContextStrc original_pContext{};
			D2PathPointStrc tPathPoint{ static_cast<uint16_t>(random_unsigned_integer(0, 65535)), static_cast<uint16_t>(random_unsigned_integer(0, 65535)) };

			const auto setup_data = [tPathPoint](
				D2PathFoWallContextStrc& pContext
			) {
				// Fill every cache bucket with a node matching tPathPoint, so the
				// lookup succeeds regardless of which bucket the point hashes to.
				for (size_t i = 0; i < D2PathFoWallContextStrc::CACHE_SIZE; ++i)
				{
					pContext.aNodesStorage[i].tPoint = tPathPoint;
					pContext.aVisitedCache[i] = &pContext.aNodesStorage[i];
				}
			};

			setup_data(moo_pContext);
			setup_data(original_pContext);

			// Call both implementations
			const auto moo_result = sut(&moo_pContext, tPathPoint);
			const auto original_result = original(&original_pContext, tPathPoint);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pContext, original_pContext, "Comparing pContext");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA7320")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AStar_MakeCandidate, dll_base + 0x00067320);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto x = static_cast<uint16_t>(random_unsigned_integer(0, 65535));
			const auto y = static_cast<uint16_t>(random_unsigned_integer(0, 65535));
			const auto nFScore = static_cast<int16_t>(random_unsigned_integer(0, 1000));
			const auto nExistingFScore = static_cast<int16_t>(random_unsigned_integer(0, 1000));

			D2PathFoWallContextStrc moo_pContext{};
			D2PathFoWallNodeStrc moo_pNode{};
			D2PathFoWallContextStrc original_pContext{};
			D2PathFoWallNodeStrc original_pNode{};

			const auto setup_data = [x, y, nFScore, nExistingFScore](
				D2PathFoWallContextStrc& pContext,
				D2PathFoWallNodeStrc& pNode
			) {
				pNode.tPoint = { x, y };
				pNode.nFScore = nFScore;

				// Pre-populate the sorted list with an existing candidate, to
				// exercise the insertion point search.
				pContext.aNodesStorage[0].nFScore = nExistingFScore;
				pContext.pSortedListByFScore = &pContext.aNodesStorage[0];
			};

			setup_data(moo_pContext, moo_pNode);
			setup_data(original_pContext, original_pNode);

			// Call both implementations
			sut(&moo_pContext, &moo_pNode);
			original(&original_pContext, &original_pNode);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pContext, original_pContext, "Comparing pContext");
			MOO_CHECK_EQ(moo_pNode, original_pNode, "Comparing pNode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA7390")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AStar_PropagateNewFScoreToChildren, dll_base + 0x00067390);
		
		SUBCASE("")
		{
			// Input data
			D2PathFoWallContextStrc moo_pContext{};
			D2PathFoWallNodeStrc moo_pNewNode{};
			D2PathFoWallNodeStrc moo_pChildNode{};
			D2PathFoWallContextStrc original_pContext{};
			D2PathFoWallNodeStrc original_pNewNode{};
			D2PathFoWallNodeStrc original_pChildNode{};
			int nUnused{};

			const auto setup_data = [](
				D2PathFoWallContextStrc& pContext,
				D2PathFoWallNodeStrc& pNewNode,
				D2PathFoWallNodeStrc& pChildNode
			) {
				pNewNode.tPoint = { 10, 10 };
				pNewNode.nBestDistanceFromStart = 0;
				pNewNode.pChildren[0] = &pChildNode;

				// Give the child a much larger distance from start than what it
				// would get through pNewNode, so the propagation updates it.
				pChildNode.tPoint = { 11, 11 };
				pChildNode.nBestDistanceFromStart = 200;
				pChildNode.nHeuristicDistanceToTarget = 42;
			};

			setup_data(moo_pContext, moo_pNewNode, moo_pChildNode);
			setup_data(original_pContext, original_pNewNode, original_pChildNode);

			// Call both implementations
			sut(&moo_pContext, nUnused, &moo_pNewNode);
			original(&original_pContext, nUnused, &original_pNewNode);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pContext, original_pContext, "Comparing pContext");
			MOO_CHECK_EQ(moo_pNewNode, original_pNewNode, "Comparing pNewNode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA7490")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AStar_EvaluateNeighbor, dll_base + 0x00067490);
		
		SUBCASE("")
		{
			// Input data
			D2PathInfoStrc moo_pPathInfo{};
			D2PathFoWallContextStrc moo_pContext{};
			D2PathFoWallNodeStrc moo_pCurrentNode{};
			D2PathInfoStrc original_pPathInfo{};
			D2PathFoWallContextStrc original_pContext{};
			D2PathFoWallNodeStrc original_pCurrentNode{};
			D2PathPointStrc tNewPointCoord{ 11, 10 };
			D2PathPointStrc tTargetCoord{ static_cast<uint16_t>(random_unsigned_integer(0, 65535)), static_cast<uint16_t>(random_unsigned_integer(0, 65535)) };

			const auto setup_data = [](
				D2PathInfoStrc& pPathInfo,
				D2PathFoWallContextStrc& pContext,
				D2PathFoWallNodeStrc& pCurrentNode
			) {
				// Both pending and visited caches are empty, so the neighbor will
				// be allocated as a brand new node.
				pCurrentNode.tPoint = { 10, 10 };
				pCurrentNode.nBestDistanceFromStart = 5;
			};

			setup_data(moo_pPathInfo, moo_pContext, moo_pCurrentNode);
			setup_data(original_pPathInfo, original_pContext, original_pCurrentNode);

			// Call both implementations
			const auto moo_result = sut(&moo_pPathInfo, &moo_pContext, &moo_pCurrentNode, tNewPointCoord, tTargetCoord);
			const auto original_result = original(&original_pPathInfo, &original_pContext, &original_pCurrentNode, tNewPointCoord, tTargetCoord);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
			MOO_CHECK_EQ(moo_pContext, original_pContext, "Comparing pContext");
			MOO_CHECK_EQ(moo_pCurrentNode, original_pCurrentNode, "Comparing pCurrentNode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA78A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AStar_FlushNodeToDynamicPath, dll_base + 0x000678A0);
		
		SUBCASE("")
		{
			// Input data
			D2PathFoWallNodeStrc moo_pNode{};
			D2PathInfoStrc moo_pPathInfo{};
			D2PathFoWallNodeStrc moo_pParentNode{};
			D2PathFoWallNodeStrc moo_pStartNode{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2PathFoWallNodeStrc original_pNode{};
			D2PathInfoStrc original_pPathInfo{};
			D2PathFoWallNodeStrc original_pParentNode{};
			D2PathFoWallNodeStrc original_pStartNode{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [](
				D2PathFoWallNodeStrc& pNode,
				D2PathInfoStrc& pPathInfo,
				D2PathFoWallNodeStrc& pParentNode,
				D2PathFoWallNodeStrc& pStartNode,
				D2DynamicPathStrc& pDynamicPath
			) {
				// Build a 3 point path (pStartNode -> pParentNode -> pNode), with a
				// change of direction at every step so that none of the points are
				// skipped by the straight line compression.
				pStartNode.tPoint = { 0, 0 };

				pParentNode.tPoint = { 1, 1 };
				pParentNode.pBestParent = &pStartNode;

				pNode.tPoint = { 2, 1 };
				pNode.pBestParent = &pParentNode;

				pPathInfo.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pNode, moo_pPathInfo, moo_pParentNode, moo_pStartNode, moo_pDynamicPath);
			setup_data(original_pNode, original_pPathInfo, original_pParentNode, original_pStartNode, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pNode, &moo_pPathInfo);
			const auto original_result = original(&original_pNode, &original_pPathInfo);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pNode, original_pNode, "Comparing pNode");
			MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
}

#endif
