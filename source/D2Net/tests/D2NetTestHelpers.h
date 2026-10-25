#pragma once


#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <ostream>
#include <thread>
#include <vector>

#include <WinSock2.h>
#include <Windows.h>

#include <TestUtilities.h>
#include <Fixtures/D2Net/D2NetFogMockFixture.h>

#include <Client.h>
#include <D2Net.h>
#include <Packet.h>
#include <Server.h>


// A packet returned by CLIENT_DequeueGamePacket / CLIENT_DequeueSystemPacket
struct D2NetDequeuedPacket
{
	int32_t nSize;
	std::vector<uint8_t> data;

	bool operator==(const D2NetDequeuedPacket& other) const
	{
		return nSize == other.nSize && data == other.data;
	}

	bool operator!=(const D2NetDequeuedPacket& other) const
	{
		return !(*this == other);
	}
};

inline std::ostream& operator<<(std::ostream& stream, const D2NetDequeuedPacket& packet)
{
	stream << "size=" << packet.nSize << " data=[";
	for (size_t i = 0; i < packet.data.size(); ++i)
	{
		stream << (i ? " " : "") << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(packet.data[i]);
	}
	return stream << std::dec << std::setfill(' ') << ']';
}

inline std::ostream& operator<<(std::ostream& stream, const std::vector<D2NetDequeuedPacket>& packets)
{
	stream << '{';
	for (const auto& packet : packets)
	{
		stream << "\n\t" << packet;
	}
	return stream << (packets.empty() ? "}" : "\n}");
}


using D2NetDequeueFunction = int32_t(__stdcall*)(uint8_t* pBuffer, uint32_t nBufferSize);

// Dequeues packets until the queue is empty (or holds back its first packet)
inline std::vector<D2NetDequeuedPacket> drain_packets(D2NetDequeueFunction dequeue, size_t nMaxPackets = 256)
{
	std::vector<D2NetDequeuedPacket> packets;
	for (size_t i = 0; i < nMaxPackets; ++i)
	{
		D2NetReceiveBufferStrc buffer{};
		const int32_t nSize = dequeue(buffer.data, MAX_MSG_SIZE);
		if (nSize < 0)
		{
			break;
		}

		const auto nCopiedSize = std::min<uint32_t>(static_cast<uint32_t>(nSize), MAX_MSG_SIZE);
		packets.push_back({ nSize, std::vector<uint8_t>(buffer.data, buffer.data + nCopiedSize) });
	}
	return packets;
}


// Server packets whose size depends on their content
inline bool is_variable_size_server_packet(uint8_t nHeader)
{
	switch (nHeader)
	{
	case 0x16: case 0x26: case 0x3E: case 0x5B: case 0x94: case 0x9C: case 0x9D:
	case 0xA6: case 0xA8: case 0xAA: case 0xAC: case 0xAE: case 0xB2:
		return true;
	default:
		return false;
	}
}

// Valid server packets of fixed size, except 0x8F which gets patched with the current tick count by the client
inline const std::vector<uint8_t>& fixed_size_server_packet_headers()
{
	static const std::vector<uint8_t> headers = []()
	{
		std::vector<uint8_t> result;
		for (int32_t nHeader = 0; nHeader < SERVER_PACKET_HEADER_END; ++nHeader)
		{
			if (is_variable_size_server_packet(static_cast<uint8_t>(nHeader)) || nHeader == 0x8F)
			{
				continue;
			}

			D2NetReceiveBufferStrc buffer{};
			buffer.data[0] = static_cast<uint8_t>(nHeader);
			int32_t nSize = 0;
			if (SERVER_GetServerPacketSize(&buffer, sizeof(buffer.data), &nSize) > 0 && nSize > 0 && nSize <= static_cast<int32_t>(MAX_MSG_SIZE))
			{
				result.push_back(static_cast<uint8_t>(nHeader));
			}
		}
		return result;
	}();
	return headers;
}

inline int32_t server_packet_size(uint8_t nHeader)
{
	D2NetReceiveBufferStrc buffer{};
	buffer.data[0] = nHeader;
	int32_t nSize = 0;
	SERVER_GetServerPacketSize(&buffer, sizeof(buffer.data), &nSize);
	return nSize;
}

