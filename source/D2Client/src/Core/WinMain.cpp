#include "Core/WinMain.h"

#include <D2WinMain.h>
#include <D2WinArchive.h>
#include <D2DataTbls.h>
#include <D2Log.h>
#include <Window.h>

#include "Core/Lng.h"
#include "Core/MemoryPartitions.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/Record.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "Skills/SkillsPal.h"
#include "UI/UI.h"


//D2Client.0x6FB6E0C8
static int32_t(__fastcall* gpfInitializers[])() =
{
	LNG_RegisterCommandLineArgument,
};

//D2Client.0x6FB6E0D0
static D2CommandLineArgStrc gaCommandLineArgs[] =
{
	{ 0,       (uint32_t)-1, "?",    CLIENT_ShowCommandLineHelp },
	{ 0,       (uint32_t)-1, "h",    CLIENT_ShowCommandLineHelp },
	{ 0,       (uint32_t)-1, "help", CLIENT_ShowCommandLineHelp },
	{ 0x20000, (uint32_t)-1, "set",  CLIENT_SetDefaultCommandLine },
	{ 0x20000, (uint32_t)-1, "mode", CLIENT_SetAppModeFromCommandLine },
	{ 0,       (uint32_t)-1, "c",    CLIENT_PrecacheMemory },
	{ 0,       (uint32_t)-1, "r",    CLIENT_StartRecording },
	{ 0,       (uint32_t)-1, "p",    CLIENT_StartPlayback },
};

//D2Client.0x6FB740EC
int32_t gnScreenWidth = 640;
//D2Client.0x6FB740F0
int32_t gnScreenHeight = 480;
//D2Client.0x6FB740F4
int32_t gnScreenWidth2 = 640;

//D2Client.0x6FB744D8
int32_t gnAppMode = APPMODE_START;

//D2Client.0x6FB744EC
static int32_t(__fastcall* gpfAppModeHandlers[])() =
{
	nullptr,
	nullptr,
	sub_6FAAB370,
	sub_6FAAA4E0,
	sub_6FAABB40,
	sub_6FAADD00,
	sub_6FAADE60,
};

//D2Client.0x6FB74508
static const char* gszAppModeNames[] =
{
	nullptr,
	nullptr,
	"Game",
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	"Tyler",
	"Path",
	"Test",
	"Composite",
};

//D2Client.0x6FB74538
int32_t gbExitToMenu = TRUE;
//D2Client.0x6FB747C0
int32_t gbIsAppActive = TRUE;

//D2Client.0x6FB9A700
int32_t gnViewHeight = 480 - 40;	// Initialized at startup from gnScreenHeight (D2Client.0x6FAA1190)
//D2Client.0x6FB9A704
int32_t gnViewWidth = 640;			// Initialized at startup from gnScreenWidth (D2Client.0x6FAA1180)
//D2Client.0x6FB9A708
int32_t gbIsHighResolution;
//D2Client.0x6FB9A830
char gszModulePath[MAX_PATH];
//D2Client.0x6FB9A934
static int32_t gaAppModeStack[APPMODE_STACK_SIZE];
//D2Client.0x6FB9A948
D2ConfigStrc* gpConfig;
//D2Client.0x6FB9A94C
HINSTANCE ghClientInstance;
//D2Client.0x6FB9A950
int32_t gnClientExitCode;
//D2Client.0x6FB9A954
HACCEL ghClientAccelerators;
//D2Client.0x6FB9A958
static BOOL gbCommandLineHelpShown;
//D2Client.0x6FB9A95C
static int32_t sgnLastAppmode;


//D2Client.0x6FAA1D00
void __fastcall CLIENT_PushAppMode(int32_t nAppMode)
{
	D2_ASSERT(sgnLastAppmode < APPMODE_STACK_SIZE);
	gaAppModeStack[sgnLastAppmode] = nAppMode;
	++sgnLastAppmode;
}

//D2Client.0x6FAA1D40
int32_t __fastcall CLIENT_PopAppMode()
{
	D2_ASSERT(sgnLastAppmode);

	const int32_t nAppMode = gaAppModeStack[0];
	gaAppModeStack[0] = gaAppModeStack[1];
	gaAppModeStack[1] = gaAppModeStack[2];
	gaAppModeStack[2] = gaAppModeStack[3];
	--sgnLastAppmode;
	return nAppMode;
}

