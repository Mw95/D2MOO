#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include <D2Config.h>
#include <D2WinEditBox.h>
#include <D2WinTextBox.h>

#include <ChatDlg.h>
#include <ComCallback.h>

#include "D2MultiTestFixtures.h"


extern char gszChatHistory_6F9C1A48[CHATDLG_MAX_CHAT_HISTORY][256];
extern char gszPendingChatText_6F9C2458[512];
extern int32_t gnChatHistoryCount_6F9C2864;


namespace
{
// Bnclient interface recording the chat commands
struct FakeBnClient
{
	static inline std::vector<std::string> commands;
	static inline BOOL bConnected = TRUE;

	static BOOL __fastcall ChatCommand(const char* szText)
	{
		commands.emplace_back(szText);
		return TRUE;
	}

	static BOOL __stdcall IsConnected()
	{
		return bConnected;
	}

	static const char* __stdcall GetUniqueName()
	{
		return "Hero*Account";
	}

	static BnClientInterface* table()
	{
		static BnClientInterface tInterface = []()
		{
			BnClientInterface tTable;
			std::memset(&tTable, 0, sizeof(tTable));
			tTable.ChatCommand = &ChatCommand;
			tTable.IsConnected = &IsConnected;
			tTable.GetUniqueName = &GetUniqueName;
			return tTable;
		}();
		return &tInterface;
	}
};

// The D2Win text and edit box functions do nothing, there is no user interface in the tests
struct D2WinTextMock
{
	static BOOL __fastcall AddLine(D2WinTextBoxStrc* pTextBox, const Unicode* wszText, int32_t nColor, char bIsWrapped, int32_t nIndent) { return TRUE; }
	static int32_t __fastcall GetNumLines(D2WinTextBoxStrc* pTextBox) { return 0; }
	static BOOL __fastcall SetLine(D2WinTextBoxStrc* pTextBox, int32_t nLine) { return TRUE; }
	static int32_t __fastcall GetVisibleLines(D2WinTextBoxStrc* pTextBox) { return 0; }
	static int __fastcall SetText(D2WinEditBoxStrc* pEditBox, const Unicode* pText) { return 0; }
};

// Globals of one implementation used by the chat commands
struct ChatGlobals
{
	BnClientInterface** ppComInt;
	D2ConfigStrc** ppConfig;
	char* szLastWhisperSender;
	BOOL* pbShowJoinLeaveNotifications;
	char (*pChatHistory)[256];
	int32_t* pnChatHistoryCount;
	char* szPendingChatText;
	D2MultiChannelUserStrc** ppSelectedUnit;
	decltype(&CHATDLG_HandleReplyCommand) HandleReplyCommand;
	decltype(&CHATDLG_HandleNotifyCommand) HandleNotifyCommand;
	decltype(&CHATDLG_SendChatText) SendChatText;
};

const ChatGlobals& moo_globals()
{
	static const ChatGlobals globals = {
		&gptComInt_6F9C19BC, &gpConfig_6F9C26F0, gszLastWhisperSender_6F9C1898, &gbShowJoinLeaveNotifications_6F9C2868,
		gszChatHistory_6F9C1A48, &gnChatHistoryCount_6F9C2864, gszPendingChatText_6F9C2458, &gptSelectedUnit_6F9C2B30,
		&CHATDLG_HandleReplyCommand, &CHATDLG_HandleNotifyCommand, &CHATDLG_SendChatText,
	};
	return globals;
}

const ChatGlobals& original_globals()
{
	static const ChatGlobals globals = {
		original_d2multi_global<BnClientInterface*>(0x6F9C19BC),
		original_d2multi_global<D2ConfigStrc*>(0x6F9C26F0),
		original_d2multi_global<char>(0x6F9C1898),
		original_d2multi_global<BOOL>(0x6F9C2868),
		original_d2multi_global<char[256]>(0x6F9C1A48),
		original_d2multi_global<int32_t>(0x6F9C2864),
		original_d2multi_global<char>(0x6F9C2458),
		original_d2multi_global<D2MultiChannelUserStrc*>(0x6F9C2B30),
		reinterpret_cast<decltype(&CHATDLG_HandleReplyCommand)>(original_d2multi_address(0x6F9A66F0)),
		reinterpret_cast<decltype(&CHATDLG_HandleNotifyCommand)>(original_d2multi_address(0x6F9A6550)),
		reinterpret_cast<decltype(&CHATDLG_SendChatText)>(original_d2multi_address(0x6F9A6B20)),
	};
	return globals;
}

template<class Fixture>
struct D2MultiChatFixture : D2MultiFixture<Fixture>
{
	D2ConfigStrc tConfig = {};

