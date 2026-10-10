#include <D2CommonTestDefines.h>

#ifdef MISSILE_TESTS

#include <doctest.h>

#include <Windows.h>

#include <array>
#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <memory>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Units/Missile.h>
#include <Units/Player.h>
#include <Units/Units.h>

#include <Calc.h>
#include <D2Combat.h>
#include <D2DataTbls.h>
#include <D2Skills.h>
#include <D2StatList.h>

#include <Fixtures/DataTbls/Fixtures.h>


DYNAMIC_ARRAY_TYPE(D2StatStrc)


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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9F80 (#11116)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_FreeMissileData, dll_base + 0x00079F80);
		const auto [moo_alloc, original_alloc] = make_function_pair(MISSILE_AllocMissileData, dll_base + 0x00079F30);

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

			moo_alloc(&moo_pMissile);
			original_alloc(&original_pMissile);

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
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<SkillsTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FDBA5B0 (#11217)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_CalculateDamageData, dll_base + 0x0007A5B0);

		REPEAT_5();

		SUBCASE("")
		{
			// Input data
			const auto owner_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto origin_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto missile_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				owner_stat_array[i].nLayer = 0;
				owner_stat_array[i].nStat = static_cast<uint16_t>(i);
				owner_stat_array[i].nValue = random_unsigned_integer(0, 100);

				origin_stat_array[i].nLayer = 0;
				origin_stat_array[i].nStat = static_cast<uint16_t>(i);
				origin_stat_array[i].nValue = random_unsigned_integer(0, 100);

				missile_stat_array[i].nLayer = 0;
				missile_stat_array[i].nStat = static_cast<uint16_t>(i);
				missile_stat_array[i].nValue = random_unsigned_integer(0, 100);
			}

			// Barbarians and Assassins are excluded, dual wielding requires an inventory
			const auto owner_class = GENERATE(PCLASS_AMAZON, PCLASS_SORCERESS, PCLASS_NECROMANCER, PCLASS_PALADIN, PCLASS_DRUID);
			const auto has_origin = GENERATE(true, false);
			const auto owner_low_seed = random_unsigned_integer();
			const auto owner_high_seed = random_unsigned_integer();
			const auto origin_low_seed = random_unsigned_integer();
			const auto origin_high_seed = random_unsigned_integer();

			for (auto i = 0; i < missiles_record_count; ++i)
			{
				D2MissileDamageDataStrc moo_pMissileDamageData{};
				D2UnitStrc moo_pOwner{};
				D2StatListExStrc moo_pOwnerStatListEx{};
				const auto moo_pOwnerStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
				D2UnitStrc moo_pOrigin{};
				D2StatListExStrc moo_pOriginStatListEx{};
				const auto moo_pOriginStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
				D2UnitStrc moo_pMissile{};
				D2MissileDataStrc moo_pMissileData{};
				D2StatListExStrc moo_pMissileStatListEx{};
				const auto moo_pMissileStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
				D2MissileDamageDataStrc original_pMissileDamageData{};
				D2UnitStrc original_pOwner{};
				D2StatListExStrc original_pOwnerStatListEx{};
				const auto original_pOwnerStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
				D2UnitStrc original_pOrigin{};
				D2StatListExStrc original_pOriginStatListEx{};
				const auto original_pOriginStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
				D2UnitStrc original_pMissile{};
				D2MissileDataStrc original_pMissileData{};
				D2StatListExStrc original_pMissileStatListEx{};
				const auto original_pMissileStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
				int nLevel = random_unsigned_integer(1, 30);

				const auto setup_data = [&, i, nLevel](
					D2MissileDamageDataStrc& pMissileDamageData,
					D2UnitStrc& pOwner,
					D2StatListExStrc& pOwnerStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pOwnerStat,
					D2UnitStrc& pOrigin,
					D2StatListExStrc& pOriginStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pOriginStat,
					D2UnitStrc& pMissile,
					D2MissileDataStrc& pMissileData,
					D2StatListExStrc& pMissileStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pMissileStat
				) {
					// The output is expected to be cleared by the function
					std::memset(&pMissileDamageData, 0xFF, sizeof(pMissileDamageData));

					pOwner.dwUnitType = UNIT_PLAYER;
					pOwner.dwClassId = owner_class;
					pOwner.pSeed.nLowSeed = owner_low_seed;
					pOwner.pSeed.nHighSeed = owner_high_seed;
					pOwner.pStatListEx = &pOwnerStatListEx;
					pOwnerStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pOwnerStat.get(), owner_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pOwnerStatListEx.FullStats.pStat = pOwnerStat.get();
					pOwnerStatListEx.FullStats.nStatCount = itemstatcost_record_count;
					pOwnerStatListEx.FullStats.nCapacity = itemstatcost_record_count;

					pOrigin.dwUnitType = UNIT_MONSTER;
					pOrigin.pSeed.nLowSeed = origin_low_seed;
					pOrigin.pSeed.nHighSeed = origin_high_seed;
					pOrigin.pStatListEx = &pOriginStatListEx;
					pOriginStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pOriginStat.get(), origin_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pOriginStatListEx.FullStats.pStat = pOriginStat.get();
					pOriginStatListEx.FullStats.nStatCount = itemstatcost_record_count;
					pOriginStatListEx.FullStats.nCapacity = itemstatcost_record_count;

					pMissile.dwUnitType = UNIT_MISSILE;
					pMissile.dwClassId = i;
					pMissile.pMissileData = &pMissileData;
					pMissileData.nLevel = static_cast<int16_t>(nLevel);
					pMissile.pStatListEx = &pMissileStatListEx;
					pMissileStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pMissileStat.get(), missile_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pMissileStatListEx.FullStats.pStat = pMissileStat.get();
					pMissileStatListEx.FullStats.nStatCount = itemstatcost_record_count;
					pMissileStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				};

				setup_data(moo_pMissileDamageData, moo_pOwner, moo_pOwnerStatListEx, moo_pOwnerStat, moo_pOrigin, moo_pOriginStatListEx, moo_pOriginStat, moo_pMissile, moo_pMissileData, moo_pMissileStatListEx, moo_pMissileStat);
				setup_data(original_pMissileDamageData, original_pOwner, original_pOwnerStatListEx, original_pOwnerStat, original_pOrigin, original_pOriginStatListEx, original_pOriginStat, original_pMissile, original_pMissileData, original_pMissileStatListEx, original_pMissileStat);

				// Call both implementations
				sut(&moo_pMissileDamageData, &moo_pOwner, has_origin ? &moo_pOrigin : nullptr, &moo_pMissile, nLevel);
				original(&original_pMissileDamageData, &original_pOwner, has_origin ? &original_pOrigin : nullptr, &original_pMissile, nLevel);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
				MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
				MOO_CHECK_EQ(moo_pOrigin, original_pOrigin, "Comparing pOrigin");
				MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			}
		}

		SUBCASE("invalid input")
		{
			// Input data
			D2MissileDamageDataStrc moo_pMissileDamageData{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pMissile{};
			D2MissileDamageDataStrc original_pMissileDamageData{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pMissile{};
			const auto has_owner = GENERATE(true, false);
			const auto missile_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM);
			int nLevel = random_unsigned_integer(1, 30);

			const auto setup_data = [missile_type](
				D2MissileDamageDataStrc& pMissileDamageData,
				D2UnitStrc& pOwner,
				D2UnitStrc& pMissile
			) {
				// The output is expected to be cleared by the function
				std::memset(&pMissileDamageData, 0xFF, sizeof(pMissileDamageData));

				pOwner.dwUnitType = UNIT_PLAYER;
				pMissile.dwUnitType = missile_type;
			};

			setup_data(moo_pMissileDamageData, moo_pOwner, moo_pMissile);
			setup_data(original_pMissileDamageData, original_pOwner, original_pMissile);

			// Call both implementations
			sut(&moo_pMissileDamageData, has_owner ? &moo_pOwner : nullptr, nullptr, &moo_pMissile, nLevel);
			original(&original_pMissileDamageData, has_owner ? &original_pOwner : nullptr, nullptr, &original_pMissile, nLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDBADF0" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_HasBonusStats, dll_base + 0x0007ADF0);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			// Stats have to be sorted by stat id
			const auto stat_array = std::make_unique<D2StatStrc[]>(2);

			stat_array[0].nLayer = 0;
			stat_array[0].nStat = STAT_ITEM_DEADLYSTRIKE;
			stat_array[0].nValue = random_unsigned_integer(0, 100);
			stat_array[1].nLayer = 0;
			stat_array[1].nStat = STAT_PASSIVE_CRITICAL_STRIKE;
			stat_array[1].nValue = random_unsigned_integer(0, 100);

			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();
			const auto has_item = GENERATE(true, false);

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(2);
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(2);
			D2UnitStrc original_pItem{};

			const auto setup_data = [&stat_array, low_seed, high_seed](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2UnitStrc& pItem
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pSeed.nLowSeed = low_seed;
				pUnit.pSeed.nHighSeed = high_seed;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * 2);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = 2;
				pStatListEx.FullStats.nCapacity = 2;

				// The unit has no weapon mastery, so the item is never inspected
				pItem.dwUnitType = UNIT_ITEM;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pItem);
			setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, has_item ? &moo_pItem : nullptr);
			const auto original_result = original(&original_pUnit, has_item ? &original_pItem : nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDBAED0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_AddStatsToDamage, dll_base + 0x0007AED0);
		
		SUBCASE("STAT_SKILL_POISON_OVERRIDE_LENGTH > 0")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2MissileDamageDataStrc moo_pMissileDamageData{};
			D2UnitStrc moo_pMissile{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2MissileDamageDataStrc original_pMissileDamageData{};
			D2UnitStrc original_pMissile{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			uint8_t nShift = GENERATE(0, 8);

			const auto setup_data = [&stat_array, this](
				D2MissileDamageDataStrc& pMissileDamageData,
				D2UnitStrc& pMissile,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pMissile.dwUnitType = UNIT_MISSILE;
				pMissile.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pMissileDamageData, moo_pMissile, moo_pStatListEx, moo_pStat);
			setup_data(original_pMissileDamageData, original_pMissile, original_pStatListEx, original_pStat);

			// Call both implementations
			sut(&moo_pMissileDamageData, &moo_pMissile, nShift);
			original(&original_pMissileDamageData, &original_pMissile, nShift);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}

		SUBCASE("STAT_SKILL_POISON_OVERRIDE_LENGTH = 0")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			stat_array[STAT_SKILL_POISON_OVERRIDE_LENGTH].nValue = 0;

			D2MissileDamageDataStrc moo_pMissileDamageData{};
			D2UnitStrc moo_pMissile{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2MissileDamageDataStrc original_pMissileDamageData{};
			D2UnitStrc original_pMissile{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			uint8_t nShift = GENERATE(0, 8);

			const auto setup_data = [&stat_array, this](
				D2MissileDamageDataStrc& pMissileDamageData,
				D2UnitStrc& pMissile,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pMissile.dwUnitType = UNIT_MISSILE;
				pMissile.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pMissileDamageData, moo_pMissile, moo_pStatListEx, moo_pStat);
			setup_data(original_pMissileDamageData, original_pMissile, original_pStatListEx, original_pStat);

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
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDBB1B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_CalculateMasteryBonus, dll_base + 0x0007B1B0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(4);

			for (auto i = 0; i < 4; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(STAT_PASSIVE_FIRE_MASTERY + i);
				stat_array[i].nValue = random_unsigned_integer(0, 100);
			}

			D2MissileDamageDataStrc moo_pMissileDamageData{};
			D2UnitStrc moo_pMissile{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(4);
			D2MissileDamageDataStrc original_pMissileDamageData{};
			D2UnitStrc original_pMissile{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(4);
			int nElemType = GENERATE(ELEMTYPE_FIRE, ELEMTYPE_COLD, ELEMTYPE_FREEZE, ELEMTYPE_LTNG, ELEMTYPE_POIS, ELEMTYPE_MAGIC);
			int nSrcDamage = random_unsigned_integer();

			const auto setup_data = [&stat_array](
				D2MissileDamageDataStrc& pMissileDamageData,
				D2UnitStrc& pMissile,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pMissile.dwUnitType = UNIT_MISSILE;
				pMissile.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * 4);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = 4;
				pStatListEx.FullStats.nCapacity = 4;
			};

			setup_data(moo_pMissileDamageData, moo_pMissile, moo_pStatListEx, moo_pStat);
			setup_data(original_pMissileDamageData, original_pMissile, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, nElemType, nSrcDamage);
			const auto original_result = original(&original_pMissile, nElemType, nSrcDamage);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDBB2E0 (#11218)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetDamageStats, dll_base + 0x0007B2E0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			// Stats have to be sorted by stat id and layer
			constexpr auto owner_stat_count = 4;
			const auto owner_stat_array = std::make_unique<D2StatStrc[]>(owner_stat_count);

			for (auto i = 0; i < owner_stat_count; ++i)
			{
				owner_stat_array[i].nLayer = static_cast<uint16_t>(i + 1);
				owner_stat_array[i].nStat = STAT_DAMAGE_VS_MONTYPE;
				owner_stat_array[i].nValue = random_unsigned_integer(1, 100);
			}

			const auto flags_bits = std::array<int32_t, 7>{ 0x1, 0x2, 0x4, 0x100, 0x200, 0x400, 0x800 };
			int32_t flags = 0;
			for (const auto flag : flags_bits)
			{
				if (random_unsigned_integer(0, 1))
				{
					flags |= flag;
				}
			}

			auto damage_values = std::array<int32_t, 30>{};
			for (auto& value : damage_values)
			{
				value = random_unsigned_integer(0, 3) ? random_unsigned_integer(0, 65535) : 0;
			}

			const auto missile_flags = random_unsigned_integer();
			const auto has_owner = GENERATE(true, false);

			D2UnitStrc moo_pOwner{};
			D2StatListExStrc moo_pOwnerStatListEx{};
			const auto moo_pOwnerStat = std::make_unique<D2StatStrc[]>(owner_stat_count);
			D2UnitStrc moo_pMissile{};
			D2MissileDataStrc moo_pMissileData{};
			D2StatListExStrc moo_pMissileStatListEx{};
			D2MissileDamageDataStrc moo_pMissileDamageData{};
			D2UnitStrc original_pOwner{};
			D2StatListExStrc original_pOwnerStatListEx{};
			const auto original_pOwnerStat = std::make_unique<D2StatStrc[]>(owner_stat_count);
			D2UnitStrc original_pMissile{};
			D2MissileDataStrc original_pMissileData{};
			D2StatListExStrc original_pMissileStatListEx{};
			D2MissileDamageDataStrc original_pMissileDamageData{};
			int nLevel = random_unsigned_integer(1, 30);

			const auto setup_data = [owner_stat_count, &owner_stat_array, flags, &damage_values, missile_flags](
				D2UnitStrc& pOwner,
				D2StatListExStrc& pOwnerStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pOwnerStat,
				D2UnitStrc& pMissile,
				D2MissileDataStrc& pMissileData,
				D2StatListExStrc& pMissileStatListEx,
				D2MissileDamageDataStrc& pMissileDamageData
			) {
				pOwner.dwUnitType = UNIT_PLAYER;
				pOwner.pStatListEx = &pOwnerStatListEx;
				pOwnerStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pOwnerStat.get(), owner_stat_array.get(), sizeof(D2StatStrc) * owner_stat_count);
				pOwnerStatListEx.FullStats.pStat = pOwnerStat.get();
				pOwnerStatListEx.FullStats.nStatCount = owner_stat_count;
				pOwnerStatListEx.FullStats.nCapacity = owner_stat_count;

				// The missile starts with an empty stat list, stats are allocated by the function
				pMissile.dwUnitType = UNIT_MISSILE;
				pMissile.pMissileData = &pMissileData;
				pMissileData.fFlags = missile_flags;
				pMissile.pStatListEx = &pMissileStatListEx;
				pMissileStatListEx.dwFlags |= STATLIST_EXTENDED;
				pMissileStatListEx.dwOwnerType = UNIT_MISSILE;

				pMissileDamageData.nFlags = flags;
				std::memcpy(&pMissileDamageData.nMinDamage, damage_values.data(), sizeof(int32_t) * damage_values.size());
			};

			static_assert(sizeof(D2MissileDamageDataStrc) == sizeof(int32_t) * (1 + 30), "Unexpected D2MissileDamageDataStrc layout");

			setup_data(moo_pOwner, moo_pOwnerStatListEx, moo_pOwnerStat, moo_pMissile, moo_pMissileData, moo_pMissileStatListEx, moo_pMissileDamageData);
			setup_data(original_pOwner, original_pOwnerStatListEx, original_pOwnerStat, original_pMissile, original_pMissileData, original_pMissileStatListEx, original_pMissileDamageData);

			// Call both implementations
			sut(has_owner ? &moo_pOwner : nullptr, &moo_pMissile, &moo_pMissileDamageData, nLevel);
			original(has_owner ? &original_pOwner : nullptr, &original_pMissile, &original_pMissileDamageData, nLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");

			// Compare all stats that were added to the missile
			auto moo_stats = DynamicArray<D2StatStrc>{ moo_pMissileStatListEx.Stats.pStat, moo_pMissileStatListEx.Stats.nStatCount };
			auto original_stats = DynamicArray<D2StatStrc>{ original_pMissileStatListEx.Stats.pStat, original_pMissileStatListEx.Stats.nStatCount };
			MOO_CHECK_EQ(moo_stats, original_stats, "Comparing missile stats");

			auto moo_full_stats = DynamicArray<D2StatStrc>{ moo_pMissileStatListEx.FullStats.pStat, moo_pMissileStatListEx.FullStats.nStatCount };
			auto original_full_stats = DynamicArray<D2StatStrc>{ original_pMissileStatListEx.FullStats.pStat, original_pMissileStatListEx.FullStats.nStatCount };
			MOO_CHECK_EQ(moo_full_stats, original_full_stats, "Comparing missile full stats");
		}

		SUBCASE("not a missile")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2MissileDamageDataStrc moo_pMissileDamageData{};
			D2UnitStrc original_pMissile{};
			D2MissileDamageDataStrc original_pMissileDamageData{};
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_ITEM);
			int nLevel = random_unsigned_integer(1, 30);

			const auto setup_data = [unit_type](
				D2UnitStrc& pMissile,
				D2MissileDamageDataStrc& pMissileDamageData
			) {
				pMissile.dwUnitType = unit_type;
				pMissileDamageData.nFlags = 0x1;
				pMissileDamageData.nMinDamage = 1;
			};

			setup_data(moo_pMissile, moo_pMissileDamageData);
			setup_data(original_pMissile, original_pMissileDamageData);

			// Call both implementations
			sut(nullptr, &moo_pMissile, &moo_pMissileDamageData, nLevel);
			original(nullptr, &original_pMissile, &original_pMissileDamageData, nLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
		}
	}
	TEST_CASE_FIXTURE(MissilesTxtFixture<NoopFixture>, "D2Common.0x6FDBB5A0 (#11285)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMinDamage, dll_base + 0x0007B5A0);
		
		SUBCASE("without formula")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				for (const auto level : { -1, 0, 1, 2, 8, 9, 16, 17, 22, 23, 28, 29, 40 })
				{
					// Input data
					D2UnitStrc moo_pMissile{};
					D2MissileDataStrc moo_pMissileData{};
					D2UnitStrc moo_pOwner{};
					D2UnitStrc original_pMissile{};
					D2MissileDataStrc original_pMissileData{};
					D2UnitStrc original_pOwner{};
					const auto missile_level = random_unsigned_integer(0, 40);
					int nMissileId = random_unsigned_integer(0, 1) ? i : -1;
					int nLevel = level;

					const auto setup_data = [i, missile_level](
						D2UnitStrc& pMissile,
						D2MissileDataStrc& pMissileData,
						D2UnitStrc& pOwner
					) {
						pMissile.dwUnitType = UNIT_MISSILE;
						pMissile.dwClassId = i;
						pMissile.pMissileData = &pMissileData;
						pMissileData.nLevel = missile_level;
						pOwner.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pMissile, moo_pMissileData, moo_pOwner);
					setup_data(original_pMissile, original_pMissileData, original_pOwner);

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
		}

		SUBCASE("with formula")
		{
			// Bonus percentage: min(lvl * 10, 100)
			auto formula = std::array<uint8_t, 10>{
				AST_Callback_Param_UInt8, 18,
				AST_Raw_Int8, 10,
				AST_Multipliction,
				AST_Raw_Int8, 100,
				AST_CallbackTable, 0,
				AST_None,
			};

			const auto previous_miss_code = sgptDataTables->pMissCode;
			const auto previous_miss_code_size = sgptDataTables->nMissCodeSize;
			sgptDataTables->pMissCode = reinterpret_cast<FOGASTNodeStrc*>(formula.data());
			sgptDataTables->nMissCodeSize = static_cast<unsigned int>(formula.size());

			for (auto i = 0; i < missiles_record_count; ++i)
			{
				missiles_txt[i].dwDmgSymPerCalc = 0;

				for (const auto level : { 1, 5, 10, 20, 30 })
				{
					// Input data
					D2UnitStrc moo_pMissile{};
					D2MissileDataStrc moo_pMissileData{};
					D2UnitStrc moo_pOwner{};
					D2UnitStrc original_pMissile{};
					D2MissileDataStrc original_pMissileData{};
					D2UnitStrc original_pOwner{};
					int nMissileId = i;
					int nLevel = level;

					const auto setup_data = [i](
						D2UnitStrc& pMissile,
						D2MissileDataStrc& pMissileData,
						D2UnitStrc& pOwner
					) {
						pMissile.dwUnitType = UNIT_MISSILE;
						pMissile.dwClassId = i;
						pMissile.pMissileData = &pMissileData;
						pOwner.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pMissile, moo_pMissileData, moo_pOwner);
					setup_data(original_pMissile, original_pMissileData, original_pOwner);

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

			sgptDataTables->pMissCode = previous_miss_code;
			sgptDataTables->nMissCodeSize = previous_miss_code_size;
		}

		SUBCASE("without missile unit")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				int nMissileId = i;
				int nLevel = random_unsigned_integer(1, 30);

				// Call both implementations
				const auto moo_result = sut(nullptr, nullptr, nMissileId, nLevel);
				const auto original_result = original(nullptr, nullptr, nMissileId, nLevel);
				
				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}

		SUBCASE("not a missile")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc original_pMissile{};
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_ITEM);
			int nMissileId = random_unsigned_integer(0, missiles_record_count - 1);
			int nLevel = random_unsigned_integer(1, 30);

			const auto setup_data = [unit_type](
				D2UnitStrc& pMissile
			) {
				pMissile.dwUnitType = unit_type;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, nullptr, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, nullptr, nMissileId, nLevel);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<NoopFixture>, "D2Common.0x6FDBB710 (#11286)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMaxDamage, dll_base + 0x0007B710);
		
		SUBCASE("without formula")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				for (const auto level : { -1, 0, 1, 2, 8, 9, 16, 17, 22, 23, 28, 29, 40 })
				{
					// Input data
					D2UnitStrc moo_pMissile{};
					D2MissileDataStrc moo_pMissileData{};
					D2UnitStrc moo_pOwner{};
					D2UnitStrc original_pMissile{};
					D2MissileDataStrc original_pMissileData{};
					D2UnitStrc original_pOwner{};
					const auto missile_level = random_unsigned_integer(0, 40);
					int nMissileId = random_unsigned_integer(0, 1) ? i : -1;
					int nLevel = level;

					const auto setup_data = [i, missile_level](
						D2UnitStrc& pMissile,
						D2MissileDataStrc& pMissileData,
						D2UnitStrc& pOwner
					) {
						pMissile.dwUnitType = UNIT_MISSILE;
						pMissile.dwClassId = i;
						pMissile.pMissileData = &pMissileData;
						pMissileData.nLevel = missile_level;
						pOwner.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pMissile, moo_pMissileData, moo_pOwner);
					setup_data(original_pMissile, original_pMissileData, original_pOwner);

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
		}

		SUBCASE("with formula")
		{
			// Bonus percentage: min(lvl * 10, 100)
			auto formula = std::array<uint8_t, 10>{
				AST_Callback_Param_UInt8, 18,
				AST_Raw_Int8, 10,
				AST_Multipliction,
				AST_Raw_Int8, 100,
				AST_CallbackTable, 0,
				AST_None,
			};

			const auto previous_miss_code = sgptDataTables->pMissCode;
			const auto previous_miss_code_size = sgptDataTables->nMissCodeSize;
			sgptDataTables->pMissCode = reinterpret_cast<FOGASTNodeStrc*>(formula.data());
			sgptDataTables->nMissCodeSize = static_cast<unsigned int>(formula.size());

			for (auto i = 0; i < missiles_record_count; ++i)
			{
				missiles_txt[i].dwDmgSymPerCalc = 0;

				for (const auto level : { 1, 5, 10, 20, 30 })
				{
					// Input data
					D2UnitStrc moo_pMissile{};
					D2MissileDataStrc moo_pMissileData{};
					D2UnitStrc moo_pOwner{};
					D2UnitStrc original_pMissile{};
					D2MissileDataStrc original_pMissileData{};
					D2UnitStrc original_pOwner{};
					int nMissileId = i;
					int nLevel = level;

					const auto setup_data = [i](
						D2UnitStrc& pMissile,
						D2MissileDataStrc& pMissileData,
						D2UnitStrc& pOwner
					) {
						pMissile.dwUnitType = UNIT_MISSILE;
						pMissile.dwClassId = i;
						pMissile.pMissileData = &pMissileData;
						pOwner.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pMissile, moo_pMissileData, moo_pOwner);
					setup_data(original_pMissile, original_pMissileData, original_pOwner);

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

			sgptDataTables->pMissCode = previous_miss_code;
			sgptDataTables->nMissCodeSize = previous_miss_code_size;
		}

		SUBCASE("without missile unit")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				int nMissileId = i;
				int nLevel = random_unsigned_integer(1, 30);

				// Call both implementations
				const auto moo_result = sut(nullptr, nullptr, nMissileId, nLevel);
				const auto original_result = original(nullptr, nullptr, nMissileId, nLevel);
				
				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}

		SUBCASE("not a missile")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc original_pMissile{};
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_ITEM);
			int nMissileId = random_unsigned_integer(0, missiles_record_count - 1);
			int nLevel = random_unsigned_integer(1, 30);

			const auto setup_data = [unit_type](
				D2UnitStrc& pMissile
			) {
				pMissile.dwUnitType = unit_type;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, nullptr, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, nullptr, nMissileId, nLevel);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
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
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<NoopFixture>, "D2Common.0x6FDBB8C0 (#11287)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMinElemDamage, dll_base + 0x0007B8C0);
		
		SUBCASE("without formula")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				for (const auto level : { -1, 0, 1, 2, 8, 9, 16, 17, 22, 23, 28, 29, 40 })
				{
					// Input data
					D2UnitStrc moo_pMissile{};
					D2MissileDataStrc moo_pMissileData{};
					D2UnitStrc moo_pOwner{};
					D2UnitStrc original_pMissile{};
					D2MissileDataStrc original_pMissileData{};
					D2UnitStrc original_pOwner{};
					const auto missile_level = random_unsigned_integer(0, 40);
					int nMissileId = random_unsigned_integer(0, 1) ? i : -1;
					int nLevel = level;

					const auto setup_data = [i, missile_level](
						D2UnitStrc& pMissile,
						D2MissileDataStrc& pMissileData,
						D2UnitStrc& pOwner
					) {
						pMissile.dwUnitType = UNIT_MISSILE;
						pMissile.dwClassId = i;
						pMissile.pMissileData = &pMissileData;
						pMissileData.nLevel = missile_level;
						pOwner.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pMissile, moo_pMissileData, moo_pOwner);
					setup_data(original_pMissile, original_pMissileData, original_pOwner);

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
		}

		SUBCASE("with formula")
		{
			// Bonus percentage: min(lvl * 10, 100)
			auto formula = std::array<uint8_t, 10>{
				AST_Callback_Param_UInt8, 18,
				AST_Raw_Int8, 10,
				AST_Multipliction,
				AST_Raw_Int8, 100,
				AST_CallbackTable, 0,
				AST_None,
			};

			const auto previous_miss_code = sgptDataTables->pMissCode;
			const auto previous_miss_code_size = sgptDataTables->nMissCodeSize;
			sgptDataTables->pMissCode = reinterpret_cast<FOGASTNodeStrc*>(formula.data());
			sgptDataTables->nMissCodeSize = static_cast<unsigned int>(formula.size());

			for (auto i = 0; i < missiles_record_count; ++i)
			{
				missiles_txt[i].dwElemDmgSymPerCalc = 0;

				for (const auto level : { 1, 5, 10, 20, 30 })
				{
					// Input data
					D2UnitStrc moo_pMissile{};
					D2MissileDataStrc moo_pMissileData{};
					D2UnitStrc moo_pOwner{};
					D2UnitStrc original_pMissile{};
					D2MissileDataStrc original_pMissileData{};
					D2UnitStrc original_pOwner{};
					int nMissileId = i;
					int nLevel = level;

					const auto setup_data = [i](
						D2UnitStrc& pMissile,
						D2MissileDataStrc& pMissileData,
						D2UnitStrc& pOwner
					) {
						pMissile.dwUnitType = UNIT_MISSILE;
						pMissile.dwClassId = i;
						pMissile.pMissileData = &pMissileData;
						pOwner.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pMissile, moo_pMissileData, moo_pOwner);
					setup_data(original_pMissile, original_pMissileData, original_pOwner);

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

			sgptDataTables->pMissCode = previous_miss_code;
			sgptDataTables->nMissCodeSize = previous_miss_code_size;
		}

		SUBCASE("without missile unit")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				int nMissileId = i;
				int nLevel = random_unsigned_integer(1, 30);

				// Call both implementations
				const auto moo_result = sut(nullptr, nullptr, nMissileId, nLevel);
				const auto original_result = original(nullptr, nullptr, nMissileId, nLevel);
				
				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}

		SUBCASE("not a missile")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc original_pMissile{};
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_ITEM);
			int nMissileId = random_unsigned_integer(0, missiles_record_count - 1);
			int nLevel = random_unsigned_integer(1, 30);

			const auto setup_data = [unit_type](
				D2UnitStrc& pMissile
			) {
				pMissile.dwUnitType = unit_type;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, nullptr, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, nullptr, nMissileId, nLevel);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<NoopFixture>, "D2Common.0x6FDBBA30 (#11288)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMaxElemDamage, dll_base + 0x0007BA30);
		
		SUBCASE("without formula")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				for (const auto level : { -1, 0, 1, 2, 8, 9, 16, 17, 22, 23, 28, 29, 40 })
				{
					// Input data
					D2UnitStrc moo_pMissile{};
					D2MissileDataStrc moo_pMissileData{};
					D2UnitStrc moo_pOwner{};
					D2UnitStrc original_pMissile{};
					D2MissileDataStrc original_pMissileData{};
					D2UnitStrc original_pOwner{};
					const auto missile_level = random_unsigned_integer(0, 40);
					int nMissileId = random_unsigned_integer(0, 1) ? i : -1;
					int nLevel = level;

					const auto setup_data = [i, missile_level](
						D2UnitStrc& pMissile,
						D2MissileDataStrc& pMissileData,
						D2UnitStrc& pOwner
					) {
						pMissile.dwUnitType = UNIT_MISSILE;
						pMissile.dwClassId = i;
						pMissile.pMissileData = &pMissileData;
						pMissileData.nLevel = missile_level;
						pOwner.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pMissile, moo_pMissileData, moo_pOwner);
					setup_data(original_pMissile, original_pMissileData, original_pOwner);

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
		}

		SUBCASE("with formula")
		{
			// Bonus percentage: min(lvl * 10, 100)
			auto formula = std::array<uint8_t, 10>{
				AST_Callback_Param_UInt8, 18,
				AST_Raw_Int8, 10,
				AST_Multipliction,
				AST_Raw_Int8, 100,
				AST_CallbackTable, 0,
				AST_None,
			};

			const auto previous_miss_code = sgptDataTables->pMissCode;
			const auto previous_miss_code_size = sgptDataTables->nMissCodeSize;
			sgptDataTables->pMissCode = reinterpret_cast<FOGASTNodeStrc*>(formula.data());
			sgptDataTables->nMissCodeSize = static_cast<unsigned int>(formula.size());

			for (auto i = 0; i < missiles_record_count; ++i)
			{
				missiles_txt[i].dwElemDmgSymPerCalc = 0;

				for (const auto level : { 1, 5, 10, 20, 30 })
				{
					// Input data
					D2UnitStrc moo_pMissile{};
					D2MissileDataStrc moo_pMissileData{};
					D2UnitStrc moo_pOwner{};
					D2UnitStrc original_pMissile{};
					D2MissileDataStrc original_pMissileData{};
					D2UnitStrc original_pOwner{};
					int nMissileId = i;
					int nLevel = level;

					const auto setup_data = [i](
						D2UnitStrc& pMissile,
						D2MissileDataStrc& pMissileData,
						D2UnitStrc& pOwner
					) {
						pMissile.dwUnitType = UNIT_MISSILE;
						pMissile.dwClassId = i;
						pMissile.pMissileData = &pMissileData;
						pOwner.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pMissile, moo_pMissileData, moo_pOwner);
					setup_data(original_pMissile, original_pMissileData, original_pOwner);

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

			sgptDataTables->pMissCode = previous_miss_code;
			sgptDataTables->nMissCodeSize = previous_miss_code_size;
		}

		SUBCASE("without missile unit")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				int nMissileId = i;
				int nLevel = random_unsigned_integer(1, 30);

				// Call both implementations
				const auto moo_result = sut(nullptr, nullptr, nMissileId, nLevel);
				const auto original_result = original(nullptr, nullptr, nMissileId, nLevel);
				
				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}

		SUBCASE("not a missile")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc original_pMissile{};
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_ITEM);
			int nMissileId = random_unsigned_integer(0, missiles_record_count - 1);
			int nLevel = random_unsigned_integer(1, 30);

			const auto setup_data = [unit_type](
				D2UnitStrc& pMissile
			) {
				pMissile.dwUnitType = unit_type;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, nullptr, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, nullptr, nMissileId, nLevel);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
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
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<NoopFixture>, "D2Common.0x6FDBBC50 (#11290)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetSpecialParamValue, dll_base + 0x0007BC50);

		SUBCASE("")
		{
			for (auto k = 0; k < 30; ++k)
			{
				for (auto j = 0; j < 44; ++j)
				{
					for (auto i = 0; i < missiles_record_count; ++i)
					{
						// Input data
						D2UnitStrc moo_pMissile{};
						D2MissileDataStrc moo_pMissileData{};
						D2UnitStrc moo_pOwner{};
						D2UnitStrc original_pMissile{};
						D2MissileDataStrc original_pMissileData{};
						D2UnitStrc original_pOwner{};
						uint8_t nParamId = j;
						int nMissileId = i;
						int nLevel = k;

						const auto setup_data = [i, k](
							D2UnitStrc& pMissile,
							D2MissileDataStrc& pMissileData,
							D2UnitStrc& pOwner
						) {
							pMissile.dwUnitType = UNIT_MISSILE;
							pMissile.dwClassId = i;
							pMissile.pMissileData = &pMissileData;
							pMissileData.nLevel = static_cast<int16_t>(k);
							pOwner.dwUnitType = UNIT_PLAYER;
						};

						setup_data(moo_pMissile, moo_pMissileData, moo_pOwner);
						setup_data(original_pMissile, original_pMissileData, original_pOwner);

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
			}
		}

		SUBCASE("without missile unit")
		{
			for (auto j = 0; j < 44; ++j)
			{
				for (auto i = 0; i < missiles_record_count; ++i)
				{
					// Input data
					uint8_t nParamId = j;
					int nMissileId = i;
					int nLevel = random_unsigned_integer(0, 30);

					// Call both implementations
					const auto moo_result = sut(nullptr, nullptr, nParamId, nMissileId, nLevel);
					const auto original_result = original(nullptr, nullptr, nParamId, nMissileId, nLevel);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}

		SUBCASE("not a missile")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc original_pMissile{};
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_ITEM);
			uint8_t nParamId = random_unsigned_integer(0, 17);
			int nMissileId = random_unsigned_integer(0, missiles_record_count - 1);
			int nLevel = random_unsigned_integer(1, 30);

			const auto setup_data = [unit_type](
				D2UnitStrc& pMissile
			) {
				pMissile.dwUnitType = unit_type;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, nullptr, nParamId, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, nullptr, nParamId, nMissileId, nLevel);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	TEST_CASE_FIXTURE(MissilesTxtFixture<NoopFixture>, "D2Common.0x6FDBC060")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetCalcParamValue, dll_base + 0x0007C060);

		SUBCASE("")
		{
			for (auto k = 0; k < 30; ++k)
			{
				for (auto j = 0; j < 44; ++j)
				{
					for (auto i = 0; i < missiles_record_count; ++i)
					{
						// Input data
						D2MissileCalcStrc moo_pUserData{};
						D2UnitStrc moo_pMissile{};
						D2MissileDataStrc moo_pMissileData{};
						D2UnitStrc moo_pOwner{};
						D2MissileCalcStrc original_pUserData{};
						D2UnitStrc original_pMissile{};
						D2MissileDataStrc original_pMissileData{};
						D2UnitStrc original_pOwner{};
						int32_t nParamId = j;

						const auto setup_data = [i, k](
							D2MissileCalcStrc& pUserData,
							D2UnitStrc& pMissile,
							D2MissileDataStrc& pMissileData,
							D2UnitStrc& pOwner
						) {
							pUserData.pMissile = &pMissile;
							pUserData.pOwner = &pOwner;
							pUserData.nMissileId = i;
							pUserData.nMissileLevel = k;
							pMissile.dwUnitType = UNIT_MISSILE;
							pMissile.dwClassId = i;
							pMissile.pMissileData = &pMissileData;
							pMissileData.nLevel = static_cast<int16_t>(k);
							pOwner.dwUnitType = UNIT_PLAYER;
						};

						setup_data(moo_pUserData, moo_pMissile, moo_pMissileData, moo_pOwner);
						setup_data(original_pUserData, original_pMissile, original_pMissileData, original_pOwner);

						// Call both implementations
						const auto moo_result = sut(nParamId, &moo_pUserData);
						const auto original_result = original(nParamId, &original_pUserData);

						// Compare return values
						MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pUserData, original_pUserData, "Comparing pUserData");
					}
				}
			}
		}

		SUBCASE("without user data")
		{
			// Input data
			int32_t nParamId = random_unsigned_integer(0, 43);

			// Call both implementations
			const auto moo_result = sut(nParamId, nullptr);
			const auto original_result = original(nParamId, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
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
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();

			int nMin = random_unsigned_integer(0, 65535);
			int nMax = random_unsigned_integer(0, 65535);
			int nUnused = random_unsigned_integer();

			D2UnkMissileCalcStrc moo_pUserData{};
			D2UnkMissileCalcStrc original_pUserData{};

			const auto setup_data = [low_seed, high_seed](
				D2UnkMissileCalcStrc& pCalc
			) {
				pCalc.pSeed.nLowSeed = low_seed;
				pCalc.pSeed.nHighSeed = high_seed;
			};

			setup_data(moo_pUserData);
			setup_data(original_pUserData);

			// Call both implementations
			const auto moo_result = sut(nMin, nMax, nUnused, &moo_pUserData);
			const auto original_result = original(nMin, nMax, nUnused, &original_pUserData);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUserData, original_pUserData, "Comparing pUserData");
		}

		SUBCASE("without user data")
		{
			int nMin = random_unsigned_integer(0, 65535);
			int nMax = random_unsigned_integer(0, 65535);
			int nUnused = random_unsigned_integer();

			// Call both implementations
			const auto moo_result = sut(nMin, nMax, nUnused, nullptr);
			const auto original_result = original(nMin, nMax, nUnused, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(ExperienceTxtFixture<SkillsTxtFixture<MissilesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>>, "D2Common.0x6FDBC120" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetSpecialParamValueForSkillMissile, dll_base + 0x0007C120);

		// Params 26-37 and 43-48 depend on SkillDesc.txt which is not loaded
		std::vector<int> param_ids;
		for (auto nParamId = 0; nParamId <= 72; ++nParamId)
		{
			if ((nParamId >= 26 && nParamId <= 37) || (nParamId >= 43 && nParamId <= 48))
			{
				continue;
			}
			param_ids.push_back(nParamId);
		}

		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = random_unsigned_integer(0, 100);
			}

			const auto has_skill = GENERATE(0, 1);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (const auto nParamId : param_ids)
				{
					D2MissileCalcStrc moo_pUserData{};
					D2UnitStrc moo_pOwner{};
					D2StatListExStrc moo_pStatListEx{};
					const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
					D2SkillListStrc moo_pSkillList{};
					D2SkillStrc moo_pSkill{};
					D2MissileCalcStrc original_pUserData{};
					D2UnitStrc original_pOwner{};
					D2StatListExStrc original_pStatListEx{};
					const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
					D2SkillListStrc original_pSkillList{};
					D2SkillStrc original_pSkill{};
					int nSkillId = i;
					int nUnused = random_unsigned_integer();
					const auto skill_level = static_cast<int32_t>(random_unsigned_integer(1, 20));

					const auto setup_data = [this, i, &stat_array, has_skill, skill_level](
						D2MissileCalcStrc& pUserData,
						D2UnitStrc& pOwner,
						D2StatListExStrc& pStatListEx,
						const std::unique_ptr<D2StatStrc[]>& pStat,
						D2SkillListStrc& pSkillList,
						D2SkillStrc& pSkill
					) {
						pUserData.pOwner = &pOwner;
						pOwner.dwUnitType = UNIT_PLAYER;
						pOwner.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
						pStatListEx.FullStats.pStat = pStat.get();
						pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
						pStatListEx.FullStats.nCapacity = itemstatcost_record_count;

						if (has_skill)
						{
							// Not a native skill (nOwnerGUID != -1), so no bonus skill levels are computed
							pSkill.pSkillsTxt = &skills_txt[i];
							pSkill.nSkillLevel = skill_level;
							pSkill.nOwnerGUID = 0;
							pSkillList.pFirstSkill = &pSkill;
							pOwner.pSkills = &pSkillList;
						}
					};

					setup_data(moo_pUserData, moo_pOwner, moo_pStatListEx, moo_pStat, moo_pSkillList, moo_pSkill);
					setup_data(original_pUserData, original_pOwner, original_pStatListEx, original_pStat, original_pSkillList, original_pSkill);

					// Call both implementations
					const auto moo_result = sut(nSkillId, nParamId, nUnused, &moo_pUserData);
					const auto original_result = original(nSkillId, nParamId, nUnused, &original_pUserData);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUserData, original_pUserData, "Comparing pUserData");
				}
			}
		}

		SUBCASE("without owner")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (const auto nParamId : param_ids)
				{
					// Input data
					D2MissileCalcStrc moo_pUserData{};
					D2MissileCalcStrc original_pUserData{};
					int nSkillId = i;
					int nUnused = random_unsigned_integer();

					// Call both implementations
					const auto moo_result = sut(nSkillId, nParamId, nUnused, &moo_pUserData);
					const auto original_result = original(nSkillId, nParamId, nUnused, &original_pUserData);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUserData, original_pUserData, "Comparing pUserData");
				}
			}
		}

		SUBCASE("without user data")
		{
			// Input data
			int nSkillId = random_unsigned_integer(0, skills_record_count - 1);
			int nParamId = random_unsigned_integer(0, 72);
			int nUnused = random_unsigned_integer();

			// Call both implementations
			const auto moo_result = sut(nSkillId, nParamId, nUnused, nullptr);
			const auto original_result = original(nSkillId, nParamId, nUnused, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	TEST_CASE_FIXTURE(MissilesTxtFixture<NoopFixture>, "D2Common.0x6FDBC170 (#11284)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_EvaluateMissileFormula, dll_base + 0x0007C170);

		// Compiled formulas, each one is 10 bytes long
		// The rand() and skill() callbacks are not used: rand() reads a seed that D2MissileCalcStrc does not have
		auto formulas = std::array<uint8_t, 40>{
			// 0: min(lvl * 10, 100)
			AST_Callback_Param_UInt8, 18,
			AST_Raw_Int8, 10,
			AST_Multipliction,
			AST_Raw_Int8, 100,
			AST_CallbackTable, 0,
			AST_None,
			// 10: max(par28, par0) + 3
			AST_Callback_Param_UInt8, 28,
			AST_Callback_Param_UInt8, 0,
			AST_CallbackTable, 1,
			AST_Raw_Int8, 3,
			AST_Addition,
			AST_None,
			// 20: (lvl > 5) * 42
			AST_Callback_Param_UInt8, 18,
			AST_Raw_Int8, 5,
			AST_GreaterThan,
			AST_Raw_Int8, 42,
			AST_Multipliction,
			AST_None,
			AST_None,
			// 30: par29 * 1000 / 7
			AST_Callback_Param_UInt8, 29,
			AST_Raw_Int16, 0xE8, 0x03,
			AST_Multipliction,
			AST_Raw_Int8, 7,
			AST_Division,
			AST_None,
		};

		const auto previous_miss_code = sgptDataTables->pMissCode;
		const auto previous_miss_code_size = sgptDataTables->nMissCodeSize;
		sgptDataTables->pMissCode = reinterpret_cast<FOGASTNodeStrc*>(formulas.data());
		sgptDataTables->nMissCodeSize = static_cast<unsigned int>(formulas.size());

		SUBCASE("")
		{
			// 0 = missile, 1 = no missile unit, 2 = not a missile
			const auto missile_mode = GENERATE(0, 1, 2);

			for (auto i = 0; i < missiles_record_count; ++i)
			{
				for (const auto nCalc : { 0u, 10u, 20u, 30u, 40u, 1000u })
				{
					// Input data
					D2UnitStrc moo_pMissile{};
					D2MissileDataStrc moo_pMissileData{};
					D2UnitStrc moo_pOwner{};
					D2UnitStrc original_pMissile{};
					D2MissileDataStrc original_pMissileData{};
					D2UnitStrc original_pOwner{};
					const auto missile_level = random_unsigned_integer(0, 30);
					int nMissileId = random_unsigned_integer(0, 1) ? i : -1;
					int nLevel = random_unsigned_integer(0, 1) ? static_cast<int>(random_unsigned_integer(0, 30)) : -1;

					const auto setup_data = [i, missile_mode, missile_level](
						D2UnitStrc& pMissile,
						D2MissileDataStrc& pMissileData,
						D2UnitStrc& pOwner
					) {
						pMissile.dwUnitType = missile_mode == 2 ? UNIT_MONSTER : UNIT_MISSILE;
						pMissile.dwClassId = i;
						pMissile.pMissileData = &pMissileData;
						pMissileData.nLevel = missile_level;
						pOwner.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pMissile, moo_pMissileData, moo_pOwner);
					setup_data(original_pMissile, original_pMissileData, original_pOwner);

					// Call both implementations
					const auto moo_result = sut(missile_mode == 1 ? nullptr : &moo_pMissile, &moo_pOwner, nCalc, nMissileId, nLevel);
					const auto original_result = original(missile_mode == 1 ? nullptr : &original_pMissile, &original_pOwner, nCalc, nMissileId, nLevel);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
					MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
				}
			}
		}

		SUBCASE("without compiled formulas")
		{
			sgptDataTables->pMissCode = nullptr;

			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc original_pMissile{};
			unsigned int nCalc = 0;
			int nMissileId = random_unsigned_integer(0, missiles_record_count - 1);
			int nLevel = random_unsigned_integer(1, 30);

			const auto setup_data = [nMissileId](
				D2UnitStrc& pMissile
			) {
				pMissile.dwUnitType = UNIT_MISSILE;
				pMissile.dwClassId = nMissileId;
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, nullptr, nCalc, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, nullptr, nCalc, nMissileId, nLevel);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}

		sgptDataTables->pMissCode = previous_miss_code;
		sgptDataTables->nMissCodeSize = previous_miss_code_size;
	}
}

#endif
