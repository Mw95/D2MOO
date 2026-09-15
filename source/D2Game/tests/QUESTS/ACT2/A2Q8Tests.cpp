#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <QUESTS/ACT2/A2Q8.h>
#include <Units/Units.h>


TEST_SUITE("A2Q8Tests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA66F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT2Q8_InitQuestData, dll_base + 0x000766F0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestDataStrc original_pQuestData{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData);
			setup_data(original_pQuestData);

			// Call both implementations
			sut(&moo_pQuestData);
			original(&original_pQuestData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA6770" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT2Q8_Callback11_ScrollMessage, dll_base + 0x00076770);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestArgStrc moo_pQuestArg{};
			D2QuestDataStrc original_pQuestData{};
			D2QuestArgStrc original_pQuestArg{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData,
				D2QuestArgStrc& pQuestArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData, moo_pQuestArg);
			setup_data(original_pQuestData, original_pQuestArg);

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA67B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT2Q8_Callback00_NpcActivate, dll_base + 0x000767B0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestArgStrc moo_pQuestArg{};
			D2QuestDataStrc original_pQuestData{};
			D2QuestArgStrc original_pQuestArg{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData,
				D2QuestArgStrc& pQuestArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData, moo_pQuestArg);
			setup_data(original_pQuestData, original_pQuestArg);

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA6850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT2Q8_ActiveFilterCallback, dll_base + 0x00076850);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuest{};
			D2UnitStrc moo_pPlayer{};
			D2BitBufferStrc moo_pQuestFlags{};
			D2UnitStrc moo_pNPC{};
			D2QuestDataStrc original_pQuest{};
			D2UnitStrc original_pPlayer{};
			D2BitBufferStrc original_pQuestFlags{};
			D2UnitStrc original_pNPC{};
			int32_t nNpcId{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuest,
				D2UnitStrc& pPlayer,
				D2BitBufferStrc& pQuestFlags,
				D2UnitStrc& pNPC
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuest, moo_pPlayer, moo_pQuestFlags, moo_pNPC);
			setup_data(original_pQuest, original_pPlayer, original_pQuestFlags, original_pNPC);

			// Call both implementations
			const auto moo_result = sut(&moo_pQuest, nNpcId, &moo_pPlayer, &moo_pQuestFlags, &moo_pNPC);
			const auto original_result = original(&original_pQuest, nNpcId, &original_pPlayer, &original_pQuestFlags, &original_pNPC);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuest, original_pQuest, "Comparing pQuest");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pQuestFlags, original_pQuestFlags, "Comparing pQuestFlags");
			SKIP_MOO_CHECK_EQ(moo_pNPC, original_pNPC, "Comparing pNPC");
		}
	}
}
