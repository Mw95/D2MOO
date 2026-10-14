#pragma once

#include <D2BasicTypes.h>
#include <Fog.h>

// Network server used by the game server (D2Net).
// Clients are identified by an id, and their messages are sorted in queues according to the type given by the validation callback.
// On Windows NT, sockets are read with I/O completion ports (QServerNT.cpp), otherwise with select (QServer98.cpp).

#define QSERVER_MAX_PORTS 4
#define QSERVER_READ_BUFFER_SIZE 0x5B4
#define QSERVER_MAX_WHITELIST 256
#define QSERVER_HACKLIST_TIME 120				// In seconds
#define QSERVER_RECONNECT_DELAY 15000			// In milliseconds
#define QSERVER_FLOOD_MAX_COST 1000

// Values returned by the validation callback
enum D2QServerPacketStatus
{
	QSPACKET_QUEUE = 1,				// Queue the message
	QSPACKET_QUEUE_LIMITED = 2,		// Queue the message, its cost counts toward the flood limit
	QSPACKET_INCOMPLETE = 3,		// Wait for more data
	QSPACKET_INVALID = 4,			// Disconnect and ban the client
	QSPACKET_SKIP = 5,				// Drop the message
};

enum D2QServerMode
{
	QSMODE_NETWORK = 0,
	QSMODE_LOCAL = 1,				// No network, messages are sent through the local send callback
	QSMODE_LOCAL2 = 2,
};

// int __fastcall(uint8_t* pBuffer, int nBufferSize, int* pPacketSize, int* pHeaderSize, int* pMessageType, int* pCost, int nClientId, int nUserData)
typedef int(__fastcall* QServerValidatePacketCallback)(uint8_t*, int, int*, int*, int*, int*, int, int);
// int __fastcall(QServer* pServer, int nClientId, const char* szFile, int nLine)
typedef int(__fastcall* QServerClientCallback)(QServer*, int, const char*, int);
// int __fastcall(QServer* pServer, const uint8_t* pData, int nSize)
typedef int(__fastcall* QServerLocalSendCallback)(QServer*, const uint8_t*, int);
// void __fastcall(uint32_t nIP, const char* szFile, int nLine)
typedef void(__fastcall* QServerHackListCallback)(uint32_t, const char*, int);

#pragma pack(push, 1)

struct D2QSConfigStrc							// sizeof 0x10
{
	int32_t nClientHashSize;					// 0x00 Must be a power of 2
	int32_t nIPCountHashSize;					// 0x04
	int32_t nHackListHashSize;					// 0x08
	BOOL bUseReadThreads;						// 0x0C
};

struct D2QSWriteBufferStrc						// sizeof 0x08 + data
{
	int32_t nSize;								// 0x00
	D2QSWriteBufferStrc* pNext;					// 0x04
	// Data follows
};

struct D2QSOverlappedStrc						// sizeof 0x18
{
	OVERLAPPED tOverlapped;						// 0x00
	int32_t nTag;								// 0x14 QSOVERLAPPED_*
};

enum D2QSOverlappedTag
{
	QSOVERLAPPED_READ = 1,
	QSOVERLAPPED_WRITE = 2,
	QSOVERLAPPED_PENDING = 4,
};

struct D2QSClientStrc							// sizeof 0x664
{
	int32_t nClientId;							// 0x000
	D2QSClientStrc* pNext;						// 0x004 In the client hash table
	LONG nRefCount;								// 0x008
	BOOL bClosing;								// 0x00C
	SOCKET hSocket;								// 0x010
	int32_t nPortIndex;							// 0x014
	uint32_t nIP;								// 0x018
	D2QSClientStrc* pNextInIPHash;				// 0x01C
	int32_t nUserData;							// 0x020
	DWORD dwLastFloodUpdate;					// 0x024
	uint32_t nFloodCost;						// 0x028
	CRITICAL_SECTION tLock;						// 0x02C
	D2QSOverlappedStrc tRead;					// 0x044
	D2QSOverlappedStrc tWrite;					// 0x05C
	D2QSWriteBufferStrc* pWriteHead;			// 0x074
	sockaddr_in tLocalAddress;					// 0x078
	sockaddr_in tPeerAddress;					// 0x088
	int32_t nConnectTime;						// 0x098
	int32_t nLastReceiveTime;					// 0x09C
	int32_t nLastSendTime;						// 0x0A0
	int32_t nUnknownTime;						// 0x0A4
	int32_t nReadBufferSize;					// 0x0A8
	DWORD dwBytesRead;							// 0x0AC
	uint8_t pReadBuffer[QSERVER_READ_BUFFER_SIZE];	// 0x0B0
};

struct D2QSMessageStrc							// sizeof 0x5C0
{
	int32_t nClientId;							// 0x000
	uint8_t pData[0x5B0];						// 0x004
	int32_t nSize;								// 0x5B4
	DWORD dwTime;								// 0x5B8
	D2QSMessageStrc* pNext;						// 0x5BC
};