	D2MultiChatFixture()
	{
		this->hooks.hook("D2Win.dll", 10051, reinterpret_cast<void*>(&D2Win_10051), reinterpret_cast<const void*>(&D2WinTextMock::AddLine), false);
		this->hooks.hook("D2Win.dll", 10052, reinterpret_cast<void*>(&D2Win_10052_TEXTBOX_GetNumLines), reinterpret_cast<const void*>(&D2WinTextMock::GetNumLines), false);
		this->hooks.hook("D2Win.dll", 10053, reinterpret_cast<void*>(&D2Win_10053), reinterpret_cast<const void*>(&D2WinTextMock::SetLine), false);
		this->hooks.hook("D2Win.dll", 10055, reinterpret_cast<void*>(&D2Win_10055), reinterpret_cast<const void*>(&D2WinTextMock::GetVisibleLines), false);
		this->hooks.hook("D2Win.dll", 10075, reinterpret_cast<void*>(&EDITBOX_SetText), reinterpret_cast<const void*>(&D2WinTextMock::SetText), false);

		for (const ChatGlobals* pGlobals : { &moo_globals(), &original_globals() })
		{
			*pGlobals->ppComInt = FakeBnClient::table();
			*pGlobals->ppConfig = &tConfig;
			*pGlobals->ppSelectedUnit = nullptr;
			pGlobals->szLastWhisperSender[0] = '\0';
			*pGlobals->pnChatHistoryCount = 0;
			std::memset(pGlobals->pChatHistory, 0, CHATDLG_MAX_CHAT_HISTORY * 256);
		}
		FakeBnClient::commands.clear();
		FakeBnClient::bConnected = TRUE;
	}

	~D2MultiChatFixture()
	{
		for (const ChatGlobals* pGlobals : { &moo_globals(), &original_globals() })
		{
			*pGlobals->ppComInt = nullptr;
			*pGlobals->ppConfig = nullptr;
		}
	}
};

template<typename Test>
void for_each_globals(Test&& test)
{
	test(moo_globals());
	test(original_globals());
}
}


