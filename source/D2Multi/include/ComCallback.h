#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2Unicode.h>

struct D2CompositeUnitStrc;
struct SMSGHANDLER_PARAMS;

#define COMCALLBACK_MAX_USER_HISTORY 1024

// Battle.net chat event ids, the index in gapfComCallbacks_6F9BE798
enum D2MultiChatEvent
{
	CHATEVENT_SHOWUSER = 0x01,
	CHATEVENT_JOIN = 0x02,
	CHATEVENT_LEAVE = 0x03,
	CHATEVENT_WHISPER = 0x04,
	CHATEVENT_TALK = 0x05,
	CHATEVENT_BROADCAST = 0x06,
	CHATEVENT_CHANNEL = 0x07,
	CHATEVENT_USERFLAGS = 0x09,
	CHATEVENT_WHISPERSENT = 0x0A,
	CHATEVENT_CHANNELFULL = 0x0D,
	CHATEVENT_CHANNELDOESNOTEXIST = 0x0E,
	CHATEVENT_CHANNELRESTRICTED = 0x0F,
	CHATEVENT_INFO = 0x12,
	CHATEVENT_ERROR = 0x13,
	CHATEVENT_EMOTE = 0x17,
	CHATEVENT_COUNT = 0x18,
};

// Battle.net user flags sent with the chat events
enum D2MultiChatUserFlags
{
	CHATUSERFLAG_BLIZZARDREPRESENTATIVE = 0x01,
	CHATUSERFLAG_CHANNELOPERATOR = 0x02,
	CHATUSERFLAG_SPEAKER = 0x04,
	CHATUSERFLAG_BATTLENETADMINISTRATOR = 0x08,
	CHATUSERFLAG_SQUELCHED = 0x20,
};

#pragma pack(push, 1)
// User present in the current channel
struct D2MultiChannelUserStrc
{
	uint32_t dwProduct;							//0x00 First 4 characters of the statstring, 'NKNU' if unknown
	char szUserName[50];						//0x04 "CharacterName*AccountName" or "*AccountName"
	char szCharacterName[16];					//0x36
	char szRealmName[32];						//0x46
	uint8_t pComponents[16];					//0x66
	uint8_t pComponentColors[16];				//0x76
	uint8_t nClass;								//0x86
	uint8_t unk0x87;							//0x87
	uint16_t nLevel;							//0x88
	uint16_t nCharacterFlags;					//0x8A D2ClientSaveFlags
	uint16_t nGuildFlags;						//0x8C
	uint16_t unk0x8E;							//0x8E
	uint32_t dwChatFlags;						//0x90 D2MultiChatUserFlags
	uint8_t nLadder;							//0x94
	uint8_t unk0x95;							//0x95
	uint8_t unk0x96;							//0x96
	char szUnk0x97[5];							//0x97 Never filled, but given to D2Win_10154 as a string
	D2CompositeUnitStrc* pCompositeUnit;		//0x9C
	BOOL bHardcore;								//0xA0
	BOOL bDead;									//0xA4
	BOOL bExpansion;							//0xA8
	BOOL bLadder;								//0xAC
	D2MultiChannelUserStrc* pNext;				//0xB0
};

// Remembers the character name used by an account, even after it left the channel
struct D2MultiUserHistoryStrc
{
	char szUserName[50];						//0x00
	char szCharacterName[18];					//0x32
	D2MultiUserHistoryStrc* pNext;				//0x44
};
#pragma pack(pop)

typedef int32_t(__fastcall* D2MultiChatEventCallback)(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText);

extern D2MultiChannelUserStrc* gpChannelUsers_6F9C2B1C;
extern D2MultiChannelUserStrc* gptSelectedUnit_6F9C2B30;
extern int32_t gnSelectedUserIndex_6F9BE790;

