#pragma once


#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <deque>
#include <filesystem>
#include <stdexcept>
#include <vector>

#include <Windows.h>

#include <InlineHook.h>
#include <NoOpFixture.h>
#include <Fog.h>
#include <Safesock.h>

#include <D2MCPClient.h>
#include <McpConnect.h>


// Every D2MCPClient function tested, with its address in the original 1.10f D2MCPClient.dll
#define D2MCPCLIENT_TESTED_FUNCTIONS(X)							\
	X(D2MCPClientConnect,					0x6F9F17D0)		\
	X(D2MCPClientCloseMCP,					0x6F9F1980)		\
	X(D2MCPClientIsConnected,				0x6F9F19E0)		\
	X(D2MCPClientProcessMessages,			0x6F9F1A20)		\
	X(D2MCPClientGetConnectionThread,		0x6F9F17C0)		\
	X(D2MCPClientCharCreate,				0x6F9F1CA0)		\
	X(D2MCPClientCharLogon,					0x6F9F1CC0)		\
	X(D2MCPClientCreateGame,				0x6F9F2180)		\
	X(D2MCPClientJoinGame,					0x6F9F2300)		\
	X(D2MCPClientRequestGameList,			0x6F9F2400)		\
	X(D2MCPClientRequestGameInfo,			0x6F9F2490)		\
	X(D2MCPClientSendMsg08,					0x6F9F2520)		\
	X(D2MCPClientSendMsg09,					0x6F9F25D0)		\
	X(D2MCPClientCharDelete,				0x6F9F2680)		\
	X(D2MCPClientSendMsg0B,					0x6F9F2730)		\
	X(D2MCPClientSendMsg0C,					0x6F9F2820)		\
	X(D2MCPClientSendMsg0D,					0x6F9F28C0)		\
	X(D2MCPClientSendMsg0F,					0x6F9F28F0)		\
	X(D2MCPClientSendMsg10,					0x6F9F2920)		\
	X(D2MCPClientRequestLadderData,			0x6F9F2950)		\
	X(D2MCPClientRequestMotd,				0x6F9F2990)		\
	X(D2MCPClientCancelGameCreate,			0x6F9F29C0)		\
	X(D2MCPClientRequestCharList,			0x6F9F29F0)		\
	X(D2MCPClientCharRank,					0x6F9F2A20)		\
	X(D2MCPClientCharUpgrade,				0x6F9F26E0)		\
	X(D2MCPClientSetMsg08Callback,			0x6F9F1780)		\
	X(D2MCPClientSetMsg09Callback,			0x6F9F1790)		\
	X(D2MCPClientSetLadderDataCallbacks,	0x6F9F17A0)		\
	X(D2MCPClientSetMotdCallback,			0x6F9F17B0)		\
	X(D2MCPClientGetLastError,				0x6F9F1AB0)		\
	X(D2MCPClientSetLastError,				0x6F9F1AA0)		\
	X(D2MCPClientGetGameServerIp,			0x6F9F1A70)		\
	X(D2MCPClientGetGameRequestId,			0x6F9F1A80)		\
	X(D2MCPClientGetGameToken,				0x6F9F1A90)		\
	X(D2MCPClientGetGameHash,				0x6F9F1C90)		\
	X(D2MCPClientGetGameInfo,				0x6F9F1C00)		\
	X(D2MCPClientClearGameInfo,				0x6F9F1C10)		\
	X(D2MCPClientGetCharacterList,			0x6F9F1D10)		\
	X(D2MCPClientSetCharacterList,			0x6F9F1D20)		\
	X(D2MCPClientGetMsg0EStrings,			0x6F9F1B80)		\
	X(D2MCPClientSetMsg0EStrings,			0x6F9F1BC0)		\
	X(D2MCPClientGetCreateQueuePosition,	0x6F9F1CD0)		\
	X(D2MCPClientSetCreateQueuePosition,	0x6F9F1CE0)		\
	X(D2MCPClientGetCharCreateReceived,		0x6F9F1AC0)		\
	X(D2MCPClientSetCharCreateReceived,		0x6F9F1AD0)		\
	X(D2MCPClientGetCharLogonReceived,		0x6F9F1AE0)		\
	X(D2MCPClientSetCharLogonReceived,		0x6F9F1AF0)		\
	X(D2MCPClientGetCharDeleteReceived,		0x6F9F1B00)		\
	X(D2MCPClientSetCharDeleteReceived,		0x6F9F1B10)		\
	X(D2MCPClientGetMsg0BReceived,			0x6F9F1B50)		\
	X(D2MCPClientSetMsg0BReceived,			0x6F9F1B40)		\
	X(D2MCPClientGetMsg0CReceived,			0x6F9F1B60)		\
	X(D2MCPClientSetMsg0CReceived,			0x6F9F1B70)		\
	X(D2MCPClientGetMsg0DReceived,			0x6F9F1C30)		\
	X(D2MCPClientSetMsg0DReceived,			0x6F9F1C40)		\
	X(D2MCPClientGetMsg0FReceived,			0x6F9F1C50)		\
	X(D2MCPClientSetMsg0FReceived,			0x6F9F1C60)		\
	X(D2MCPClientGetMsg10Received,			0x6F9F1C70)		\
	X(D2MCPClientSetMsg10Received,			0x6F9F1C80)		\
	X(D2MCPClientGetCreateQueueReceived,	0x6F9F1CF0)		\
	X(D2MCPClientSetCreateQueueReceived,	0x6F9F1D00)		\
	X(D2MCPClientGetCharUpgradeReceived,	0x6F9F1B20)		\
	X(D2MCPClientSetCharUpgradeReceived,	0x6F9F1B30)		\
	X(MCP_DispatchMessage,					0x6F9F16F0)		\
	X(MCP_DispatchConnectionMessage,		0x6F9F1730)


