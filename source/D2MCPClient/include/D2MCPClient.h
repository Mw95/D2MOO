#pragma once


#include <Windows.h>

#include <cstdint>


//1.10f Image base: 0x6F9F0000

// D2MCPClient implements the client side of the Realm server protocol (MCP),
// used for character management and game creation/joining on closed Battle.net.
//
// Overview:
// - D2MCPClientConnect starts a thread that opens a Fog client connection to the realm (address obtained from Battle.net),
//   sends the protocol selection byte and MCP_STARTUP, then waits up to 60 seconds for the server to answer.
// - Messages received from the server are queued by Fog. Only MCP_STARTUP is handled directly on the network thread,
//   every other message is handled when the game polls D2MCPClientProcessMessages (one message per call).
// - Requests are sent with the D2MCPClient<Request> functions. Most of them reset the last error to MCPCLIENT_ERROR_NONE,
//   and the game then polls the matching "Received" flag and D2MCPClientGetLastError to get the server answer.
// - Requests carrying a request id (game creation/join/list/info, character deletion, messages 0x08/0x09) remember it as the
//   pending request id. Answers carrying another request id are ignored, except for messages 0x08/0x09.

#ifdef D2_VERSION_110F
constexpr int D2MCPClientImageBase = 0x6F9F0000;
#endif

// Messages exchanged with the Realm server (MCP). The values are the first byte of each message.
// The purpose of messages 0x08 to 0x10 is unknown (they are not documented by the community either),
// their payload is described on the functions sending/handling them.
enum D2C_MCPMessages : uint8_t
{
	MCP_STARTUP = 0x01,				// C->S: realm cookie and status from SID_LOGONREALMEX, unique name. S->C: result
	MCP_CHARCREATE = 0x02,			// C->S: class, flags, name. S->C: result
	MCP_CREATEGAME = 0x03,			// C->S: request id, difficulty, level difference, max players, name, password, description. S->C: request id, game token, result
	MCP_JOINGAME = 0x04,			// C->S: request id, name, password. S->C: request id, game token, game server ip, game hash, result
	MCP_GAMELIST = 0x05,			// C->S: request id, search string. S->C: one message per game (request id, index, players, status, name, description)
	MCP_GAMEINFO = 0x06,			// C->S: request id, name. S->C: request id, status, uptime, players, description and characters
	MCP_CHARLOGON = 0x07,			// C->S: name. S->C: result
	MCP_MSG_08 = 0x08,				// C->S: request id, string. S->C: request id, data forwarded to a callback
	MCP_MSG_09 = 0x09,				// C->S: request id, string. S->C: request id, data forwarded to a callback
	MCP_CHARDELETE = 0x0A,			// C->S: request id, name. S->C: request id, result
	MCP_MSG_0B = 0x0B,				// C->S: two strings. S->C: result
	MCP_MSG_0C = 0x0C,				// C->S: string. S->C: result
	MCP_MSG_0D = 0x0D,				// C->S: no data. S->C: result
	MCP_MSG_0E = 0x0E,				// S->C only: two strings
	MCP_MSG_0F = 0x0F,				// C->S: no data. S->C: result
	MCP_MSG_10 = 0x10,				// C->S: no data. S->C: game token, game hash, game server ip, result
	MCP_REQUESTLADDERDATA = 0x11,	// C->S: ladder type, starting position. S->C: ladder data, possibly split in several chunks
	MCP_MOTD = 0x12,				// C->S: no data. S->C: message of the day
	MCP_CANCELGAMECREATE = 0x13,	// C->S only: no data, leaves the game creation queue
	MCP_CREATEQUEUE = 0x14,			// S->C only: position in the game creation queue
	MCP_CHARRANK = 0x16,			// C->S only: two DWORDs, name. The answer is not handled
	MCP_CHARLIST = 0x17,			// S->C only: character list (pre 1.10 format), stored as is
	MCP_CHARUPGRADE = 0x18,			// C->S: name (converts a classic character to expansion). S->C: result
	MCP_CHARLIST2 = 0x19,			// C->S: number of characters to list. S->C: character list with expiration dates, stored as is

