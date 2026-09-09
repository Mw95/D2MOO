#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Environment.h>
#include <Drlg/D2DrlgDrlg.h>


TEST_SUITE("D2EnvironmentTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D8E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_AllocDrlgEnvironment, dll_base + 0x0004D8E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			const auto moo_result = sut(moo_pMemPool);
			const auto original_result = original(original_pMemPool);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D970" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_UpdateLightIntensity, dll_base + 0x0004D970);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgEnvironmentStrc pEnvironment{};
				
				return std::tuple{ pEnvironment };
			};
			
			// Input data
			auto [moo_pEnvironment] = setup_data();
			auto [original_pEnvironment] = setup_data();
			int nLevelId{};
			int nAct{};

			// Call both implementations
			sut(&moo_pEnvironment, nLevelId, nAct);
			original(&original_pEnvironment, nLevelId, nAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEnvironment, original_pEnvironment, "Comparing pEnvironment");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8DAC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_UpdateLightColor, dll_base + 0x0004DAC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgEnvironmentStrc pEnvironment{};
				
				return std::tuple{ pEnvironment };
			};
			
			// Input data
			auto [moo_pEnvironment] = setup_data();
			auto [original_pEnvironment] = setup_data();
			int nAct{};

			// Call both implementations
			sut(&moo_pEnvironment, nAct);
			original(&original_pEnvironment, nAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEnvironment, original_pEnvironment, "Comparing pEnvironment");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8DC00 (#10923)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_UpdatePeriodOfDay, dll_base + 0x0004DC00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pAct, pRoom };
			};
			
			// Input data
			auto [moo_pAct, moo_pRoom] = setup_data();
			auto [original_pAct, original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, &moo_pRoom);
			const auto original_result = original(&original_pAct, &original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8DC70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_UpdateTicks, dll_base + 0x0004DC70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgEnvironmentStrc pEnvironment{};
				
				return std::tuple{ pEnvironment };
			};
			
			// Input data
			auto [moo_pEnvironment] = setup_data();
			auto [original_pEnvironment] = setup_data();
			int nActNo{};

			// Call both implementations
			sut(&moo_pEnvironment, nActNo);
			original(&original_pEnvironment, nActNo);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pEnvironment, original_pEnvironment, "Comparing pEnvironment");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8DD60 (#10924)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_UpdateCycleIndex, dll_base + 0x0004DD60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();
			int nActNo{};

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nActNo);
			const auto original_result = original(&original_pAct, nActNo);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8DDD0 (#10927)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_GetLightColorFromAct, dll_base + 0x0004DDD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				uint8_t pRed{};
				uint8_t pGreen{};
				uint8_t pBlue{};
				
				return std::tuple{ pAct, pRed, pGreen, pBlue };
			};
			
			// Input data
			auto [moo_pAct, moo_pRed, moo_pGreen, moo_pBlue] = setup_data();
			auto [original_pAct, original_pRed, original_pGreen, original_pBlue] = setup_data();

			// Call both implementations
			sut(&moo_pAct, &moo_pRed, &moo_pGreen, &moo_pBlue);
			original(&original_pAct, &original_pRed, &original_pGreen, &original_pBlue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pRed, original_pRed, "Comparing pRed");
			SKIP_MOO_CHECK_EQ(moo_pGreen, original_pGreen, "Comparing pGreen");
			SKIP_MOO_CHECK_EQ(moo_pBlue, original_pBlue, "Comparing pBlue");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8DE00 (#10926)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_GetIntensityFromAct, dll_base + 0x0004DE00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8DE20 (#10933)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_GetPeriodOfDayFromAct, dll_base + 0x0004DE20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				int pBaseTime{};
				
				return std::tuple{ pAct, pBaseTime };
			};
			
			// Input data
			auto [moo_pAct, moo_pBaseTime] = setup_data();
			auto [original_pAct, original_pBaseTime] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, &moo_pBaseTime);
			const auto original_result = original(&original_pAct, &original_pBaseTime);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pBaseTime, original_pBaseTime, "Comparing pBaseTime");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8DE70 (#10928)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_GetUnusedMember, dll_base + 0x0004DE70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8DE90 (#10929)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_NextEnvCycle, dll_base + 0x0004DE90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pAct, pRoom };
			};
			
			// Input data
			auto [moo_pAct, moo_pRoom] = setup_data();
			auto [original_pAct, original_pRoom] = setup_data();

			// Call both implementations
			sut(&moo_pAct, &moo_pRoom);
			original(&original_pAct, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8DF30 (#10930)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_GetCycleIndexFromAct, dll_base + 0x0004DF30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8DF40 (#10932)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_InitializeEnvironment, dll_base + 0x0004DF40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pAct, pRoom };
			};
			
			// Input data
			auto [moo_pAct, moo_pRoom] = setup_data();
			auto [original_pAct, original_pRoom] = setup_data();
			int nIndex{};
			int nTicks{};
			BOOL bEclipse{};

			// Call both implementations
			sut(&moo_pAct, &moo_pRoom, nIndex, nTicks, bEclipse);
			original(&original_pAct, &original_pRoom, nIndex, nTicks, bEclipse);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E080 (#10931)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_GetCycleIndex_Ticks_EclipseFromAct, dll_base + 0x0004E080);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				int pCycleIndex{};
				int pTicks{};
				BOOL pEclipse{};
				
				return std::tuple{ pAct, pCycleIndex, pTicks, pEclipse };
			};
			
			// Input data
			auto [moo_pAct, moo_pCycleIndex, moo_pTicks, moo_pEclipse] = setup_data();
			auto [original_pAct, original_pCycleIndex, original_pTicks, original_pEclipse] = setup_data();

			// Call both implementations
			sut(&moo_pAct, &moo_pCycleIndex, &moo_pTicks, &moo_pEclipse);
			original(&original_pAct, &original_pCycleIndex, &original_pTicks, &original_pEclipse);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pCycleIndex, original_pCycleIndex, "Comparing pCycleIndex");
			SKIP_MOO_CHECK_EQ(moo_pTicks, original_pTicks, "Comparing pTicks");
			SKIP_MOO_CHECK_EQ(moo_pEclipse, original_pEclipse, "Comparing pEclipse");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E0B0 (#10925)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_GetStatistics, dll_base + 0x0004E0B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				float pCos{};
				float pLast{};
				float pSin{};
				int a5{};
				
				return std::tuple{ pAct, pCos, pLast, pSin, a5 };
			};
			
			// Input data
			auto [moo_pAct, moo_pCos, moo_pLast, moo_pSin, moo_a5] = setup_data();
			auto [original_pAct, original_pCos, original_pLast, original_pSin, original_a5] = setup_data();

			// Call both implementations
			sut(&moo_pAct, &moo_pCos, &moo_pLast, &moo_pSin, &moo_a5);
			original(&original_pAct, &original_pCos, &original_pLast, &original_pSin, &original_a5);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pCos, original_pCos, "Comparing pCos");
			SKIP_MOO_CHECK_EQ(moo_pLast, original_pLast, "Comparing pLast");
			SKIP_MOO_CHECK_EQ(moo_pSin, original_pSin, "Comparing pSin");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E0F0 (#10934)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_GetTimeRateFromAct, dll_base + 0x0004E0F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E100 (#10935)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_SetNextTimeRate, dll_base + 0x0004E100);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pAct, pRoom };
			};
			
			// Input data
			auto [moo_pAct, moo_pRoom] = setup_data();
			auto [original_pAct, original_pRoom] = setup_data();

			// Call both implementations
			sut(&moo_pAct, &moo_pRoom);
			original(&original_pAct, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E1B0 (#10936)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_TaintedSunBegin, dll_base + 0x0004E1B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			sut(&moo_pAct);
			original(&original_pAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E1E0 (#10937)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ENVIRONMENT_TaintedSunEnd, dll_base + 0x0004E1E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			sut(&moo_pAct);
			original(&original_pAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
}
