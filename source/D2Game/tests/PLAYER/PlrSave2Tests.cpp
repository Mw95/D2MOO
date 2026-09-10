#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <PLAYER/PlrSave2.h>
#include <Units/Units.h>


TEST_SUITE("PlrSave2Tests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8CCD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_WriteMercData, dll_base + 0x0005CCD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2SaveHeaderStrc pMercData{};
				
				return std::tuple{ pGame, pPlayer, pMercData };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pMercData] = setup_data();
			auto [original_pGame, original_pPlayer, original_pMercData] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pMercData);
			original(&original_pGame, &original_pPlayer, &original_pMercData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pMercData, original_pMercData, "Comparing pMercData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8CD80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_WriteSaveHeader, dll_base + 0x0005CD80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				uint8_t* ppSection{};
				
				return std::tuple{ pGame, pPlayer, ppSection };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_ppSection] = setup_data();
			auto [original_pGame, original_pPlayer, original_ppSection] = setup_data();
			uint8_t pEnd{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &pEnd);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &pEnd);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8D390" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_WriteWaypointData, dll_base + 0x0005D390);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				uint8_t* ppSection{};
				
				return std::tuple{ pGame, pUnit, ppSection };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_ppSection] = setup_data();
			auto [original_pGame, original_pUnit, original_ppSection] = setup_data();
			uint8_t pEnd{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_ppSection, &pEnd);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_ppSection, &pEnd);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8D440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_WritePlrIntroSection, dll_base + 0x0005D440);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				uint8_t* ppSection{};
				
				return std::tuple{ pGame, pUnit, ppSection };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_ppSection] = setup_data();
			auto [original_pGame, original_pUnit, original_ppSection] = setup_data();
			uint8_t pEnd{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_ppSection, &pEnd);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_ppSection, &pEnd);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8D4F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_WritePlayerStats, dll_base + 0x0005D4F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				uint8_t* ppSection{};
				
				return std::tuple{ pGame, pPlayer, ppSection };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_ppSection] = setup_data();
			auto [original_pGame, original_pPlayer, original_ppSection] = setup_data();
			uint8_t pEnd{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &pEnd);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &pEnd);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8D710" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_WriteCorpsesSection, dll_base + 0x0005D710);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				uint8_t* ppSection{};
				
				return std::tuple{ pGame, pPlayer, ppSection };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_ppSection] = setup_data();
			auto [original_pGame, original_pPlayer, original_ppSection] = setup_data();
			uint8_t pEnd{};
			int32_t a5{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &pEnd, a5);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &pEnd, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8D880" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_WriteIronGolemSection, dll_base + 0x0005D880);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				uint8_t* ppSection{};
				
				return std::tuple{ pGame, pPlayer, ppSection };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_ppSection] = setup_data();
			auto [original_pGame, original_pPlayer, original_ppSection] = setup_data();
			uint8_t pEnd{};
			int32_t a5{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &pEnd, a5);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &pEnd, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8D940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_CreateSaveFile, dll_base + 0x0005D940);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				uint8_t pData{};
				uint32_t pSize{};
				
				return std::tuple{ pGame, pPlayer, pData, pSize };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pData, moo_pSize] = setup_data();
			auto [original_pGame, original_pPlayer, original_pData, original_pSize] = setup_data();
			uint32_t nMaxSize{};
			int32_t a6{};
			int32_t a7{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pData, &moo_pSize, nMaxSize, a6, a7);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pData, &original_pSize, nMaxSize, a6, a7);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
			SKIP_MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8DD00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_ReadSaveHeader, dll_base + 0x0005DD00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ClientStrc pClient{};
				uint8_t* ppSection{};
				uint8_t pEnd{};
				D2UnitStrc* ppPlayer{};
				
				return std::tuple{ pGame, pClient, ppSection, pEnd, ppPlayer };
			};
			
			// Input data
			auto [moo_pGame, moo_pClient, moo_ppSection, moo_pEnd, moo_ppPlayer] = setup_data();
			auto [original_pGame, original_pClient, original_ppSection, original_pEnd, original_ppPlayer] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pClient, &moo_ppSection, &moo_pEnd, &moo_ppPlayer);
			const auto original_result = original(&original_pGame, &original_pClient, &original_ppSection, &original_pEnd, &original_ppPlayer);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
			SKIP_MOO_CHECK_EQ(moo_pEnd, original_pEnd, "Comparing pEnd");
			SKIP_MOO_CHECK_EQ(moo_ppPlayer, original_ppPlayer, "Comparing ppPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8E070" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_ReadWaypointData, dll_base + 0x0005E070);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				uint8_t* ppSection{};
				uint8_t pEnd{};
				
				return std::tuple{ pGame, pUnit, ppSection, pEnd };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_ppSection, moo_pEnd] = setup_data();
			auto [original_pGame, original_pUnit, original_ppSection, original_pEnd] = setup_data();
			int32_t nUnused{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_ppSection, &moo_pEnd, nUnused);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_ppSection, &original_pEnd, nUnused);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
			SKIP_MOO_CHECK_EQ(moo_pEnd, original_pEnd, "Comparing pEnd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8E0F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_ReadStatsEx, dll_base + 0x0005E0F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				uint8_t* ppSection{};
				uint8_t pEnd{};
				
				return std::tuple{ pGame, pUnit, ppSection, pEnd };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_ppSection, moo_pEnd] = setup_data();
			auto [original_pGame, original_pUnit, original_ppSection, original_pEnd] = setup_data();
			uint32_t nVersion{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_ppSection, &moo_pEnd, nVersion);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_ppSection, &original_pEnd, nVersion);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
			SKIP_MOO_CHECK_EQ(moo_pEnd, original_pEnd, "Comparing pEnd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8E250" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_ReadStats, dll_base + 0x0005E250);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				uint8_t* ppSection{};
				uint8_t pEnd{};
				
				return std::tuple{ pGame, pUnit, ppSection, pEnd };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_ppSection, moo_pEnd] = setup_data();
			auto [original_pGame, original_pUnit, original_ppSection, original_pEnd] = setup_data();
			uint32_t nVersion{};
			int32_t nStats{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_ppSection, &moo_pEnd, nVersion, nStats);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_ppSection, &original_pEnd, nVersion, nStats);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
			SKIP_MOO_CHECK_EQ(moo_pEnd, original_pEnd, "Comparing pEnd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8E330" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_ReadSkills, dll_base + 0x0005E330);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				uint8_t* ppSection{};
				uint8_t pEnd{};
				
				return std::tuple{ pGame, pPlayer, ppSection, pEnd };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_ppSection, moo_pEnd] = setup_data();
			auto [original_pGame, original_pPlayer, original_ppSection, original_pEnd] = setup_data();
			uint32_t nVersion{};
			int32_t nSkills{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &moo_pEnd, nVersion, nSkills);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &original_pEnd, nVersion, nSkills);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
			SKIP_MOO_CHECK_EQ(moo_pEnd, original_pEnd, "Comparing pEnd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8E420" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_ReadCorpses, dll_base + 0x0005E420);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				uint8_t* ppSection{};
				uint8_t pEnd{};
				int32_t a6{};
				
				return std::tuple{ pGame, pPlayer, ppSection, pEnd, a6 };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_ppSection, moo_pEnd, moo_a6] = setup_data();
			auto [original_pGame, original_pPlayer, original_ppSection, original_pEnd, original_a6] = setup_data();
			uint32_t nVersion{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &moo_pEnd, nVersion, &moo_a6);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &original_pEnd, nVersion, &original_a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
			SKIP_MOO_CHECK_EQ(moo_pEnd, original_pEnd, "Comparing pEnd");
			SKIP_MOO_CHECK_EQ(moo_a6, original_a6, "Comparing a6");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8E670" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_ReadMercData, dll_base + 0x0005E670);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2MercSaveDataStrc pData{};
				
				return std::tuple{ pGame, pPlayer, pData };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pData] = setup_data();
			auto [original_pGame, original_pPlayer, original_pData] = setup_data();
			uint32_t dwVersion{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pData, dwVersion);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pData, dwVersion);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8E850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_ReadPetSection, dll_base + 0x0005E850);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pMerc{};
				uint8_t* ppSection{};
				uint8_t pEnd{};
				int32_t a6{};
				
				return std::tuple{ pGame, pPlayer, pMerc, ppSection, pEnd, a6 };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pMerc, moo_ppSection, moo_pEnd, moo_a6] = setup_data();
			auto [original_pGame, original_pPlayer, original_pMerc, original_ppSection, original_pEnd, original_a6] = setup_data();
			uint32_t dwVersion{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pMerc, &moo_ppSection, &moo_pEnd, dwVersion, &moo_a6);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pMerc, &original_ppSection, &original_pEnd, dwVersion, &original_a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pMerc, original_pMerc, "Comparing pMerc");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
			SKIP_MOO_CHECK_EQ(moo_pEnd, original_pEnd, "Comparing pEnd");
			SKIP_MOO_CHECK_EQ(moo_a6, original_a6, "Comparing a6");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8E920" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_CreateItem, dll_base + 0x0005E920);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc* ppItem{};
				uint8_t* ppSection{};
				uint8_t pEnd{};
				
				return std::tuple{ pGame, pPlayer, ppItem, ppSection, pEnd };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_ppItem, moo_ppSection, moo_pEnd] = setup_data();
			auto [original_pGame, original_pPlayer, original_ppItem, original_ppSection, original_pEnd] = setup_data();
			uint32_t dwVersion{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppItem, &moo_ppSection, &moo_pEnd, dwVersion);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_ppItem, &original_ppSection, &original_pEnd, dwVersion);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_ppItem, original_ppItem, "Comparing ppItem");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
			SKIP_MOO_CHECK_EQ(moo_pEnd, original_pEnd, "Comparing pEnd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8EAB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_ReadIronGolemSection, dll_base + 0x0005EAB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				uint8_t* ppSection{};
				uint8_t pEnd{};
				
				return std::tuple{ pGame, pPlayer, ppSection, pEnd };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_ppSection, moo_pEnd] = setup_data();
			auto [original_pGame, original_pPlayer, original_ppSection, original_pEnd] = setup_data();
			uint32_t dwVersion{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &moo_pEnd, dwVersion);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &original_pEnd, dwVersion);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_ppSection, original_ppSection, "Comparing ppSection");
			SKIP_MOO_CHECK_EQ(moo_pEnd, original_pEnd, "Comparing pEnd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8EBA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_InitializeStats, dll_base + 0x0005EBA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nHitpoints{};
			int32_t nMana{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nHitpoints, nMana);
			original(&original_pGame, &original_pUnit, nHitpoints, nMana);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8EF20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_ProcessSaveFile, dll_base + 0x0005EF20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ClientStrc pClient{};
				uint8_t pSaveFile{};
				D2UnitStrc* ppPlayer{};
				D2ActiveRoomStrc pRoomArg{};
				
				return std::tuple{ pGame, pClient, pSaveFile, ppPlayer, pRoomArg };
			};
			
			// Input data
			auto [moo_pGame, moo_pClient, moo_pSaveFile, moo_ppPlayer, moo_pRoomArg] = setup_data();
			auto [original_pGame, original_pClient, original_pSaveFile, original_ppPlayer, original_pRoomArg] = setup_data();
			uint32_t nSize{};
			int32_t nXArg{};
			int32_t nYArg{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pClient, &moo_pSaveFile, nSize, &moo_ppPlayer, &moo_pRoomArg, nXArg, nYArg);
			const auto original_result = original(&original_pGame, &original_pClient, &original_pSaveFile, nSize, &original_ppPlayer, &original_pRoomArg, nXArg, nYArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pSaveFile, original_pSaveFile, "Comparing pSaveFile");
			SKIP_MOO_CHECK_EQ(moo_ppPlayer, original_ppPlayer, "Comparing ppPlayer");
			SKIP_MOO_CHECK_EQ(moo_pRoomArg, original_pRoomArg, "Comparing pRoomArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8F3A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE2_GetCharStatsTxtRecord, dll_base + 0x0005F3A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nClass{};

			// Call both implementations
			const auto moo_result = sut(nClass);
			const auto original_result = original(nClass);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
}
