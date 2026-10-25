#include <D2NetTestDefines.h>

#ifdef SERVER_TESTS

#include <doctest.h>

#include <WinSock2.h>
#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <type_traits>
#include <vector>

#include <EqualityMacros.h>
#include <RepetitionMacros.h>
#include <TestUtilities.h>
#include <D2Net/PacketVisitorDefinitions.h>
#include <Fixtures/D2Net/D2NetFogMockFixture.h>

#include <D2NetTestHelpers.h>

#include <Client.h>
#include <D2Net.h>
#include <Packet.h>
#include <Server.h>


// Initializes the server of both implementations (gpServer is the fake server of D2NetFogMock), and releases it at the end of the test
template<class Fixture>
struct D2NetServerFixture : Fixture
{
	D2NetServerFixture()
	{
		const auto [moo_initialize, original_initialize] = make_function_pair(SERVER_Initialize, this->d2net_base + 0x00002150);
		moo_initialize(0, 0);
		original_initialize(0, 0);

		this->take_fog_calls();
	}

	~D2NetServerFixture()
	{
		const auto [moo_release, original_release] = make_function_pair(SERVER_Release, this->d2net_base + 0x00002220);
		moo_release();
		original_release();
	}
};

using ServerFixture = D2NetServerFixture<D2NetFogMockFixture<NoopFixture>>;
using ServerAndLocalClientFixture = D2NetLocalClientFixture<D2NetServerFixture<D2NetFogMockFixture<NoopFixture>>>;


static int32_t random_int32()
{
	return static_cast<int32_t>(random_unsigned_integer());
}

// Random content with many zeroes, so that string lengths and sizes encoded in packets are often small
static D2NetReceiveBufferStrc make_random_packet_buffer(uint8_t nHeader)
{
	D2NetReceiveBufferStrc buffer{};
	for (auto& byte : buffer.data)
	{
		byte = random_unsigned_integer(0, 7) == 0 ? 0 : static_cast<uint8_t>(random_unsigned_integer(0, 255));
	}
	buffer.data[0] = nHeader;
	// Strings read by the packet size functions always end inside the buffer
	buffer.data[sizeof(buffer.data) - 2] = 0;
	buffer.data[sizeof(buffer.data) - 1] = 0;
	buffer.nUsedBytes = 0;
	return buffer;
}

static uint32_t random_buffer_size()
{
	switch (random_unsigned_integer(0, 3))
	{
	case 0:
		return 0;
	case 1:
		return random_unsigned_integer(1, 16);
	case 2:
		return random_unsigned_integer(1, 64);
	default:
		return random_unsigned_integer(0, sizeof(D2NetReceiveBufferStrc::data));
	}
}

// Calls both implementations of a function that forwards its arguments to Fog, then compares their results and the Fog calls they made
template<typename Function, typename... Args>
static void compare_results_and_fog_calls(Function sut, Function original, Args... args)
{
	using Result = std::invoke_result_t<Function, Args...>;

	D2NetFogMock::take_calls();
	D2NetFogMock::return_value = random_int32();

	if constexpr (std::is_void_v<Result>)
	{
		// Call both implementations
		sut(args...);
		auto moo_fog_calls = D2NetFogMock::take_calls();
		original(args...);
		auto original_fog_calls = D2NetFogMock::take_calls();

		// Compare Fog calls
		MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");
	}
	else
	{
		// Call both implementations
		const auto moo_result = sut(args...);
		auto moo_fog_calls = D2NetFogMock::take_calls();
		const auto original_result = original(args...);
		auto original_fog_calls = D2NetFogMock::take_calls();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare Fog calls
		MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");
	}
}


