#include <D2CommonTestDefines.h>

#ifdef UNITROOM_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <Units/UnitRoom.h>
#include <Units/Units.h>


TEST_SUITE("UnitRoomTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBCF10 (#11279)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITROOM_AddUnitToRoomEx, dll_base + 0x0007CF10);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc original_pRoom{};
			int nUnused{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc& pRoom
			) {
				pUnit.dwUnitType = UNIT_MONSTER;

				// Make the room contain the unit's (0, 0) coordinates
				pRoom.tCoords.nSubtileWidth = 1;
				pRoom.tCoords.nSubtileHeight = 1;
			};

			setup_data(moo_pUnit, moo_pRoom);
			setup_data(original_pUnit, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pRoom, nUnused);
			const auto original_result = original(&original_pUnit, &original_pRoom, nUnused);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD100 (#10384)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITROOM_AddUnitToRoom, dll_base + 0x0007D100);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc& pRoom
			) {
				pUnit.dwUnitType = UNIT_MONSTER;

				// Make the room contain the unit's (0, 0) coordinates
				pRoom.tCoords.nSubtileWidth = 1;
				pRoom.tCoords.nSubtileHeight = 1;
			};

			setup_data(moo_pUnit, moo_pRoom);
			setup_data(original_pUnit, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pRoom);
			const auto original_result = original(&original_pUnit, &original_pRoom);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD120 (#10385)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITROOM_RefreshUnit, dll_base + 0x0007D120);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc moo_pAct{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgActStrc original_pAct{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom,
				D2DrlgActStrc& pAct
			) {
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pRoom = &pRoom;
				pRoom.pAct = &pAct;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom, moo_pAct);
			setup_data(original_pUnit, original_pDynamicPath, original_pRoom, original_pAct);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD1B0 (#10388)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITROOM_SortUnitListByTargetY, dll_base + 0x0007D1B0);
		
		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pUnits[2]{};
			D2DynamicPathStrc moo_pDynamicPaths[2]{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pUnits[2]{};
			D2DynamicPathStrc original_pDynamicPaths[2]{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc(& pUnits)[2],
				D2DynamicPathStrc(& pDynamicPaths)[2]
			) {
				for (auto i = 0; i < 2; ++i)
				{
					pUnits[i].dwUnitType = UNIT_MONSTER;
					pUnits[i].pDynamicPath = &pDynamicPaths[i];
				}

				// First unit is below the second one, so they are expected to be swapped by the sort
				pDynamicPaths[0].dwClientCoordY = 20;
				pDynamicPaths[1].dwClientCoordY = 10;

				pUnits[0].pRoomNext = &pUnits[1];
				pRoom.pUnitFirst = &pUnits[0];
			};

			setup_data(moo_pRoom, moo_pUnits, moo_pDynamicPaths);
			setup_data(original_pRoom, original_pUnits, original_pDynamicPaths);

			// Call both implementations
			sut(&moo_pRoom);
			original(&original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD250 (#10390)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITROOM_UpdatePath, dll_base + 0x0007D250);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD2B0 (#10391)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITROOM_ClearUpdateQueue, dll_base + 0x0007D2B0);
		
		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pUnits[2]{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pUnits[2]{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc(& pUnits)[2]
			) {
				pUnits[0].dwFlags = UNITFLAG_ISLINKREFRESHMSG;
				pUnits[1].dwFlags = UNITFLAG_ISLINKREFRESHMSG;
				pUnits[0].pChangeNextUnit = &pUnits[1];

				pRoom.pUnitUpdate = &pUnits[0];
			};

			setup_data(moo_pRoom, moo_pUnits);
			setup_data(original_pRoom, original_pUnits);

			// Call both implementations
			sut(&moo_pRoom);
			original(&original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD300 (#10386)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITROOM_RemoveUnitFromRoom, dll_base + 0x0007D300);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom
			) {
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pRoom = &pRoom;

				// The unit is the only unit currently in the room
				pRoom.pUnitFirst = &pUnit;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom);
			setup_data(original_pUnit, original_pDynamicPath, original_pRoom);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD400 (#10387)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITROOM_RemoveUnitFromUpdateQueue, dll_base + 0x0007D400);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom
			) {
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pRoom = &pRoom;

				// The unit is the only unit currently in the room's update queue
				pRoom.pUnitUpdate = &pUnit;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom);
			setup_data(original_pUnit, original_pDynamicPath, original_pRoom);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD4C0 (#10389)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITROOM_IsUnitInRoom, dll_base + 0x0007D4C0);
		
		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc& pUnit
			) {
				// The unit is the first (and only) unit in the room
				pRoom.pUnitFirst = &pUnit;
			};

			setup_data(moo_pRoom, moo_pUnit);
			setup_data(original_pRoom, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_pUnit);
			const auto original_result = original(&original_pRoom, &original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}

#endif
