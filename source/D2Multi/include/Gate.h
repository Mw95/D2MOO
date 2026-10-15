#pragma once

#include <Windows.h>
#include <cstdint>

struct SMSGHANDLER_PARAMS;
struct D2WinControlStrc;

#define GATE_MAX_GAMES 1000

#pragma pack(push, 1)
// Game listed in the join game dialog
struct D2MultiGameListEntryStrc
{
	uint8_t unk0x00;							//0x00
	char szGameName[16];						//0x01
	char szGameDescription[32];					//0x11
	uint16_t nPlayers;							//0x31
	uint16_t nGameToken;						//0x33
	uint32_t nIpAddress;						//0x37
};

// Game list entry as sent by the MCP (MCP_GAMELIST)
struct D2MultiMCPGameListStrc
{
	uint32_t nType;								//0x00 0 for a game list entry
	uint16_t nRequestId;						//0x04
	uint16_t unk0x06;							//0x06
	uint16_t nGameToken;						//0x08
	uint16_t unk0x0A;							//0x0A
	uint32_t unk0x0C;							//0x0C
	uint32_t unk0x10;							//0x10
	uint16_t nPlayers;							//0x14
	uint16_t unk0x16;							//0x16
	uint32_t unk0x18;							//0x18
	char szGameName[16];						//0x1C
	char szGameDescription[32];					//0x2C
};

// Game info as sent by the MCP (MCP_GAMEINFO)
struct D2MultiMCPGameInfoStrc
{
	uint32_t nType;								//0x00
	uint16_t nRequestId;						//0x04
	uint16_t unk0x06;							//0x06
	uint32_t unk0x08;							//0x08
	uint32_t nUptime;							//0x0C In seconds
	uint8_t nLevel;								//0x10
	uint8_t nLevelDifference;					//0x11
	uint8_t nMaxPlayers;						//0x12
	uint8_t unk0x13;							//0x13
	int32_t nPlayers;							//0x14
	uint8_t unk0x18[20];						//0x18
	char szGameDescription[32];					//0x2C
	uint16_t nClasses[16];						//0x4C
	uint16_t nLevels[16];						//0x6C
	char szCharacterNames[16][16];				//0x8C
};
#pragma pack(pop)

//D2Multi.0x6F9AF3C0
void __fastcall GATE_RequestBattleNetGameList();
//D2Multi.0x6F9AF5D0
void __fastcall GATE_AddMCPGame(D2MultiMCPGameListStrc* pGame);
//D2Multi.0x6F9AF660
void __fastcall GATE_CreateJoinDialog();
//D2Multi.0x6F9AF920
void __fastcall GATE_RequestGameList();
//D2Multi.0x6F9AF9A0
void __fastcall GATE_UpdateGameList();
//D2Multi.0x6F9AFB40
int32_t __stdcall GATE_JoinNameInputCallback(int32_t a1, int32_t a2, const char* pKey);
//D2Multi.0x6F9AFBF0
void __stdcall GATE_JoinNameChangeCallback(int32_t a1);
//D2Multi.0x6F9AFC50
void __fastcall GATE_RequestSelectedGameInfo();
//D2Multi.0x6F9AFC80
int32_t __stdcall GATE_GameListCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AFE10
void __fastcall GATE_ShowGameInfo(D2MultiMCPGameInfoStrc* pGameInfo);
//D2Multi.0x6F9B0080
void __fastcall GATE_CloseJoinDialog();
//D2Multi.0x6F9B0100
void __fastcall GATE_UpdateLevelDifferenceControls();
//D2Multi.0x6F9B0240
void __fastcall GATE_ShowGameQueue();
//D2Multi.0x6F9B03E0
int32_t __stdcall GATE_GameQueueTimerCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B0400
void __fastcall GATE_CreateCreateDialog();
//D2Multi.0x6F9B0C80
void __fastcall GATE_CloseCreateDialog();
//D2Multi.0x6F9B0DC0
int32_t __stdcall GATE_LevelDifferenceCheckboxCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B0F10
int32_t __stdcall GATE_MaxPlayersUpCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B0F70
int32_t __stdcall GATE_MaxPlayersDownCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B0FD0
int32_t __stdcall GATE_LevelDifferenceUpCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1030
int32_t __stdcall GATE_LevelDifferenceDownCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1090
int32_t __stdcall GATE_GameNameInputCallback(int32_t a1, int32_t a2, const char* pKey);
//D2Multi.0x6F9B1130
int32_t __stdcall GATE_TextInputCallback(int32_t a1, int32_t a2, const char* pKey);
//D2Multi.0x6F9B1160
void __stdcall GATE_GameNameChangeCallback(int32_t a1);
//D2Multi.0x6F9B1170
void __stdcall GATE_MaxPlayersChangeCallback(int32_t a1);
//D2Multi.0x6F9B1180
void __stdcall GATE_LevelDifferenceChangeCallback(int32_t a1);
//D2Multi.0x6F9B1190
void __fastcall GATE_UpdateCreateButton();
//D2Multi.0x6F9B1300
void __stdcall GATE_WaitCreateGameResultCallback(DWORD dwCounter);
//D2Multi.0x6F9B1330
void __stdcall GATE_WaitGameQueueCallback(DWORD dwCounter);
//D2Multi.0x6F9B1370
int32_t __stdcall GATE_GameQueueCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1390
int32_t __stdcall GATE_CreateGameCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1760
int32_t __stdcall GATE_CancelGameCreationCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1770
int32_t __fastcall GATE_FindBattleNetGame(const char* szGameName, const char* szGamePassword, D2MultiGameListEntryStrc* pGame);
//D2Multi.0x6F9B1920
int32_t __stdcall GATE_JoinGameCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1CA0
int32_t __stdcall GATE_JoinButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1CF0
int32_t __stdcall GATE_CreateButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1D30
int32_t __stdcall GATE_ClickBoxCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1D40
int32_t __stdcall GATE_NormalDifficultyCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1D90
int32_t __stdcall GATE_NightmareDifficultyCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1DE0
int32_t __stdcall GATE_HellDifficultyCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B1E30
void __fastcall GATE_ShowOwnProfile(const char* szCharacterName, BOOL bHardcore, BOOL bExpansion);
//D2Multi.0x6F9B20F0
void __fastcall GATE_ShowProfile(const char* szUserName, const char* szCharacterName, BOOL bHardcore, BOOL bExpansion);
//D2Multi.0x6F9B2340
void __fastcall GATE_CloseProfileDialog();
//D2Multi.0x6F9B2420
int32_t __stdcall GATE_ProfileLadderCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B2550
void __fastcall GATE_GetProfileCharacterName(char* szCharacterName);
//D2Multi.0x6F9B2570
int32_t __stdcall GATE_ProfileCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B2660
int32_t __stdcall GATE_ProfileOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9B27E0
void __fastcall GATE_ShowHelp();
//D2Multi.0x6F9B35E0
int32_t __fastcall GATE_CloseHelp();

extern BOOL gbHelpOpened_6F9DFA40;
