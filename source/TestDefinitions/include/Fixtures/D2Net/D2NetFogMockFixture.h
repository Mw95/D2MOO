#pragma once


#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <initializer_list>
#include <iomanip>
#include <iterator>
#include <mutex>
#include <ostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <WinSock2.h>
#include <Windows.h>

#include <Fog.h>
#include <Safesock.h>

#include <D2Net.h>
#include <FunctionPair.h>
#include <InlineHook.h>


// A call made by D2Net to one of the mocked Fog functions.
// Pointers that are owned by the caller (and thus differ between both implementations) are not recorded as is:
// the data they point to is recorded instead.
struct D2NetFogCall
{
	std::string function;
	std::vector<int32_t> arguments;
	std::vector<uint8_t> data;
	std::string text;

	bool operator==(const D2NetFogCall& other) const
	{
		return function == other.function && arguments == other.arguments && data == other.data && text == other.text;
	}

	bool operator!=(const D2NetFogCall& other) const
	{
		return !(*this == other);
	}
};

inline std::ostream& operator<<(std::ostream& stream, const D2NetFogCall& call)
{
	stream << call.function << '(';
	for (size_t i = 0; i < call.arguments.size(); ++i)
	{
		stream << (i ? ", " : "") << "0x" << std::hex << call.arguments[i] << std::dec;
	}
	stream << ')';

	if (!call.text.empty())
	{
		stream << " text=\"" << call.text << '"';
	}

	if (!call.data.empty())
	{
		stream << " data=[";
		for (size_t i = 0; i < call.data.size(); ++i)
		{
			stream << (i ? " " : "") << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(call.data[i]);
		}
		stream << std::dec << std::setfill(' ') << ']';
	}

	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const std::vector<D2NetFogCall>& calls)
{
	stream << '{';
	for (const auto& call : calls)
	{
		stream << "\n\t" << call;
	}
	return stream << (calls.empty() ? "}" : "\n}");
}


// Replaces the Fog functions used by D2Net, both for the D2MOO implementation and the original D2Net.dll:
// - Memory and critical section functions are replaced by working implementations that do not depend on Fog being initialized.
// - QServer, (de)compression and socket functions are replaced by fakes that record their arguments in `calls`.
//   Tests can then compare the calls made by both implementations.
// Mocks can be called from the client threads of D2Net, so their state is guarded by a mutex.
struct D2NetFogMock
{
	static inline std::mutex mutex;
	static inline std::vector<D2NetFogCall> calls;

	// Value returned by the mocked QServer functions
	static inline int32_t return_value = 0;
	// Number of bytes written by the mocked FOG_10223 (compression), a negative value writes as many bytes as the input
	static inline int32_t compressed_size = -1;

	// Returned by the mocked FOG_InitializeServer
	static inline uint8_t fake_server[64]{};
	// Callbacks given to the last FOG_InitializeServer call
	static inline void* server_callbacks[4]{};

	static inline std::unordered_map<void*, size_t> live_allocations;
	static inline std::vector<std::pair<void*, size_t>> allocation_history;

	static QServer* server()
	{
		return reinterpret_cast<QServer*>(fake_server);
	}

	static void reset()
	{
		std::lock_guard<std::mutex> lock(mutex);
		calls.clear();
		return_value = 0;
		compressed_size = -1;
		std::fill(std::begin(server_callbacks), std::end(server_callbacks), nullptr);
		allocation_history.clear();
	}

	static std::vector<D2NetFogCall> take_calls()
	{
		std::lock_guard<std::mutex> lock(mutex);
		return std::exchange(calls, {});
	}

	static size_t live_allocation_count()
	{
		std::lock_guard<std::mutex> lock(mutex);
		return live_allocations.size();
	}

	// Returns the most recent allocation of `size` bytes that is still alive, or nullptr
	static void* last_live_allocation_of_size(size_t size)
	{
		std::lock_guard<std::mutex> lock(mutex);
		for (auto it = allocation_history.rbegin(); it != allocation_history.rend(); ++it)
		{
			if (it->second == size && live_allocations.count(it->first))
			{
				return it->first;
			}
		}
		return nullptr;
	}

	static void free_live_allocations()
	{
		std::lock_guard<std::mutex> lock(mutex);
		for (const auto& [pMemory, nSize] : live_allocations)
		{
			std::free(pMemory);
		}
		live_allocations.clear();
		allocation_history.clear();
	}