	NUM_MCP_MESSAGES = 0x1A,
};

// Error codes reported through D2MCPClientGetLastError, besides the result codes sent by the server.
enum D2C_MCPClientErrors : uint32_t
{
	MCPCLIENT_ERROR_NONE = 0,
	MCPCLIENT_ERROR_CONNECTION_FAILED = 2,		// Connection failed, lost or MCP_STARTUP not answered in time
	MCPCLIENT_ERROR_STARTUP_SEND_FAILED = 11,	// MCP_STARTUP could not be sent
	MCPCLIENT_ERROR_GAME_NOT_FOUND = 40,		// MCP_JOINGAME/MCP_MSG_10 answered without game server ip nor error
	MCPCLIENT_ERROR_GAME_LIST_FAILED = 50,		// MCP_GAMELIST/MCP_GAMEINFO answered with status -1
	MCPCLIENT_ERROR_GAME_LIST_UNAVAILABLE = 51,	// MCP_GAMELIST/MCP_GAMEINFO answered with status -2
};

#pragma pack(push, 1)

// Realm logon information obtained from Battle.net (SID_LOGONREALMEX), see S2C_Packet_SID_LOGONREALMEX
struct D2MCPConnectInfoStrc				// sizeof 0x148
{
	uint32_t dwMCPCookie;				// 0x00
	uint32_t dwMCPStatus;				// 0x04
	uint32_t dwMCPChunk1[2];			// 0x08
	uint32_t dwMCPIp;					// 0x10
	uint32_t dwMCPPort;					// 0x14
	uint32_t dwMCPChunk2[12];			// 0x18
	char szBattleNetUniqueName[256];	// 0x48
};

// Parameters of D2MCPClientCreateGame
struct D2MCPCreateGameInfoStrc			// sizeof 0x47
{
	char szGameName[16];				// 0x00
	char szGamePassword[16];			// 0x10
	char szGameDescription[32];			// 0x20
	uint32_t dwDifficulty;				// 0x40
	uint8_t nUnk0x44;					// 0x44 Sent as is
	uint8_t nLevelDifference;			// 0x45 Maximum level difference with the game creator
	uint8_t nMaxPlayers;				// 0x46
};

// Parameters of D2MCPClientRequestGameList
struct D2MCPGameListRequestStrc			// sizeof 0x18
{
	char szSearchString[20];			// 0x00
	uint32_t dwUnk0x14;					// 0x14 Sent as is
};

// Filled by MCP_GAMELIST (one game per message) and MCP_GAMEINFO responses, see D2MCPClientGetGameInfo
struct D2MCPGameInfoStrc				// sizeof 0x18C
{
	BOOL bMoreData;						// 0x00 MCP_GAMELIST: TRUE if the message contains more data after the game description
	uint16_t nRequestId;				// 0x04 Request id of the last answer
	uint16_t pad0x06;					// 0x06
	uint32_t dwIndex;					// 0x08 MCP_GAMELIST: index of the game in the list
	uint32_t dwUptime;					// 0x0C MCP_GAMEINFO: time since the game creation, in seconds
	uint8_t nUnk0x10;					// 0x10 MCP_GAMEINFO
	uint8_t nUnk0x11;					// 0x11 MCP_GAMEINFO
	uint8_t nMaxPlayers;				// 0x12 MCP_GAMEINFO
	uint8_t pad0x13;					// 0x13
	uint32_t nPlayers;					// 0x14
	int32_t nStatus;					// 0x18 Game status, -1 and -2 are errors (see D2C_MCPClientErrors)
	char szGameName[16];				// 0x1C MCP_GAMELIST
	char szGameDescription[32];			// 0x2C
	uint16_t nPlayerClass[16];			// 0x4C MCP_GAMEINFO
	uint16_t nPlayerLevel[16];			// 0x6C MCP_GAMEINFO
	char szPlayerName[16][16];			// 0x8C MCP_GAMEINFO
};

