#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

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
		
		SUBCASE("")
		{
			for (auto i = 0; i < 16; ++i)
			{
				const auto speed = random_unsigned_integer(0, 10);

				const auto setup_data = [speed, i]() {
					D2UnitStrc pTargetUnit{};
					pTargetUnit.dwUnitType = UNIT_PLAYER;

					D2DynamicPathStrc pDynamicPath{};

					pDynamicPath.nDirection = i;

					pDynamicPath.tGameCoords.wPosX = random_unsigned_integer(0, 65535);
					pDynamicPath.tGameCoords.wPosY = random_unsigned_integer(0, 65535);

					pTargetUnit.pDynamicPath = &pDynamicPath;

					D2DynamicPathStrc ptPath{};

					ptPath.pTargetUnit = &pTargetUnit;

					ptPath.dwSpeed = speed;

					return std::tuple{ ptPath, pDynamicPath, pTargetUnit };
				};

				// Input data
				auto [moo_ptPath, moo_pDynamicPath, moo_pTargetUnit] = setup_data();
				auto [original_ptPath, original_pDynamicPath, original_pTargetUnit] = setup_data();

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
		
		SUBCASE("Static target")
		{
			const auto setup_data = []() {
				D2UnitStrc pTargetUnit{};
				pTargetUnit.dwUnitType = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);

				D2StaticPathStrc pStaticPath{};
				pStaticPath.tGameCoords.nX = random_unsigned_integer(0, 65535);
				pStaticPath.tGameCoords.nY = random_unsigned_integer(0, 65535);

				pTargetUnit.pStaticPath = &pStaticPath;

				D2PathPointStrc pOutPathPoint{};
				D2DynamicPathStrc ptPath{};

				ptPath.pTargetUnit = &pTargetUnit;
				
				return std::tuple{ pOutPathPoint, ptPath, pStaticPath, pTargetUnit };
			};
			
			// Input data
			auto [moo_pOutPathPoint, moo_ptPath, moo_pStaticPath, moo_pTargetUnit] = setup_data();
			auto [original_pOutPathPoint, original_ptPath, original_pStaticPath, original_pTargetUnit] = setup_data();

			// Call both implementations
			sut(&moo_pOutPathPoint, &moo_ptPath);
			original(&original_pOutPathPoint, &original_ptPath);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pOutPathPoint, original_pOutPathPoint, "Comparing pOutPathPoint");
			MOO_CHECK_EQ(moo_ptPath, original_ptPath, "Comparing ptPath");
		}

		SUBCASE("Dynamic target")
		{
			const auto setup_data = []() {
				D2UnitStrc pTargetUnit{};
				pTargetUnit.dwUnitType = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);

				D2DynamicPathStrc pDynamicPath{};

				pDynamicPath.tGameCoords.wPosX = random_unsigned_integer(0, 65535);
				pDynamicPath.tGameCoords.wPosY = random_unsigned_integer(0, 65535);

				pTargetUnit.pDynamicPath = &pDynamicPath;

				D2PathPointStrc pOutPathPoint{};
				D2DynamicPathStrc ptPath{};

				ptPath.pTargetUnit = &pTargetUnit;

				return std::tuple{ pOutPathPoint, ptPath, pDynamicPath, pTargetUnit };
			};

			// Input data
			auto [moo_pOutPathPoint, moo_ptPath, moo_pDynamicPath, moo_pTargetUnit] = setup_data();
			auto [original_pOutPathPoint, original_ptPath, original_pDynamicPath, original_pTargetUnit] = setup_data();

			// Call both implementations
			sut(&moo_pOutPathPoint, &moo_ptPath);
			original(&original_pOutPathPoint, &original_ptPath);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pOutPathPoint, original_pOutPathPoint, "Comparing pOutPathPoint");
			MOO_CHECK_EQ(moo_ptPath, original_ptPath, "Comparing ptPath");
		}
	}
}
