#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2DataTbls.h>
#include <Units/Units.h>


TEST_SUITE("D2DataTblsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD494D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetStringIdFromReferenceString, dll_base + 0x000094D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szReference{};
				
				return std::tuple{ szReference };
			};
			
			// Input data
			auto [moo_szReference] = setup_data();
			auto [original_szReference] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_szReference);
			const auto original_result = original(&original_szReference);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szReference, original_szReference, "Comparing szReference");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD49660 (#11255)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetCodeFromCompCodeTxt, dll_base + 0x00009660);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nCompCode{};

			// Call both implementations
			const auto moo_result = sut(nCompCode);
			const auto original_result = original(nCompCode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD49680 (#11249)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetExpRatio, dll_base + 0x00009680);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nLevel{};

			// Call both implementations
			const auto moo_result = sut(nLevel);
			const auto original_result = original(nLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD496B0 (#10628)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetLevelThreshold, dll_base + 0x000096B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nClass{};
			uint32_t dwLevel{};

			// Call both implementations
			const auto moo_result = sut(nClass, dwLevel);
			const auto original_result = original(nClass, dwLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD496E0 (#10629)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetMaxLevel, dll_base + 0x000096E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nClass{};

			// Call both implementations
			const auto moo_result = sut(nClass);
			const auto original_result = original(nClass);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD49710 (#10630)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetCurrentLevelFromExp, dll_base + 0x00009710);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nClass{};
			uint32_t dwExperience{};

			// Call both implementations
			const auto moo_result = sut(nClass, dwExperience);
			const auto original_result = original(nClass, dwExperience);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD49760" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetBinFileHandle, dll_base + 0x00009760);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				void* ppFileHandle{};
				int pSize{};
				int pSizeEx{};
				
				return std::tuple{ ppFileHandle, pSize, pSizeEx };
			};
			
			// Input data
			auto [moo_ppFileHandle, moo_pSize, moo_pSizeEx] = setup_data();
			auto [original_ppFileHandle, original_pSize, original_pSizeEx] = setup_data();
			HD2ARCHIVE hArchive{};
			char szFile{};

			// Call both implementations
			sut(hArchive, &szFile, &moo_ppFileHandle, &moo_pSize, &moo_pSizeEx);
			original(hArchive, &szFile, &original_ppFileHandle, &original_pSize, &original_pSizeEx);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppFileHandle, original_ppFileHandle, "Comparing ppFileHandle");
			SKIP_MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
			SKIP_MOO_CHECK_EQ(moo_pSizeEx, original_pSizeEx, "Comparing pSizeEx");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD49850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_AppendMemoryBuffer, dll_base + 0x00009850);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char* ppCodes{};
				int pSize{};
				int pSizeEx{};
				
				return std::tuple{ ppCodes, pSize, pSizeEx };
			};
			
			// Input data
			auto [moo_ppCodes, moo_pSize, moo_pSizeEx] = setup_data();
			auto [original_ppCodes, original_pSize, original_pSizeEx] = setup_data();
			void* moo_pBuffer = nullptr;
			void* original_pBuffer = nullptr;
			int nBufferSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_ppCodes, &moo_pSize, &moo_pSizeEx, moo_pBuffer, nBufferSize);
			const auto original_result = original(&original_ppCodes, &original_pSize, &original_pSizeEx, original_pBuffer, nBufferSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppCodes, original_ppCodes, "Comparing ppCodes");
			SKIP_MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
			SKIP_MOO_CHECK_EQ(moo_pSizeEx, original_pSizeEx, "Comparing pSizeEx");
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4E4B0 (#10593)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetCharstatsTxtTable, dll_base + 0x0000E4B0);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4E4C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetAnimData, dll_base + 0x0000E4C0);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4E4D0 (#10655)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetDifficultyLevelsTxtRecord, dll_base + 0x0000E4D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nDifficulty{};

			// Call both implementations
			const auto moo_result = sut(nDifficulty);
			const auto original_result = original(nDifficulty);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4E500" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadStatesTxt, dll_base + 0x0000E500);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4F4A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_UnloadStatesTxt, dll_base + 0x0000F4A0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4F5A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadPetTypeTxt, dll_base + 0x0000F5A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4F990 (#11298)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetUnitNameFromUnit, dll_base + 0x0000F990);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				char szName{};
				
				return std::tuple{ pUnit, szName };
			};
			
			// Input data
			auto [moo_pUnit, moo_szName] = setup_data();
			auto [original_pUnit, original_szName] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_szName);
			const auto original_result = original(&original_pUnit, &original_szName);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4FB50 (#11299)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetUnitNameFromUnitTypeAndClassId, dll_base + 0x0000FB50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szName{};
				
				return std::tuple{ szName };
			};
			
			// Input data
			auto [moo_szName] = setup_data();
			auto [original_szName] = setup_data();
			int nUnitType{};
			int nClassId{};

			// Call both implementations
			const auto moo_result = sut(nUnitType, nClassId, &moo_szName);
			const auto original_result = original(nUnitType, nClassId, &original_szName);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4FCF0 (#10580)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_WriteBinFile, dll_base + 0x0000FCF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szFileName{};
				
				return std::tuple{ szFileName };
			};
			
			// Input data
			auto [moo_szFileName] = setup_data();
			auto [original_szFileName] = setup_data();
			void* moo_pWriteBuffer = nullptr;
			void* original_pWriteBuffer = nullptr;
			size_t nBufferSize{};
			int nRecordCount{};

			// Call both implementations
			sut(&moo_szFileName, moo_pWriteBuffer, nBufferSize, nRecordCount);
			original(&original_szFileName, original_pWriteBuffer, nBufferSize, nRecordCount);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szFileName, original_szFileName, "Comparing szFileName");
			SKIP_MOO_CHECK_EQ(moo_pWriteBuffer, original_pWriteBuffer, "Comparing pWriteBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4FD70 (#10578)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_CompileTxt, dll_base + 0x0000FD70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2BinFieldStrc pTbl{};
				int pRecordCount{};
				
				return std::tuple{ pTbl, pRecordCount };
			};
			
			// Input data
			auto [moo_pTbl, moo_pRecordCount] = setup_data();
			auto [original_pTbl, original_pRecordCount] = setup_data();
			HD2ARCHIVE hArchive{};
			char szName{};
			size_t dwSize{};

			// Call both implementations
			const auto moo_result = sut(hArchive, &szName, &moo_pTbl, &moo_pRecordCount, dwSize);
			const auto original_result = original(hArchive, &szName, &original_pTbl, &original_pRecordCount, dwSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTbl, original_pTbl, "Comparing pTbl");
			SKIP_MOO_CHECK_EQ(moo_pRecordCount, original_pRecordCount, "Comparing pRecordCount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD500F0 (#11242)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_ToggleCompileTxtFlag, dll_base + 0x000100F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			BOOL bSilent{};

			// Call both implementations
			sut(bSilent);
			original(bSilent);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD50110 (#10579)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_UnloadBin, dll_base + 0x00010110);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			void* moo_pBinFile = nullptr;
			void* original_pBinFile = nullptr;

			// Call both implementations
			sut(moo_pBinFile);
			original(original_pBinFile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pBinFile, original_pBinFile, "Comparing pBinFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD50150 (#10575)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_UnloadAllBins, dll_base + 0x00010150);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD504B0 (#10576)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadAllTxts, dll_base + 0x000104B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			HD2ARCHIVE hArchive{};
			int a2{};
			int a3{};

			// Call both implementations
			sut(hArchive, a2, a3);
			original(hArchive, a2, a3);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD507B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadSomeTxts, dll_base + 0x000107B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD50FB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadCharStatsTxt, dll_base + 0x00010FB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD51BF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadDifficultyLevelsTxt, dll_base + 0x00011BF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
}
