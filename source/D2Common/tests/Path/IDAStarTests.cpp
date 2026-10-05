#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Collision.h>
#include <Path/IDAStar.h>


TEST_SUITE("IDAStarTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA7970")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_IdaStar_6FDA7970, dll_base + 0x00067970);
		
		SUBCASE("")
		{
			// Input data
			D2PathInfoStrc moo_pPathInfo{};
			D2PathInfoStrc original_pPathInfo{};

			const auto setup_data = [](
				D2PathInfoStrc& pPathInfo
			) {
				// No rooms are set up, so the computed path room AABB degenerates to a small
				// area around the origin; this still exercises the AABB/cutoff computation
				// without requiring a full DRLG room setup.
				pPathInfo.tStartCoord = { 10, 10 };
				pPathInfo.tTargetCoord = { 15, 12 };
				pPathInfo.pStartRoom = nullptr;
				pPathInfo.pTargetRoom = nullptr;
				pPathInfo.field_14 = 2;
				pPathInfo.nMinimumFScoreToEvaluate = 50;
				pPathInfo.nPathType = PATHTYPE_IDASTAR;
				pPathInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
				pPathInfo.nCollisionMask = 0;
			};

			setup_data(moo_pPathInfo);
			setup_data(original_pPathInfo);

			// Call both implementations
			const auto moo_result = sut(&moo_pPathInfo);
			const auto original_result = original(&original_pPathInfo);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA7D40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_IDAStar_VisitNodes, dll_base + 0x00067D40);
		
		SUBCASE("")
		{
			// Input data
			D2PathIDAStarContextStrc moo_pContext{};
			D2PathInfoStrc moo_pPathInfo{};
			D2PathIDAStarContextStrc original_pContext{};
			D2PathInfoStrc original_pPathInfo{};
			// Backing storage for the current node's neighbor sequence pointer.
			// Left at zero so the explored neighbor direction never changes.
			int32_t moo_aNeighborsSequence[8]{};
			int32_t original_aNeighborsSequence[8]{};
			int nFScoreCutoff{};

			const auto setup_data = [](
				D2PathIDAStarContextStrc& pContext,
				D2PathInfoStrc& pPathInfo,
				int32_t (&aNeighborsSequence)[8]
			) {
				// Set up a single current node, within the context bounds, that is not
				// yet at the target, with no room/collision data so the pathing is
				// deterministic (every freshly visited neighbor is reported blocked).
				pContext.pCurrentNode = &pContext.aNodesStorage[0];
				pContext.pCurrentNode->tCoord = { 10, 10 };
				pContext.pCurrentNode->nBestDistanceFromStart = 0;
				pContext.pCurrentNode->nNextNeighborIndex = 0;
				pContext.pCurrentNode->pNeighborsSequence = aNeighborsSequence;
				pContext.pCurrentNode->nEvaluationsCount = 0;
				pContext.pCurrentNode->pParent = nullptr;
				pContext.pCurrentNode->pBestChild = nullptr;
				pContext.nNodesCount = 1;
				pContext.nCoord[0] = { 0, 0 };
				pContext.nCoord[1] = { 20, 20 };
				pContext.nStride = 50;
				pContext.nXOffset = 0;
				pContext.nYOffset = 0;
				pContext.bRandomDirection = FALSE;
				pContext.pSeed = nullptr;

				pPathInfo.tTargetCoord = { 15, 15 };
				pPathInfo.pStartRoom = nullptr;
				pPathInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
				pPathInfo.nCollisionMask = 0;
				pPathInfo.field_14 = 0;
			};

			setup_data(moo_pContext, moo_pPathInfo, moo_aNeighborsSequence);
			setup_data(original_pContext, original_pPathInfo, original_aNeighborsSequence);

			// Call both implementations
			const auto moo_result = sut(&moo_pContext, nFScoreCutoff, &moo_pPathInfo);
			const auto original_result = original(&original_pContext, nFScoreCutoff, &original_pPathInfo);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pContext, original_pContext, "Comparing pContext");
			MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
		}
	}
}
