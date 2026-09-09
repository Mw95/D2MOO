#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <Path/Step.h>
#include <Units/Units.h>


TEST_SUITE("StepTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAC5E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetDirectionVector, dll_base + 0x0006C5E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2CoordStrc pDirectionVector{};
				int pOutDirection{};
				
				return std::tuple{ pDirectionVector, pOutDirection };
			};
			
			// Input data
			auto [moo_pDirectionVector, moo_pOutDirection] = setup_data();
			auto [original_pDirectionVector, original_pOutDirection] = setup_data();
			DWORD dwStartPrecisionX{};
			DWORD dwStartPrecisionY{};
			DWORD dwTargetPrecisionX{};
			DWORD dwTargetPrecisionY{};

			// Call both implementations
			sut(&moo_pDirectionVector, &moo_pOutDirection, dwStartPrecisionX, dwStartPrecisionY, dwTargetPrecisionX, dwTargetPrecisionY);
			original(&original_pDirectionVector, &original_pOutDirection, dwStartPrecisionX, dwStartPrecisionY, dwTargetPrecisionX, dwTargetPrecisionY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDirectionVector, original_pDirectionVector, "Comparing pDirectionVector");
			SKIP_MOO_CHECK_EQ(moo_pOutDirection, original_pOutDirection, "Comparing pOutDirection");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDACEC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDACEC0, dll_base + 0x0006CEC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DynamicPathStrc pDynamicPath{};
				D2FP32_16 a2{};
				D2UnitStrc* pUnit{};
				
				return std::tuple{ pDynamicPath, a2, pUnit };
			};
			
			// Input data
			auto [moo_pDynamicPath, moo_a2, moo_pUnit] = setup_data();
			auto [original_pDynamicPath, original_a2, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, &moo_a2, &moo_pUnit);
			const auto original_result = original(&original_pDynamicPath, &original_a2, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAD5E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAD5E0, dll_base + 0x0006D5E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DynamicPathStrc pDynamicPath{};
				D2ActiveRoomStrc pDestRoom{};
				
				return std::tuple{ pDynamicPath, pDestRoom };
			};
			
			// Input data
			auto [moo_pDynamicPath, moo_pDestRoom] = setup_data();
			auto [original_pDynamicPath, original_pDestRoom] = setup_data();
			D2PathPointStrc tDest{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, &moo_pDestRoom, tDest);
			const auto original_result = original(&original_pDynamicPath, &original_pDestRoom, tDest);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			SKIP_MOO_CHECK_EQ(moo_pDestRoom, original_pDestRoom, "Comparing pDestRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAE250" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATHMISC_SetRoom, dll_base + 0x0006E250);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DynamicPathStrc pPath{};
				D2ActiveRoomStrc pNewRoom{};
				
				return std::tuple{ pPath, pNewRoom };
			};
			
			// Input data
			auto [moo_pPath, moo_pNewRoom] = setup_data();
			auto [original_pPath, original_pNewRoom] = setup_data();

			// Call both implementations
			sut(&moo_pPath, &moo_pNewRoom);
			original(&original_pPath, &original_pNewRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPath, original_pPath, "Comparing pPath");
			SKIP_MOO_CHECK_EQ(moo_pNewRoom, original_pNewRoom, "Comparing pNewRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDADF00 (#10230)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10230, dll_base + 0x0006DF00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DynamicPathStrc pDynamicPath{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pDynamicPath, pRoom };
			};
			
			// Input data
			auto [moo_pDynamicPath, moo_pRoom] = setup_data();
			auto [original_pDynamicPath, original_pRoom] = setup_data();
			int a2{};
			unsigned int a4{};
			__int16 a5{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, a2, &moo_pRoom, a4, a5);
			const auto original_result = original(&original_pDynamicPath, a2, &original_pRoom, a4, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDADC20 (#10231)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10231, dll_base + 0x0006DC20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DynamicPathStrc pDynamicPath{};
				D2UnitStrc pUnit_unused{};
				D2ActiveRoomStrc pRooms{};
				
				return std::tuple{ pDynamicPath, pUnit_unused, pRooms };
			};
			
			// Input data
			auto [moo_pDynamicPath, moo_pUnit_unused, moo_pRooms] = setup_data();
			auto [original_pDynamicPath, original_pUnit_unused, original_pRooms] = setup_data();
			uint16_t nX{};
			uint16_t nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, &moo_pUnit_unused, &moo_pRooms, nX, nY);
			const auto original_result = original(&original_pDynamicPath, &original_pUnit_unused, &original_pRooms, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			SKIP_MOO_CHECK_EQ(moo_pUnit_unused, original_pUnit_unused, "Comparing pUnit_unused");
			SKIP_MOO_CHECK_EQ(moo_pRooms, original_pRooms, "Comparing pRooms");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDADF50 (#10232)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10232, dll_base + 0x0006DF50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DynamicPathStrc pPath{};
				D2UnitStrc pUnit{};
				D2ActiveRoomStrc pDestRoom{};
				
				return std::tuple{ pPath, pUnit, pDestRoom };
			};
			
			// Input data
			auto [moo_pPath, moo_pUnit, moo_pDestRoom] = setup_data();
			auto [original_pPath, original_pUnit, original_pDestRoom] = setup_data();
			int nTargetX{};
			int nTargetY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pPath, &moo_pUnit, &moo_pDestRoom, nTargetX, nTargetY);
			const auto original_result = original(&original_pPath, &original_pUnit, &original_pDestRoom, nTargetX, nTargetY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPath, original_pPath, "Comparing pPath");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDestRoom, original_pDestRoom, "Comparing pDestRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAE290 (#10233)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_RecacheRoomIfNeeded, dll_base + 0x0006E290);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DynamicPathStrc pDynamicPath{};
				
				return std::tuple{ pDynamicPath };
			};
			
			// Input data
			auto [moo_pDynamicPath] = setup_data();
			auto [original_pDynamicPath] = setup_data();

			// Call both implementations
			sut(&moo_pDynamicPath);
			original(&original_pDynamicPath);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAE500 (#10234)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10234, dll_base + 0x0006E500);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DynamicPathStrc pDynamicPath{};
				
				return std::tuple{ pDynamicPath };
			};
			
			// Input data
			auto [moo_pDynamicPath] = setup_data();
			auto [original_pDynamicPath] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAE520 (#10235)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10235_PATH_UpdateRiderPath, dll_base + 0x0006E520);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pRiderUnit{};
				D2UnitStrc pMountUnit{};
				
				return std::tuple{ pRiderUnit, pMountUnit };
			};
			
			// Input data
			auto [moo_pRiderUnit, moo_pMountUnit] = setup_data();
			auto [original_pRiderUnit, original_pMountUnit] = setup_data();

			// Call both implementations
			sut(&moo_pRiderUnit, &moo_pMountUnit);
			original(&original_pRiderUnit, &original_pMountUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRiderUnit, original_pRiderUnit, "Comparing pRiderUnit");
			SKIP_MOO_CHECK_EQ(moo_pMountUnit, original_pMountUnit, "Comparing pMountUnit");
		}
	}
}