// Header of the MCP_CHARLIST and MCP_CHARLIST2 messages. Names come from the original asserts.
struct D2MCPCharListStrc				// sizeof 0x09
{
	uint8_t nMessageId;					// 0x00 MCP_CHARLIST or MCP_CHARLIST2
	uint16_t count;						// 0x01
	uint16_t firstChar;					// 0x03
	uint16_t totalChars;				// 0x05
	uint16_t maxCharsAllowed;			// 0x07 MCP_CHARLIST2: number of characters following the header
	// Followed by the characters. For MCP_CHARLIST2, each one is a DWORD (expiration date), the name and the stats string.
};

#pragma pack(pop)

// Receives the answer to MCP_MSG_08/MCP_MSG_09, regardless of the pending request id
using MCPRequestCallback = void(__fastcall*)(uint16_t nRequestId, const uint8_t* pData);
// Called for each block of a reassembled ladder response. Each of the nEntries entries is 12 bytes followed by nNameSize bytes of character name.
// Also called with all parameters set to 0 when the server answers with an empty response.
using MCPLadderDataCallback = void(__fastcall*)(int32_t nStartingPosition, int32_t nEntries, int32_t nNameSize, uint8_t nLadderType, const uint8_t* pEntries);
// Called once a ladder response is complete, before the MCPLadderDataCallback calls
using MCPLadderDataBeginCallback = void(__fastcall*)();
// Receives the message of the day, pData is not guaranteed to be null terminated
using MCPMotdCallback = void(__fastcall*)(uint8_t nUnk, uint32_t nSize, const uint8_t* pData);

// Connection
// Starts the connection thread (if not already started) and returns its handle. The thread exit code is FALSE if the connection
// could not be established, TRUE otherwise, in which case D2MCPClientGetLastError tells whether MCP_STARTUP succeeded.
//D2MCPClient.0x6F9F17D0 (#10000)
D2MCPCLIENT_DLL_DECL HANDLE __stdcall D2MCPClientConnect(const D2MCPConnectInfoStrc* pConnectInfo);
// Closes the connection and waits for the connection thread to finish
//D2MCPClient.0x6F9F1980 (#10001)
D2MCPCLIENT_DLL_DECL void __cdecl D2MCPClientCloseMCP();
//D2MCPClient.0x6F9F19E0 (#10002)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientIsConnected();
// Handles at most one received message. Returns FALSE if there is no connection.
//D2MCPClient.0x6F9F1A20 (#10003)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientProcessMessages();
//D2MCPClient.0x6F9F17C0 (#10055)
D2MCPCLIENT_DLL_DECL HANDLE __cdecl D2MCPClientGetConnectionThread();