// Appends a server packet with the given header and random content
inline void append_server_packet(std::vector<uint8_t>& stream, uint8_t nHeader)
{
	const int32_t nSize = server_packet_size(nHeader);
	stream.push_back(nHeader);
	for (int32_t i = 1; i < nSize; ++i)
	{
		stream.push_back(static_cast<uint8_t>(random_unsigned_integer(0, 255)));
	}
}

// Builds a sequence of random fixed size server packets (game and/or system packets) that fits in nMaxSize bytes
inline std::vector<uint8_t> make_server_packet_stream(size_t nPacketCount, bool bGamePackets, bool bSystemPackets, size_t nMaxSize, size_t* pPacketCount = nullptr)
{
	std::vector<uint8_t> headers;
	for (const auto nHeader : fixed_size_server_packet_headers())
	{
		const bool bSystemPacket = nHeader >= SERVER_SYSTEM_PACKET_HEADER_MIN;
		if ((bSystemPacket && bSystemPackets) || (!bSystemPacket && bGamePackets))
		{
			headers.push_back(nHeader);
		}
	}

	std::vector<uint8_t> stream;
	size_t nAddedPackets = 0;
	for (size_t i = 0; i < nPacketCount && !headers.empty(); ++i)
	{
		const auto nHeader = headers[random_unsigned_integer(0, static_cast<uint32_t>(headers.size() - 1))];
		if (stream.size() + server_packet_size(nHeader) > nMaxSize)
		{
			continue;
		}

		append_server_packet(stream, nHeader);
		++nAddedPackets;
	}

	if (pPacketCount)
	{
		*pPacketCount = nAddedPackets;
	}
	return stream;
}

inline D2NetReceiveBufferStrc make_receive_buffer(const std::vector<uint8_t>& stream)
{
	D2NetReceiveBufferStrc buffer{};
	const auto nSize = std::min(stream.size(), sizeof(buffer.data));
	std::memcpy(buffer.data, stream.data(), nSize);
	buffer.nUsedBytes = static_cast<uint32_t>(nSize);
	return buffer;
}


// Initializes the client of both implementations in a local connection mode.
// Pointers to their receive buffers (gpReceiveBuffer) are retrieved from the Fog allocation mock.
// Should be used on top of D2NetFogMockFixture.
template<class Fixture>
struct D2NetLocalClientFixture : Fixture
{
	D2NetReceiveBufferStrc* moo_receive_buffer = nullptr;
	D2NetReceiveBufferStrc* original_receive_buffer = nullptr;
	int32_t moo_initialize_result = 0;
	int32_t original_initialize_result = 0;
	bool clients_initialized = false;

	~D2NetLocalClientFixture()
	{
		release_clients();
	}

	void initialize_clients(int32_t nConnectionMode = D2NET_CONNECTION_LOCAL)
	{
		const auto [moo_initialize, original_initialize] = make_function_pair(CLIENT_Initialize, this->d2net_base + 0x000011B0);

		moo_initialize_result = moo_initialize(nConnectionMode, "127.0.0.1");
		moo_receive_buffer = static_cast<D2NetReceiveBufferStrc*>(D2NetFogMock::last_live_allocation_of_size(sizeof(D2NetReceiveBufferStrc)));

		original_initialize_result = original_initialize(nConnectionMode, "127.0.0.1");
		original_receive_buffer = static_cast<D2NetReceiveBufferStrc*>(D2NetFogMock::last_live_allocation_of_size(sizeof(D2NetReceiveBufferStrc)));

		clients_initialized = true;
	}

	void release_clients()
	{
		if (!clients_initialized)
		{
			return;
		}

		const auto [moo_release, original_release] = make_function_pair(CLIENT_Release, this->d2net_base + 0x00001240);
		moo_release();
		original_release();

		clients_initialized = false;
		moo_receive_buffer = nullptr;
		original_receive_buffer = nullptr;
	}

	std::vector<D2NetDequeuedPacket> drain_moo_game_packets()
	{
		return drain_packets(&CLIENT_DequeueGamePacket);
	}

	std::vector<D2NetDequeuedPacket> drain_original_game_packets()
	{
		return drain_packets(reinterpret_cast<D2NetDequeueFunction>(this->d2net_base + 0x00001300));
	}

	std::vector<D2NetDequeuedPacket> drain_moo_system_packets()
	{
		return drain_packets(&CLIENT_DequeueSystemPacket);
	}