//D2Multi.0x6F9AB3E0
BOOL __fastcall COMCALLBACK_ProcessMessages();
//D2Multi.0x6F9AB5B0
void __fastcall COMCALLBACK_ScrollUserList(int32_t nDelta);
//D2Multi.0x6F9AB640
int32_t __stdcall COMCALLBACK_UserButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9ABB50
int32_t __stdcall COMCALLBACK_SendButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9ABBB0
int32_t __stdcall COMCALLBACK_WhisperButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9ABC10
int32_t __stdcall COMCALLBACK_SquelchButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9ABE20
int32_t __stdcall COMCALLBACK_HelpButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9ABE40
int32_t __stdcall COMCALLBACK_UnsquelchButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AC050
int32_t __stdcall COMCALLBACK_EmoteButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AC0E0
char* __fastcall COMCALLBACK_GetChannelName();
//D2Multi.0x6F9AC0F0
int32_t __fastcall COMCALLBACK_OnUnknownEvent(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText);
//D2Multi.0x6F9AC100
void __fastcall COMCALLBACK_UpdateUserList();
//D2Multi.0x6F9AC570
int32_t __fastcall COMCALLBACK_OnShowUser(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szStatstring);
//D2Multi.0x6F9AC590
D2MultiChannelUserStrc* __fastcall COMCALLBACK_AddUser(const char* szUserName, const char* szStatstring, uint32_t nFlags);
//D2Multi.0x6F9AC970
uint8_t __fastcall COMCALLBACK_ParseStatstring(D2MultiChannelUserStrc* pUser, const char* szStatstring, uint32_t nFlags);
//D2Multi.0x6F9ACD50
void __fastcall COMCALLBACK_UpdateUserDescription(D2MultiChannelUserStrc* pUser);
//D2Multi.0x6F9ACF10
int32_t __fastcall COMCALLBACK_OnJoin(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szStatstring);
//D2Multi.0x6F9AD050
void __fastcall COMCALLBACK_ClearUserList();
//D2Multi.0x6F9AD2F0
int32_t __fastcall COMCALLBACK_OnLeave(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText);
//D2Multi.0x6F9AD5F0
void __fastcall COMCALLBACK_RemoveColorCodes(Unicode* wszText);
//D2Multi.0x6F9AD680
int32_t __fastcall COMCALLBACK_OnChannel(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szChannelName);
//D2Multi.0x6F9AD800
int32_t __fastcall COMCALLBACK_OnUserFlags(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szStatstring);
//D2Multi.0x6F9AD8E0
void __fastcall COMCALLBACK_AddOwnMessage(const char* szText);
//D2Multi.0x6F9ADCE0
void __fastcall COMCALLBACK_AddUserHistory(const char* szUserName, const char* szCharacterName);
//D2Multi.0x6F9ADE40
void __fastcall COMCALLBACK_GetUserDisplayName(const char* szUserName, char* szTitle, char* szCharacterName);
//D2Multi.0x6F9ADFC0
int32_t __fastcall COMCALLBACK_OnTalk(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText);
//D2Multi.0x6F9AE3B0
int32_t __fastcall COMCALLBACK_OnInfo(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText);
//D2Multi.0x6F9AE490
int32_t __fastcall COMCALLBACK_OnError(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText);
//D2Multi.0x6F9AE570
int32_t __fastcall COMCALLBACK_OnChannelFull(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szChannelName);
//D2Multi.0x6F9AE670
int32_t __fastcall COMCALLBACK_OnChannelRestricted(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szChannelName);
//D2Multi.0x6F9AE770
int32_t __fastcall COMCALLBACK_OnChannelDoesNotExist(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szChannelName);
//D2Multi.0x6F9AE790
int32_t __fastcall COMCALLBACK_OnEmote(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText);
//D2Multi.0x6F9AEA10
int32_t __fastcall COMCALLBACK_OnWhisper(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText);
//D2Multi.0x6F9AED90
int32_t __fastcall COMCALLBACK_OnWhisperSent(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText);
//D2Multi.0x6F9AF020
int32_t __fastcall COMCALLBACK_OnIgnoredEvent(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText);
//D2Multi.0x6F9AF030
void __fastcall COMCALLBACK_UpdateChatButtons();
//D2Multi.0x6F9AF110
void __fastcall COMCALLBACK_AppendColorCode(Unicode* wszText, int32_t nColor);
//D2Multi.0x6F9AF1F0
void __fastcall COMCALLBACK_PrependColorCode(Unicode* wszText, int32_t nColor);