TEST_SUITE("D2MultiChatTests")
{
	TEST_CASE_FIXTURE(D2MultiChatFixture<NoOpFixture>, "D2Multi.0x6F9A66F0")
	{
		struct Case
		{
			const char* szLastWhisperSender;
			const char* szText;
			const char* szCommand;
			BOOL bConnected;
		};

		const Case cases[] = {
			{ "Friend", "/r hello there", "/r", TRUE },
			{ "Friend", "/R  spaced   words", "/r", TRUE },
			{ "Friend", "/reply hi", "/reply", TRUE },
			{ "Friend", "/reply hi", "/r", TRUE },
			{ "Friend", "/rx hi", "/r", TRUE },
			{ "Friend", "/r", "/r", TRUE },
			{ "", "/r hello", "/r", TRUE },
			{ "Friend", "hello", "/r", TRUE },
		};

		for (const Case& testCase : cases)
		{
			CAPTURE(testCase.szText);
			CAPTURE(testCase.szCommand);
			CAPTURE(testCase.szLastWhisperSender);

			std::vector<std::pair<BOOL, std::vector<std::string>>> results;
			for_each_globals([&](const ChatGlobals& globals)
			{
				std::strcpy(globals.szLastWhisperSender, testCase.szLastWhisperSender);
				FakeBnClient::commands.clear();
				FakeBnClient::bConnected = testCase.bConnected;
				const BOOL bResult = globals.HandleReplyCommand(testCase.szText, testCase.szCommand);
				results.emplace_back(bResult, FakeBnClient::commands);
			});

			CHECK_EQ(results[0].first, results[1].first);
			CHECK_EQ(results[0].second, results[1].second);
		}

		std::strcpy(gszLastWhisperSender_6F9C1898, "Friend");
		FakeBnClient::commands.clear();
		CHECK_EQ(CHATDLG_HandleReplyCommand("/r hello there", "/r"), TRUE);
		CHECK_EQ(FakeBnClient::commands, std::vector<std::string>{ "/w *Friend hello there" });
	}

	TEST_CASE_FIXTURE(D2MultiChatFixture<NoOpFixture>, "D2Multi.0x6F9A6550")
	{
		std::vector<std::vector<std::pair<BOOL, BOOL>>> results;
		for_each_globals([&](const ChatGlobals& globals)
		{
			std::vector<std::pair<BOOL, BOOL>> states;
			*globals.pbShowJoinLeaveNotifications = FALSE;
			for (const char* szText : { "/d2notify", "/D2NOTIFY", "/d2notify on", "/d2notifyx", "/d2", "hello" })
			{
				const BOOL bResult = globals.HandleNotifyCommand(szText, "/d2notify");
				states.emplace_back(bResult, *globals.pbShowJoinLeaveNotifications);
			}
			results.push_back(states);
		});

		CHECK_EQ(results[0], results[1]);
		CHECK_EQ(results[0][0], std::make_pair(TRUE, TRUE));
		CHECK_EQ(results[0][1], std::make_pair(TRUE, FALSE));
	}

	TEST_CASE_FIXTURE(D2MultiChatFixture<NoOpFixture>, "D2Multi.0x6F9A6B20")
	{
		struct Result
		{
			BOOL bResult;
			std::vector<std::string> commands;
			std::string szPendingText;
			std::vector<std::string> history;
			int32_t nHistoryCount;
			BOOL bShowJoinLeaveNotifications;

			bool operator==(const Result& other) const
			{
				return bResult == other.bResult && commands == other.commands && szPendingText == other.szPendingText
					&& history == other.history && nHistoryCount == other.nHistoryCount && bShowJoinLeaveNotifications == other.bShowJoinLeaveNotifications;
			}
		};

		// Commands are sent as is and kept in the history, /r and /d2notify are handled by D2Multi.
		// Texts looking like a password or a CD key show a warning instead, they are not tested since it needs the user interface.
		const std::vector<std::pair<const char*, BOOL>> texts = {
			{ "/join Diablo II", FALSE },
			{ "hello everyone", FALSE },
			{ "no selected user to whisper to", TRUE },
			{ "/who channel", TRUE },
			{ "/r hello", FALSE },
			{ "/d2notify", FALSE },
			{ "/f list", FALSE },
			{ "/w", FALSE },
			{ "/1", FALSE },
			{ "/2", FALSE },
			{ "/3", FALSE },
			{ "/4", FALSE },
			{ "/5", FALSE },
			{ "/6", FALSE },
			{ "/7", FALSE },
			{ "/8", FALSE },
			{ "/9", FALSE },
			{ "/10", FALSE },
			{ "/11 history is full", FALSE },
		};

		std::vector<std::vector<Result>> results;
		for_each_globals([&](const ChatGlobals& globals)
		{
			std::strcpy(globals.szLastWhisperSender, "Friend");
			*globals.pbShowJoinLeaveNotifications = FALSE;

			std::vector<Result> sequence;
			for (const auto& [szText, bWhisper] : texts)
			{
				FakeBnClient::commands.clear();
				std::string szBuffer = szText;
				Result result;
				result.bResult = globals.SendChatText(szBuffer.data(), bWhisper);
				result.commands = FakeBnClient::commands;
				result.szPendingText = globals.szPendingChatText;
				for (int32_t i = 0; i < CHATDLG_MAX_CHAT_HISTORY; ++i)
				{
					result.history.emplace_back(globals.pChatHistory[i]);
				}
				result.nHistoryCount = *globals.pnChatHistoryCount;
				result.bShowJoinLeaveNotifications = *globals.pbShowJoinLeaveNotifications;
				sequence.push_back(result);
			}
			results.push_back(sequence);
		});

		REQUIRE_EQ(results[0].size(), results[1].size());
		for (size_t i = 0; i < results[0].size(); ++i)
		{
			CAPTURE(texts[i].first);
			CHECK_EQ(results[0][i].bResult, results[1][i].bResult);
			CHECK_EQ(results[0][i].commands, results[1][i].commands);
			CHECK_EQ(results[0][i].szPendingText, results[1][i].szPendingText);
			CHECK_EQ(results[0][i].history, results[1][i].history);
			CHECK_EQ(results[0][i].nHistoryCount, results[1][i].nHistoryCount);
			CHECK_EQ(results[0][i].bShowJoinLeaveNotifications, results[1][i].bShowJoinLeaveNotifications);
		}

		CHECK_EQ(results[0][0].commands, std::vector<std::string>{ "/join Diablo II" });
		CHECK_EQ(results[0][1].commands, std::vector<std::string>{ "hello everyone" });
		CHECK_EQ(results[0][4].commands, std::vector<std::string>{ "/w *Friend hello" });
		CHECK_EQ(results[0][5].bShowJoinLeaveNotifications, TRUE);
		CHECK_EQ(results[0].back().nHistoryCount, CHATDLG_MAX_CHAT_HISTORY);
	}
}
