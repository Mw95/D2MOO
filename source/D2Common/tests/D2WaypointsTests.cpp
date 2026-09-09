#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Waypoints.h>


TEST_SUITE("D2WaypointsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3D20 (#11153)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_GetLevelIdFromWaypointNo, dll_base + 0x00083D20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				int pLevelId{};
				
				return std::tuple{ pLevelId };
			};
			
			// Input data
			auto [moo_pLevelId] = setup_data();
			auto [original_pLevelId] = setup_data();
			short nWaypointNo{};

			// Call both implementations
			const auto moo_result = sut(nWaypointNo, &moo_pLevelId);
			const auto original_result = original(nWaypointNo, &original_pLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelId, original_pLevelId, "Comparing pLevelId");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3D90 (#11152)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_GetWaypointNoFromLevelId, dll_base + 0x00083D90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				short pWaypointNo{};
				
				return std::tuple{ pWaypointNo };
			};
			
			// Input data
			auto [moo_pWaypointNo] = setup_data();
			auto [original_pWaypointNo] = setup_data();
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(nLevelId, &moo_pWaypointNo);
			const auto original_result = original(nLevelId, &original_pWaypointNo);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pWaypointNo, original_pWaypointNo, "Comparing pWaypointNo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3DE0 (#11146)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_IsActivated, dll_base + 0x00083DE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2WaypointDataStrc pData{};
				
				return std::tuple{ pData };
			};
			
			// Input data
			auto [moo_pData] = setup_data();
			auto [original_pData] = setup_data();
			uint16_t wField{};

			// Call both implementations
			const auto moo_result = sut(&moo_pData, wField);
			const auto original_result = original(&original_pData, wField);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3E80 (#11147)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_ActivateWaypoint, dll_base + 0x00083E80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2WaypointDataStrc pData{};
				
				return std::tuple{ pData };
			};
			
			// Input data
			auto [moo_pData] = setup_data();
			auto [original_pData] = setup_data();
			uint16_t wField{};

			// Call both implementations
			sut(&moo_pData, wField);
			original(&original_pData, wField);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3F20 (#11148)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_AllocWaypointData, dll_base + 0x00083F20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			const auto moo_result = sut(moo_pMemPool);
			const auto original_result = original(original_pMemPool);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3F70 (#11149)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_FreeWaypointData, dll_base + 0x00083F70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2WaypointDataStrc pData{};
				
				return std::tuple{ pData };
			};
			
			// Input data
			auto [moo_pData] = setup_data();
			auto [original_pData] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			sut(moo_pMemPool, &moo_pData);
			original(original_pMemPool, &original_pData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3FD0 (#11150)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_CopyAndValidateWaypointData, dll_base + 0x00083FD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2WaypointDataStrc pDestination{};
				D2WaypointDataStrc pSource{};
				
				return std::tuple{ pDestination, pSource };
			};
			
			// Input data
			auto [moo_pDestination, moo_pSource] = setup_data();
			auto [original_pDestination, original_pSource] = setup_data();

			// Call both implementations
			sut(&moo_pDestination, &moo_pSource);
			original(&original_pDestination, &original_pSource);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDestination, original_pDestination, "Comparing pDestination");
			SKIP_MOO_CHECK_EQ(moo_pSource, original_pSource, "Comparing pSource");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC4060 (#11151)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_ValidateAndCopyWaypointData, dll_base + 0x00084060);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2WaypointDataStrc pSource{};
				D2WaypointDataStrc pDestination{};
				
				return std::tuple{ pSource, pDestination };
			};
			
			// Input data
			auto [moo_pSource, moo_pDestination] = setup_data();
			auto [original_pSource, original_pDestination] = setup_data();

			// Call both implementations
			sut(&moo_pSource, &moo_pDestination);
			original(&original_pSource, &original_pDestination);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSource, original_pSource, "Comparing pSource");
			SKIP_MOO_CHECK_EQ(moo_pDestination, original_pDestination, "Comparing pDestination");
		}
	}
}
