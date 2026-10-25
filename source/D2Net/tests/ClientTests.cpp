#include <D2NetTestDefines.h>

#ifdef CLIENT_TESTS

#include <doctest.h>

#include <WinSock2.h>
#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <initializer_list>
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


using LocalClientFixture = D2NetLocalClientFixture<D2NetFogMockFixture<NoopFixture>>;


// Client functions of one implementation, used to run the same remote session with both implementations
struct D2NetClientFunctions
{
	decltype(&CLIENT_Initialize) initialize;
	decltype(&CLIENT_GetConnectionStatus) get_connection_status;
	decltype(&CLIENT_IsConnected) is_connected;
	decltype(&CLIENT_GetLocalIpAddressString) get_local_ip_address_string;
	decltype(&CLIENT_Send) send;
	D2NetDequeueFunction dequeue_game_packet;
	D2NetDequeueFunction dequeue_system_packet;
	decltype(&CLIENT_Release) release;
};

static D2NetClientFunctions make_moo_client_functions()
{
	return {
		&CLIENT_Initialize,
		&CLIENT_GetConnectionStatus,
		&CLIENT_IsConnected,
		&CLIENT_GetLocalIpAddressString,
		&CLIENT_Send,
		&CLIENT_DequeueGamePacket,
		&CLIENT_DequeueSystemPacket,
		&CLIENT_Release,
	};
}

static D2NetClientFunctions make_original_client_functions(uintptr_t dll_base)
{
	return {
		reinterpret_cast<decltype(&CLIENT_Initialize)>(dll_base + 0x000011B0),
		reinterpret_cast<decltype(&CLIENT_GetConnectionStatus)>(dll_base + 0x00001120),
		reinterpret_cast<decltype(&CLIENT_IsConnected)>(dll_base + 0x00001000),
		reinterpret_cast<decltype(&CLIENT_GetLocalIpAddressString)>(dll_base + 0x000019A0),
		reinterpret_cast<decltype(&CLIENT_Send)>(dll_base + 0x00001760),
		reinterpret_cast<D2NetDequeueFunction>(dll_base + 0x00001300),
		reinterpret_cast<D2NetDequeueFunction>(dll_base + 0x00001310),
		reinterpret_cast<decltype(&CLIENT_Release)>(dll_base + 0x00001240),
	};
}

// What the server sends and expects during a remote session
struct D2NetRemoteSessionInput
{
	// Sent by the client with CLIENT_Send
	std::vector<uint8_t> client_data;
	// Sent by the server before enabling compression
	std::vector<uint8_t> uncompressed_stream;
	size_t uncompressed_packet_count = 0;
	// Sent by the server once compression is enabled, each frame is a size header followed by the "compressed" packets.
	// The Fog decompression mock leaves the data as is.
	std::vector<std::vector<uint8_t>> compressed_frames;
	size_t compressed_packet_count = 0;
};

struct D2NetRemoteSessionResult
{
	bool server_accepted_connection = false;
	int32_t initialize_result = 0;
	int32_t connection_status = 0;
	int32_t is_connected = 0;
	char local_ip_address[32]{};
	int32_t send_result = 0;
	std::vector<uint8_t> received_by_server;
	std::vector<D2NetDequeuedPacket> game_packets;
	std::vector<D2NetDequeuedPacket> system_packets;
	int32_t is_connected_after_release = 0;
	std::vector<D2NetFogCall> fog_calls;
};

static std::vector<uint8_t> make_compressed_frame(const std::vector<uint8_t>& payload)
{
	std::vector<uint8_t> frame;
	if (payload.size() + 1 < 0xF0)
	{
		frame.push_back(static_cast<uint8_t>(payload.size() + 1));
	}
	else
	{
		const auto nFrameSize = payload.size() + 2;
		frame.push_back(static_cast<uint8_t>(0xF0 | ((nFrameSize >> 8) & 0x0F)));
		frame.push_back(static_cast<uint8_t>(nFrameSize & 0xFF));
	}
	frame.insert(frame.end(), payload.begin(), payload.end());
	return frame;
}

