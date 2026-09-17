#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/CCmd.h>


TEST_SUITE("CCmdTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC317F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CCMD_IsStringZeroTerminated, dll_base + 0x000017F0);
		
		SUBCASE("")
		{
			char pData{};
			int32_t nDataSize{};

			// Call both implementations
			const auto moo_result = sut(&pData, nDataSize);
			const auto original_result = original(&pData, nDataSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC31810" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CCMD_CanClientJoinGame, dll_base + 0x00001810);
		
		SUBCASE("")
		{
			// Input data
			char moo_szClientName{};
			char original_szClientName{};
			int32_t a1{};
			int32_t a2{};

			const auto setup_data = [](
				char& szClientName
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szClientName);
			setup_data(original_szClientName);

			// Call both implementations
			const auto moo_result = sut(a1, a2, &moo_szClientName);
			const auto original_result = original(a1, a2, &original_szClientName);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szClientName, original_szClientName, "Comparing szClientName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC31910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CCMD_ProcessClientSystemMessage, dll_base + 0x00001910);
		
		SUBCASE("")
		{
			void* moo_pData = nullptr;
			void* original_pData = nullptr;
			int32_t nSize{};

			// Call both implementations
			sut(moo_pData, nSize);
			original(original_pData, nSize);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC31C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CCMD_ProcessClientMessage, dll_base + 0x00001C00);
		
		SUBCASE("")
		{
			void* moo_pData = nullptr;
			void* original_pData = nullptr;
			int32_t nPacketSize{};

			// Call both implementations
			sut(moo_pData, nPacketSize);
			original(original_pData, nPacketSize);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
}
