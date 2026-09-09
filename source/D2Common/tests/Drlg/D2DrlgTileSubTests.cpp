#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgTileSub.h>


TEST_SUITE("D2DrlgTileSubTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8A460" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_AddSecondaryBorder, dll_base + 0x0004A460);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnkOutdoorStrc a1{};
				
				return std::tuple{ a1 };
			};
			
			// Input data
			auto [moo_a1] = setup_data();
			auto [original_a1] = setup_data();

			// Call both implementations
			sut(&moo_a1);
			original(&original_a1);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8A750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_TestReplaceSubPreset, dll_base + 0x0004A750);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnkOutdoorStrc a3{};
				D2DrlgSubstGroupStrc pSubstGroup{};
				D2LvlSubTxt pLvlSubTxtRecord{};
				
				return std::tuple{ a3, pSubstGroup, pLvlSubTxtRecord };
			};
			
			// Input data
			auto [moo_a3, moo_pSubstGroup, moo_pLvlSubTxtRecord] = setup_data();
			auto [original_a3, original_pSubstGroup, original_pLvlSubTxtRecord] = setup_data();
			int a1{};
			int a2{};

			// Call both implementations
			const auto moo_result = sut(a1, a2, &moo_a3, &moo_pSubstGroup, &moo_pLvlSubTxtRecord);
			const auto original_result = original(a1, a2, &original_a3, &original_pSubstGroup, &original_pLvlSubTxtRecord);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			SKIP_MOO_CHECK_EQ(moo_pSubstGroup, original_pSubstGroup, "Comparing pSubstGroup");
			SKIP_MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8A8E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_ReplaceSubPreset, dll_base + 0x0004A8E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnkOutdoorStrc a3{};
				D2DrlgSubstGroupStrc pSubstGroup{};
				D2LvlSubTxt pLvlSubTxtRecord{};
				
				return std::tuple{ a3, pSubstGroup, pLvlSubTxtRecord };
			};
			
			// Input data
			auto [moo_a3, moo_pSubstGroup, moo_pLvlSubTxtRecord] = setup_data();
			auto [original_a3, original_pSubstGroup, original_pLvlSubTxtRecord] = setup_data();
			int a1{};
			int a2{};
			int a6{};

			// Call both implementations
			sut(a1, a2, &moo_a3, &moo_pSubstGroup, &moo_pLvlSubTxtRecord, a6);
			original(a1, a2, &original_a3, &original_pSubstGroup, &original_pLvlSubTxtRecord, a6);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			SKIP_MOO_CHECK_EQ(moo_pSubstGroup, original_pSubstGroup, "Comparing pSubstGroup");
			SKIP_MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8AA80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD8AA80, dll_base + 0x0004AA80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnkOutdoorStrc2 a1{};
				
				return std::tuple{ a1 };
			};
			
			// Input data
			auto [moo_a1] = setup_data();
			auto [original_a1] = setup_data();

			// Call both implementations
			sut(&moo_a1);
			original(&original_a1);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8ACE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD8ACE0, dll_base + 0x0004ACE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnkOutdoorStrc2 a4{};
				D2DrlgSubstGroupStrc pSubstGroup{};
				D2LvlSubTxt pLvlSubTxtRecord{};
				
				return std::tuple{ a4, pSubstGroup, pLvlSubTxtRecord };
			};
			
			// Input data
			auto [moo_a4, moo_pSubstGroup, moo_pLvlSubTxtRecord] = setup_data();
			auto [original_a4, original_pSubstGroup, original_pLvlSubTxtRecord] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			int nX{};
			int nY{};
			int a7{};

			// Call both implementations
			sut(moo_pMemPool, nX, nY, &moo_a4, &moo_pSubstGroup, &moo_pLvlSubTxtRecord, a7);
			original(original_pMemPool, nX, nY, &original_a4, &original_pSubstGroup, &original_pLvlSubTxtRecord, a7);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
			SKIP_MOO_CHECK_EQ(moo_pSubstGroup, original_pSubstGroup, "Comparing pSubstGroup");
			SKIP_MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B010" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD8B010, dll_base + 0x0004B010);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnkOutdoorStrc2 a3{};
				D2DrlgSubstGroupStrc pSubstGroup{};
				D2LvlSubTxt pLvlSubTxtRecord{};
				
				return std::tuple{ a3, pSubstGroup, pLvlSubTxtRecord };
			};
			
			// Input data
			auto [moo_a3, moo_pSubstGroup, moo_pLvlSubTxtRecord] = setup_data();
			auto [original_a3, original_pSubstGroup, original_pLvlSubTxtRecord] = setup_data();
			int a1{};
			int a2{};

			// Call both implementations
			const auto moo_result = sut(a1, a2, &moo_a3, &moo_pSubstGroup, &moo_pLvlSubTxtRecord);
			const auto original_result = original(a1, a2, &original_a3, &original_pSubstGroup, &original_pLvlSubTxtRecord);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			SKIP_MOO_CHECK_EQ(moo_pSubstGroup, original_pSubstGroup, "Comparing pSubstGroup");
			SKIP_MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B130" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD8B130, dll_base + 0x0004B130);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnkOutdoorStrc2 a3{};
				D2DrlgSubstGroupStrc pSubstGroup{};
				D2LvlSubTxt pLvlSubTxtRecord{};
				
				return std::tuple{ a3, pSubstGroup, pLvlSubTxtRecord };
			};
			
			// Input data
			auto [moo_a3, moo_pSubstGroup, moo_pLvlSubTxtRecord] = setup_data();
			auto [original_a3, original_pSubstGroup, original_pLvlSubTxtRecord] = setup_data();
			int a1{};
			int a2{};

			// Call both implementations
			const auto moo_result = sut(a1, a2, &moo_a3, &moo_pSubstGroup, &moo_pLvlSubTxtRecord);
			const auto original_result = original(a1, a2, &original_a3, &original_pSubstGroup, &original_pLvlSubTxtRecord);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			SKIP_MOO_CHECK_EQ(moo_pSubstGroup, original_pSubstGroup, "Comparing pSubstGroup");
			SKIP_MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B290" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_DoSubstitutions, dll_base + 0x0004B290);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnkOutdoorStrc2 pOutdoorLevel{};
				D2LvlSubTxt pLvlSubTxtRecord{};
				
				return std::tuple{ pOutdoorLevel, pLvlSubTxtRecord };
			};
			
			// Input data
			auto [moo_pOutdoorLevel, moo_pLvlSubTxtRecord] = setup_data();
			auto [original_pOutdoorLevel, original_pLvlSubTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOutdoorLevel, &moo_pLvlSubTxtRecord);
			original(&original_pOutdoorLevel, &original_pLvlSubTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOutdoorLevel, original_pOutdoorLevel, "Comparing pOutdoorLevel");
			SKIP_MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B640" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_InitializeDrlgFile, dll_base + 0x0004B640);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2LvlSubTxt pLvlSubTxtRecord{};
				
				return std::tuple{ pLvlSubTxtRecord };
			};
			
			// Input data
			auto [moo_pLvlSubTxtRecord] = setup_data();
			auto [original_pLvlSubTxtRecord] = setup_data();
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive, &moo_pLvlSubTxtRecord);
			original(hArchive, &original_pLvlSubTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B770" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_FreeDrlgFile, dll_base + 0x0004B770);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2LvlSubTxt pLvlSubTxtRecord{};
				
				return std::tuple{ pLvlSubTxtRecord };
			};
			
			// Input data
			auto [moo_pLvlSubTxtRecord] = setup_data();
			auto [original_pLvlSubTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pLvlSubTxtRecord);
			original(&original_pLvlSubTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLvlSubTxtRecord, original_pLvlSubTxtRecord, "Comparing pLvlSubTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B7E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGTILESUB_PickSubThemes, dll_base + 0x0004B7E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();
			int nSubType{};
			int nSubTheme{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nSubType, nSubTheme);
			const auto original_result = original(&original_pDrlgRoom, nSubType, nSubTheme);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
}
