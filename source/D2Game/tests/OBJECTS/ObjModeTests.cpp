#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2StatList.h>
#include <DataTbls/ObjectsTbls.h>
#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <OBJECTS/ObjMode.h>
#include <Units/Units.h>


TEST_SUITE("ObjModeTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC748A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC748A0, dll_base + 0x000448A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC74A40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC74A40, dll_base + 0x00044A40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC74AC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC74AC0, dll_base + 0x00044AC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC74B00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC74B00, dll_base + 0x00044B00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC74B40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC74B40, dll_base + 0x00044B40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC74CA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC74CA0, dll_base + 0x00044CA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC74D10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC74D10, dll_base + 0x00044D10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC74DF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC74DF0, dll_base + 0x00044DF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC74F60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SpikeTraps_6FC74F60, dll_base + 0x00044F60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC750D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC750D0, dll_base + 0x000450D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75250" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_OBJMODE_InvokeEventFunction_6FC75250, dll_base + 0x00045250);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();
			int32_t nEventType{};

			// Call both implementations
			sut(&moo_pGame, &moo_pObject, nEventType);
			original(&original_pGame, &original_pObject, nEventType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC752A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC752A0, dll_base + 0x000452A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pUnit, pClient };
			};
			
			// Input data
			auto [moo_pUnit, moo_pClient] = setup_data();
			auto [original_pUnit, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pUnit, &moo_pClient);
			original(&original_pUnit, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75350" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC75350, dll_base + 0x00045350);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pUnit, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pClient] = setup_data();
			auto [original_pGame, original_pUnit, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pClient);
			original(&original_pGame, &original_pUnit, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC753E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction27_TeleportPad, dll_base + 0x000453E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75530" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction30_ExplodingChest, dll_base + 0x00045530);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC755A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction08_Door, dll_base + 0x000455A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75730" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction16_TrapDoor, dll_base + 0x00045730);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC757E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction47_Stair, dll_base + 0x000457E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC758F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction61_HarrogathMainGate, dll_base + 0x000458F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC759F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction50_Stair, dll_base + 0x000459F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75A10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction29_SlimeDoor, dll_base + 0x00045A10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75AC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_OBJECTS_TrapHandler8_9_6FC75AC0, dll_base + 0x00045AC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75B40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SpawnTrapMonster_6FC75B40, dll_base + 0x00045B40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nMonsterId{};
			int32_t a3{};

			// Call both implementations
			sut(&moo_pOp, nMonsterId, a3);
			original(&original_pOp, nMonsterId, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75BC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_OBJECTS_TrapHandler5_7_6FC75BC0, dll_base + 0x00045BC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75C70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_OBJECTS_TrapHandler1_6FC75C70, dll_base + 0x00045C70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75D00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_OBJECTS_TrapHandler2_6_6FC75D00, dll_base + 0x00045D00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75D90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_OBJECTS_TrapHandler3_6FC75D90, dll_base + 0x00045D90);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_OBJECTS_TrapHandler4_6FC75E20, dll_base + 0x00045E20);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC75EB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC75EB0, dll_base + 0x00045EB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76030" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction04_Chest, dll_base + 0x00046030);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC764B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SetTrapCallback_6FC764B0, dll_base + 0x000464B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			uint8_t nTrapType{};

			// Call both implementations
			sut(&moo_pOp, nTrapType);
			original(&original_pOp, nTrapType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction17_Obelisk, dll_base + 0x00046570);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC766B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_Health_6FC766B0, dll_base + 0x000466B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC766F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_FillMana_6FC766F0, dll_base + 0x000466F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76730" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_Refill_6FC76730, dll_base + 0x00046730);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76790" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_ExchangeHealth_6FC76790, dll_base + 0x00046790);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC767F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_ExchangeMana_6FC767F0, dll_base + 0x000467F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_Enirhs_6FC76850, dll_base + 0x00046850);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76880" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_Portal_6FC76880, dll_base + 0x00046880);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_Gem_6FC76910, dll_base + 0x00046910);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76A60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC76A60, dll_base + 0x00046A60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pGame, pPlayer, pItem };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pItem] = setup_data();
			auto [original_pGame, original_pPlayer, original_pItem] = setup_data();
			int32_t nItemId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, nItemId, &moo_pItem);
			const auto original_result = original(&original_pGame, &original_pPlayer, nItemId, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76BC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_Storm_6FC76BC0, dll_base + 0x00046BC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76E90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC76E90, dll_base + 0x00046E90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitFindArgStrc pArg{};
				
				return std::tuple{ pUnit, pArg };
			};
			
			// Input data
			auto [moo_pUnit, moo_pArg] = setup_data();
			auto [original_pUnit, original_pArg] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pArg);
			const auto original_result = original(&original_pUnit, &original_pArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76ED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_Monster_6FC76ED0, dll_base + 0x00046ED0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC76F60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC76F60, dll_base + 0x00046F60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				D2UnitStrc pUnit1{};
				
				return std::tuple{ pMonster, pUnit1 };
			};
			
			// Input data
			auto [moo_pMonster, moo_pUnit1] = setup_data();
			auto [original_pMonster, original_pUnit1] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonster, &moo_pUnit1);
			const auto original_result = original(&original_pMonster, &original_pUnit1);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC770D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_Exploding_6FC770D0, dll_base + 0x000470D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC773B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_Poison_6FC773B0, dll_base + 0x000473B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC77690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_CombatBoost_6FC77690, dll_base + 0x00047690);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC77750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC77750, dll_base + 0x00047750);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ShrinesTxt pShrinesTxtRecord{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pShrinesTxtRecord, pUnit };
			};
			
			// Input data
			auto [moo_pShrinesTxtRecord, moo_pUnit] = setup_data();
			auto [original_pShrinesTxtRecord, original_pUnit] = setup_data();
			int32_t nStatId{};
			int32_t nValue{};

			// Call both implementations
			const auto moo_result = sut(&moo_pShrinesTxtRecord, nStatId, nValue, &moo_pUnit);
			const auto original_result = original(&original_pShrinesTxtRecord, nStatId, nValue, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC779C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_Stamina_6FC779C0, dll_base + 0x000479C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC77AB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC77AB0, dll_base + 0x00047AB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				struct D2StatListStrc pStatList{};
				
				return std::tuple{ pUnit, pStatList };
			};
			
			// Input data
			auto [moo_pUnit, moo_pStatList] = setup_data();
			auto [original_pUnit, original_pStatList] = setup_data();
			int32_t nState{};

			// Call both implementations
			sut(&moo_pUnit, nState, &moo_pStatList);
			original(&original_pUnit, nState, &original_pStatList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC77AE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_DefensiveBoost_6FC77AE0, dll_base + 0x00047AE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC77BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SHRINES_SkillBoost_6FC77BA0, dll_base + 0x00047BA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				D2ShrinesTxt pShrinesTxtRecord{};
				
				return std::tuple{ pOp, pShrinesTxtRecord };
			};
			
			// Input data
			auto [moo_pOp, moo_pShrinesTxtRecord] = setup_data();
			auto [original_pOp, original_pShrinesTxtRecord] = setup_data();

			// Call both implementations
			sut(&moo_pOp, &moo_pShrinesTxtRecord);
			original(&original_pOp, &original_pShrinesTxtRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
			SKIP_MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC77C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC77C10, dll_base + 0x00047C10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				struct D2StatListStrc pStatList{};
				
				return std::tuple{ pUnit, pStatList };
			};
			
			// Input data
			auto [moo_pUnit, moo_pStatList] = setup_data();
			auto [original_pUnit, original_pStatList] = setup_data();
			int32_t nState{};

			// Call both implementations
			sut(&moo_pUnit, nState, &moo_pStatList);
			original(&original_pUnit, nState, &original_pStatList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC77C30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction02_Shrine, dll_base + 0x00047C30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC77E80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction01_Casket, dll_base + 0x00047E80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC77F70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction68_EvilUrn, dll_base + 0x00047F70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction33_WirtsBody, dll_base + 0x00048120);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC781C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction03_Urn_Basket_Jar, dll_base + 0x000481C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78290" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction14_Corpse, dll_base + 0x00048290);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC78340, dll_base + 0x00048340);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78390" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction51_JungleStash, dll_base + 0x00048390);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78470" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction18_SecretDoor, dll_base + 0x00048470);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC784E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction26_BookShelf, dll_base + 0x000484E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC785D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction19_ArmorStand, dll_base + 0x000485D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78640" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction20_WeaponRack, dll_base + 0x00048640);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC786B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction05_Barrel, dll_base + 0x000486B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC787F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction07_ExplodingBarrel, dll_base + 0x000487F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction13_TorchTiki, dll_base + 0x00048940);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78970" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction11_Torch, dll_base + 0x00048970);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC789C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateHandler, dll_base + 0x000489C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				int32_t pResult{};
				
				return std::tuple{ pGame, pPlayer, pResult };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pResult] = setup_data();
			auto [original_pGame, original_pPlayer, original_pResult] = setup_data();
			int32_t nObjectType{};
			int32_t nObjectGUID{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, nObjectType, nObjectGUID, &moo_pResult);
			const auto original_result = original(&original_pGame, &original_pPlayer, nObjectType, nObjectGUID, &original_pResult);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pResult, original_pResult, "Comparing pResult");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78B20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC78B20, dll_base + 0x00048B20);
		
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
			int32_t nObjectType{};
			int32_t nObjectGUID{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nObjectType, nObjectGUID);
			const auto original_result = original(&original_pGame, &original_pUnit, nObjectType, nObjectGUID);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78BB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC78BB0, dll_base + 0x00048BB0);
		
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
			int32_t nUnused{};
			int32_t nObjectGUID{};

			// Call both implementations
			sut(&moo_pGame, nUnused, nObjectGUID);
			original(&original_pGame, nUnused, nObjectGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78C90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction34_ArcaneSanctuaryPortal, dll_base + 0x00048C90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78D30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction46_HellGatePortal, dll_base + 0x00048D30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC78E00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction15_Portal, dll_base + 0x00048E00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC79310" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction43_DurielPortal, dll_base + 0x00049310);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC79490" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction23_Waypoint, dll_base + 0x00049490);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC79600" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_WAYPOINT_Unk_6FC79600, dll_base + 0x00049600);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pGame, pPlayer };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer] = setup_data();
			auto [original_pGame, original_pPlayer] = setup_data();
			int32_t nWaypointGUID{};
			int32_t nLevelId{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nWaypointGUID, nLevelId);
			original(&original_pGame, &original_pPlayer, nWaypointGUID, nLevelId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC797A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJMODE_ObeliskPowerUp_IncreaseMana, dll_base + 0x000497A0);
		
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
			int32_t nValue{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nValue);
			const auto original_result = original(&original_pGame, &original_pUnit, nValue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC797E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJMODE_ObeliskPowerUp_IncreaseEnergy, dll_base + 0x000497E0);
		
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
			int32_t nValue{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nValue);
			const auto original_result = original(&original_pGame, &original_pUnit, nValue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC79800" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJMODE_ObeliskPowerUp_IncreaseDexterity, dll_base + 0x00049800);
		
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
			int32_t nValue{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nValue);
			const auto original_result = original(&original_pGame, &original_pUnit, nValue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC79820" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJMODE_ObeliskPowerUp_IncreaseVitality, dll_base + 0x00049820);
		
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
			int32_t nValue{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nValue);
			const auto original_result = original(&original_pGame, &original_pUnit, nValue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC79840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJMODE_ObeliskPowerUp_IncreaseStrength, dll_base + 0x00049840);
		
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
			int32_t nValue{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nValue);
			const auto original_result = original(&original_pGame, &original_pUnit, nValue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC79860" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJMODE_ObeliskPowerUp_IncreaseHitpoints, dll_base + 0x00049860);
		
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
			int32_t nValue{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nValue);
			const auto original_result = original(&original_pGame, &original_pUnit, nValue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC798A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJMODE_ObeliskPowerUp_IncreaseSkillpoints, dll_base + 0x000498A0);
		
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
			int32_t nValue{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nValue);
			const auto original_result = original(&original_pGame, &original_pUnit, nValue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC798C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJMODE_MainObeliskHandler, dll_base + 0x000498C0);
		
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
			int32_t nPlayerGUID{};
			int32_t nObjectGUID{};
			int32_t nItemGUID{};
			int16_t nState{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nPlayerGUID, nObjectGUID, nItemGUID, nState);
			const auto original_result = original(&original_pGame, nPlayerGUID, nObjectGUID, nItemGUID, nState);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC79B50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC79B50, dll_base + 0x00049B50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pUnit, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pObject] = setup_data();
			auto [original_pGame, original_pUnit, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pObject);
			original(&original_pGame, &original_pUnit, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC79C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC79C00, dll_base + 0x00049C00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pObject{};
				
				return std::tuple{ pGame, pObject };
			};
			
			// Input data
			auto [moo_pGame, moo_pObject] = setup_data();
			auto [original_pGame, original_pObject] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC79C30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC79C30, dll_base + 0x00049C30);
		
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
			int32_t nUnused{};
			int32_t nPortalGUID{};
			int32_t nDestLevel{};

			// Call both implementations
			sut(&moo_pGame, nUnused, nPortalGUID, nDestLevel);
			original(&original_pGame, nUnused, nPortalGUID, nDestLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC79D90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction22_Well, dll_base + 0x00049D90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7A000" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJMODE_PetIterate_Heal, dll_base + 0x0004A000);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pUnit2{};
				
				return std::tuple{ pGame, pUnit, pUnit2 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pUnit2] = setup_data();
			auto [original_pGame, original_pUnit, original_pUnit2] = setup_data();
			void* moo_pUnitHealed = nullptr;
			void* original_pUnitHealed = nullptr;

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pUnit2, moo_pUnitHealed);
			original(&original_pGame, &original_pUnit, &original_pUnit2, original_pUnitHealed);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
			SKIP_MOO_CHECK_EQ(moo_pUnitHealed, original_pUnitHealed, "Comparing pUnitHealed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7A070" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction48_TrappedSoul, dll_base + 0x0004A070);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7A140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJMODE_DropItemWithCodeAndQuality, dll_base + 0x0004A140);
		
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
			uint32_t dwCode{};
			int32_t nItemQuality{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, dwCode, nItemQuality);
			const auto original_result = original(&original_pGame, &original_pUnit, dwCode, nItemQuality);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7A220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJMODE_DropFromChestTCWithQuality, dll_base + 0x0004A220);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nItemQuality{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nItemQuality);
			const auto original_result = original(&original_pOp, nItemQuality);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
}
