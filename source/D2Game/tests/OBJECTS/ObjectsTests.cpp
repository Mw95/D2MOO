#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Game.h>
#include <OBJECTS/Objects.h>
#include <Units/Units.h>


TEST_SUITE("ObjectsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70180" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnShrine, dll_base + 0x00040180);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nClassId{};
			int32_t nX{};
			int32_t nY{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nClassId, nX, nY, nMode);
			const auto original_result = original(&original_pGame, &original_pRoom, nClassId, nX, nY, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnPresetChest, dll_base + 0x00040270);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nClassId{};
			int32_t nX{};
			int32_t nY{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nClassId, nX, nY, nMode);
			const auto original_result = original(&original_pGame, &original_pRoom, nClassId, nX, nY, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70470" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnSpecialChest, dll_base + 0x00040470);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nClassId{};
			int32_t nX{};
			int32_t nY{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nClassId, nX, nY, nMode);
			const auto original_result = original(&original_pGame, &original_pRoom, nClassId, nX, nY, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnArcaneSymbol, dll_base + 0x00040520);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nClassId{};
			int32_t nX{};
			int32_t nY{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nClassId, nX, nY, nMode);
			const auto original_result = original(&original_pGame, &original_pRoom, nClassId, nX, nY, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnPresetObject, dll_base + 0x00040570);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nClassId{};
			int32_t nX{};
			int32_t nY{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nClassId, nX, nY, nMode);
			const auto original_result = original(&original_pGame, &original_pRoom, nClassId, nX, nY, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70600" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitHandler, dll_base + 0x00040600);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pObject{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pObject{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nUnitId{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pObject,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pObject, moo_pRoom);
			setup_data(original_pGame, original_pObject, original_pRoom);

			// Call both implementations
			sut(&moo_pGame, &moo_pObject, nUnitId, &moo_pRoom, nX, nY);
			original(&original_pGame, &original_pObject, nUnitId, &original_pRoom, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction10_Unused, dll_base + 0x00040850);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC708B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction28_GoldPlaceHolder, dll_base + 0x000408B0);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70A50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction01_Shrine, dll_base + 0x00040A50);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_GetShrineId, dll_base + 0x00040BA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			uint8_t nShrineClass{};
			int32_t nLevelId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nShrineClass, nLevelId, &moo_pRoom);
			const auto original_result = original(&original_pGame, nShrineClass, nLevelId, &original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70CA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction22_Fire, dll_base + 0x00040CA0);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70CF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction16_Well, dll_base + 0x00040CF0);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70D10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction24_SpikeFloorTrap, dll_base + 0x00040D10);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70D30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction02_Urn, dll_base + 0x00040D30);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70DC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction27_GooPile, dll_base + 0x00040DC0);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70E10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction03_Chest, dll_base + 0x00040E10);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC70F30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction57_SparklyChest, dll_base + 0x00040F30);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC71060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction58_Fissure, dll_base + 0x00041060);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC710B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction59_VileDogAfterglow, dll_base + 0x000410B0);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC71110" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction12_PermanentPortal, dll_base + 0x00041110);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC71360" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction08_Torch, dll_base + 0x00041360);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC71370" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction14_Brazier, dll_base + 0x00041370);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC71380" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction34_HellBrazierFire, dll_base + 0x00041380);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC713D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction11_Portal, dll_base + 0x000413D0);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC71470" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction51_TrappedSoul, dll_base + 0x00041470);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC714A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction46_TrappedSoulPlaceHolder, dll_base + 0x000414A0);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC718C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_PopulateFn1_CasketJarSarcophagusUrn, dll_base + 0x000418C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			uint8_t nDensity{};
			uint32_t nObjectId{};
			uint16_t nProbability{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nDensity, nObjectId, nProbability);
			const auto original_result = original(&original_pGame, &original_pRoom, nDensity, nObjectId, nProbability);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC71F60" * doctest::skip(""))
	{
//		// Set up function pointers
//		const auto [sut, original] = make_function_pair(sub_6FC71F60, dll_base + 0x00041F60);
//		
//		SUBCASE("")
//		{
//			// Call both implementations
//			const auto moo_result = sut();
//			const auto original_result = original();
//			
//			// Compare return values
//			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
//		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC71FB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_PopulateFn7_RogueOnStick, dll_base + 0x00041FB0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			uint8_t nDensity{};
			uint32_t nObjectId{};
			uint16_t nProbability{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nDensity, nObjectId, nProbability);
			const auto original_result = original(&original_pGame, &original_pRoom, nDensity, nObjectId, nProbability);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC72340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnFliesOnCorpse, dll_base + 0x00042340);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC723F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_PopulateFn3_CommonObjects, dll_base + 0x000423F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			uint8_t nDensity{};
			uint32_t nObjectId{};
			uint16_t nChance{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nDensity, nObjectId, nChance);
			const auto original_result = original(&original_pGame, &original_pRoom, nDensity, nObjectId, nChance);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC72510" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_CreateObject, dll_base + 0x00042510);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nClassId{};
			int32_t nSizeX{};
			int32_t nSizeY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nClassId, nSizeX, nSizeY, &moo_pRoom);
			const auto original_result = original(&original_pGame, nClassId, nSizeX, nSizeY, &original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC726D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_PopulateFn9_TrappedSoul, dll_base + 0x000426D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			uint8_t nDensity{};
			uint32_t nObjectId{};
			uint16_t nProbability{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nDensity, nObjectId, nProbability);
			const auto original_result = original(&original_pGame, &original_pRoom, nDensity, nObjectId, nProbability);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC727F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_PopulateFn6_RogueGuardCorpse, dll_base + 0x000427F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			uint8_t nDensity{};
			uint32_t nObjectId{};
			uint16_t nProbability{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nDensity, nObjectId, nProbability);
			const auto original_result = original(&original_pGame, &original_pRoom, nDensity, nObjectId, nProbability);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC728C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_PopulateFn8_Well, dll_base + 0x000428C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			uint8_t nDensity{};
			uint32_t nObjectId{};
			uint16_t nProbability{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nDensity, nObjectId, nProbability);
			const auto original_result = original(&original_pGame, &original_pRoom, nDensity, nObjectId, nProbability);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC72C30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_PopulateFn2_WaypointShrine, dll_base + 0x00042C30);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			uint8_t nDensity{};
			uint32_t nObjectId{};
			uint16_t nProbability{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nDensity, nObjectId, nProbability);
			const auto original_result = original(&original_pGame, &original_pRoom, nDensity, nObjectId, nProbability);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC73050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_RollRandomNumber, dll_base + 0x00043050);
		
		SUBCASE("")
		{
			// Input data
			D2SeedStrc moo_pSeed{};
			D2SeedStrc original_pSeed{};
			int32_t nMin{};
			int32_t nMax{};

			const auto setup_data = [](
				D2SeedStrc& pSeed
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSeed);
			setup_data(original_pSeed);

			// Call both implementations
			const auto moo_result = sut(&moo_pSeed, nMin, nMax);
			const auto original_result = original(&original_pSeed, nMin, nMax);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC730C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_PopulateFn4_Barrel, dll_base + 0x000430C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			uint8_t nDensity{};
			uint32_t nObjectId{};
			uint16_t nProbability{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nDensity, nObjectId, nProbability);
			const auto original_result = original(&original_pGame, &original_pRoom, nDensity, nObjectId, nProbability);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC73550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_PopulateFn5_Crate, dll_base + 0x00043550);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			uint8_t nDensity{};
			uint32_t nObjectId{};
			uint16_t nProbability{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nDensity, nObjectId, nProbability);
			const auto original_result = original(&original_pGame, &original_pRoom, nDensity, nObjectId, nProbability);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC73A70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnNothing, dll_base + 0x00043A70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgCoordsStrc moo_pDrlgCoords{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgCoordsStrc original_pDrlgCoords{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2DrlgCoordsStrc& pDrlgCoords
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pDrlgCoords);
			setup_data(original_pGame, original_pRoom, original_pDrlgCoords);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pDrlgCoords);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pDrlgCoords);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoords, original_pDrlgCoords, "Comparing pDrlgCoords");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC73A80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnBarrel, dll_base + 0x00043A80);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgCoordsStrc moo_pDrlgCoords{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgCoordsStrc original_pDrlgCoords{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2DrlgCoordsStrc& pDrlgCoords
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pDrlgCoords);
			setup_data(original_pGame, original_pRoom, original_pDrlgCoords);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pDrlgCoords);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pDrlgCoords);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoords, original_pDrlgCoords, "Comparing pDrlgCoords");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC73C50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnNothing2, dll_base + 0x00043C50);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgCoordsStrc moo_pDrlgCoords{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgCoordsStrc original_pDrlgCoords{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2DrlgCoordsStrc& pDrlgCoords
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pDrlgCoords);
			setup_data(original_pGame, original_pRoom, original_pDrlgCoords);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pDrlgCoords);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pDrlgCoords);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoords, original_pDrlgCoords, "Comparing pDrlgCoords");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC73D80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnArmorStand, dll_base + 0x00043D80);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgCoordsStrc moo_pDrlgCoords{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgCoordsStrc original_pDrlgCoords{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2DrlgCoordsStrc& pDrlgCoords
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pDrlgCoords);
			setup_data(original_pGame, original_pRoom, original_pDrlgCoords);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pDrlgCoords);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pDrlgCoords);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoords, original_pDrlgCoords, "Comparing pDrlgCoords");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC73DA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnArmorStandOrWeaponRack, dll_base + 0x00043DA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgCoordsStrc moo_pDrlgCoords{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgCoordsStrc original_pDrlgCoords{};
			int32_t bWeaponRack{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2DrlgCoordsStrc& pDrlgCoords
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pDrlgCoords);
			setup_data(original_pGame, original_pRoom, original_pDrlgCoords);

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom, &moo_pDrlgCoords, bWeaponRack);
			original(&original_pGame, &original_pRoom, &original_pDrlgCoords, bWeaponRack);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoords, original_pDrlgCoords, "Comparing pDrlgCoords");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC740C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SpawnWeaponRack, dll_base + 0x000440C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgCoordsStrc moo_pDrlgCoords{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgCoordsStrc original_pDrlgCoords{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2DrlgCoordsStrc& pDrlgCoords
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pDrlgCoords);
			setup_data(original_pGame, original_pRoom, original_pDrlgCoords);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pDrlgCoords);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pDrlgCoords);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoords, original_pDrlgCoords, "Comparing pDrlgCoords");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC740E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_PopulationHandler, dll_base + 0x000440E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC744B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_FreeHoverMessage, dll_base + 0x000444B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pObject{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pObject{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pObject
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pObject);
			setup_data(original_pGame, original_pObject);

			// Call both implementations
			sut(&moo_pGame, &moo_pObject);
			original(&original_pGame, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC74520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_RemoveAll, dll_base + 0x00044520);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame);
			original(&original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC74590" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_SetUnitIdInTimerArg, dll_base + 0x00044590);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPortal{};
			D2UnitStrc original_pPortal{};
			int32_t nUnitId{};

			const auto setup_data = [](
				D2UnitStrc& pPortal
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPortal);
			setup_data(original_pPortal);

			// Call both implementations
			sut(&moo_pPortal, nUnitId);
			original(&original_pPortal, nUnitId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPortal, original_pPortal, "Comparing pPortal");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC745B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_GetUnitIdFromTimerArg, dll_base + 0x000445B0);
		
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
}
