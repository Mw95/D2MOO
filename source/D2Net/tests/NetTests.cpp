#include <D2NetTestDefines.h>

#ifdef NET_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <vector>

#include <EqualityMacros.h>
#include <RepetitionMacros.h>
#include <TestUtilities.h>
#include <D2Net/PacketVisitorDefinitions.h>
#include <Fixtures/D2Net/D2NetFogMockFixture.h>

#include <D2NetTestHelpers.h>

#include <D2Net.h>
#include <Packet.h>


extern int32_t gnConnectionMode;


// Random packets used as the content of the packet lists
static std::vector<D2NetQueuedPacketStrc> make_random_packets(size_t nCount, uint32_t dwReceiveTick)
{
	std::vector<D2NetQueuedPacketStrc> packets(nCount);
	for (auto& packet : packets)
	{
		for (auto& byte : packet.data)
		{
			byte = static_cast<uint8_t>(random_unsigned_integer(0, 255));
		}
		packet.nPacketSize = random_unsigned_integer(1, MAX_MSG_SIZE);
		packet.dwReceiveTick = dwReceiveTick;
		packet.pNext = nullptr;
	}
	return packets;
}

// Builds a linked list from the given packets. The list is allocated through Fog, since D2Net frees the packets it dequeues.
static D2NetQueuedPacketStrc* make_packet_list(const std::vector<D2NetQueuedPacketStrc>& packets)
{
	D2NetQueuedPacketStrc* pList = nullptr;
	D2NetQueuedPacketStrc** ppLast = &pList;
	for (const auto& packet : packets)
	{
		auto pPacket = static_cast<D2NetQueuedPacketStrc*>(FOG_Alloc(sizeof(D2NetQueuedPacketStrc), __FILE__, __LINE__, 0));
		*pPacket = packet;
		pPacket->pNext = nullptr;

		*ppLast = pPacket;
		ppLast = &pPacket->pNext;
	}
	return pList;
}

static void free_packet_list(D2NetQueuedPacketStrc* pList)
{
	while (pList)
	{
		D2NetQueuedPacketStrc* pNext = pList->pNext;
		FOG_Free(pList, __FILE__, __LINE__, 0);
		pList = pNext;
	}
}