static D2NetRemoteSessionInput make_remote_session_input()
{
	D2NetRemoteSessionInput input;

	for (uint32_t i = 0, nSize = random_unsigned_integer(1, MAX_MSG_SIZE); i < nSize; ++i)
	{
		input.client_data.push_back(static_cast<uint8_t>(random_unsigned_integer(0, 255)));
	}

	input.uncompressed_stream = make_server_packet_stream(random_unsigned_integer(1, 10), true, true, 1000, &input.uncompressed_packet_count);

	// A frame with a 1 byte header
	size_t nPacketCount = 0;
	input.compressed_frames.push_back(make_compressed_frame(make_server_packet_stream(random_unsigned_integer(1, 3), true, true, 0xE0, &nPacketCount)));
	input.compressed_packet_count += nPacketCount;

	// A frame with a 2 bytes header
	std::vector<uint8_t> payload;
	for (int i = 0; i < 16 && payload.size() < 0xF0; ++i)
	{
		payload = make_server_packet_stream(32, true, true, 600, &nPacketCount);
	}
	input.compressed_frames.push_back(make_compressed_frame(payload));
	input.compressed_packet_count += nPacketCount;

	return input;
}

// Connects the client to the local server, exchanges data and releases the client
static D2NetRemoteSessionResult run_remote_session(const D2NetClientFunctions& functions, const D2NetLocalGameServer& server, const D2NetRemoteSessionInput& input)
{
	D2NetRemoteSessionResult result;

	D2NetFogMock::take_calls();

	result.initialize_result = functions.initialize(D2NET_CONNECTION_REMOTE, "127.0.0.1");

	// CLIENT_GetConnectionStatus waits up to 100ms for the connection thread
	result.connection_status = CLIENT_CONNECTION_PENDING;
	for (int i = 0; i < 50 && result.connection_status == CLIENT_CONNECTION_PENDING; ++i)
	{
		result.connection_status = functions.get_connection_status();
	}

	const SOCKET nServerSocket = server.accept_client();
	result.server_accepted_connection = nServerSocket != INVALID_SOCKET;

	if (result.connection_status == CLIENT_CONNECTION_ESTABLISHED && result.server_accepted_connection)
	{
		result.is_connected = functions.is_connected();

		functions.get_local_ip_address_string(result.local_ip_address);

		result.send_result = functions.send(0, input.client_data.data(), static_cast<int32_t>(input.client_data.size()));
		result.received_by_server = D2NetLocalGameServer::receive(nServerSocket, input.client_data.size());

		// Packets sent before compression is enabled, followed by the compression info
		std::vector<uint8_t> uncompressed_stream = input.uncompressed_stream;
		uncompressed_stream.push_back(SERVER_PACKET_HEADER_COMPRESSION_INFO);
		uncompressed_stream.push_back(1);
		D2NetLocalGameServer::send_all(nServerSocket, uncompressed_stream);

		// Compressed frames must only be sent once the client parsed the compression info, otherwise they could be received together
		const size_t nUncompressedPacketCount = input.uncompressed_packet_count + 1;
		poll_packets(functions.dequeue_game_packet, functions.dequeue_system_packet, result.game_packets, result.system_packets, nUncompressedPacketCount);

		if (result.game_packets.size() + result.system_packets.size() == nUncompressedPacketCount)
		{
			for (const auto& frame : input.compressed_frames)
			{
				D2NetLocalGameServer::send_all(nServerSocket, frame);
			}

			poll_packets(functions.dequeue_game_packet, functions.dequeue_system_packet, result.game_packets, result.system_packets, nUncompressedPacketCount + input.compressed_packet_count);
		}
	}

	functions.release();
	result.is_connected_after_release = functions.is_connected();

	if (nServerSocket != INVALID_SOCKET)
	{
		closesocket(nServerSocket);
	}

	result.fog_calls = D2NetFogMock::take_calls();
	return result;
}


