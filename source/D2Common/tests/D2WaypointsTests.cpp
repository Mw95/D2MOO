#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

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
			for (auto i = -1; i < 256; ++i)
			{
				// Input data
				int moo_pLevelId{};
				int original_pLevelId{};
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
			for (auto i = -1; i < levels_record_count + 1; ++i)
			{
				// Input data
				short moo_pWaypointNo{};
				short original_pWaypointNo{};
				int nLevelId = i;

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
			// Input data
			uint16_t flags[8]{};
			flags[0] = 0x102;
			for (auto i = 1; i < 8; ++i)
			{
				flags[i] = random_unsigned_integer(0, 65535);
			}

			for (auto i = 0; i < 112; ++i)
			{
				D2WaypointDataStrc moo_pData{};
				D2WaypointDataStrc original_pData{};
				uint16_t wField = i;

				const auto setup_data = [flags](
					D2WaypointDataStrc& pData
				) {
					memcpy(pData.nFlags, flags, sizeof(flags));
				};

				setup_data(moo_pData);
				setup_data(original_pData);

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
			for (auto i = 0; i < 112; ++i)
			{
				// Input data
				D2WaypointDataStrc moo_pData{};
				D2WaypointDataStrc original_pData{};
				uint16_t wField = i;

				const auto setup_data = [](
					D2WaypointDataStrc& pData
				) {
					pData.nFlags[0] = 0x102;
					pData.nFlags[1] |= 1;
				};

				setup_data(moo_pData);
				setup_data(original_pData);

				// Call both implementations
				sut(&moo_pData, wField);
				original(&original_pData, wField);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3F20 (#11148)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_AllocWaypointData, dll_base + 0x00083F20);
		
		SUBCASE("")
		{
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			const auto moo_result = sut(moo_pMemPool);
			const auto original_result = original(original_pMemPool);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3F70 (#11149)" * doctest::skip("Not really testable"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WAYPOINTS_FreeWaypointData, dll_base + 0x00083F70);
		
		SUBCASE("")
		{
			// Input data
			D2WaypointDataStrc moo_pData{};
			D2WaypointDataStrc original_pData{};
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			const auto setup_data = [](
				D2WaypointDataStrc& pData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pData);
			setup_data(original_pData);

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
			// Input data
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

			D2WaypointDataStrc moo_pDestination{};
			D2WaypointDataStrc moo_pSource{};
			D2WaypointDataStrc original_pDestination{};
			D2WaypointDataStrc original_pSource{};

			const auto setup_data = [flags](
				D2WaypointDataStrc& pDestination,
				D2WaypointDataStrc& pSource
			) {
				memcpy(pSource.nFlags, flags, sizeof(flags));
			};

			setup_data(moo_pDestination, moo_pSource);
			setup_data(original_pDestination, original_pSource);

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
			// Input data
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

			D2WaypointDataStrc moo_pSource{};
			D2WaypointDataStrc moo_pDestination{};
			D2WaypointDataStrc original_pSource{};
			D2WaypointDataStrc original_pDestination{};

			const auto setup_data = [flags](
				D2WaypointDataStrc& pSource,
				D2WaypointDataStrc& pDestination
			) {
				memcpy(pSource.nFlags, flags, sizeof(flags));
			};

			setup_data(moo_pSource, moo_pDestination);
			setup_data(original_pSource, original_pDestination);

			// Call both implementations
			sut(&moo_pSource, &moo_pDestination);
			original(&original_pSource, &original_pDestination);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSource, original_pSource, "Comparing pSource");
			MOO_CHECK_EQ(moo_pDestination, original_pDestination, "Comparing pDestination");
		}
	}
}