//D2Client.0x6FAA1DA0 (inlined)
static void CLIENT_DisplayCommandLineHelp()
{
	if (gbCommandLineHelpShown)
	{
		return;
	}

	gbCommandLineHelpShown = TRUE;

	char szUserName[16] = {};
	DWORD nUserNameSize = 15;
	GetUserNameA(szUserName, &nUserNameSize);
	if (SStrCmp(szUserName, "rseis", 0x7FFFFFFF))
	{
		MessageBoxA(nullptr,
			"Available command line options:\n"
			"  -set[default command line]\t\tSet new default command line char\n"
			"  -lng[lngfile]\t\t\tUse \"lngfile\" for language resources\n"
			"  -s[name]\t\t\t\tAttach to server \"name\"\n"
			"  -mode[mode]\t\t\tStart in [mode], where mode is\n"
			"  -c\t\t\t\tPrecache\n"
			"  \t\t\t\tgame\n"
			"  \t\t\t\tTyler\n"
			"  \t\t\t\tPath\n"
			"  \t\t\t\tComposite\n",
			"Diablo II", MB_OK);
	}
}

//D2Client.0x6FAA1DA0
BOOL __stdcall CLIENT_ShowCommandLineHelp(D2CommandLineParamsStrc* pParams, uint32_t nUnused)
{
	CLIENT_DisplayCommandLineHelp();
	return FALSE;
}

//D2Client.0x6FAA1E10
BOOL __stdcall CLIENT_PrecacheMemory(D2CommandLineParamsStrc* pParams, uint32_t nUnused)
{
	constexpr size_t nPrecacheSize = 0x6000000;

	uint8_t* pMemory = (uint8_t*)D2_ALLOC(nPrecacheSize);
	for (uint8_t* pPage = pMemory; pPage < pMemory + nPrecacheSize; pPage += 0x1000)
	{
		*pPage = 0;
	}
	D2_FREE(pMemory);
	return TRUE;
}

//D2Client.0x6FAA1E60
BOOL __stdcall CLIENT_StartRecording(D2CommandLineParamsStrc* pParams, uint32_t nUnused)
{
	sub_6FAAEB20();
	return TRUE;
}

//D2Client.0x6FAA1E70
BOOL __stdcall CLIENT_StartPlayback(D2CommandLineParamsStrc* pParams, uint32_t nUnused)
{
	sub_6FAAE940();
	return TRUE;
}

//D2Client.0x6FAA1E80
BOOL __stdcall CLIENT_SetDefaultCommandLine(D2CommandLineParamsStrc* pParams, uint32_t nUnused)
{
	return SRegSaveString("Diablo II", "Default Command Line", 0, pParams->pszParam);
}

//D2Client.0x6FAA1EA0
BOOL __stdcall CLIENT_SetAppModeFromCommandLine(D2CommandLineParamsStrc* pParams, uint32_t nUnused)
{
	for (int32_t i = 0; i < ARRAY_SIZE(gszAppModeNames); ++i)
	{
		if (gszAppModeNames[i] && !_stricmp(gszAppModeNames[i], pParams->pszParam))
		{
			gnAppMode = i;
			return TRUE;
		}
	}

	CLIENT_DisplayCommandLineHelp();
	return FALSE;
}

//D2Client.0x6FAA1F50 (#10003)
void __stdcall D2Client_10003()
{
	if (HWND hWnd = WINDOW_GetWindow())
	{
		SendMessageA(hWnd, WM_ACTIVATEAPP, FALSE, 0);
	}

	WINDOW_ShowAll();
}

//D2Client.0x6FAA1F70
D2ConfigStrc* __fastcall CLIENT_GetConfig()
{
	return gpConfig;
}

//D2Client.0x6FAA1F80
BnClientInterface* __fastcall CLIENT_GetComInterface()
{
	return gpConfig->pComInterface;
}

//D2Client.0x6FAA1F90
const char* __fastcall CLIENT_GetGameName()
{
	if (gpConfig && strlen(gpConfig->szGameName))
	{
		return gpConfig->szGameName;
	}

	return nullptr;
}

//D2Client.0x6FAA1FC0
const char* __fastcall CLIENT_GetGamePassword()
{
	if (gpConfig && strlen(gpConfig->szGamePassword))
	{
		return gpConfig->szGamePassword;
	}

	return nullptr;
}

