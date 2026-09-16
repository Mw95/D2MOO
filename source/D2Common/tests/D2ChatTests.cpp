#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

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
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			char szText{};
			int nTimeout{};

			// Call both implementations
			auto moo_result = sut(moo_pMemPool, &szText, nTimeout);
			auto original_result = original(original_pMemPool, &szText, nTimeout);
			
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
			// Input data
			D2HoverTextStrc moo_pHoverMsg{};
			D2HoverTextStrc original_pHoverMsg{};
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			const auto setup_data = [](
				D2HoverTextStrc& pHoverMsg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pHoverMsg);
			setup_data(original_pHoverMsg);

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
			// Input data
			const auto display_time = random_unsigned_integer();

			D2HoverTextStrc moo_pHoverMsg{};
			D2HoverTextStrc original_pHoverMsg{};

			const auto setup_data = [display_time](
				D2HoverTextStrc& pHoverMsg
			) {
				pHoverMsg.dwDisplayTime = display_time;
			};

			setup_data(moo_pHoverMsg);
			setup_data(original_pHoverMsg);

			// Call both implementations
			auto moo_result = sut(&moo_pHoverMsg);
			auto original_result = original(&original_pHoverMsg);
			
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
			// Input data
			const auto timeout = random_unsigned_integer();

			D2HoverTextStrc moo_pHoverMsg{};
			D2HoverTextStrc original_pHoverMsg{};

			const auto setup_data = [timeout](
				D2HoverTextStrc& pHoverMsg
			) {
				pHoverMsg.dwExpireTime = timeout;
			};

			setup_data(moo_pHoverMsg);
			setup_data(original_pHoverMsg);

			// Call both implementations
			auto moo_result = sut(&moo_pHoverMsg);
			auto original_result = original(&original_pHoverMsg);
			
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
			// Input data
			const char* message = "Test message";

			D2HoverTextStrc moo_pHoverMsg{};
			char moo_szMessage[256]{};
			D2HoverTextStrc original_pHoverMsg{};
			char original_szMessage[256]{};

			const auto setup_data = [message](
				D2HoverTextStrc& pHoverMsg
			) {
				strcpy_s(pHoverMsg.szMsg, sizeof(pHoverMsg.szMsg), message);
			};

			setup_data(moo_pHoverMsg);
			setup_data(original_pHoverMsg);

			// Call both implementations
			sut(&moo_pHoverMsg, moo_szMessage);
			original(&original_pHoverMsg, original_szMessage);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pHoverMsg, original_pHoverMsg, "Comparing pHoverMsg");
			//MOO_CHECK_EQ((DynamicArray<char>{ moo_szMessage, 256 }), (DynamicArray<char>{ original_szMessage, 256 }), "Comparing szMessage");
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

			// Input data
			D2HoverTextStrc moo_pHoverMsg{};
			D2HoverTextStrc original_pHoverMsg{};

			const auto setup_data = [bUsed](
				D2HoverTextStrc& pHoverMsg
			) {
				pHoverMsg.bUsed = bUsed;
			};

			setup_data(moo_pHoverMsg);
			setup_data(original_pHoverMsg);

			// Call both implementations
			auto moo_result = sut(&moo_pHoverMsg);
			auto original_result = original(&original_pHoverMsg);
			
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
			// Input data
			D2HoverTextStrc moo_pHoverMsg{};
			D2HoverTextStrc original_pHoverMsg{};
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
			// Input data
			const auto lang_id = random_unsigned_integer(0, 255);

			D2HoverTextStrc moo_pHoverMsg{};
			D2HoverTextStrc original_pHoverMsg{};

			const auto setup_data = [lang_id](
				D2HoverTextStrc& pHoverMsg
			) {
				pHoverMsg.nLangId = lang_id;
			};

			setup_data(moo_pHoverMsg);
			setup_data(original_pHoverMsg);

			// Call both implementations
			auto moo_result = sut(&moo_pHoverMsg);
			auto original_result = original(&original_pHoverMsg);
			
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
			// Input data
			D2HoverTextStrc moo_pHoverMsg{};
			D2HoverTextStrc original_pHoverMsg{};
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