// Number of clients connected from an IP
struct D2QSIPCountStrc							// sizeof 0x0C
{
	uint32_t nIP;								// 0x00
	int32_t nCount;								// 0x04
	D2QSIPCountStrc* pNext;						// 0x08
};

struct D2QSHackListStrc							// sizeof 0x10
{
	uint32_t nIP;								// 0x00
	uint32_t nLifeTime;							// 0x04 Remaining time before the entry is removed, in seconds
	uint32_t nBanTime;							// 0x08 Remaining ban time in seconds, connecting again restarts it
	D2QSHackListStrc* pNext;					// 0x0C
};

struct D2QSReconnectStrc						// sizeof 0x10
{
	uint32_t nIP;								// 0x00
	DWORD dwTime;								// 0x04
	uint32_t nCount;							// 0x08
	D2QSReconnectStrc* pNext;					// 0x0C
};

struct D2QSWhitelistStrc						// sizeof 0x08
{
	uint32_t nAddress;							// 0x00
	int32_t nMaskBits;							// 0x04
};

#pragma pack(pop)

struct QServer									// sizeof 0xC4C
{
	BOOL bUseNT;								// 0x000
	int32_t nLastClientId;						// 0x004
	uint32_t nClientHashSize;					// 0x008
	uint32_t nClientHashMask;					// 0x00C
	uint32_t nIPCountHashSize;					// 0x010
	D2QSClientStrc** pClientHash;				// 0x014
	uint32_t nClientHashSize2;					// 0x018
	CRITICAL_SECTION* pClientHashLocks;			// 0x01C
	D2QSClientStrc** pIPHash;					// 0x020 Uses nClientHashMask
	uint32_t nClientHashLocks;					// 0x024
	CRITICAL_SECTION tIPHashLock;				// 0x028
	D2QSIPCountStrc** pIPCounts;				// 0x040
	uint32_t nIPCountHashSize2;					// 0x044
	D2QSWhitelistStrc tWhitelist[QSERVER_MAX_WHITELIST];	// 0x048
	int32_t nWhitelist;							// 0x848
	D2QSReconnectStrc* pReconnectsHead;			// 0x84C
	D2QSReconnectStrc* pReconnectsTail;			// 0x850
	CRITICAL_SECTION tLock;						// 0x854
	int32_t nMode;								// 0x86C D2QServerMode
	D2QSMessageStrc** pMessageQueuesHead;		// 0x870
	D2QSMessageStrc** pMessageQueuesTail;		// 0x874
	D2QSMessageStrc* pFreeMessages;				// 0x878
	int32_t nMessageQueues;						// 0x87C
	int32_t nClients;							// 0x880
	int32_t nMaxConnectionsPerIP;				// 0x884
	DWORD dwLastHackListUpdate;					// 0x888
	D2QSHackListStrc* pFreeHackListEntries;		// 0x88C
	int32_t nHackListEntries;					// 0x890
	CRITICAL_SECTION tHackListLock;				// 0x894
	D2QSHackListStrc** pHackList;				// 0x8AC
	uint32_t nHackListHashSize;					// 0x8B0
	CRITICAL_SECTION tStatsLock;				// 0x8B4
	uint8_t pAcceptStats[QSERVER_MAX_PORTS][0xB0];	// 0x8CC Profiling of the accept threads, not used
	int32_t nPorts;								// 0xB8C
	SOCKET hListenSockets[QSERVER_MAX_PORTS];	// 0xB90
	uint16_t nPortNumbers[QSERVER_MAX_PORTS];	// 0xBA0
	int32_t nPortFlags[QSERVER_MAX_PORTS];		// 0xBA8 See FOG_10186
	QServerHackListCallback pfHackList;			// 0xBB8
	void* pfUnknownCallback;					// 0xBBC
	QServerValidatePacketCallback pfValidatePacket;	// 0xBC0
	QServerClientCallback pfOnConnect;			// 0xBC4
	QServerClientCallback pfOnDisconnect;		// 0xBC8
	QServerLocalSendCallback pfLocalSend;		// 0xBCC
	BOOL bHackListEnabled;						// 0xBD0
	HANDLE hDataEvent;							// 0xBD4 Win98 only, set when messages were received
	HANDLE hAcceptThreads[QSERVER_MAX_PORTS];	// 0xBD8
	DWORD dwAcceptThreadIds[QSERVER_MAX_PORTS];	// 0xBE8
	BOOL bStopAcceptThreads[QSERVER_MAX_PORTS];	// 0xBF8
	HANDLE hCompletionPorts[QSERVER_MAX_PORTS];	// 0xC08
	BOOL bUseReadThreads;						// 0xC18
	HANDLE hReadThreads[QSERVER_MAX_PORTS];		// 0xC1C
	DWORD dwReadThreadIds[QSERVER_MAX_PORTS];	// 0xC2C
	BOOL bStopReadThreads[QSERVER_MAX_PORTS];	// 0xC3C
};

