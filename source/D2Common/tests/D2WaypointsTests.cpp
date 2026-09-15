#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Waypoints.h>

#include <Fixtures/DataTbls/Fixtures.h>


TEST_SUITE("D2WaypointsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(LevelsTxtFixture<NoopFixture>, "D2Common.0x6FDC3D20 (#11153)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_GetLevelIdFromWaypointNo, dll_base + 0x00083D20);
		
		SUBCASE("")
		{
			const auto setup_data = []() {
				int pLevelId{};

				return std::tuple{ pLevelId };
			};

			for (auto i = -1; i < 256; ++i)
			{
				// Input data
				auto [moo_pLevelId] = setup_data();
				auto [original_pLevelId] = setup_data();
				short nWaypointNo = i;

				// Call both implementations
				const auto moo_result = sut(nWaypointNo, &moo_pLevelId);
				const auto original_result = original(nWaypointNo, &original_pLevelId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevelId, original_pLevelId, "Comparing pLevelId");
			}
		}
	}
	
	TEST_CASE_FIXTURE(LevelsTxtFixture<NoopFixture>, "D2Common.0x6FDC3D90 (#11152)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_GetWaypointNoFromLevelId, dll_base + 0x00083D90);
		
		SUBCASE("")
		{
			const auto setup_data = []() {
				short pWaypointNo{};
				
				return std::tuple{ pWaypointNo };
			};
			
			for (auto i = -1; i < levels_record_count + 1; ++i)
			{
				// Input data
				auto [moo_pWaypointNo] = setup_data();
				auto [original_pWaypointNo] = setup_data();
				int nLevelId{};

				// Call both implementations
				const auto moo_result = sut(nLevelId, &moo_pWaypointNo);
				const auto original_result = original(nLevelId, &original_pWaypointNo);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pWaypointNo, original_pWaypointNo, "Comparing pWaypointNo");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3DE0 (#11146)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_IsActivated, dll_base + 0x00083DE0);

		REPEAT_10();
		
		SUBCASE("")
		{
			uint16_t flags[8]{};
			flags[0] = 0x102;
			for (auto i = 1; i < 8; ++i)
			{
				flags[i] = random_unsigned_integer(0, 65535);
			}

			const auto setup_data = [flags]() {
				D2WaypointDataStrc pData{};

				memcpy(pData.nFlags, flags, sizeof(flags));
				
				return std::tuple{ pData };
			};
			
			for (auto i = 0; i < 112; ++i)
			{
				// Input data
				auto [moo_pData] = setup_data();
				auto [original_pData] = setup_data();
				uint16_t wField = i;

				// Call both implementations
				const auto moo_result = sut(&moo_pData, wField);
				const auto original_result = original(&original_pData, wField);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");

				// Check specific values
				CHECK_EQ(moo_result, flags[wField / 16 + 1] & (1 << (wField & 15)));
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3E80 (#11147)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_ActivateWaypoint, dll_base + 0x00083E80);
		
		SUBCASE("")
		{
			const auto setup_data = []() {
				D2WaypointDataStrc pData{};

				pData.nFlags[0] = 0x102;
				pData.nFlags[1] |= 1;
				
				return std::tuple{ pData };
			};
			
			for (auto i = 0; i < 112; ++i)
			{
				// Input data
				auto [moo_pData] = setup_data();
				auto [original_pData] = setup_data();
				uint16_t wField = i;

				// Call both implementations
				sut(&moo_pData, wField);
				original(&original_pData, wField);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
			}
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3FD0 (#11150)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_CopyAndValidateWaypointData, dll_base + 0x00083FD0);

		REPEAT_10();
		
		SUBCASE("")
		{
			uint16_t flags[8]{};
			switch (random_unsigned_integer(0, 2))
			{
			case 0:
				flags[0] = 0x00;
				break;
			case 1:
				flags[0] = 0x101;
				break;
			case 2:
				flags[0] = 0x102;
				break;
			}
			for (auto i = 1; i < 8; ++i)
			{
				flags[i] = random_unsigned_integer(0, 65535);
			}

			const auto setup_data = [flags]() {
				D2WaypointDataStrc pDestination{};
				D2WaypointDataStrc pSource{};

				memcpy(pSource.nFlags, flags, sizeof(flags));
				
				return std::tuple{ pDestination, pSource };
			};
			
			// Input data
			auto [moo_pDestination, moo_pSource] = setup_data();
			auto [original_pDestination, original_pSource] = setup_data();

			// Call both implementations
			sut(&moo_pDestination, &moo_pSource);
			original(&original_pDestination, &original_pSource);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDestination, original_pDestination, "Comparing pDestination");
			MOO_CHECK_EQ(moo_pSource, original_pSource, "Comparing pSource");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC4060 (#11151)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_ValidateAndCopyWaypointData, dll_base + 0x00084060);
		
		REPEAT_10();

		SUBCASE("")
		{
			uint16_t flags[8]{};
			switch (random_unsigned_integer(0, 2))
			{
			case 0:
				flags[0] = 0x00;
				break;
			case 1:
				flags[0] = 0x101;
				break;
			case 2:
				flags[0] = 0x102;
				break;
			}
			for (auto i = 1; i < 8; ++i)
			{
				flags[i] = random_unsigned_integer(0, 65535);
			}

			const auto setup_data = [flags]() {
				D2WaypointDataStrc pDestination{};
				D2WaypointDataStrc pSource{};

				memcpy(pSource.nFlags, flags, sizeof(flags));

				return std::tuple{ pDestination, pSource };
			};
			
			// Input data
			auto [moo_pSource, moo_pDestination] = setup_data();
			auto [original_pSource, original_pDestination] = setup_data();

			// Call both implementations
			sut(&moo_pSource, &moo_pDestination);
			original(&original_pSource, &original_pDestination);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSource, original_pSource, "Comparing pSource");
			MOO_CHECK_EQ(moo_pDestination, original_pDestination, "Comparing pDestination");
		}
	}
}
