#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Monsters.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Units/UnitFinds.h>
#include <Units/Units.h>


namespace
{
	// Matches every unit, used to test the generic unit finding logic without relying on UNITFINDS_TestUnit
	int32_t __fastcall UnitFindsTests_MatchAllUnits(D2UnitStrc* pUnit, D2UnitFindArgStrc* pUnitFindArg)
	{
		return 1;
	}
}

TEST_SUITE("UnitFindsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC680 (#10408)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_AreUnitsInNeighboredRooms, dll_base + 0x0007C680);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pDestUnit{};
			D2UnitStrc moo_pSrcUnit{};
			D2DynamicPathStrc moo_pDestDynamicPath{};
			D2DynamicPathStrc moo_pSrcDynamicPath{};
			D2ActiveRoomStrc moo_pDestRoom{};
			D2ActiveRoomStrc moo_pSrcRoom{};
			D2ActiveRoomStrc* moo_pRoomList[1]{};
			D2UnitStrc original_pDestUnit{};
			D2UnitStrc original_pSrcUnit{};
			D2DynamicPathStrc original_pDestDynamicPath{};
			D2DynamicPathStrc original_pSrcDynamicPath{};
			D2ActiveRoomStrc original_pDestRoom{};
			D2ActiveRoomStrc original_pSrcRoom{};
			D2ActiveRoomStrc* original_pRoomList[1]{};

			const auto setup_data = [](
				D2UnitStrc& pDestUnit,
				D2UnitStrc& pSrcUnit,
				D2DynamicPathStrc& pDestDynamicPath,
				D2DynamicPathStrc& pSrcDynamicPath,
				D2ActiveRoomStrc& pDestRoom,
				D2ActiveRoomStrc& pSrcRoom,
				D2ActiveRoomStrc* (&pRoomList)[1]
			) {
				// Place both units in rooms reachable through a dynamic path
				pDestUnit.dwUnitType = UNIT_MONSTER;
				pDestUnit.pDynamicPath = &pDestDynamicPath;
				pDestDynamicPath.pRoom = &pDestRoom;

				pSrcUnit.dwUnitType = UNIT_MONSTER;
				pSrcUnit.pDynamicPath = &pSrcDynamicPath;
				pSrcDynamicPath.pRoom = &pSrcRoom;

				// Make the destination room a neighbor of the source room
				pRoomList[0] = &pDestRoom;
				pSrcRoom.ppRoomList = pRoomList;
				pSrcRoom.nNumRooms = 1;
			};

			setup_data(moo_pDestUnit, moo_pSrcUnit, moo_pDestDynamicPath, moo_pSrcDynamicPath, moo_pDestRoom, moo_pSrcRoom, moo_pRoomList);
			setup_data(original_pDestUnit, original_pSrcUnit, original_pDestDynamicPath, original_pSrcDynamicPath, original_pDestRoom, original_pSrcRoom, original_pRoomList);

			// Call both implementations
			const auto moo_result = sut(&moo_pDestUnit, &moo_pSrcUnit);
			const auto original_result = original(&original_pDestUnit, &original_pSrcUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDestUnit, original_pDestUnit, "Comparing pDestUnit");
			MOO_CHECK_EQ(moo_pSrcUnit, original_pSrcUnit, "Comparing pSrcUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC720 (#11087)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_FindUnitInNeighboredRooms, dll_base + 0x0007C720);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_type = random_unsigned_integer();
			const auto class_id = random_unsigned_integer();

			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc* moo_pRoomList[1]{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc* original_pRoomList[1]{};
			int nUnitType = unit_type;
			int nClassId = class_id;

			const auto setup_data = [unit_type, class_id](
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc* (&pRoomList)[1]
			) {
				// Make the unit the matching one found inside the room
				pUnit.dwUnitType = unit_type;
				pUnit.dwClassId = class_id;
				pRoom.pUnitFirst = &pUnit;

				// The room is its own (only) neighbor
				pRoomList[0] = &pRoom;
				pRoom.ppRoomList = pRoomList;
				pRoom.nNumRooms = 1;
			};

			setup_data(moo_pRoom, moo_pUnit, moo_pRoomList);
			setup_data(original_pRoom, original_pUnit, original_pRoomList);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nUnitType, nClassId);
			const auto original_result = original(&original_pRoom, nUnitType, nClassId);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC7B0 (#10405)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_GetTestedUnitsFromRoom, dll_base + 0x0007C7B0);
		
		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc* moo_ppUnits{};
			D2UnitFindArgStrc moo_pUnitFindArg{};
			D2UnitStrc moo_pRoomUnit{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc* original_ppUnits{};
			D2UnitFindArgStrc original_pUnitFindArg{};
			D2UnitStrc original_pRoomUnit{};
			UNITFINDTEST pfnUnitTest = UnitFindsTests_MatchAllUnits;

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc*& ppUnits,
				D2UnitFindArgStrc& pUnitFindArg,
				D2UnitStrc& pRoomUnit
			) {
				// A single unit in the room, matched by pfnUnitTest
				pRoom.pUnitFirst = &pRoomUnit;
			};

			setup_data(moo_pRoom, moo_ppUnits, moo_pUnitFindArg, moo_pRoomUnit);
			setup_data(original_pRoom, original_ppUnits, original_pUnitFindArg, original_pRoomUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_ppUnits, pfnUnitTest, &moo_pUnitFindArg);
			const auto original_result = original(&original_pRoom, &original_ppUnits, pfnUnitTest, &original_pUnitFindArg);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_ppUnits, original_ppUnits, "Comparing ppUnits");
			MOO_CHECK_EQ(moo_pUnitFindArg, original_pUnitFindArg, "Comparing pUnitFindArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC840 (#11088)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_GetNearestTestedUnit, dll_base + 0x0007C840);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};
			int nX = random_unsigned_integer();
			int nY = random_unsigned_integer();
			int nSize = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom
			) {
				// The unit needs to be inside a room for UNITS_GetRoom to succeed
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pRoom = &pRoom;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom);
			setup_data(original_pUnit, original_pDynamicPath, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nX, nY, nSize, nullptr);
			const auto original_result = original(&original_pUnit, nX, nY, nSize, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC990 (#10401)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_InitializeUnitFindData, dll_base + 0x0007C990);
		
		SUBCASE("")
		{
			// Input data
			const auto room_flags = random_unsigned_integer();

			D2UnitFindDataStrc moo_pUnitFindData{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitFindArgStrc moo_pUnitFindArg{};
			D2UnitFindDataStrc original_pUnitFindData{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitFindArgStrc original_pUnitFindArg{};
			int nX = random_unsigned_integer();
			int nY = random_unsigned_integer();
			int nSize = random_unsigned_integer();
			UNITFINDTEST pfnUnitTest{};

			const auto setup_data = [room_flags](
				D2UnitFindDataStrc& pUnitFindData,
				D2ActiveRoomStrc& pRoom,
				D2UnitFindArgStrc& pUnitFindArg
			) {
				pRoom.dwFlags = room_flags;
			};

			setup_data(moo_pUnitFindData, moo_pRoom, moo_pUnitFindArg);
			setup_data(original_pUnitFindData, original_pRoom, original_pUnitFindArg);

			// Call both implementations
			sut(nullptr, &moo_pUnitFindData, &moo_pRoom, nX, nY, nSize, pfnUnitTest, &moo_pUnitFindArg);
			original(nullptr, &original_pUnitFindData, &original_pRoom, nX, nY, nSize, pfnUnitTest, &original_pUnitFindArg);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnitFindData, original_pUnitFindData, "Comparing pUnitFindData");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pUnitFindArg, original_pUnitFindArg, "Comparing pUnitFindArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBCA50 (#10402)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_FreeUnitFindData, dll_base + 0x0007CA50);
		const auto [moo_alloc, original_alloc] = make_function_pair(UNITFINDS_InitializeUnitFindData, dll_base + 0x0007C990);

		SUBCASE("")
		{
			// Input data
			const auto room_flags = random_unsigned_integer();

			D2UnitFindDataStrc moo_pUnitFindData{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitFindArgStrc moo_pUnitFindArg{};
			D2UnitFindDataStrc original_pUnitFindData{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitFindArgStrc original_pUnitFindArg{};
			int nX = random_unsigned_integer();
			int nY = random_unsigned_integer();
			int nSize = random_unsigned_integer();
			UNITFINDTEST pfnUnitTest{};

			const auto setup_data = [room_flags](
				D2UnitFindDataStrc& pUnitFindData,
				D2ActiveRoomStrc& pRoom,
				D2UnitFindArgStrc& pUnitFindArg
			) {
				pRoom.dwFlags = room_flags;
			};

			setup_data(moo_pUnitFindData, moo_pRoom, moo_pUnitFindArg);
			setup_data(original_pUnitFindData, original_pRoom, original_pUnitFindArg);

			// Call both implementations
			moo_alloc(nullptr, &moo_pUnitFindData, &moo_pRoom, nX, nY, nSize, pfnUnitTest, &moo_pUnitFindArg);
			original_alloc(nullptr, &original_pUnitFindData, &original_pRoom, nX, nY, nSize, pfnUnitTest, &original_pUnitFindArg);

			// Call both implementations
			sut(&moo_pUnitFindData);
			original(&original_pUnitFindData);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnitFindData, original_pUnitFindData, "Comparing pUnitFindData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBCA80 (#10403)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_FindAllMatchingUnitsInNeighboredRooms, dll_base + 0x0007CA80);
		
		SUBCASE("")
		{
			// Input data
			D2UnitFindDataStrc moo_pUnitFindData{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pRoomUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitFindArgStrc moo_pUnitFindArg{};
			D2UnitStrc* moo_pUnitsArray[UNIT_FIND_ARRAY_SIZE]{};
			D2UnitFindDataStrc original_pUnitFindData{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pRoomUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitFindArgStrc original_pUnitFindArg{};
			D2UnitStrc* original_pUnitsArray[UNIT_FIND_ARRAY_SIZE]{};

			const auto setup_data = [](
				D2UnitFindDataStrc& pUnitFindData,
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc& pRoomUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2UnitFindArgStrc& pUnitFindArg,
				D2UnitStrc* (&pUnitsArray)[UNIT_FIND_ARRAY_SIZE]
			) {
				// Room large enough that no neighbor room lookup is needed
				pRoom.tCoords.nSubtileWidth = 100;
				pRoom.tCoords.nSubtileHeight = 100;
				pRoom.pUnitFirst = &pRoomUnit;

				// A monster unit located at the center of the room, inside the find area
				pRoomUnit.dwUnitType = UNIT_MONSTER;
				pRoomUnit.dwAnimMode = MONMODE_NEUTRAL;
				pRoomUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pRoom = &pRoom;
				pDynamicPath.tGameCoords.wPosX = 50;
				pDynamicPath.tGameCoords.wPosY = 50;

				// Falls back to UNITFINDS_TestUnit, only allowing monster units
				pUnitFindArg.nFlags = 2;
				pUnitFindArg.nX = 50;
				pUnitFindArg.nY = 50;
				pUnitFindArg.nSize = 10;

				pUnitFindData.pRoom = &pRoom;
				pUnitFindData.pUnitFindArg = &pUnitFindArg;
				pUnitFindData.pUnitsArray = pUnitsArray;
				pUnitFindData.nMaxArrayEntries = UNIT_FIND_ARRAY_SIZE;
				pUnitFindData.nX = 50;
				pUnitFindData.nY = 50;
				pUnitFindData.nSize = 10;
			};

			setup_data(moo_pUnitFindData, moo_pRoom, moo_pRoomUnit, moo_pDynamicPath, moo_pUnitFindArg, moo_pUnitsArray);
			setup_data(original_pUnitFindData, original_pRoom, original_pRoomUnit, original_pDynamicPath, original_pUnitFindArg, original_pUnitsArray);

			// Call both implementations
			sut(&moo_pUnitFindData);
			original(&original_pUnitFindData);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnitFindData, original_pUnitFindData, "Comparing pUnitFindData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBCCA0 (#10404)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITFINDS_TestUnit, dll_base + 0x0007CCA0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitFindArgStrc moo_pUnitFindArg{};
			D2UnitStrc original_pUnit{};
			D2UnitFindArgStrc original_pUnitFindArg{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitFindArgStrc& pUnitFindArg
			) {
				// A living monster at (0, 0), matching the find arguments
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.dwAnimMode = MONMODE_NEUTRAL;

				pUnitFindArg.nFlags = 2;
			};

			setup_data(moo_pUnit, moo_pUnitFindArg);
			setup_data(original_pUnit, original_pUnitFindArg);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pUnitFindArg);
			const auto original_result = original(&original_pUnit, &original_pUnitFindArg);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pUnitFindArg, original_pUnitFindArg, "Comparing pUnitFindArg");
		}
	}
}
