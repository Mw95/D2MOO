#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <AI/AiGeneral.h>
#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Game.h>
#include <UNIT/SUnitInactive.h>
#include <Units/Units.h>


TEST_SUITE("SUnitInactiveTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC3850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_RestoreInactiveUnits, dll_base + 0x00093850);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pGame, pRoom };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom] = setup_data();
			auto [original_pGame, original_pRoom] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom);
			original(&original_pGame, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC40D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_GetAiControlFromUnit, dll_base + 0x000940D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC40F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_FreeInactiveMonsterNode, dll_base + 0x000940F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2InactiveMonsterNodeStrc pInactiveMonsterNode{};
				
				return std::tuple{ pGame, pInactiveMonsterNode };
			};
			
			// Input data
			auto [moo_pGame, moo_pInactiveMonsterNode] = setup_data();
			auto [original_pGame, original_pInactiveMonsterNode] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pInactiveMonsterNode);
			original(&original_pGame, &original_pInactiveMonsterNode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pInactiveMonsterNode, original_pInactiveMonsterNode, "Comparing pInactiveMonsterNode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC4120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_RestoreInactiveItem, dll_base + 0x00094120);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2InactiveItemNodeStrc pInactiveItemNode{};
				
				return std::tuple{ pGame, pRoom, pInactiveItemNode };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pInactiveItemNode] = setup_data();
			auto [original_pGame, original_pRoom, original_pInactiveItemNode] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pInactiveItemNode);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pInactiveItemNode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pInactiveItemNode, original_pInactiveItemNode, "Comparing pInactiveItemNode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC4270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_FreeInactiveUnitLists, dll_base + 0x00094270);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();

			// Call both implementations
			sut(&moo_pGame);
			original(&original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC4370" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_CompressUnitIfNeeded, dll_base + 0x00094370);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC4650" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_CompressInactiveUnit, dll_base + 0x00094650);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC4C90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_DeleteSingleListNode, dll_base + 0x00094C90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();
			uint16_t nUnitType{};
			uint16_t nClassId{};
			uint8_t nAct{};

			// Call both implementations
			sut(&moo_pGame, nUnitType, nClassId, nAct);
			original(&original_pGame, nUnitType, nClassId, nAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC4DC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_GetListNodeFromActAndCoordinates, dll_base + 0x00094DC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();
			int32_t nAct{};
			int32_t nX{};
			int32_t nY{};
			int32_t bAllocNewNode{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nAct, nX, nY, bAllocNewNode);
			const auto original_result = original(&original_pGame, nAct, nX, nY, bAllocNewNode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC4E80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_GetListNodeFromRoom, dll_base + 0x00094E80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pGame, pRoom };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom] = setup_data();
			auto [original_pGame, original_pRoom] = setup_data();
			int32_t bAllocNewNode{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, bAllocNewNode);
			const auto original_result = original(&original_pGame, &original_pRoom, bAllocNewNode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC4ED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_RestoreSpecialMonsterParameters, dll_base + 0x00094ED0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2InactiveMonsterNodeStrc pInactiveMonsterNode{};
				
				return std::tuple{ pGame, pUnit, pInactiveMonsterNode };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pInactiveMonsterNode] = setup_data();
			auto [original_pGame, original_pUnit, original_pInactiveMonsterNode] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pInactiveMonsterNode);
			original(&original_pGame, &original_pUnit, &original_pInactiveMonsterNode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pInactiveMonsterNode, original_pInactiveMonsterNode, "Comparing pInactiveMonsterNode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC50B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_SaveSpecialMonsterParameters, dll_base + 0x000950B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2InactiveMonsterNodeStrc pInactiveMonsterNode{};
				
				return std::tuple{ pGame, pUnit, pInactiveMonsterNode };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pInactiveMonsterNode] = setup_data();
			auto [original_pGame, original_pUnit, original_pInactiveMonsterNode] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pInactiveMonsterNode);
			original(&original_pGame, &original_pUnit, &original_pInactiveMonsterNode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pInactiveMonsterNode, original_pInactiveMonsterNode, "Comparing pInactiveMonsterNode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC52C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_IsUnitInsideRoom, dll_base + 0x000952C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoomNear{};
				
				return std::tuple{ pGame, pRoomNear };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoomNear] = setup_data();
			auto [original_pGame, original_pRoomNear] = setup_data();
			int32_t nGameX{};
			int32_t nGameY{};
			int32_t nClassId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoomNear, nGameX, nGameY, nClassId);
			const auto original_result = original(&original_pGame, &original_pRoomNear, nGameX, nGameY, nClassId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoomNear, original_pRoomNear, "Comparing pRoomNear");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC5490" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_DeleteExpiredItemNodes, dll_base + 0x00095490);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();
			int32_t nAct{};

			// Call both implementations
			sut(&moo_pGame, nAct);
			original(&original_pGame, nAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC54F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITINACTIVE_SetUnitFlagEx, dll_base + 0x000954F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();
			uint32_t nFlag{};
			int32_t bSet{};

			// Call both implementations
			sut(&moo_pUnit, nFlag, bSet);
			original(&original_pUnit, nFlag, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