// SERVER_Read*Packet: compares the results, the Fog calls and the content written to the buffer
using D2NetReadPacketFunction = int32_t(__stdcall*)(uint8_t* pBuffer, int32_t nBufferSize);
static void compare_read_packet(D2NetReadPacketFunction sut, D2NetReadPacketFunction original)
{
	// Input data
	const auto nBufferSize = static_cast<int32_t>(random_unsigned_integer(0, sizeof(D2NetReceiveBufferStrc::data)));
	D2NetReceiveBufferStrc moo_pBuffer{};
	D2NetReceiveBufferStrc original_pBuffer{};

	D2NetFogMock::take_calls();
	D2NetFogMock::return_value = random_int32();

	// Call both implementations
	const auto moo_result = sut(moo_pBuffer.data, nBufferSize);
	auto moo_fog_calls = D2NetFogMock::take_calls();
	const auto original_result = original(original_pBuffer.data, nBufferSize);
	auto original_fog_calls = D2NetFogMock::take_calls();

	// Compare return values
	MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

	// Compare potentially modified input data
	MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");

	// Compare Fog calls
	MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");
}


static void __stdcall DummyRemoveClientCallback(int32_t nClientId, const char* szFile, int32_t nLine)
{
}


TEST_SUITE("ServerTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Net.dll").string().c_str()));


	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC01B30 (#10024)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_WSAGetLastError, dll_base + 0x00001B30);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nError = random_int32();

			// Call both implementations
			WSASetLastError(nError);
			const auto moo_result = sut();
			WSASetLastError(nError);
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			CHECK_EQ(moo_result, nError);
		}
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC01B60 (#10030)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_GetServerPacketSize, dll_base + 0x00001B60);

		REPEAT_10();

		SUBCASE("")
		{
			for (int32_t nHeader = 0; nHeader < 256; ++nHeader)
			{
				// Input data
				const auto nBufferSize = random_buffer_size();
				const auto nInitialSize = random_int32();

				D2NetReceiveBufferStrc moo_pBuffer = make_random_packet_buffer(static_cast<uint8_t>(nHeader));
				D2NetReceiveBufferStrc original_pBuffer = moo_pBuffer;
				int32_t moo_pSize = nInitialSize;
				int32_t original_pSize = nInitialSize;

				// Call both implementations
				const auto moo_result = sut(&moo_pBuffer, nBufferSize, &moo_pSize);
				const auto original_result = original(&original_pBuffer, nBufferSize, &original_pSize);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
				MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
			}
		}
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC01E60 (#10031)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_GetClientPacketSize, dll_base + 0x00001E60);

		REPEAT_10();

		SUBCASE("")
		{
			for (int32_t nHeader = 0; nHeader < 256; ++nHeader)
			{
				// Input data
				const auto nBufferSize = random_buffer_size();
				const auto nInitialSize = random_int32();

				D2NetReceiveBufferStrc moo_pBuffer = make_random_packet_buffer(static_cast<uint8_t>(nHeader));
				D2NetReceiveBufferStrc original_pBuffer = moo_pBuffer;
				int32_t moo_pSize = nInitialSize;
				int32_t original_pSize = nInitialSize;

				// Call both implementations
				const auto moo_result = sut(&moo_pBuffer, nBufferSize, &moo_pSize);
				const auto original_result = original(&original_pBuffer, nBufferSize, &original_pSize);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
				MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
			}
		}
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC01FA0 (#10039)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_GetClientSendFunction, dll_base + 0x00001FA0);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Each implementation returns its own CLIENT_Send
			CHECK_EQ(reinterpret_cast<uintptr_t>(moo_result), reinterpret_cast<uintptr_t>(&CLIENT_Send));
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result), dll_base + 0x00001760);
		}
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC01FB0 (#10040)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_GetClientGameGUIDFunction, dll_base + 0x00001FB0);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Each implementation returns its own SERVER_GetClientGameGUID
			CHECK_EQ(reinterpret_cast<uintptr_t>(moo_result), reinterpret_cast<uintptr_t>(&SERVER_GetClientGameGUID));
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result), dll_base + 0x00002580);
		}
	}

	TEST_CASE_FIXTURE(ServerAndLocalClientFixture, "D2Net.0x6FC01FC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_SendToLocalClientCallback, dll_base + 0x00001FC0);

		REPEAT_10();

		SUBCASE("")
		{
			initialize_clients(D2NET_CONNECTION_LOCAL);
			clear_client_queues();

			// Input data
			const auto stream = make_server_packet_stream(random_unsigned_integer(1, 10), true, true, sizeof(D2NetReceiveBufferStrc::data));

			D2NetReceiveBufferStrc moo_pPacketBuffer = make_receive_buffer(stream);
			D2NetReceiveBufferStrc original_pPacketBuffer = make_receive_buffer(stream);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pPacketBuffer, static_cast<int32_t>(stream.size()));
			const auto original_result = original(nullptr, &original_pPacketBuffer, static_cast<int32_t>(stream.size()));

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPacketBuffer, original_pPacketBuffer, "Comparing pPacketBuffer");

			// Compare the packets that were sent to the clients
			auto moo_game_packets = drain_moo_game_packets();
			auto original_game_packets = drain_original_game_packets();
			MOO_CHECK_EQ(moo_game_packets, original_game_packets, "Comparing game packets");

			auto moo_system_packets = drain_moo_system_packets();
			auto original_system_packets = drain_original_system_packets();
			MOO_CHECK_EQ(moo_system_packets, original_system_packets, "Comparing system packets");
		}
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC01FE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_ValidateClientPacket, dll_base + 0x00001FE0);

		REPEAT_10();

		SUBCASE("")
		{
			for (int32_t nHeader = 0; nHeader < 256; ++nHeader)
			{
				// Input data
				const auto nBufferSize = random_buffer_size();
				const auto nInitialValue = random_int32();
				const auto nUnused1 = random_int32();
				const auto nUnused2 = random_int32();

				D2NetReceiveBufferStrc moo_pPacketBuffer = make_random_packet_buffer(static_cast<uint8_t>(nHeader));
				D2NetReceiveBufferStrc original_pPacketBuffer = moo_pPacketBuffer;
				int32_t moo_pPacketSize = nInitialValue;
				int32_t original_pPacketSize = nInitialValue;
				int32_t moo_a4 = nInitialValue;
				int32_t original_a4 = nInitialValue;
				int32_t moo_pPacketQueue = nInitialValue;
				int32_t original_pPacketQueue = nInitialValue;
				int32_t moo_a6 = nInitialValue;
				int32_t original_a6 = nInitialValue;

				// Call both implementations
				const auto moo_result = sut(&moo_pPacketBuffer, nBufferSize, &moo_pPacketSize, &moo_a4, &moo_pPacketQueue, &moo_a6, nUnused1, nUnused2);
				const auto original_result = original(&original_pPacketBuffer, nBufferSize, &original_pPacketSize, &original_a4, &original_pPacketQueue, &original_a6, nUnused1, nUnused2);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPacketBuffer, original_pPacketBuffer, "Comparing pPacketBuffer");
				MOO_CHECK_EQ(moo_pPacketSize, original_pPacketSize, "Comparing pPacketSize");
				MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
				MOO_CHECK_EQ(moo_pPacketQueue, original_pPacketQueue, "Comparing pPacketQueue");
				MOO_CHECK_EQ(moo_a6, original_a6, "Comparing a6");
			}
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC020B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_OnClientConnectedCallback, dll_base + 0x000020B0);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32(), random_int32(), random_int32(), random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC020E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_OnClientDisconnectedCallback, dll_base + 0x000020E0);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32(), random_int32(), random_int32(), random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerAndLocalClientFixture, "D2Net.0x6FC02110")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_DisableLocalClientCompression, dll_base + 0x00002110);

		SUBCASE("Remote connection")
		{
			for (const int32_t nReturnValue : { 0, 1, random_int32() })
			{
				D2NetFogMock::take_calls();
				D2NetFogMock::return_value = nReturnValue;

				// Call both implementations
				const auto moo_result = sut();
				auto moo_fog_calls = take_fog_calls();
				const auto original_result = original();
				auto original_fog_calls = take_fog_calls();

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare Fog calls
				MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");
			}
		}

		SUBCASE("Local connection")
		{
			initialize_clients(D2NET_CONNECTION_LOCAL);
			clear_client_queues();

			// Call both implementations
			const auto moo_result = sut();
			auto moo_fog_calls = take_fog_calls();
			const auto original_result = original();
			auto original_fog_calls = take_fog_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare Fog calls
			MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");

			// Compare the packets that were sent to the clients
			auto moo_system_packets = drain_moo_system_packets();
			auto original_system_packets = drain_original_system_packets();
			MOO_CHECK_EQ(moo_system_packets, original_system_packets, "Comparing system packets");
			CHECK_EQ(moo_system_packets.size(), 1u);
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02130 (#10002)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_WaitForSingleObject, dll_base + 0x00002130);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_unsigned_integer());
		}
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC02150 (#10003)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_Initialize, dll_base + 0x00002150);
		const auto [moo_release, original_release] = make_function_pair(SERVER_Release, dll_base + 0x00002220);
		const auto [moo_10027, original_10027] = make_function_pair(D2NET_10027, dll_base + 0x000021F0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto a1 = random_int32();
			const auto a2 = random_int32();

			// Call both implementations
			take_fog_calls();
			sut(a1, a2);
			auto moo_fog_calls = take_fog_calls();
			const std::vector<void*> moo_callbacks(std::begin(D2NetFogMock::server_callbacks), std::end(D2NetFogMock::server_callbacks));

			original(a1, a2);
			auto original_fog_calls = take_fog_calls();
			const std::vector<void*> original_callbacks(std::begin(D2NetFogMock::server_callbacks), std::end(D2NetFogMock::server_callbacks));

			// Compare Fog calls
			MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");

			// Each implementation registers its own callbacks
			REQUIRE_EQ(moo_callbacks.size(), 4u);
			CHECK_EQ(moo_callbacks[0], reinterpret_cast<void*>(&SERVER_ValidateClientPacket));
			CHECK_EQ(moo_callbacks[1], reinterpret_cast<void*>(&SERVER_OnClientConnectedCallback));
			CHECK_EQ(moo_callbacks[2], reinterpret_cast<void*>(&SERVER_OnClientDisconnectedCallback));
			CHECK_EQ(moo_callbacks[3], reinterpret_cast<void*>(&SERVER_SendToLocalClientCallback));

			REQUIRE_EQ(original_callbacks.size(), 4u);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_callbacks[0]), dll_base + 0x00001FE0);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_callbacks[1]), dll_base + 0x000020B0);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_callbacks[2]), dll_base + 0x000020E0);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_callbacks[3]), dll_base + 0x00001FC0);

			// Both implementations now use the server returned by FOG_InitializeServer
			moo_10027();
			auto moo_server_calls = take_fog_calls();
			original_10027();
			auto original_server_calls = take_fog_calls();
			MOO_CHECK_EQ(moo_server_calls, original_server_calls, "Comparing Fog calls using the server");
			REQUIRE_EQ(moo_server_calls.size(), 1u);
			CHECK_EQ(moo_server_calls[0].arguments.at(0), static_cast<int32_t>(reinterpret_cast<uintptr_t>(D2NetFogMock::server())));

			moo_release();
			original_release();
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02190 (#10035)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10035, dll_base + 0x00002190);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32(), random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC021B0 (#10036)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10036, dll_base + 0x000021B0);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32(), random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC021D0 (#10026)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_SetMaxClientsPerGame, dll_base + 0x000021D0);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC021F0 (#10027)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10027, dll_base + 0x000021F0);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original);
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02200 (#10023)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_SetHackListEnabled, dll_base + 0x00002200);

		SUBCASE("")
		{
			for (const BOOL bEnabled : { FALSE, TRUE, random_int32() })
			{
				compare_results_and_fog_calls(sut, original, bEnabled);
			}
		}
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC02220 (#10004)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_Release, dll_base + 0x00002220);
		const auto [moo_initialize, original_initialize] = make_function_pair(SERVER_Initialize, dll_base + 0x00002150);
		const auto [moo_10018, original_10018] = make_function_pair(D2NET_10018, dll_base + 0x00002510);

		SUBCASE("")
		{
			// Input data
			moo_initialize(0, 0);
			original_initialize(0, 0);

			// Call both implementations
			compare_results_and_fog_calls(sut, original);

			// gpServer was reset: D2NET_10018 does not call Fog without a server
			moo_10018(random_int32());
			original_10018(random_int32());
			CHECK(take_fog_calls().empty());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02250 (#10010)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_ReadGamePacket, dll_base + 0x00002250);

		REPEAT_10();

		SUBCASE("")
		{
			compare_read_packet(sut, original);
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02270 (#10011)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_ReadSystemPacket, dll_base + 0x00002270);

		REPEAT_10();

		SUBCASE("")
		{
			compare_read_packet(sut, original);
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02290 (#10012)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_ReadAdminPacket, dll_base + 0x00002290);

		REPEAT_10();

		SUBCASE("")
		{
			compare_read_packet(sut, original);
		}
	}

	TEST_CASE_FIXTURE(ServerAndLocalClientFixture, "D2Net.0x6FC022B0 (#10006)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_SendPacketToClient, dll_base + 0x000022B0);

		REPEAT_10();

		// Structured bindings can't be captured by lambdas in C++17
		const auto moo_send_packet_to_client = sut;
		const auto original_send_packet_to_client = original;
		const auto run = [&](int8_t nSendMode, int32_t nClientId, const D2NetReceiveBufferStrc& packet, uint32_t nPacketSize)
		{
			D2NetReceiveBufferStrc moo_pPacketArg = packet;
			D2NetReceiveBufferStrc original_pPacketArg = packet;

			// Call both implementations
			take_fog_calls();
			const auto moo_result = moo_send_packet_to_client(nSendMode, nClientId, moo_pPacketArg.data, nPacketSize);
			auto moo_fog_calls = take_fog_calls();
			const auto original_result = original_send_packet_to_client(nSendMode, nClientId, original_pPacketArg.data, nPacketSize);
			auto original_fog_calls = take_fog_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPacketArg, original_pPacketArg, "Comparing pPacketArg");

			// Compare Fog calls
			MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");
		};

		SUBCASE("Remote connection, compression info")
		{
			for (const int8_t nSendMode : { D2NET_SEND_SYSTEM, D2NET_SEND_GAME, D2NET_SEND_UNCOMPRESSED })
			{
				for (const int32_t nReturnValue : { 0, 1 })
				{
					D2NetFogMock::return_value = nReturnValue;

					D2NetReceiveBufferStrc packet = make_random_packet_buffer(SERVER_PACKET_HEADER_COMPRESSION_INFO);
					run(nSendMode, random_int32(), packet, random_unsigned_integer(1, 2));
				}
			}
		}

		SUBCASE("Remote connection, uncompressed")
		{
			for (const int32_t nReturnValue : { 0, 1 })
			{
				D2NetFogMock::return_value = nReturnValue;

				D2NetReceiveBufferStrc packet = make_random_packet_buffer(static_cast<uint8_t>(random_unsigned_integer(0, 255)));
				run(D2NET_SEND_UNCOMPRESSED, random_int32(), packet, random_unsigned_integer(1, MAX_MSG_SIZE));
			}
		}

		SUBCASE("Remote connection, compressed")
		{
			// Frames smaller than 0xF0 bytes have a 1 byte header, the others a 2 bytes header
			for (const int32_t nCompressedSize : { 1, 0xEE, 0xEF, 0xF0, static_cast<int32_t>(random_unsigned_integer(1, 0xEE)), static_cast<int32_t>(random_unsigned_integer(0xEF, 1032)) })
			{
				for (const int8_t nSendMode : { D2NET_SEND_SYSTEM, D2NET_SEND_GAME })
				{
					for (const int32_t nReturnValue : { 0, 1 })
					{
						D2NetFogMock::return_value = nReturnValue;
						D2NetFogMock::compressed_size = nCompressedSize;

						uint8_t nHeader = 0;
						do
						{
							nHeader = static_cast<uint8_t>(random_unsigned_integer(0, 255));
						} while (nHeader == SERVER_PACKET_HEADER_COMPRESSION_INFO);

						D2NetReceiveBufferStrc packet = make_random_packet_buffer(nHeader);
						run(nSendMode, random_int32(), packet, random_unsigned_integer(1, MAX_MSG_SIZE));
					}
				}
			}
		}

		SUBCASE("Local connection")
		{
			initialize_clients(D2NET_CONNECTION_LOCAL);
			clear_client_queues();

			// Input data
			const auto stream = make_server_packet_stream(random_unsigned_integer(1, 5), true, true, MAX_MSG_SIZE);
			const auto packet = make_receive_buffer(stream);

			for (const int8_t nSendMode : { D2NET_SEND_SYSTEM, D2NET_SEND_GAME, D2NET_SEND_UNCOMPRESSED })
			{
				run(nSendMode, 0, packet, static_cast<uint32_t>(stream.size()));
			}

			// Compare the packets that were sent to the clients
			auto moo_game_packets = drain_moo_game_packets();
			auto original_game_packets = drain_original_game_packets();
			MOO_CHECK_EQ(moo_game_packets, original_game_packets, "Comparing game packets");

			auto moo_system_packets = drain_moo_system_packets();
			auto original_system_packets = drain_original_system_packets();
			MOO_CHECK_EQ(moo_system_packets, original_system_packets, "Comparing system packets");
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02410 (#10014)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_GetIpAddressStringFromClientId, dll_base + 0x00002410);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nClientId = random_int32();
			const auto nBufferSize = static_cast<int32_t>(random_unsigned_integer(1, 32));

			char moo_szBuffer[32]{};
			char original_szBuffer[32]{};

			// Call both implementations
			take_fog_calls();
			sut(nClientId, moo_szBuffer, nBufferSize);
			auto moo_fog_calls = take_fog_calls();
			original(nClientId, original_szBuffer, nBufferSize);
			auto original_fog_calls = take_fog_calls();

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_szBuffer, original_szBuffer, "Comparing szBuffer");

			// Compare Fog calls
			MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02430 (#10038)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_GetIpAddressFromClientId, dll_base + 0x00002430);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02450 (#10037)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_GetSocketFromClientId, dll_base + 0x00002450);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02470 (#10015)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10015, dll_base + 0x00002470);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32(), "D2NetTests.cpp", random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02490 (#10032)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10032, dll_base + 0x00002490);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32(), "D2NetTests.cpp", random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC024B0 (#10033)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10033, dll_base + 0x000024B0);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32(), random_int32(), random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC024D0 (#10034)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10034, dll_base + 0x000024D0);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32(), random_int32(), random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC024F0 (#10016)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10016, dll_base + 0x000024F0);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32());
		}
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC02510 (#10018)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10018, dll_base + 0x00002510);
		const auto [moo_initialize, original_initialize] = make_function_pair(SERVER_Initialize, dll_base + 0x00002150);
		const auto [moo_release, original_release] = make_function_pair(SERVER_Release, dll_base + 0x00002220);

		REPEAT_10();

		SUBCASE("Without server")
		{
			compare_results_and_fog_calls(sut, original, random_int32());
		}

		SUBCASE("With server")
		{
			moo_initialize(0, 0);
			original_initialize(0, 0);

			compare_results_and_fog_calls(sut, original, random_int32());

			moo_release();
			original_release();
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02530 (#10019)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_SetRemoveClientCallback, dll_base + 0x00002530);

		SUBCASE("")
		{
			for (const D2NET_RemoveClientCallback pfRemoveClient : { static_cast<D2NET_RemoveClientCallback>(nullptr), &DummyRemoveClientCallback })
			{
				compare_results_and_fog_calls(sut, original, pfRemoveClient);
			}
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02550 (#10020)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_SetClientGameGUID, dll_base + 0x00002550);
		const auto [moo_get_client_game_guid, original_get_client_game_guid] = make_function_pair(SERVER_GetClientGameGUID, dll_base + 0x00002580);

		REPEAT_10();

		SUBCASE("Local client")
		{
			// Input data
			const auto dwGameGuid = random_int32();

			compare_results_and_fog_calls(sut, original, 0, dwGameGuid);

			// The GUID of the local client is stored by D2Net
			const auto moo_result = moo_get_client_game_guid(0);
			const auto original_result = original_get_client_game_guid(0);
			MOO_CHECK_EQ(moo_result, original_result, "Comparing SERVER_GetClientGameGUID results");
			CHECK_EQ(moo_result, dwGameGuid);
		}

		SUBCASE("Remote client")
		{
			int32_t nClientId = 0;
			while (nClientId == 0)
			{
				nClientId = random_int32();
			}

			compare_results_and_fog_calls(sut, original, nClientId, random_int32());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02580 (#10021)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_GetClientGameGUID, dll_base + 0x00002580);
		const auto [moo_set_client_game_guid, original_set_client_game_guid] = make_function_pair(SERVER_SetClientGameGUID, dll_base + 0x00002550);

		REPEAT_10();

		SUBCASE("Local client")
		{
			// Input data
			const auto dwGameGuid = random_int32();
			moo_set_client_game_guid(0, dwGameGuid);
			original_set_client_game_guid(0, dwGameGuid);

			compare_results_and_fog_calls(sut, original, 0);
		}

		SUBCASE("Remote client")
		{
			int32_t nClientId = 0;
			while (nClientId == 0)
			{
				nClientId = random_int32();
			}

			compare_results_and_fog_calls(sut, original, nClientId);
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC025A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SERVER_EnqueueLocalClientPacket, dll_base + 0x000025A0);

		REPEAT_10();

		SUBCASE("")
		{
			for (const int32_t nReturnValue : { 0, 1, random_int32() })
			{
				// Input data
				const auto nPacketSize = static_cast<uint16_t>(random_unsigned_integer(0, MAX_MSG_SIZE));
				const D2NetReceiveBufferStrc packet = make_random_packet_buffer(static_cast<uint8_t>(random_unsigned_integer(0, 255)));
				D2NetReceiveBufferStrc moo_pPacket = packet;
				D2NetReceiveBufferStrc original_pPacket = packet;

				D2NetFogMock::return_value = nReturnValue;

				// Call both implementations
				take_fog_calls();
				const auto moo_result = sut(moo_pPacket.data, nPacketSize);
				auto moo_fog_calls = take_fog_calls();
				const auto original_result = original(original_pPacket.data, nPacketSize);
				auto original_fog_calls = take_fog_calls();

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");

				// Compare Fog calls
				MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");
			}
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC025F0 (#10022)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10022, dll_base + 0x000025F0);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_unsigned_integer());
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02610 (#10028)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10028_Return, dll_base + 0x00002610);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original);
		}
	}

	TEST_CASE_FIXTURE(ServerFixture, "D2Net.0x6FC02620 (#10029)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2NET_10029_Return, dll_base + 0x00002620);

		REPEAT_10();

		SUBCASE("")
		{
			compare_results_and_fog_calls(sut, original, random_int32());
		}
	}
}

#endif
