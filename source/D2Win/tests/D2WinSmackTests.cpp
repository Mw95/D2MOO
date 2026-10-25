#include <D2WinTestDefines.h>

#ifdef SMACK_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <string>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinSmack.h>


// Whether the video must be decoded again when drawing
extern int32_t dword_6F96A8D8;
// Whether the text boxes use a reduced line spacing
extern int32_t dword_6F96A8DC;


TEST_SUITE("D2WinSmackTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// File that doesn't exist, so that deleting it does nothing
	constexpr const char* szTestVideo = "D2WinTests_NonExistentVideo.smk";

	void setup_smack(D2WinSmackStrc& pSmack, const char* szName)
	{
		d2win_init_control(pSmack.controlHeader, D2WIN_SMACK, 100, 200, 468, 60);
		pSmack.smackerContext.nX = 100;
		pSmack.smackerContext.nY = 140;
		strcpy_s(pSmack.szFileName, szTestVideo);
		D2WinCallLog::name_pointer(&pSmack, szName);
		D2WinCallLog::name_pointer(&pSmack.smackerContext, std::string(szName) + "->smackerContext");
	}

	struct SmackGlobalsFixture : D2WinFixture<NoopFixture>
	{
		int32_t& original_bDecodeAgain = original_d2win_global<int32_t>(0x6F96A8D8);
		int32_t& original_bReducedLineSpacing = original_d2win_global<int32_t>(0x6F96A8DC);

		SmackGlobalsFixture()
		{
			dword_6F96A8D8 = 0;
			original_bDecodeAgain = 0;
		}

		~SmackGlobalsFixture()
		{
			dword_6F96A8D8 = 0;
			original_bDecodeAgain = 0;
			dword_6F96A8DC = 0;
			original_bReducedLineSpacing = 0;
		}
	};


	TEST_CASE_FIXTURE(SmackGlobalsFixture, "D2Win.0x6F8AF710 (#10097)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_Create, dll_base + 0x0000F710);

		SUBCASE("")
		{
			// Input data
			const int32_t nX = random_unsigned_integer(0, 800);
			const int32_t nY = random_unsigned_integer(0, 600);
			const int32_t nWidth = GENERATE(0, 468, 800);
			const int32_t nHeight = GENERATE(0, 60, 600);

			// Call both implementations
			D2WinSmackStrc* moo_result = sut(nX, nY, nWidth, nHeight, D2WinCallbacks::Callback);
			D2WinSmackStrc* original_result = original(nX, nY, nWidth, nHeight, D2WinCallbacks::Callback);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			CHECK_EQ(moo_state.pControlList, &moo_result->controlHeader);
			CHECK_EQ(original_state.pControlList, &original_result->controlHeader);
			CHECK_EQ(moo_result->controlHeader.pfDraw, &SMACK_Draw);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseDown, &SMACK_HandleMouseDown);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfDraw), dll_base + 0x0000F960);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseDown), dll_base + 0x0000FA40);
		}
	}

	TEST_CASE_FIXTURE(SmackGlobalsFixture, "D2Win.0x6F8AF7E0 (#10099)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_Decode, dll_base + 0x0000F7E0);

		SUBCASE("")
		{
			// Input data
			const char* szFileName = GENERATE("", "data\\local\\video\\New_Bliz640x480.bik", "video.smk");
			const int nVersion = GENERATE(0, 1);
			D2WinSmackStrc moo_pSmack{};
			D2WinSmackStrc original_pSmack{};
			setup_smack(moo_pSmack, "pSmack");
			setup_smack(original_pSmack, "pSmack");

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut(&moo_pSmack, szFileName, nVersion, 0, 0);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(&original_pSmack, szFileName, nVersion, 0, 0);
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSmack, original_pSmack, "Comparing pSmack");
		}
	}

	TEST_CASE_FIXTURE(SmackGlobalsFixture, "D2Win.0x6F8AF860 (#10101)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_DeleteFile, dll_base + 0x0000F860);

		SUBCASE("")
		{
			// Input data
			const int32_t bDecodeAgain = GENERATE(0, 1);
			dword_6F96A8D8 = bDecodeAgain;
			original_bDecodeAgain = bDecodeAgain;
			D2WinSmackStrc moo_pSmack{};
			D2WinSmackStrc original_pSmack{};
			setup_smack(moo_pSmack, "pSmack");
			setup_smack(original_pSmack, "pSmack");

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut(&moo_pSmack);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(&original_pSmack);
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSmack, original_pSmack, "Comparing pSmack");
			CHECK_EQ(dword_6F96A8D8, original_bDecodeAgain);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF8B0 (#10100)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_SetCoordinates, dll_base + 0x0000F8B0);

		SUBCASE("")
		{
			// Input data
			const int nX = random_unsigned_integer(0, 800);
			const int nY = random_unsigned_integer(0, 600);
			D2WinSmackStrc moo_pSmack{};
			D2WinSmackStrc original_pSmack{};
			setup_smack(moo_pSmack, "pSmack");
			setup_smack(original_pSmack, "pSmack");

			// Call both implementations
			const auto moo_result = sut(&moo_pSmack, nX, nY);
			const auto original_result = original(&original_pSmack, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSmack, original_pSmack, "Comparing pSmack");
		}
	}

	TEST_CASE_FIXTURE(SmackGlobalsFixture, "D2Win.0x6F8AF900 (#10098)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_Destroy, dll_base + 0x0000F900);

		SUBCASE("")
		{
			// Input data
			D2WinSmackStrc* moo_pSmack = d2win_calloc<D2WinSmackStrc>();
			D2WinSmackStrc* original_pSmack = d2win_calloc<D2WinSmackStrc>();
			setup_smack(*moo_pSmack, "pSmack");
			setup_smack(*original_pSmack, "pSmack");
			moo_state.pControlList = &moo_pSmack->controlHeader;
			original_state.pControlList = &original_pSmack->controlHeader;

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut(moo_pSmack);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(original_pSmack);
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSmack, original_pSmack, "Comparing pSmack");
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
		}
	}

	TEST_CASE_FIXTURE(SmackGlobalsFixture, "D2Win.0x6F8AF950 (#10184)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10184, dll_base + 0x0000F950);

		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();

			// Compare the modified globals
			CHECK_EQ(dword_6F96A8D8, original_bDecodeAgain);
			CHECK_EQ(dword_6F96A8D8, 1);
		}
	}

	TEST_CASE_FIXTURE(SmackGlobalsFixture, "D2Win.0x6F8AF960")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_Draw, dll_base + 0x0000F960);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		const int32_t bDecodeAgain = GENERATE(0, 1);
		CAPTURE(dwFlags);
		CAPTURE(bDecodeAgain);

		D2WinSmackStrc moo_pSmack{};
		D2WinSmackStrc original_pSmack{};
		setup_smack(moo_pSmack, "pSmack");
		setup_smack(original_pSmack, "pSmack");
		moo_pSmack.controlHeader.dwFlags = dwFlags;
		original_pSmack.controlHeader.dwFlags = dwFlags;

		// The name of the last decoded video is stored in a global variable whose address in the original .dll is unknown,
		// both implementations decode the same video first.
		SMACK_Decode(&moo_pSmack, "last_video.smk", 1, 0, 0);
		reinterpret_cast<decltype(&SMACK_Decode)>(dll_base + 0x0000F7E0)(&original_pSmack, "last_video.smk", 1, 0, 0);
		dword_6F96A8D8 = bDecodeAgain;
		original_bDecodeAgain = bDecodeAgain;

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pSmack.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pSmack.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pSmack, original_pSmack, "Comparing pSmack");
		CHECK_EQ(dword_6F96A8D8, original_bDecodeAgain);
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AFA40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_HandleMouseDown, dll_base + 0x0000FA40);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		const bool bHasCallback = GENERATE(true, false);
		CAPTURE(dwFlags);
		CAPTURE(bHasCallback);

		D2WinSmackStrc moo_pSmack{};
		D2WinSmackStrc original_pSmack{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinSmackStrc& pSmack,
			SMSGHANDLER_PARAMS& pMsg
		) {
			setup_smack(pSmack, "pSmack");
			pSmack.controlHeader.dwFlags = dwFlags;
			pSmack.controlHeader.pfCallback = bHasCallback ? D2WinCallbacks::Callback : nullptr;
			pMsg.hWindow = reinterpret_cast<HWND>(&pSmack);
			pMsg.nMessage = WM_LBUTTONDOWN;
		};

		setup_data(moo_pSmack, moo_pMsg);
		setup_data(original_pSmack, original_pMsg);

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pMsg);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pMsg);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pSmack, original_pSmack, "Comparing pSmack");
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
	}

	TEST_CASE_FIXTURE(SmackGlobalsFixture, "D2Win.0x6F8AFA90 (#10208)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10208, dll_base + 0x0000FA90);

		SUBCASE("")
		{
			// Input data
			const int bReducedLineSpacing = GENERATE(0, 1, 2);

			// Call both implementations
			sut(bReducedLineSpacing);
			original(bReducedLineSpacing);

			// Compare the modified globals
			CHECK_EQ(dword_6F96A8DC, original_bReducedLineSpacing);
			CHECK_EQ(dword_6F96A8DC, bReducedLineSpacing);
		}
	}
}

#endif