// Requests. They all return the result of FOG_10070_ClientSendMessage.
//D2MCPClient.0x6F9F1CA0 (#10008)
D2MCPCLIENT_DLL_DECL BOOL __stdcall D2MCPClientCharCreate(const char* szCharName, uint32_t nClass, uint16_t nFlags);
//D2MCPClient.0x6F9F1CC0 (#10009)
D2MCPCLIENT_DLL_DECL BOOL __stdcall D2MCPClientCharLogon(const char* szCharName);
//D2MCPClient.0x6F9F2180 (#10004)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientCreateGame(const D2MCPCreateGameInfoStrc* pCreateGameInfo, uint16_t nRequestId);
//D2MCPClient.0x6F9F2300 (#10005)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientJoinGame(const char* szGameName, const char* szGamePassword, uint16_t nRequestId);
//D2MCPClient.0x6F9F2400 (#10006)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientRequestGameList(const D2MCPGameListRequestStrc* pRequest, uint16_t nRequestId);
//D2MCPClient.0x6F9F2490 (#10007)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientRequestGameInfo(const char* szGameName, uint16_t nRequestId);
//D2MCPClient.0x6F9F2520 (#10013)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientSendMsg08(const char* szString, uint16_t nRequestId);
//D2MCPClient.0x6F9F25D0 (#10014)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientSendMsg09(const char* szString, uint16_t nRequestId);
//D2MCPClient.0x6F9F2680 (#10021)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientCharDelete(const char* szCharName, uint16_t nRequestId);
//D2MCPClient.0x6F9F2730 (#10022)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientSendMsg0B(const char* szString1, const char* szString2);
//D2MCPClient.0x6F9F2820 (#10023)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientSendMsg0C(const char* szString);
//D2MCPClient.0x6F9F28C0 (#10024)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientSendMsg0D();
//D2MCPClient.0x6F9F28F0 (#10025)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientSendMsg0F();
//D2MCPClient.0x6F9F2920 (#10026)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientSendMsg10();
//D2MCPClient.0x6F9F2950 (#10027)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientRequestLadderData(uint8_t nLadderType, uint16_t nStartingPosition);
//D2MCPClient.0x6F9F2990 (#10049)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientRequestMotd();
//D2MCPClient.0x6F9F29C0 (#10054)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientCancelGameCreate();
//D2MCPClient.0x6F9F29F0 (#10056)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientRequestCharList();
//D2MCPClient.0x6F9F2A20 (#10059)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientCharRank(const char* szCharName, uint32_t dwUnk1, uint32_t dwUnk2);
//D2MCPClient.0x6F9F26E0 (#10062)
D2MCPCLIENT_DLL_DECL BOOL __fastcall D2MCPClientCharUpgrade(const char* szCharName);

// Callbacks, called from D2MCPClientProcessMessages
//D2MCPClient.0x6F9F1780 (#10011)
D2MCPCLIENT_DLL_DECL void __fastcall D2MCPClientSetMsg08Callback(MCPRequestCallback pCallback);
//D2MCPClient.0x6F9F1790 (#10010)
D2MCPCLIENT_DLL_DECL void __fastcall D2MCPClientSetMsg09Callback(MCPRequestCallback pCallback);
//D2MCPClient.0x6F9F17A0 (#10012)
D2MCPCLIENT_DLL_DECL void __fastcall D2MCPClientSetLadderDataCallbacks(MCPLadderDataCallback pCallback, MCPLadderDataBeginCallback pBeginCallback);
//D2MCPClient.0x6F9F17B0 (#10048)
D2MCPCLIENT_DLL_DECL void __fastcall D2MCPClientSetMotdCallback(MCPMotdCallback pCallback);

// State
// Last error, either a D2C_MCPClientErrors value or the result sent by the server
//D2MCPClient.0x6F9F1AB0 (#10046)
D2MCPCLIENT_DLL_DECL uint32_t __cdecl D2MCPClientGetLastError();
//D2MCPClient.0x6F9F1AA0 (#10047)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetLastError(uint32_t nError);
// Game server address of the last game joined (MCP_JOINGAME or MCP_MSG_10)
//D2MCPClient.0x6F9F1A70 (#10015)
D2MCPCLIENT_DLL_DECL const char* __cdecl D2MCPClientGetGameServerIp();
// Request id of the last answered MCP_CREATEGAME/MCP_JOINGAME
//D2MCPClient.0x6F9F1A80 (#10016)
D2MCPCLIENT_DLL_DECL uint16_t __cdecl D2MCPClientGetGameRequestId();
// Game token of the last game created or joined, reset by D2MCPClientCreateGame
//D2MCPClient.0x6F9F1A90 (#10017)
D2MCPCLIENT_DLL_DECL uint32_t __cdecl D2MCPClientGetGameToken();
// Game hash of the last game joined (MCP_JOINGAME or MCP_MSG_10)
//D2MCPClient.0x6F9F1C90 (#10018)
D2MCPCLIENT_DLL_DECL uint32_t __cdecl D2MCPClientGetGameHash();
//D2MCPClient.0x6F9F1C00 (#10019)
D2MCPCLIENT_DLL_DECL D2MCPGameInfoStrc* __cdecl D2MCPClientGetGameInfo();
//D2MCPClient.0x6F9F1C10 (#10020)
D2MCPCLIENT_DLL_DECL void __cdecl D2MCPClientClearGameInfo();
// Last MCP_CHARLIST/MCP_CHARLIST2 message received, or nullptr
//D2MCPClient.0x6F9F1D10 (#10057)
D2MCPCLIENT_DLL_DECL D2MCPCharListStrc* __cdecl D2MCPClientGetCharacterList();
// Replaces the stored character list by a copy of pMessage, or frees it if nMessageSize is 0
//D2MCPClient.0x6F9F1D20 (#10058)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetCharacterList(const uint8_t* pMessage, uint32_t nMessageSize);
// Copies the strings of the last MCP_MSG_0E message (szString1 must hold 36 bytes, szString2 28 bytes) and returns whether one was received
//D2MCPClient.0x6F9F1B80 (#10038)
D2MCPCLIENT_DLL_DECL BOOL __stdcall D2MCPClientGetMsg0EStrings(char* szString1, char* szString2);
//D2MCPClient.0x6F9F1BC0 (#10039)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetMsg0EStrings(BOOL bReceived, const char* szString1, const char* szString2);
// Position in the game creation queue, from MCP_CREATEQUEUE
//D2MCPClient.0x6F9F1CD0 (#10050)
D2MCPCLIENT_DLL_DECL uint32_t __cdecl D2MCPClientGetCreateQueuePosition();
//D2MCPClient.0x6F9F1CE0 (#10051)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetCreateQueuePosition(uint32_t nPosition);

