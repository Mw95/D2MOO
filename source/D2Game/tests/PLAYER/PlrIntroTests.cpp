#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

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
			// Input data
			D2UnitStrc moo_pUnit{};
			D2GameStrc moo_pGame{};
			D2UnitStrc original_pUnit{};
			D2GameStrc original_pGame{};
			int32_t nNpcId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pGame);
			setup_data(original_pUnit, original_pGame);

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
			// Input data
			D2UnitStrc moo_pUnit{};
			D2GameStrc moo_pGame{};
			D2UnitStrc original_pUnit{};
			D2GameStrc original_pGame{};
			int32_t nNpcId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pGame);
			setup_data(original_pUnit, original_pGame);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, &moo_pGame, nNpcId);
			auto original_result = original(&original_pUnit, &original_pGame, nNpcId);
			
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
			// Input data
			D2PlrIntroStrc moo_pPlayerIntro{};
			D2PlrIntroStrc original_pPlayerIntro{};
			int32_t nNpcId{};

			const auto setup_data = [](
				D2PlrIntroStrc& pPlayerIntro
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayerIntro);
			setup_data(original_pPlayerIntro);

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
			// Input data
			D2PlrIntroStrc moo_pPlayerIntro{};
			D2PlrIntroStrc original_pPlayerIntro{};
			int32_t nNpcId{};

			const auto setup_data = [](
				D2PlrIntroStrc& pPlayerIntro
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayerIntro);
			setup_data(original_pPlayerIntro);

			// Call both implementations
			auto moo_result = sut(&moo_pPlayerIntro, nNpcId);
			auto original_result = original(&original_pPlayerIntro, nNpcId);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nNpcId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2PlrIntroStrc moo_pPlayerIntro{};
			uint8_t moo_pBuffer{};
			D2PlrIntroStrc original_pPlayerIntro{};
			uint8_t original_pBuffer{};

			const auto setup_data = [](
				D2PlrIntroStrc& pPlayerIntro,
				uint8_t& pBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayerIntro, moo_pBuffer);
			setup_data(original_pPlayerIntro, original_pBuffer);

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
			// Input data
			D2PlrIntroStrc moo_pPlayerIntro{};
			uint8_t moo_pBuffer{};
			D2PlrIntroStrc original_pPlayerIntro{};
			uint8_t original_pBuffer{};

			const auto setup_data = [](
				D2PlrIntroStrc& pPlayerIntro,
				uint8_t& pBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayerIntro, moo_pBuffer);
			setup_data(original_pPlayerIntro, original_pBuffer);

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
			// Input data
			D2PlrIntroStrc moo_pPlayerIntro{};
			uint8_t moo_pBuffer{};
			D2PlrIntroStrc original_pPlayerIntro{};
			uint8_t original_pBuffer{};

			const auto setup_data = [](
				D2PlrIntroStrc& pPlayerIntro,
				uint8_t& pBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayerIntro, moo_pBuffer);
			setup_data(original_pPlayerIntro, original_pBuffer);

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
			// Input data
			D2PlrIntroStrc moo_pPlayerIntro{};
			uint8_t moo_pBuffer{};
			D2PlrIntroStrc original_pPlayerIntro{};
			uint8_t original_pBuffer{};

			const auto setup_data = [](
				D2PlrIntroStrc& pPlayerIntro,
				uint8_t& pBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayerIntro, moo_pBuffer);
			setup_data(original_pPlayerIntro, original_pBuffer);

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
			auto moo_result = sut(&moo_pGame);
			auto original_result = original(&original_pGame);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2PlrIntroStrc moo_pPlayerIntro{};
			D2GameStrc original_pGame{};
			D2PlrIntroStrc original_pPlayerIntro{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2PlrIntroStrc& pPlayerIntro
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayerIntro);
			setup_data(original_pGame, original_pPlayerIntro);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayerIntro);
			original(&original_pGame, &original_pPlayerIntro);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayerIntro, original_pPlayerIntro, "Comparing pPlayerIntro");
		}
	}
}