// The functions and globals of one implementation (D2MOO or the original dll), so that tests can run the same scenario on both
struct McpClientApi
{
	const char* szName;

#define D2MCPCLIENT_API_MEMBER(NAME, ADDRESS) decltype(&NAME) NAME;
	D2MCPCLIENT_TESTED_FUNCTIONS(D2MCPCLIENT_API_MEMBER)
#undef D2MCPCLIENT_API_MEMBER

	FClientConnection** ppConnection;
	uint16_t* pPendingRequestId;
	uint32_t* pGameToken;
};

inline HMODULE get_original_d2mcpclient()
{
	static const HMODULE module = []()
	{
		const auto module = LoadLibraryA((std::filesystem::current_path() / "D2MCPClient.dll").string().c_str());
		if (module == nullptr)
		{
			throw std::runtime_error("Cannot load the original D2MCPClient.dll");
		}
		return module;
	}();
	return module;
}

inline uintptr_t original_d2mcpclient_address(uintptr_t nAddress)
{
	return reinterpret_cast<uintptr_t>(get_original_d2mcpclient()) + nAddress - D2MCPClientImageBase;
}

inline const McpClientApi& moo_api()
{
	static const McpClientApi api = {
		"MOO",
#define D2MCPCLIENT_API_MOO(NAME, ADDRESS) &NAME,
		D2MCPCLIENT_TESTED_FUNCTIONS(D2MCPCLIENT_API_MOO)
#undef D2MCPCLIENT_API_MOO
		&gpMCPConnection,
		&gnMCPPendingRequestId,
		&gdwMCPGameToken,
	};
	return api;
}

inline const McpClientApi& original_api()
{
	static const McpClientApi api = {
		"Original",
#define D2MCPCLIENT_API_ORIGINAL(NAME, ADDRESS) reinterpret_cast<decltype(&NAME)>(original_d2mcpclient_address(ADDRESS)),
		D2MCPCLIENT_TESTED_FUNCTIONS(D2MCPCLIENT_API_ORIGINAL)
#undef D2MCPCLIENT_API_ORIGINAL
		reinterpret_cast<FClientConnection**>(original_d2mcpclient_address(0x6FA02E58)),
		reinterpret_cast<uint16_t*>(original_d2mcpclient_address(0x6FA02CD0)),
		reinterpret_cast<uint32_t*>(original_d2mcpclient_address(0x6FA02CCC)),
	};
	return api;
}

// Runs `test` with the D2MOO implementation, then with the original one
template<typename Test>
void for_each_api(Test&& test)
{
	test(moo_api());
	test(original_api());
}


// Replaces the Fog.dll functions used by D2MCPClient (client connection, inet_ntoa and memory), for both the D2MOO implementation and the original D2MCPClient.dll.
// Sent messages are recorded, received messages are taken from `receive_queue`.
struct McpFogMock
{
	struct SentMessage
	{
		FClientConnection* pConnection;
		std::vector<uint8_t> data;
	};