// Shared between QServer.cpp, QServer98.cpp and QServerNT.cpp

// 1.10f: 0x6FF54A80
D2QSClientStrc* __fastcall QSERVER_CreateClient(QServer* pServer, SOCKET hSocket, uint32_t nIP);
// 1.10f: 0x6FF54C20
// Closes the socket of the client, and releases the reference of the connection
void __fastcall QSERVER_CloseClient(QServer* pServer, int nClientId, const char* szFile, int nLine);
// 1.10f: 0x6FF54F30
D2QSClientStrc* __fastcall QSERVER_FindClient(QServer* pServer, int nClientId);
// 1.10f: 0x6FF54F90
D2QSClientStrc* __fastcall QSERVER_FindClientBySocket(QServer* pServer, SOCKET hSocket);
// 1.10f: 0x6FF55010
void __fastcall QSERVER_AddRef(QServer* pServer, D2QSClientStrc* pClient);
// 1.10f: 0x6FF55020
// Removes and frees the client when its last reference is released
void __fastcall QSERVER_Release(QServer* pServer, D2QSClientStrc* pClient);
// 1.10f: 0x6FF55290
void __fastcall QSERVER_UpdateHackList(QServer* pServer);
// 1.10f: 0x6FF55410
void __fastcall QSERVER_HackListAdd(QServer* pServer, const char* szFile, uint32_t nIP, int nLine);
// 1.10f: 0x6FF55630
BOOL __fastcall QSERVER_IsBanned(QServer* pServer, uint32_t nIP);
// 1.10f: 0x6FF556A0
BOOL __fastcall QSERVER_HasTooManyConnections(QServer* pServer, const uint32_t* pIP);
// 1.10f: 0x6FF55710
// Returns FALSE if the IP reconnected too many times recently
BOOL __fastcall QSERVER_CheckReconnections(QServer* pServer, const uint32_t* pIP);
// 1.10f: 0x6FF558C0
// Disconnects and bans the client already connected from this IP
BOOL __fastcall QSERVER_KickClientWithSameIP(QServer* pServer, const uint32_t* pIP, const char* szFile, int nLine);
// 1.10f: 0x6FF55AD0
// Queues the complete messages of the read buffer of the client
void __fastcall QSERVER_ProcessClientData(QServer* pServer, D2QSClientStrc* pClient);

// 1.10f: 0x6FF57750
BOOL __fastcall QSERVER98_Initialize(QServer* pServer, int nPort);
// 1.10f: 0x6FF578B0
void __fastcall QSERVER98_Shutdown(QServer* pServer);
// 1.10f: 0x6FF578F0
BOOL __fastcall QSERVER98_Send(QServer* pServer, D2QSClientStrc* pClient, const uint8_t* pData, int nSize);

// 1.10f: 0x6FF57E90
BOOL __fastcall QSERVERNT_Initialize(QServer* pServer, int nPort);
// 1.10f: 0x6FF57EE0
SOCKET __fastcall QSERVERNT_AddPort(QServer* pServer, int nPort);
// 1.10f: 0x6FF58130
void __fastcall QSERVERNT_Shutdown(QServer* pServer);
// 1.10f: 0x6FF58760
BOOL __fastcall QSERVERNT_Send(QServer* pServer, D2QSClientStrc* pClient, const uint8_t* pData, int nSize);
// 1.10f: 0x6FF589C0
BOOL __fastcall QSERVERNT_WaitForData(QServer* pServer, DWORD dwMilliseconds);

// Exported

// 1.10f: 0x6FF54120 (#10185)
FOG_DLL_DECL void __stdcall FOG_QServerSetConfig(const D2QSConfigStrc* pConfig);
// 1.10f: 0x6FF54480 (#10150)
FOG_DLL_DECL SOCKET __stdcall FOG_QServerAddPort(QServer* pServer, int nPort);
// 1.10f: 0x6FF549B0 (#10153)
FOG_DLL_DECL BOOL __stdcall FOG_QServerBroadcast(QServer* pServer, const uint8_t* pData, int nSize);
// 1.10f: 0x6FF54890 (#10155)
FOG_DLL_DECL BOOL __stdcall FOG_QServerClearMessages(QServer* pServer);
// 1.10f: 0x6FF56280 (#10160)
FOG_DLL_DECL uint32_t __stdcall FOG_QServerGetClientPeerIP(QServer* pServer, int nClientId);
// 1.10f: 0x6FF54940 (#10174)
FOG_DLL_DECL BOOL __stdcall FOG_QServerIsLocal(QServer* pServer);
// 1.10f: 0x6FF55970 (#10184)
FOG_DLL_DECL int __stdcall FOG_QServerGetMessageCount(QServer* pServer, int nMessageType);
// 1.10f: 0x6FF57680 (#10188)
FOG_DLL_DECL BOOL __fastcall FOG_QServerIsWhitelisted(QServer* pServer, uint32_t nIP);