TEST_SUITE("ClientTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Net.dll").string().c_str()));


	TEST_CASE_FIXTURE(LocalClientFixture, "D2Net.0x6FC01000 (#10017)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_IsConnected, dll_base + 0x00001000);

		SUBCASE("Local connection")
		{
			for (const int32_t nConnectionMode : { D2NET_CONNECTION_LOCAL, D2NET_CONNECTION_LOCAL_SIMULATED_LAG })
			{
				set_connection_mode(nConnectionMode);

				// Call both implementations
				const auto moo_result = sut();
				const auto original_result = original();

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}

		SUBCASE("Remote connection, client not initialized")
		{
			set_connection_mode(D2NET_CONNECTION_REMOTE);

			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}

		SUBCASE("Remote connection, not connected")
		{
			initialize_clients(D2NET_CONNECTION_LOCAL);
			set_connection_mode(D2NET_CONNECTION_REMOTE);

			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}

		SUBCASE("Remote connection, connected")
		{
			D2NetLocalGameServer server;
			if (!server.is_listening())
			{
				MESSAGE("Cannot listen on the game port, skipping");
				return;
			}

			// Call both implementations
			const auto input = make_remote_session_input();
			const auto moo_session = run_remote_session(make_moo_client_functions(), server, input);
			const auto original_session = run_remote_session(make_original_client_functions(dll_base), server, input);

			// Compare return values
			MOO_CHECK_EQ(moo_session.is_connected, original_session.is_connected, "Comparing results while connected");
			MOO_CHECK_EQ(moo_session.is_connected_after_release, original_session.is_connected_after_release, "Comparing results after release");
		}
	}

	TEST_CASE_FIXTURE(LocalClientFixture, "D2Net.0x6FC01040")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_ConnectToHost, dll_base + 0x00001040);
		const auto [moo_get_local_ip_address_string, original_get_local_ip_address_string] = make_function_pair(CLIENT_GetLocalIpAddressString, dll_base + 0x000019A0);

		SUBCASE("")
		{
			D2NetLocalGameServer server;
			if (!server.is_listening())
			{
				MESSAGE("Cannot listen on the game port, skipping");
				return;
			}

			// The critical section and receive buffer are only needed for CLIENT_Release
			initialize_clients(D2NET_CONNECTION_LOCAL);
			set_connection_mode(D2NET_CONNECTION_REMOTE);
			take_fog_calls();

			// Input data
			char szHostAddress[] = "127.0.0.1";

			// Call both implementations
			const auto moo_result = sut(szHostAddress);
			const SOCKET moo_server_socket = server.accept_client();
			auto moo_fog_calls = take_fog_calls();

			const auto original_result = original(szHostAddress);
			const SOCKET original_server_socket = server.accept_client();
			auto original_fog_calls = take_fog_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare Fog calls
			MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");

			// Both clients connected to the server
			CHECK_NE(moo_server_socket, INVALID_SOCKET);
			CHECK_NE(original_server_socket, INVALID_SOCKET);

			// Compare the address of the connected sockets
			char moo_szBuffer[32]{};
			char original_szBuffer[32]{};
			moo_get_local_ip_address_string(moo_szBuffer);
			original_get_local_ip_address_string(original_szBuffer);
			MOO_CHECK_EQ(moo_szBuffer, original_szBuffer, "Comparing local ip addresses");

			// Closes the client sockets
			release_clients();

			if (moo_server_socket != INVALID_SOCKET)
			{
				closesocket(moo_server_socket);
			}
			if (original_server_socket != INVALID_SOCKET)
			{
				closesocket(original_server_socket);
			}
		}
	}

	TEST_CASE_FIXTURE(LocalClientFixture, "D2Net.0x6FC01120 (#10025)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_GetConnectionStatus, dll_base + 0x00001120);

		SUBCASE("Local connection")
		{
			for (const int32_t nConnectionMode : { D2NET_CONNECTION_LOCAL, D2NET_CONNECTION_LOCAL_SIMULATED_LAG })
			{
				set_connection_mode(nConnectionMode);

				// Call both implementations
				const auto moo_result = sut();
				const auto original_result = original();

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				CHECK_EQ(moo_result, CLIENT_CONNECTION_ESTABLISHED);
			}
		}

		SUBCASE("Remote connection")
		{
			D2NetLocalGameServer server;
			if (!server.is_listening())
			{
				MESSAGE("Cannot listen on the game port, skipping");
				return;
			}

			// Call both implementations
			const auto input = make_remote_session_input();
			const auto moo_session = run_remote_session(make_moo_client_functions(), server, input);
			const auto original_session = run_remote_session(make_original_client_functions(dll_base), server, input);

			// Compare return values
			MOO_CHECK_EQ(moo_session.connection_status, original_session.connection_status, "Comparing results");
			CHECK_EQ(moo_session.connection_status, CLIENT_CONNECTION_ESTABLISHED);
			CHECK(moo_session.server_accepted_connection);
			CHECK(original_session.server_accepted_connection);
		}
	}

	TEST_CASE_FIXTURE(LocalClientFixture, "D2Net.0x6FC011B0 (#10000)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_Initialize, dll_base + 0x000011B0);
		const auto [moo_is_local_connection, original_is_local_connection] = make_function_pair(NET_IsLocalConnection, dll_base + 0x00001A00);

		SUBCASE("Local connection")
		{
			for (const int32_t nConnectionMode : { D2NET_CONNECTION_LOCAL, D2NET_CONNECTION_LOCAL_SIMULATED_LAG })
			{
				take_fog_calls();

				// Call both implementations
				const auto moo_result = sut(nConnectionMode, "127.0.0.1");
				moo_receive_buffer = static_cast<D2NetReceiveBufferStrc*>(D2NetFogMock::last_live_allocation_of_size(sizeof(D2NetReceiveBufferStrc)));
				const auto original_result = original(nConnectionMode, "127.0.0.1");
				original_receive_buffer = static_cast<D2NetReceiveBufferStrc*>(D2NetFogMock::last_live_allocation_of_size(sizeof(D2NetReceiveBufferStrc)));
				// Let the fixture release both clients
				clients_initialized = true;
				auto fog_calls = take_fog_calls();

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Neither implementation uses the server for the local client
				CHECK(fog_calls.empty());

				// Compare the receive buffers (gpReceiveBuffer)
				REQUIRE(moo_receive_buffer != nullptr);
				REQUIRE(original_receive_buffer != nullptr);
				MOO_CHECK_EQ(moo_receive_buffer, original_receive_buffer, "Comparing gpReceiveBuffer");

				// Compare the connection modes
				const auto moo_is_local = moo_is_local_connection();
				const auto original_is_local = original_is_local_connection();
				MOO_CHECK_EQ(moo_is_local, original_is_local, "Comparing NET_IsLocalConnection results");

				// The local client is told that the stream is not compressed
				auto moo_system_packets = drain_moo_system_packets();
				auto original_system_packets = drain_original_system_packets();
				MOO_CHECK_EQ(moo_system_packets, original_system_packets, "Comparing system packets");

				auto moo_game_packets = drain_moo_game_packets();
				auto original_game_packets = drain_original_game_packets();
				MOO_CHECK_EQ(moo_game_packets, original_game_packets, "Comparing game packets");

				release_clients();
			}
		}

		SUBCASE("Remote connection")
		{
			D2NetLocalGameServer server;
			if (!server.is_listening())
			{
				MESSAGE("Cannot listen on the game port, skipping");
				return;
			}

			// Call both implementations
			const auto input = make_remote_session_input();
			const auto moo_session = run_remote_session(make_moo_client_functions(), server, input);
			const auto original_session = run_remote_session(make_original_client_functions(dll_base), server, input);

			// Compare return values
			MOO_CHECK_EQ(moo_session.initialize_result, original_session.initialize_result, "Comparing results");

			// Compare Fog calls
			auto moo_fog_calls = moo_session.fog_calls;
			auto original_fog_calls = original_session.fog_calls;
			MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");
		}
	}

	TEST_CASE_FIXTURE(LocalClientFixture, "D2Net.0x6FC01240 (#10001)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_Release, dll_base + 0x00001240);
		const auto [moo_is_connected, original_is_connected] = make_function_pair(CLIENT_IsConnected, dll_base + 0x00001000);

		const auto nInitialAllocationCount = D2NetFogMock::live_allocation_count();

		SUBCASE("Local connection")
		{
			initialize_clients(D2NET_CONNECTION_LOCAL);
			clients_initialized = false;
			take_fog_calls();

			// Call both implementations
			sut();
			auto moo_fog_calls = take_fog_calls();
			original();
			auto original_fog_calls = take_fog_calls();

			// Compare Fog calls
			MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");

			// The receive buffer and the queued packets were freed
			CHECK_EQ(D2NetFogMock::live_allocation_count(), nInitialAllocationCount);
		}

		SUBCASE("Remote connection")
		{
			initialize_clients(D2NET_CONNECTION_LOCAL);
			clients_initialized = false;
			set_connection_mode(D2NET_CONNECTION_REMOTE);
			take_fog_calls();

			// Call both implementations
			sut();
			auto moo_fog_calls = take_fog_calls();
			original();
			auto original_fog_calls = take_fog_calls();

			// Compare Fog calls
			MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");

			// The receive buffer and the queued packets were freed
			CHECK_EQ(D2NetFogMock::live_allocation_count(), nInitialAllocationCount);

			// Without receive buffer, the remote client is not connected anymore
			const auto moo_result = moo_is_connected();
			const auto original_result = original_is_connected();
			MOO_CHECK_EQ(moo_result, original_result, "Comparing CLIENT_IsConnected results");
		}
	}

	TEST_CASE_FIXTURE(LocalClientFixture, "D2Net.0x6FC01300 (#10007)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_DequeueGamePacket, dll_base + 0x00001300);
		const auto [moo_enqueue, original_enqueue] = make_function_pair(CLIENT_EnqueuePacketsFromLocalServer, dll_base + 0x00001810);

		REPEAT_10();

		SUBCASE("")
		{
			initialize_clients(D2NET_CONNECTION_LOCAL);
			clear_client_queues();

			// Input data
			size_t nPacketCount = 0;
			const auto stream = make_server_packet_stream(random_unsigned_integer(1, 10), true, false, sizeof(D2NetReceiveBufferStrc::data), &nPacketCount);
			D2NetReceiveBufferStrc moo_packets = make_receive_buffer(stream);
			D2NetReceiveBufferStrc original_packets = make_receive_buffer(stream);
			moo_enqueue(&moo_packets, static_cast<int32_t>(stream.size()));
			original_enqueue(&original_packets, static_cast<int32_t>(stream.size()));

			// Call both implementations, until the queue is empty
			for (size_t i = 0; i <= nPacketCount; ++i)
			{
				const auto nBufferSize = random_unsigned_integer(0, sizeof(D2NetReceiveBufferStrc::data));
				D2NetReceiveBufferStrc moo_pBuffer{};
				D2NetReceiveBufferStrc original_pBuffer{};

				const auto moo_result = sut(moo_pBuffer.data, nBufferSize);
				const auto original_result = original(original_pBuffer.data, nBufferSize);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
			}
		}
	}

	TEST_CASE_FIXTURE(LocalClientFixture, "D2Net.0x6FC01310 (#10008)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_DequeueSystemPacket, dll_base + 0x00001310);
		const auto [moo_enqueue, original_enqueue] = make_function_pair(CLIENT_EnqueuePacketsFromLocalServer, dll_base + 0x00001810);

		REPEAT_10();

		SUBCASE("")
		{
			initialize_clients(D2NET_CONNECTION_LOCAL);
			clear_client_queues();

			// Input data
			size_t nPacketCount = 0;
			const auto stream = make_server_packet_stream(random_unsigned_integer(1, 10), false, true, sizeof(D2NetReceiveBufferStrc::data), &nPacketCount);
			D2NetReceiveBufferStrc moo_packets = make_receive_buffer(stream);
			D2NetReceiveBufferStrc original_packets = make_receive_buffer(stream);
			moo_enqueue(&moo_packets, static_cast<int32_t>(stream.size()));
			original_enqueue(&original_packets, static_cast<int32_t>(stream.size()));

			// Call both implementations, until the queue is empty
			for (size_t i = 0; i <= nPacketCount; ++i)
			{
				const auto nBufferSize = random_unsigned_integer(0, sizeof(D2NetReceiveBufferStrc::data));
				D2NetReceiveBufferStrc moo_pBuffer{};
				D2NetReceiveBufferStrc original_pBuffer{};

				const auto moo_result = sut(moo_pBuffer.data, nBufferSize);
				const auto original_result = original(original_pBuffer.data, nBufferSize);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
			}
		}

		SUBCASE("Simulated lag")
		{
			initialize_clients(D2NET_CONNECTION_LOCAL_SIMULATED_LAG);

			// The compression info enqueued by CLIENT_Initialize is held back
			D2NetReceiveBufferStrc moo_pBuffer{};
			D2NetReceiveBufferStrc original_pBuffer{};

			const auto moo_result = sut(moo_pBuffer.data, MAX_MSG_SIZE);
			const auto original_result = original(original_pBuffer.data, MAX_MSG_SIZE);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC01320")
	{
		// NOTE: The receive thread is started by CLIENT_GetConnectionStatus once connected to a server, so it is tested through a whole remote session.
		SUBCASE("")
		{
			D2NetLocalGameServer server;
			if (!server.is_listening())
			{
				MESSAGE("Cannot listen on the game port, skipping");
				return;
			}

			// Call both implementations
			const auto input = make_remote_session_input();
			auto moo_session = run_remote_session(make_moo_client_functions(), server, input);
			auto original_session = run_remote_session(make_original_client_functions(dll_base), server, input);

			// Compare the packets received from the server
			MOO_CHECK_EQ(moo_session.game_packets, original_session.game_packets, "Comparing game packets");
			MOO_CHECK_EQ(moo_session.system_packets, original_session.system_packets, "Comparing system packets");

			// Compare Fog calls (decompression)
			MOO_CHECK_EQ(moo_session.fog_calls, original_session.fog_calls, "Comparing Fog calls");

			// Check specific values
			CHECK_EQ(moo_session.game_packets.size() + moo_session.system_packets.size(), input.uncompressed_packet_count + 1 + input.compressed_packet_count);
		}
	}

	TEST_CASE_FIXTURE(LocalClientFixture, "D2Net.0x6FC015C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_ParseReceiveBuffer, dll_base + 0x000015C0);

		REPEAT_10();

		initialize_clients(D2NET_CONNECTION_LOCAL);
		clear_client_queues();
		REQUIRE(moo_receive_buffer != nullptr);
		REQUIRE(original_receive_buffer != nullptr);

		// Structured bindings can't be captured by lambdas in C++17
		const auto moo_parse_receive_buffer = sut;
		const auto original_parse_receive_buffer = original;
		const auto run = [&](const std::vector<uint8_t>& stream, uint32_t dwTickBefore = 0)
		{
			*moo_receive_buffer = make_receive_buffer(stream);
			*original_receive_buffer = make_receive_buffer(stream);
			take_fog_calls();

			// Call both implementations
			const auto moo_result = moo_parse_receive_buffer();
			auto moo_fog_calls = take_fog_calls();
			const auto original_result = original_parse_receive_buffer();
			auto original_fog_calls = take_fog_calls();
			const uint32_t dwTickAfter = GetTickCount();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified data
			MOO_CHECK_EQ(moo_receive_buffer, original_receive_buffer, "Comparing gpReceiveBuffer");

			// Compare Fog calls
			MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");

			// Compare the packets that were enqueued
			auto moo_game_packets = drain_moo_game_packets();
			auto original_game_packets = drain_original_game_packets();

			// Packet 0x8F gets the tick count at which it was received
			for (auto* pPackets : { &moo_game_packets, &original_game_packets })
			{
				for (auto& packet : *pPackets)
				{
					if (!packet.data.empty() && packet.data[0] == 0x8F && packet.data.size() >= 17)
					{
						uint32_t dwReceiveTick = 0;
						std::memcpy(&dwReceiveTick, &packet.data[13], sizeof(dwReceiveTick));
						CHECK_GE(dwReceiveTick, dwTickBefore);
						CHECK_LE(dwReceiveTick, dwTickAfter);
						std::memset(&packet.data[13], 0, sizeof(dwReceiveTick));
					}
				}
			}

			MOO_CHECK_EQ(moo_game_packets, original_game_packets, "Comparing game packets");

			auto moo_system_packets = drain_moo_system_packets();
			auto original_system_packets = drain_original_system_packets();
			MOO_CHECK_EQ(moo_system_packets, original_system_packets, "Comparing system packets");
		};

		SUBCASE("Complete packets")
		{
			run(make_server_packet_stream(random_unsigned_integer(1, 10), true, true, sizeof(D2NetReceiveBufferStrc::data)));
		}

		SUBCASE("Incomplete packet")
		{
			auto stream = make_server_packet_stream(random_unsigned_integer(0, 5), true, true, sizeof(D2NetReceiveBufferStrc::data) - MAX_MSG_SIZE);

			// Only the beginning of a packet was received
			std::vector<uint8_t> packet;
			do
			{
				packet.clear();
				append_server_packet(packet, fixed_size_server_packet_headers()[random_unsigned_integer(0, static_cast<uint32_t>(fixed_size_server_packet_headers().size() - 1))]);
			} while (packet.size() < 2);
			stream.insert(stream.end(), packet.begin(), packet.begin() + random_unsigned_integer(1, static_cast<uint32_t>(packet.size() - 1)));

			run(stream);
		}

		SUBCASE("Empty buffer")
		{
			run({});
		}

		SUBCASE("Compression info")
		{
			for (const uint8_t nCompressionInfo : std::initializer_list<uint8_t>{ 0x00, 0x01, 0x05, 0x81 })
			{
				auto stream = make_server_packet_stream(random_unsigned_integer(0, 3), true, true, 512);

				// 0x81 also sends the compression table to Fog
				stream.push_back(SERVER_PACKET_HEADER_COMPRESSION_INFO);
				stream.push_back(nCompressionInfo);
				for (int32_t i = 2; i < (nCompressionInfo ? nCompressionInfo + 1 : 2); ++i)
				{
					stream.push_back(static_cast<uint8_t>(random_unsigned_integer(0, 255)));
				}

				const auto packets_after = make_server_packet_stream(random_unsigned_integer(0, 3), true, true, 512);
				stream.insert(stream.end(), packets_after.begin(), packets_after.end());

				run(stream);
			}
		}

		SUBCASE("Packet 0x8F")
		{
			auto stream = make_server_packet_stream(random_unsigned_integer(0, 3), true, true, 512);
			append_server_packet(stream, 0x8F);

			run(stream, GetTickCount());
		}
	}

	TEST_CASE_FIXTURE(LocalClientFixture, "D2Net.0x6FC01760 (#10005)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_Send, dll_base + 0x00001760);

		REPEAT_10();

		// Input data
		std::vector<uint8_t> data;
		for (uint32_t i = 0, nSize = random_unsigned_integer(1, MAX_MSG_SIZE); i < nSize; ++i)
		{
			data.push_back(static_cast<uint8_t>(random_unsigned_integer(0, 255)));
		}
		const auto nUnused = static_cast<int32_t>(random_unsigned_integer());

		// Structured bindings can't be captured by lambdas in C++17
		const auto moo_send = sut;
		const auto original_send = original;
		const auto run = [&]()
		{
			D2NetFogMock::return_value = static_cast<int32_t>(random_unsigned_integer(0, 1));
			take_fog_calls();

			// Call both implementations
			const auto moo_result = moo_send(nUnused, data.data(), static_cast<int32_t>(data.size()));
			auto moo_fog_calls = take_fog_calls();
			const auto original_result = original_send(nUnused, data.data(), static_cast<int32_t>(data.size()));
			auto original_fog_calls = take_fog_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare Fog calls
			MOO_CHECK_EQ(moo_fog_calls, original_fog_calls, "Comparing Fog calls");
		};

		SUBCASE("Client not initialized")
		{
			run();
		}

		SUBCASE("Local connection")
		{
			// The packets are given to the local server
			initialize_clients(D2NET_CONNECTION_LOCAL);
			run();
		}

		SUBCASE("Remote connection, not connected")
		{
			initialize_clients(D2NET_CONNECTION_LOCAL);
			set_connection_mode(D2NET_CONNECTION_REMOTE);
			run();
		}

		SUBCASE("Remote connection, connected")
		{
			D2NetLocalGameServer server;
			if (!server.is_listening())
			{
				MESSAGE("Cannot listen on the game port, skipping");
				return;
			}

			// Call both implementations
			auto input = make_remote_session_input();
			input.client_data = data;
			const auto moo_session = run_remote_session(make_moo_client_functions(), server, input);
			const auto original_session = run_remote_session(make_original_client_functions(dll_base), server, input);

			// Compare return values
			MOO_CHECK_EQ(moo_session.send_result, original_session.send_result, "Comparing results");

			// Compare the data received by the server
			CHECK(moo_session.received_by_server == original_session.received_by_server);
			CHECK(moo_session.received_by_server == data);
		}
	}

	TEST_CASE_FIXTURE(LocalClientFixture, "D2Net.0x6FC01810")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_EnqueuePacketsFromLocalServer, dll_base + 0x00001810);

		REPEAT_10();

		initialize_clients(D2NET_CONNECTION_LOCAL);
		clear_client_queues();

		// Structured bindings can't be captured by lambdas in C++17
		const auto moo_enqueue = sut;
		const auto original_enqueue = original;
		const auto run = [&](const std::vector<uint8_t>& stream, int32_t nBufferSize)
		{
			D2NetReceiveBufferStrc moo_pBuffer = make_receive_buffer(stream);
			D2NetReceiveBufferStrc original_pBuffer = make_receive_buffer(stream);

			// Call both implementations
			moo_enqueue(&moo_pBuffer, nBufferSize);
			original_enqueue(&original_pBuffer, nBufferSize);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");

			// Compare the packets that were enqueued
			auto moo_game_packets = drain_moo_game_packets();
			auto original_game_packets = drain_original_game_packets();
			MOO_CHECK_EQ(moo_game_packets, original_game_packets, "Comparing game packets");

			auto moo_system_packets = drain_moo_system_packets();
			auto original_system_packets = drain_original_system_packets();
			MOO_CHECK_EQ(moo_system_packets, original_system_packets, "Comparing system packets");
		};

		SUBCASE("Complete packets")
		{
			const auto stream = make_server_packet_stream(random_unsigned_integer(1, 10), true, true, sizeof(D2NetReceiveBufferStrc::data));
			run(stream, static_cast<int32_t>(stream.size()));
		}

		SUBCASE("Truncated buffer size")
		{
			const auto stream = make_server_packet_stream(random_unsigned_integer(1, 10), true, true, sizeof(D2NetReceiveBufferStrc::data));
			run(stream, static_cast<int32_t>(random_unsigned_integer(0, static_cast<uint32_t>(stream.size()))));
		}

		SUBCASE("Packet of unknown size")
		{
			auto stream = make_server_packet_stream(random_unsigned_integer(0, 5), true, true, sizeof(D2NetReceiveBufferStrc::data) - 1);
			// Packet 0x17 has no size, which stops the parsing
			stream.push_back(0x17);
			run(stream, static_cast<int32_t>(stream.size()));
		}
	}

	TEST_CASE_FIXTURE(LocalClientFixture, "D2Net.0x6FC019A0 (#10013)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_GetLocalIpAddressString, dll_base + 0x000019A0);

		SUBCASE("Not connected")
		{
			char moo_szBuffer[32]{};
			char original_szBuffer[32]{};

			// Call both implementations
			sut(moo_szBuffer);
			original(original_szBuffer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_szBuffer, original_szBuffer, "Comparing szBuffer");
		}

		SUBCASE("Connected")
		{
			D2NetLocalGameServer server;
			if (!server.is_listening())
			{
				MESSAGE("Cannot listen on the game port, skipping");
				return;
			}

			// Call both implementations
			const auto input = make_remote_session_input();
			auto moo_session = run_remote_session(make_moo_client_functions(), server, input);
			auto original_session = run_remote_session(make_original_client_functions(dll_base), server, input);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_session.local_ip_address, original_session.local_ip_address, "Comparing szBuffer");
			CHECK_EQ(std::strcmp(moo_session.local_ip_address, "127.0.0.1"), 0);
		}
	}
}

#endif
