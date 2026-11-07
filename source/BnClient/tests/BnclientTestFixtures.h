#pragma once


#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <vector>

#include <Windows.h>

#include <FogMemoryMocks.h>
#include <FunctionPair.h>
#include <ImportHooks.h>
#include <NoOpFixture.h>
#include <StormMocks.h>

#include <Fog.h>

#include <BnConnect.h>
#include <BnMessQueue.h>
#include <BnRecv.h>
#include <BnSend.h>


//1.10f Image base: 0x6FF00000
constexpr uintptr_t BnclientImageBase = 0x6FF00000;

inline HMODULE get_original_bnclient()
{
	static const HMODULE module = []()
	{
		const auto module = LoadLibraryA((std::filesystem::current_path() / "Bnclient.dll").string().c_str());
		if (module == nullptr)
		{
			throw std::runtime_error("Cannot load the original Bnclient.dll");
		}
		return module;
	}();
	return module;
}

// Address in the loaded original Bnclient.dll of an address given for the 1.10f image base
inline uintptr_t original_bnclient_address(uintptr_t nAddress)
{
	return reinterpret_cast<uintptr_t>(get_original_bnclient()) + nAddress - BnclientImageBase;
}

template<typename T>
T* original_bnclient_global(uintptr_t nAddress)
{
	return reinterpret_cast<T*>(original_bnclient_address(nAddress));
}

// Pair of the D2MOO function and the same function in the original Bnclient.dll
template<typename Function>
auto make_bnclient_pair(Function& function, uintptr_t nAddress)
{
	return make_function_pair(function, original_bnclient_address(nAddress));
}

// Stateful functions tested through sequences of calls, with their address in the original 1.10f Bnclient.dll
#define BNCLIENT_TESTED_FUNCTIONS(X)						\
	X(BNMESSQUEUE_PushData,				0x6FF06320)		\
	X(BNMESSQUEUE_PushString,			0x6FF063F0)		\
	X(BNMESSQUEUE_Read,					0x6FF064A0)		\
	X(BNMESSQUEUE_Clear,				0x6FF06530)		\
	X(BNMESSQUEUE_SetErrorIfNone,		0x6FF06580)		\
	X(BNMESSQUEUE_SetError,				0x6FF065B0)		\
	X(BNMESSQUEUE_SetErrorText,			0x6FF065E0)		\
	X(BNMESSQUEUE_GetLastError,			0x6FF06610)		\
	X(BNMESSQUEUE_PeekLastError,		0x6FF06670)		\
	X(BNRECV_DispatchMessage,			0x6FF032A0)		\
	X(BNRECV_SetDisconnected,			0x6FF022D0)		\
	X(BNRECV_IsDisconnected,			0x6FF022E0)		\
	X(BNRECV_GetCreateAccountResult,	0x6FF022F0)		\
	X(BNRECV_GetChangePasswordResult,	0x6FF02300)		\
	X(BNRECV_ResetAllMessages,			0x6FF02310)		\
	X(BNRECV_WasMessageReceived,		0x6FF023D0)		\
	X(BNRECV_ResetMessage,				0x6FF023E0)		\
	X(BNRECV_GetMessageResult,			0x6FF02400)		\
	X(BNSEND_SetServerToken,			0x6FF07180)		\
	X(BNSEND_GetServerToken,			0x6FF07190)		\
	X(BNSEND_SetLogonType,				0x6FF071A0)		\
	X(BNSEND_GetLogonType,				0x6FF071B0)		\
	X(BNSEND_LogonResponse2,			0x6FF071C0)		\
	X(BNSEND_CreateAccount2,			0x6FF07280)		\
	X(BNSEND_ChangePassword,			0x6FF07300)		\
	X(BNSEND_StoreRealmList,			0x6FF073F0)		\
	X(BNSEND_StoreAdUrl,				0x6FF07470)		\
	X(BNSEND_QueryAdUrl,				0x6FF074C0)		\
	X(BNSEND_QueryRealms,				0x6FF07510)		\
	X(BNSEND_StoreChannelList,			0x6FF07550)		\
	X(BNSEND_FreeChannelList,			0x6FF075B0)		\
	X(BNSEND_GetChannelList,			0x6FF075E0)		\
	X(BNSEND_JoinChannel,				0x6FF07630)		\
	X(BNSEND_EnterChat,					0x6FF076D0)		\
	X(BNSEND_LeaveChat,					0x6FF077A0)		\
	X(BNSEND_CheckAd,					0x6FF07860)		\
	X(BNSEND_DisplayAd,					0x6FF078B0)		\
	X(BNSEND_StartAdvEx3,				0x6FF07910)		\
	X(BNSEND_StopAdv,					0x6FF079C0)		\
	X(BNSEND_LeaveGame,					0x6FF079E0)		\
	X(BNSEND_GetCreateGameResult,		0x6FF07A00)		\
	X(BNSEND_StoreGameList,				0x6FF07A20)		\
	X(BNSEND_FreeGameList,				0x6FF07A80)		\
	X(BNSEND_GetGameList,				0x6FF07AB0)		\
	X(BNSEND_NotifyJoin,				0x6FF07B60)		\
	X(BNSEND_StoreRealmLogonInformation, 0x6FF07BD0)	\
	X(BNSEND_LogonRealm,				0x6FF07C60)		\
	X(BNSEND_ClickAd,					0x6FF07D10)		\
	X(BNSEND_WriteUserData,				0x6FF07D40)		\
	X(BNSEND_StoreUserData,				0x6FF07E40)		\
	X(BNSEND_RequestUserData,			0x6FF07E90)		\
	X(BNSEND_GetUserData,				0x6FF07F50)		\
	X(BNSEND_SetEmail,					0x6FF07FF0)		\
	X(BNSEND_ResetPassword,				0x6FF08060)		\
	X(BNSEND_ChangeEmail,				0x6FF08180)		\
	X(BNET_SendPacket,					0x6FF01F70)		\
	X(BNET_SetUniqueName,				0x6FF01000)		\
	X(BNET_GetUniqueName,				0x6FF01020)		\
	X(BNET_IsEmailRequested,			0x6FF022A0)		\
	X(BNET_SetEmailRequested,			0x6FF022B0)

