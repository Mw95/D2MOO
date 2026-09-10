#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Skills.h>
#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <PLAYER/PlrMsg.h>
#include <Units/Units.h>


TEST_SUITE("PlrMsgTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81C00, dll_base + 0x00051C00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pUnit, pClient };
			};
			
			// Input data
			auto [moo_pUnit, moo_pClient] = setup_data();
			auto [original_pUnit, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pUnit, &moo_pClient);
			original(&original_pUnit, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81CA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81CA0, dll_base + 0x00051CA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pUnit, pClient };
			};
			
			// Input data
			auto [moo_pUnit, moo_pClient] = setup_data();
			auto [original_pUnit, original_pClient] = setup_data();
			char a3{};

			// Call both implementations
			sut(&moo_pUnit, &moo_pClient, a3);
			original(&original_pUnit, &original_pClient, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81D20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81D20, dll_base + 0x00051D20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pUnit, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pClient] = setup_data();
			auto [original_pGame, original_pUnit, original_pClient] = setup_data();
			int32_t nAnimMode{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pClient, nAnimMode);
			original(&original_pGame, &original_pUnit, &original_pClient, nAnimMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81E10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81E10, dll_base + 0x00051E10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pUnit, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pClient] = setup_data();
			auto [original_pGame, original_pUnit, original_pClient] = setup_data();
			int32_t nAnimMode{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pClient, nAnimMode);
			original(&original_pGame, &original_pUnit, &original_pClient, nAnimMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81F60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81F60, dll_base + 0x00051F60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pUnit, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pClient] = setup_data();
			auto [original_pGame, original_pUnit, original_pClient] = setup_data();
			int32_t nAnimMode{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pClient, nAnimMode);
			original(&original_pGame, &original_pUnit, &original_pClient, nAnimMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC82010" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC82010, dll_base + 0x00052010);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pUnit, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pClient] = setup_data();
			auto [original_pGame, original_pUnit, original_pClient] = setup_data();
			int32_t nAnimMode{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pClient, nAnimMode);
			original(&original_pGame, &original_pUnit, &original_pClient, nAnimMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC820C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC820C0, dll_base + 0x000520C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pUnit, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pClient] = setup_data();
			auto [original_pGame, original_pUnit, original_pClient] = setup_data();
			int32_t nAnimMode{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pClient, nAnimMode);
			original(&original_pGame, &original_pUnit, &original_pClient, nAnimMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC821C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC821C0, dll_base + 0x000521C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pUnit, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pClient] = setup_data();
			auto [original_pGame, original_pUnit, original_pClient] = setup_data();
			int32_t nAnimMode{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pClient, nAnimMode);
			original(&original_pGame, &original_pUnit, &original_pClient, nAnimMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC82270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC82270, dll_base + 0x00052270);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pUnit, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pClient] = setup_data();
			auto [original_pGame, original_pUnit, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pClient);
			original(&original_pGame, &original_pUnit, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC822D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_UpdateAttribute_6FC822D0, dll_base + 0x000522D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pUnit, pPlayer };
			};
			
			// Input data
			auto [moo_pUnit, moo_pPlayer] = setup_data();
			auto [original_pUnit, original_pPlayer] = setup_data();
			WORD nStat{};
			uint32_t nNewValue{};

			// Call both implementations
			sut(&moo_pUnit, nStat, nNewValue, &moo_pPlayer);
			original(&original_pUnit, nStat, nNewValue, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC82360" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC82360, dll_base + 0x00052360);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitStrc pUnit2{};
				
				return std::tuple{ pUnit, pUnit2 };
			};
			
			// Input data
			auto [moo_pUnit, moo_pUnit2] = setup_data();
			auto [original_pUnit, original_pUnit2] = setup_data();
			int32_t bSkipHpCheck{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pUnit2, bSkipHpCheck);
			const auto original_result = original(&original_pUnit, &original_pUnit2, bSkipHpCheck);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC82830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC82830, dll_base + 0x00052830);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pUnit, pClient };
			};
			
			// Input data
			auto [moo_pUnit, moo_pClient] = setup_data();
			auto [original_pUnit, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pUnit, &moo_pClient);
			original(&original_pUnit, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC828D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC828D0, dll_base + 0x000528D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer{};
				D2GameStrc pGame{};
				
				return std::tuple{ pPlayer, pGame };
			};
			
			// Input data
			auto [moo_pPlayer, moo_pGame] = setup_data();
			auto [original_pPlayer, original_pGame] = setup_data();
			int32_t nUnitType{};
			int32_t nUnitGUID{};
			int32_t a4{};

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, nUnitType, nUnitGUID, a4, &moo_pGame);
			const auto original_result = original(&original_pPlayer, nUnitType, nUnitGUID, a4, &original_pGame);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC82CB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x01_Walk_6FC82CB0, dll_base + 0x00052CB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC82D10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC82D10, dll_base + 0x00052D10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				uint16_t pX{};
				uint16_t pY{};
				
				return std::tuple{ pGame, pUnit, pX, pY };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pX, moo_pY] = setup_data();
			auto [original_pGame, original_pUnit, original_pX, original_pY] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nPacketSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nPacketSize, &moo_pX, &moo_pY);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nPacketSize, &original_pX, &original_pY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC82ED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x02_WalkToEntity_6FC82ED0, dll_base + 0x00052ED0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x03_Run_6FC83090, dll_base + 0x00053090);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC830F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x04_RunToEntity_6FC830F0, dll_base + 0x000530F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC832B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x05_ShiftLeftClickSkill_6FC832B0, dll_base + 0x000532B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC83340, dll_base + 0x00053340);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2SkillStrc pSkill{};
				
				return std::tuple{ pGame, pUnit, pSkill };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pSkill] = setup_data();
			auto [original_pGame, original_pUnit, original_pSkill] = setup_data();
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pSkill, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pSkill, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC83450, dll_base + 0x00053450);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2SkillStrc pSkill{};
				
				return std::tuple{ pUnit, pSkill };
			};
			
			// Input data
			auto [moo_pUnit, moo_pSkill] = setup_data();
			auto [original_pUnit, original_pSkill] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
			const auto original_result = original(&original_pUnit, &original_pSkill);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x06_LeftSkillOnUnit_6FC83550, dll_base + 0x00053550);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC836D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC836D0, dll_base + 0x000536D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2SkillStrc pSkill{};
				
				return std::tuple{ pGame, pUnit, pSkill };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pSkill] = setup_data();
			auto [original_pGame, original_pUnit, original_pSkill] = setup_data();
			int32_t nUnitType{};
			int32_t nUnitGUID{};
			int32_t a6{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pSkill, nUnitType, nUnitGUID, a6);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pSkill, nUnitType, nUnitGUID, a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x07_ShiftLeftSkillOnUnit_6FC83890, dll_base + 0x00053890);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83A10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x08_ShiftLeftSkillHold_6FC83A10, dll_base + 0x00053A10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83AC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x09_LeftSkillOnUnitHold_6FC83AC0, dll_base + 0x00053AC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83C60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC83C60, dll_base + 0x00053C60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();
			uint16_t nX{};
			uint16_t nY{};
			int32_t nMaxDistance{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nX, nY, nMaxDistance);
			const auto original_result = original(&original_pUnit, nX, nY, nMaxDistance);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83D00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC83D00, dll_base + 0x00053D00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitStrc a2{};
				
				return std::tuple{ pUnit, a2 };
			};
			
			// Input data
			auto [moo_pUnit, moo_a2] = setup_data();
			auto [original_pUnit, original_a2] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_a2);
			const auto original_result = original(&original_pUnit, &original_a2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83D40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x0A_ShiftLeftSkillOnUnitHold_6FC83D40, dll_base + 0x00053D40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83EE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x0B_6FC83EE0, dll_base + 0x00053EE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83EF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x0C_RightSkill_6FC83EF0, dll_base + 0x00053EF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC83F80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x0D_RightSkillOnUnit_6FC83F80, dll_base + 0x00053F80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84100" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x0E_ShiftRightSkillOnUnit_6FC84100, dll_base + 0x00054100);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84280" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x0F_RightSkillHold_6FC84280, dll_base + 0x00054280);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84330" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x10_RightSkillOnUnitHold_6FC84330, dll_base + 0x00054330);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC844D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x11_ShiftRightSkillOnUnitHold_6FC844D0, dll_base + 0x000544D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84670" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x12_6FC84670, dll_base + 0x00054670);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x14_HandleOverheadChat_6FC84690, dll_base + 0x00054690);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC847B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_HandlePlayerMessage_6FC847B0, dll_base + 0x000547B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ClientStrc pClient{};
				
				return std::tuple{ pClient };
			};
			
			// Input data
			auto [moo_pClient] = setup_data();
			auto [original_pClient] = setup_data();
			void* moo_pArgs = nullptr;
			void* original_pArgs = nullptr;

			// Call both implementations
			sut(&moo_pClient, moo_pArgs);
			original(&original_pClient, original_pArgs);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pArgs, original_pArgs, "Comparing pArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC848A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETS_HandleWhisper_6FC848A0, dll_base + 0x000548A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ClientStrc pClient{};
				
				return std::tuple{ pClient };
			};
			
			// Input data
			auto [moo_pClient] = setup_data();
			auto [original_pClient] = setup_data();
			void* moo_pArgs = nullptr;
			void* original_pArgs = nullptr;

			// Call both implementations
			sut(&moo_pClient, moo_pArgs);
			original(&original_pClient, original_pArgs);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pArgs, original_pArgs, "Comparing pArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(j_D2GAME_PACKETS_SendPacket0x26_ServerMessage_6FC3DDF0, dll_base + 0x00054940);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ClientStrc pClient{};
				
				return std::tuple{ pClient };
			};
			
			// Input data
			auto [moo_pClient] = setup_data();
			auto [original_pClient] = setup_data();
			void* moo_pMsg = nullptr;
			void* original_pMsg = nullptr;

			// Call both implementations
			sut(&moo_pClient, moo_pMsg);
			original(&original_pClient, original_pMsg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84950" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x15_HandleChatMessage_6FC84950, dll_base + 0x00054950);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84C70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC84C70, dll_base + 0x00054C70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();
			char szMessage{};
			uint8_t nColor{};

			// Call both implementations
			sut(&moo_pGame, &szMessage, nColor);
			original(&original_pGame, &szMessage, nColor);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84CD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC84CD0, dll_base + 0x00054CD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();
			char szMessage{};
			uint8_t nColor{};

			// Call both implementations
			sut(&moo_pGame, &szMessage, nColor);
			original(&original_pGame, &szMessage, nColor);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84D30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(j_D2GAME_SendPacket0x5A_6FC3DEC0, dll_base + 0x00054D30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ClientStrc pClient{};
				
				return std::tuple{ pClient };
			};
			
			// Input data
			auto [moo_pClient] = setup_data();
			auto [original_pClient] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;

			// Call both implementations
			sut(&moo_pClient, moo_pPacket);
			original(&original_pClient, original_pPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84D40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC84D40, dll_base + 0x00054D40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2GSPacketSrv5A pPacket5A{};
				
				return std::tuple{ pGame, pPacket5A };
			};
			
			// Input data
			auto [moo_pGame, moo_pPacket5A] = setup_data();
			auto [original_pGame, original_pPacket5A] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPacket5A);
			original(&original_pGame, &original_pPacket5A);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPacket5A, original_pPacket5A, "Comparing pPacket5A");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84D70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x13_InteractWithEntity_6FC84D70, dll_base + 0x00054D70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84DB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x16_PickItemOnGround_6FC84DB0, dll_base + 0x00054DB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x17_DropItemOnGround_6FC84E20, dll_base + 0x00054E20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC84ED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x18_InsertItemInBuffer_6FC84ED0, dll_base + 0x00054ED0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC850C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x19_RemoveItemFromBuffer_6FC850C0, dll_base + 0x000550C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC85280" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x1A_EquipItem_6FC85280, dll_base + 0x00055280);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC853C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x1B_Swap2HandedItem_6FC853C0, dll_base + 0x000553C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC854B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x1C_RemoveBodyItem_6FC854B0, dll_base + 0x000554B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC85550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x1D_SwapCursorItemWithBody_6FC85550, dll_base + 0x00055550);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC85690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x1E_SwapTwo1HandedWithOne2HandedItem_6FC85690, dll_base + 0x00055690);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC857C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x1F_SwapCursorBufferItems_6FC857C0, dll_base + 0x000557C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC85990" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x20_UseGridItem_6FC85990, dll_base + 0x00055990);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC85B50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x27_UseItemAction_6FC85B50, dll_base + 0x00055B50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC85C80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x21_StackItems_6FC85C80, dll_base + 0x00055C80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC85DA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x22_UnstackItems_6FC85DA0, dll_base + 0x00055DA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC85E70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x23_ItemToBelt_6FC85E70, dll_base + 0x00055E70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC85F50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x24_ItemFromBelt_6FC85F50, dll_base + 0x00055F50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86040" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x25_SwitchBeltItem_6FC86040, dll_base + 0x00056040);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86150" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x26_UseBeltItem_6FC86150, dll_base + 0x00056150);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86310" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x28_SocketItem_6FC86310, dll_base + 0x00056310);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x29_ScrollToBook_6FC86450, dll_base + 0x00056450);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC86520, dll_base + 0x00056520);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pGame, pPlayer };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer] = setup_data();
			auto [original_pGame, original_pPlayer] = setup_data();
			int32_t nItemGUID{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, nItemGUID);
			const auto original_result = original(&original_pGame, &original_pPlayer, nItemGUID);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC866E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x2A_ItemToCubeIndirect_6FC866E0, dll_base + 0x000566E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC867B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x2C_2D_52_6FC867B0, dll_base + 0x000567B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC867C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PlayerChangeAct_6FC867C0, dll_base + 0x000567C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			DWORD dwDestLvl{};
			DWORD nTileCalc{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, dwDestLvl, nTileCalc);
			original(&original_pGame, &original_pUnit, dwDestLvl, nTileCalc);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC868C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x2F_InitEntityChat_6FC868C0, dll_base + 0x000568C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC869F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x30_TerminateEntityChat_6FC869F0, dll_base + 0x000569F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86AB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x31_QuestMessage_6FC86AB0, dll_base + 0x00056AB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86AE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x32_BuyItemFromNpcBuffer_6FC86AE0, dll_base + 0x00056AE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86B30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x33_SellItemToNpcBuffer_6FC86B30, dll_base + 0x00056B30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86B70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x35_Repair_6FC86B70, dll_base + 0x00056B70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x34_IdentifyItemsWithNpc_6FC86BA0, dll_base + 0x00056BA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86BD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x36_HireMerc_6FC86BD0, dll_base + 0x00056BD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x62_ResurrectMerc_6FC86C00, dll_base + 0x00056C00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86C30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x37_IdentifyFromGamble_6FC86C30, dll_base + 0x00056C30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86CB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x38_EntityAction_6FC86CB0, dll_base + 0x00056CB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86E50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x39_PurchaseLife_6FC86E50, dll_base + 0x00056E50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86E80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x3A_AddStatPoint_6FC86E80, dll_base + 0x00056E80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC86EF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x3B_AddSkillPoint_6FC86EF0, dll_base + 0x00056EF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x3C_SelectSkill_6FC87050, dll_base + 0x00057050);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC870F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x3D_HighlightADoor_6FC870F0, dll_base + 0x000570F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x3E_ActivateInifussScroll_6FC87270, dll_base + 0x00057270);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x3F_PlayAudio_6FC87410, dll_base + 0x00057410);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87460" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x40_RequestQuestData_6FC87460, dll_base + 0x00057460);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87480" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x41_Resurrect_6FC87480, dll_base + 0x00057480);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC876B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x5D_SquelchHostile_6FC876B0, dll_base + 0x000576B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87720" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x5E_InviteToParty_6FC87720, dll_base + 0x00057720);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87780" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x44_StaffInOrifice_6FC87780, dll_base + 0x00057780);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x45_ChangeTpLocation_6FC87930, dll_base + 0x00057930);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87B00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x46_MercInteract_6FC87B00, dll_base + 0x00057B00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87CE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x47_MoveMerc_6FC87CE0, dll_base + 0x00057CE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x48_TurnOffBusyState_6FC87E20, dll_base + 0x00057E20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC87E60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x49_TakeOrCloseWp_6FC87E60, dll_base + 0x00057E60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nPacketSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nPacketSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nPacketSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC880A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x4D_PlayNpcMessage_6FC880A0, dll_base + 0x000580A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC880F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x4B_RequestEntityUpdate_6FC880F0, dll_base + 0x000580F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC88170" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x4C_Transmogrify_6FC88170, dll_base + 0x00058170);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC881D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x4F_ClickButton_6FC881D0, dll_base + 0x000581D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC88210" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x50_DropGold_6FC88210, dll_base + 0x00058210);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC88290" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x51_BindHotkeyToSkill_6FC88290, dll_base + 0x00058290);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC88340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x53_TurnStaminaOn_6FC88340, dll_base + 0x00058340);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC88380" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x54_TurnStaminaOff_6FC88380, dll_base + 0x00058380);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC883B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x58_QuestCompleted_6FC883B0, dll_base + 0x000583B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC88400" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x59_MakeEntityMove_6FC88400, dll_base + 0x00058400);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC88530" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x5F_UpdatePlayerPos_6FC88530, dll_base + 0x00058530);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC888A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x60_SwapWeapons_6FC888A0, dll_base + 0x000588A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC88930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x61_DropPickupMercItem_6FC88930, dll_base + 0x00058930);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC88D10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MERCS_EquipItem_6FC88D10, dll_base + 0x00058D10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pMerc{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pGame, pPlayer, pMerc, pItem };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pMerc, moo_pItem] = setup_data();
			auto [original_pGame, original_pPlayer, original_pMerc, original_pItem] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pMerc, &moo_pItem);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pMerc, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pMerc, original_pMerc, "Comparing pMerc");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC88F80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x63_ShiftLeftClickItemToBelt_6FC88F80, dll_base + 0x00058F80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC89310" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKETCALLBACK_Rcv0x2E_42_43_64_65_6FC89310, dll_base + 0x00059310);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC89320" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PACKET_Handler_6FC89320, dll_base + 0x00059320);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pPacket = nullptr;
			void* original_pPacket = nullptr;
			int32_t nSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pPacket, nSize);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pPacket, nSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC89450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PLRMSG_Last_6FC89450, dll_base + 0x00059450);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pDefender{};
				
				return std::tuple{ pGame, pAttacker, pDefender };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pDefender] = setup_data();
			auto [original_pGame, original_pAttacker, original_pDefender] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pAttacker, &moo_pDefender);
			original(&original_pGame, &original_pAttacker, &original_pDefender);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
}
