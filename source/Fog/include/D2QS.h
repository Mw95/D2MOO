#pragma once

#include <Safesock.h>
#include <D2BasicTypes.h>
#include <Fog.h>

// Client socket receiving messages in a thread, the messages are given to a dispatcher or queued.
// A message starts with a header of nHeaderSize bytes, containing its total size (16 bits) at nSizeOffset.

#define D2QS_MAX_BUFFER_SIZE 0x2000

// Returns TRUE if the message was handled, otherwise it is queued
typedef BOOL(__fastcall* D2QSDispatcher)(const uint8_t* pData, uint16_t nSize, void* pParam);

#pragma pack(push, 1)

struct D2QSQueueMessageStrc					// sizeof 0x08 + data
{
	uint16_t nSize;							// 0x00
	uint16_t unk0x02;						// 0x02
	D2QSQueueMessageStrc* pNext;			// 0x04
	// Data follows
};

struct D2QSQueueStrc						// sizeof 0x24
{
	BOOL bOverflow;							// 0x00 Set when a message was dropped because the buffer was too small
	CRITICAL_SECTION tLock;					// 0x04
	D2QSQueueMessageStrc* pHead;			// 0x1C
	D2QSQueueMessageStrc* pTail;			// 0x20
};

struct D2QSSocketStrc						// sizeof 0x194
{
	HANDLE hConnectThread;					// 0x000
	DWORD dwConnectThreadId;				// 0x004
	char szHostAddress[MAX_PATH];			// 0x008
	int32_t nPort;							// 0x10C
	FSafeSock* pSafeSock;					// 0x110
	HANDLE hMessageEvent;					// 0x114
	int32_t nHeaderSize;					// 0x118
	int32_t nSizeOffset;					// 0x11C
	int32_t nMessageType;					// 0x120 First byte of the 4 bytes header
	BOOL bStop;								// 0x124
	char szName[64];						// 0x128
	D2QSDispatcher pfDispatcher;			// 0x168
	void* pDispatcherParam;					// 0x16C
	D2QSQueueStrc tQueue;					// 0x170
};

#pragma pack(pop)

// Internal

// 1.10f: 0x6FF51030
void __fastcall D2QS_QueueInitialize(D2QSQueueStrc* pQueue);
// 1.10f: 0x6FF51050
void __fastcall D2QS_QueueDestroy(D2QSQueueStrc* pQueue);
// 1.10f: 0x6FF510B0
void __fastcall D2QS_QueuePush(D2QSQueueStrc* pQueue, const uint8_t* pData, uint16_t nSize);
// 1.10f: 0x6FF51160
// Returns the size of the message, or 0 if the queue is empty or the message did not fit in the buffer
uint16_t __fastcall D2QS_QueuePop(D2QSQueueStrc* pQueue, uint8_t* pBuffer, uint16_t nBufferSize);

// Exported

// 1.10f: 0x6FF51920 (#10068)
FOG_DLL_DECL D2QSSocketStrc* __stdcall FOG_D2QSSocketCreate(const char* szHostAddress, int nPort, const char* szName);
// 1.10f: 0x6FF51A10 (#10069)
FOG_DLL_DECL void __stdcall FOG_D2QSSocketDestroy(D2QSSocketStrc* pSocket);
// 1.10f: 0x6FF51210 (#10070)
// Sends a message with its header
FOG_DLL_DECL BOOL __stdcall FOG_D2QSSocketSend(D2QSSocketStrc* pSocket, const uint8_t* pData, uint16_t nSize);
// 1.10f: 0x6FF51390 (#10071)
// Sends raw data
FOG_DLL_DECL BOOL __stdcall FOG_D2QSSocketSendRaw(D2QSSocketStrc* pSocket, const uint8_t* pData, uint16_t nSize);
// 1.10f: 0x6FF51400 (#10072)
// Pops a received message, returns its size
FOG_DLL_DECL int __stdcall FOG_D2QSSocketReceive(D2QSSocketStrc* pSocket, uint8_t* pBuffer, uint16_t nBufferSize);
// 1.10f: 0x6FF517F0 (#10073)
// Connects and waits for the connection to be established
FOG_DLL_DECL void __stdcall FOG_D2QSSocketConnect(D2QSSocketStrc* pSocket);
// 1.10f: 0x6FF51860 (#10074)
FOG_DLL_DECL HANDLE __stdcall FOG_D2QSSocketConnectAsync(D2QSSocketStrc* pSocket);
// 1.10f: 0x6FF518C0 (#10075)
FOG_DLL_DECL void __stdcall FOG_D2QSSocketDisconnect(D2QSSocketStrc* pSocket);
// 1.10f: 0x6FF51AB0 (#10076)
FOG_DLL_DECL DWORD __stdcall FOG_D2QSSocketWaitForMessage(D2QSSocketStrc* pSocket, DWORD dwMilliseconds);
// 1.10f: 0x6FF511F0 (#10077)
FOG_DLL_DECL void __stdcall FOG_D2QSSocketSetDispatcher(D2QSSocketStrc* pSocket, D2QSDispatcher pfDispatcher, void* pParam);
// 1.10f: 0x6FF515B0 (#10078)
FOG_DLL_DECL void __stdcall FOG_D2QSSocketSetHeaderFormat(D2QSSocketStrc* pSocket, int nHeaderSize, int nSizeOffset, int nMessageType);
// 1.10f: 0x6FF51AD0 (#10079)
FOG_DLL_DECL FSafeSock* __stdcall FOG_D2QSSocketGetSafeSock(D2QSSocketStrc* pSocket);
// 1.10f: 0x6FF51AF0 (#10080)
FOG_DLL_DECL void __stdcall FOG_D2QSSocketSignal(D2QSSocketStrc* pSocket);
