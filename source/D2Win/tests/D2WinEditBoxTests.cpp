#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2WinEditBox.h>


TEST_SUITE("D2WinEditBoxTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6C80 (#10070)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10070_EDITBOX_Create, dll_base + 0x00006C80);
		
		SUBCASE("")
		{
			// Input data
			D2CellFileStrc moo_pCellFile{};
			D2CellFileStrc original_pCellFile{};
			int32_t nX{};
			int32_t nY{};
			int32_t nWidth{};
			int32_t nHeight{};
			int32_t nTextOffsetX{};
			int32_t nTextOffsetY{};
			EditBoxReturnFunc pfOnReturn{};
			int32_t nEditBoxFlags{};
			D2WinEditBoxFontStrc pFont{};

			const auto setup_data = [](
				D2CellFileStrc& pCellFile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCellFile);
			setup_data(original_pCellFile);

			// Call both implementations
			const auto moo_result = sut(nX, nY, nWidth, nHeight, nTextOffsetX, nTextOffsetY, &moo_pCellFile, pfOnReturn, nullptr, nEditBoxFlags, &pFont);
			const auto original_result = original(nX, nY, nWidth, nHeight, nTextOffsetX, nTextOffsetY, &original_pCellFile, pfOnReturn, nullptr, nEditBoxFlags, &pFont);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCellFile, original_pCellFile, "Comparing pCellFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6DC0 (#10071)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10071_EDITBOX_Destroy, dll_base + 0x00006DC0);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pEditBox);
			const auto original_result = original(&original_pEditBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6E10 (#10072)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10072, dll_base + 0x00006E10);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			EditBoxCharFilterFunc pfCharFilter{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			sut(&moo_pEditBox, pfCharFilter);
			original(&original_pEditBox, pfCharFilter);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6E60 (#10073)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10073, dll_base + 0x00006E60);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			EditBoxTextChangedFunc pfOnTextChanged{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			sut(&moo_pEditBox, pfOnTextChanged);
			original(&original_pEditBox, pfOnTextChanged);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6EB0 (#10083)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10083, dll_base + 0x00006EB0);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			sut(&moo_pEditBox);
			original(&original_pEditBox);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6F10 (#10082)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10082, dll_base + 0x00006F10);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pEditBox);
			const auto original_result = original(&original_pEditBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6F70 (#10074)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10074, dll_base + 0x00006F70);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			uint8_t nChar{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pEditBox, nChar);
			const auto original_result = original(&original_pEditBox, nChar);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A7970" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_DeleteSelection, dll_base + 0x00007970);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			sut(&moo_pEditBox);
			original(&original_pEditBox);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A7AB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_HandleVirtualKey, dll_base + 0x00007AB0);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			char nVirtualKey{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pEditBox, nVirtualKey);
			const auto original_result = original(&original_pEditBox, nVirtualKey);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A80A0 (#10081)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10081, dll_base + 0x000080A0);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			int32_t nMaxLength{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			sut(&moo_pEditBox, nMaxLength);
			original(&original_pEditBox, nMaxLength);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A80F0 (#10076)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10076, dll_base + 0x000080F0);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			char szText{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pEditBox, &szText);
			const auto original_result = original(&original_pEditBox, &szText);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A8140 (#10075)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10075, dll_base + 0x00008140);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			Unicode pText{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pEditBox, &pText);
			const auto original_result = original(&original_pEditBox, &pText);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A81E0 (#10077)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10077_EDITBOX_GetText, dll_base + 0x000081E0);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pEditBox);
			const auto original_result = original(&original_pEditBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A8230 (#10080)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10080_EDITBOX_SetNextEditBox, dll_base + 0x00008230);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc moo_pNext{};
			D2WinEditBoxStrc original_pEditBox{};
			D2WinEditBoxStrc original_pNext{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox,
				D2WinEditBoxStrc& pNext
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox, moo_pNext);
			setup_data(original_pEditBox, original_pNext);

			// Call both implementations
			sut(&moo_pEditBox, &moo_pNext);
			original(&original_pEditBox, &original_pNext);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
			SKIP_MOO_CHECK_EQ(moo_pNext, original_pNext, "Comparing pNext");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A82D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_Draw, dll_base + 0x000082D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A86C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_DrawMultiline, dll_base + 0x000086C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A8D60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_GetCursorOffset, dll_base + 0x00008D60);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			int32_t moo_pX{};
			int32_t moo_pY{};
			D2WinEditBoxStrc original_pEditBox{};
			int32_t original_pX{};
			int32_t original_pY{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox,
				int32_t& pX,
				int32_t& pY
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox, moo_pX, moo_pY);
			setup_data(original_pEditBox, original_pX, original_pY);

			// Call both implementations
			sut(&moo_pEditBox, &moo_pX, &moo_pY);
			original(&original_pEditBox, &original_pX, &original_pY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_HandleMouseDown, dll_base + 0x00009120);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A93A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_HandleMouseUp, dll_base + 0x000093A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_SetCursorFromOffset, dll_base + 0x00009410);
		
		SUBCASE("")
		{
			// Input data
			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				SMSGHANDLER_PARAMS& pMsg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMsg);
			setup_data(original_pMsg);

			// Call both implementations
			const auto moo_result = sut(&moo_pMsg, nX, nY);
			const auto original_result = original(&original_pMsg, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A97D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_HandleMouseDownMultiline, dll_base + 0x000097D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9850 (#10078)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10078_IsNumber, dll_base + 0x00009850);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			char moo_szChar{};
			D2WinEditBoxStrc original_pEditBox{};
			char original_szChar{};
			int32_t nPosition{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox,
				char& szChar
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox, moo_szChar);
			setup_data(original_pEditBox, original_szChar);

			// Call both implementations
			const auto moo_result = sut(&moo_pEditBox, nPosition, &moo_szChar);
			const auto original_result = original(&original_pEditBox, nPosition, &original_szChar);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
			SKIP_MOO_CHECK_EQ(moo_szChar, original_szChar, "Comparing szChar");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9870 (#10079)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10079_IsLetter, dll_base + 0x00009870);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			char moo_szChar{};
			D2WinEditBoxStrc original_pEditBox{};
			char original_szChar{};
			int32_t nPosition{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox,
				char& szChar
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox, moo_szChar);
			setup_data(original_pEditBox, original_szChar);

			// Call both implementations
			const auto moo_result = sut(&moo_pEditBox, nPosition, &moo_szChar);
			const auto original_result = original(&original_pEditBox, nPosition, &original_szChar);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
			SKIP_MOO_CHECK_EQ(moo_szChar, original_szChar, "Comparing szChar");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A98A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_UpdateVisibleRange, dll_base + 0x000098A0);
		
		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};

			const auto setup_data = [](
				D2WinEditBoxStrc& pEditBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pEditBox);
			setup_data(original_pEditBox);

			// Call both implementations
			sut(&moo_pEditBox);
			original(&original_pEditBox);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}
}
