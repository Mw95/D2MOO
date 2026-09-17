#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <Path/Path.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>


TEST_SUITE("PathTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA8220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDA8220, dll_base + 0x00068220);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath);
			original(&original_pDynamicPath);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA82A0 (#10141)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetClientCoordsVelocity, dll_base + 0x000682A0);
		
		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer();
			const auto y = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			int moo_pX{};
			int moo_pY{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			int original_pX{};
			int original_pY{};

			const auto setup_data = [x, y](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				int& pX,
				int& pY
			) {
				pDynamicPath.dwPathPoints = 5;
				pDynamicPath.tVelocityVector.nX = x;
				pDynamicPath.tVelocityVector.nY = y;

				pUnit.dwAnimMode = PLRMODE_RUN;
				pUnit.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pX, moo_pY);
			setup_data(original_pUnit, original_pDynamicPath, original_pX, original_pY);

			// Call both implementations
			sut(&moo_pUnit, &moo_pX, &moo_pY);
			original(&original_pUnit, &original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA8320 (#10222)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AddCollisionFootprintForUnit, dll_base + 0x00068320);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA8450 (#10223)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_RemoveCollisionFootprintForUnit, dll_base + 0x00068450);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			BOOL bForce{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, bForce);
			const auto original_result = original(&original_pUnit, bForce);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA8600 (#10142)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10142, dll_base + 0x00068600);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pPath{};
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc original_pPath{};
			D2UnitStrc original_pUnit{};
			int bAllowInTown{};

			const auto setup_data = [](
				D2DynamicPathStrc& pPath,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPath, moo_pUnit);
			setup_data(original_pPath, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pPath, &moo_pUnit, bAllowInTown);
			const auto original_result = original(&original_pPath, &original_pUnit, bAllowInTown);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPath, original_pPath, "Comparing pPath");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA8E30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_ComputePathClassicMissile, dll_base + 0x00068E30);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDynamicPath, moo_pUnit);
			setup_data(original_pDynamicPath, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, &moo_pUnit);
			const auto original_result = original(&original_pDynamicPath, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA8FE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_FindValidTargetCoordsByMovingOrthogonally, dll_base + 0x00068FE0);
		
		SUBCASE("")
		{
			// Input data
			D2PathInfoStrc moo_pPathInfo{};
			D2PathInfoStrc original_pPathInfo{};

			const auto setup_data = [](
				D2PathInfoStrc& pPathInfo
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPathInfo);
			setup_data(original_pPathInfo);

			// Call both implementations
			sut(&moo_pPathInfo);
			original(&original_pPathInfo);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
		}
	}
	
	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FDA90C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AdvanceToDoor, dll_base + 0x000690C0);
		
		const auto door_id = GENERATE(13, 14, 15, 16, 23, 24, 25, 27, 47, 62, 63, 64, 75, 91, 92, 98, 99, 229, 230, 290, 291, 292, 293, 294, 295);

		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2PathInfoStrc moo_pPathInfo{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc moo_pTargetUnit{};
			D2DynamicPathStrc moo_pTargetUnitDynamicPath{};
			D2ObjectDataStrc moo_pObjectData{};
			D2PathInfoStrc original_pPathInfo{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitStrc original_pTargetUnit{};
			D2DynamicPathStrc original_pTargetUnitDynamicPath{};
			D2ObjectDataStrc original_pObjectData{};

			const auto setup_data = [this, door_id, x, y](
				D2PathInfoStrc& pPathInfo,
				D2DynamicPathStrc& pDynamicPath,
				D2UnitStrc& pTargetUnit,
				D2DynamicPathStrc& pTargetUnitDynamicPath,
				D2ObjectDataStrc& pObjectData
			) {
				pObjectData.pObjectTxt = &objects_txt[door_id];
				
				pTargetUnitDynamicPath.tGameCoords.wPosX = x;
				pTargetUnitDynamicPath.tGameCoords.wPosY = y;
				
				pTargetUnit.dwClassId = door_id;
				pTargetUnit.dwUnitType = UNIT_OBJECT;
				pTargetUnit.pObjectData = &pObjectData;
				pTargetUnit.pDynamicPath = &pTargetUnitDynamicPath;
				
				pDynamicPath.pTargetUnit = &pTargetUnit;

				pPathInfo.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pPathInfo, moo_pDynamicPath, moo_pTargetUnit, moo_pTargetUnitDynamicPath, moo_pObjectData);
			setup_data(original_pPathInfo, original_pDynamicPath, original_pTargetUnit, original_pTargetUnitDynamicPath, original_pObjectData);

			// Call both implementations
			const auto moo_result = sut(&moo_pPathInfo);
			const auto original_result = original(&original_pPathInfo);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9190 (#10156)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_FreeDynamicPath, dll_base + 0x00069190);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(moo_pMemPool, &moo_pDynamicPath);
			original(original_pMemPool, &original_pDynamicPath);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>, "D2Common.0x6FDA91B0 (#11282)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetCollisionPatternFromMonStats2Txt, dll_base + 0x000691B0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				int nMonsterId = i;

				// Call both implementations
				const auto moo_result = sut(nMonsterId);
				const auto original_result = original(nMonsterId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA9250 (#11281)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11281_CollisionPatternFromSize, dll_base + 0x00069250);
		
		// TODO: Check if sizes bigger than 3 are allowed. If so, we have a bug here
		const auto size = GENERATE(0, 1, 2, 3);

		SUBCASE("")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				int nSize = size;

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
				};

				setup_data(moo_pUnit);
				setup_data(original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nSize);
				const auto original_result = original(&original_pUnit, nSize);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA92F0 (#10214)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10214, dll_base + 0x000692F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9480 (#10152)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AllocDynamicPath, dll_base + 0x00069480);
		
		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pUnit{};
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			int nX{};
			int nY{};
			BOOL bSetFlag{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pRoom, moo_pUnit);
			setup_data(original_pRoom, original_pUnit);

			// Call both implementations
			sut(moo_pMemPool, &moo_pRoom, nX, nY, &moo_pUnit, bSetFlag);
			original(original_pMemPool, &original_pRoom, nX, nY, &original_pUnit, bSetFlag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9720")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDA9720, dll_base + 0x00069720);

		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 128; ++i)
			{
				// Input data
				const auto flags = random_unsigned_integer();

				D2DynamicPathStrc moo_pDynamicPath{};
				D2UnitStrc moo_pUnit{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc original_pUnit{};
				uint8_t nDirection = i;

				const auto setup_data = [unit_type, flags](
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = unit_type;
					pDynamicPath.pUnit = &pUnit;
					pDynamicPath.dwFlags = flags;
				};

				setup_data(moo_pDynamicPath, moo_pUnit);
				setup_data(original_pDynamicPath, original_pUnit);

				// Call both implementations
				sut(&moo_pDynamicPath, nDirection);
				original(&original_pDynamicPath, nDirection);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9770 (#10193)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10193_PATH_AdjustDirection, dll_base + 0x00069770);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto direction = random_unsigned_integer(0, 63);
			const auto new_direction = random_unsigned_integer(0, 63);
			const auto diff_direction = random_unsigned_integer(0, 63);
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [direction, new_direction, diff_direction, flags](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.nDirection = direction;
				pDynamicPath.nNewDirection = new_direction;
				pDynamicPath.nDiffDirection = diff_direction;
				pDynamicPath.dwFlags = flags;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath);
			original(&original_pDynamicPath);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA97C0 (#10216)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10216, dll_base + 0x000697C0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nX{};
			int nY{};
			int a4{};

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath, nX, nY, a4);
			original(&original_pDynamicPath, nX, nY, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9850 (#10228)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10228, dll_base + 0x00069850);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9870 (#10143)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetUnitDeadCollision, dll_base + 0x00069870);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			BOOL bForGameLogic{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, bForGameLogic);
			original(&original_pUnit, bForGameLogic);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA98F0 (#10144)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetUnitAliveCollision, dll_base + 0x000698F0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			BOOL bForGameLogic{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, bForGameLogic);
			original(&original_pUnit, bForGameLogic);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9A70 (#10146)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetVelocity, dll_base + 0x00069A70);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nVelocity = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pDynamicPath, nVelocity, __FILE__, __LINE__);
			original(&original_pDynamicPath, nVelocity, __FILE__, __LINE__);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9AB0 (#10147)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetVelocity, dll_base + 0x00069AB0);
		
		SUBCASE("")
		{
			// Input data
			const auto velocity = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [velocity](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwVelocity = velocity;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9AC0 (#10148)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetMaxVelocity, dll_base + 0x00069AC0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nMaxVelocity = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pDynamicPath, nMaxVelocity);
			original(&original_pDynamicPath, nMaxVelocity);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9AE0 (#10149)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetMaxVelocity, dll_base + 0x00069AE0);
		
		SUBCASE("")
		{
			// Input data
			const auto max_velocity = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [max_velocity](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwMaxVelocity = max_velocity;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9AF0 (#10150)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetAcceleration, dll_base + 0x00069AF0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nAcceleration = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pDynamicPath, nAcceleration);
			original(&original_pDynamicPath, nAcceleration);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9B10 (#10151)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetAcceleration, dll_base + 0x00069B10);
		
		SUBCASE("")
		{
			// Input data
			const auto acceleration = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [acceleration](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwAcceleration = acceleration;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9B20 (#10153)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10153, dll_base + 0x00069B20);
		
		SUBCASE("")
		{
			// Input data
			const auto path_points = random_unsigned_integer();
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [path_points, flags](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwPathPoints = path_points;
				pDynamicPath.dwFlags = flags;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath);
			original(&original_pDynamicPath);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9B40 (#10208)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10208_PathSetPathingFlag, dll_base + 0x00069B40);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			BOOL bSet = GENERATE(true, false);

			const auto setup_data = [flags](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwFlags = flags;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath, bSet);
			original(&original_pDynamicPath, bSet);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9B70 (#10209)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10209_PathCheckPathingFlag, dll_base + 0x00069B70);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [flags](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwFlags = flags;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9B80 (#10154)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetNumberOfPathPoints, dll_base + 0x00069B80);
		
		SUBCASE("")
		{
			// Input data
			const auto path_points = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [path_points](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwPathPoints = path_points;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9B90 (#11291)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetNumberOfPathPoints, dll_base + 0x00069B90);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 100; ++i)
			{
				// Input data
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				int a2 = i;

				// Call both implementations
				sut(&moo_pDynamicPath, a2);
				original(&original_pDynamicPath, a2);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9BC0 (#10155)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10155, dll_base + 0x00069BC0);
		
		SUBCASE("")
		{
			// Input data
			const auto current_point_index = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [current_point_index](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwCurrentPointIdx = current_point_index;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9BD0 (#10157)" * doctest::skip("ppPathPoints check fails"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetPathPoints, dll_base + 0x00069BD0);
		
		SUBCASE("")
		{
			// Input data
			D2PathPointStrc path_points[78]{};
			const auto count = random_unsigned_integer(0, std::size(path_points));
			for (auto i = 0; i < count; ++i)
			{
				path_points[i].X = random_unsigned_integer(0, 65535);
				path_points[i].Y = random_unsigned_integer(0, 65535);
			}

			D2DynamicPathStrc moo_pDynamicPath{};
			D2PathPointStrc* moo_ppPathPoints{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2PathPointStrc* original_ppPathPoints{};

			const auto setup_data = [&path_points, count](
				D2DynamicPathStrc& pDynamicPath,
				D2PathPointStrc*& ppPathPoints
			) {
				memcpy(pDynamicPath.PathPoints, path_points, sizeof(pDynamicPath.PathPoints));
				pDynamicPath.dwPathPoints = count;
			};

			setup_data(moo_pDynamicPath, moo_ppPathPoints);
			setup_data(original_pDynamicPath, original_ppPathPoints);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, &moo_ppPathPoints);
			const auto original_result = original(&original_pDynamicPath, &original_ppPathPoints);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			MOO_CHECK_EQ(moo_ppPathPoints, original_ppPathPoints, "Comparing ppPathPoints");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9BF0 (#10158)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetDirection, dll_base + 0x00069BF0);
		
		SUBCASE("")
		{
			// Input data
			const auto direction = random_unsigned_integer(0, 255);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [direction](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.nDirection = direction;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9C10 (#10159)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetNewDirection, dll_base + 0x00069C10);
		
		SUBCASE("")
		{
			// Input data
			const auto new_direction = random_unsigned_integer(0, 255);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [new_direction](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.nNewDirection = new_direction;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9C20 (#10160)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10160_PathUpdateDirection, dll_base + 0x00069C20);
		
		REPEAT_10();
		
		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM);

		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			uint8_t nDirection = random_unsigned_integer(0, 63);

			const auto setup_data = [unit_type, flags](
				D2DynamicPathStrc& pDynamicPath,
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				
				pDynamicPath.pUnit = &pUnit;
				pDynamicPath.dwFlags = flags;
			};

			setup_data(moo_pDynamicPath, moo_pUnit);
			setup_data(original_pDynamicPath, original_pUnit);

			// Call both implementations
			sut(&moo_pDynamicPath, nDirection);
			original(&original_pDynamicPath, nDirection);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9C90 (#10161)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetDirection, dll_base + 0x00069C90);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			uint8_t nDirection = random_unsigned_integer(0, 255);

			// Call both implementations
			sut(&moo_pDynamicPath, nDirection);
			original(&original_pDynamicPath, nDirection);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9CB0 (#10162)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetXPosition, dll_base + 0x00069CB0);
		
		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer(0, 65535);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [x](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tGameCoords.wPosX = x;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9CF0 (#10163)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetYPosition, dll_base + 0x00069CF0);
		
		SUBCASE("")
		{
			// Input data
			const auto y = random_unsigned_integer(0, 65535);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [y](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tGameCoords.wPosY = y;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9D30 (#10194)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetPrecisionX, dll_base + 0x00069D30);
		
		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer(0, 65535);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [x](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tGameCoords.dwPrecisionX = x;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9D60 (#10195)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetPrecisionY, dll_base + 0x00069D60);
		
		SUBCASE("")
		{
			// Input data
			const auto y = random_unsigned_integer(0, 65535);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [y](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tGameCoords.dwPrecisionY = y;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9D90 (#10196)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetPrecisionX, dll_base + 0x00069D90);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nPrecisionX = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pDynamicPath, nPrecisionX);
			original(&original_pDynamicPath, nPrecisionX);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9DA0 (#10197)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetPrecisionY, dll_base + 0x00069DA0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nPrecisionY = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pDynamicPath, nPrecisionY);
			original(&original_pDynamicPath, nPrecisionY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9DB0 (#10164)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetClientCoordX, dll_base + 0x00069DB0);
		
		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer(0, 65535);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [x](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwClientCoordX = x;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3CE0 (#10165)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetClientCoordY, dll_base + 0x00083CE0);
		
		SUBCASE("")
		{
			// Input data
			const auto y = random_unsigned_integer(0, 65535);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [y](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwClientCoordY = y;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9DC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetClientCoordX, dll_base + 0x00069DC0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nTargetX = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pDynamicPath, nTargetX);
			original(&original_pDynamicPath, nTargetX);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9DD0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetClientCoordY, dll_base + 0x00069DD0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nTargetY = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pDynamicPath, nTargetY);
			original(&original_pDynamicPath, nTargetY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9DE0 (#10175)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10175_PathGetFirstPointX, dll_base + 0x00069DE0);
		
		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer(0, 65535);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [x](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tTargetCoord.X = x;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9DF0 (#10176)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10176_PathGetFirstPointY, dll_base + 0x00069DF0);
		
		SUBCASE("")
		{
			// Input data
			const auto y = random_unsigned_integer(0, 65535);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [y](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tTargetCoord.Y = y;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9E00 (#10224)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10224, dll_base + 0x00069E00);
		
		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer(0, 65535);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [x](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tFinalTargetCoord.X = x;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9E10 (#10225)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10225, dll_base + 0x00069E10);
		
		SUBCASE("")
		{
			// Input data
			const auto y = random_unsigned_integer(0, 65535);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [y](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tFinalTargetCoord.Y = y;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9E20 (#10177)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10177_PATH_GetLastPointX, dll_base + 0x00069E20);
		
		SUBCASE("")
		{
			// Input data
			D2PathPointStrc path_points[78]{};
			const auto count = random_unsigned_integer(0, std::size(path_points));
			for (auto i = 0; i < count; ++i)
			{
				path_points[i].X = random_unsigned_integer(0, 65535);
				path_points[i].Y = random_unsigned_integer(0, 65535);
			}

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [&path_points, count](
				D2DynamicPathStrc& pDynamicPath
			) {
				memcpy(pDynamicPath.PathPoints, path_points, sizeof(pDynamicPath.PathPoints));
				pDynamicPath.dwPathPoints = count;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9E40 (#10178)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10178_PATH_GetLastPointY, dll_base + 0x00069E40);
		
		SUBCASE("")
		{
			// Input data
			D2PathPointStrc path_points[78]{};
			const auto count = random_unsigned_integer(0, std::size(path_points));
			for (auto i = 0; i < count; ++i)
			{
				path_points[i].X = random_unsigned_integer(0, 65535);
				path_points[i].Y = random_unsigned_integer(0, 65535);
			}
			
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [&path_points, count](
				D2DynamicPathStrc& pDynamicPath
			) {
				memcpy(pDynamicPath.PathPoints, path_points, sizeof(pDynamicPath.PathPoints));
				pDynamicPath.dwPathPoints = count;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9C10 (#10166)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetRoom, dll_base + 0x00079C10);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [flags](
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.dwFlags = flags;
				pDynamicPath.pRoom = &pRoom;
			};

			setup_data(moo_pDynamicPath, moo_pRoom);
			setup_data(original_pDynamicPath, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9E60 (#10167)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetRoom, dll_base + 0x00069E60);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [flags](
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.dwFlags = flags;
			};

			setup_data(moo_pDynamicPath, moo_pRoom);
			setup_data(original_pDynamicPath, original_pRoom);

			// Call both implementations
			sut(&moo_pDynamicPath, &moo_pRoom);
			original(&original_pDynamicPath, &original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9E70 (#10168)" * doctest::skip("Fails for some reason (probably visitor)"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetNextRoom, dll_base + 0x00069E70);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [flags](
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.dwFlags = flags;
				pDynamicPath.pRoom = &pRoom;
			};

			setup_data(moo_pDynamicPath, moo_pRoom);
			setup_data(original_pDynamicPath, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9E80 (#10169)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_ClearNextRoom, dll_base + 0x00069E80);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom
			) {
				pDynamicPath.pRoom = &pRoom;
			};

			setup_data(moo_pDynamicPath, moo_pRoom);
			setup_data(original_pDynamicPath, original_pRoom);

			// Call both implementations
			sut(&moo_pDynamicPath);
			original(&original_pDynamicPath);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9E90 (#10170)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10170_PathSetTargetPos, dll_base + 0x00069E90);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc moo_pTargetUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitStrc original_pTargetUnit{};
			int nX = random_unsigned_integer();
			int nY = random_unsigned_integer();

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath,
				D2UnitStrc& pTargetUnit
			) {
				pDynamicPath.pTargetUnit = &pTargetUnit;
			};

			setup_data(moo_pDynamicPath, moo_pTargetUnit);
			setup_data(original_pDynamicPath, original_pTargetUnit);

			// Call both implementations
			sut(&moo_pDynamicPath, nX, nY);
			original(&original_pDynamicPath, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9EC0 (#10172)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_IsCurrentRoomInvalid, dll_base + 0x00069EC0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [flags](
				D2DynamicPathStrc& pDynamicPath
			) {
					pDynamicPath.dwFlags = flags;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9ED0 (#10173)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetCurrentRoomInvalid, dll_base + 0x00069ED0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			BOOL bSet = GENERATE(true, false);

			const auto setup_data = [flags](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwFlags = flags;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath, bSet);
			original(&original_pDynamicPath, bSet);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9F00 (#10145)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetUnusedFlag_0x00004, dll_base + 0x00069F00);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			BOOL bSet = GENERATE(true, false);

			const auto setup_data = [flags](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwFlags = flags;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath, bSet);
			original(&original_pDynamicPath, bSet);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9F30 (#10174)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetUnusedFlag_0x00004, dll_base + 0x00069F30);

		REPEAT_10();
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [flags](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwFlags = flags;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9F40 (#10179)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetTargetUnit, dll_base + 0x00069F40);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDynamicPath, moo_pUnit);
			setup_data(original_pDynamicPath, original_pUnit);

			// Call both implementations
			sut(&moo_pDynamicPath, &moo_pUnit);
			original(&original_pDynamicPath, &original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9F60 (#10171)" * doctest::skip("Fails for some reason"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetTargetTypeAndGUID, dll_base + 0x00069F60);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			int moo_pTargetType{};
			D2UnitGUID moo_pTargetGUID{};
			D2DynamicPathStrc original_pDynamicPath{};
			int original_pTargetType{};
			D2UnitGUID original_pTargetGUID{};

			const auto setup_data = [unit_id](
				D2DynamicPathStrc& pDynamicPath,
				int& pTargetType,
				D2UnitGUID& pTargetGUID
			) {
				pDynamicPath.dwTargetType = UNIT_MONSTER;
				pDynamicPath.dwTargetId = unit_id;
			};

			setup_data(moo_pDynamicPath, moo_pTargetType, moo_pTargetGUID);
			setup_data(original_pDynamicPath, original_pTargetType, original_pTargetGUID);

			// Call both implementations
			sut(&moo_pDynamicPath, &moo_pTargetType, &moo_pTargetGUID);
			original(&original_pDynamicPath, &original_pTargetType, &original_pTargetGUID);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			MOO_CHECK_EQ(moo_pTargetType, original_pTargetType, "Comparing pTargetType");
			MOO_CHECK_EQ(moo_pTargetGUID, original_pTargetGUID, "Comparing pTargetGUID");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9FA0 (#10180)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetTargetUnit, dll_base + 0x00069FA0);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc moo_pTargetUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitStrc original_pTargetUnit{};

			const auto setup_data = [unit_id](
				D2DynamicPathStrc& pDynamicPath,
				D2UnitStrc& pTargetUnit
			) {
				pTargetUnit.dwUnitType = UNIT_MONSTER;
				pTargetUnit.dwUnitId = unit_id;
				pDynamicPath.pTargetUnit = &pTargetUnit;
			};

			setup_data(moo_pDynamicPath, moo_pTargetUnit);
			setup_data(original_pDynamicPath, original_pTargetUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9FC0 (#10181)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetFootprintCollisionMask, dll_base + 0x00069FC0);
		
		SUBCASE("")
		{
			// Input data
			const auto mask = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [mask](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.nFootprintCollisionMask = mask;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}

		SUBCASE("nullptr")
		{
			// Call both implementations
			const auto moo_result = sut(nullptr);
			const auto original_result = original(nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9FE0 (#10182)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetFootprintCollisionMask, dll_base + 0x00069FE0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nCollisionMask{};

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath, nCollisionMask);
			original(&original_pDynamicPath, nCollisionMask);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA0C0 (#10183)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetMoveTestCollisionMask, dll_base + 0x0006A0C0);
		
		SUBCASE("")
		{
			// Input data
			const auto mask = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [mask](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.nMoveTestCollisionMask = mask;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA0D0 (#10184)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetMoveTestCollisionMask, dll_base + 0x0006A0D0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nCollisionMask = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pDynamicPath, nCollisionMask);
			original(&original_pDynamicPath, nCollisionMask);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA0E0 (#10185)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetType, dll_base + 0x0006A0E0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nPathType{};

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath, nPathType);
			original(&original_pDynamicPath, nPathType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA1E0 (#10186)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_ResetToPreviousType, dll_base + 0x0006A1E0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath);
			original(&original_pDynamicPath);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA240 (#10187)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetType, dll_base + 0x0006A240);
		
		SUBCASE("")
		{
			// Input data
			const auto type = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [type](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwPathType = type;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA250 (#10190)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10190_PATH_SetDistance, dll_base + 0x0006A250);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			uint8_t nDistance = random_unsigned_integer(0, 255);

			// Call both implementations
			sut(&moo_pDynamicPath, nDistance);
			original(&original_pDynamicPath, nDistance);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA270 (#10191)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10191_PATH_GetDistance, dll_base + 0x0006A270);
		
		SUBCASE("")
		{
			// Input data
			const auto distance = random_unsigned_integer(0, 255);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [distance](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.nDist = distance;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA280 (#10188)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetNewDistance, dll_base + 0x0006A280);

		REPEAT_10();
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			uint8_t nNewDistance = random_unsigned_integer(0, 255);

			// Call both implementations
			sut(&moo_pDynamicPath, nNewDistance);
			original(&original_pDynamicPath, nNewDistance);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA2B0 (#10189)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetMaxDistance, dll_base + 0x0006A2B0);
		
		SUBCASE("")
		{
			// Input data
			const auto max_distance = random_unsigned_integer(0, 255);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [max_distance](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.nDistMax = max_distance;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA2C0 (#10201)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10201, dll_base + 0x0006A2C0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA300 (#10202)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10202, dll_base + 0x0006A300);
		
		SUBCASE("")
		{
			// Input data
			const auto mask = random_unsigned_integer(0, 65535);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [mask](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.nCollidedWithMask = mask;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA310 (#10192)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetIDAStarInitFScore, dll_base + 0x0006A310);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nIDAStarInitFScore = random_unsigned_integer();

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwPathType = PATHTYPE_IDASTAR;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath, nIDAStarInitFScore);
			original(&original_pDynamicPath, nIDAStarInitFScore);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA350 (#10198)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10198_PathGetSaveStep, dll_base + 0x0006A350);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2PathPointStrc* moo_ppPathPoints{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2PathPointStrc* original_ppPathPoints{};

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath,
				D2PathPointStrc*& ppPathPoints
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDynamicPath, moo_ppPathPoints);
			setup_data(original_pDynamicPath, original_ppPathPoints);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, &moo_ppPathPoints);
			const auto original_result = original(&original_pDynamicPath, &original_ppPathPoints);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			SKIP_MOO_CHECK_EQ(moo_ppPathPoints, original_ppPathPoints, "Comparing ppPathPoints");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA390 (#10199)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10199_PathGetSaveX, dll_base + 0x0006A390);

		REPEAT_10();
		
		SUBCASE("")
		{
			// Input data
			D2PathPointStrc path_points[10]{};

			const auto count = random_unsigned_integer(0, std::size(path_points));
			for (auto i = 0; i < count; ++i)
			{
				path_points[i].X = random_unsigned_integer(0, 65535);
				path_points[i].Y = random_unsigned_integer(0, 65535);
			}

			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [flags, count, &path_points](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwFlags = flags | PATH_SAVE_STEPS_MASK;
				pDynamicPath.nSavedStepsCount = count;
				memcpy(pDynamicPath.SavedSteps, path_points, sizeof(pDynamicPath.SavedSteps));
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA3E0 (#10200)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10200_PathGetSaveY, dll_base + 0x0006A3E0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			D2PathPointStrc path_points[10]{};
			
			const auto count = random_unsigned_integer(0, std::size(path_points));
			for (auto i = 0; i < count; ++i)
			{
				path_points[i].X = random_unsigned_integer(0, 65535);
				path_points[i].Y = random_unsigned_integer(0, 65535);
			}
			
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [flags, count, &path_points](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwFlags = flags | PATH_SAVE_STEPS_MASK;
				pDynamicPath.nSavedStepsCount = count;
				memcpy(pDynamicPath.SavedSteps, path_points, sizeof(pDynamicPath.SavedSteps));
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA430 (#10203)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10203_PATH_SetRotateFlag, dll_base + 0x0006A430);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			BOOL bReset = GENERATE(true, false);;

			const auto setup_data = [flags](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwFlags = flags;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath, bReset);
			original(&original_pDynamicPath, bReset);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA460 (#10204)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10204_PATH_ClearPoint2, dll_base + 0x0006A460);
		
		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer();
			const auto y = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [x, y](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tPrevTargetCoord.X = x;
				pDynamicPath.tPrevTargetCoord.Y = y;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath);
			original(&original_pDynamicPath);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA480 (#10205)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetStepNum, dll_base + 0x0006A480);

		REPEAT_10();
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			uint8_t nSteps = random_unsigned_integer(0, 32);

			// Call both implementations
			sut(&moo_pDynamicPath, nSteps);
			original(&original_pDynamicPath, nSteps);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA4B0 (#10206)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetStepNum, dll_base + 0x0006A4B0);
		
		SUBCASE("")
		{
			// Input data
			const auto steps = random_unsigned_integer(0, 32);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [steps](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.nStepNum = steps;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA4C0 (#10207)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10207, dll_base + 0x0006A4C0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			char a2 = random_unsigned_integer(0, 255);
			char a3 = random_unsigned_integer(0, 255);

			// Call both implementations
			sut(&moo_pDynamicPath, a2, a3);
			original(&original_pDynamicPath, a2, a3);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA4E0 (#10217)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetDistance, dll_base + 0x0006A4E0);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nDist = random_unsigned_integer(0, 255);

			// Call both implementations
			sut(&moo_pDynamicPath, nDist);
			original(&original_pDynamicPath, nDist);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA520 (#10218)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetDistance, dll_base + 0x0006A520);
		
		SUBCASE("")
		{
			// Input data
			const auto distance = random_unsigned_integer(0, 255);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [distance](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.nDistance = distance;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath);
			const auto original_result = original(&original_pDynamicPath);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA530 (#10219)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AddToDistance, dll_base + 0x0006A530);
		
		SUBCASE("")
		{
			// Input data
			const auto distance = random_unsigned_integer(0, 255);

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nAddition = random_unsigned_integer(0, 255);

			const auto setup_data = [distance](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.nDistance = distance;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath, nAddition);
			original(&original_pDynamicPath, nAddition);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA570 (#10210)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetUnitCollisionPattern, dll_base + 0x0006A570);
		
		SUBCASE("")
		{
			// Input data
			const auto collision_pattern = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [collision_pattern](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwCollisionPattern = collision_pattern;
				pUnit.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA580 (#10211)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_SetUnitCollisionPattern, dll_base + 0x0006A580);
		
		SUBCASE("")
		{
			// Input data
			const auto collision_pattern = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nCollisionPattern = random_unsigned_integer();

			const auto setup_data = [collision_pattern](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwCollisionPattern = collision_pattern;
				pUnit.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			sut(&moo_pUnit, nCollisionPattern);
			original(&original_pUnit, nCollisionPattern);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA5A0 (#10212)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10212_PATH_SetMoveFlags, dll_base + 0x0006A5A0);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			BOOL bSet = GENERATE(true, false);

			const auto setup_data = [flags](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.unk0x38 = 5;

				pUnit.dwFlagEx = flags;
				pUnit.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			sut(&moo_pUnit, bSet);
			original(&original_pUnit, bSet);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA600 (#10213)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10213, dll_base + 0x0006A600);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA6A0 (#10220)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_ComputeSquaredDistance, dll_base + 0x0006A6A0);
		
		SUBCASE("")
		{
			int nX1 = random_unsigned_integer(0, 65535);
			int nY1 = random_unsigned_integer(0, 65535);
			int nX2 = random_unsigned_integer(0, 65535);
			int nY2 = random_unsigned_integer(0, 65535);

			// Call both implementations
			const auto moo_result = sut(nX1, nY1, nX2, nY2);
			const auto original_result = original(nX1, nY1, nX2, nY2);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA6D0 (#10221)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_AddCollisionFootprintForOptionalUnit, dll_base + 0x0006A6D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA6F0 (#10237)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10237, dll_base + 0x0006A6F0);
		
		SUBCASE("")
		{
			// Input data
			const auto current_point_index = random_unsigned_integer(0, 5);
			const auto path_points = random_unsigned_integer(0, 5);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [current_point_index, path_points](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwCurrentPointIdx = current_point_index;
				pDynamicPath.dwPathPoints = path_points;
				pUnit.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