	// Memory
	static void* __fastcall Alloc(int nSize, const char* szFile, int nLine, int n0)
	{
		const size_t nAllocationSize = nSize > 0 ? static_cast<size_t>(nSize) : 1;
		void* pMemory = std::malloc(nAllocationSize);
		if (pMemory)
		{
			// Same content for both implementations, in case uninitialized memory ends up being compared
			std::memset(pMemory, 0xCD, nAllocationSize);

			std::lock_guard<std::mutex> lock(mutex);
			live_allocations[pMemory] = static_cast<size_t>(nSize);
			allocation_history.emplace_back(pMemory, static_cast<size_t>(nSize));
		}
		return pMemory;
	}

	static void __fastcall Free(void* pFree, const char* szFile, int nLine, int n0)
	{
		std::lock_guard<std::mutex> lock(mutex);
		const auto it = live_allocations.find(pFree);
		if (it != live_allocations.end())
		{
			std::free(pFree);
			live_allocations.erase(it);
		}
	}

	static void __fastcall LockCriticalSection(CRITICAL_SECTION* pCriticalSection, int nLine)
	{
		EnterCriticalSection(pCriticalSection);
	}

	// Sockets
	static int __fastcall SOCKET_CloseSocket(SOCKET nSocket)
	{
		record("FOG_SOCKET_CloseSocket", { nSocket != 0 });
		if (nSocket != 0)
		{
			closesocket(nSocket);
		}
		return 0;
	}

	static const char* __fastcall ResolveHostIPAddress(const char* szHostName)
	{
		record("FOG_ResolveHostIPAddress", {}, nullptr, 0, szHostName);
		return szHostName;
	}

	// QServer
	static QServer* __stdcall InitializeServer(int a1, int a2, int a3, int a4, void* a5, void* a6, void* a7, void* a8)
	{
		record("FOG_InitializeServer", { a1, a2, a3, a4 });

		std::lock_guard<std::mutex> lock(mutex);
		server_callbacks[0] = a5;
		server_callbacks[1] = a6;
		server_callbacks[2] = a7;
		server_callbacks[3] = a8;
		return server();
	}

	static int __stdcall SetMaxClientsPerGame(QServer* pServer, int nMaxClients)
	{
		return record("FOG_SetMaxClientsPerGame", { pointer(pServer), nMaxClients });
	}

	static int __stdcall Fog10152(void* pServer, const uint8_t* pData, int nSize)
	{
		return record("FOG_10152", { pointer(pServer), nSize }, pData, nSize);
	}

	static int __stdcall WaitForSingleObject(void* pServer, int nMilliseconds)
	{
		return record("FOG_WaitForSingleObject", { pointer(pServer), nMilliseconds });
	}

	static int __stdcall Fog10156(void* pServer, int nQueue, uint8_t* pBuffer, int nBufferSize)
	{
		if (pBuffer)
		{
			for (int i = 0; i < nBufferSize; ++i)
			{
				pBuffer[i] = static_cast<uint8_t>(nQueue * 31 + i);
			}
		}
		return record("FOG_10156", { pointer(pServer), nQueue, nBufferSize });
	}

	static int __stdcall Fog10157(void* pServer, int nClientId, const uint8_t* pData, int nSize)
	{
		return record("FOG_10157", { pointer(pServer), nClientId, nSize }, pData, nSize);
	}

	static int __stdcall Fog10158(void* pServer, int nClientId)
	{
		return record("FOG_10158", { pointer(pServer), nClientId });
	}

	static int __stdcall Fog10159(void* pServer, int nClientId, char* szBuffer, int nBufferSize)
	{
		if (szBuffer && nBufferSize > 0)
		{
			std::snprintf(szBuffer, nBufferSize, "10.0.0.%d", nClientId & 0xFF);
		}
		return record("FOG_10159", { pointer(pServer), nClientId, nBufferSize });
	}

	static int __stdcall Fog10161(void* pServer, int nClientId)
	{
		return record("FOG_10161", { pointer(pServer), nClientId });
	}

	static int __stdcall Fog10162(void* pServer, int nClientId, const char* szFile, int nLine)
	{
		return record("FOG_10162", { pointer(pServer), nClientId, nLine }, nullptr, 0, szFile);
	}

	static int __stdcall Fog10163(void* pServer, int nClientId, const char* szFile, int nLine)
	{
		return record("FOG_10163", { pointer(pServer), nClientId, nLine }, nullptr, 0, szFile);
	}