	std::vector<D2NetDequeuedPacket> drain_original_system_packets()
	{
		return drain_packets(reinterpret_cast<D2NetDequeueFunction>(this->d2net_base + 0x00001310));
	}

	// Removes the packets enqueued by CLIENT_Initialize
	void clear_client_queues()
	{
		drain_moo_game_packets();
		drain_original_game_packets();
		drain_moo_system_packets();
		drain_original_system_packets();
	}
};


// TCP server listening on 127.0.0.1:GAME_PORT, used to test the remote connection of the client
struct D2NetLocalGameServer
{
	SOCKET listen_socket = INVALID_SOCKET;
	bool wsa_started = false;

	D2NetLocalGameServer()
	{
		WSADATA wsaData{};
		wsa_started = WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
		if (!wsa_started)
		{
			return;
		}

		listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (listen_socket == INVALID_SOCKET)
		{
			return;
		}

		sockaddr_in address{};
		address.sin_family = AF_INET;
		address.sin_port = htons(GAME_PORT);
		address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

		if (bind(listen_socket, reinterpret_cast<sockaddr*>(&address), sizeof(address)) != 0 || listen(listen_socket, SOMAXCONN) != 0)
		{
			closesocket(listen_socket);
			listen_socket = INVALID_SOCKET;
		}
	}

	D2NetLocalGameServer(const D2NetLocalGameServer&) = delete;
	D2NetLocalGameServer& operator=(const D2NetLocalGameServer&) = delete;

	~D2NetLocalGameServer()
	{
		if (listen_socket != INVALID_SOCKET)
		{
			closesocket(listen_socket);
		}

		if (wsa_started)
		{
			WSACleanup();
		}
	}

	bool is_listening() const
	{
		return listen_socket != INVALID_SOCKET;
	}

	// Returns INVALID_SOCKET if no client connected in time
	SOCKET accept_client(uint32_t nTimeoutMs = 2000) const
	{
		if (!wait_readable(listen_socket, nTimeoutMs))
		{
			return INVALID_SOCKET;
		}

		return accept(listen_socket, nullptr, nullptr);
	}

	static bool wait_readable(SOCKET nSocket, uint32_t nTimeoutMs)
	{
		fd_set readfds{};
		FD_SET(nSocket, &readfds);

		timeval timeout{};
		timeout.tv_sec = static_cast<long>(nTimeoutMs / 1000);
		timeout.tv_usec = static_cast<long>((nTimeoutMs % 1000) * 1000);

		return select(0, &readfds, nullptr, nullptr, &timeout) > 0;
	}

	static bool send_all(SOCKET nSocket, const std::vector<uint8_t>& data)
	{
		size_t nSentBytes = 0;
		while (nSentBytes < data.size())
		{
			const int nResult = send(nSocket, reinterpret_cast<const char*>(data.data() + nSentBytes), static_cast<int>(data.size() - nSentBytes), 0);
			if (nResult <= 0)
			{
				return false;
			}
			nSentBytes += nResult;
		}
		return true;
	}

	static std::vector<uint8_t> receive(SOCKET nSocket, size_t nSize, uint32_t nTimeoutMs = 2000)
	{
		std::vector<uint8_t> data;
		while (data.size() < nSize && wait_readable(nSocket, nTimeoutMs))
		{
			uint8_t buffer[1024];
			const int nResult = recv(nSocket, reinterpret_cast<char*>(buffer), static_cast<int>(std::min(sizeof(buffer), nSize - data.size())), 0);
			if (nResult <= 0)
			{
				break;
			}
			data.insert(data.end(), buffer, buffer + nResult);
		}
		return data;
	}
};

// Polls both client queues until nExpectedPackets were dequeued in total, or the timeout expired
inline void poll_packets(D2NetDequeueFunction dequeue_game, D2NetDequeueFunction dequeue_system, std::vector<D2NetDequeuedPacket>& game_packets, std::vector<D2NetDequeuedPacket>& system_packets, size_t nExpectedPackets, uint32_t nTimeoutMs = 2000)
{
	const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(nTimeoutMs);
	while (game_packets.size() + system_packets.size() < nExpectedPackets && std::chrono::steady_clock::now() < deadline)
	{
		for (const auto& packet : drain_packets(dequeue_game))
		{
			game_packets.push_back(packet);
		}
		for (const auto& packet : drain_packets(dequeue_system))
		{
			system_packets.push_back(packet);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