// The functions of one implementation (D2MOO or the original dll), so that tests can run the same scenario on both
struct BnclientApi
{
	const char* szName;

#define BNCLIENT_API_MEMBER(NAME, ADDRESS) decltype(&NAME) NAME;
	BNCLIENT_TESTED_FUNCTIONS(BNCLIENT_API_MEMBER)
#undef BNCLIENT_API_MEMBER
};

inline const BnclientApi& moo_api()
{
	static const BnclientApi api = {
		"MOO",
#define BNCLIENT_API_MOO(NAME, ADDRESS) &NAME,
		BNCLIENT_TESTED_FUNCTIONS(BNCLIENT_API_MOO)
#undef BNCLIENT_API_MOO
	};
	return api;
}

inline const BnclientApi& original_api()
{
	static const BnclientApi api = {
		"Original",
#define BNCLIENT_API_ORIGINAL(NAME, ADDRESS) reinterpret_cast<decltype(&NAME)>(original_bnclient_address(ADDRESS)),
		BNCLIENT_TESTED_FUNCTIONS(BNCLIENT_API_ORIGINAL)
#undef BNCLIENT_API_ORIGINAL
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

// The D2MOO implementation is linked into the test executable, so its DllMain is not called
inline void initialize_moo_bnclient()
{
	static const bool bInitialized = []()
	{
		BNMESSQUEUE_Initialize();
		return true;
	}();
	(void)bInitialized;
}

// Replaces the Storm and Fog memory functions, which are only stubs in D2MOO
template<class Fixture>
struct BnclientStormFixture : Fixture
{
	ImportHooks hooks{ get_original_bnclient() };

	BnclientStormFixture()
	{
		initialize_moo_bnclient();
		hook_storm_mocks(hooks);
		hook_fog_memory_mocks(hooks);
	}
};


// Records the packets sent with BNET_SendPacket instead of sending them, and controls FOG_IsExpansion
struct BnSendMock
{
	struct Packet
	{
		uint8_t nMessageId;
		std::vector<uint8_t> data;

		bool operator==(const Packet& other) const { return nMessageId == other.nMessageId && data == other.data; }
	};

	static inline std::vector<Packet> sent;
	static inline int nSendResult = 1;
	static inline int bExpansion = TRUE;

	static int __fastcall SendPacket(uint8_t nMessageId, const void* pData, uint32_t nSize)
	{
		const auto pBytes = static_cast<const uint8_t*>(pData);
		sent.push_back({ nMessageId, pBytes ? std::vector<uint8_t>(pBytes, pBytes + nSize) : std::vector<uint8_t>(nSize) });
		return nSendResult;
	}

	static int __fastcall IsExpansion()
	{
		return bExpansion;
	}

	static void reset()
	{
		sent.clear();
		nSendResult = 1;
		bExpansion = TRUE;
	}
};

template<class Fixture>
struct BnclientSendFixture : BnclientStormFixture<Fixture>
{
	BnclientSendFixture()
	{
		this->hooks.hook_target(reinterpret_cast<void*>(&BNET_SendPacket), reinterpret_cast<const void*>(&BnSendMock::SendPacket));
		this->hooks.hook_target(reinterpret_cast<void*>(original_bnclient_address(0x6FF01F70)), reinterpret_cast<const void*>(&BnSendMock::SendPacket));
		this->hooks.hook("Fog.dll", 10227, reinterpret_cast<void*>(&FOG_IsExpansion), reinterpret_cast<const void*>(&BnSendMock::IsExpansion));
		BnSendMock::reset();
	}

	~BnclientSendFixture()
	{
		BnSendMock::reset();
	}
};