	static int __stdcall Fog10164(void* pServer, int a2, int a3, int a4)
	{
		return record("FOG_10164", { pointer(pServer), a2, a3, a4 });
	}

	static int __stdcall Fog10165(void* pServer, int nClientId, const char* szFile, int nLine)
	{
		// szFile and nLine are the location of the call inside each implementation, so they can't be compared
		return record("FOG_10165", { pointer(pServer), nClientId });
	}

	static int __stdcall Fog10166(void* pServer, int a2, int a3, int a4)
	{
		return record("FOG_10166", { pointer(pServer), a2, a3, a4 });
	}

	static int __stdcall Fog10170(void* pServer, int a2)
	{
		return record("FOG_10170", { pointer(pServer), a2 });
	}

	static int __stdcall Fog10171(void* pServer, void* pCallback)
	{
		return record("FOG_10171", { pointer(pServer), pointer(pCallback) });
	}

	static int __stdcall Fog10172(void* pServer, int nClientId, int dwGameGuid)
	{
		return record("FOG_10172", { pointer(pServer), nClientId, dwGameGuid });
	}

	static int __stdcall Fog10173(void* pServer, int nClientId)
	{
		return record("FOG_10173", { pointer(pServer), nClientId });
	}

	static int __stdcall Fog10175(void* pServer, const uint8_t* pData, int nSize, int nClientId)
	{
		return record("FOG_10175", { pointer(pServer), nSize, nClientId }, pData, nSize);
	}

	static int __stdcall Fog10177(void* pServer, int nMilliseconds)
	{
		return record("FOG_10177", { pointer(pServer), nMilliseconds });
	}

	static int __stdcall SetHackListEnabled(QServer* pServer, BOOL bHacklistEnabled)
	{
		return record("FOG_SetHackListEnabled", { pointer(pServer), bHacklistEnabled });
	}

	static int __stdcall Fog10180(void* pServer)
	{
		return record("FOG_10180", { pointer(pServer) });
	}

	static int __stdcall Fog10182(void* pServer)
	{
		return record("FOG_10182_Return", { pointer(pServer) });
	}

	static int __stdcall Fog10183(void* pServer, int a2)
	{
		return record("FOG_10183_Return", { pointer(pServer), a2 });
	}

	static int __stdcall Fog10186(void* pServer, int nIndex, int nValue)
	{
		return record("FOG_10186", { pointer(pServer), nIndex, nValue });
	}

	static int __fastcall Fog10187(void* pServer, int a2, int a3)
	{
		return record("FOG_10187", { pointer(pServer), a2, a3 });
	}

	// Compression
	static int __fastcall Fog10219(uint8_t* pData)
	{
		return record("FOG_10219", {}, pData, 256);
	}

	static int __fastcall Fog10222(const uint8_t* pData, int nSize)
	{
		return record("FOG_10222", { nSize }, pData, nSize);
	}

	static int __fastcall Fog10223(uint8_t* pDest, int nDestSize, const uint8_t* pSource, int nSourceSize)
	{
		record("FOG_10223", { nDestSize, nSourceSize }, pSource, nSourceSize);

		int32_t nSize = 0;
		{
			std::lock_guard<std::mutex> lock(mutex);
			nSize = compressed_size >= 0 ? compressed_size : nSourceSize;
		}
		nSize = std::min(nSize, nDestSize);

		for (int32_t i = 0; i < nSize; ++i)
		{
			pDest[i] = static_cast<uint8_t>((nSourceSize > 0 ? pSource[i % nSourceSize] : i) ^ 0x5A);
		}
		return nSize;
	}

	// Decompression, writes the input as is
	static int __fastcall Fog10224(char* pDest, int nDestSize, uint8_t* pSource, int nSourceSize)
	{
		record("FOG_10224", { nDestSize, nSourceSize }, pSource, nSourceSize);

		const int32_t nSize = std::max(0, std::min(nSourceSize, nDestSize));
		if (nSize > 0)
		{
			std::memcpy(pDest, pSource, nSize);
		}
		return nSize;
	}

private:
	template<typename T>
	static int32_t pointer(T* ptr)
	{
		return static_cast<int32_t>(reinterpret_cast<uintptr_t>(ptr));
	}

