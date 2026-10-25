#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2WinButton.h>


TEST_SUITE("D2WinButtonTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A61A0 (#10107)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_Create, dll_base + 0x000061A0);
		
		SUBCASE("")
		{
			// Input data
			D2CellFileStrc moo_pCellFile{};
			D2CellFileStrc original_pCellFile{};
			int32_t nX{};
			int32_t nY{};
			int32_t nWidth{};
			int32_t nHeight{};
			int32_t nActivationVirtualKey{};
			int32_t nBaseFrame{};
			uint32_t nFlags{};
			uint16_t nStringId{};

			const auto setup_data = [](
				D2CellFileStrc& pCellFile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCellFile);
			setup_data(original_pCellFile);

			// Call both implementations
			const auto moo_result = sut(nX, nY, nWidth, nHeight, &moo_pCellFile, nullptr, nActivationVirtualKey, nBaseFrame, nFlags, nStringId, nullptr);
			const auto original_result = original(nX, nY, nWidth, nHeight, &original_pCellFile, nullptr, nActivationVirtualKey, nBaseFrame, nFlags, nStringId, nullptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCellFile, original_pCellFile, "Comparing pCellFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A62C0 (#10108)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_Destroy, dll_base + 0x000062C0);
		
		SUBCASE("")
		{
			// Input data
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};

			const auto setup_data = [](
				D2WinButtonStrc& pButton
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pButton);
			setup_data(original_pButton);

			// Call both implementations
			const auto moo_result = sut(&moo_pButton);
			const auto original_result = original(&original_pButton);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A62F0 (#10109)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_IsPressed, dll_base + 0x000062F0);
		
		SUBCASE("")
		{
			// Input data
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};

			const auto setup_data = [](
				D2WinButtonStrc& pButton
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pButton);
			setup_data(original_pButton);

			// Call both implementations
			const auto moo_result = sut(&moo_pButton);
			const auto original_result = original(&original_pButton);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6330 (#10110)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetIsPressed, dll_base + 0x00006330);
		
		SUBCASE("")
		{
			// Input data
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			int32_t bIsPressed{};

			const auto setup_data = [](
				D2WinButtonStrc& pButton
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pButton);
			setup_data(original_pButton);

			// Call both implementations
			sut(&moo_pButton, bIsPressed);
			original(&original_pButton, bIsPressed);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6360 (#10186)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetText, dll_base + 0x00006360);
		
		SUBCASE("")
		{
			// Input data
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			Font eFont{};
			Unicode wszText{};
			int32_t nTextColor{};

			const auto setup_data = [](
				D2WinButtonStrc& pButton
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pButton);
			setup_data(original_pButton);

			// Call both implementations
			sut(&moo_pButton, eFont, &wszText, nTextColor);
			original(&original_pButton, eFont, &wszText, nTextColor);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A63A0 (#10111)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetTextWithStringId, dll_base + 0x000063A0);
		
		SUBCASE("")
		{
			// Input data
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			Font eFont{};
			uint16_t nStringId{};
			int32_t nTextColor{};

			const auto setup_data = [](
				D2WinButtonStrc& pButton
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pButton);
			setup_data(original_pButton);

			// Call both implementations
			sut(&moo_pButton, eFont, nStringId, nTextColor);
			original(&original_pButton, eFont, nStringId, nTextColor);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A63F0 (#10112)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetCoordinates, dll_base + 0x000063F0);
		
		SUBCASE("")
		{
			// Input data
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			int32_t nX{};
			int32_t nY{};
			int32_t nWidth{};
			int32_t nHeight{};

			const auto setup_data = [](
				D2WinButtonStrc& pButton
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pButton);
			setup_data(original_pButton);

			// Call both implementations
			sut(&moo_pButton, nX, nY, nWidth, nHeight);
			original(&original_pButton, nX, nY, nWidth, nHeight);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6430 (#10113)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SimulateClick, dll_base + 0x00006430);
		
		SUBCASE("")
		{
			// Input data
			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};

			const auto setup_data = [](
				SMSGHANDLER_PARAMS& pMsg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMsg);
			setup_data(original_pMsg);

			// Call both implementations
			sut(&moo_pMsg);
			original(&original_pMsg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A64A0 (#10114)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetBaseFrame, dll_base + 0x000064A0);
		
		SUBCASE("")
		{
			// Input data
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			int32_t nBaseFrame{};

			const auto setup_data = [](
				D2WinButtonStrc& pButton
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pButton);
			setup_data(original_pButton);

			// Call both implementations
			sut(&moo_pButton, nBaseFrame);
			original(&original_pButton, nBaseFrame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A64D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_OnMouseWheelScrolled, dll_base + 0x000064D0);
		
		SUBCASE("")
		{
			// Input data
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			int32_t nMouseWheelIncrement{};

			const auto setup_data = [](
				D2WinButtonStrc& pButton
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pButton);
			setup_data(original_pButton);

			// Call both implementations
			const auto moo_result = sut(&moo_pButton, nMouseWheelIncrement);
			const auto original_result = original(&original_pButton, nMouseWheelIncrement);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6570 (#10189)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetStringId, dll_base + 0x00006570);
		
		SUBCASE("")
		{
			// Input data
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			uint16_t nStringId{};

			const auto setup_data = [](
				D2WinButtonStrc& pButton
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pButton);
			setup_data(original_pButton);

			// Call both implementations
			sut(&moo_pButton, nStringId);
			original(&original_pButton, nStringId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A65A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_Draw, dll_base + 0x000065A0);
		
		SUBCASE("")
		{
			// Input data
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};

			const auto setup_data = [](
				D2WinControlStrc& pControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pControl);
			setup_data(original_pControl);

			// Call both implementations
			const auto moo_result = sut(&moo_pControl);
			const auto original_result = original(&original_pControl);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6A10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_HandleMouseDown, dll_base + 0x00006A10);
		
		SUBCASE("")
		{
			// Input data
			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};

			const auto setup_data = [](
				SMSGHANDLER_PARAMS& pMsg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMsg);
			setup_data(original_pMsg);

			// Call both implementations
			const auto moo_result = sut(&moo_pMsg);
			const auto original_result = original(&original_pMsg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6AF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_HandleMouseUp, dll_base + 0x00006AF0);
		
		SUBCASE("")
		{
			// Input data
			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};

			const auto setup_data = [](
				SMSGHANDLER_PARAMS& pMsg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMsg);
			setup_data(original_pMsg);

			// Call both implementations
			const auto moo_result = sut(&moo_pMsg);
			const auto original_result = original(&original_pMsg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6BB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_HandleVirtualKeyInput, dll_base + 0x00006BB0);
		
		SUBCASE("")
		{
			// Input data
			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};

			const auto setup_data = [](
				SMSGHANDLER_PARAMS& pMsg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMsg);
			setup_data(original_pMsg);

			// Call both implementations
			const auto moo_result = sut(&moo_pMsg);
			const auto original_result = original(&original_pMsg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		}
	}
}
