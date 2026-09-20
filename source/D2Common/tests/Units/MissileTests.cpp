#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Units/Missile.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>


template<class Fixture>
struct MissileFixture : Fixture
{
	D2UnitStrc moo_pMissile{};
	D2UnitStrc original_pMissile{};
	D2MissileDataStrc moo_pMissileData{};
	D2MissileDataStrc original_pMissileData{};

	MissileFixture()
	{
		setup(moo_pMissile, moo_pMissileData);
		setup(original_pMissile, original_pMissileData);
	}

private:
	void setup(D2UnitStrc& pMissile, D2MissileDataStrc& pMissileData)
	{
		pMissile.dwUnitType = UNIT_MISSILE;
		pMissile.pMissileData = &pMissileData;
	}
};


TEST_SUITE("MissileTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9F30 (#11115)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_AllocMissileData, dll_base + 0x00079F30);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc original_pMissile{};

			const auto setup_data = [](
				D2UnitStrc& pMissile
			) {
				pMissile.dwUnitType = UNIT_MISSILE;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			sut(&moo_pMissile);
			original(&original_pMissile);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9F80 (#11116)" * doctest::skip("Not really testable"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_FreeMissileData, dll_base + 0x00079F80);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc original_pMissile{};

			const auto setup_data = [](
				D2UnitStrc& pMissile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			sut(&moo_pMissile);
			original(&original_pMissile);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDB9FC0 (#11117)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetFlags, dll_base + 0x00079FC0);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			const auto setup_data = [flags](
				D2UnitStrc& pMissile
			) {
				pMissile.pMissileData->fFlags = flags;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDB9FE0 (#11118)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetFlags, dll_base + 0x00079FE0);
		
		SUBCASE("")
		{
			// Input data
			uint32_t dwFlags = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pMissile, dwFlags);
			original(&original_pMissile, dwFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA000 (#11119)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetLevel, dll_base + 0x0007A000);
		
		SUBCASE("")
		{
			// Input data
			uint16_t nLevel = random_unsigned_integer(0, 65535);

			// Call both implementations
			sut(&moo_pMissile, nLevel);
			original(&original_pMissile, nLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA020 (#11120)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetLevel, dll_base + 0x0007A020);
		
		SUBCASE("")
		{
			// Input data
			const auto level = random_unsigned_integer();

			const auto setup_data = [level](
				D2UnitStrc& pMissile
			) {
				pMissile.pMissileData->nLevel = level;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA040 (#11126)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetSkill, dll_base + 0x0007A040);
		
		SUBCASE("")
		{
			// Input data
			int nSkill = random_unsigned_integer(0, 65535);

			// Call both implementations
			sut(&moo_pMissile, nSkill);
			original(&original_pMissile, nSkill);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA080 (#11127)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetSkill, dll_base + 0x0007A080);
		
		SUBCASE("")
		{
			// Input data
			const auto skill_id = random_unsigned_integer();

			const auto setup_data = [skill_id](
				D2UnitStrc& pMissile
			) {
				pMissile.pMissileData->nSkill = skill_id;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA0A0 (#11121)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetTotalFrames, dll_base + 0x0007A0A0);
		
		SUBCASE("")
		{
			// Input data
			int nTotalFrames = random_unsigned_integer(0, 65535);

			// Call both implementations
			sut(&moo_pMissile, nTotalFrames);
			original(&original_pMissile, nTotalFrames);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA0E0 (#11122)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetTotalFrames, dll_base + 0x0007A0E0);
		
		SUBCASE("")
		{
			// Input data
			const auto total_frames = random_unsigned_integer();

			const auto setup_data = [total_frames](
				D2UnitStrc& pMissile
			) {
				pMissile.pMissileData->nTotalFrames = total_frames;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA100 (#11123)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetCurrentFrame, dll_base + 0x0007A100);
		
		SUBCASE("")
		{
			// Input data
			int nCurrentFrame = random_unsigned_integer(0, 65535);

			// Call both implementations
			sut(&moo_pMissile, nCurrentFrame);
			original(&original_pMissile, nCurrentFrame);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA140 (#11124)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetCurrentFrame, dll_base + 0x0007A140);
		
		SUBCASE("")
		{
			// Input data
			const auto current_frame = random_unsigned_integer();

			const auto setup_data = [current_frame](
				D2UnitStrc& pMissile
			) {
				pMissile.pMissileData->nCurrentFrame = current_frame;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA160 (#11125)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetRemainingFrames, dll_base + 0x0007A160);
		
		SUBCASE("")
		{
			// Input data
			const auto total_frames = random_unsigned_integer();
			const auto current_frame = random_unsigned_integer(0, total_frames);

			const auto setup_data = [total_frames, current_frame](
				D2UnitStrc& pMissile
			) {
				pMissile.pMissileData->nTotalFrames = total_frames;
				pMissile.pMissileData->nCurrentFrame = current_frame;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA190 (#11128)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetClassId, dll_base + 0x0007A190);
		
		SUBCASE("")
		{
			// Input data
			const auto class_id = random_unsigned_integer();

			const auto setup_data = [class_id](
				D2UnitStrc& pMissile
			) {
				pMissile.dwClassId = class_id;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<MissileFixture<NoopFixture>>, "D2Common.0x6FDBA1B0 (#11129)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetOwner, dll_base + 0x0007A1B0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				const auto owner_type = random_unsigned_integer();
				const auto owner_id = random_unsigned_integer();

				D2UnitStrc moo_pOwner{};
				D2UnitStrc original_pOwner{};

				const auto setup_data = [i, owner_type, owner_id](
					D2UnitStrc& pMissile,
					D2UnitStrc& pOwner
				) {
					pMissile.dwClassId = i;
					pOwner.dwUnitType = owner_type;
					pOwner.dwUnitId = owner_id;
				};

				setup_data(moo_pMissile, moo_pOwner);
				setup_data(original_pMissile, original_pOwner);

				// Call both implementations
				sut(&moo_pMissile, &moo_pOwner);
				original(&original_pMissile, &original_pOwner);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
				MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<MissileFixture<NoopFixture>>, "D2Common.0x6FDBA230 (#11130)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_CheckUnitIfOwner, dll_base + 0x0007A230);
		
		SUBCASE("is owner")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				const auto unit_id = random_unsigned_integer(1, 255);

				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [unit_id](
					D2UnitStrc& pMissile,
					D2UnitStrc& pUnit
				) {
					pMissile.pMissileData->nOwnerType = UNIT_PLAYER;
					pMissile.pMissileData->dwOwnerGUID = unit_id;
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwUnitId = unit_id;
				};

				setup_data(moo_pMissile, moo_pUnit);
				setup_data(original_pMissile, original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pMissile, &moo_pUnit);
				const auto original_result = original(&original_pMissile, &original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("is not owner")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				const auto unit_id = random_unsigned_integer(1, 255);

				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [unit_id](
					D2UnitStrc& pMissile,
					D2UnitStrc& pUnit
				) {
					pMissile.pMissileData->nOwnerType = UNIT_PLAYER;
					pMissile.pMissileData->dwOwnerGUID = unit_id;
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwUnitId = unit_id + 1;
				};

				setup_data(moo_pMissile, moo_pUnit);
				setup_data(original_pMissile, original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pMissile, &moo_pUnit);
				const auto original_result = original(&original_pMissile, &original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA2B0 (#11131)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetStreamMissile, dll_base + 0x0007A2B0);
		
		SUBCASE("")
		{
			// Input data
			uint16_t nStreamMissile = random_unsigned_integer(0, 65535);

			// Call both implementations
			sut(&moo_pMissile, nStreamMissile);
			original(&original_pMissile, nStreamMissile);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA2D0 (#11132)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetStreamMissile, dll_base + 0x0007A2D0);
		
		SUBCASE("")
		{
			// Input data
			const auto stream_missile = random_unsigned_integer();

			const auto setup_data = [stream_missile](
				D2UnitStrc& pMissile
			) {
				pMissile.pMissileData->nStreamMissile = stream_missile;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA300 (#11133)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetStreamRange, dll_base + 0x0007A300);
		
		SUBCASE("")
		{
			// Input data
			short nStreamRange = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pMissile, nStreamRange);
			original(&original_pMissile, nStreamRange);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA320 (#11134)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetStreamRange, dll_base + 0x0007A320);
		
		SUBCASE("")
		{
			// Input data
			const auto stream_range = random_unsigned_integer(0, 65535);

			const auto setup_data = [stream_range](
				D2UnitStrc& pMissile
			) {
				pMissile.pMissileData->nStreamRange = stream_range;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<MissileFixture<NoopFixture>>, "D2Common.0x6FDBA340 (#11135)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetHitClass, dll_base + 0x0007A340);
		
		SUBCASE("")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				const auto setup_data = [i](
					D2UnitStrc& pMissile
				) {
					pMissile.dwClassId = i;
				};

				setup_data(moo_pMissile);
				setup_data(original_pMissile);

				// Call both implementations
				const auto moo_result = sut(&moo_pMissile);
				const auto original_result = original(&original_pMissile);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA390 (#11136)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetActivateFrame, dll_base + 0x0007A390);
		
		SUBCASE("")
		{
			// Input data
			int nActivateFrame = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pMissile, nActivateFrame);
			original(&original_pMissile, nActivateFrame);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA3D0 (#11137)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetActivateFrame, dll_base + 0x0007A3D0);
		
		SUBCASE("")
		{
			// Input data
			const auto activate_frame = random_unsigned_integer(0, 65535);

			const auto setup_data = [activate_frame](
				D2UnitStrc& pMissile
			) {
				pMissile.pMissileData->nActivateFrame = activate_frame;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA3F0 (#11138)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetAnimSpeed, dll_base + 0x0007A3F0);
		
		SUBCASE("")
		{
			// Input data
			const auto anim_speed = random_unsigned_integer(0, 65535);

			const auto setup_data = [anim_speed](
				D2UnitStrc& pMissile
			) {
				pMissile.wAnimSpeed = anim_speed;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA410 (#11139)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetAnimSpeed, dll_base + 0x0007A410);
		
		SUBCASE("")
		{
			// Input data
			int nAnimSpeed = random_unsigned_integer(0, 65535);

			// Call both implementations
			sut(&moo_pMissile, nAnimSpeed);
			original(&original_pMissile, nAnimSpeed);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA450")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetStream, dll_base + 0x0007A450);
		
		SUBCASE("")
		{
			// Input data
			const auto value = random_unsigned_integer();

			D2MissileStreamStrc moo_pStream{};
			D2MissileStreamStrc original_pStream{};

			const auto setup_data = [value](
				D2UnitStrc& pMissile,
				D2MissileStreamStrc& pStream
			) {
				pStream.unk0x04 = value;
			};

			setup_data(moo_pMissile, moo_pStream);
			setup_data(original_pMissile, original_pStream);

			// Call both implementations
			sut(&moo_pMissile, &moo_pStream);
			original(&original_pMissile, &original_pStream);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pStream, original_pStream, "Comparing pStream");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA470")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetStream, dll_base + 0x0007A470);
		
		SUBCASE("")
		{
			// Input data
			const auto value = random_unsigned_integer();

			D2MissileStreamStrc moo_pStream{};
			D2MissileStreamStrc original_pStream{};

			const auto setup_data = [value](
				D2UnitStrc& pMissile,
				D2MissileStreamStrc& pStream
			) {
				pMissile.pMissileData->pStream = &pStream;
				pStream.unk0x04 = value;
			};

			setup_data(moo_pMissile, moo_pStream);
			setup_data(original_pMissile, original_pStream);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA490 (#11140)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetTargetX, dll_base + 0x0007A490);
		
		SUBCASE("")
		{
			// Input data
			int nTargetX = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pMissile, nTargetX);
			original(&original_pMissile, nTargetX);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA4B0 (#11141)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetTargetX, dll_base + 0x0007A4B0);
		
		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer(0, 65535);

			const auto setup_data = [x](
				D2UnitStrc& pMissile
			) {
				pMissile.pMissileData->pTargetCoords.nX = x;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA4D0 (#11142)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetTargetY, dll_base + 0x0007A4D0);
		
		SUBCASE("")
		{
			// Input data
			int nTargetY = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pMissile, nTargetY);
			original(&original_pMissile, nTargetY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA4F0 (#11143)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetTargetY, dll_base + 0x0007A4F0);
		
		SUBCASE("")
		{
			// Input data
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [y](
				D2UnitStrc& pMissile
			) {
				pMissile.pMissileData->pTargetCoords.nY = y;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA510 (#11144)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetHomeType, dll_base + 0x0007A510);
		
		SUBCASE("")
		{
			// Input data
			const auto target_type = random_unsigned_integer();
			const auto target_id = random_unsigned_integer();

			D2UnitStrc moo_pTarget{};
			D2UnitStrc original_pTarget{};

			const auto setup_data = [target_type, target_id](
				D2UnitStrc& pMissile,
				D2UnitStrc& pTarget
			) {
				pTarget.dwUnitType = target_type;
				pTarget.dwUnitId = target_id;
			};

			setup_data(moo_pMissile, moo_pTarget);
			setup_data(original_pMissile, original_pTarget);

			// Call both implementations
			sut(&moo_pMissile, &moo_pTarget);
			original(&original_pMissile, &original_pTarget);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(MissileFixture<NoopFixture>, "D2Common.0x6FDBA550 (#11145)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetHomeType, dll_base + 0x0007A550);
		
		SUBCASE("")
		{
			// Input data
			const auto home_type = random_unsigned_integer();
			const auto home_id = random_unsigned_integer();

			int moo_nHomeType{};
			D2UnitGUID moo_nHomeGUID{};
			int original_nHomeType{};
			D2UnitGUID original_nHomeGUID{};

			const auto setup_data = [home_type, home_id](
				D2UnitStrc& pMissile,
				int& nHomeType,
				D2UnitGUID& nHomeGUID
			) {
				pMissile.pMissileData->nHomeType = home_type;
				pMissile.pMissileData->dwHomeGUID = home_id;
			};

			setup_data(moo_pMissile, moo_nHomeType, moo_nHomeGUID);
			setup_data(original_pMissile, original_nHomeType, original_nHomeGUID);

			// Call both implementations
			sut(&moo_pMissile, &moo_nHomeType, &moo_nHomeGUID);
			original(&original_pMissile, &original_nHomeType, &original_nHomeGUID);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_nHomeType, original_nHomeType, "Comparing nHomeType");
			MOO_CHECK_EQ(moo_nHomeGUID, original_nHomeGUID, "Comparing nHomeGUID");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA5B0 (#11217)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_CalculateDamageData, dll_base + 0x0007A5B0);
		
		SUBCASE("")
		{
			// Input data
			D2MissileDamageDataStrc moo_pMissileDamageData{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pOrigin{};
			D2UnitStrc moo_pMissile{};
			D2MissileDamageDataStrc original_pMissileDamageData{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pOrigin{};
			D2UnitStrc original_pMissile{};
			int nLevel{};

			const auto setup_data = [](
				D2MissileDamageDataStrc& pMissileDamageData,
				D2UnitStrc& pOwner,
				D2UnitStrc& pOrigin,
				D2UnitStrc& pMissile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissileDamageData, moo_pOwner, moo_pOrigin, moo_pMissile);
			setup_data(original_pMissileDamageData, original_pOwner, original_pOrigin, original_pMissile);

			// Call both implementations
			sut(&moo_pMissileDamageData, &moo_pOwner, &moo_pOrigin, &moo_pMissile, nLevel);
			original(&original_pMissileDamageData, &original_pOwner, &original_pOrigin, &original_pMissile, nLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			MOO_CHECK_EQ(moo_pOrigin, original_pOrigin, "Comparing pOrigin");
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBADF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_HasBonusStats, dll_base + 0x0007ADF0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pItem);
			setup_data(original_pUnit, original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pItem);
			const auto original_result = original(&original_pUnit, &original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBAED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_AddStatsToDamage, dll_base + 0x0007AED0);
		
		SUBCASE("")
		{
			// Input data
			D2MissileDamageDataStrc moo_pMissileDamageData{};
			D2UnitStrc moo_pMissile{};
			D2MissileDamageDataStrc original_pMissileDamageData{};
			D2UnitStrc original_pMissile{};
			uint8_t nShift{};

			const auto setup_data = [](
				D2MissileDamageDataStrc& pMissileDamageData,
				D2UnitStrc& pMissile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissileDamageData, moo_pMissile);
			setup_data(original_pMissileDamageData, original_pMissile);

			// Call both implementations
			sut(&moo_pMissileDamageData, &moo_pMissile, nShift);
			original(&original_pMissileDamageData, &original_pMissile, nShift);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB060")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_CalculateFinalDamage, dll_base + 0x0007B060);
		
		SUBCASE("")
		{
			// Input data
			const auto fire_min_damage = random_unsigned_integer(0, 65535);
			const auto fire_max_damage = random_unsigned_integer(0, 65535);
			const auto light_min_damage = random_unsigned_integer(0, 65535);
			const auto light_max_damage = random_unsigned_integer(0, 65535);
			const auto magic_min_damage = random_unsigned_integer(0, 65535);
			const auto magic_max_damage = random_unsigned_integer(0, 65535);
			const auto cold_min_damage = random_unsigned_integer(0, 65535);
			const auto cold_max_damage = random_unsigned_integer(0, 65535);
			const auto cold_length = random_unsigned_integer(0, 65535);
			const auto poison_min_damage = random_unsigned_integer(0, 65535);
			const auto poison_max_damage = random_unsigned_integer(0, 65535);
			const auto poison_count = random_unsigned_integer(0, 65535);
			const auto life_drain_min_damage = random_unsigned_integer(0, 65535);
			const auto mana_drain_min_damage = random_unsigned_integer(0, 65535);
			const auto burning_min = random_unsigned_integer(0, 65535);
			const auto burning_max = random_unsigned_integer(0, 65535);
			const auto burn_length = random_unsigned_integer(0, 65535);

			D2MissileDamageDataStrc moo_pMissileDamageData{};
			D2MissileDamageDataStrc original_pMissileDamageData{};
			int nSrcDamage = GENERATE(4, 8, 16, 32, 64, 128, 256, 512, 1024);

			const auto setup_data = [fire_min_damage, fire_max_damage, light_min_damage, light_max_damage, magic_min_damage, magic_max_damage, cold_min_damage, cold_max_damage, cold_length, poison_min_damage, poison_max_damage, poison_count, life_drain_min_damage, mana_drain_min_damage, burning_min, burning_max, burn_length](
				D2MissileDamageDataStrc& pMissileDamageData
			) {
				pMissileDamageData.nFireMinDamage = fire_min_damage;
				pMissileDamageData.nFireMaxDamage = fire_max_damage;
				pMissileDamageData.nLightMinDamage = light_min_damage;
				pMissileDamageData.nLightMaxDamage = light_max_damage;
				pMissileDamageData.nMagicMinDamage = magic_min_damage;
				pMissileDamageData.nMagicMaxDamage = magic_max_damage;
				pMissileDamageData.nColdMinDamage = cold_min_damage;
				pMissileDamageData.nColdMaxDamage = cold_max_damage;
				pMissileDamageData.nColdLength = cold_length;
				pMissileDamageData.nPoisonMinDamage = poison_min_damage;
				pMissileDamageData.nPoisonMaxDamage = poison_max_damage;
				pMissileDamageData.nPoisonCount = poison_count;
				pMissileDamageData.nLifeDrainMinDamage = life_drain_min_damage;
				pMissileDamageData.nManaDrainMinDamage = mana_drain_min_damage;
				pMissileDamageData.nBurningMin = burning_min;
				pMissileDamageData.nBurningMax = burning_max;
				pMissileDamageData.nBurnLength = burn_length;
			};

			setup_data(moo_pMissileDamageData);
			setup_data(original_pMissileDamageData);

			// Call both implementations
			sut(&moo_pMissileDamageData, nSrcDamage);
			original(&original_pMissileDamageData, nSrcDamage);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB1B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_CalculateMasteryBonus, dll_base + 0x0007B1B0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nElemType{};
			int nSrcDamage{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nElemType, nSrcDamage);
			const auto original_result = original(&original_pUnit, nElemType, nSrcDamage);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB2E0 (#11218)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetDamageStats, dll_base + 0x0007B2E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pMissile{};
			D2MissileDamageDataStrc moo_pMissileDamageData{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pMissile{};
			D2MissileDamageDataStrc original_pMissileDamageData{};
			int nLevel{};

			const auto setup_data = [](
				D2UnitStrc& pOwner,
				D2UnitStrc& pMissile,
				D2MissileDamageDataStrc& pMissileDamageData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOwner, moo_pMissile, moo_pMissileDamageData);
			setup_data(original_pOwner, original_pMissile, original_pMissileDamageData);

			// Call both implementations
			sut(&moo_pOwner, &moo_pMissile, &moo_pMissileDamageData, nLevel);
			original(&original_pOwner, &original_pMissile, &original_pMissileDamageData, nLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB5A0 (#11285)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMinDamage, dll_base + 0x0007B5A0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc original_pMissile{};
			D2UnitStrc original_pOwner{};
			int nMissileId{};
			int nLevel{};

			const auto setup_data = [](
				D2UnitStrc& pMissile,
				D2UnitStrc& pOwner
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissile, moo_pOwner);
			setup_data(original_pMissile, original_pOwner);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nMissileId, nLevel);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB710 (#11286)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMaxDamage, dll_base + 0x0007B710);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc original_pMissile{};
			D2UnitStrc original_pOwner{};
			int nMissileId{};
			int nLevel{};

			const auto setup_data = [](
				D2UnitStrc& pMissile,
				D2UnitStrc& pOwner
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissile, moo_pOwner);
			setup_data(original_pMissile, original_pOwner);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nMissileId, nLevel);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<NoopFixture>, "D2Common.0x6FDBB880 (#11289)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetElemTypeFromMissileId, dll_base + 0x0007B880);
		
		SUBCASE("")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				int nMissileId = i;

				// Call both implementations
				const auto moo_result = sut(nMissileId);
				const auto original_result = original(nMissileId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB8C0 (#11287)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMinElemDamage, dll_base + 0x0007B8C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc original_pMissile{};
			D2UnitStrc original_pOwner{};
			int nMissileId{};
			int nLevel{};

			const auto setup_data = [](
				D2UnitStrc& pMissile,
				D2UnitStrc& pOwner
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissile, moo_pOwner);
			setup_data(original_pMissile, original_pOwner);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nMissileId, nLevel);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBBA30 (#11288)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMaxElemDamage, dll_base + 0x0007BA30);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc original_pMissile{};
			D2UnitStrc original_pOwner{};
			int nMissileId{};
			int nLevel{};

			const auto setup_data = [](
				D2UnitStrc& pMissile,
				D2UnitStrc& pOwner
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissile, moo_pOwner);
			setup_data(original_pMissile, original_pOwner);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nMissileId, nLevel);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<NoopFixture>, "D2Common.0x6FDBBBA0 (#11221)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetElementalLength, dll_base + 0x0007BBA0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pMissile{};
				D2UnitStrc original_pMissile{};
				int nUnused = random_unsigned_integer();
				int nMissileId = i;
				int nLevel = random_unsigned_integer(1, 30);

				// Call both implementations
				const auto moo_result = sut(nUnused, &moo_pMissile, nMissileId, nLevel);
				const auto original_result = original(nUnused, &original_pMissile, nMissileId, nLevel);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBBC50 (#11290)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetSpecialParamValue, dll_base + 0x0007BC50);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc original_pMissile{};
			D2UnitStrc original_pOwner{};
			uint8_t nParamId{};
			int nMissileId{};
			int nLevel{};

			const auto setup_data = [](
				D2UnitStrc& pMissile,
				D2UnitStrc& pOwner
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissile, moo_pOwner);
			setup_data(original_pMissile, original_pOwner);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nParamId, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nParamId, nMissileId, nLevel);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetCalcParamValue, dll_base + 0x0007C060);
		
		SUBCASE("")
		{
			int32_t nParamId{};
			void* moo_pUserData = nullptr;
			void* original_pUserData = nullptr;

			// Call both implementations
			const auto moo_result = sut(nParamId, moo_pUserData);
			const auto original_result = original(nParamId, original_pUserData);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUserData, original_pUserData, "Comparing pUserData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC080")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMinimum, dll_base + 0x0007C080);
		
		SUBCASE("")
		{
			int a1 = random_unsigned_integer();
			int a2 = random_unsigned_integer();
			int a3 = random_unsigned_integer();

			// Call both implementations
			const auto moo_result = sut(a1, a2, a3, nullptr);
			const auto original_result = original(a1, a2, a3, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC090")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMaximum, dll_base + 0x0007C090);
		
		SUBCASE("")
		{
			int a1 = random_unsigned_integer();
			int a2 = random_unsigned_integer();
			int a3 = random_unsigned_integer();

			// Call both implementations
			const auto moo_result = sut(a1, a2, a3, nullptr);
			const auto original_result = original(a1, a2, a3, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC0A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetRandomNumberInRange, dll_base + 0x0007C0A0);
		
		SUBCASE("")
		{
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();

			int nMin = random_unsigned_integer(0, 65535);
			int nMax = random_unsigned_integer(0, 65535);
			int nUnused = random_unsigned_integer();

			D2UnkMissileCalcStrc moo_pUserData{};
			D2SeedStrc moo_pSeed{};
			D2UnkMissileCalcStrc original_pUserData{};
			D2SeedStrc original_pSeed{};

			const auto setup_data = [low_seed, high_seed](
				D2UnkMissileCalcStrc& pCalc,
				D2SeedStrc& pSeed
			) {
				pCalc.pSeed.nLowSeed = low_seed;
				pCalc.pSeed.nHighSeed = high_seed;
			};

			// Call both implementations
			const auto moo_result = sut(nMin, nMax, nUnused, &moo_pUserData);
			const auto original_result = original(nMin, nMax, nUnused, &original_pUserData);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUserData, original_pUserData, "Comparing pUserData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetSpecialParamValueForSkillMissile, dll_base + 0x0007C120);
		
		SUBCASE("")
		{
			int nSkillId{};
			int nParamId{};
			int nUnused{};
			void* moo_pUserData = nullptr;
			void* original_pUserData = nullptr;

			// Call both implementations
			const auto moo_result = sut(nSkillId, nParamId, nUnused, moo_pUserData);
			const auto original_result = original(nSkillId, nParamId, nUnused, original_pUserData);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUserData, original_pUserData, "Comparing pUserData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC170 (#11284)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_EvaluateMissileFormula, dll_base + 0x0007C170);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc original_pMissile{};
			D2UnitStrc original_pOwner{};
			unsigned int nCalc{};
			int nMissileId{};
			int nLevel{};

			const auto setup_data = [](
				D2UnitStrc& pMissile,
				D2UnitStrc& pOwner
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissile, moo_pOwner);
			setup_data(original_pMissile, original_pOwner);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nCalc, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nCalc, nMissileId, nLevel);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
}
