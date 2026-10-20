#pragma once

#include <D2Client.h>


enum D2C_AppModes
{
	APPMODE_CONTINUE = 0,
	APPMODE_EXIT = 1,
	APPMODE_GAME = 2,
	APPMODE_START = 3,
	APPMODE_LAST = 12,
	APPMODE_STACK_SIZE = 5,
};

#pragma pack(push, 1)
// Storm CMDPARAMS
struct D2CommandLineParamsStrc
{
	uint32_t dwFlags;						//0x00
	uint32_t dwId;							//0x04
	const char* szName;						//0x08
	void* pCallback;						//0x0C
	uint32_t unk0x10;						//0x10
	uint32_t unk0x14;						//0x14
	char* pszParam;							//0x18
};

using CommandLineArgumentCallback = BOOL(__stdcall*)(D2CommandLineParamsStrc* pParams, uint32_t nUnused);

// Storm ARGLIST
struct D2CommandLineArgStrc
{
	uint32_t dwFlags;						//0x00
	uint32_t dwId;							//0x04
	const char* szName;						//0x08
	CommandLineArgumentCallback pfCallback;	//0x0C
};
#pragma pack(pop)

using CLIENT_IdleCallback = int32_t(__fastcall*)(int32_t nIteration);


//D2Client.0x6FB740EC
extern int32_t gnScreenWidth;
//D2Client.0x6FB740F0
extern int32_t gnScreenHeight;
//D2Client.0x6FB740F4
extern int32_t gnScreenWidth2;
//D2Client.0x6FB744D8
extern int32_t gnAppMode;
//D2Client.0x6FB74538
extern int32_t gbExitToMenu;
//D2Client.0x6FB747C0
extern int32_t gbIsAppActive;
//D2Client.0x6FB9A700
extern int32_t gnViewHeight;
//D2Client.0x6FB9A704
extern int32_t gnViewWidth;
//D2Client.0x6FB9A708
extern int32_t gbIsHighResolution;
//D2Client.0x6FB9A830
extern char gszModulePath[MAX_PATH];
//D2Client.0x6FB9A948
extern D2ConfigStrc* gpConfig;
//D2Client.0x6FB9A94C
extern HINSTANCE ghClientInstance;
//D2Client.0x6FB9A950
extern int32_t gnClientExitCode;
//D2Client.0x6FB9A954
extern HACCEL ghClientAccelerators;


//D2Client.0x6FAA1D00
void __fastcall CLIENT_PushAppMode(int32_t nAppMode);
//D2Client.0x6FAA1D40
int32_t __fastcall CLIENT_PopAppMode();
//D2Client.0x6FAA1DA0
BOOL __stdcall CLIENT_ShowCommandLineHelp(D2CommandLineParamsStrc* pParams, uint32_t nUnused);
//D2Client.0x6FAA1E10
BOOL __stdcall CLIENT_PrecacheMemory(D2CommandLineParamsStrc* pParams, uint32_t nUnused);
//D2Client.0x6FAA1E60
BOOL __stdcall CLIENT_StartRecording(D2CommandLineParamsStrc* pParams, uint32_t nUnused);
//D2Client.0x6FAA1E70
BOOL __stdcall CLIENT_StartPlayback(D2CommandLineParamsStrc* pParams, uint32_t nUnused);
//D2Client.0x6FAA1E80
BOOL __stdcall CLIENT_SetDefaultCommandLine(D2CommandLineParamsStrc* pParams, uint32_t nUnused);
//D2Client.0x6FAA1EA0
BOOL __stdcall CLIENT_SetAppModeFromCommandLine(D2CommandLineParamsStrc* pParams, uint32_t nUnused);
//D2Client.0x6FAA1F50 (#10003)
void __stdcall D2Client_10003();
//D2Client.0x6FAA1F70
D2ConfigStrc* __fastcall CLIENT_GetConfig();
//D2Client.0x6FAA1F80
BnClientInterface* __fastcall CLIENT_GetComInterface();
//D2Client.0x6FAA1F90
const char* __fastcall CLIENT_GetGameName();
//D2Client.0x6FAA1FC0
const char* __fastcall CLIENT_GetGamePassword();
//D2Client.0x6FAA1FF0
const char* __fastcall CLIENT_GetServerIP();
//D2Client.0x6FAA2020
uint8_t __fastcall CLIENT_IsHardcore();
//D2Client.0x6FAA2030
void __fastcall CLIENT_SetCharacterDied();
//D2Client.0x6FAA2040
void __fastcall CLIENT_SetExitToMenu(int32_t bExitToMenu);
//D2Client.0x6FAA2050
int32_t __stdcall CLIENT_Main(HINSTANCE hInstance, D2ConfigStrc* pConfig);
//D2Client.0x6FAA22D0
BOOL __stdcall CLIENT_OnUnknownCommandLineArgument(const char* szArgument);
//D2Client.0x6FAA2340
BOOL __stdcall CLIENT_OnCommandLineArgumentError(const char* szArgument);
//D2Client.0x6FAA23B0
void __fastcall CLIENT_SetResolution(int32_t nResolution);
//D2Client.0x6FAA2460
void __stdcall CLIENT_OnClose(SMSGHANDLER_PARAMS* pMsg);
//D2Client.0x6FAA2480
void __stdcall CLIENT_OnActivateApp(SMSGHANDLER_PARAMS* pMsg);
//D2Client.0x6FAA24A0
void __stdcall CLIENT_OnDefaultWindowProc(SMSGHANDLER_PARAMS* pMsg);
//D2Client.0x6FAA24D0
void __stdcall CLIENT_OnQuitCommand(SMSGHANDLER_PARAMS* pMsg);
//D2Client.0x6FAA2500
void __stdcall CLIENT_OnIgnoredMessage(SMSGHANDLER_PARAMS* pMsg);
//D2Client.0x6FAA2520
void __stdcall CLIENT_OnUserCommand(SMSGHANDLER_PARAMS* pMsg);
//D2Client.0x6FAA2550
LRESULT __stdcall CLIENT_WindowProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam);
//D2Client.0x6FAA25D0
BOOL __fastcall CLIENT_RunMessageLoop(CLIENT_IdleCallback pfIdle);