//D2Client.0x6FAA1FF0
const char* __fastcall CLIENT_GetServerIP()
{
	if (gpConfig && strlen(gpConfig->szServerIP))
	{
		return gpConfig->szServerIP;
	}

	return nullptr;
}

//D2Client.0x6FAA2020
uint8_t __fastcall CLIENT_IsHardcore()
{
	return gpConfig->unpackedCTemp.nCharacterSaveFlags & 0x04; // CLIENTSAVEFLAG_HARDCORE
}

//D2Client.0x6FAA2030
void __fastcall CLIENT_SetCharacterDied()
{
	gpConfig->unpackedCTemp.nCharacterSaveFlags |= 0x08; // CLIENTSAVEFLAG_DEAD
}

//D2Client.0x6FAA2040
void __fastcall CLIENT_SetExitToMenu(int32_t bExitToMenu)
{
	gbExitToMenu = bExitToMenu;
}

//D2Client.0x6FAA2050
int32_t __stdcall CLIENT_Main(HINSTANCE hInstance, D2ConfigStrc* pConfig)
{
	gpConfig = pConfig;
	FOG_10144(0);
	FOG_SetMemoryPoolSystemMode(nullptr, 1);
	ghClientInstance = hInstance;
	GetModuleFileNameA(hInstance, gszModulePath, sizeof(gszModulePath));
	SCmdRegisterArgList((int)gaCommandLineArgs, ARRAY_SIZE(gaCommandLineArgs));

	for (int32_t i = 0; i < ARRAY_SIZE(gpfInitializers); ++i)
	{
		if (!gpfInitializers[i]())
		{
			return 0;
		}
	}

	if (!CONFIG_Apply(pConfig))
	{
		return 0;
	}

	char szCommandLine[260] = {};
	if (SRegLoadString("Diablo II", "Default Command Line", 0, szCommandLine, sizeof(szCommandLine)))
	{
		const char* pCommandLine = szCommandLine;
		SCmdProcess(&pCommandLine, 0, (int)CLIENT_OnUnknownCommandLineArgument, (int)CLIENT_OnCommandLineArgumentError);
	}

	DWORD nNameSize = 15;
	if (!gszPlayerName[0] && !GetUserNameA(gszPlayerName, &nNameSize))
	{
		wsprintfA(gszPlayerName, "%s", "noname");
	}

	if (!LNG_Initialize())
	{
		return 0;
	}

	D2Win_10015();
	D2Win_10014_SetWndProc(CLIENT_WindowProc);
	ghClientAccelerators = LoadAcceleratorsA(ghClientInstance, MAKEINTRESOURCEA(101));

	if (!D2LANG_10000(D2Win_GetArchive(), 0, FOG_IsExpansion()))
	{
		return 0;
	}

	char szLanguage[4] = {};
	D2LANG_10006(szLanguage, 0);
	FOG_Trace("%s is locale\n", szLanguage);

	DATATBLS_LoadAllTxts(D2Win_GetArchive(), 0, pConfig->dwGameType == 6);

	gbExitToMenu = TRUE;
	gnAppMode = APPMODE_START;
	do
	{
		gnAppMode = gpfAppModeHandlers[gnAppMode]();
		D2_ASSERT(gnAppMode < APPMODE_LAST);
		D2_ASSERT(gnAppMode > APPMODE_CONTINUE);
	}
	while (gnAppMode != APPMODE_EXIT);

	D2Win_10016();
	DATATBLS_UnloadAllBins();
	D2LANG_10001();
	LNG_Shutdown();
	LOG_11105();
	sub_6FAADC70();

	if (gbExitToMenu)
	{
		gnClientExitCode = 0;
		return 0;
	}

	switch (pConfig->dwGameType)
	{
	case 2:
	case 3:
	case 6:
	case 7:
		gnClientExitCode = 3;
		return 3;

	default:
		gnClientExitCode = 4;
		return 4;
	}
}

//D2Client.0x6FAA22D0
BOOL __stdcall CLIENT_OnUnknownCommandLineArgument(const char* szArgument)
{
	CLIENT_DisplayCommandLineHelp();
	return FALSE;
}

//D2Client.0x6FAA2340
BOOL __stdcall CLIENT_OnCommandLineArgumentError(const char* szArgument)
{
	CLIENT_DisplayCommandLineHelp();
	return FALSE;
}

