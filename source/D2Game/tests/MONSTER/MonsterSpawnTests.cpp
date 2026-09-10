#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Game.h>
#include <MONSTER/MonsterSpawn.h>
#include <Units/Units.h>


TEST_SUITE("MonsterSpawnTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC68350" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC68350, dll_base + 0x00038350);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int32_t nMonsterId{};
			int32_t nX{};
			int32_t nY{};
			int32_t a5{};

			// Call both implementations
			const auto moo_result = sut(nMonsterId, &moo_pRoom, nX, nY, a5);
			const auto original_result = original(nMonsterId, &original_pRoom, nX, nY, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC68630" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC68630, dll_base + 0x00038630);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pTarget] = setup_data();
			int32_t nSkillId{};
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, &moo_pTarget, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, &original_pTarget, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC68CC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERSPAWN_GetResurrectMode, dll_base + 0x00038CC0);
		
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
			int32_t a2{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, a2);
			const auto original_result = original(&original_pUnit, a2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC68D70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC68D70, dll_base + 0x00038D70);
		
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
			int32_t nMonsterId{};
			int32_t nAnimMode{};
			int32_t a5{};
			int16_t nFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nMonsterId, nAnimMode, a5, nFlags);
			const auto original_result = original(&original_pGame, &original_pUnit, nMonsterId, nAnimMode, a5, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC68E30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SpawnNormalMonster_6FC68E30, dll_base + 0x00038E30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnkMonCreateStrc pMonCreate{};
				
				return std::tuple{ pMonCreate };
			};
			
			// Input data
			auto [moo_pMonCreate] = setup_data();
			auto [original_pMonCreate] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonCreate);
			const auto original_result = original(&original_pMonCreate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonCreate, original_pMonCreate, "Comparing pMonCreate");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC69B60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERSPAWN_EquipAncientBarbarians, dll_base + 0x00039B60);
		
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
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC69C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC69C00, dll_base + 0x00039C00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnkMonCreateStrc pMonCreate{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pMonCreate, pUnit };
			};
			
			// Input data
			auto [moo_pMonCreate, moo_pUnit] = setup_data();
			auto [original_pMonCreate, original_pUnit] = setup_data();

			// Call both implementations
			sut(&moo_pMonCreate, &moo_pUnit);
			original(&original_pMonCreate, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonCreate, original_pMonCreate, "Comparing pMonCreate");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC69F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SpawnMonster_6FC69F10, dll_base + 0x00039F10);
		
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
			int32_t nX{};
			int32_t nY{};
			int32_t nMonsterId{};
			int32_t nAnimMode{};
			int32_t a7{};
			int16_t nFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nX, nY, nMonsterId, nAnimMode, a7, nFlags);
			const auto original_result = original(&original_pGame, &original_pRoom, nX, nY, nMonsterId, nAnimMode, a7, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC69F70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC69F70, dll_base + 0x00039F70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2RoomCoordListStrc pRoomCoordList{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pRoomCoordList, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoomCoordList, moo_pUnit] = setup_data();
			auto [original_pGame, original_pRoomCoordList, original_pUnit] = setup_data();
			int32_t nMonsterId{};
			int32_t nAnimMode{};
			int32_t a6{};
			int16_t nFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoomCoordList, &moo_pUnit, nMonsterId, nAnimMode, a6, nFlags);
			const auto original_result = original(&original_pGame, &original_pRoomCoordList, &original_pUnit, nMonsterId, nAnimMode, a6, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoomCoordList, original_pRoomCoordList, "Comparing pRoomCoordList");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6A030" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6A030, dll_base + 0x0003A030);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2RoomCoordListStrc pRoomCoordList{};
				
				return std::tuple{ pGame, pRoom, pRoomCoordList };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pRoomCoordList] = setup_data();
			auto [original_pGame, original_pRoom, original_pRoomCoordList] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nMonsterId{};
			int32_t nAnimMode{};
			int32_t a8{};
			int16_t nFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pRoomCoordList, nX, nY, nMonsterId, nAnimMode, a8, nFlags);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pRoomCoordList, nX, nY, nMonsterId, nAnimMode, a8, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pRoomCoordList, original_pRoomCoordList, "Comparing pRoomCoordList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6A090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6A090, dll_base + 0x0003A090);
		
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
			int32_t nX{};
			int32_t nY{};
			int32_t nMonsterId{};
			int32_t nAnimMode{};
			int16_t nFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nX, nY, nMonsterId, nAnimMode, nFlags);
			const auto original_result = original(&original_pGame, &original_pRoom, nX, nY, nMonsterId, nAnimMode, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6A0F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6A0F0, dll_base + 0x0003A0F0);
		
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
			int32_t nX{};
			int32_t nY{};
			int32_t nMonsterId{};
			int32_t nMode{};
			int32_t nUnitId{};
			int32_t a8{};
			int16_t nFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nX, nY, nMonsterId, nMode, nUnitId, a8, nFlags);
			const auto original_result = original(&original_pGame, &original_pRoom, nX, nY, nMonsterId, nMode, nUnitId, a8, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6A150" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6A150, dll_base + 0x0003A150);
		
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
			int32_t nMonsterId{};
			int32_t nAnimMode{};
			int32_t a5{};
			int16_t nFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nMonsterId, nAnimMode, a5, nFlags);
			const auto original_result = original(&original_pGame, &original_pUnit, nMonsterId, nAnimMode, a5, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6A230" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6A230, dll_base + 0x0003A230);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pOwner{};
				
				return std::tuple{ pGame, pOwner };
			};
			
			// Input data
			auto [moo_pGame, moo_pOwner] = setup_data();
			auto [original_pGame, original_pOwner] = setup_data();
			int32_t nMonsterId{};
			int32_t nAnimMode{};
			int32_t a5{};
			int32_t nCount{};
			int16_t nFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pOwner, nMonsterId, nAnimMode, a5, nCount, nFlags);
			const auto original_result = original(&original_pGame, &original_pOwner, nMonsterId, nAnimMode, a5, nCount, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6A350" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6A350, dll_base + 0x0003A350);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2UnitStrc pOwner{};
				D2UnkMonCreateStrc2 a8{};
				
				return std::tuple{ pGame, pRoom, pOwner, a8 };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pOwner, moo_a8] = setup_data();
			auto [original_pGame, original_pRoom, original_pOwner, original_a8] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nClassId{};
			int32_t nAnimMode{};
			int16_t nFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nX, nY, &moo_pOwner, nClassId, nAnimMode, &moo_a8, nFlags);
			const auto original_result = original(&original_pGame, &original_pRoom, nX, nY, &original_pOwner, nClassId, nAnimMode, &original_a8, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_a8, original_a8, "Comparing a8");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6A810" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6A810, dll_base + 0x0003A810);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2UnitStrc pTargetUnit{};
				
				return std::tuple{ pGame, pRoom, pTargetUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pTargetUnit] = setup_data();
			auto [original_pGame, original_pRoom, original_pTargetUnit] = setup_data();
			int32_t a3{};
			int32_t a4{};
			int32_t a6{};
			int16_t a7{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, a3, a4, &moo_pTargetUnit, a6, a7);
			const auto original_result = original(&original_pGame, &original_pRoom, a3, a4, &original_pTargetUnit, a6, a7);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6A8C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6A8C0, dll_base + 0x0003A8C0);
		
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
			int32_t nMonsterId{};
			int32_t nAnimMode{};
			int32_t nCount{};
			int32_t a6{};
			int16_t nFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nMonsterId, nAnimMode, nCount, a6, nFlags);
			const auto original_result = original(&original_pGame, &original_pUnit, nMonsterId, nAnimMode, nCount, a6, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6AA70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERSPAWN_SpawnRandomMonsterForLevel, dll_base + 0x0003AA70);
		
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
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nX, nY);
			const auto original_result = original(&original_pGame, &original_pRoom, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
}
