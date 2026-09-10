#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Chat.h>


TEST_SUITE("D2ChatTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3BF0 (#10892)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CHAT_AllocHoverMsg, dll_base + 0x00083BF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			char szText{};
			int nTimeout{};

			// Call both implementations
			const auto moo_result = sut(moo_pMemPool, &szText, nTimeout);
			const auto original_result = original(original_pMemPool, &szText, nTimeout);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3C80 (#10893)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CHAT_FreeHoverMsg, dll_base + 0x00083C80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2HoverTextStrc pHoverMsg{};
				
				return std::tuple{ pHoverMsg };
			};
			
			// Input data
			auto [moo_pHoverMsg] = setup_data();
			auto [original_pHoverMsg] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			sut(moo_pMemPool, &moo_pHoverMsg);
			original(original_pMemPool, &original_pHoverMsg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pHoverMsg, original_pHoverMsg, "Comparing pHoverMsg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3CA0 (#10894)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CHAT_GetDisplayTimeFromHoverMsg, dll_base + 0x00083CA0);
		
		SUBCASE("")
		{
			const auto display_time = random_unsigned_integer();

			const auto setup_data = [&display_time]() {
				D2HoverTextStrc pHoverMsg{};
				pHoverMsg.dwDisplayTime = display_time;

				return std::tuple{ pHoverMsg };
			};
			
			// Input data
			auto [moo_pHoverMsg] = setup_data();
			auto [original_pHoverMsg] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pHoverMsg);
			const auto original_result = original(&original_pHoverMsg);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pHoverMsg, original_pHoverMsg, "Comparing pHoverMsg");

			// Check specific values
			CHECK_EQ(moo_result, display_time);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3CB0 (#10895)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CHAT_GetTimeoutFromHoverMsg, dll_base + 0x00083CB0);
		
		SUBCASE("")
		{
			const auto timeout = random_unsigned_integer();

			const auto setup_data = [&timeout]() {
				D2HoverTextStrc pHoverMsg{};
				pHoverMsg.dwExpireTime = timeout;

				return std::tuple{ pHoverMsg };
			};
			
			// Input data
			auto [moo_pHoverMsg] = setup_data();
			auto [original_pHoverMsg] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pHoverMsg);
			const auto original_result = original(&original_pHoverMsg);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pHoverMsg, original_pHoverMsg, "Comparing pHoverMsg");

			// Check specific values
			CHECK_EQ(moo_result, timeout);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3CC0 (#10896)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CHAT_CopyHoverMsgToBuffer, dll_base + 0x00083CC0);
		
		SUBCASE("")
		{
			const char* message = "Test message";

			const auto setup_data = [&message]() {
				D2HoverTextStrc pHoverMsg{};
				char szMessage[256]{};
				strcpy_s(pHoverMsg.szMsg, sizeof(pHoverMsg.szMsg), message);

				return std::tuple{ pHoverMsg, szMessage };
			};
			
			// Input data
			auto [moo_pHoverMsg, moo_szMessage] = setup_data();
			auto [original_pHoverMsg, original_szMessage] = setup_data();

			// Call both implementations
			sut(&moo_pHoverMsg, moo_szMessage);
			original(&original_pHoverMsg, original_szMessage);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pHoverMsg, original_pHoverMsg, "Comparing pHoverMsg");
			MOO_CHECK_EQ(moo_szMessage, original_szMessage, "Comparing szMessage");

			// Check specific values
			CHECK_EQ(strcmp(moo_szMessage, message), 0);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3CE0 (#10897)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CHAT_GetUsedFromHoverMsg, dll_base + 0x00083CE0);
		
		SUBCASE("")
		{
			BOOL bUsed = GENERATE(true, false);

			const auto setup_data = [&bUsed]() {
				D2HoverTextStrc pHoverMsg{};
				pHoverMsg.bUsed = bUsed;
				
				return std::tuple{ pHoverMsg };
			};
			
			// Input data
			auto [moo_pHoverMsg] = setup_data();
			auto [original_pHoverMsg] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pHoverMsg);
			const auto original_result = original(&original_pHoverMsg);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pHoverMsg, original_pHoverMsg, "Comparing pHoverMsg");

			// Check specific values
			CHECK_EQ(moo_pHoverMsg.bUsed, bUsed);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3CF0 (#10898)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CHAT_SetUsedInHoverMsg, dll_base + 0x00083CF0);
		
		SUBCASE("")
		{
			const auto setup_data = []() {
				D2HoverTextStrc pHoverMsg{};
				
				return std::tuple{ pHoverMsg };
			};
			
			// Input data
			auto [moo_pHoverMsg] = setup_data();
			auto [original_pHoverMsg] = setup_data();
			BOOL bUsed = GENERATE(true, false);

			// Call both implementations
			sut(&moo_pHoverMsg, bUsed);
			original(&original_pHoverMsg, bUsed);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pHoverMsg, original_pHoverMsg, "Comparing pHoverMsg");

			// Check specific values
			CHECK_EQ(moo_pHoverMsg.bUsed, bUsed);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3D00 (#10899)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CHAT_GetLangIdFromHoverMsg, dll_base + 0x00083D00);
		
		SUBCASE("")
		{
			const auto lang_id = random_unsigned_integer(0, 255);

			const auto setup_data = [&lang_id]() {
				D2HoverTextStrc pHoverMsg{};
				pHoverMsg.nLangId = lang_id;

				return std::tuple{ pHoverMsg };
			};
			
			// Input data
			auto [moo_pHoverMsg] = setup_data();
			auto [original_pHoverMsg] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pHoverMsg);
			const auto original_result = original(&original_pHoverMsg);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pHoverMsg, original_pHoverMsg, "Comparing pHoverMsg");

			// Check specific values
			CHECK_EQ(moo_result, lang_id);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3D10 (#10900)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CHAT_SetLangIdInHoverMsg, dll_base + 0x00083D10);
		
		SUBCASE("")
		{
			const auto setup_data = []() {
				D2HoverTextStrc pHoverMsg{};
				
				return std::tuple{ pHoverMsg };
			};
			
			// Input data
			auto [moo_pHoverMsg] = setup_data();
			auto [original_pHoverMsg] = setup_data();
			uint8_t nLangId = random_unsigned_integer(0, 255);

			// Call both implementations
			sut(&moo_pHoverMsg, nLangId);
			original(&original_pHoverMsg, nLangId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pHoverMsg, original_pHoverMsg, "Comparing pHoverMsg");

			// Check specific values
			CHECK_EQ(moo_pHoverMsg.nLangId, nLangId);
		}
	}
}