	static int32_t record(const char* szFunction, std::initializer_list<int32_t> arguments, const void* pData = nullptr, int32_t nSize = 0, const char* szText = nullptr)
	{
		D2NetFogCall call;
		call.function = szFunction;
		call.arguments = arguments;
		if (pData && nSize > 0)
		{
			const auto pBytes = static_cast<const uint8_t*>(pData);
			call.data.assign(pBytes, pBytes + nSize);
		}
		if (szText)
		{
			call.text = szText;
		}

		std::lock_guard<std::mutex> lock(mutex);
		calls.push_back(std::move(call));
		return return_value;
	}
};


// Loads the original D2Net.dll and replaces the Fog functions it uses (see D2NetFogMock) for both implementations.
// The connection mode of both implementations is reset to D2NET_CONNECTION_REMOTE when the fixture is created and destroyed.
template<class Fixture>
struct D2NetFogMockFixture : Fixture
{
	uintptr_t d2net_base = 0;
	std::vector<InlineHook> fog_hooks;

	D2NetFogMockFixture()
	{
		const auto working_directory = std::filesystem::current_path();
		const auto original_d2net = LoadLibraryA((working_directory / "D2Net.dll").string().c_str());
		if (original_d2net == nullptr)
		{
			throw std::runtime_error("D2NetFogMockFixture: Cannot load original D2Net.dll");
		}
		d2net_base = reinterpret_cast<uintptr_t>(original_d2net);

		struct FogHookDefinition
		{
			WORD ordinal;
			void* moo_target;
			const void* replacement;
		};

		const FogHookDefinition definitions[] =
		{
			{ 10000, reinterpret_cast<void*>(&FOG_SOCKET_CloseSocket), reinterpret_cast<const void*>(&D2NetFogMock::SOCKET_CloseSocket) },
			{ 10015, reinterpret_cast<void*>(&FOG_ResolveHostIPAddress), reinterpret_cast<const void*>(&D2NetFogMock::ResolveHostIPAddress) },
			{ 10042, reinterpret_cast<void*>(&FOG_Alloc), reinterpret_cast<const void*>(&D2NetFogMock::Alloc) },
			{ 10043, reinterpret_cast<void*>(&FOG_Free), reinterpret_cast<const void*>(&D2NetFogMock::Free) },
			{ 10050, reinterpret_cast<void*>(&FOG_10050_EnterCriticalSection), reinterpret_cast<const void*>(&D2NetFogMock::LockCriticalSection) },
			{ 10149, reinterpret_cast<void*>(&FOG_InitializeServer), reinterpret_cast<const void*>(&D2NetFogMock::InitializeServer) },
			{ 10151, reinterpret_cast<void*>(&FOG_SetMaxClientsPerGame), reinterpret_cast<const void*>(&D2NetFogMock::SetMaxClientsPerGame) },
			{ 10152, reinterpret_cast<void*>(&FOG_10152), reinterpret_cast<const void*>(&D2NetFogMock::Fog10152) },
			{ 10154, reinterpret_cast<void*>(&FOG_WaitForSingleObject), reinterpret_cast<const void*>(&D2NetFogMock::WaitForSingleObject) },
			{ 10156, reinterpret_cast<void*>(&FOG_10156), reinterpret_cast<const void*>(&D2NetFogMock::Fog10156) },
			{ 10157, reinterpret_cast<void*>(&FOG_10157), reinterpret_cast<const void*>(&D2NetFogMock::Fog10157) },
			{ 10158, reinterpret_cast<void*>(&FOG_10158), reinterpret_cast<const void*>(&D2NetFogMock::Fog10158) },
			{ 10159, reinterpret_cast<void*>(&FOG_10159), reinterpret_cast<const void*>(&D2NetFogMock::Fog10159) },
			{ 10161, reinterpret_cast<void*>(&FOG_10161), reinterpret_cast<const void*>(&D2NetFogMock::Fog10161) },
			{ 10162, reinterpret_cast<void*>(&FOG_10162), reinterpret_cast<const void*>(&D2NetFogMock::Fog10162) },
			{ 10163, reinterpret_cast<void*>(&FOG_10163), reinterpret_cast<const void*>(&D2NetFogMock::Fog10163) },
			{ 10164, reinterpret_cast<void*>(&FOG_10164), reinterpret_cast<const void*>(&D2NetFogMock::Fog10164) },
			{ 10165, reinterpret_cast<void*>(&FOG_10165), reinterpret_cast<const void*>(&D2NetFogMock::Fog10165) },
			{ 10166, reinterpret_cast<void*>(&FOG_10166), reinterpret_cast<const void*>(&D2NetFogMock::Fog10166) },
			{ 10170, reinterpret_cast<void*>(&FOG_10170), reinterpret_cast<const void*>(&D2NetFogMock::Fog10170) },
			{ 10171, reinterpret_cast<void*>(&FOG_10171), reinterpret_cast<const void*>(&D2NetFogMock::Fog10171) },
			{ 10172, reinterpret_cast<void*>(&FOG_10172), reinterpret_cast<const void*>(&D2NetFogMock::Fog10172) },
			{ 10173, reinterpret_cast<void*>(&FOG_10173), reinterpret_cast<const void*>(&D2NetFogMock::Fog10173) },
			{ 10175, reinterpret_cast<void*>(&FOG_10175), reinterpret_cast<const void*>(&D2NetFogMock::Fog10175) },
			{ 10177, reinterpret_cast<void*>(&FOG_10177), reinterpret_cast<const void*>(&D2NetFogMock::Fog10177) },
			{ 10178, reinterpret_cast<void*>(&FOG_SetHackListEnabled), reinterpret_cast<const void*>(&D2NetFogMock::SetHackListEnabled) },
			{ 10180, reinterpret_cast<void*>(&FOG_10180), reinterpret_cast<const void*>(&D2NetFogMock::Fog10180) },
			{ 10182, reinterpret_cast<void*>(&FOG_10182_Return), reinterpret_cast<const void*>(&D2NetFogMock::Fog10182) },
			{ 10183, reinterpret_cast<void*>(&FOG_10183_Return), reinterpret_cast<const void*>(&D2NetFogMock::Fog10183) },
			{ 10186, reinterpret_cast<void*>(&FOG_10186), reinterpret_cast<const void*>(&D2NetFogMock::Fog10186) },
			{ 10187, reinterpret_cast<void*>(&FOG_10187), reinterpret_cast<const void*>(&D2NetFogMock::Fog10187) },
			{ 10219, reinterpret_cast<void*>(&FOG_10219), reinterpret_cast<const void*>(&D2NetFogMock::Fog10219) },
			{ 10222, reinterpret_cast<void*>(&FOG_10222), reinterpret_cast<const void*>(&D2NetFogMock::Fog10222) },
			{ 10223, reinterpret_cast<void*>(&FOG_10223), reinterpret_cast<const void*>(&D2NetFogMock::Fog10223) },
			{ 10224, reinterpret_cast<void*>(&FOG_10224), reinterpret_cast<const void*>(&D2NetFogMock::Fog10224) },
		};

		// The D2MOO implementation and the original D2Net.dll usually call into the same Fog.dll, so each target is only hooked once.
		std::vector<void*> hooked_targets;
		const auto hook = [this, &hooked_targets](void* target, const void* replacement)
		{
			if (target == nullptr || std::find(hooked_targets.begin(), hooked_targets.end(), target) != hooked_targets.end())
			{
				return;
			}

			hooked_targets.push_back(target);
			fog_hooks.emplace_back(target, replacement);
		};

		fog_hooks.reserve(2 * std::size(definitions));
		for (const auto& definition : definitions)
		{
			// Function called by the D2MOO implementation linked into the test executable
			hook(definition.moo_target, definition.replacement);
			// Function called by the original D2Net.dll. If it does not import this ordinal, it can't call it either.
			hook(find_imported_function_by_ordinal(original_d2net, "Fog.dll", definition.ordinal), definition.replacement);
		}

		D2NetFogMock::reset();

		set_connection_mode(D2NET_CONNECTION_REMOTE);
	}

	~D2NetFogMockFixture()
	{
		set_connection_mode(D2NET_CONNECTION_REMOTE);

		// Must happen before the hooks are removed, since this memory was allocated by the mock
		D2NetFogMock::free_live_allocations();
		D2NetFogMock::reset();
	}

	void set_connection_mode(int32_t nConnectionMode)
	{
		const auto [moo_set_connection_mode, original_set_connection_mode] = make_function_pair(NET_SetConnectionMode, d2net_base + 0x00001A20);

		moo_set_connection_mode(nConnectionMode);
		original_set_connection_mode(nConnectionMode);
	}

	std::vector<D2NetFogCall> take_fog_calls()
	{
		return D2NetFogMock::take_calls();
	}
};