	static inline std::vector<SentMessage> sent;
	static inline BOOL send_result = TRUE;
	static inline std::deque<std::vector<uint8_t>> receive_queue;
	static inline std::vector<FClientConnection*> receive_connections;
	static inline std::vector<ULONG> inet_ntoa_calls;

	static BOOL __stdcall ClientSendMessage(FClientConnection* pConnection, const void* pMessage, uint32_t nMessageSize)
	{
		const auto pBytes = static_cast<const uint8_t*>(pMessage);
		sent.push_back({ pConnection, std::vector<uint8_t>(pBytes, pBytes + nMessageSize) });
		return send_result;
	}

	static uint16_t __stdcall ClientReceive(FClientConnection* pConnection, uint8_t* pBuffer, uint32_t nBufferSize)
	{
		receive_connections.push_back(pConnection);
		if (receive_queue.empty())
		{
			return 0;
		}

		const auto message = receive_queue.front();
		receive_queue.pop_front();
		if (message.size() > nBufferSize)
		{
			throw std::runtime_error("McpFogMock: received message does not fit the buffer");
		}
		std::memcpy(pBuffer, message.data(), message.size());
		return static_cast<uint16_t>(message.size());
	}

	static const char* __fastcall inet_ntoa(ULONG nAddress)
	{
		inet_ntoa_calls.push_back(nAddress);
		static char szAddress[16];
		std::snprintf(szAddress, sizeof(szAddress), "%u.%u.%u.%u", nAddress & 0xFF, (nAddress >> 8) & 0xFF, (nAddress >> 16) & 0xFF, (nAddress >> 24) & 0xFF);
		return szAddress;
	}

	static void* __fastcall Alloc(int nSize, const char* szFile, int nLine, int n0)
	{
		return std::malloc(nSize);
	}

	static void __fastcall Free(void* pMemory, const char* szFile, int nLine, int n0)
	{
		std::free(pMemory);
	}

	static void reset()
	{
		sent.clear();
		send_result = TRUE;
		receive_queue.clear();
		receive_connections.clear();
		inet_ntoa_calls.clear();
	}
};

template<class Fixture>
struct McpFogFixture : Fixture
{
	std::vector<InlineHook> fog_hooks;
	std::vector<void*> hooked_targets;

	McpFogFixture()
	{
		fog_hooks.reserve(8);
		hook(10070, reinterpret_cast<void*>(&FOG_10070_ClientSendMessage), reinterpret_cast<const void*>(&McpFogMock::ClientSendMessage));
		hook(10072, reinterpret_cast<void*>(&FOG_10072_ClientReceive), reinterpret_cast<const void*>(&McpFogMock::ClientReceive));
		hook(10014, reinterpret_cast<void*>(&FOG_inet_ntoa), reinterpret_cast<const void*>(&McpFogMock::inet_ntoa));
		// Memory is allocated by one implementation and may be freed by the other one
		hook(10042, reinterpret_cast<void*>(&FOG_Alloc), reinterpret_cast<const void*>(&McpFogMock::Alloc));
		hook(10043, reinterpret_cast<void*>(&FOG_Free), reinterpret_cast<const void*>(&McpFogMock::Free));
		McpFogMock::reset();
	}

	~McpFogFixture()
	{
		McpFogMock::reset();
	}

private:
	// Hooks the function called by the D2MOO implementation, and the one the original dll imports if it is a different one
	// (it is the same when D2MOO's Fog.dll was loaded first)
	void hook(WORD nOrdinal, void* pMooTarget, const void* pReplacement)
	{
		void* pOriginalTarget = find_imported_function_by_ordinal(get_original_d2mcpclient(), "Fog.dll", nOrdinal);
		if (pOriginalTarget == nullptr)
		{
			throw std::runtime_error("McpFogFixture: the original D2MCPClient.dll does not import this Fog ordinal");
		}

		for (void* pTarget : { pMooTarget, pOriginalTarget })
		{
			if (std::find(hooked_targets.begin(), hooked_targets.end(), pTarget) == hooked_targets.end())
			{
				fog_hooks.emplace_back(pTarget, pReplacement);
				hooked_targets.push_back(pTarget);
			}
		}
	}
};
