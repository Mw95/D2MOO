#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <UNIT/SUnit.h>
#include <Units/Units.h>


TEST_SUITE("SUnitTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBAEE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_RemoveUnit, dll_base + 0x0008AEE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBB160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetNextUnitFromList, dll_base + 0x0008B160);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBB190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBB190, dll_base + 0x0008B190);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pRoom);
			setup_data(original_pGame, original_pUnit, original_pRoom);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pRoom);
			original(&original_pGame, &original_pUnit, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBB440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_WarpPlayer, dll_base + 0x0008B440);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pTarget{};
			D2UnitStrc moo_pRoomTile{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pTarget{};
			D2UnitStrc original_pRoomTile{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pTarget,
				D2UnitStrc& pRoomTile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pTarget, moo_pRoomTile);
			setup_data(original_pGame, original_pTarget, original_pRoomTile);

			// Call both implementations
			sut(&moo_pGame, &moo_pTarget, &moo_pRoomTile);
			original(&original_pGame, &original_pTarget, &original_pRoomTile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pRoomTile, original_pRoomTile, "Comparing pRoomTile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBB630" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_InitSeed, dll_base + 0x0008B630);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2SeedStrc moo_pSeed{};
			D2UnitStrc original_pUnit{};
			D2SeedStrc original_pSeed{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2SeedStrc& pSeed
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pSeed);
			setup_data(original_pUnit, original_pSeed);

			// Call both implementations
			sut(&moo_pUnit, &moo_pSeed);
			original(&original_pUnit, &original_pSeed);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBB6C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_AllocUnitData, dll_base + 0x0008B6C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nUnitType{};
			int32_t nClassId{};
			int32_t nX{};
			int32_t nY{};
			char a7{};
			int32_t nMode{};
			DWORD a3{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(nUnitType, nClassId, nX, nY, &moo_pGame, &moo_pRoom, a7, nMode, a3);
			const auto original_result = original(nUnitType, nClassId, nX, nY, &original_pGame, &original_pRoom, a7, nMode, a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBBB00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetServerUnit, dll_base + 0x0008BB00);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nUnitType{};
			int32_t nUnitGUID{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nUnitType, nUnitGUID);
			const auto original_result = original(&original_pGame, nUnitType, nUnitGUID);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBBB70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetOwner, dll_base + 0x0008BB70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBBC00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetLastAttacker, dll_base + 0x0008BC00);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBBCB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_Add, dll_base + 0x0008BCB0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nX{};
			int32_t nY{};
			int32_t a6{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pGame, moo_pRoom);
			setup_data(original_pUnit, original_pGame, original_pRoom);

			// Call both implementations
			sut(&moo_pUnit, nX, nY, &moo_pGame, &moo_pRoom, a6);
			original(&original_pUnit, nX, nY, &original_pGame, &original_pRoom, a6);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBBFE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_Restore, dll_base + 0x0008BFE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pRoom);
			setup_data(original_pGame, original_pUnit, original_pRoom);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pRoom, nX, nY);
			original(&original_pGame, &original_pUnit, &original_pRoom, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC280" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_InitClientInPlayerData, dll_base + 0x0008C280);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2ClientStrc moo_pClient{};
			D2UnitStrc original_pUnit{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pClient);
			setup_data(original_pUnit, original_pClient);

			// Call both implementations
			sut(&moo_pUnit, &moo_pClient);
			original(&original_pUnit, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC2E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetClientFromPlayer, dll_base + 0x0008C2E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pPlayer{};
			char szFile{};
			int32_t nLine{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer);
			setup_data(original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, &szFile, nLine);
			const auto original_result = original(&original_pPlayer, &szFile, nLine);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC300" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBC300, dll_base + 0x0008C300);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC480" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_AttachSound, dll_base + 0x0008C480);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pUpdateUnit{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pUpdateUnit{};
			int32_t nUpdateType{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pUpdateUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pUpdateUnit);
			setup_data(original_pUnit, original_pUpdateUnit);

			// Call both implementations
			sut(&moo_pUnit, nUpdateType, &moo_pUpdateUnit);
			original(&original_pUnit, nUpdateType, &original_pUpdateUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pUpdateUnit, original_pUpdateUnit, "Comparing pUpdateUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC4D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBC4D0, dll_base + 0x0008C4D0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC590" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_CreatePresetUnit, dll_base + 0x0008C590);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nUnitType{};
			int32_t nClassId{};
			int32_t nX{};
			int32_t nY{};
			int32_t nMode{};
			int32_t nUnitFlags{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nUnitType, nClassId, nX, nY, nMode, nUnitFlags);
			const auto original_result = original(&original_pGame, &original_pRoom, nUnitType, nClassId, nX, nY, nMode, nUnitFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC6F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_SpawnPresetUnit, dll_base + 0x0008C6F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2PresetUnitStrc moo_pPresetUnit{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2PresetUnitStrc original_pPresetUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2PresetUnitStrc& pPresetUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pPresetUnit);
			setup_data(original_pGame, original_pRoom, original_pPresetUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom, &moo_pPresetUnit);
			original(&original_pGame, &original_pRoom, &original_pPresetUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pPresetUnit, original_pPresetUnit, "Comparing pPresetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC780" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_SpawnPresetUnitsInRoom, dll_base + 0x0008C780);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom);
			original(&original_pGame, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC7E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBC7E0, dll_base + 0x0008C7E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC900" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetTargetUnit, dll_base + 0x0008C900);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBC930, dll_base + 0x0008C930);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMissile{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMissile{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pMissile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMissile);
			setup_data(original_pGame, original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC9A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_SetCombatMode, dll_base + 0x0008C9A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nMode);
			original(&original_pGame, &original_pUnit, nMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBC9C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBC9C0, dll_base + 0x0008C9C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pFirst{};
			D2UnitStrc moo_pSecond{};
			D2UnitStrc original_pFirst{};
			D2UnitStrc original_pSecond{};

			const auto setup_data = [](
				D2UnitStrc& pFirst,
				D2UnitStrc& pSecond
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pFirst, moo_pSecond);
			setup_data(original_pFirst, original_pSecond);

			// Call both implementations
			sut(&moo_pFirst, &moo_pSecond);
			original(&original_pFirst, &original_pSecond);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pFirst, original_pFirst, "Comparing pFirst");
			SKIP_MOO_CHECK_EQ(moo_pSecond, original_pSecond, "Comparing pSecond");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBCB30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetPortalOwner, dll_base + 0x0008CB30);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPortal{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPortal{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPortal
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPortal);
			setup_data(original_pGame, original_pPortal);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPortal);
			const auto original_result = original(&original_pGame, &original_pPortal);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPortal, original_pPortal, "Comparing pPortal");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBCC40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_IterateUnitsOfType, dll_base + 0x0008CC40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nType{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame, nType, moo_pArg, nullptr);
			original(&original_pGame, nType, original_pArg, nullptr);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBCD70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_IterateLivingPlayers, dll_base + 0x0008CD70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame, nullptr, moo_pArg);
			original(&original_pGame, nullptr, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBCE30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_SetTimerOnUnit, dll_base + 0x0008CE30);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2EventTimerStrc moo_pTimer{};
			D2UnitStrc original_pUnit{};
			D2EventTimerStrc original_pTimer{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2EventTimerStrc& pTimer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pTimer);
			setup_data(original_pUnit, original_pTimer);

			// Call both implementations
			sut(&moo_pUnit, &moo_pTimer);
			original(&original_pUnit, &original_pTimer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTimer, original_pTimer, "Comparing pTimer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBCE40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetTimerFromUnit, dll_base + 0x0008CE40);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBCE50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_DeletePlayerPerFrameEvents_6FCBCE50, dll_base + 0x0008CE50);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBCE70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBCE70, dll_base + 0x0008CE70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBCFD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBCFD0, dll_base + 0x0008CFD0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3);
			original(&original_pGame, &original_pUnit, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBD120, dll_base + 0x0008D120);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3);
			original(&original_pGame, &original_pUnit, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SKILLS_RewindSkillEx_6FCBD260, dll_base + 0x0008D260);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3);
			original(&original_pGame, &original_pUnit, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD3A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBD3A0, dll_base + 0x0008D3A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD3D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_FillUnitInfo, dll_base + 0x0008D3D0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitInfoStrc moo_pInfo{};
			D2UnitStrc original_pUnit{};
			D2UnitInfoStrc original_pInfo{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitInfoStrc& pInfo
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pInfo);
			setup_data(original_pUnit, original_pInfo);

			// Call both implementations
			sut(&moo_pUnit, &moo_pInfo);
			original(&original_pUnit, &original_pInfo);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pInfo, original_pInfo, "Comparing pInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD4D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetInteractUnit, dll_base + 0x0008D4D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_RemoveAllItemsFromInventory, dll_base + 0x0008D550);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD730" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetGameFromUnit, dll_base + 0x0008D730);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD760" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SetNecropetFlag_6FCBD760, dll_base + 0x0008D760);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nFlag{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nFlag);
			original(&original_pUnit, nFlag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD790" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_GetNecropetFlag_6FCBD790, dll_base + 0x0008D790);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD7C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SetSparkChest_6FCBD7C0, dll_base + 0x0008D7C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			uint8_t nSparkChest{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nSparkChest);
			original(&original_pUnit, nSparkChest);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD7F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_CheckIfSparklyChest_6FCBD7F0, dll_base + 0x0008D7F0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD820" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetInteractInfo, dll_base + 0x0008D820);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			int32_t moo_pInteractUnitType{};
			int32_t moo_pInteractUnitGUID{};
			D2UnitStrc original_pUnit{};
			int32_t original_pInteractUnitType{};
			int32_t original_pInteractUnitGUID{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				int32_t& pInteractUnitType,
				int32_t& pInteractUnitGUID
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pInteractUnitType, moo_pInteractUnitGUID);
			setup_data(original_pUnit, original_pInteractUnitType, original_pInteractUnitGUID);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pInteractUnitType, &moo_pInteractUnitGUID);
			const auto original_result = original(&original_pUnit, &original_pInteractUnitType, &original_pInteractUnitGUID);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pInteractUnitType, original_pInteractUnitType, "Comparing pInteractUnitType");
			SKIP_MOO_CHECK_EQ(moo_pInteractUnitGUID, original_pInteractUnitGUID, "Comparing pInteractUnitGUID");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_SetInteractInfo, dll_base + 0x0008D840);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nInteractUnitType{};
			int32_t nInteractUnitGUID{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nInteractUnitType, nInteractUnitGUID);
			original(&original_pUnit, nInteractUnitType, nInteractUnitGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_ResetInteractInfo, dll_base + 0x0008D890);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD8B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_IsDead, dll_base + 0x0008D8B0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBD900" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBD900, dll_base + 0x0008D900);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBDA10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetUnitList, dll_base + 0x0008DA10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nUnitType{};
			int32_t nUnitGUID{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			const auto moo_result = sut(nUnitType, &moo_pGame, nUnitGUID);
			const auto original_result = original(nUnitType, &original_pGame, nUnitGUID);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBDA40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_CanPetBeTargetedBySkill, dll_base + 0x0008DA40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pPet{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pPet{};
			int32_t nSkillId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pOwner,
				D2UnitStrc& pPet
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pOwner, moo_pPet);
			setup_data(original_pGame, original_pOwner, original_pPet);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pOwner, &moo_pPet, nSkillId);
			const auto original_result = original(&original_pGame, &original_pOwner, &original_pPet, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pPet, original_pPet, "Comparing pPet");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBDAD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_CanAllyBeTargetedBySkill, dll_base + 0x0008DAD0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pPet{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pPet{};
			int32_t nSkillId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pOwner,
				D2UnitStrc& pPet
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pOwner, moo_pPet);
			setup_data(original_pGame, original_pOwner, original_pPet);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pOwner, &moo_pPet, nSkillId);
			const auto original_result = original(&original_pGame, &original_pOwner, &original_pPet, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pPet, original_pPet, "Comparing pPet");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBDC60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_AreUnitsAligned, dll_base + 0x0008DC60);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit1, moo_pUnit);
			setup_data(original_pGame, original_pUnit1, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit1, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit1, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBDD30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBDD30, dll_base + 0x0008DD30);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			uint8_t nAlignNew{};
			int32_t a3{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nAlignNew, a3);
			original(&original_pUnit, nAlignNew, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBDE90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBDE90, dll_base + 0x0008DE90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t bSetUninterruptable{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, bSetUninterruptable);
			original(&original_pUnit, bSetUninterruptable);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBDF90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBDF90, dll_base + 0x0008DF90);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2C_EventTypes nEventType{};
			int32_t a4{};
			int32_t a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, nEventType, a4, a5);
			const auto original_result = original(&original_pGame, &original_pPlayer, nEventType, a4, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBDFE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBDFE0, dll_base + 0x0008DFE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc moo_pInputRoom{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc original_pInputRoom{};
			int32_t nX{};
			int32_t nY{};
			int32_t a6{};
			int32_t a7{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc& pInputRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pInputRoom);
			setup_data(original_pGame, original_pUnit, original_pInputRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pInputRoom, nX, nY, a6, a7);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pInputRoom, nX, nY, a6, a7);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pInputRoom, original_pInputRoom, "Comparing pInputRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBE2D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNIT_GetPartyId, dll_base + 0x0008E2D0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pPlayer{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer);
			setup_data(original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer);
			const auto original_result = original(&original_pPlayer);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
}
