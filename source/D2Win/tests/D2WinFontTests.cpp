#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2WinFont.h>


TEST_SUITE("D2WinFontTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9B00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_ClearFramedText, dll_base + 0x00009B00);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9B20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_ClearColorCodeChar, dll_base + 0x00009B20);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9B40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_ClearMonsterIndicatorChar, dll_base + 0x00009B40);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9B60 (#10115)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10115_FONT, dll_base + 0x00009B60);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9DC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_GetCellFilePath, dll_base + 0x00009DC0);
		
		SUBCASE("")
		{
			// Input data
			char moo_pBuffer{};
			char original_pBuffer{};
			int nFont{};
			int nLength{};

			const auto setup_data = [](
				char& pBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pBuffer);
			setup_data(original_pBuffer);

			// Call both implementations
			sut(nFont, &moo_pBuffer, nLength);
			original(nFont, &original_pBuffer, nLength);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9E90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_LoadFontTable, dll_base + 0x00009E90);
		
		SUBCASE("")
		{
			int nFont{};

			// Call both implementations
			sut(nFont);
			original(nFont);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9F90 (#10116)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10116, dll_base + 0x00009F90);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9FF0 (#10127)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10127_SetFont, dll_base + 0x00009FF0);
		
		SUBCASE("")
		{
			Font nFontSize{};

			// Call both implementations
			const auto moo_result = sut(nFontSize);
			const auto original_result = original(nFontSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AA100" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_GetCharInfoDirect, dll_base + 0x0000A100);
		
		SUBCASE("")
		{
			Unicode wszChar{};

			// Call both implementations
			const auto moo_result = sut(wszChar);
			const auto original_result = original(wszChar);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AA140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_GetCharInfoSearch, dll_base + 0x0000A140);
		
		SUBCASE("")
		{
			Unicode wszChar{};

			// Call both implementations
			const auto moo_result = sut(wszChar);
			const auto original_result = original(wszChar);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AA1D0 (#10123)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10123, dll_base + 0x0000A1D0);
		
		SUBCASE("")
		{
			Unicode wszText{};
			int nTextLength{};

			// Call both implementations
			const auto moo_result = sut(&wszText, nTextLength);
			const auto original_result = original(&wszText, nTextLength);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AA260 (#10122)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10122, dll_base + 0x0000A260);
		
		SUBCASE("")
		{
			Unicode wszText{};
			int nTextLength{};

			// Call both implementations
			const auto moo_result = sut(&wszText, nTextLength);
			const auto original_result = original(&wszText, nTextLength);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AA2A0 (#10121)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10121_GetTextWidth, dll_base + 0x0000A2A0);
		
		SUBCASE("")
		{
			Unicode wszText{};

			// Call both implementations
			const auto moo_result = sut(&wszText);
			const auto original_result = original(&wszText);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AA2F0 (#10125)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10125, dll_base + 0x0000A2F0);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AA310 (#10119)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10119_DrawCroppedText, dll_base + 0x0000A310);
		
		SUBCASE("")
		{
			Unicode wszText{};
			int32_t nX{};
			int32_t nY{};
			int32_t nUnused{};
			int32_t nCropOffset{};
			int32_t nCropHeight{};
			int32_t nUnused2{};

			// Call both implementations
			sut(&wszText, nX, nY, nUnused, nCropOffset, nCropHeight, nUnused2);
			original(&wszText, nX, nY, nUnused, nCropOffset, nCropHeight, nUnused2);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AA510" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_DrawScrollingText, dll_base + 0x0000A510);
		
		SUBCASE("")
		{
			Unicode wszText{};
			int32_t nX{};
			int32_t nY{};
			int32_t nColor{};
			int32_t nScrollOffset{};
			int32_t nMaxWidth{};

			// Call both implementations
			sut(&wszText, nX, nY, nColor, nScrollOffset, nMaxWidth);
			original(&wszText, nX, nY, nColor, nScrollOffset, nMaxWidth);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AA6E0 (#10124)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10124, dll_base + 0x0000A6E0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AA910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_GetMaxLineWidth, dll_base + 0x0000A910);
		
		SUBCASE("")
		{
			Unicode pStr{};

			// Call both implementations
			const auto moo_result = sut(&pStr);
			const auto original_result = original(&pStr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AA9E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_DrawTextEx, dll_base + 0x0000A9E0);
		
		SUBCASE("")
		{
			Unicode wszText{};
			int32_t nX{};
			int32_t nY{};
			int32_t nBoxWidth{};
			int32_t nGlobalPaletteShift{};
			int32_t bCentered{};

			// Call both implementations
			sut(&wszText, nX, nY, nBoxWidth, nGlobalPaletteShift, bCentered);
			original(&wszText, nX, nY, nBoxWidth, nGlobalPaletteShift, bCentered);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AABB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_GetFirstLineWidth, dll_base + 0x0000ABB0);
		
		SUBCASE("")
		{
			Unicode pStr{};

			// Call both implementations
			const auto moo_result = sut(&pStr);
			const auto original_result = original(&pStr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AAC60 (#10129)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10129_DrawFramedText, dll_base + 0x0000AC60);
		
		SUBCASE("")
		{
			Unicode wszText{};
			int nX{};
			int nY{};
			int nTextColor{};
			int nAlign{};

			// Call both implementations
			sut(&wszText, nX, nY, nTextColor, nAlign);
			original(&wszText, nX, nY, nTextColor, nAlign);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AACD0 (#10130)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10130_DrawFramedTextEx, dll_base + 0x0000ACD0);
		
		SUBCASE("")
		{
			Unicode wszText{};
			int nX{};
			int nY{};
			int nTextColor{};
			int nAlign{};
			int nRectangleColor{};

			// Call both implementations
			sut(&wszText, nX, nY, nTextColor, nAlign, nRectangleColor);
			original(&wszText, nX, nY, nTextColor, nAlign, nRectangleColor);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AAD40 (#10117)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10117_DrawText, dll_base + 0x0000AD40);
		
		SUBCASE("")
		{
			Unicode wszText{};
			int nX{};
			int nY{};
			int nColor{};
			BOOL bCentered{};

			// Call both implementations
			sut(&wszText, nX, nY, nColor, bCentered);
			original(&wszText, nX, nY, nColor, bCentered);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AAD80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10118_DrawBlendedText, dll_base + 0x0000AD80);
		
		SUBCASE("")
		{
			Unicode wszText{};
			int32_t nX{};
			int32_t nY{};
			int32_t nColor{};
			int32_t bCentered{};
			DrawMode eDrawMode{};

			// Call both implementations
			sut(&wszText, nX, nY, nColor, bCentered, eDrawMode);
			original(&wszText, nX, nY, nColor, bCentered, eDrawMode);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AAF80 (#10126)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10126_DrawTextFromCache, dll_base + 0x0000AF80);
		
		SUBCASE("")
		{
			// Input data
			Unicode moo_wszText{};
			Unicode original_wszText{};
			int nX{};
			int nY{};

			const auto setup_data = [](
				Unicode& wszText
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_wszText);
			setup_data(original_wszText);

			// Call both implementations
			sut(&moo_wszText, nX, nY);
			original(&original_wszText, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_wszText, original_wszText, "Comparing wszText");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AB080 (#10132)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10132, dll_base + 0x0000B080);
		
		SUBCASE("")
		{
			Unicode wszText{};
			int nX{};
			int nY{};
			DWORD dwColor{};
			DrawMode eDrawMode{};
			int nColor{};

			// Call both implementations
			sut(&wszText, nX, nY, dwColor, eDrawMode, nColor);
			original(&wszText, nX, nY, dwColor, eDrawMode, nColor);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AB1B0 (#10133)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10133, dll_base + 0x0000B1B0);
		
		SUBCASE("")
		{
			Unicode pText{};
			int nX{};
			int nY{};
			DWORD dwColor{};
			DrawMode eDrawMode{};
			int nPaletteShift{};

			// Call both implementations
			sut(&pText, nX, nY, dwColor, eDrawMode, nPaletteShift);
			original(&pText, nX, nY, dwColor, eDrawMode, nPaletteShift);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AB260 (#1031)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10131_GetTextDimensions, dll_base + 0x0000B260);
		
		SUBCASE("")
		{
			// Input data
			int moo_pWidth{};
			int moo_pHeight{};
			int original_pWidth{};
			int original_pHeight{};
			Unicode pText{};

			const auto setup_data = [](
				int& pWidth,
				int& pHeight
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pWidth, moo_pHeight);
			setup_data(original_pWidth, original_pHeight);

			// Call both implementations
			sut(&pText, &moo_pWidth, &moo_pHeight);
			original(&pText, &original_pWidth, &original_pHeight);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pWidth, original_pWidth, "Comparing pWidth");
			SKIP_MOO_CHECK_EQ(moo_pHeight, original_pHeight, "Comparing pHeight");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AB2F0 (#10128)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10128, dll_base + 0x0000B2F0);
		
		SUBCASE("")
		{
			uint8_t nChar{};

			// Call both implementations
			const auto moo_result = sut(nChar);
			const auto original_result = original(nChar);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AB360" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_DrawTextWithBox, dll_base + 0x0000B360);
		
		SUBCASE("")
		{
			Unicode pStr{};
			int nX{};
			int nY{};
			int nBoxWidth{};
			DWORD dwColor{};
			DrawMode eDrawMode{};
			int nPaletteShift{};

			// Call both implementations
			sut(&pStr, nX, nY, nBoxWidth, dwColor, eDrawMode, nPaletteShift);
			original(&pStr, nX, nY, nBoxWidth, dwColor, eDrawMode, nPaletteShift);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AB480 (#10134)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10134_DrawCellFile, dll_base + 0x0000B480);
		
		SUBCASE("")
		{
			// Input data
			D2CellFileStrc moo_pCellFile{};
			D2CellFileStrc original_pCellFile{};
			int nX{};
			int nY{};
			int nDiv{};
			DrawMode eDrawMode{};
			int nColor{};

			const auto setup_data = [](
				D2CellFileStrc& pCellFile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCellFile);
			setup_data(original_pCellFile);

			// Call both implementations
			sut(&moo_pCellFile, nX, nY, nDiv, eDrawMode, nColor);
			original(&original_pCellFile, nX, nY, nDiv, eDrawMode, nColor);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCellFile, original_pCellFile, "Comparing pCellFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AB560 (#10120)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10120, dll_base + 0x0000B560);
		
		SUBCASE("")
		{
			Unicode wszText{};
			int nX{};
			int nY{};
			int nColor{};
			int nAlign{};
			int nProgress{};

			// Call both implementations
			sut(&wszText, nX, nY, nColor, nAlign, nProgress);
			original(&wszText, nX, nY, nColor, nAlign, nProgress);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AB730 (#10200)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10200, dll_base + 0x0000B730);
		
		SUBCASE("")
		{
			// Input data
			D2SplittedTextStrc moo_pSplitText{};
			D2SplittedTextStrc original_pSplitText{};

			const auto setup_data = [](
				D2SplittedTextStrc& pSplitText
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSplitText);
			setup_data(original_pSplitText);

			// Call both implementations
			sut(&moo_pSplitText);
			original(&original_pSplitText);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSplitText, original_pSplitText, "Comparing pSplitText");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AB770 (#10199)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10199, dll_base + 0x0000B770);
		
		SUBCASE("")
		{
			// Input data
			int moo_pLines{};
			int original_pLines{};
			Unicode wszText{};
			int nMaxLength{};

			const auto setup_data = [](
				int& pLines
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pLines);
			setup_data(original_pLines);

			// Call both implementations
			const auto moo_result = sut(&wszText, &moo_pLines, nMaxLength);
			const auto original_result = original(&wszText, &original_pLines, nMaxLength);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLines, original_pLines, "Comparing pLines");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ABA70 (#10206)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10206, dll_base + 0x0000BA70);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ABA80 (#10207)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10207, dll_base + 0x0000BA80);
		
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