// "Response received" flags, set to TRUE when the server answers the matching request.
// Only D2MCPClientCharCreate resets its flag, the game is expected to reset the others before sending the request.
//D2MCPClient.0x6F9F1AC0 (#10029)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientGetCharCreateReceived();
//D2MCPClient.0x6F9F1AD0 (#10028)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetCharCreateReceived(BOOL bReceived);
//D2MCPClient.0x6F9F1AE0 (#10031)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientGetCharLogonReceived();
//D2MCPClient.0x6F9F1AF0 (#10030)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetCharLogonReceived(BOOL bReceived);
//D2MCPClient.0x6F9F1B00 (#10033)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientGetCharDeleteReceived();
//D2MCPClient.0x6F9F1B10 (#10032)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetCharDeleteReceived(BOOL bReceived);
//D2MCPClient.0x6F9F1B50 (#10035)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientGetMsg0BReceived();
//D2MCPClient.0x6F9F1B40 (#10034)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetMsg0BReceived(BOOL bReceived);
//D2MCPClient.0x6F9F1B60 (#10037)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientGetMsg0CReceived();
//D2MCPClient.0x6F9F1B70 (#10036)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetMsg0CReceived(BOOL bReceived);
//D2MCPClient.0x6F9F1C30 (#10040)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientGetMsg0DReceived();
//D2MCPClient.0x6F9F1C40 (#10041)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetMsg0DReceived(BOOL bReceived);
//D2MCPClient.0x6F9F1C50 (#10042)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientGetMsg0FReceived();
//D2MCPClient.0x6F9F1C60 (#10043)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetMsg0FReceived(BOOL bReceived);
//D2MCPClient.0x6F9F1C70 (#10044)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientGetMsg10Received();
//D2MCPClient.0x6F9F1C80 (#10045)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetMsg10Received(BOOL bReceived);
//D2MCPClient.0x6F9F1CF0 (#10052)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientGetCreateQueueReceived();
//D2MCPClient.0x6F9F1D00 (#10053)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetCreateQueueReceived(BOOL bReceived);
//D2MCPClient.0x6F9F1B20 (#10061)
D2MCPCLIENT_DLL_DECL BOOL __cdecl D2MCPClientGetCharUpgradeReceived();
//D2MCPClient.0x6F9F1B30 (#10060)
D2MCPCLIENT_DLL_DECL void __stdcall D2MCPClientSetCharUpgradeReceived(BOOL bReceived);
