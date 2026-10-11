#include <D2CommonTestDefines.h>

#ifdef MISSILESTREAM_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Path/Path.h>
#include <Units/MissileStream.h>
#include <Units/Units.h>


TEST_SUITE("MissileStreamTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC230 (#11213)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_AllocMissileStream, dll_base + 0x0007C230);
		const auto [moo_free, original_free] = make_function_pair(MISSTREAM_FreeMissileStream, dll_base + 0x0007C280);

		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2MissileDataStrc moo_pMissileData{};
			D2UnitStrc original_pMissile{};
			D2MissileDataStrc original_pMissileData{};

			const auto setup_data = [](
				D2UnitStrc& pMissile,
				D2MissileDataStrc& pMissileData
			) {
				pMissile.dwUnitType = UNIT_MISSILE;
				pMissile.pMissileData = &pMissileData;
			};

			setup_data(moo_pMissile, moo_pMissileData);
			setup_data(original_pMissile, original_pMissileData);

			// Call both implementations
			sut(&moo_pMissile);
			original(&original_pMissile);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");

			// Free allocated memory
			moo_free(&moo_pMissile);
			original_free(&original_pMissile);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC280 (#11214)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_FreeMissileStream, dll_base + 0x0007C280);
		const auto [moo_alloc, original_alloc] = make_function_pair(MISSTREAM_AllocMissileStream, dll_base + 0x0007C230);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2MissileDataStrc moo_pMissileData{};
			D2UnitStrc original_pMissile{};
			D2MissileDataStrc original_pMissileData{};

			const auto setup_data = [](
				D2UnitStrc& pMissile,
				D2MissileDataStrc& pMissileData
			) {
				pMissile.dwUnitType = UNIT_MISSILE;
				pMissile.pMissileData = &pMissileData;
			};

			setup_data(moo_pMissile, moo_pMissileData);
			setup_data(original_pMissile, original_pMissileData);

			moo_alloc(&moo_pMissile);
			original_alloc(&original_pMissile);

			// Call both implementations
			sut(&moo_pMissile);
			original(&original_pMissile);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC2E0 (#11215)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_ExecuteHit, dll_base + 0x0007C2E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nCollisionMask{};
			int nCollisionPattern{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = UNIT_MISSILE;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pUnit = &pUnit;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			sut(&moo_pUnit, nCollisionMask, nCollisionPattern, nullptr);
			original(&original_pUnit, nCollisionMask, nCollisionPattern, nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC3B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_Return1, dll_base + 0x0007C3B0);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id1 = random_unsigned_integer();
			const auto unit_id2 = random_unsigned_integer();

			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit2{};

			const auto setup_data = [unit_id1, unit_id2](
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit2
			) {
				pUnit1.dwUnitId = unit_id1;
				pUnit2.dwUnitId = unit_id2;
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
			const auto original_result = original(&original_pUnit1, &original_pUnit2);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC3C0 (#11216)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_Update, dll_base + 0x0007C3C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_a1{};
			D2UnitStrc moo_pMissile{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_a1{};
			D2UnitStrc original_pMissile{};
			D2DynamicPathStrc original_pDynamicPath{};
			int a3{};
			int a4{};

			const auto setup_data = [](
				D2UnitStrc& a1,
				D2UnitStrc& pMissile,
				D2DynamicPathStrc& pDynamicPath
			) {
				pMissile.dwUnitType = UNIT_MISSILE;
				pMissile.pDynamicPath = &pDynamicPath;
				pDynamicPath.pUnit = &pMissile;
			};

			setup_data(moo_a1, moo_pMissile, moo_pDynamicPath);
			setup_data(original_a1, original_pMissile, original_pDynamicPath);

			// Call both implementations
			sut(&moo_a1, &moo_pMissile, a3, a4, nullptr, nullptr);
			original(&original_a1, &original_pMissile, a3, a4, nullptr, nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
}

#endif
