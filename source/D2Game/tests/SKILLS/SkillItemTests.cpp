#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <SKILLS/SkillItem.h>
#include <Units/Units.h>


TEST_SUITE("SkillItemTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD02BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell01_Initializer, dll_base + 0x000D2BA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD02BF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell01_IdentifyItem, dll_base + 0x000D2BF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD02C80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell02_CastPortal, dll_base + 0x000D2C80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD02E10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell03_Potion, dll_base + 0x000D2E10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD032D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell04_Unused, dll_base + 0x000D32D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD03610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell05_RejuvPotion, dll_base + 0x000D3610);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD039A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell09_StaminaPotion, dll_base + 0x000D39A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD03BB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell09_AntidoteThawingPotion, dll_base + 0x000D3BB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD03C80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell08_ExperienceElixir, dll_base + 0x000D3C80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD03CD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell07_OpenCube, dll_base + 0x000D3CD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD03D80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell10_CastFireBallOnTarget, dll_base + 0x000D3D80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD03DF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell11_CastFireBallToCoordinates, dll_base + 0x000D3DF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD03E40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_pSpell_Handler, dll_base + 0x000D3E40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pTarget] = setup_data();
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pTarget, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pTarget, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD040B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo113_Scroll_Book, dll_base + 0x000D40B0);
		
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
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD04270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_ActivateAura, dll_base + 0x000D4270);
		
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
			int32_t a5{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a5, nSkillId, nSkillLevel);
			original(&original_pGame, &original_pUnit, a5, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD04340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_DeactivateAura, dll_base + 0x000D4340);
		
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
			int32_t a4{};
			int32_t nSkillId{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a4, nSkillId);
			original(&original_pGame, &original_pUnit, a4, nSkillId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD043F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc06_AttackerTakesDamage, dll_base + 0x000D43F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD044B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc10_AttackerTakesLightDamage, dll_base + 0x000D44B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD04570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc11_ApplyFireDamage, dll_base + 0x000D4570);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD04630" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc12_ApplyColdDamage, dll_base + 0x000D4630);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD04720" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc07_Knockback, dll_base + 0x000D4720);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD04820" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc08_Howl, dll_base + 0x000D4820);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD048B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc09_Stupidity, dll_base + 0x000D48B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD049D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc13_DamageToMana, dll_base + 0x000D49D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD04B10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc14_Freeze, dll_base + 0x000D4B10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD04C40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_CalculateOpenWoundsHpRegen, dll_base + 0x000D4C40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nLevel{};
			int32_t pValues{};

			// Call both implementations
			const auto moo_result = sut(nLevel, &pValues);
			const auto original_result = original(nLevel, &pValues);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD04CF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc15_OpenWounds, dll_base + 0x000D4CF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD04E50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc16_CrushingBlow, dll_base + 0x000D4E50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD050D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc17_ManaAfterKill, dll_base + 0x000D50D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD05160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc28_HealAfterKill, dll_base + 0x000D5160);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD051E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc18_HealAfterDemonKill, dll_base + 0x000D51E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD05270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc19_Slow, dll_base + 0x000D5270);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD053D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc20_SkillOnAttackHitKill, dll_base + 0x000D53D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD05520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc21_SkillOnGetHit, dll_base + 0x000D5520);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD05640" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc30_SkillOnDeathLevelup, dll_base + 0x000D5640);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD05750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc29_RestInPeace, dll_base + 0x000D5750);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD05780" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_TimerCallback_ReanimateMonster, dll_base + 0x000D5780);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pSource{};
				D2UnitStrc pTarget{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pSource, pTarget, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pSource, moo_pTarget, moo_pDamage] = setup_data();
			auto [original_pGame, original_pSource, original_pTarget, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nMonId{};
			int32_t nOwnerId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pSource, &moo_pTarget, &moo_pDamage, nMonId, nOwnerId);
			const auto original_result = original(&original_pGame, nEvent, &original_pSource, &original_pTarget, &original_pDamage, nMonId, nOwnerId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pSource, original_pSource, "Comparing pSource");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD05B60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_EventFunc31_Reanimate, dll_base + 0x000D5B60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pUnit, original_pDamage] = setup_data();
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD05C20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_FindTargetPosition, dll_base + 0x000D5C20);
		
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
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD05D70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_HandleItemEffectSkill, dll_base + 0x000D5D70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pTargetUnit{};
				int32_t pUnitType{};
				int32_t pUnitGUID{};
				int32_t pX{};
				int32_t pY{};
				
				return std::tuple{ pGame, pUnit, pTargetUnit, pUnitType, pUnitGUID, pX, pY };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pTargetUnit, moo_pUnitType, moo_pUnitGUID, moo_pX, moo_pY] = setup_data();
			auto [original_pGame, original_pUnit, original_pTargetUnit, original_pUnitType, original_pUnitGUID, original_pX, original_pY] = setup_data();
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nX{};
			int32_t nY{};
			int32_t a7{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel, &moo_pTargetUnit, nX, nY, &moo_pUnitType, &moo_pUnitGUID, &moo_pX, &moo_pY, a7);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel, &original_pTargetUnit, nX, nY, &original_pUnitType, &original_pUnitGUID, &original_pX, &original_pY, a7);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
			SKIP_MOO_CHECK_EQ(moo_pUnitType, original_pUnitType, "Comparing pUnitType");
			SKIP_MOO_CHECK_EQ(moo_pUnitGUID, original_pUnitGUID, "Comparing pUnitGUID");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD06020" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_CastSkillOnTarget, dll_base + 0x000D6020);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitStrc pTargetUnit{};
				
				return std::tuple{ pUnit, pTargetUnit };
			};
			
			// Input data
			auto [moo_pUnit, moo_pTargetUnit] = setup_data();
			auto [original_pUnit, original_pTargetUnit] = setup_data();
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t a5{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nSkillId, nSkillLevel, &moo_pTargetUnit, a5);
			const auto original_result = original(&original_pUnit, nSkillId, nSkillLevel, &original_pTargetUnit, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD060F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLITEM_CastSkillOnPosition, dll_base + 0x000D60F0);
		
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
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nX{};
			int32_t nY{};
			int32_t a0{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nSkillId, nSkillLevel, nX, nY, a0);
			const auto original_result = original(&original_pUnit, nSkillId, nSkillLevel, nX, nY, a0);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
