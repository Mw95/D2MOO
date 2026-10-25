#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2WinTextBox.h>


TEST_SUITE("D2WinTextBoxTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AFAA0 (#10042)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10042_TEXTBOX_Create, dll_base + 0x0000FAA0);
		
		SUBCASE("")
		{
			// Input data
			D2CellFileStrc moo_pCellFile{};
			D2CellFileStrc original_pCellFile{};
			int nX{};
			int nY{};
			int nWidth{};
			int nHeight{};
			int nTextOffsetX{};
			int nTextOffsetY{};
			unsigned int dwTextBoxFlags{};
			int pFont{};
			int pScrollBarRect{};

			const auto setup_data = [](
				D2CellFileStrc& pCellFile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCellFile);
			setup_data(original_pCellFile);

			// Call both implementations
			const auto moo_result = sut(nX, nY, nWidth, nHeight, nTextOffsetX, nTextOffsetY, &moo_pCellFile, nullptr, dwTextBoxFlags, pFont, pScrollBarRect);
			const auto original_result = original(nX, nY, nWidth, nHeight, nTextOffsetX, nTextOffsetY, &original_pCellFile, nullptr, dwTextBoxFlags, pFont, pScrollBarRect);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCellFile, original_pCellFile, "Comparing pCellFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AFCC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TEXTBOX_UpdateLineSpacing, dll_base + 0x0000FCC0);
		
		SUBCASE("")
		{
			Font nFontSize{};

			// Call both implementations
			sut(nFontSize);
			original(nFontSize);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AFDC0 (#10043)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10043_TEXTBOX_Destroy, dll_base + 0x0000FDC0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox);
			const auto original_result = original(&original_pTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AFE30 (#10047)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10047, dll_base + 0x0000FE30);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox);
			const auto original_result = original(&original_pTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AFED0 (#10062)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10062, dll_base + 0x0000FED0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int nContinuedLineSpacing{};
			int nLineSpacing{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, nContinuedLineSpacing, nLineSpacing);
			const auto original_result = original(&original_pTextBox, nContinuedLineSpacing, nLineSpacing);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AFF30 (#10045)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10045, dll_base + 0x0000FF30);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			char szText{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			sut(&moo_pTextBox, &szText);
			original(&original_pTextBox, &szText);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AFFB0 (#10046)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10046, dll_base + 0x0000FFB0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			char szText{};
			int nColor{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, &szText, nColor);
			const auto original_result = original(&original_pTextBox, &szText, nColor);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0030 (#10044)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10044, dll_base + 0x00010030);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			Unicode wszText{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, &wszText);
			const auto original_result = original(&original_pTextBox, &wszText);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0040 (#10051)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10051, dll_base + 0x00010040);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			Unicode wszText{};
			int nColor{};
			char bContinued{};
			signed int nIndentMode{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, &wszText, nColor, bContinued, nIndentMode);
			const auto original_result = original(&original_pTextBox, &wszText, nColor, bContinued, nIndentMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B05E0 (#10198)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10198, dll_base + 0x000105E0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			Unicode pText{};
			int nCount{};
			int nColor{};
			char bContinued{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, &pText, nCount, nColor, bContinued);
			const auto original_result = original(&original_pTextBox, &pText, nCount, nColor, bContinued);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0750 (#10057)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10057, dll_base + 0x00010750);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			char szText{};
			int nLine{};
			int nColumn{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, &szText, nLine, nColumn);
			const auto original_result = original(&original_pTextBox, &szText, nLine, nColumn);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B07C0 (#10058)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10058_0, dll_base + 0x000107C0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			Unicode pText{};
			int nLine{};
			int nColumn{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, &pText, nLine, nColumn);
			const auto original_result = original(&original_pTextBox, &pText, nLine, nColumn);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B08F0 (#10197)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10197, dll_base + 0x000108F0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int nLineNum{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			sut(&moo_pTextBox, nLineNum);
			original(&original_pTextBox, nLineNum);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B09E0 (#10052)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10052_TEXTBOX_GetNumLines, dll_base + 0x000109E0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox);
			const auto original_result = original(&original_pTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0A30 (#10054)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10054, dll_base + 0x00010A30);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox);
			const auto original_result = original(&original_pTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0A80 (#10049)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10049, dll_base + 0x00010A80);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox);
			const auto original_result = original(&original_pTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0AD0 (#10050)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10050_TEXTBOX_SetLine, dll_base + 0x00010AD0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int nLine{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			sut(&moo_pTextBox, nLine);
			original(&original_pTextBox, nLine);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0B30 (#10053)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10053, dll_base + 0x00010B30);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int nLine{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, nLine);
			const auto original_result = original(&original_pTextBox, nLine);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0BC0 (#10055)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10055, dll_base + 0x00010BC0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox);
			const auto original_result = original(&original_pTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0C50 (#10048)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10048, dll_base + 0x00010C50);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox);
			const auto original_result = original(&original_pTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0CC0 (#10196)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10196, dll_base + 0x00010CC0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int nLineNum{};
			int nColumnNum{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, nLineNum, nColumnNum);
			const auto original_result = original(&original_pTextBox, nLineNum, nColumnNum);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0DC0 (#10056)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10056, dll_base + 0x00010DC0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int nNumColumns{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			sut(&moo_pTextBox, nNumColumns);
			original(&original_pTextBox, nNumColumns);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0E60 (#10059)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10059, dll_base + 0x00010E60);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			Unicode moo_pColumn{};
			D2WinTextBoxStrc original_pTextBox{};
			Unicode original_pColumn{};
			int nColumn{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox,
				Unicode& pColumn
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox, moo_pColumn);
			setup_data(original_pTextBox, original_pColumn);

			// Call both implementations
			sut(&moo_pTextBox, nColumn, &moo_pColumn);
			original(&original_pTextBox, nColumn, &original_pColumn);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
			SKIP_MOO_CHECK_EQ(moo_pColumn, original_pColumn, "Comparing pColumn");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0EE0 (#10060)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10060, dll_base + 0x00010EE0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int nColumn{};
			int nFlags{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			sut(&moo_pTextBox, nColumn, nFlags);
			original(&original_pTextBox, nColumn, nFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0F60 (#10061)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10061, dll_base + 0x00010F60);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox);
			const auto original_result = original(&original_pTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0FC0 (#10187)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10187, dll_base + 0x00010FC0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int bSet{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			sut(&moo_pTextBox, bSet);
			original(&original_pTextBox, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1030 (#10188)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10188, dll_base + 0x00011030);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int nLineNum{};
			int nColor{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, nLineNum, nColor);
			const auto original_result = original(&original_pTextBox, nLineNum, nColor);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1130" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TEXTBOX_Draw, dll_base + 0x00011130);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B15A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TEXTBOX_HandleMouseDown, dll_base + 0x000115A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B16B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TEXTBOX_HandleVirtualKeyInput, dll_base + 0x000116B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B18F0 (#10190)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10190, dll_base + 0x000118F0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox);
			const auto original_result = original(&original_pTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1940 (#10191)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10191, dll_base + 0x00011940);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int nMaxSteps{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, nMaxSteps);
			const auto original_result = original(&original_pTextBox, nMaxSteps);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1990 (#10192)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10192, dll_base + 0x00011990);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox);
			const auto original_result = original(&original_pTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B19E0 (#10193)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10193, dll_base + 0x000119E0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int nStep{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, nStep);
			const auto original_result = original(&original_pTextBox, nStep);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1A30 (#10194)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10194, dll_base + 0x00011A30);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc moo_pTargetTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			D2WinTextBoxStrc original_pTargetTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox,
				D2WinTextBoxStrc& pTargetTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox, moo_pTargetTextBox);
			setup_data(original_pTextBox, original_pTargetTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, &moo_pTargetTextBox);
			const auto original_result = original(&original_pTextBox, &original_pTargetTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
			SKIP_MOO_CHECK_EQ(moo_pTargetTextBox, original_pTargetTextBox, "Comparing pTargetTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1A80 (#10195)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10195, dll_base + 0x00011A80);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox, nullptr);
			const auto original_result = original(&original_pTextBox, nullptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1AD0 (#10204)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10204, dll_base + 0x00011AD0);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			int nPageSize{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			sut(&moo_pTextBox, nPageSize);
			original(&original_pTextBox, nPageSize);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1B20 (#10203)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10203_TEXTBOX, dll_base + 0x00011B20);
		
		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};

			const auto setup_data = [](
				D2WinTextBoxStrc& pTextBox
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTextBox);
			setup_data(original_pTextBox);

			// Call both implementations
			const auto moo_result = sut(&moo_pTextBox);
			const auto original_result = original(&original_pTextBox);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		}
	}
}
