#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Units/Missile.h>
#include <Units/Units.h>


TEST_SUITE("MissileTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9F30 (#11115)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_AllocMissileData, dll_base + 0x00079F30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			sut(&moo_pMissile);
			original(&original_pMissile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9F80 (#11116)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_FreeMissileData, dll_base + 0x00079F80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			sut(&moo_pMissile);
			original(&original_pMissile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9FC0 (#11117)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetFlags, dll_base + 0x00079FC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9FE0 (#11118)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetFlags, dll_base + 0x00079FE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			uint32_t dwFlags{};

			// Call both implementations
			sut(&moo_pMissile, dwFlags);
			original(&original_pMissile, dwFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA000 (#11119)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetLevel, dll_base + 0x0007A000);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			uint16_t nLevel{};

			// Call both implementations
			sut(&moo_pMissile, nLevel);
			original(&original_pMissile, nLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA020 (#11120)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetLevel, dll_base + 0x0007A020);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA040 (#11126)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetSkill, dll_base + 0x0007A040);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			int nSkill{};

			// Call both implementations
			sut(&moo_pMissile, nSkill);
			original(&original_pMissile, nSkill);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA080 (#11127)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetSkill, dll_base + 0x0007A080);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA0A0 (#11121)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetTotalFrames, dll_base + 0x0007A0A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			int nTotalFrames{};

			// Call both implementations
			sut(&moo_pMissile, nTotalFrames);
			original(&original_pMissile, nTotalFrames);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA0E0 (#11122)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetTotalFrames, dll_base + 0x0007A0E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA100 (#11123)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetCurrentFrame, dll_base + 0x0007A100);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			int nCurrentFrame{};

			// Call both implementations
			sut(&moo_pMissile, nCurrentFrame);
			original(&original_pMissile, nCurrentFrame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA140 (#11124)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetCurrentFrame, dll_base + 0x0007A140);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA160 (#11125)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetRemainingFrames, dll_base + 0x0007A160);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA190 (#11128)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetClassId, dll_base + 0x0007A190);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA1B0 (#11129)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetOwner, dll_base + 0x0007A1B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				D2UnitStrc pOwner{};
				
				return std::tuple{ pMissile, pOwner };
			};
			
			// Input data
			auto [moo_pMissile, moo_pOwner] = setup_data();
			auto [original_pMissile, original_pOwner] = setup_data();

			// Call both implementations
			sut(&moo_pMissile, &moo_pOwner);
			original(&original_pMissile, &original_pOwner);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA230 (#11130)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_CheckUnitIfOwner, dll_base + 0x0007A230);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA2B0 (#11131)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetStreamMissile, dll_base + 0x0007A2B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			uint16_t nStreamMissile{};

			// Call both implementations
			sut(&moo_pMissile, nStreamMissile);
			original(&original_pMissile, nStreamMissile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA2D0 (#11132)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetStreamMissile, dll_base + 0x0007A2D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA300 (#11133)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetStreamRange, dll_base + 0x0007A300);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			short nStreamRange{};

			// Call both implementations
			sut(&moo_pMissile, nStreamRange);
			original(&original_pMissile, nStreamRange);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA320 (#11134)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetStreamRange, dll_base + 0x0007A320);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA340 (#11135)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetHitClass, dll_base + 0x0007A340);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA390 (#11136)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetActivateFrame, dll_base + 0x0007A390);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			int nActivateFrame{};

			// Call both implementations
			sut(&moo_pMissile, nActivateFrame);
			original(&original_pMissile, nActivateFrame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA3D0 (#11137)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetActivateFrame, dll_base + 0x0007A3D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA3F0 (#11138)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetAnimSpeed, dll_base + 0x0007A3F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA410 (#11139)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetAnimSpeed, dll_base + 0x0007A410);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			int nAnimSpeed{};

			// Call both implementations
			sut(&moo_pMissile, nAnimSpeed);
			original(&original_pMissile, nAnimSpeed);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetStream, dll_base + 0x0007A450);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				D2MissileStreamStrc pStream{};
				
				return std::tuple{ pMissile, pStream };
			};
			
			// Input data
			auto [moo_pMissile, moo_pStream] = setup_data();
			auto [original_pMissile, original_pStream] = setup_data();

			// Call both implementations
			sut(&moo_pMissile, &moo_pStream);
			original(&original_pMissile, &original_pStream);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pStream, original_pStream, "Comparing pStream");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA470" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetStream, dll_base + 0x0007A470);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA490 (#11140)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetTargetX, dll_base + 0x0007A490);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			int nTargetX{};

			// Call both implementations
			sut(&moo_pMissile, nTargetX);
			original(&original_pMissile, nTargetX);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA4B0 (#11141)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetTargetX, dll_base + 0x0007A4B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA4D0 (#11142)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetTargetY, dll_base + 0x0007A4D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			int nTargetY{};

			// Call both implementations
			sut(&moo_pMissile, nTargetY);
			original(&original_pMissile, nTargetY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA4F0 (#11143)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetTargetY, dll_base + 0x0007A4F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile);
			const auto original_result = original(&original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA510 (#11144)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetHomeType, dll_base + 0x0007A510);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pMissile, pTarget };
			};
			
			// Input data
			auto [moo_pMissile, moo_pTarget] = setup_data();
			auto [original_pMissile, original_pTarget] = setup_data();

			// Call both implementations
			sut(&moo_pMissile, &moo_pTarget);
			original(&original_pMissile, &original_pTarget);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA550 (#11145)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetHomeType, dll_base + 0x0007A550);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				int nHomeType{};
				D2UnitGUID nHomeGUID{};
				
				return std::tuple{ pMissile, nHomeType, nHomeGUID };
			};
			
			// Input data
			auto [moo_pMissile, moo_nHomeType, moo_nHomeGUID] = setup_data();
			auto [original_pMissile, original_nHomeType, original_nHomeGUID] = setup_data();

			// Call both implementations
			sut(&moo_pMissile, &moo_nHomeType, &moo_nHomeGUID);
			original(&original_pMissile, &original_nHomeType, &original_nHomeGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_nHomeType, original_nHomeType, "Comparing nHomeType");
			SKIP_MOO_CHECK_EQ(moo_nHomeGUID, original_nHomeGUID, "Comparing nHomeGUID");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBA5B0 (#11217)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_CalculateDamageData, dll_base + 0x0007A5B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2MissileDamageDataStrc pMissileDamageData{};
				D2UnitStrc pOwner{};
				D2UnitStrc pOrigin{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissileDamageData, pOwner, pOrigin, pMissile };
			};
			
			// Input data
			auto [moo_pMissileDamageData, moo_pOwner, moo_pOrigin, moo_pMissile] = setup_data();
			auto [original_pMissileDamageData, original_pOwner, original_pOrigin, original_pMissile] = setup_data();
			int nLevel{};

			// Call both implementations
			sut(&moo_pMissileDamageData, &moo_pOwner, &moo_pOrigin, &moo_pMissile, nLevel);
			original(&original_pMissileDamageData, &original_pOwner, &original_pOrigin, &original_pMissile, nLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pOrigin, original_pOrigin, "Comparing pOrigin");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBADF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_HasBonusStats, dll_base + 0x0007ADF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pUnit, pItem };
			};
			
			// Input data
			auto [moo_pUnit, moo_pItem] = setup_data();
			auto [original_pUnit, original_pItem] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pItem);
			const auto original_result = original(&original_pUnit, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBAED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_AddStatsToDamage, dll_base + 0x0007AED0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2MissileDamageDataStrc pMissileDamageData{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissileDamageData, pMissile };
			};
			
			// Input data
			auto [moo_pMissileDamageData, moo_pMissile] = setup_data();
			auto [original_pMissileDamageData, original_pMissile] = setup_data();
			uint8_t nShift{};

			// Call both implementations
			sut(&moo_pMissileDamageData, &moo_pMissile, nShift);
			original(&original_pMissileDamageData, &original_pMissile, nShift);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_CalculateFinalDamage, dll_base + 0x0007B060);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2MissileDamageDataStrc pMissileDamageData{};
				
				return std::tuple{ pMissileDamageData };
			};
			
			// Input data
			auto [moo_pMissileDamageData] = setup_data();
			auto [original_pMissileDamageData] = setup_data();
			int nSrcDamage{};

			// Call both implementations
			sut(&moo_pMissileDamageData, nSrcDamage);
			original(&original_pMissileDamageData, nSrcDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB1B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_CalculateMasteryBonus, dll_base + 0x0007B1B0);
		
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
			int nElemType{};
			int nSrcDamage{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nElemType, nSrcDamage);
			const auto original_result = original(&original_pUnit, nElemType, nSrcDamage);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB2E0 (#11218)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_SetDamageStats, dll_base + 0x0007B2E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pOwner{};
				D2UnitStrc pMissile{};
				D2MissileDamageDataStrc pMissileDamageData{};
				
				return std::tuple{ pOwner, pMissile, pMissileDamageData };
			};
			
			// Input data
			auto [moo_pOwner, moo_pMissile, moo_pMissileDamageData] = setup_data();
			auto [original_pOwner, original_pMissile, original_pMissileDamageData] = setup_data();
			int nLevel{};

			// Call both implementations
			sut(&moo_pOwner, &moo_pMissile, &moo_pMissileDamageData, nLevel);
			original(&original_pOwner, &original_pMissile, &original_pMissileDamageData, nLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pMissileDamageData, original_pMissileDamageData, "Comparing pMissileDamageData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB5A0 (#11285)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMinDamage, dll_base + 0x0007B5A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				D2UnitStrc pOwner{};
				
				return std::tuple{ pMissile, pOwner };
			};
			
			// Input data
			auto [moo_pMissile, moo_pOwner] = setup_data();
			auto [original_pMissile, original_pOwner] = setup_data();
			int nMissileId{};
			int nLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nMissileId, nLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB710 (#11286)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMaxDamage, dll_base + 0x0007B710);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				D2UnitStrc pOwner{};
				
				return std::tuple{ pMissile, pOwner };
			};
			
			// Input data
			auto [moo_pMissile, moo_pOwner] = setup_data();
			auto [original_pMissile, original_pOwner] = setup_data();
			int nMissileId{};
			int nLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nMissileId, nLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB880 (#11289)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetElemTypeFromMissileId, dll_base + 0x0007B880);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nMissileId{};

			// Call both implementations
			const auto moo_result = sut(nMissileId);
			const auto original_result = original(nMissileId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBB8C0 (#11287)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMinElemDamage, dll_base + 0x0007B8C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				D2UnitStrc pOwner{};
				
				return std::tuple{ pMissile, pOwner };
			};
			
			// Input data
			auto [moo_pMissile, moo_pOwner] = setup_data();
			auto [original_pMissile, original_pOwner] = setup_data();
			int nMissileId{};
			int nLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nMissileId, nLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBBA30 (#11288)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMaxElemDamage, dll_base + 0x0007BA30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				D2UnitStrc pOwner{};
				
				return std::tuple{ pMissile, pOwner };
			};
			
			// Input data
			auto [moo_pMissile, moo_pOwner] = setup_data();
			auto [original_pMissile, original_pOwner] = setup_data();
			int nMissileId{};
			int nLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nMissileId, nLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBBBA0 (#11221)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetElementalLength, dll_base + 0x0007BBA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			int nUnused{};
			int nMissileId{};
			int nLevel{};

			// Call both implementations
			const auto moo_result = sut(nUnused, &moo_pMissile, nMissileId, nLevel);
			const auto original_result = original(nUnused, &original_pMissile, nMissileId, nLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBBC50 (#11290)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetSpecialParamValue, dll_base + 0x0007BC50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				D2UnitStrc pOwner{};
				
				return std::tuple{ pMissile, pOwner };
			};
			
			// Input data
			auto [moo_pMissile, moo_pOwner] = setup_data();
			auto [original_pMissile, original_pOwner] = setup_data();
			uint8_t nParamId{};
			int nMissileId{};
			int nLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nParamId, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nParamId, nMissileId, nLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetCalcParamValue, dll_base + 0x0007C060);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nParamId{};
			void* moo_pUserData = nullptr;
			void* original_pUserData = nullptr;

			// Call both implementations
			const auto moo_result = sut(nParamId, moo_pUserData);
			const auto original_result = original(nParamId, original_pUserData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUserData, original_pUserData, "Comparing pUserData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMinimum, dll_base + 0x0007C080);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int a1{};
			int a2{};
			int a3{};
			void* moo_pUserData = nullptr;
			void* original_pUserData = nullptr;

			// Call both implementations
			const auto moo_result = sut(a1, a2, a3, moo_pUserData);
			const auto original_result = original(a1, a2, a3, original_pUserData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUserData, original_pUserData, "Comparing pUserData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetMaximum, dll_base + 0x0007C090);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int a1{};
			int a2{};
			int a3{};
			void* moo_pUserData = nullptr;
			void* original_pUserData = nullptr;

			// Call both implementations
			const auto moo_result = sut(a1, a2, a3, moo_pUserData);
			const auto original_result = original(a1, a2, a3, original_pUserData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUserData, original_pUserData, "Comparing pUserData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC0A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetRandomNumberInRange, dll_base + 0x0007C0A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nMin{};
			int nMax{};
			int nUnused{};
			void* moo_pUserData = nullptr;
			void* original_pUserData = nullptr;

			// Call both implementations
			const auto moo_result = sut(nMin, nMax, nUnused, moo_pUserData);
			const auto original_result = original(nMin, nMax, nUnused, original_pUserData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUserData, original_pUserData, "Comparing pUserData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILE_GetSpecialParamValueForSkillMissile, dll_base + 0x0007C120);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nSkillId{};
			int nParamId{};
			int nUnused{};
			void* moo_pUserData = nullptr;
			void* original_pUserData = nullptr;

			// Call both implementations
			const auto moo_result = sut(nSkillId, nParamId, nUnused, moo_pUserData);
			const auto original_result = original(nSkillId, nParamId, nUnused, original_pUserData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				D2UnitStrc pOwner{};
				
				return std::tuple{ pMissile, pOwner };
			};
			
			// Input data
			auto [moo_pMissile, moo_pOwner] = setup_data();
			auto [original_pMissile, original_pOwner] = setup_data();
			unsigned int nCalc{};
			int nMissileId{};
			int nLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pMissile, &moo_pOwner, nCalc, nMissileId, nLevel);
			const auto original_result = original(&original_pMissile, &original_pOwner, nCalc, nMissileId, nLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
}
