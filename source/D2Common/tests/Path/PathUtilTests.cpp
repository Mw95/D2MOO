#include <D2CommonTestDefines.h>

#ifdef PATHUTIL_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Path/PathUtil.h>


TEST_SUITE("PathUtilTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB890")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATHUtil_AdvanceTowardsTarget_6FDAB890, dll_base + 0x0006B890);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			for (auto i = 0; i < 16; ++i)
			{
				const auto x = random_unsigned_integer(0, 65535);
				const auto y = random_unsigned_integer(0, 65535);
				const auto speed = random_unsigned_integer(0, 10);

				D2DynamicPathStrc moo_ptPath{};
				D2DynamicPathStrc original_ptPath{};
				D2UnitStrc moo_pTargetUnit{};
				D2UnitStrc original_pTargetUnit{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};

				const auto setup_data = [i, speed, x, y](
					D2DynamicPathStrc& ptPath,
					D2UnitStrc& pTargetUnit,
					D2DynamicPathStrc& pDynamicPath
				) {										
					pDynamicPath.nDirection = i;
					pDynamicPath.tGameCoords.wPosX = x;
					pDynamicPath.tGameCoords.wPosY = y;
					
					pTargetUnit.dwUnitType = UNIT_PLAYER;
					pTargetUnit.pDynamicPath = &pDynamicPath;
					
					ptPath.pTargetUnit = &pTargetUnit;
					ptPath.dwSpeed = speed;
				};

				setup_data(moo_ptPath, moo_pTargetUnit, moo_pDynamicPath);
				setup_data(original_ptPath, original_pTargetUnit, original_pDynamicPath);

				// Call both implementations
				sut(&moo_ptPath);
				original(&original_ptPath);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_ptPath, original_ptPath, "Comparing ptPath");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB940")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAB940, dll_base + 0x0006B940);
		
		REPEAT_10();

		SUBCASE("Static target, speed == 0")
		{
			for (auto unit_type : { UNIT_OBJECT, UNIT_ITEM, UNIT_TILE })
			{
				// Input data
				const auto x = random_unsigned_integer(0, 65535);
				const auto y = random_unsigned_integer(0, 65535);
				const auto speed = 0;

				D2PathPointStrc moo_pOutPathPoint{};
				D2DynamicPathStrc moo_ptPath{};
				D2UnitStrc moo_pTargetUnit{};
				D2StaticPathStrc moo_pTargetStaticPath{};
				D2PathPointStrc original_pOutPathPoint{};
				D2DynamicPathStrc original_ptPath{};
				D2UnitStrc original_pTargetUnit{};
				D2StaticPathStrc original_pTargetStaticPath{};

				const auto setup_data = [x, y, speed, unit_type](
					D2PathPointStrc& pOutPathPoint,
					D2DynamicPathStrc& ptPath,
					D2UnitStrc& pTargetUnit,
					D2StaticPathStrc& pTargetStaticPath
				) {
					pTargetStaticPath.tGameCoords.nX = x;
					pTargetStaticPath.tGameCoords.nY = y;
					
					pTargetUnit.dwUnitType = unit_type;
					pTargetUnit.pStaticPath = &pTargetStaticPath;

					ptPath.pTargetUnit = &pTargetUnit;
					ptPath.dwSpeed = speed;
				};

				setup_data(moo_pOutPathPoint, moo_ptPath, moo_pTargetUnit, moo_pTargetStaticPath);
				setup_data(original_pOutPathPoint, original_ptPath, original_pTargetUnit, original_pTargetStaticPath);

				// Call both implementations
				sut(&moo_pOutPathPoint, &moo_ptPath);
				original(&original_pOutPathPoint, &original_ptPath);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pOutPathPoint, original_pOutPathPoint, "Comparing pOutPathPoint");
				MOO_CHECK_EQ(moo_ptPath, original_ptPath, "Comparing ptPath");
			}
		}

		SUBCASE("Static target, speed != 0")
		{
			// Invalid, since static targets can't use PATH_GetDirection(ptTarget->pDynamicPath) in PATHUtil_AdvanceTowardsTarget
		}

		SUBCASE("Dynamic target, speed == 0")
		{
			for (auto unit_type : { UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE })
			{
				// Input data
				const auto x = random_unsigned_integer(0, 65535);
				const auto y = random_unsigned_integer(0, 65535);
				const auto speed = 0;

				D2PathPointStrc moo_pOutPathPoint{};
				D2DynamicPathStrc moo_ptPath{};
				D2UnitStrc moo_pTargetUnit{};
				D2DynamicPathStrc moo_pTargetDynamicPath{};
				D2PathPointStrc original_pOutPathPoint{};
				D2DynamicPathStrc original_ptPath{};
				D2UnitStrc original_pTargetUnit{};
				D2DynamicPathStrc original_pTargetDynamicPath{};

				const auto setup_data = [x, y, speed, unit_type](
					D2PathPointStrc& pOutPathPoint,
					D2DynamicPathStrc& ptPath,
					D2UnitStrc& pTargetUnit,
					D2DynamicPathStrc& pTargetDynamicPath
				) {
					pTargetDynamicPath.tGameCoords.wPosX = x;
					pTargetDynamicPath.tGameCoords.wPosY = y;
					
					pTargetUnit.dwUnitType = unit_type;
					pTargetUnit.pDynamicPath = &pTargetDynamicPath;

					ptPath.pTargetUnit = &pTargetUnit;
					ptPath.dwSpeed = speed;
				};

				setup_data(moo_pOutPathPoint, moo_ptPath, moo_pTargetUnit, moo_pTargetDynamicPath);
				setup_data(original_pOutPathPoint, original_ptPath, original_pTargetUnit, original_pTargetDynamicPath);

				// Call both implementations
				sut(&moo_pOutPathPoint, &moo_ptPath);
				original(&original_pOutPathPoint, &original_ptPath);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pOutPathPoint, original_pOutPathPoint, "Comparing pOutPathPoint");
				MOO_CHECK_EQ(moo_ptPath, original_ptPath, "Comparing ptPath");
			}
		}

		SUBCASE("Dynamic target, speed != 0")
		{
			for (auto unit_type : { UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE })
			{
				// Input data
				const auto x = random_unsigned_integer(0, 65535);
				const auto y = random_unsigned_integer(0, 65535);
				const auto speed = random_unsigned_integer(1, 10);

				D2PathPointStrc moo_pOutPathPoint{};
				D2DynamicPathStrc moo_ptPath{};
				D2UnitStrc moo_pTargetUnit{};
				D2DynamicPathStrc moo_pTargetDynamicPath{};
				D2PathPointStrc original_pOutPathPoint{};
				D2DynamicPathStrc original_ptPath{};
				D2UnitStrc original_pTargetUnit{};
				D2DynamicPathStrc original_pTargetDynamicPath{};

				const auto setup_data = [x, y, speed, unit_type](
					D2PathPointStrc& pOutPathPoint,
					D2DynamicPathStrc& ptPath,
					D2UnitStrc& pTargetUnit,
					D2DynamicPathStrc& pTargetDynamicPath
				) {
					pTargetDynamicPath.tGameCoords.wPosX = x;
					pTargetDynamicPath.tGameCoords.wPosY = y;

					pTargetUnit.dwUnitType = unit_type;
					pTargetUnit.pDynamicPath = &pTargetDynamicPath;

					ptPath.pTargetUnit = &pTargetUnit;
					ptPath.dwSpeed = speed;
				};

				setup_data(moo_pOutPathPoint, moo_ptPath, moo_pTargetUnit, moo_pTargetDynamicPath);
				setup_data(original_pOutPathPoint, original_ptPath, original_pTargetUnit, original_pTargetDynamicPath);

				// Call both implementations
				sut(&moo_pOutPathPoint, &moo_ptPath);
				original(&original_pOutPathPoint, &original_ptPath);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pOutPathPoint, original_pOutPathPoint, "Comparing pOutPathPoint");
				MOO_CHECK_EQ(moo_ptPath, original_ptPath, "Comparing ptPath");
			}
		}
	}
}

#endif
