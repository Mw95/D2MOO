#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <GAME/SCmd.h>
#include <Units/Units.h>


TEST_SUITE("SCmdTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C640" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3C640, dll_base + 0x0000C640);
		
		SUBCASE("")
		{
			int32_t nClientId{};
			int16_t nGameId{};
			int16_t nClientCount{};
			char szGameName{};

			// Call both implementations
			auto moo_result = sut(nClientId, nGameId, nClientCount, &szGameName);
			auto original_result = original(nClientId, nGameId, nClientCount, &szGameName);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3C690, dll_base + 0x0000C690);
		
		SUBCASE("")
		{
			int32_t nClientId{};

			// Call both implementations
			sut(nClientId);
			original(nClientId);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C6B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3C6B0, dll_base + 0x0000C6B0);
		
		SUBCASE("")
		{
			int32_t nClientId{};

			// Call both implementations
			sut(nClientId);
			original(nClientId);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C6D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3C6D0, dll_base + 0x0000C6D0);
		
		SUBCASE("")
		{
			int32_t nClientId{};
			uint32_t nErrorCode{};

			// Call both implementations
			sut(nClientId, nErrorCode);
			original(nClientId, nErrorCode);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C6F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendHeaderOnlyPacket, dll_base + 0x0000C6F0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t nHeader{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader);
			original(&original_pClient, nHeader);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C710" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket_6FC3C710, dll_base + 0x0000C710);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nPacketSize{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, moo_pPacket, nPacketSize);
			original(&original_pClient, original_pPacket, nPacketSize);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C7C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x01_6FC3C7C0, dll_base + 0x0000C7C0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GameStrc moo_pGame{};
			D2ClientStrc original_pClient{};
			D2GameStrc original_pGame{};
			char nHeader{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pGame);
			setup_data(original_pClient, original_pGame);

			// Call both implementations
			sut(&moo_pClient, nHeader, &moo_pGame);
			original(&original_pClient, nHeader, &original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C810" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x03_6FC3C810, dll_base + 0x0000C810);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char nHeader{};
			char nAct{};
			int32_t nInitSeed{};
			int32_t nObjectSeed{};
			int16_t nTownId{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, nAct, nInitSeed, nObjectSeed, nTownId);
			original(&original_pClient, nHeader, nAct, nInitSeed, nObjectSeed, nTownId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacketSize06_6FC3C850, dll_base + 0x0000C850);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			DWORD nHeader{};
			DWORD dwUnitType{};
			DWORD dwUnitId{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, dwUnitType, dwUnitId);
			original(&original_pClient, nHeader, dwUnitType, dwUnitId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C880" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacketSize05_6FC3C880, dll_base + 0x0000C880);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char nHeader{};
			int32_t nArg{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, nArg);
			original(&original_pClient, nHeader, nArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C8A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x0C_6FC3C8A0, dll_base + 0x0000C8A0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char nHeader{};
			D2C_UnitTypes nUnitType{};
			int32_t nUnitGUID{};
			char a5{};
			char nHitClass{};
			char nLifePct{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, nUnitType, nUnitGUID, a5, nHitClass, nLifePct);
			original(&original_pClient, nHeader, nUnitType, nUnitGUID, a5, nHitClass, nLifePct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C8E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x0E_6FC3C8E0, dll_base + 0x0000C8E0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char nHeader{};
			char a3{};
			int32_t a4{};
			char a5{};
			char a6{};
			int32_t nAnimMode{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, a3, a4, a5, a6, nAnimMode);
			original(&original_pClient, nHeader, a3, a4, a5, a6, nAnimMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C920" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x0D_6FC3C920, dll_base + 0x0000C920);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char nPacketId{};
			int32_t nUnitType{};
			int32_t nUnitId{};
			char a5{};
			WORD nX{};
			WORD nY{};
			char a8{};
			char nLife{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nPacketId, nUnitType, nUnitId, a5, nX, nY, a8, nLife);
			original(&original_pClient, nPacketId, nUnitType, nUnitId, a5, nX, nY, a8, nLife);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C9A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x10_6FC3C9A0, dll_base + 0x0000C9A0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char nHeader{};
			char a3{};
			int32_t a4{};
			char a5{};
			char a6{};
			int32_t a7{};
			int16_t a8{};
			int16_t a9{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, a3, a4, a5, a6, a7, a8, a9);
			original(&original_pClient, nHeader, a3, a4, a5, a6, a7, a8, a9);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3CA00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x0F_6FC3CA00, dll_base + 0x0000CA00);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char nHeader{};
			uint8_t bTOU{};
			int32_t a4{};
			char a5{};
			int16_t a6{};
			int16_t a7{};
			char a8{};
			int16_t a9{};
			int16_t a10{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, bTOU, a4, a5, a6, a7, a8, a9, a10);
			original(&original_pClient, nHeader, bTOU, a4, a5, a6, a7, a8, a9, a10);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3CA90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x68_6FC3CA90, dll_base + 0x0000CA90);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t nHeader{};
			int32_t nUnitGUID{};
			int8_t a4{};
			int8_t a5{};
			int32_t a6{};
			int8_t a7{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, nUnitGUID, a4, a5, a6, a7);
			original(&original_pClient, nHeader, nUnitGUID, a4, a5, a6, a7);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3CBC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x67_6FC3CBC0, dll_base + 0x0000CBC0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t nHeader{};
			int32_t nUnitGUID{};
			int8_t a4{};
			int16_t nX{};
			int16_t nY{};
			int8_t a7{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, nUnitGUID, a4, nX, nY, a7);
			original(&original_pClient, nHeader, nUnitGUID, a4, nX, nY, a7);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3CCB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x68_6FC3CCB0, dll_base + 0x0000CCB0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t nHeader{};
			int32_t nUnitGUID{};
			int8_t a4{};
			int8_t a5{};
			int32_t a6{};
			int8_t a7{};
			int8_t a8{};
			int8_t a9{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, nUnitGUID, a4, a5, a6, a7, a8, a9);
			original(&original_pClient, nHeader, nUnitGUID, a4, a5, a6, a7, a8, a9);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3CDE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x67_6FC3CDE0, dll_base + 0x0000CDE0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t nHeader{};
			int32_t nUnitGUID{};
			int8_t a4{};
			int16_t nX{};
			int16_t nY{};
			int8_t a7{};
			int8_t a8{};
			int8_t a9{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, nUnitGUID, a4, nX, nY, a7, a8, a9);
			original(&original_pClient, nHeader, nUnitGUID, a4, nX, nY, a7, a8, a9);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3CEE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x6A_6FC3CEE0, dll_base + 0x0000CEE0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char a2{};
			int32_t nUnitGUID{};
			char a4{};
			char a5{};
			int32_t a6{};
			char nDirection{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, nUnitGUID, a4, a5, a6, nDirection);
			original(&original_pClient, a2, nUnitGUID, a4, a5, a6, nDirection);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3CF30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x69_6FC3CF30, dll_base + 0x0000CF30);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char a2{};
			int32_t a3{};
			char a4{};
			int16_t a5{};
			int16_t a6{};
			char a7{};
			char a8{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6, a7, a8);
			original(&original_pClient, a2, a3, a4, a5, a6, a7, a8);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3CF90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x6C_6FC3CF90, dll_base + 0x0000CF90);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char a2{};
			int32_t a3{};
			char a4{};
			char a5{};
			int32_t a6{};
			char a7{};
			int16_t a8{};
			int16_t a9{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6, a7, a8, a9);
			original(&original_pClient, a2, a3, a4, a5, a6, a7, a8, a9);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D000" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x6B_6FC3D000, dll_base + 0x0000D000);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char a2{};
			int32_t a3{};
			char a4{};
			int16_t a5{};
			int16_t a6{};
			char a7{};
			char a8{};
			int16_t a9{};
			int16_t a10{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6, a7, a8, a9, a10);
			original(&original_pClient, a2, a3, a4, a5, a6, a7, a8, a9, a10);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x6D_6FC3D080, dll_base + 0x0000D080);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			DWORD dwUnitId{};
			WORD nX{};
			WORD nY{};
			BYTE nUnitLife{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, dwUnitId, nX, nY, nUnitLife);
			original(&original_pClient, dwUnitId, nX, nY, nUnitLife);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D0D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x15_6FC3D0D0, dll_base + 0x0000D0D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char a2{};
			char a3{};
			int32_t a4{};
			int16_t a5{};
			int16_t a6{};
			char a7{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6, a7);
			original(&original_pClient, a2, a3, a4, a5, a6, a7);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x07_6FC3D120, dll_base + 0x0000D120);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t nAreaId{};
			uint16_t nTileX{};
			uint16_t nTileY{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nAreaId, nTileX, nTileY);
			original(&original_pClient, nAreaId, nTileX, nTileY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x08_6FC3D160, dll_base + 0x0000D160);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t nAreaId{};
			uint16_t nTileX{};
			uint16_t nTileY{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nAreaId, nTileX, nTileY);
			original(&original_pClient, nAreaId, nTileX, nTileY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D1A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x09_6FC3D1A0, dll_base + 0x0000D1A0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE a2{};
			BYTE a3{};
			DWORD a4{};
			BYTE a5{};
			WORD a6{};
			WORD a7{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6, a7);
			original(&original_pClient, a2, a3, a4, a5, a6, a7);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D1F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3D1F0, dll_base + 0x0000D1F0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t nUnitGUID{};
			uint8_t nClassId{};
			char szName{};
			int16_t nX{};
			int16_t nY{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nUnitGUID, nClassId, &szName, nX, nY);
			original(&original_pClient, nUnitGUID, nClassId, &szName, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D300" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x51_6FC3D300, dll_base + 0x0000D300);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char nHeader{};
			uint8_t nUnitType{};
			int32_t nUnitGUID{};
			int16_t nObjectId{};
			int16_t nX{};
			int16_t nY{};
			char a8{};
			char a9{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, nUnitType, nUnitGUID, nObjectId, nX, nY, a8, a9);
			original(&original_pClient, nHeader, nUnitType, nUnitGUID, nObjectId, nX, nY, a8, a9);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D3A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x0A_RemoveObject_6FC3D3A0, dll_base + 0x0000D3A0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char alw0x0A{};
			char nUnitType{};
			int32_t nUnitId{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, alw0x0A, nUnitType, nUnitId);
			original(&original_pClient, alw0x0A, nUnitType, nUnitId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D3D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x19_6FC3D3D0, dll_base + 0x0000D3D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t nValue{};
			int32_t a3{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nValue, a3);
			original(&original_pClient, nValue, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x1A_B_C_6FC3D410, dll_base + 0x0000D410);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t nExperience{};
			int32_t a3{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nExperience, a3);
			original(&original_pClient, nExperience, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D480" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x1D_E_F_6FC3D480, dll_base + 0x0000D480);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint16_t nStatId{};
			uint32_t nValue{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nStatId, nValue);
			original(&original_pClient, nStatId, nValue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x9E_9F_A0_6FC3D520, dll_base + 0x0000D520);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			uint16_t nStatId{};
			uint32_t nValue{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, nStatId, nValue);
			original(&original_pClient, &original_pUnit, nStatId, nValue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0xA0_A1_A2_6FC3D610, dll_base + 0x0000D610);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			uint16_t nStatId{};
			uint32_t nBaseValue{};
			uint32_t nFullValue{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, nStatId, nBaseValue, nFullValue);
			original(&original_pClient, &original_pUnit, nStatId, nBaseValue, nFullValue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D730" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0xA3_6FC3D730, dll_base + 0x0000D730);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE a2{};
			WORD a3{};
			WORD a4{};
			BYTE a5{};
			int32_t a6{};
			BYTE a7{};
			int32_t a8{};
			int32_t a9{};
			int32_t a10{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6, a7, a8, a9, a10);
			original(&original_pClient, a2, a3, a4, a5, a6, a7, a8, a9, a10);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D7B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0xAB_6FC3D7B0, dll_base + 0x0000D7B0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t nUnitType{};
			int32_t dwUnitId{};
			uint8_t nUnitLife{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nUnitType, dwUnitId, nUnitLife);
			original(&original_pClient, nUnitType, dwUnitId, nUnitLife);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D7F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0xA5_6FC3D7F0, dll_base + 0x0000D7F0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t a2{};
			int32_t a3{};
			uint16_t a4{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4);
			original(&original_pClient, a2, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3D830, dll_base + 0x0000D830);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE nHeader{};
			int32_t nUnitGUID{};
			WORD nStatId{};
			int32_t nValue{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, nUnitGUID, nStatId, nValue);
			original(&original_pClient, nHeader, nUnitGUID, nStatId, nValue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3D890, dll_base + 0x0000D890);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint16_t a2{};
			uint16_t a3{};
			uint16_t a4{};
			uint8_t a5{};
			uint8_t a6{};
			uint16_t a7{};
			uint16_t a8{};
			uint8_t a9{};
			uint8_t a10{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6, a7, a8, a9, a10);
			original(&original_pClient, a2, a3, a4, a5, a6, a7, a8, a9, a10);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3D9A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3D9A0, dll_base + 0x0000D9A0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint16_t a2{};
			uint16_t a3{};
			uint16_t a4{};
			uint16_t a5{};
			uint16_t a6{};
			uint8_t a7{};
			uint8_t a8{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6, a7, a8);
			original(&original_pClient, a2, a3, a4, a5, a6, a7, a8);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3DA90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x96_WalkVerify_6FC3DA90, dll_base + 0x0000DA90);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint16_t a2{};
			uint16_t a3{};
			uint16_t a4{};
			uint8_t a5{};
			uint8_t a6{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6);
			original(&original_pClient, a2, a3, a4, a5, a6);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3DB50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x21_UpdateSkills_6FC3DB50, dll_base + 0x0000DB50);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			WORD nSkillId{};
			BYTE nSkillLevel{};
			BYTE a4{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, nSkillId, nSkillLevel, a4);
			original(&original_pClient, &original_pUnit, nSkillId, nSkillLevel, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3DBE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x22_6FC3DBE0, dll_base + 0x0000DBE0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE nUnitType{};
			int32_t nUnitGUID{};
			int16_t nSkillId{};
			char a5{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nUnitType, nUnitGUID, nSkillId, a5);
			original(&original_pClient, nUnitType, nUnitGUID, nSkillId, a5);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3DC60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x23_6FC3DC60, dll_base + 0x0000DC60);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE nUnitType{};
			int32_t nUnitGUID{};
			BYTE a4{};
			WORD a5{};
			int32_t a6{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nUnitType, nUnitGUID, a4, a5, a6);
			original(&original_pClient, nUnitType, nUnitGUID, a4, a5, a6);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3DCA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3DCA0, dll_base + 0x0000DCA0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit);
			original(&original_pClient, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3DDF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x26_ServerMessage_6FC3DDF0, dll_base + 0x0000DDF0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv26 moo_pMsg{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv26 original_pMsg{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv26& pMsg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pMsg);
			setup_data(original_pClient, original_pMsg);

			// Call both implementations
			sut(&moo_pClient, &moo_pMsg);
			original(&original_pClient, &original_pMsg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3DEC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x5A_6FC3DEC0, dll_base + 0x0000DEC0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv5A moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv5A original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv5A& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3DF20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x27_6FC3DF20, dll_base + 0x0000DF20);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv27 moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv27 original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv27& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3DF50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x53_6FC3DF50, dll_base + 0x0000DF50);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv53 moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv53 original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv53& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3DF80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3DF80, dll_base + 0x0000DF80);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient1{};
			D2UnitStrc moo_pPlayer{};
			D2ClientStrc moo_pClient2{};
			D2ClientStrc original_pClient1{};
			D2UnitStrc original_pPlayer{};
			D2ClientStrc original_pClient2{};

			const auto setup_data = [](
				D2ClientStrc& pClient1,
				D2UnitStrc& pPlayer,
				D2ClientStrc& pClient2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient1, moo_pPlayer, moo_pClient2);
			setup_data(original_pClient1, original_pPlayer, original_pClient2);

			// Call both implementations
			sut(&moo_pClient1, &moo_pPlayer, &moo_pClient2);
			original(&original_pClient1, &original_pPlayer, &original_pClient2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient1, original_pClient1, "Comparing pClient1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pClient2, original_pClient2, "Comparing pClient2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x5C_6FC3E090, dll_base + 0x0000E090);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			DWORD dwUnitId{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, dwUnitId);
			original(&original_pClient, dwUnitId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E0B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x77_Ui_6FC3E0B0, dll_base + 0x0000E0B0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE nUiNo{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nUiNo);
			original(&original_pClient, nUiNo);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E0D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3E0D0, dll_base + 0x0000E0D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv78 moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv78 original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv78& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E100" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x7A_6FC3E100, dll_base + 0x0000E100);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char a2{};
			char a3{};
			int32_t a4{};
			int32_t a5{};
			int16_t a6{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6);
			original(&original_pClient, a2, a3, a4, a5, a6);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x81_6FC3E160, dll_base + 0x0000E160);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char a2{};
			int32_t a3{};
			int32_t a4{};
			int16_t a5{};
			int32_t a6{};
			int32_t a7{};
			int32_t a8{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6, a7, a8);
			original(&original_pClient, a2, a3, a4, a5, a6, a7, a8);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E1D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x79_6FC3E1D0, dll_base + 0x0000E1D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t a2{};
			char a3{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3);
			original(&original_pClient, a2, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E200" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3E200, dll_base + 0x0000E200);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit);
			original(&original_pClient, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E3D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3E3D0, dll_base + 0x0000E3D0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit);
			auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E3F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3E3F0, dll_base + 0x0000E3F0);
		
		SUBCASE("")
		{
			// Input data
			D2UnkMonsterDataStrc moo_a1{};
			D2UnkMonsterDataStrc original_a1{};
			int32_t nCurrentLifePercentage{};

			const auto setup_data = [](
				D2UnkMonsterDataStrc& a1
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_a1);
			setup_data(original_a1);

			// Call both implementations
			auto moo_result = sut(&moo_a1, nCurrentLifePercentage);
			auto original_result = original(&original_a1, nCurrentLifePercentage);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3E440, dll_base + 0x0000E440);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit2{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit1, &moo_pUnit2, a3, a4);
			auto original_result = original(&original_pUnit1, &original_pUnit2, a3, a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			SKIP_MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x9C_6FC3E570, dll_base + 0x0000E570);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pItem{};
			char nAction{};
			DWORD dwFlag{};
			int32_t bGamble{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pItem);
			setup_data(original_pClient, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pItem, nAction, dwFlag, bGamble);
			original(&original_pClient, &original_pItem, nAction, dwFlag, bGamble);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E6F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x9D_6FC3E6F0, dll_base + 0x0000E6F0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			char nAction{};
			DWORD dwFlag{};
			int32_t bGamble{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit, moo_pItem);
			setup_data(original_pClient, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, &moo_pItem, nAction, dwFlag, bGamble);
			original(&original_pClient, &original_pUnit, &original_pItem, nAction, dwFlag, bGamble);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_AddToGround_6FC3E850, dll_base + 0x0000E850);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pItem{};
			DWORD dwFlag{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pItem);
			setup_data(original_pClient, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pItem, dwFlag);
			original(&original_pClient, &original_pItem, dwFlag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E870" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_GroundToCursor_6FC3E870, dll_base + 0x0000E870);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			DWORD a4{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pItem);
			setup_data(original_pClient, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pItem, a4);
			original(&original_pClient, &original_pPlayer, &original_pItem, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E8E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_DropToGround_6FC3E8E0, dll_base + 0x0000E8E0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			DWORD a4{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pItem);
			setup_data(original_pClient, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pItem, a4);
			original(&original_pClient, &original_pPlayer, &original_pItem, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_OnGround_6FC3E930, dll_base + 0x0000E930);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			DWORD a4{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pItem);
			setup_data(original_pClient, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pItem, a4);
			original(&original_pClient, &original_pPlayer, &original_pItem, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E980" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_PutInContainer_6FC3E980, dll_base + 0x0000E980);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			DWORD a4{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pItem);
			setup_data(original_pClient, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pItem, a4);
			original(&original_pClient, &original_pPlayer, &original_pItem, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3E9D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_UpdateClientItem_6FC3E9D0, dll_base + 0x0000E9D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			DWORD dwCmdFlag{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pItem);
			setup_data(original_pClient, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pItem, dwCmdFlag);
			original(&original_pClient, &original_pPlayer, &original_pItem, dwCmdFlag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EA50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9D_ItemAction_Equip_6FC3EA50, dll_base + 0x0000EA50);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			DWORD dwFlags{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit, moo_pItem);
			setup_data(original_pClient, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, &moo_pItem, dwFlags);
			original(&original_pClient, &original_pUnit, &original_pItem, dwFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EA70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9D_ItemAction_IndirectlySwapBodyItem_6FC3EA70, dll_base + 0x0000EA70);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			DWORD dwFlags{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit, moo_pItem);
			setup_data(original_pClient, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, &moo_pItem, dwFlags);
			original(&original_pClient, &original_pUnit, &original_pItem, dwFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EA90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9D_ItemAction_Unequip_6FC3EA90, dll_base + 0x0000EA90);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			DWORD dwFlags{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit, moo_pItem);
			setup_data(original_pClient, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, &moo_pItem, dwFlags);
			original(&original_pClient, &original_pUnit, &original_pItem, dwFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EAB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9D_ItemAction_SwapBodyItem_6FC3EAB0, dll_base + 0x0000EAB0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			DWORD dwFlags{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit, moo_pItem);
			setup_data(original_pClient, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, &moo_pItem, dwFlags);
			original(&original_pClient, &original_pUnit, &original_pItem, dwFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EAD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9D_ItemAction_WeaponSwitch_6FC3EAD0, dll_base + 0x0000EAD0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			DWORD dwFlags{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit, moo_pItem);
			setup_data(original_pClient, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, &moo_pItem, dwFlags);
			original(&original_pClient, &original_pUnit, &original_pItem, dwFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EAF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_AddQuantity_6FC3EAF0, dll_base + 0x0000EAF0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			DWORD a4{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pItem);
			setup_data(original_pClient, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pItem, a4);
			original(&original_pClient, &original_pPlayer, &original_pItem, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EB40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_SwapInContainer_6FC3EB40, dll_base + 0x0000EB40);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			DWORD a4{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pItem);
			setup_data(original_pClient, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pItem, a4);
			original(&original_pClient, &original_pPlayer, &original_pItem, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EB90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_PutInBelt_6FC3EB90, dll_base + 0x0000EB90);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			DWORD a4{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pItem);
			setup_data(original_pClient, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pItem, a4);
			original(&original_pClient, &original_pPlayer, &original_pItem, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EBE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_RemoveFromBelt_6FC3EBE0, dll_base + 0x0000EBE0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			DWORD dwFlag{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit, moo_pItem);
			setup_data(original_pClient, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, &moo_pItem, dwFlag);
			original(&original_pClient, &original_pUnit, &original_pItem, dwFlag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EC00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_SwapInBelt_6FC3EC00, dll_base + 0x0000EC00);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			DWORD a3{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pItem);
			setup_data(original_pClient, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pItem, a3);
			original(&original_pClient, &original_pPlayer, &original_pItem, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EC20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x3E_6FC3EC20, dll_base + 0x0000EC20);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pItem{};
			uint8_t a3{};
			int32_t nStatId{};
			uint32_t nValue{};
			uint16_t a6{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pItem);
			setup_data(original_pClient, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pItem, a3, nStatId, nValue, a6);
			original(&original_pClient, &original_pItem, a3, nStatId, nValue, a6);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EDC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x3F_6FC3EDC0, dll_base + 0x0000EDC0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			char a3{};
			int32_t a4{};
			int32_t a5{};
			int16_t a6{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, a3, a4, a5, a6);
			original(&original_pClient, &original_pUnit, a3, a4, a5, a6);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EE20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9D_ItemAction_AutoUnequip_6FC3EE20, dll_base + 0x0000EE20);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			DWORD dwFlags{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit, moo_pItem);
			setup_data(original_pClient, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, &moo_pItem, dwFlags);
			original(&original_pClient, &original_pUnit, &original_pItem, dwFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EE40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x42_6FC3EE40, dll_base + 0x0000EE40);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit);
			original(&original_pClient, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EEA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_ToCursor_6FC3EEA0, dll_base + 0x0000EEA0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pItem);
			setup_data(original_pClient, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pItem);
			original(&original_pClient, &original_pPlayer, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EEC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9D_ItemAction_Unknown0x14_6FC3EEC0, dll_base + 0x0000EEC0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			DWORD dwFlags{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit, moo_pItem);
			setup_data(original_pClient, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, &moo_pItem, dwFlags);
			original(&original_pClient, &original_pUnit, &original_pItem, dwFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EEE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x47_6FC3EEE0, dll_base + 0x0000EEE0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit);
			original(&original_pClient, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EF40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x48_6FC3EF40, dll_base + 0x0000EF40);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			BYTE a3{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, a3);
			original(&original_pClient, &original_pUnit, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EFA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9D_ItemAction_UpdateStats_6FC3EFA0, dll_base + 0x0000EFA0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			DWORD dwFlags{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit, moo_pItem);
			setup_data(original_pClient, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, &moo_pItem, dwFlags);
			original(&original_pClient, &original_pUnit, &original_pItem, dwFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3EFC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3EFC0, dll_base + 0x0000EFC0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit2{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit2{};
			int32_t a4{};
			int32_t a5{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit1, moo_pUnit2);
			setup_data(original_pClient, original_pUnit1, original_pUnit2);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit1, &moo_pUnit2, a4, a5);
			original(&original_pClient, &original_pUnit1, &original_pUnit2, a4, a5);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			SKIP_MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F040" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9D_ItemAction_Unknown0x16_6FC3F040, dll_base + 0x0000F040);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			DWORD dwFlags{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit, moo_pItem);
			setup_data(original_pClient, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit, &moo_pItem, dwFlags);
			original(&original_pClient, &original_pUnit, &original_pItem, dwFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F060, dll_base + 0x0000F060);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t a2{};
			int32_t a3{};
			uint16_t a4{};
			uint16_t a5{};
			int32_t a6{};
			uint16_t a7{};
			uint8_t a8{};
			int32_t a9{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6, a7, a8, a9);
			original(&original_pClient, a2, a3, a4, a5, a6, a7, a8, a9);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F0C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F0C0, dll_base + 0x0000F0C0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t a2{};
			int32_t a3{};
			uint8_t nUnitType{};
			int32_t nUnitGUID{};
			uint16_t a6{};
			uint16_t a7{};
			uint8_t a8{};
			int32_t a9{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, nUnitType, nUnitGUID, a6, a7, a8, a9);
			original(&original_pClient, a2, a3, nUnitType, nUnitGUID, a6, a7, a8, a9);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendP0x9C_ItemAction_AddOrRemoveFromShop_6FC3F260, dll_base + 0x0000F260);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			char a3{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pItem);
			setup_data(original_pClient, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pItem, a3);
			original(&original_pClient, &original_pPlayer, &original_pItem, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F2F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x28_6FC3F2F0, dll_base + 0x0000F2F0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2BitBufferStrc moo_a5{};
			D2ClientStrc original_pClient{};
			D2BitBufferStrc original_a5{};
			BYTE nHeader{};
			BYTE a3{};
			int32_t a4{};
			BYTE a6{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2BitBufferStrc& a5
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_a5);
			setup_data(original_pClient, original_a5);

			// Call both implementations
			sut(&moo_pClient, nHeader, a3, a4, &moo_a5, a6);
			original(&original_pClient, nHeader, a3, a4, &original_a5, a6);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F340, dll_base + 0x0000F340);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE nHeader{};
			BYTE nUnitType{};
			int32_t nUnitId{};
			int32_t a5{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHeader, nUnitType, nUnitId, a5);
			original(&original_pClient, nHeader, nUnitType, nUnitId, a5);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F370" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x29_6FC3F370, dll_base + 0x0000F370);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv29 moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv29 original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv29& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F380" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F380, dll_base + 0x0000F380);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv5D moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv5D original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv5D& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F3B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x2A_6FC3F3B0, dll_base + 0x0000F3B0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			char a2{};
			char a3{};
			int32_t a4{};
			int32_t a5{};
			char a6{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6);
			original(&original_pClient, a2, a3, a4, a5, a6);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F3F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F3F0, dll_base + 0x0000F3F0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv2C moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv2C original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv2C& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x4E_6FC3F410, dll_base + 0x0000F410);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv4E moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv4E original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv4E& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x50_6FC3F440, dll_base + 0x0000F440);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv50 moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv50 original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv50& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F480" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F480, dll_base + 0x0000F480);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, moo_pPacket);
			original(&original_pClient, original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F490" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x52_6FC3F490, dll_base + 0x0000F490);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv52 moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv52 original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv52& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F4A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x11_6FC3F4A0, dll_base + 0x0000F4A0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE nUnitType{};
			DWORD dwUnitId{};
			WORD unk{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nUnitType, dwUnitId, unk);
			original(&original_pClient, nUnitType, dwUnitId, unk);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F4D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F4D0, dll_base + 0x0000F4D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t a2{};
			char a3{};
			int16_t a4{};
			int16_t a5{};
			int16_t a6{};
			int16_t a7{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3, a4, a5, a6, a7);
			original(&original_pClient, a2, a3, a4, a5, a6, a7);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x58_6FC3F520, dll_base + 0x0000F520);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv58 moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv58 original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv58& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F550, dll_base + 0x0000F550);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit);
			original(&original_pClient, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F590" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x61_6FC3F590, dll_base + 0x0000F590);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE unk{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, unk);
			original(&original_pClient, unk);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F5B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x63_WaypointMenu_6FC3F5B0, dll_base + 0x0000F5B0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv63 moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv63 original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv63& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F5E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x65_6FC3F5E0, dll_base + 0x0000F5E0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			DWORD dwPlayerId{};
			WORD nCount{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, dwPlayerId, nCount);
			original(&original_pClient, dwPlayerId, nCount);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F610, dll_base + 0x0000F610);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv73 moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv73 original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv73& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F640" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x74_6FC3F640, dll_base + 0x0000F640);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_a2{};
			D2UnitStrc moo_a3{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_a2{};
			D2UnitStrc original_a3{};
			BYTE bAssign{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& a2,
				D2UnitStrc& a3
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_a2, moo_a3);
			setup_data(original_pClient, original_a2, original_a3);

			// Call both implementations
			sut(&moo_pClient, &moo_a2, &moo_a3, bAssign);
			original(&original_pClient, &original_a2, &original_a3, bAssign);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCMD_Send0x75_PartyRosterUpdate, dll_base + 0x0000F690);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pLocalPlayer{};
			D2UnitStrc moo_pOtherPlayer{};
			D2UnitStrc original_pLocalPlayer{};
			D2UnitStrc original_pOtherPlayer{};

			const auto setup_data = [](
				D2UnitStrc& pLocalPlayer,
				D2UnitStrc& pOtherPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pLocalPlayer, moo_pOtherPlayer);
			setup_data(original_pLocalPlayer, original_pOtherPlayer);

			// Call both implementations
			sut(&moo_pLocalPlayer, &moo_pOtherPlayer);
			original(&original_pLocalPlayer, &original_pOtherPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLocalPlayer, original_pLocalPlayer, "Comparing pLocalPlayer");
			SKIP_MOO_CHECK_EQ(moo_pOtherPlayer, original_pOtherPlayer, "Comparing pOtherPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F720" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x7B_6FC3F720, dll_base + 0x0000F720);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE slot{};
			int16_t nSkill{};
			int32_t nHand{};
			int32_t nItemGUID{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, slot, nSkill, nHand, nItemGUID);
			original(&original_pClient, slot, nSkill, nHand, nItemGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F770" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x7E_6FC3F770, dll_base + 0x0000F770);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient);
			original(&original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F790" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x82_6FC3F790, dll_base + 0x0000F790);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};
			int32_t nPortalGUID{};
			int32_t nPortalOwnerGUID{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient);
			setup_data(original_pGame, original_pClient);

			// Call both implementations
			sut(&moo_pGame, &moo_pClient, nPortalGUID, nPortalOwnerGUID);
			original(&original_pGame, &original_pClient, nPortalGUID, nPortalOwnerGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F810" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x8B_6FC3F810, dll_base + 0x0000F810);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			DWORD dwUnitId{};
			BYTE bParty{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, dwUnitId, bParty);
			original(&original_pClient, dwUnitId, bParty);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F840, dll_base + 0x0000F840);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t dwPlayerId1{};
			int32_t dwPlayerId2{};
			int16_t wRelationState{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame, dwPlayerId1, dwPlayerId2, wRelationState);
			original(&original_pGame, dwPlayerId1, dwPlayerId2, wRelationState);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F880" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F880, dll_base + 0x0000F880);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			void* moo_packet = nullptr;
			void* original_packet = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, moo_packet);
			original(&original_pGame, &original_pPlayer, original_packet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_packet, original_packet, "Comparing packet");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F8B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x8C_6FC3F8B0, dll_base + 0x0000F8B0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			DWORD dwPlayerId1{};
			DWORD dwPlayerId2{};
			WORD wRelationState{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, dwPlayerId1, dwPlayerId2, wRelationState);
			original(&original_pUnit, dwPlayerId1, dwPlayerId2, wRelationState);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F8F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F8F0, dll_base + 0x0000F8F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer);
			original(&original_pGame, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F930, dll_base + 0x0000F930);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			void* moo_packet = nullptr;
			void* original_packet = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, moo_packet);
			original(&original_pGame, &original_pPlayer, original_packet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_packet, original_packet, "Comparing packet");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F960" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x8D_6FC3F960, dll_base + 0x0000F960);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_a2{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_a2{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& a2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_a2);
			setup_data(original_pUnit, original_a2);

			// Call both implementations
			sut(&moo_pUnit, &moo_a2);
			original(&original_pUnit, &original_a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F9B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x8E_CorpseAssign_ToAllPlayers_6FC3F9B0, dll_base + 0x0000F9B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nUnitId{};
			int32_t nCorpseId{};
			BYTE bAssign{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame, nUnitId, nCorpseId, bAssign);
			original(&original_pGame, nUnitId, nCorpseId, bAssign);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3F9F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3F9F0, dll_base + 0x0000F9F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, moo_pPacket);
			original(&original_pGame, &original_pPlayer, original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FA20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x8E_6FC3FA20, dll_base + 0x0000FA20);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t nUnitId{};
			int32_t nCorpseId{};
			BYTE bAssign{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nUnitId, nCorpseId, bAssign);
			original(&original_pClient, nUnitId, nCorpseId, bAssign);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FA50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3FA50, dll_base + 0x0000FA50);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			void* moo_a2 = nullptr;
			void* original_a2 = nullptr;

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, moo_a2);
			original(&original_pClient, original_a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FA60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SendPacket0x8A_6FC3FA60, dll_base + 0x0000FA60);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv8A moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv8A original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv8A& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FA90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x8F_6FC3FA90, dll_base + 0x0000FA90);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient);
			original(&original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FAC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3FAC0, dll_base + 0x0000FAC0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GSPacketSrv91 moo_pPacket{};
			D2ClientStrc original_pClient{};
			D2GSPacketSrv91 original_pPacket{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GSPacketSrv91& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacket);
			setup_data(original_pClient, original_pPacket);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacket);
			original(&original_pClient, &original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FAF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3FAF0, dll_base + 0x0000FAF0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint32_t a2{};
			uint16_t a3{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3);
			original(&original_pClient, a2, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FB30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x9B_6FC3FB30, dll_base + 0x0000FB30);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int16_t a2{};
			int32_t a3{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2, a3);
			original(&original_pClient, a2, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FB60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x97_6FC3FB60, dll_base + 0x0000FB60);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient);
			original(&original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FB80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0x16_UnitsUpdate, dll_base + 0x0000FB80);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient);
			original(&original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FC00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0xA4_6FC3FC00, dll_base + 0x0000FC00);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int16_t a2{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2);
			original(&original_pClient, a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FC20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0xA7_StateOn_6FC3FC20, dll_base + 0x0000FC20);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE nUnitType{};
			DWORD dwUnitId{};
			uint16_t nState{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nUnitType, dwUnitId, nState);
			original(&original_pClient, nUnitType, dwUnitId, nState);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FC50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_SendPacket0xA9_StateOff_6FC3FC50, dll_base + 0x0000FC50);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BYTE nUnitType{};
			DWORD dwUnitId{};
			uint16_t nState{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nUnitType, dwUnitId, nState);
			original(&original_pClient, nUnitType, dwUnitId, nState);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3FC80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3FC80, dll_base + 0x0000FC80);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit);
			original(&original_pClient, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
