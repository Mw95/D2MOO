#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2Unicode.h>
#include <D2WinComp.h>

struct SMSGHANDLER_PARAMS;

enum D2CharSelNodeType
{
	CHARSELNODE_CHARACTER = 0,		// eCharacter
	CHARSELNODE_CREATE_NEW = 1,		// Classic only, "Create New Character" entry
	CHARSELNODE_MORE_CHARACTERS = 2,	// The account has more characters than what was returned by the realm
};

#pragma pack(push, 1)
struct D2CharSelNodeStrc
{
	char szName[256];							//0x000
	Unicode wszRealm[256];						//0x100
	uint8_t pComponents[16];					//0x300
	uint8_t pComponentColors[16];				//0x310
	uint8_t nClass;								//0x320
	uint8_t pad0x321;							//0x321
	uint16_t nLevel;							//0x322
	uint16_t nFlags;							//0x324 D2ClientSaveFlags
	uint16_t nVersion;							//0x326
	uint16_t nGuildFlags;						//0x328
	char szGuildTag[4];							//0x32A
	uint8_t bLadder;							//0x32E
	uint8_t unk0x32F;							//0x32F
	uint8_t unk0x330;							//0x330
	uint8_t pad0x331[3];						//0x331
	int32_t eType;								//0x334 D2CharSelNodeType
	D2CompositeUnitStrc* hUnit;					//0x338
	uint32_t unk0x33C;							//0x33C
	uint32_t dwLastWriteTimeLow;				//0x340
	uint32_t dwLastWriteTimeHigh;				//0x344
	uint32_t dwExpirationTime;					//0x348
	D2CharSelNodeStrc* pNext;					//0x34C
};

struct D2RealmCharListCacheStrc
{
	uint32_t dwRealmNameHash;					//0x00
	uint8_t* pCharListPacket;					//0x04
	DWORD dwExpirationTickCount;				//0x08
	D2RealmCharListCacheStrc* pNext;			//0x0C
};
#pragma pack(pop)

extern BOOL gbAllowHardcore;

//D2Launch.0x6FA12FC0
uint8_t* __fastcall CHARSEL_GetCachedRealmCharList(const char* szRealmName);
//D2Launch.0x6FA13000
void __fastcall CHARSEL_CacheRealmCharList(const char* szRealmName, const uint8_t* pPacket, size_t nPacketSize);
//D2Launch.0x6FA130E0
void __fastcall CHARSEL_FreeRealmCharListCache();
//D2Launch.0x6FA13130
int32_t __stdcall CHARSEL_RealmSelectOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA13230
int32_t __stdcall CHARSEL_RealmSelectCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA134B0
int32_t __stdcall CHARSEL_RealmListClickCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA13820
int32_t __stdcall CHARSEL_ChangeRealmCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA13AE0
const char* __fastcall CHARSEL_GetPreferredRealmName();
//D2Launch.0x6FA13AF0
void __fastcall CHARSEL_FreeSelectedCharacter();
//D2Launch.0x6FA13B40
void __fastcall CHARSEL_UpdateCharacterList();
//D2Launch.0x6FA14520
Unicode* __fastcall CHARSEL_GetClassName(Unicode* wszBuffer, uint8_t nClass);
//D2Launch.0x6FA14600
uint32_t __fastcall CHARSEL_GetDaysBeforeExpiration(uint32_t dwExpirationTime);
//D2Launch.0x6FA14630
void __fastcall CHARSEL_FreeCharacterList();
//D2Launch.0x6FA146D0
BOOL __fastcall CHARSEL_LoadLocalCharacters();
//D2Launch.0x6FA147F0
BOOL __fastcall CHARSEL_AddCharacter(const char* szName, const char* szRealmName, const uint8_t* pStatString, uint32_t dwExpirationTime, uint32_t dwLastWriteTimeLow, uint32_t dwLastWriteTimeHigh);
//D2Launch.0x6FA14D30
BOOL __fastcall CHARSEL_UpdateSelection();
//D2Launch.0x6FA15520
int32_t __stdcall CHARSEL_CharacterSlotClickCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15600
void __fastcall CHARSEL_ShowDifficultySelection(int32_t nProgression, BOOL bExpansion);
//D2Launch.0x6FA156C0
int32_t __stdcall CHARSEL_OkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15960
int32_t __stdcall CHARSEL_NormalDifficultyCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA159F0
int32_t __stdcall CHARSEL_NightmareDifficultyCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15A80
int32_t __stdcall CHARSEL_HellDifficultyCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15B10
int32_t __stdcall CHARSEL_ConvertToExpansionCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15BD0
int32_t __stdcall CHARSEL_ConvertToExpansionCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15BF0
int32_t __stdcall CHARSEL_ConvertToExpansionConfirmCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15DC0
int32_t __stdcall CHARSEL_DeleteCharacterCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15DD0
int32_t __stdcall CHARSEL_DeleteCharacterCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15E50
int32_t __stdcall CHARSEL_DeleteCharacterConfirmCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15F40
int32_t __stdcall CHARSEL_ScrollUpCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15F70
int32_t __stdcall CHARSEL_ScrollDownCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA15FC0
int32_t __stdcall CHARSEL_ScrollBarCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA16030
int32_t __stdcall CHARSEL_ExpansionKeyDownCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA16260
int32_t __stdcall CHARSEL_KeyDownCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA16350
void __fastcall CHARSEL_LoadRealmCharacters(const char* szRealmName, const uint8_t* pPacket, BOOL bCache);
//D2Launch.0x6FA164F0
int32_t __stdcall CHARSEL_RealmTimerCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA16710
BOOL __fastcall CHARSEL_InitializeRealmSelection();
//D2Launch.0x6FA168F0
void __fastcall CHARSEL_CreateExpansionMenu();
//D2Launch.0x6FA16E50
void __fastcall CHARSEL_CreateMenu();
//D2Launch.0x6FA175C0
BOOL __fastcall CHARSEL_AddSpecialNode(const Unicode* wszName, const Unicode* wszText, int32_t eType, uint8_t nClass);
