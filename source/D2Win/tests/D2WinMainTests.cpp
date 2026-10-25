#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2WinMain.h>


TEST_SUITE("D2WinMainTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACC60 (#10000)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_CreateWindow, dll_base + 0x0000CC60);
		
		SUBCASE("")
		{
			HINSTANCE hInstance{};
			DisplayType nRenderMode{};
			BOOL bWindowed{};
			BOOL bCompress{};

			// Call both implementations
			const auto moo_result = sut(hInstance, nRenderMode, bWindowed, bCompress);
			const auto original_result = original(hInstance, nRenderMode, bWindowed, bCompress);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACC90 (#10001)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_InitializeSpriteCache, dll_base + 0x0000CC90);
		
		SUBCASE("")
		{
			BOOL bWindowed{};
			D2GameResolutionMode nResolution{};

			// Call both implementations
			const auto moo_result = sut(bWindowed, nResolution);
			const auto original_result = original(bWindowed, nResolution);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACD40 (#10014)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10014_SetWndProc, dll_base + 0x0000CD40);
		
		SUBCASE("")
		{
			WNDPROC wndProc{};

			// Call both implementations
			const auto moo_result = sut(wndProc);
			const auto original_result = original(wndProc);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACD60 (#10015)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10015, dll_base + 0x0000CD60);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACDB0 (#10002)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_CloseSpriteCache, dll_base + 0x0000CDB0);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACDD0 (#10003)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10003, dll_base + 0x0000CDD0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACDE0 (#10004)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10004, dll_base + 0x0000CDE0);
		
		SUBCASE("")
		{
			BOOL bForceResize{};

			// Call both implementations
			sut(bForceResize);
			original(bForceResize);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACE20 (#10016)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10016, dll_base + 0x0000CE20);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACEC0 (#10005)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10005, dll_base + 0x0000CEC0);
		
		SUBCASE("")
		{
			BOOL bForceResize{};

			// Call both implementations
			const auto moo_result = sut(bForceResize);
			const auto original_result = original(bForceResize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACF20 (#10006)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10006_ClearDrawCaches, dll_base + 0x0000CF20);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACF30 (#10007)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BACKGROUND_SetCellFile, dll_base + 0x0000CF30);
		
		SUBCASE("")
		{
			// Input data
			D2CellFileStrc moo_pCellFile{};
			D2CellFileStrc original_pCellFile{};

			const auto setup_data = [](
				D2CellFileStrc& pCellFile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCellFile);
			setup_data(original_pCellFile);

			// Call both implementations
			const auto moo_result = sut(&moo_pCellFile);
			const auto original_result = original(&original_pCellFile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCellFile, original_pCellFile, "Comparing pCellFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACF50 (#10011)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CURSOR_SetCellFile, dll_base + 0x0000CF50);
		
		SUBCASE("")
		{
			// Input data
			D2CellFileStrc moo_pCellFile{};
			D2CellFileStrc original_pCellFile{};

			const auto setup_data = [](
				D2CellFileStrc& pCellFile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCellFile);
			setup_data(original_pCellFile);

			// Call both implementations
			const auto moo_result = sut(&moo_pCellFile);
			const auto original_result = original(&original_pCellFile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCellFile, original_pCellFile, "Comparing pCellFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACF70 (#10010)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10010, dll_base + 0x0000CF70);
		
		SUBCASE("")
		{
			// Call both implementations
			sut(nullptr);
			original(nullptr);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACF80 (#10009)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10009, dll_base + 0x0000CF80);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACF90 (#10008)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10008, dll_base + 0x0000CF90);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut(nullptr);
			const auto original_result = original(nullptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD0B0 (#10013)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_SetCellFile, dll_base + 0x0000D0B0);
		
		SUBCASE("")
		{
			// Input data
			D2WinControlStrc moo_pControl{};
			D2CellFileStrc moo_pCellFile{};
			D2WinControlStrc original_pControl{};
			D2CellFileStrc original_pCellFile{};

			const auto setup_data = [](
				D2WinControlStrc& pControl,
				D2CellFileStrc& pCellFile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pControl, moo_pCellFile);
			setup_data(original_pControl, original_pCellFile);

			// Call both implementations
			const auto moo_result = sut(&moo_pControl, &moo_pCellFile);
			const auto original_result = original(&original_pControl, &original_pCellFile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
			SKIP_MOO_CHECK_EQ(moo_pCellFile, original_pCellFile, "Comparing pCellFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD0D0 (#10012)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10012, dll_base + 0x0000D0D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD110 (#10023)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10023, dll_base + 0x0000D110);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_AppendToList, dll_base + 0x0000D120);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_RemoveFromList, dll_base + 0x0000D160);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD260 (#10017)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_Create, dll_base + 0x0000D260);
		
		SUBCASE("")
		{
			// Input data
			D2WinControlInitStrc moo_pControlInit{};
			D2WinControlInitStrc original_pControlInit{};

			const auto setup_data = [](
				D2WinControlInitStrc& pControlInit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pControlInit);
			setup_data(original_pControlInit);

			// Call both implementations
			const auto moo_result = sut(&moo_pControlInit);
			const auto original_result = original(&original_pControlInit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pControlInit, original_pControlInit, "Comparing pControlInit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD450 (#10018)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_Destroy, dll_base + 0x0000D450);
		
		SUBCASE("")
		{
			void* moo_ppControl = nullptr;
			void* original_ppControl = nullptr;

			// Call both implementations
			const auto moo_result = sut(moo_ppControl);
			const auto original_result = original(original_ppControl);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppControl, original_ppControl, "Comparing ppControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD570 (#10025)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10025_CONTROL_ToggleFirstFlag, dll_base + 0x0000D570);
		
		SUBCASE("")
		{
			// Input data
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};
			int bSet{};

			const auto setup_data = [](
				D2WinControlStrc& pControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pControl);
			setup_data(original_pControl);

			// Call both implementations
			sut(&moo_pControl, bSet);
			original(&original_pControl, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD5A0 (#10024)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10024_CONTROL_CheckFirstFlag, dll_base + 0x0000D5A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD5D0 (#10027)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10027_CONTROL_ToggleThirdFlag, dll_base + 0x0000D5D0);
		
		SUBCASE("")
		{
			// Input data
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};
			int bSet{};

			const auto setup_data = [](
				D2WinControlStrc& pControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pControl);
			setup_data(original_pControl);

			// Call both implementations
			sut(&moo_pControl, bSet);
			original(&original_pControl, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD620 (#10026)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10026_CONTROL_CheckThirdFlag, dll_base + 0x0000D620);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD650 (#10170)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_MouseInsideRect, dll_base + 0x0000D650);
		
		SUBCASE("")
		{
			RECT pRect{};

			// Call both implementations
			const auto moo_result = sut(&pRect);
			const auto original_result = original(&pRect);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD670" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_MouseMove_6F8AD670, dll_base + 0x0000D670);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD6F0 (#10019)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10019, dll_base + 0x0000D6F0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD9B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_MAINWINDOW_WndProc_6F8AD9B0, dll_base + 0x0000D9B0);
		
		SUBCASE("")
		{
			HWND hWnd{};
			UINT Msg{};
			WPARAM wParam{};
			LPARAM lParam{};

			// Call both implementations
			const auto moo_result = sut(hWnd, Msg, wParam, lParam);
			const auto original_result = original(hWnd, Msg, wParam, lParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ADA80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_Char_6F8ADA80, dll_base + 0x0000DA80);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ADB10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_Escape_6F8ADB10, dll_base + 0x0000DB10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ADB50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_VirtualKey_6F8ADB50, dll_base + 0x0000DB50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ADBE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_Control_6F8ADBE0, dll_base + 0x0000DBE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ADBF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_Control_6F8ADBF0, dll_base + 0x0000DBF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ADC00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_SysCommand_6F8ADC00, dll_base + 0x0000DC00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ADC40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_ActivateApp_6F8ADC40, dll_base + 0x0000DC40);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ADCD0 (#10168)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10168_WINMAIN_CreateScreenshot, dll_base + 0x0000DCD0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ADE70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_Snapshot_6F8ADE70, dll_base + 0x0000DE70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE020" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_KeyF1_6F8AE020, dll_base + 0x0000E020);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE070" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_MouseButton_6F8AE070, dll_base + 0x0000E070);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_MouseWheel_6F8AE220, dll_base + 0x0000E220);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE4A0 (#10029)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10029, dll_base + 0x0000E4A0);
		
		SUBCASE("")
		{
			int bShowCursor{};

			// Call both implementations
			sut(bShowCursor);
			original(bShowCursor);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE4B0 (#10030)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10030_CONTROL_ToggleFourthFlag, dll_base + 0x0000E4B0);
		
		SUBCASE("")
		{
			// Input data
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};
			int bSet{};

			const auto setup_data = [](
				D2WinControlStrc& pControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pControl);
			setup_data(original_pControl);

			// Call both implementations
			sut(&moo_pControl, bSet);
			original(&original_pControl, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE4F0 (#10031)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10031, dll_base + 0x0000E4F0);
		
		SUBCASE("")
		{
			void* moo_pCancelButton = nullptr;
			void* original_pCancelButton = nullptr;

			// Call both implementations
			sut(moo_pCancelButton);
			original(original_pCancelButton);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCancelButton, original_pCancelButton, "Comparing pCancelButton");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE500 (#10032)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_IsMouseButtonPressed, dll_base + 0x0000E500);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE510 (#10033)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10033, dll_base + 0x0000E510);
		
		SUBCASE("")
		{
			// Input data
			D2WinControlStrc moo_pModalControlList{};
			D2WinControlStrc original_pModalControlList{};
			int bDimBackground{};

			const auto setup_data = [](
				D2WinControlStrc& pModalControlList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pModalControlList);
			setup_data(original_pModalControlList);

			// Call both implementations
			const auto moo_result = sut(&moo_pModalControlList, bDimBackground);
			const auto original_result = original(&original_pModalControlList, bDimBackground);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pModalControlList, original_pModalControlList, "Comparing pModalControlList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE530 (#10035)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_GetType, dll_base + 0x0000E530);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_GetModalControlList, dll_base + 0x0000E540);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
}
