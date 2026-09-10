#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <UNIT/SUnitNpc.h>
#include <UNIT/SUnitProxy.h>
#include <Units/Units.h>


TEST_SUITE("SUnitProxyTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCB8A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_GetNpcRecordFromClassId, dll_base + 0x0009B8A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				int32_t pIndex{};
				
				return std::tuple{ pGame, pIndex };
			};
			
			// Input data
			auto [moo_pGame, moo_pIndex] = setup_data();
			auto [original_pGame, original_pIndex] = setup_data();
			int32_t nNpcClassId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nNpcClassId, &moo_pIndex);
			const auto original_result = original(&original_pGame, nNpcClassId, &original_pIndex);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pIndex, original_pIndex, "Comparing pIndex");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCB910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_GetNpcRecordFromUnit, dll_base + 0x0009B910);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pNpc{};
				int32_t pIndex{};
				
				return std::tuple{ pGame, pNpc, pIndex };
			};
			
			// Input data
			auto [moo_pGame, moo_pNpc, moo_pIndex] = setup_data();
			auto [original_pGame, original_pNpc, original_pIndex] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pNpc, &moo_pIndex);
			const auto original_result = original(&original_pGame, &original_pNpc, &original_pIndex);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pIndex, original_pIndex, "Comparing pIndex");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCB980" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_AllocNpcEvent, dll_base + 0x0009B980);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pNpc{};
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pNpc, pGame, pPlayer };
			};
			
			// Input data
			auto [moo_pNpc, moo_pGame, moo_pPlayer] = setup_data();
			auto [original_pNpc, original_pGame, original_pPlayer] = setup_data();
			int32_t a4{};

			// Call both implementations
			sut(&moo_pNpc, &moo_pGame, &moo_pPlayer, a4);
			original(&original_pNpc, &original_pGame, &original_pPlayer, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCBA30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_InitializeNpcControl, dll_base + 0x0009BA30);
		
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

			// Call both implementations
			sut(&moo_pGame);
			original(&original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCBF50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_InitializeItemCache, dll_base + 0x0009BF50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitProxyStrc pUnitProxy{};
				
				return std::tuple{ pGame, pUnitProxy };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnitProxy] = setup_data();
			auto [original_pGame, original_pUnitProxy] = setup_data();
			void* moo_pUnused = nullptr;
			void* original_pUnused = nullptr;
			int32_t nNpcInventoryId{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnitProxy, moo_pUnused, nNpcInventoryId);
			original(&original_pGame, &original_pUnitProxy, original_pUnused, nNpcInventoryId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnitProxy, original_pUnitProxy, "Comparing pUnitProxy");
			SKIP_MOO_CHECK_EQ(moo_pUnused, original_pUnused, "Comparing pUnused");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCC030" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_FreeNpcControl, dll_base + 0x0009C030);
		
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

			// Call both implementations
			sut(&moo_pGame);
			original(&original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCC140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_ClearNpcRecordData, dll_base + 0x0009C140);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2NpcRecordStrc pNpcRecord{};
				
				return std::tuple{ pGame, pNpcRecord };
			};
			
			// Input data
			auto [moo_pGame, moo_pNpcRecord] = setup_data();
			auto [original_pGame, original_pNpcRecord] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pNpcRecord);
			original(&original_pGame, &original_pNpcRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pNpcRecord, original_pNpcRecord, "Comparing pNpcRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCC2E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_UpdateNpcsOnActChange, dll_base + 0x0009C2E0);
		
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
			int32_t nCurrentLevelId{};
			int32_t nDestLevelId{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nCurrentLevelId, nDestLevelId);
			original(&original_pGame, &original_pUnit, nCurrentLevelId, nDestLevelId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCC540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_UpdateVendorInventory, dll_base + 0x0009C540);
		
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
			uint8_t nAct{};
			int32_t bNoMorePlayersInLevel{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nAct, bNoMorePlayersInLevel);
			original(&original_pGame, &original_pUnit, nAct, bNoMorePlayersInLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCC690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_CountPlayersInLevel, dll_base + 0x0009C690);
		
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
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, moo_pArg);
			original(&original_pGame, &original_pUnit, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCC6B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_OnClientRemovedFromGame, dll_base + 0x0009C6B0);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCC7C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_InitializeNpcEventChain, dll_base + 0x0009C7C0);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCC860" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_GetNpcInventory, dll_base + 0x0009C860);
		
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
			int32_t nNpc{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nNpc);
			const auto original_result = original(&original_pGame, nNpc);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCC8B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_GetSeedFromNpcControl, dll_base + 0x0009C8B0);
		
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

			// Call both implementations
			const auto moo_result = sut(&moo_pGame);
			const auto original_result = original(&original_pGame);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCC8C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_FreeVendorChain, dll_base + 0x0009C8C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pNpc{};
				
				return std::tuple{ pGame, pPlayer, pNpc };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pNpc] = setup_data();
			auto [original_pGame, original_pPlayer, original_pNpc] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pNpc);
			original(&original_pGame, &original_pPlayer, &original_pNpc);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCCA70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_UpdateGambleInventory, dll_base + 0x0009CA70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pNpc{};
				D2UnitStrc pPlayer{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pNpc, pPlayer, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pNpc, moo_pPlayer, moo_pClient] = setup_data();
			auto [original_pGame, original_pNpc, original_pPlayer, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pNpc, &moo_pPlayer, &moo_pClient);
			original(&original_pGame, &original_pNpc, &original_pPlayer, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCCB20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_GetGambleInventory, dll_base + 0x0009CB20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pNpc{};
				
				return std::tuple{ pGame, pPlayer, pNpc };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pNpc] = setup_data();
			auto [original_pGame, original_pPlayer, original_pNpc] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pNpc);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pNpc);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCCBB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_GetVendorChain, dll_base + 0x0009CBB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2NpcRecordStrc pNpcRecord{};
				D2UnitStrc pNpc{};
				
				return std::tuple{ pGame, pNpcRecord, pNpc };
			};
			
			// Input data
			auto [moo_pGame, moo_pNpcRecord, moo_pNpc] = setup_data();
			auto [original_pGame, original_pNpcRecord, original_pNpc] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pNpcRecord, &moo_pNpc);
			const auto original_result = original(&original_pGame, &original_pNpcRecord, &original_pNpc);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pNpcRecord, original_pNpcRecord, "Comparing pNpcRecord");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCCC00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_AllocNpcInventory, dll_base + 0x0009CC00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2NpcRecordStrc pNpcRecord{};
				D2UnitStrc pNPC{};
				
				return std::tuple{ pGame, pNpcRecord, pNPC };
			};
			
			// Input data
			auto [moo_pGame, moo_pNpcRecord, moo_pNPC] = setup_data();
			auto [original_pGame, original_pNpcRecord, original_pNPC] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pNpcRecord, &moo_pNPC);
			original(&original_pGame, &original_pNpcRecord, &original_pNPC);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pNpcRecord, original_pNpcRecord, "Comparing pNpcRecord");
			SKIP_MOO_CHECK_EQ(moo_pNPC, original_pNPC, "Comparing pNPC");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCCC40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_FillGlobalItemCache, dll_base + 0x0009CC40);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCCED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_FillIGlobaltemCacheRecordForNpc, dll_base + 0x0009CED0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nNpcId{};

			// Call both implementations
			sut(nNpcId);
			original(nNpcId);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCD120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_ClearGlobalItemCache, dll_base + 0x0009D120);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCD190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITPROXY_FreeNpcGamble, dll_base + 0x0009D190);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pNpc{};
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pGame, pNpc, pPlayer };
			};
			
			// Input data
			auto [moo_pGame, moo_pNpc, moo_pPlayer] = setup_data();
			auto [original_pGame, original_pNpc, original_pPlayer] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pNpc, &moo_pPlayer);
			original(&original_pGame, &original_pNpc, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
}
