#include <D2CommonTestDefines.h>

#ifdef PATHWF_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Collision.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Path/PathWF.h>
#include <Units/Units.h>


DYNAMIC_ARRAY_TYPE(D2PathPointStrc)


TEST_SUITE("PathWFTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDABAC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_FindSubpathWithoutObstacles, dll_base + 0x0006BAC0);
		
		SUBCASE("")
		{
			// nMaxLength 55 replaces the subpath in place, nMaxLength 15 is too short and uses the closest path instead
			for (auto nMaxLength : { 55, 15 })
			{
				// Input data
				D2PathInfoStrc moo_pInfo{};
				D2PathPointStrc moo_pPathPoints[D2DynamicPathStrc::MAXPATHLEN]{};
				int moo_pSubPathStartIdx{};
				int moo_nMaxIndex{};
				D2PathInfoStrc original_pInfo{};
				D2PathPointStrc original_pPathPoints[D2DynamicPathStrc::MAXPATHLEN]{};
				int original_pSubPathStartIdx{};
				int original_nMaxIndex{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t moo_pCollisionMask[20 * 20]{};
				uint16_t original_pCollisionMask[20 * 20]{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2PathPointStrc tSubPathStart{ 1008, 1010 };
				int nMajorDirection = 1;

				const auto setup_data = [](
					D2PathInfoStrc& pInfo,
					D2PathPointStrc(&pPathPoints)[D2DynamicPathStrc::MAXPATHLEN],
					int& pSubPathStartIdx,
					int& nMaxIndex,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[20 * 20],
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pUnit
				) {
					// 20x20 room with a vertical wall at X = 1009 from Y = 1008 to Y = 1012
					pRoom.tCoords.nSubtileX = 1000;
					pRoom.tCoords.nSubtileY = 1000;
					pRoom.tCoords.nSubtileWidth = 20;
					pRoom.tCoords.nSubtileHeight = 20;
					pRoom.pCollisionGrid = &pCollisionGrid;

					pCollisionGrid.pRoomCoords = pRoom.tCoords;
					pCollisionGrid.pCollisionMask = pCollisionMask;
					for (auto y = 8; y <= 12; ++y)
					{
						pCollisionMask[y * 20 + 9] = COLLIDE_WALL;
					}

					pUnit.dwUnitType = UNIT_PLAYER;
					pDynamicPath.pUnit = &pUnit;

					pInfo.tStartCoord = { 1003, 1010 };
					pInfo.tTargetCoord = { 1015, 1010 };
					pInfo.pStartRoom = &pRoom;
					pInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
					pInfo.nCollisionMask = COLLIDE_WALL;
					pInfo.pDynamicPath = &pDynamicPath;

					// Straight line from start to target, the point at index 5 collides with the wall
					for (auto i = 0; i < 12; ++i)
					{
						pPathPoints[i] = { static_cast<uint16_t>(1004 + i), 1010 };
					}
					pSubPathStartIdx = 5;
					nMaxIndex = 12;
				};

				setup_data(moo_pInfo, moo_pPathPoints, moo_pSubPathStartIdx, moo_nMaxIndex, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask, moo_pDynamicPath, moo_pUnit);
				setup_data(original_pInfo, original_pPathPoints, original_pSubPathStartIdx, original_nMaxIndex, original_pRoom, original_pCollisionGrid, original_pCollisionMask, original_pDynamicPath, original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pInfo, tSubPathStart, moo_pPathPoints, &moo_pSubPathStartIdx, &moo_nMaxIndex, nMaxLength, nMajorDirection);
				const auto original_result = original(&original_pInfo, tSubPathStart, original_pPathPoints, &original_pSubPathStartIdx, &original_nMaxIndex, nMaxLength, nMajorDirection);
				
				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pInfo, original_pInfo, "Comparing pInfo");
				MOO_CHECK_EQ((DynamicArray<D2PathPointStrc> { moo_pPathPoints, D2DynamicPathStrc::MAXPATHLEN }), (DynamicArray<D2PathPointStrc> { original_pPathPoints, D2DynamicPathStrc::MAXPATHLEN }), "Comparing pPathPoints");
				MOO_CHECK_EQ(moo_pSubPathStartIdx, original_pSubPathStartIdx, "Comparing pSubPathStartIdx");
				MOO_CHECK_EQ(moo_nMaxIndex, original_nMaxIndex, "Comparing nMaxIndex");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAC170")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SimplifyToLines, dll_base + 0x0006C170);
		
		SUBCASE("")
		{
			for (signed int nbTempPoints = 0; nbTempPoints <= 10; ++nbTempPoints)
			{
				// Input data
				D2PathPointStrc moo_pOutPathPoints[10]{};
				D2PathPointStrc moo_pInputPoints[10]{};
				D2PathPointStrc original_pOutPathPoints[10]{};
				D2PathPointStrc original_pInputPoints[10]{};
				D2PathPointStrc tStartCoord{ 1003, 1010 };

				const auto setup_data = [](
					D2PathPointStrc(&pOutPathPoints)[10],
					D2PathPointStrc(&pInputPoints)[10]
				) {
					// Horizontal, diagonal, vertical and horizontal segments, followed by a single diagonal step
					const D2PathPointStrc points[10] = {
						{ 1004, 1010 }, { 1005, 1010 }, { 1006, 1010 }, { 1007, 1011 }, { 1008, 1012 },
						{ 1008, 1013 }, { 1008, 1014 }, { 1009, 1014 }, { 1010, 1014 }, { 1011, 1015 },
					};
					std::memcpy(pInputPoints, points, sizeof(points));
				};

				setup_data(moo_pOutPathPoints, moo_pInputPoints);
				setup_data(original_pOutPathPoints, original_pInputPoints);

				// Call both implementations
				const auto moo_result = sut(moo_pOutPathPoints, moo_pInputPoints, tStartCoord, nbTempPoints);
				const auto original_result = original(original_pOutPathPoints, original_pInputPoints, tStartCoord, nbTempPoints);
				
				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ((DynamicArray<D2PathPointStrc> { moo_pOutPathPoints, 10 }), (DynamicArray<D2PathPointStrc> { original_pOutPathPoints, 10 }), "Comparing pOutPathPoints");
				MOO_CHECK_EQ((DynamicArray<D2PathPointStrc> { moo_pInputPoints, 10 }), (DynamicArray<D2PathPointStrc> { original_pInputPoints, 10 }), "Comparing pInputPoints");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAC270")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_ComputePathOrSlideAlongObstacles, dll_base + 0x0006C270);
		
		SUBCASE("")
		{
			// nDistMax 60 slides along the wall, nDistMax 20 is too short to get around it
			for (auto nDistMax : { 60, 20 })
			{
				// Target behind the wall, target diagonal behind the wall and target in front of the wall
				for (const auto target : { D2PathPointStrc{ 1015, 1010 }, D2PathPointStrc{ 1015, 1007 }, D2PathPointStrc{ 1007, 1004 } })
				{
					// Input data
					D2PathInfoStrc moo_ptPathInfo{};
					D2PathInfoStrc original_ptPathInfo{};
					D2ActiveRoomStrc moo_pRoom{};
					D2ActiveRoomStrc original_pRoom{};
					D2RoomCollisionGridStrc moo_pCollisionGrid{};
					D2RoomCollisionGridStrc original_pCollisionGrid{};
					uint16_t moo_pCollisionMask[20 * 20]{};
					uint16_t original_pCollisionMask[20 * 20]{};
					D2DynamicPathStrc moo_pDynamicPath{};
					D2DynamicPathStrc original_pDynamicPath{};
					D2UnitStrc moo_pUnit{};
					D2UnitStrc original_pUnit{};

					const auto setup_data = [nDistMax, target](
						D2PathInfoStrc& ptPathInfo,
						D2ActiveRoomStrc& pRoom,
						D2RoomCollisionGridStrc& pCollisionGrid,
						uint16_t(&pCollisionMask)[20 * 20],
						D2DynamicPathStrc& pDynamicPath,
						D2UnitStrc& pUnit
					) {
						// 20x20 room with a vertical wall at X = 1009 from Y = 1008 to Y = 1012
						pRoom.tCoords.nSubtileX = 1000;
						pRoom.tCoords.nSubtileY = 1000;
						pRoom.tCoords.nSubtileWidth = 20;
						pRoom.tCoords.nSubtileHeight = 20;
						pRoom.pCollisionGrid = &pCollisionGrid;

						pCollisionGrid.pRoomCoords = pRoom.tCoords;
						pCollisionGrid.pCollisionMask = pCollisionMask;
						for (auto y = 8; y <= 12; ++y)
						{
							pCollisionMask[y * 20 + 9] = COLLIDE_WALL;
						}

						pUnit.dwUnitType = UNIT_PLAYER;
						pDynamicPath.pUnit = &pUnit;
						pDynamicPath.nDistMax = nDistMax;

						ptPathInfo.tStartCoord = { 1003, 1010 };
						ptPathInfo.tTargetCoord = target;
						ptPathInfo.pStartRoom = &pRoom;
						ptPathInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
						ptPathInfo.nCollisionMask = COLLIDE_WALL;
						ptPathInfo.pDynamicPath = &pDynamicPath;
					};

					setup_data(moo_ptPathInfo, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask, moo_pDynamicPath, moo_pUnit);
					setup_data(original_ptPathInfo, original_pRoom, original_pCollisionGrid, original_pCollisionMask, original_pDynamicPath, original_pUnit);

					// Call both implementations
					const auto moo_result = sut(&moo_ptPathInfo);
					const auto original_result = original(&original_ptPathInfo);
					
					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_ptPathInfo, original_ptPathInfo, "Comparing ptPathInfo");
					MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
				}
			}
		}
	}
}

#endif
