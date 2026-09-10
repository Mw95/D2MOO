#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <PLAYER/PlrIntro.h>
#include <Units/Units.h>


TEST_SUITE("PlrIntroTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F000" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRINTRO_SetQuestIntroFlag, dll_base + 0x0004F000);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2GameStrc pGame{};
				
				return std::tuple{ pUnit, pGame };
			};
			
			// Input data
			auto [moo_pUnit, moo_pGame] = setup_data();
			auto [original_pUnit, original_pGame] = setup_data();
			int32_t nNpcId{};

			// Call both implementations
			sut(&moo_pUnit, &moo_pGame, nNpcId);
			original(&original_pUnit, &original_pGame, nNpcId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRINTRO_GetQuestIntroFlag, dll_base + 0x0004F060);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2GameStrc pGame{};
				
				return std::tuple{ pUnit, pGame };
			};
			
			// Input data
			auto [moo_pUnit, moo_pGame] = setup_data();
			auto [original_pUnit, original_pGame] = setup_data();
			int32_t nNpcId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pGame, nNpcId);
			const auto original_result = original(&original_pUnit, &original_pGame, nNpcId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F0C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRINTRO_SetNpcIntroFlag, dll_base + 0x0004F0C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2PlrIntroStrc pPlayerIntro{};
				
				return std::tuple{ pPlayerIntro };
			};
			
			// Input data
			auto [moo_pPlayerIntro] = setup_data();
			auto [original_pPlayerIntro] = setup_data();
			int32_t nNpcId{};

			// Call both implementations
			sut(&moo_pPlayerIntro, nNpcId);
			original(&original_pPlayerIntro, nNpcId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayerIntro, original_pPlayerIntro, "Comparing pPlayerIntro");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F100" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRINTRO_GetNpcIntroFlag, dll_base + 0x0004F100);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2PlrIntroStrc pPlayerIntro{};
				
				return std::tuple{ pPlayerIntro };
			};
			
			// Input data
			auto [moo_pPlayerIntro] = setup_data();
			auto [original_pPlayerIntro] = setup_data();
			int32_t nNpcId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayerIntro, nNpcId);
			const auto original_result = original(&original_pPlayerIntro, nNpcId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayerIntro, original_pPlayerIntro, "Comparing pPlayerIntro");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRINTRO_MaskNpcIntroFlag, dll_base + 0x0004F140);
		
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
			int32_t nNpcId{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nNpcId);
			original(&original_pGame, &original_pPlayer, nNpcId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F1A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRINTRO_CopyQuestIntroFlagsToBuffer, dll_base + 0x0004F1A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2PlrIntroStrc pPlayerIntro{};
				uint8_t pBuffer{};
				
				return std::tuple{ pPlayerIntro, pBuffer };
			};
			
			// Input data
			auto [moo_pPlayerIntro, moo_pBuffer] = setup_data();
			auto [original_pPlayerIntro, original_pBuffer] = setup_data();

			// Call both implementations
			sut(&moo_pPlayerIntro, &moo_pBuffer);
			original(&original_pPlayerIntro, &original_pBuffer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayerIntro, original_pPlayerIntro, "Comparing pPlayerIntro");
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F1B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRINTRO_CopyNpcIntroFlagsToBuffer, dll_base + 0x0004F1B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2PlrIntroStrc pPlayerIntro{};
				uint8_t pBuffer{};
				
				return std::tuple{ pPlayerIntro, pBuffer };
			};
			
			// Input data
			auto [moo_pPlayerIntro, moo_pBuffer] = setup_data();
			auto [original_pPlayerIntro, original_pBuffer] = setup_data();

			// Call both implementations
			sut(&moo_pPlayerIntro, &moo_pBuffer);
			original(&original_pPlayerIntro, &original_pBuffer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayerIntro, original_pPlayerIntro, "Comparing pPlayerIntro");
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F1C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRINTRO_CopyBufferToQuestIntroFlags, dll_base + 0x0004F1C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2PlrIntroStrc pPlayerIntro{};
				uint8_t pBuffer{};
				
				return std::tuple{ pPlayerIntro, pBuffer };
			};
			
			// Input data
			auto [moo_pPlayerIntro, moo_pBuffer] = setup_data();
			auto [original_pPlayerIntro, original_pBuffer] = setup_data();

			// Call both implementations
			sut(&moo_pPlayerIntro, &moo_pBuffer);
			original(&original_pPlayerIntro, &original_pBuffer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayerIntro, original_pPlayerIntro, "Comparing pPlayerIntro");
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F1D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRINTRO_CopyBufferToNpcIntroFlags, dll_base + 0x0004F1D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2PlrIntroStrc pPlayerIntro{};
				uint8_t pBuffer{};
				
				return std::tuple{ pPlayerIntro, pBuffer };
			};
			
			// Input data
			auto [moo_pPlayerIntro, moo_pBuffer] = setup_data();
			auto [original_pPlayerIntro, original_pBuffer] = setup_data();

			// Call both implementations
			sut(&moo_pPlayerIntro, &moo_pBuffer);
			original(&original_pPlayerIntro, &original_pBuffer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayerIntro, original_pPlayerIntro, "Comparing pPlayerIntro");
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F1E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRINTRO_Create, dll_base + 0x0004F1E0);
		
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

			// Call both implementations
			const auto moo_result = sut(&moo_pGame);
			const auto original_result = original(&original_pGame);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F2A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRINTRO_Destroy, dll_base + 0x0004F2A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2PlrIntroStrc pPlayerIntro{};
				
				return std::tuple{ pGame, pPlayerIntro };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayerIntro] = setup_data();
			auto [original_pGame, original_pPlayerIntro] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayerIntro);
			original(&original_pGame, &original_pPlayerIntro);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayerIntro, original_pPlayerIntro, "Comparing pPlayerIntro");
		}
	}
}
