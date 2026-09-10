#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Task.h>


TEST_SUITE("TaskTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC404E0 (#10039)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TASK_InitializeClock, dll_base + 0x000104E0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC40500 (#10040)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TASK_FreeAllQueueSlots, dll_base + 0x00010500);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC405B0 (#10041)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10041_TASK_Create, dll_base + 0x000105B0);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC407A0 (#10042)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10042, dll_base + 0x000107A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2TaskStrc pTask{};
				D2LinkStrc pPrevTaskBalanceLink{};
				
				return std::tuple{ pTask, pPrevTaskBalanceLink };
			};
			
			// Input data
			auto [moo_pTask, moo_pPrevTaskBalanceLink] = setup_data();
			auto [original_pTask, original_pPrevTaskBalanceLink] = setup_data();
			int nTaskType{};

			// Call both implementations
			const auto moo_result = sut(&moo_pTask, nTaskType, &moo_pPrevTaskBalanceLink);
			const auto original_result = original(&original_pTask, nTaskType, &original_pPrevTaskBalanceLink);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTask, original_pTask, "Comparing pTask");
			SKIP_MOO_CHECK_EQ(moo_pPrevTaskBalanceLink, original_pPrevTaskBalanceLink, "Comparing pPrevTaskBalanceLink");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC40930 (#10043)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10043, dll_base + 0x00010930);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				int32_t pOutBalanceTaskType{};
				
				return std::tuple{ pOutBalanceTaskType };
			};
			
			// Input data
			auto [moo_pOutBalanceTaskType] = setup_data();
			auto [original_pOutBalanceTaskType] = setup_data();
			int8_t a1{};

			// Call both implementations
			const auto moo_result = sut(a1, &moo_pOutBalanceTaskType);
			const auto original_result = original(a1, &original_pOutBalanceTaskType);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOutBalanceTaskType, original_pOutBalanceTaskType, "Comparing pOutBalanceTaskType");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC40A40 (#10044)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10044, dll_base + 0x00010A40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int8_t nTaskNumber{};

			// Call both implementations
			const auto moo_result = sut(nTaskNumber);
			const auto original_result = original(nTaskNumber);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC40B30 (#10045)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TASK_ProcessGame, dll_base + 0x00010B30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2TaskStrc ptTask{};
				
				return std::tuple{ ptTask };
			};
			
			// Input data
			auto [moo_ptTask] = setup_data();
			auto [original_ptTask] = setup_data();
			char nTaskNumber{};

			// Call both implementations
			sut(nTaskNumber, &moo_ptTask);
			original(nTaskNumber, &original_ptTask);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ptTask, original_ptTask, "Comparing ptTask");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC40E40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TASK_QueueIncrement, dll_base + 0x00010E40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2TaskStrc ptTaskQueue{};
				int32_t pTaskType{};
				
				return std::tuple{ ptTaskQueue, pTaskType };
			};
			
			// Input data
			auto [moo_ptTaskQueue, moo_pTaskType] = setup_data();
			auto [original_ptTaskQueue, original_pTaskType] = setup_data();
			int nTaskTypeIncrement{};

			// Call both implementations
			sut(&moo_ptTaskQueue, &moo_pTaskType, nTaskTypeIncrement);
			original(&original_ptTaskQueue, &original_pTaskType, nTaskTypeIncrement);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ptTaskQueue, original_ptTaskQueue, "Comparing ptTaskQueue");
			SKIP_MOO_CHECK_EQ(moo_pTaskType, original_pTaskType, "Comparing pTaskType");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC40ED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TASK_LinkList_Insert, dll_base + 0x00010ED0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2LinkStrc pPrev{};
				D2LinkStrc pLink{};
				
				return std::tuple{ pPrev, pLink };
			};
			
			// Input data
			auto [moo_pPrev, moo_pLink] = setup_data();
			auto [original_pPrev, original_pLink] = setup_data();

			// Call both implementations
			sut(&moo_pPrev, &moo_pLink);
			original(&original_pPrev, &original_pLink);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPrev, original_pPrev, "Comparing pPrev");
			SKIP_MOO_CHECK_EQ(moo_pLink, original_pLink, "Comparing pLink");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC40F20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TASK_LinkList_PushFront, dll_base + 0x00010F20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2LinkStrc pList{};
				D2LinkStrc pLink{};
				
				return std::tuple{ pList, pLink };
			};
			
			// Input data
			auto [moo_pList, moo_pLink] = setup_data();
			auto [original_pList, original_pLink] = setup_data();

			// Call both implementations
			sut(&moo_pList, &moo_pLink);
			original(&original_pList, &original_pLink);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
			SKIP_MOO_CHECK_EQ(moo_pLink, original_pLink, "Comparing pLink");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC40F70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TASK_LinkList_Remove, dll_base + 0x00010F70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2LinkStrc pLink{};
				
				return std::tuple{ pLink };
			};
			
			// Input data
			auto [moo_pLink] = setup_data();
			auto [original_pLink] = setup_data();

			// Call both implementations
			sut(&moo_pLink);
			original(&original_pLink);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLink, original_pLink, "Comparing pLink");
		}
	}
}
