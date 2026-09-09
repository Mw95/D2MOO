#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgOutPlace.h>


TEST_SUITE("D2DrlgOutPlaceTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80480" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_BuildKurast, dll_base + 0x00040480);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD806A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_InitAct3OutdoorLevel, dll_base + 0x000406A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD80750, dll_base + 0x00040750);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();
			int nVertexId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, nVertexId);
			const auto original_result = original(&original_pLevel, nVertexId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80BE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD80BE0, dll_base + 0x00040BE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int a1{};
			int a2{};
			int a3{};

			// Call both implementations
			const auto moo_result = sut(a1, a2, a3);
			const auto original_result = original(a1, a2, a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD80C10, dll_base + 0x00040C10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int a1{};
			int a2{};
			int a3{};
			int a4{};
			int a5{};

			// Call both implementations
			const auto moo_result = sut(a1, a2, a3, a4, a5);
			const auto original_result = original(a1, a2, a3, a4, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80C80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_SetBlankBorderGridCells, dll_base + 0x00040C80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80DA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_SetOutGridLinkFlags, dll_base + 0x00040DA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80E10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_PlaceAct1245OutdoorBorders, dll_base + 0x00040E10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81330" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81330, dll_base + 0x00041330);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData);
			const auto original_result = original(&original_pLevelLinkData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81380" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81380, dll_base + 0x00041380);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData);
			const auto original_result = original(&original_pLevelLinkData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81430, dll_base + 0x00041430);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgCoordStrc pDrlgCoord1{};
				D2DrlgCoordStrc pDrlgCoord2{};
				
				return std::tuple{ pDrlgCoord1, pDrlgCoord2 };
			};
			
			// Input data
			auto [moo_pDrlgCoord1, moo_pDrlgCoord2] = setup_data();
			auto [original_pDrlgCoord1, original_pDrlgCoord2] = setup_data();
			int a3{};
			int a4{};

			// Call both implementations
			sut(&moo_pDrlgCoord1, &moo_pDrlgCoord2, a3, a4);
			original(&original_pDrlgCoord1, &original_pDrlgCoord2, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord1, original_pDrlgCoord1, "Comparing pDrlgCoord1");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord2, original_pDrlgCoord2, "Comparing pDrlgCoord2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81530" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81530, dll_base + 0x00041530);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData);
			const auto original_result = original(&original_pLevelLinkData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD815E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD815E0, dll_base + 0x000415E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgCoordStrc pDrlgCoord1{};
				D2DrlgCoordStrc pDrlgCoord2{};
				
				return std::tuple{ pDrlgCoord1, pDrlgCoord2 };
			};
			
			// Input data
			auto [moo_pDrlgCoord1, moo_pDrlgCoord2] = setup_data();
			auto [original_pDrlgCoord1, original_pDrlgCoord2] = setup_data();
			int a3{};
			int a4{};

			// Call both implementations
			sut(&moo_pDrlgCoord1, &moo_pDrlgCoord2, a3, a4);
			original(&original_pDrlgCoord1, &original_pDrlgCoord2, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord1, original_pDrlgCoord1, "Comparing pDrlgCoord1");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord2, original_pDrlgCoord2, "Comparing pDrlgCoord2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81720" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81720, dll_base + 0x00041720);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData);
			const auto original_result = original(&original_pLevelLinkData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81850, dll_base + 0x00041850);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgCoordStrc pDrlgCoord1{};
				D2DrlgCoordStrc pDrlgCoord2{};
				
				return std::tuple{ pDrlgCoord1, pDrlgCoord2 };
			};
			
			// Input data
			auto [moo_pDrlgCoord1, moo_pDrlgCoord2] = setup_data();
			auto [original_pDrlgCoord1, original_pDrlgCoord2] = setup_data();
			int a3{};
			int a4{};

			// Call both implementations
			sut(&moo_pDrlgCoord1, &moo_pDrlgCoord2, a3, a4);
			original(&original_pDrlgCoord1, &original_pDrlgCoord2, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord1, original_pDrlgCoord1, "Comparing pDrlgCoord1");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord2, original_pDrlgCoord2, "Comparing pDrlgCoord2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81950" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81950, dll_base + 0x00041950);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData);
			const auto original_result = original(&original_pLevelLinkData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81AD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81AD0, dll_base + 0x00041AD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData);
			const auto original_result = original(&original_pLevelLinkData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81B30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81B30, dll_base + 0x00041B30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData);
			const auto original_result = original(&original_pLevelLinkData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81BF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81BF0, dll_base + 0x00041BF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData);
			const auto original_result = original(&original_pLevelLinkData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81CA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81CA0, dll_base + 0x00041CA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData);
			const auto original_result = original(&original_pLevelLinkData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81D60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_CreateLevelConnections, dll_base + 0x00041D60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();
			uint8_t nActNo{};

			// Call both implementations
			sut(&moo_pDrlg, nActNo);
			original(&original_pDrlg, nActNo);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD82050, dll_base + 0x00042050);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();
			int nIteration{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
			const auto original_result = original(&original_pLevelLinkData, nIteration);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82130" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD82130, dll_base + 0x00042130);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();
			int nIteration{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
			const auto original_result = original(&original_pLevelLinkData, nIteration);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD821E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_LinkAct2Outdoors, dll_base + 0x000421E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();
			int nIteration{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
			const auto original_result = original(&original_pLevelLinkData, nIteration);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82240" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_LinkAct2Canyon, dll_base + 0x00042240);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();
			int nIteration{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
			const auto original_result = original(&original_pLevelLinkData, nIteration);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Comon.0x6FD822A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_LinkAct4Outdoors, dll_base + 0x000422A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();
			int nIteration{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
			const auto original_result = original(&original_pLevelLinkData, nIteration);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82300" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_LinkAct4ChaosSanctum, dll_base + 0x00042300);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelLinkDataStrc pLevelLinkData{};
				
				return std::tuple{ pLevelLinkData };
			};
			
			// Input data
			auto [moo_pLevelLinkData] = setup_data();
			auto [original_pLevelLinkData] = setup_data();
			int nIteration{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
			const auto original_result = original(&original_pLevelLinkData, nIteration);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82360" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD82360, dll_base + 0x00042360);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				int pRand{};
				
				return std::tuple{ pLevel, pRand };
			};
			
			// Input data
			auto [moo_pLevel, moo_pRand] = setup_data();
			auto [original_pLevel, original_pRand] = setup_data();
			int nIteration{};

			// Call both implementations
			sut(&moo_pLevel, nIteration, &moo_pRand);
			original(&original_pLevel, nIteration, &original_pRand);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			SKIP_MOO_CHECK_EQ(moo_pRand, original_pRand, "Comparing pRand");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD823C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD823C0, dll_base + 0x000423C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				D2DrlgLinkStrc pDrlgLink{};
				
				return std::tuple{ pDrlg, pDrlgLink };
			};
			
			// Input data
			auto [moo_pDrlg, moo_pDrlgLink] = setup_data();
			auto [original_pDrlg, original_pDrlgLink] = setup_data();

			// Call both implementations
			sut(&moo_pDrlg, &moo_pDrlgLink, nullptr, nullptr);
			original(&original_pDrlg, &original_pDrlgLink, nullptr, nullptr);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			SKIP_MOO_CHECK_EQ(moo_pDrlgLink, original_pDrlgLink, "Comparing pDrlgLink");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD826D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD826D0, dll_base + 0x000426D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();
			int nStartId{};
			int nEndId{};

			// Call both implementations
			sut(&moo_pDrlg, nStartId, nEndId);
			original(&original_pDrlg, nStartId, nEndId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD82750, dll_base + 0x00042750);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();
			int nStartId{};
			int nEndId{};

			// Call both implementations
			sut(&moo_pDrlg, nStartId, nEndId);
			original(&original_pDrlg, nStartId, nEndId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82820" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GenerateJungles, dll_base + 0x00042820);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel);
			const auto original_result = original(&original_pLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD83970" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD83970, dll_base + 0x00043970);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgCoordStrc pDrlgCoord{};
				D2JungleStrc pJungle{};
				
				return std::tuple{ pDrlgCoord, pJungle };
			};
			
			// Input data
			auto [moo_pDrlgCoord, moo_pJungle] = setup_data();
			auto [original_pDrlgCoord, original_pJungle] = setup_data();
			int nRand{};
			int nSizeX{};
			int nSizeY{};

			// Call both implementations
			sut(&moo_pDrlgCoord, &moo_pJungle, nRand, nSizeX, nSizeY);
			original(&original_pDrlgCoord, &original_pJungle, nRand, nSizeX, nSizeY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
			SKIP_MOO_CHECK_EQ(moo_pJungle, original_pJungle, "Comparing pJungle");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD83A20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_InitOutdoorRoomGrids, dll_base + 0x00043A20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD83C90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_CreateOutdoorRoomEx, dll_base + 0x00043C90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();
			int nX{};
			int nY{};
			int nWidth{};
			int nHeight{};
			int dwRoomFlags{};
			int dwOutdoorFlags{};
			int dwOutdoorFlagsEx{};
			int dwDT1Mask{};

			// Call both implementations
			sut(&moo_pLevel, nX, nY, nWidth, nHeight, dwRoomFlags, dwOutdoorFlags, dwOutdoorFlagsEx, dwDT1Mask);
			original(&original_pLevel, nX, nY, nWidth, nHeight, dwRoomFlags, dwOutdoorFlags, dwOutdoorFlagsEx, dwDT1Mask);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
}