//D2Client.0x6FAA23B0
void __fastcall CLIENT_SetResolution(int32_t nResolution)
{
	if (nResolution == D2GFX_GetResolutionMode())
	{
		return;
	}

	if (nResolution == 0)
	{
		gnScreenHeight = 480;
		gnScreenWidth = 640;
		gbIsHighResolution = FALSE;
	}
	else if (nResolution == 2)
	{
		gnScreenHeight = 600;
		gnScreenWidth = 800;
		gbIsHighResolution = TRUE;
	}

	gnViewHeight = gnScreenHeight - 40;
	gnScreenWidth2 = gnScreenWidth;
	gnViewWidth = gnScreenWidth;

	D2Win_10005(nResolution);
	sub_6FAB5760(sub_6FAB5750());
	sub_6FACB6E0(1);
	MEMORY_Nop();
	sub_6FB247D0();
}

//D2Client.0x6FAA2460
void __stdcall CLIENT_OnClose(SMSGHANDLER_PARAMS* pMsg)
{
	PostQuitMessage(0);
	pMsg->bUseResult = TRUE;
	pMsg->lResult = 0;
}

//D2Client.0x6FAA2480
void __stdcall CLIENT_OnActivateApp(SMSGHANDLER_PARAMS* pMsg)
{
	gbIsAppActive = pMsg->wParam != 0;
	pMsg->bUseResult = FALSE;
}

//D2Client.0x6FAA24A0
void __stdcall CLIENT_OnDefaultWindowProc(SMSGHANDLER_PARAMS* pMsg)
{
	pMsg->bUseResult = TRUE;
	pMsg->lResult = DefWindowProcA(pMsg->hWindow, pMsg->nMessage, pMsg->wParam, pMsg->lParam);
}

//D2Client.0x6FAA24D0
void __stdcall CLIENT_OnQuitCommand(SMSGHANDLER_PARAMS* pMsg)
{
	SendMessageA(pMsg->hWindow, WM_CLOSE, 0, 0);
	pMsg->bUseResult = TRUE;
	pMsg->lResult = 0;
}

//D2Client.0x6FAA2500
void __stdcall CLIENT_OnIgnoredMessage(SMSGHANDLER_PARAMS* pMsg)
{
	pMsg->bUseResult = TRUE;
	pMsg->lResult = 0;
}

//D2Client.0x6FAA2520
void __stdcall CLIENT_OnUserCommand(SMSGHANDLER_PARAMS* pMsg)
{
	SendMessageA(pMsg->hWindow, WM_USER, 0, 0);
	pMsg->bUseResult = TRUE;
	pMsg->lResult = 0;
}

//D2Client.0x6FAA2550
LRESULT __stdcall CLIENT_WindowProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	BOOL bUseResult = FALSE;
	LRESULT lResult = 0;

	RECORD_ProcessWindowMessage(nMessage, wParam, lParam);

	if (!RECORD_IsPlaying() || nMessage == WM_CLOSE)
	{
		if (SMsgDispatchMessage(hWnd, nMessage, wParam, lParam, &bUseResult, &lResult) && bUseResult)
		{
			return lResult;
		}
	}

	return DefWindowProcA(hWnd, nMessage, wParam, lParam);
}

//D2Client.0x6FAA25D0
BOOL __fastcall CLIENT_RunMessageLoop(CLIENT_IdleCallback pfIdle)
{
	MSG msg = {};
	BOOL bContinue = TRUE;
	int32_t nIteration = 0;

	while (true)
	{
		if (PeekMessageA(&msg, nullptr, 0, 0, PM_NOREMOVE))
		{
			bContinue = GetMessageA(&msg, nullptr, 0, 0);
			if (bContinue)
			{
				const BOOL bTranslated = ghLNGAccelerators && TranslateAcceleratorA(WINDOW_GetWindow(), ghLNGAccelerators, &msg);
				if (!bTranslated && ghClientAccelerators)
				{
					TranslateAcceleratorA(WINDOW_GetWindow(), ghClientAccelerators, &msg);
				}
			}

			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else
		{
			if (pfIdle)
			{
				const int32_t nResult = pfIdle(nIteration);
				++nIteration;
				if (nResult)
				{
					return bContinue ? nResult : TRUE;
				}
			}

			if (!gbIsAppActive && gnGameType != 6 && gnGameType != 8)
			{
				Sleep(10);
			}
		}

		if (!bContinue)
		{
			return TRUE;
		}
	}
}
