#include <D2WinTestDefines.h>

#ifdef PALETTE_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <memory>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinPalette.h>


// Palette fading state of the D2MOO implementation
extern int32_t dword_6F8BE008;
extern uint32_t dword_6F90E290;
extern uint32_t dword_6F96A7C0;
extern uint32_t dword_6F96A7C4;
extern D2ShadowLightGammaPaletteStrc gShadowsLightGammaPalette_6F91E298;
extern uint8_t gStatesPalette_6F9626C0[128][256];


TEST_SUITE("D2WinPaletteTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// Palette fading state of both implementations
	struct PaletteFadeFixture : D2WinFixture<NoopFixture>
	{
		struct FadeState
		{
			int32_t& bFading;
			uint32_t& nRemainingSteps;
			uint32_t& bTimed;
			uint32_t& dwLastStepTickCount;

			void set(int32_t bNewFading, uint32_t nNewRemainingSteps, uint32_t bNewTimed, uint32_t dwNewLastStepTickCount)
			{
				bFading = bNewFading;
				nRemainingSteps = nNewRemainingSteps;
				bTimed = bNewTimed;
				dwLastStepTickCount = dwNewLastStepTickCount;
			}
		};

		FadeState moo_fade = { dword_6F8BE008, dword_6F90E290, dword_6F96A7C0, dword_6F96A7C4 };
		FadeState original_fade = {
			original_d2win_global<int32_t>(0x6F8BE008),
			original_d2win_global<uint32_t>(0x6F90E290),
			original_d2win_global<uint32_t>(0x6F96A7C0),
			original_d2win_global<uint32_t>(0x6F96A7C4),
		};

		~PaletteFadeFixture()
		{
			moo_fade.set(0, 0, 0, 0);
			original_fade.set(0, 0, 0, 0);
		}

		void check_fade_states_eq()
		{
			CHECK_EQ(moo_fade.bFading, original_fade.bFading);
			CHECK_EQ(moo_fade.nRemainingSteps, original_fade.nRemainingSteps);
			CHECK_EQ(moo_fade.bTimed, original_fade.bTimed);
			// The tick count is the result of GetTickCount() when it changed, so it's only compared approximately
			CHECK_LE(moo_fade.dwLastStepTickCount - original_fade.dwLastStepTickCount + 100, 200u);
		}
	};


	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE550 (#10177)" * doctest::skip("Needs MPQ archives to load the palette files from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10177, dll_base + 0x0000E550);

		SUBCASE("")
		{
			uint8_t nAct = 0;

			// Call both implementations
			const auto moo_result = sut(nAct);
			const auto original_result = original(nAct);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE5E0" * doctest::skip("Needs MPQ archives to load the palette files from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PALETTE_LoadFiles, dll_base + 0x0000E5E0);

		SUBCASE("")
		{
			const char* szDatFileName = "DATA\\GLOBAL\\palette\\act1\\pal.dat";
			const char* szPL2FileName = "DATA\\GLOBAL\\palette\\act1\\pal.pl2";

			// Call both implementations
			const auto moo_result = sut(szDatFileName, szPL2FileName);
			const auto original_result = original(szDatFileName, szPL2FileName);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE930 (#10175)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10175_GetPL2Shift, dll_base + 0x0000E930);

		SUBCASE("")
		{
			// Input data
			const int32_t nIndex = GENERATE(0, 1, 64, 127);
			const uintptr_t original_pStatesPalette = reinterpret_cast<uintptr_t>(&original_d2win_global<uint8_t>(0x6F9626C0));

			// Call both implementations
			const uint8_t* moo_result = sut(nIndex);
			const uint8_t* original_result = original(nIndex);

			// Compare return values, which point into the palettes of the respective implementation
			CHECK_EQ(reinterpret_cast<uintptr_t>(moo_result) - reinterpret_cast<uintptr_t>(gStatesPalette_6F9626C0), reinterpret_cast<uintptr_t>(original_result) - original_pStatesPalette);
		}
	}

	TEST_CASE_FIXTURE(PaletteFadeFixture, "D2Win.0x6F8AE940 (#10179)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10179, dll_base + 0x0000E940);

		// Input data
		const int32_t bFading = GENERATE(0, 1);
		const uint32_t bTimed = GENERATE(0u, 1u);
		const uint32_t nRemainingSteps = GENERATE(1u, 2u);
		const bool bStepElapsed = GENERATE(false, true);
		CAPTURE(bFading);
		CAPTURE(bTimed);
		CAPTURE(nRemainingSteps);
		CAPTURE(bStepElapsed);

		const uint32_t dwLastStepTickCount = GetTickCount() - (bStepElapsed ? 5000 : 0);
		moo_fade.set(bFading, nRemainingSteps, bTimed, dwLastStepTickCount);
		original_fade.set(bFading, nRemainingSteps, bTimed, dwLastStepTickCount);

		// Call both implementations
		D2WinCallLog::clear();
		sut();
		const auto moo_calls = D2WinCallLog::take();
		original();
		const auto original_calls = D2WinCallLog::take();

		CHECK_EQ(moo_calls, original_calls);

		// Compare the modified globals
		check_fade_states_eq();
	}

	TEST_CASE_FIXTURE(PaletteFadeFixture, "D2Win.0x6F8AE9A0 (#10176)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10176, dll_base + 0x0000E9A0);

		// Input data
		const int32_t bStartFade = GENERATE(0, 1, 2);
		CAPTURE(bStartFade);

		moo_fade.set(1, 5, 1, 0);
		original_fade.set(1, 5, 1, 0);

		// Call both implementations
		D2WinCallLog::clear();
		sut(bStartFade);
		const auto moo_calls = D2WinCallLog::take();
		original(bStartFade);
		const auto original_calls = D2WinCallLog::take();

		CHECK_EQ(moo_calls, original_calls);

		// Compare the modified globals
		check_fade_states_eq();
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE9F0 (#10028)" * doctest::skip("Needs MPQ archives to load the palette files from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10028, dll_base + 0x0000E9F0);

		SUBCASE("")
		{
			const char* pszPalDatFilename = nullptr;
			const char* pszPalPL2Filename = nullptr;

			// Call both implementations
			const auto moo_result = sut(pszPalDatFilename, pszPalPL2Filename);
			const auto original_result = original(pszPalDatFilename, pszPalPL2Filename);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AEA80 (#10034)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10034_MixRGB, dll_base + 0x0000EA80);

		SUBCASE("")
		{
			// Input data
			const uint8_t nRed = random_unsigned_integer(0, 255);
			const uint8_t nGreen = random_unsigned_integer(0, 255);
			const uint8_t nBlue = random_unsigned_integer(0, 255);

			// Call both implementations
			const auto moo_result = sut(nRed, nGreen, nBlue);
			const auto original_result = original(nRed, nGreen, nBlue);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AEAC0 (#10178)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10178, dll_base + 0x0000EAC0);

		SUBCASE("")
		{
			// Input data
			auto& moo_palettes = gShadowsLightGammaPalette_6F91E298;
			auto& original_palettes = original_d2win_global<D2ShadowLightGammaPaletteStrc>(0x6F91E298);
			auto saved_moo_palettes = std::make_unique<D2ShadowLightGammaPaletteStrc>(moo_palettes);
			auto saved_original_palettes = std::make_unique<D2ShadowLightGammaPaletteStrc>(original_palettes);

			const uint32_t nSeed = random_unsigned_integer();
			for (int i = 0; i < 49; ++i)
			{
				for (int j = 0; j < 64; ++j)
				{
					const uint32_t nValue = nSeed + i * 64 + j;
					const PALETTEENTRY entry = { static_cast<BYTE>(nValue), static_cast<BYTE>(nValue >> 8), static_cast<BYTE>(nValue * 3), static_cast<BYTE>(i) };
					moo_palettes.palettes[i][j] = entry;
					original_palettes.palettes[i][j] = entry;
				}
			}

			auto moo_pBuffer = std::make_unique<D2ShadowLightGammaPaletteStrc>();
			auto original_pBuffer = std::make_unique<D2ShadowLightGammaPaletteStrc>();

			// Call both implementations
			sut(moo_pBuffer.get());
			original(original_pBuffer.get());

			// Compare potentially modified input data
			MOO_CHECK_EQ(*moo_pBuffer, *original_pBuffer, "Comparing pBuffer");
			CHECK_EQ(std::memcmp(moo_pBuffer.get(), &moo_palettes, sizeof(moo_palettes)), 0);

			moo_palettes = *saved_moo_palettes;
			original_palettes = *saved_original_palettes;
		}
	}
}

#endif
