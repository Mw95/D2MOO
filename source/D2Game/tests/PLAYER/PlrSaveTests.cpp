#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <PLAYER/PlrSave.h>
#include <Units/Units.h>


TEST_SUITE("PlrSaveTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC895D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_10036_PLRSAVE_EnableSaveFileWriting, dll_base + 0x000595D0);
		
		SUBCASE("")
		{
			int32_t bWriteSaveFile{};

			// Call both implementations
			sut(bWriteSaveFile);
			original(bWriteSaveFile);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC895E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC895E0, dll_base + 0x000595E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2SavedItemStrc moo_pSavedItem{};
			D2UnitStrc* moo_ppItem{};
			int32_t moo_a5{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2SavedItemStrc original_pSavedItem{};
			D2UnitStrc* original_ppItem{};
			int32_t original_a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2SavedItemStrc& pSavedItem,
				D2UnitStrc*& ppItem,
				int32_t& a5
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pSavedItem, moo_ppItem, moo_a5);
			setup_data(original_pGame, original_pPlayer, original_pSavedItem, original_ppItem, original_a5);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pSavedItem, &moo_ppItem, &moo_a5);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pSavedItem, &original_ppItem, &original_a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pSavedItem, original_pSavedItem, "Comparing pSavedItem");
			SKIP_MOO_CHECK_EQ(moo_ppItem, original_ppItem, "Comparing ppItem");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC897F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC897F0, dll_base + 0x000597F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2SavedItemStrc moo_pSavedItem{};
			D2GameStrc original_pGame{};
			D2SavedItemStrc original_pSavedItem{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2SavedItemStrc& pSavedItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pSavedItem);
			setup_data(original_pGame, original_pSavedItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pSavedItem);
			const auto original_result = original(&original_pGame, &original_pSavedItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pSavedItem, original_pSavedItem, "Comparing pSavedItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC898F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC898F0, dll_base + 0x000598F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_a4{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem,
				D2UnitStrc& a4
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pItem, moo_a4);
			setup_data(original_pGame, original_pPlayer, original_pItem, original_a4);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pItem, &moo_a4);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pItem, &original_a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC89AB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_10029_SAVE_WriteFileInterface, dll_base + 0x00059AB0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			char szName{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &szName);
			const auto original_result = original(&original_pGame, &original_pPlayer, &szName);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC89AD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SAVE_SerializeItem_6FC89AD0, dll_base + 0x00059AD0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			uint8_t moo_pBitstream{};
			D2UnitStrc original_pItem{};
			uint8_t original_pBitstream{};
			uint32_t nBitstreamSize{};
			int32_t n0{};
			int32_t a5{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				uint8_t& pBitstream
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pBitstream);
			setup_data(original_pItem, original_pBitstream);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pBitstream, nBitstreamSize, n0, a5);
			const auto original_result = original(&original_pItem, &original_pBitstream, nBitstreamSize, n0, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pBitstream, original_pBitstream, "Comparing pBitstream");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC89B50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE_WriteItems_6FC89B50, dll_base + 0x00059B50);
		
		SUBCASE("")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			uint8_t moo_pBitstream{};
			D2InventoryStrc original_pInventory{};
			uint8_t original_pBitstream{};
			uint32_t nBitstreamSize{};
			int32_t a4{};
			int32_t a5{};

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				uint8_t& pBitstream
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pInventory, moo_pBitstream);
			setup_data(original_pInventory, original_pBitstream);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pBitstream, nBitstreamSize, a4, a5);
			const auto original_result = original(&original_pInventory, &original_pBitstream, nBitstreamSize, a4, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			SKIP_MOO_CHECK_EQ(moo_pBitstream, original_pBitstream, "Comparing pBitstream");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8A0F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8A0F0, dll_base + 0x0005A0F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			uint8_t moo_pSection{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint8_t original_pSection{};
			int32_t nSize{};
			int32_t a5{};
			int32_t a6{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				uint8_t& pSection
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pSection);
			setup_data(original_pGame, original_pUnit, original_pSection);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pSection, nSize, a5, a6);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pSection, nSize, a5, a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSection, original_pSection, "Comparing pSection");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8A140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SAVE_CalculateChecksum_6FC8A140, dll_base + 0x0005A140);
		
		SUBCASE("")
		{
			// Input data
			D2SaveHeaderStrc moo_pSaveHeader{};
			D2SaveHeaderStrc original_pSaveHeader{};
			int32_t nSize{};

			const auto setup_data = [](
				D2SaveHeaderStrc& pSaveHeader
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSaveHeader);
			setup_data(original_pSaveHeader);

			// Call both implementations
			const auto moo_result = sut(&moo_pSaveHeader, nSize);
			const auto original_result = original(&original_pSaveHeader, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSaveHeader, original_pSaveHeader, "Comparing pSaveHeader");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8A1B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SAVE_WriteFileOnRealm_6FC8A1B0, dll_base + 0x0005A1B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			char moo_szAccountName{};
			D2ClientInfoStrc moo_pClientInfo{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			char original_szAccountName{};
			D2ClientInfoStrc original_pClientInfo{};
			char szCharName{};
			int32_t bInteractsWithPlayer{};
			int32_t nCharSaveTransactionToken{};
			int32_t a7{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				char& szAccountName,
				D2ClientInfoStrc& pClientInfo
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_szAccountName, moo_pClientInfo);
			setup_data(original_pGame, original_pPlayer, original_szAccountName, original_pClientInfo);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &szCharName, &moo_szAccountName, bInteractsWithPlayer, nCharSaveTransactionToken, a7, &moo_pClientInfo);
			const auto original_result = original(&original_pGame, &original_pPlayer, &szCharName, &original_szAccountName, bInteractsWithPlayer, nCharSaveTransactionToken, a7, &original_pClientInfo);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_szAccountName, original_szAccountName, "Comparing szAccountName");
			SKIP_MOO_CHECK_EQ(moo_pClientInfo, original_pClientInfo, "Comparing pClientInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8A500" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SAVE_WriteFile_6FC8A500, dll_base + 0x0005A500);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			char szName{};
			DWORD dwArg{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &szName, dwArg);
			const auto original_result = original(&original_pGame, &original_pPlayer, &szName, dwArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8A780" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8A780, dll_base + 0x0005A780);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			uint8_t moo_pSavefile{};
			D2UnitStrc* moo_ppPlayer{};
			int32_t moo_pValid{};
			int32_t moo_pVersion{};
			int32_t moo_a7{};
			int32_t moo_a8{};
			int32_t moo_a9{};
			int32_t moo_a10{};
			int32_t moo_a11{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};
			uint8_t original_pSavefile{};
			D2UnitStrc* original_ppPlayer{};
			int32_t original_pValid{};
			int32_t original_pVersion{};
			int32_t original_a7{};
			int32_t original_a8{};
			int32_t original_a9{};
			int32_t original_a10{};
			int32_t original_a11{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient,
				uint8_t& pSavefile,
				D2UnitStrc*& ppPlayer,
				int32_t& pValid,
				int32_t& pVersion,
				int32_t& a7,
				int32_t& a8,
				int32_t& a9,
				int32_t& a10,
				int32_t& a11
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient, moo_pSavefile, moo_ppPlayer, moo_pValid, moo_pVersion, moo_a7, moo_a8, moo_a9, moo_a10, moo_a11);
			setup_data(original_pGame, original_pClient, original_pSavefile, original_ppPlayer, original_pValid, original_pVersion, original_a7, original_a8, original_a9, original_a10, original_a11);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pClient, &moo_pSavefile, &moo_ppPlayer, &moo_pValid, &moo_pVersion, &moo_a7, &moo_a8, &moo_a9, &moo_a10, &moo_a11);
			const auto original_result = original(&original_pGame, &original_pClient, &original_pSavefile, &original_ppPlayer, &original_pValid, &original_pVersion, &original_a7, &original_a8, &original_a9, &original_a10, &original_a11);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pSavefile, original_pSavefile, "Comparing pSavefile");
			SKIP_MOO_CHECK_EQ(moo_ppPlayer, original_ppPlayer, "Comparing ppPlayer");
			SKIP_MOO_CHECK_EQ(moo_pValid, original_pValid, "Comparing pValid");
			SKIP_MOO_CHECK_EQ(moo_pVersion, original_pVersion, "Comparing pVersion");
			SKIP_MOO_CHECK_EQ(moo_a7, original_a7, "Comparing a7");
			SKIP_MOO_CHECK_EQ(moo_a8, original_a8, "Comparing a8");
			SKIP_MOO_CHECK_EQ(moo_a9, original_a9, "Comparing a9");
			SKIP_MOO_CHECK_EQ(moo_a10, original_a10, "Comparing a10");
			SKIP_MOO_CHECK_EQ(moo_a11, original_a11, "Comparing a11");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8AD50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SAVE_ReadWaypointData_6FC8AD50, dll_base + 0x0005AD50);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			uint8_t moo_pSection{};
			int32_t moo_pSize{};
			D2UnitStrc original_pUnit{};
			uint8_t original_pSection{};
			int32_t original_pSize{};
			int32_t nUnused{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				uint8_t& pSection,
				int32_t& pSize
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pSection, moo_pSize);
			setup_data(original_pUnit, original_pSection, original_pSize);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pSection, nUnused, &moo_pSize);
			const auto original_result = original(&original_pUnit, &original_pSection, nUnused, &original_pSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSection, original_pSection, "Comparing pSection");
			SKIP_MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8ADE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8ADE0, dll_base + 0x0005ADE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			uint8_t moo_pSection{};
			int32_t moo_pSize{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint8_t original_pSection{};
			int32_t original_pSize{};
			int32_t a4{};
			int32_t nUnused{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				uint8_t& pSection,
				int32_t& pSize
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pSection, moo_pSize);
			setup_data(original_pGame, original_pUnit, original_pSection, original_pSize);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pSection, a4, nUnused, &moo_pSize);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pSection, a4, nUnused, &original_pSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSection, original_pSection, "Comparing pSection");
			SKIP_MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8AEC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8AEC0, dll_base + 0x0005AEC0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			BYTE moo_pSection{};
			int32_t moo_pSkillCount{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			BYTE original_pSection{};
			int32_t original_pSkillCount{};
			int32_t a5{};
			int32_t a6{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				BYTE& pSection,
				int32_t& pSkillCount
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient, moo_pUnit, moo_pSection, moo_pSkillCount);
			setup_data(original_pGame, original_pClient, original_pUnit, original_pSection, original_pSkillCount);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pClient, &moo_pUnit, &moo_pSection, a5, a6, &moo_pSkillCount);
			const auto original_result = original(&original_pGame, &original_pClient, &original_pUnit, &original_pSection, a5, a6, &original_pSkillCount);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSection, original_pSection, "Comparing pSection");
			SKIP_MOO_CHECK_EQ(moo_pSkillCount, original_pSkillCount, "Comparing pSkillCount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8AF70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8AF70, dll_base + 0x0005AF70);
		
		SUBCASE("")
		{
			// Input data
			D2SavedItemStrc moo_pSavedItem{};
			uint8_t moo_pData{};
			D2SavedItemStrc original_pSavedItem{};
			uint8_t original_pData{};

			const auto setup_data = [](
				D2SavedItemStrc& pSavedItem,
				uint8_t& pData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSavedItem, moo_pData);
			setup_data(original_pSavedItem, original_pData);

			// Call both implementations
			const auto moo_result = sut(&moo_pSavedItem, &moo_pData);
			const auto original_result = original(&original_pSavedItem, &original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSavedItem, original_pSavedItem, "Comparing pSavedItem");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8B3D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8B3D0, dll_base + 0x0005B3D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			BYTE moo_pSection{};
			int32_t moo_pSize{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			BYTE original_pSection{};
			int32_t original_pSize{};
			uint32_t dwVersion{};
			int32_t nSize{};
			int32_t a6{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				BYTE& pSection,
				int32_t& pSize
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pSection, moo_pSize);
			setup_data(original_pGame, original_pPlayer, original_pSection, original_pSize);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pSection, dwVersion, nSize, a6, &moo_pSize);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pSection, dwVersion, nSize, a6, &original_pSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pSection, original_pSection, "Comparing pSection");
			SKIP_MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8B680" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8B680, dll_base + 0x0005B680);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2SavedItemStrc moo_pSavedItem{};
			D2UnitStrc* moo_ppItem{};
			int32_t moo_a5{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2SavedItemStrc original_pSavedItem{};
			D2UnitStrc* original_ppItem{};
			int32_t original_a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2SavedItemStrc& pSavedItem,
				D2UnitStrc*& ppItem,
				int32_t& a5
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pSavedItem, moo_ppItem, moo_a5);
			setup_data(original_pGame, original_pUnit, original_pSavedItem, original_ppItem, original_a5);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pSavedItem, &moo_ppItem, &moo_a5);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pSavedItem, &original_ppItem, &original_a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSavedItem, original_pSavedItem, "Comparing pSavedItem");
			SKIP_MOO_CHECK_EQ(moo_ppItem, original_ppItem, "Comparing ppItem");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8B8A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRSAVE_ReadItems_6FC8B8A0, dll_base + 0x0005B8A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			uint8_t moo_pSection{};
			int32_t moo_pSize{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint8_t original_pSection{};
			int32_t original_pSize{};
			uint32_t dwVersion{};
			int32_t nSize{};
			int32_t a6{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				uint8_t& pSection,
				int32_t& pSize
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pSection, moo_pSize);
			setup_data(original_pGame, original_pPlayer, original_pSection, original_pSize);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pSection, dwVersion, nSize, a6, &moo_pSize);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pSection, dwVersion, nSize, a6, &original_pSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pSection, original_pSection, "Comparing pSection");
			SKIP_MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8BAA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8BAA0, dll_base + 0x0005BAA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_a4{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem,
				D2UnitStrc& a4
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pItem, moo_a4);
			setup_data(original_pGame, original_pPlayer, original_pItem, original_a4);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pItem, &moo_a4);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pItem, &original_a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8BC70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8BC70, dll_base + 0x0005BC70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			uint8_t moo_pSection{};
			int32_t moo_pSize{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint8_t original_pSection{};
			int32_t original_pSize{};
			uint32_t dwVersion{};
			int32_t nSize{};
			int32_t a6{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				uint8_t& pSection,
				int32_t& pSize
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pSection, moo_pSize);
			setup_data(original_pGame, original_pUnit, original_pSection, original_pSize);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pSection, dwVersion, nSize, a6, &moo_pSize);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pSection, dwVersion, nSize, a6, &original_pSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSection, original_pSection, "Comparing pSection");
			SKIP_MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8BCC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8BCC0, dll_base + 0x0005BCC0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			uint8_t moo_pSection{};
			int32_t moo_pSize{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint8_t original_pSection{};
			int32_t original_pSize{};
			uint32_t dwVersion{};
			int32_t nRemainingSize{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				uint8_t& pSection,
				int32_t& pSize
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pSection, moo_pSize);
			setup_data(original_pGame, original_pPlayer, original_pSection, original_pSize);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pSection, dwVersion, nRemainingSize, &moo_pSize);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pSection, dwVersion, nRemainingSize, &original_pSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pSection, original_pSection, "Comparing pSection");
			SKIP_MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8BEE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8BEE0, dll_base + 0x0005BEE0);
		
		SUBCASE("")
		{
			int16_t nHirelingId{};
			int32_t nLevel{};

			// Call both implementations
			const auto moo_result = sut(nHirelingId, nLevel);
			const auto original_result = original(nHirelingId, nLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8C050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8C050, dll_base + 0x0005C050);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int16_t nHirelingId{};
			uint32_t a3{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nHirelingId, a3);
			const auto original_result = original(&original_pGame, nHirelingId, a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8C0C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SAVE_ProcessSaveFile_6FC8C0C0, dll_base + 0x0005C0C0);
		
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
			int32_t nSize{};
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8C890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC8C890, dll_base + 0x0005C890);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			D2UnitStrc* moo_ppPlayer{};
			D2ActiveRoomStrc moo_pRoomArg{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};
			D2UnitStrc* original_ppPlayer{};
			D2ActiveRoomStrc original_pRoomArg{};
			int32_t nXArg{};
			int32_t nYArg{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient,
				D2UnitStrc*& ppPlayer,
				D2ActiveRoomStrc& pRoomArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient, moo_ppPlayer, moo_pRoomArg);
			setup_data(original_pGame, original_pClient, original_ppPlayer, original_pRoomArg);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pClient, &moo_ppPlayer, &moo_pRoomArg, nXArg, nYArg);
			const auto original_result = original(&original_pGame, &original_pClient, &original_ppPlayer, &original_pRoomArg, nXArg, nYArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_ppPlayer, original_ppPlayer, "Comparing ppPlayer");
			SKIP_MOO_CHECK_EQ(moo_pRoomArg, original_pRoomArg, "Comparing pRoomArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8C9D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SAVE_ReadFile_6FC8C9D0, dll_base + 0x0005C9D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			D2UnitStrc* moo_ppPlayer{};
			D2ActiveRoomStrc moo_pRoomArg{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};
			D2UnitStrc* original_ppPlayer{};
			D2ActiveRoomStrc original_pRoomArg{};
			char szName{};
			int32_t nXArg{};
			int32_t nYArg{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient,
				D2UnitStrc*& ppPlayer,
				D2ActiveRoomStrc& pRoomArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient, moo_ppPlayer, moo_pRoomArg);
			setup_data(original_pGame, original_pClient, original_ppPlayer, original_pRoomArg);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pClient, &szName, &moo_ppPlayer, &moo_pRoomArg, nXArg, nYArg);
			const auto original_result = original(&original_pGame, &original_pClient, &szName, &original_ppPlayer, &original_pRoomArg, nXArg, nYArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_ppPlayer, original_ppPlayer, "Comparing ppPlayer");
			SKIP_MOO_CHECK_EQ(moo_pRoomArg, original_pRoomArg, "Comparing pRoomArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8CB40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SAVE_GetUnitDataFromFile_6FC8CB40, dll_base + 0x0005CB40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			D2UnitStrc* moo_ppPlayer{};
			D2ActiveRoomStrc moo_pRoomArg{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};
			D2UnitStrc* original_ppPlayer{};
			D2ActiveRoomStrc original_pRoomArg{};
			char szName{};
			int32_t a4{};
			int32_t nXArg{};
			int32_t nYArg{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient,
				D2UnitStrc*& ppPlayer,
				D2ActiveRoomStrc& pRoomArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient, moo_ppPlayer, moo_pRoomArg);
			setup_data(original_pGame, original_pClient, original_ppPlayer, original_pRoomArg);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pClient, &szName, a4, &moo_ppPlayer, &moo_pRoomArg, nXArg, nYArg);
			const auto original_result = original(&original_pGame, &original_pClient, &szName, a4, &original_ppPlayer, &original_pRoomArg, nXArg, nYArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_ppPlayer, original_ppPlayer, "Comparing ppPlayer");
			SKIP_MOO_CHECK_EQ(moo_pRoomArg, original_pRoomArg, "Comparing pRoomArg");
		}
	}
}
