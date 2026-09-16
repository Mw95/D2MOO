#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2SaveHeaderStrc moo_pMercData{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2SaveHeaderStrc original_pMercData{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2SaveHeaderStrc& pMercData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pMercData);
			setup_data(original_pGame, original_pPlayer, original_pMercData);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			uint8_t* moo_ppSection{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint8_t* original_ppSection{};
			uint8_t pEnd{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				uint8_t*& ppSection
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_ppSection);
			setup_data(original_pGame, original_pPlayer, original_ppSection);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &pEnd);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &pEnd);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			uint8_t* moo_ppSection{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint8_t* original_ppSection{};
			uint8_t pEnd{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				uint8_t*& ppSection
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_ppSection);
			setup_data(original_pGame, original_pUnit, original_ppSection);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_ppSection, &pEnd);
			auto original_result = original(&original_pGame, &original_pUnit, &original_ppSection, &pEnd);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			uint8_t* moo_ppSection{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint8_t* original_ppSection{};
			uint8_t pEnd{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				uint8_t*& ppSection
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_ppSection);
			setup_data(original_pGame, original_pUnit, original_ppSection);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_ppSection, &pEnd);
			auto original_result = original(&original_pGame, &original_pUnit, &original_ppSection, &pEnd);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			uint8_t* moo_ppSection{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint8_t* original_ppSection{};
			uint8_t pEnd{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				uint8_t*& ppSection
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_ppSection);
			setup_data(original_pGame, original_pPlayer, original_ppSection);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &pEnd);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &pEnd);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			uint8_t* moo_ppSection{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint8_t* original_ppSection{};
			uint8_t pEnd{};
			int32_t a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				uint8_t*& ppSection
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_ppSection);
			setup_data(original_pGame, original_pPlayer, original_ppSection);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &pEnd, a5);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &pEnd, a5);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			uint8_t* moo_ppSection{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint8_t* original_ppSection{};
			uint8_t pEnd{};
			int32_t a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				uint8_t*& ppSection
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_ppSection);
			setup_data(original_pGame, original_pPlayer, original_ppSection);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &pEnd, a5);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &pEnd, a5);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			uint8_t moo_pData{};
			uint32_t moo_pSize{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint8_t original_pData{};
			uint32_t original_pSize{};
			uint32_t nMaxSize{};
			int32_t a6{};
			int32_t a7{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				uint8_t& pData,
				uint32_t& pSize
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pData, moo_pSize);
			setup_data(original_pGame, original_pPlayer, original_pData, original_pSize);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pData, &moo_pSize, nMaxSize, a6, a7);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_pData, &original_pSize, nMaxSize, a6, a7);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			uint8_t* moo_ppSection{};
			uint8_t moo_pEnd{};
			D2UnitStrc* moo_ppPlayer{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};
			uint8_t* original_ppSection{};
			uint8_t original_pEnd{};
			D2UnitStrc* original_ppPlayer{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient,
				uint8_t*& ppSection,
				uint8_t& pEnd,
				D2UnitStrc*& ppPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient, moo_ppSection, moo_pEnd, moo_ppPlayer);
			setup_data(original_pGame, original_pClient, original_ppSection, original_pEnd, original_ppPlayer);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pClient, &moo_ppSection, &moo_pEnd, &moo_ppPlayer);
			auto original_result = original(&original_pGame, &original_pClient, &original_ppSection, &original_pEnd, &original_ppPlayer);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			uint8_t* moo_ppSection{};
			uint8_t moo_pEnd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint8_t* original_ppSection{};
			uint8_t original_pEnd{};
			int32_t nUnused{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				uint8_t*& ppSection,
				uint8_t& pEnd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_ppSection, moo_pEnd);
			setup_data(original_pGame, original_pUnit, original_ppSection, original_pEnd);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_ppSection, &moo_pEnd, nUnused);
			auto original_result = original(&original_pGame, &original_pUnit, &original_ppSection, &original_pEnd, nUnused);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			uint8_t* moo_ppSection{};
			uint8_t moo_pEnd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint8_t* original_ppSection{};
			uint8_t original_pEnd{};
			uint32_t nVersion{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				uint8_t*& ppSection,
				uint8_t& pEnd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_ppSection, moo_pEnd);
			setup_data(original_pGame, original_pUnit, original_ppSection, original_pEnd);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_ppSection, &moo_pEnd, nVersion);
			auto original_result = original(&original_pGame, &original_pUnit, &original_ppSection, &original_pEnd, nVersion);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			uint8_t* moo_ppSection{};
			uint8_t moo_pEnd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint8_t* original_ppSection{};
			uint8_t original_pEnd{};
			uint32_t nVersion{};
			int32_t nStats{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				uint8_t*& ppSection,
				uint8_t& pEnd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_ppSection, moo_pEnd);
			setup_data(original_pGame, original_pUnit, original_ppSection, original_pEnd);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_ppSection, &moo_pEnd, nVersion, nStats);
			auto original_result = original(&original_pGame, &original_pUnit, &original_ppSection, &original_pEnd, nVersion, nStats);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			uint8_t* moo_ppSection{};
			uint8_t moo_pEnd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint8_t* original_ppSection{};
			uint8_t original_pEnd{};
			uint32_t nVersion{};
			int32_t nSkills{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				uint8_t*& ppSection,
				uint8_t& pEnd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_ppSection, moo_pEnd);
			setup_data(original_pGame, original_pPlayer, original_ppSection, original_pEnd);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &moo_pEnd, nVersion, nSkills);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &original_pEnd, nVersion, nSkills);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			uint8_t* moo_ppSection{};
			uint8_t moo_pEnd{};
			int32_t moo_a6{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint8_t* original_ppSection{};
			uint8_t original_pEnd{};
			int32_t original_a6{};
			uint32_t nVersion{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				uint8_t*& ppSection,
				uint8_t& pEnd,
				int32_t& a6
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_ppSection, moo_pEnd, moo_a6);
			setup_data(original_pGame, original_pPlayer, original_ppSection, original_pEnd, original_a6);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &moo_pEnd, nVersion, &moo_a6);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &original_pEnd, nVersion, &original_a6);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2MercSaveDataStrc moo_pData{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2MercSaveDataStrc original_pData{};
			uint32_t dwVersion{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2MercSaveDataStrc& pData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pData);
			setup_data(original_pGame, original_pPlayer, original_pData);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pData, dwVersion);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_pData, dwVersion);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pMerc{};
			uint8_t* moo_ppSection{};
			uint8_t moo_pEnd{};
			int32_t moo_a6{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pMerc{};
			uint8_t* original_ppSection{};
			uint8_t original_pEnd{};
			int32_t original_a6{};
			uint32_t dwVersion{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pMerc,
				uint8_t*& ppSection,
				uint8_t& pEnd,
				int32_t& a6
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pMerc, moo_ppSection, moo_pEnd, moo_a6);
			setup_data(original_pGame, original_pPlayer, original_pMerc, original_ppSection, original_pEnd, original_a6);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pMerc, &moo_ppSection, &moo_pEnd, dwVersion, &moo_a6);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_pMerc, &original_ppSection, &original_pEnd, dwVersion, &original_a6);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc* moo_ppItem{};
			uint8_t* moo_ppSection{};
			uint8_t moo_pEnd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc* original_ppItem{};
			uint8_t* original_ppSection{};
			uint8_t original_pEnd{};
			uint32_t dwVersion{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc*& ppItem,
				uint8_t*& ppSection,
				uint8_t& pEnd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_ppItem, moo_ppSection, moo_pEnd);
			setup_data(original_pGame, original_pPlayer, original_ppItem, original_ppSection, original_pEnd);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppItem, &moo_ppSection, &moo_pEnd, dwVersion);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_ppItem, &original_ppSection, &original_pEnd, dwVersion);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			uint8_t* moo_ppSection{};
			uint8_t moo_pEnd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint8_t* original_ppSection{};
			uint8_t original_pEnd{};
			uint32_t dwVersion{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				uint8_t*& ppSection,
				uint8_t& pEnd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_ppSection, moo_pEnd);
			setup_data(original_pGame, original_pPlayer, original_ppSection, original_pEnd);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_ppSection, &moo_pEnd, dwVersion);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_ppSection, &original_pEnd, dwVersion);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nHitpoints{};
			int32_t nMana{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			uint8_t moo_pSaveFile{};
			D2UnitStrc* moo_ppPlayer{};
			D2ActiveRoomStrc moo_pRoomArg{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};
			uint8_t original_pSaveFile{};
			D2UnitStrc* original_ppPlayer{};
			D2ActiveRoomStrc original_pRoomArg{};
			uint32_t nSize{};
			int32_t nXArg{};
			int32_t nYArg{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient,
				uint8_t& pSaveFile,
				D2UnitStrc*& ppPlayer,
				D2ActiveRoomStrc& pRoomArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient, moo_pSaveFile, moo_ppPlayer, moo_pRoomArg);
			setup_data(original_pGame, original_pClient, original_pSaveFile, original_ppPlayer, original_pRoomArg);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pClient, &moo_pSaveFile, nSize, &moo_ppPlayer, &moo_pRoomArg, nXArg, nYArg);
			auto original_result = original(&original_pGame, &original_pClient, &original_pSaveFile, nSize, &original_ppPlayer, &original_pRoomArg, nXArg, nYArg);
			
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
			int32_t nClass{};

			// Call both implementations
			auto moo_result = sut(nClass);
			auto original_result = original(nClass);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
}