TEST_SUITE("NetTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Net.dll").string().c_str()));


	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC01A00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(NET_IsLocalConnection, dll_base + 0x00001A00);

		SUBCASE("")
		{
			for (const int32_t nConnectionMode : { 0, 1, 2, 3, -1, static_cast<int32_t>(random_unsigned_integer()) })
			{
				// Input data
				set_connection_mode(nConnectionMode);

				// Call both implementations
				const auto moo_result = sut();
				const auto original_result = original();

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC01A20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(NET_SetConnectionMode, dll_base + 0x00001A20);
		const auto [moo_is_local_connection, original_is_local_connection] = make_function_pair(NET_IsLocalConnection, dll_base + 0x00001A00);

		SUBCASE("")
		{
			for (const int32_t nConnectionMode : { 0, 1, 2, 3, 1, 0, 2 })
			{
				// Call both implementations
				sut(nConnectionMode);
				original(nConnectionMode);

				// Check specific values
				CHECK_EQ(gnConnectionMode, nConnectionMode);

				// The connection mode of the original is not accessible, compare its observable effect
				const auto moo_result = moo_is_local_connection();
				const auto original_result = original_is_local_connection();
				MOO_CHECK_EQ(moo_result, original_result, "Comparing NET_IsLocalConnection results");
			}
		}
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC01A30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(NET_DequeueFirstPacketFromList, dll_base + 0x00001A30);

		REPEAT_10();

		CRITICAL_SECTION moo_pCriticalSection{};
		CRITICAL_SECTION original_pCriticalSection{};
		InitializeCriticalSection(&moo_pCriticalSection);
		InitializeCriticalSection(&original_pCriticalSection);

		// Structured bindings can't be captured by lambdas in C++17
		const auto moo_dequeue_first_packet_from_list = sut;
		const auto original_dequeue_first_packet_from_list = original;
		const auto run = [&](int32_t nConnectionMode, const std::vector<D2NetQueuedPacketStrc>& packets)
		{
			set_connection_mode(nConnectionMode);

			// Input data
			const auto nBufferSize = random_unsigned_integer(0, sizeof(D2NetReceiveBufferStrc::data));

			D2NetQueuedPacketStrc* moo_pPacketList = make_packet_list(packets);
			D2NetQueuedPacketStrc* original_pPacketList = make_packet_list(packets);
			D2NetReceiveBufferStrc moo_pBuffer{};
			D2NetReceiveBufferStrc original_pBuffer{};

			// Call both implementations, until the list is empty
			for (size_t i = 0; i <= packets.size(); ++i)
			{
				const auto moo_result = moo_dequeue_first_packet_from_list(&moo_pCriticalSection, &moo_pPacketList, moo_pBuffer.data, nBufferSize);
				const auto original_result = original_dequeue_first_packet_from_list(&original_pCriticalSection, &original_pPacketList, original_pBuffer.data, nBufferSize);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
				MOO_CHECK_EQ(moo_pPacketList, original_pPacketList, "Comparing ppPacketList");
			}

			free_packet_list(moo_pPacketList);
			free_packet_list(original_pPacketList);
		};

		SUBCASE("Empty list")
		{
			for (const int32_t nConnectionMode : { D2NET_CONNECTION_REMOTE, D2NET_CONNECTION_LOCAL, D2NET_CONNECTION_LOCAL_SIMULATED_LAG })
			{
				run(nConnectionMode, {});
			}
		}

		SUBCASE("Without simulated lag")
		{
			for (const int32_t nConnectionMode : { D2NET_CONNECTION_REMOTE, D2NET_CONNECTION_LOCAL })
			{
				run(nConnectionMode, make_random_packets(random_unsigned_integer(1, 5), GetTickCount()));
			}
		}

		SUBCASE("Simulated lag, packets are old enough")
		{
			run(D2NET_CONNECTION_LOCAL_SIMULATED_LAG, make_random_packets(random_unsigned_integer(1, 5), GetTickCount() - 10 * SIMULATED_LAG_MS));
		}

		SUBCASE("Simulated lag, packets are held back")
		{
			// Packets that were just received are held back for SIMULATED_LAG_MS
			run(D2NET_CONNECTION_LOCAL_SIMULATED_LAG, make_random_packets(random_unsigned_integer(1, 5), GetTickCount()));
		}

		DeleteCriticalSection(&moo_pCriticalSection);
		DeleteCriticalSection(&original_pCriticalSection);
	}

	TEST_CASE_FIXTURE(D2NetFogMockFixture<NoopFixture>, "D2Net.0x6FC01AE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(NET_FreePacketList, dll_base + 0x00001AE0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto packets = make_random_packets(random_unsigned_integer(0, 5), GetTickCount());

			CRITICAL_SECTION moo_pCriticalSection{};
			CRITICAL_SECTION original_pCriticalSection{};
			InitializeCriticalSection(&moo_pCriticalSection);
			InitializeCriticalSection(&original_pCriticalSection);

			const auto nInitialAllocationCount = D2NetFogMock::live_allocation_count();
			D2NetQueuedPacketStrc* moo_pPacketList = make_packet_list(packets);
			D2NetQueuedPacketStrc* original_pPacketList = make_packet_list(packets);

			// Call both implementations
			const auto moo_result = sut(&moo_pCriticalSection, &moo_pPacketList);
			const auto original_result = original(&original_pCriticalSection, &original_pPacketList);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPacketList, original_pPacketList, "Comparing ppPacketList");

			// Check specific values
			CHECK(moo_pPacketList == nullptr);
			// All packets of both lists were freed
			CHECK_EQ(D2NetFogMock::live_allocation_count(), nInitialAllocationCount);

			DeleteCriticalSection(&moo_pCriticalSection);
			DeleteCriticalSection(&original_pCriticalSection);
		}
	}
}

#endif
