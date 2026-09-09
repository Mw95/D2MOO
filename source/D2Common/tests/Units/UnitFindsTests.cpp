#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <Units/UnitFinds.h>
#include <Units/Units.h>


TEST_SUITE("UnitFindsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC680 (#10408)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_AreUnitsInNeighboredRooms, dll_base + 0x0007C680);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pDestUnit{};
				D2UnitStrc pSrcUnit{};
				
				return std::tuple{ pDestUnit, pSrcUnit };
			};
			
			// Input data
			auto [moo_pDestUnit, moo_pSrcUnit] = setup_data();
			auto [original_pDestUnit, original_pSrcUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDestUnit, &moo_pSrcUnit);
			const auto original_result = original(&original_pDestUnit, &original_pSrcUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDestUnit, original_pDestUnit, "Comparing pDestUnit");
			SKIP_MOO_CHECK_EQ(moo_pSrcUnit, original_pSrcUnit, "Comparing pSrcUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC720 (#11087)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_FindUnitInNeighboredRooms, dll_base + 0x0007C720);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int nUnitType{};
			int nClassId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nUnitType, nClassId);
			const auto original_result = original(&original_pRoom, nUnitType, nClassId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC7B0 (#10405)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_GetTestedUnitsFromRoom, dll_base + 0x0007C7B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2UnitStrc* ppUnits{};
				D2UnitFindArgStrc pUnitFindArg{};
				
				return std::tuple{ pRoom, ppUnits, pUnitFindArg };
			};
			
			// Input data
			auto [moo_pRoom, moo_ppUnits, moo_pUnitFindArg] = setup_data();
			auto [original_pRoom, original_ppUnits, original_pUnitFindArg] = setup_data();
			UNITFINDTEST pfnUnitTest{};

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_ppUnits, pfnUnitTest, &moo_pUnitFindArg);
			const auto original_result = original(&original_pRoom, &original_ppUnits, pfnUnitTest, &original_pUnitFindArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_ppUnits, original_ppUnits, "Comparing ppUnits");
			SKIP_MOO_CHECK_EQ(moo_pUnitFindArg, original_pUnitFindArg, "Comparing pUnitFindArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC840 (#11088)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_GetNearestTestedUnit, dll_base + 0x0007C840);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();
			int nX{};
			int nY{};
			int nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nX, nY, nSize, nullptr);
			const auto original_result = original(&original_pUnit, nX, nY, nSize, nullptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC990 (#10401)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_InitializeUnitFindData, dll_base + 0x0007C990);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitFindDataStrc pUnitFindData{};
				D2ActiveRoomStrc pRoom{};
				D2UnitFindArgStrc pUnitFindArg{};
				
				return std::tuple{ pUnitFindData, pRoom, pUnitFindArg };
			};
			
			// Input data
			auto [moo_pUnitFindData, moo_pRoom, moo_pUnitFindArg] = setup_data();
			auto [original_pUnitFindData, original_pRoom, original_pUnitFindArg] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			int nX{};
			int nY{};
			int nSize{};
			UNITFINDTEST pfnUnitTest{};

			// Call both implementations
			sut(moo_pMemPool, &moo_pUnitFindData, &moo_pRoom, nX, nY, nSize, pfnUnitTest, &moo_pUnitFindArg);
			original(original_pMemPool, &original_pUnitFindData, &original_pRoom, nX, nY, nSize, pfnUnitTest, &original_pUnitFindArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pUnitFindData, original_pUnitFindData, "Comparing pUnitFindData");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pUnitFindArg, original_pUnitFindArg, "Comparing pUnitFindArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBCA50 (#10402)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_FreeUnitFindData, dll_base + 0x0007CA50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitFindDataStrc pUnitFindData{};
				
				return std::tuple{ pUnitFindData };
			};
			
			// Input data
			auto [moo_pUnitFindData] = setup_data();
			auto [original_pUnitFindData] = setup_data();

			// Call both implementations
			sut(&moo_pUnitFindData);
			original(&original_pUnitFindData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnitFindData, original_pUnitFindData, "Comparing pUnitFindData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBCA80 (#10403)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_FindAllMatchingUnitsInNeighboredRooms, dll_base + 0x0007CA80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitFindDataStrc pUnitFindData{};
				
				return std::tuple{ pUnitFindData };
			};
			
			// Input data
			auto [moo_pUnitFindData] = setup_data();
			auto [original_pUnitFindData] = setup_data();

			// Call both implementations
			sut(&moo_pUnitFindData);
			original(&original_pUnitFindData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnitFindData, original_pUnitFindData, "Comparing pUnitFindData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBCCA0 (#10404)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_TestUnit, dll_base + 0x0007CCA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitFindArgStrc pUnitFindArg{};
				
				return std::tuple{ pUnit, pUnitFindArg };
			};
			
			// Input data
			auto [moo_pUnit, moo_pUnitFindArg] = setup_data();
			auto [original_pUnit, original_pUnitFindArg] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pUnitFindArg);
			const auto original_result = original(&original_pUnit, &original_pUnitFindArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pUnitFindArg, original_pUnitFindArg, "Comparing pUnitFindArg");
		}
	}
}
