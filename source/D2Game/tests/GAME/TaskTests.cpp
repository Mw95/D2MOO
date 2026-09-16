#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

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
			auto moo_result = sut();
			auto original_result = original();
			
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
			// Input data
			D2TaskStrc moo_pTask{};
			D2LinkStrc moo_pPrevTaskBalanceLink{};
			D2TaskStrc original_pTask{};
			D2LinkStrc original_pPrevTaskBalanceLink{};
			int nTaskType{};

			const auto setup_data = [](
				D2TaskStrc& pTask,
				D2LinkStrc& pPrevTaskBalanceLink
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTask, moo_pPrevTaskBalanceLink);
			setup_data(original_pTask, original_pPrevTaskBalanceLink);

			// Call both implementations
			auto moo_result = sut(&moo_pTask, nTaskType, &moo_pPrevTaskBalanceLink);
			auto original_result = original(&original_pTask, nTaskType, &original_pPrevTaskBalanceLink);
			
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
			// Input data
			int32_t moo_pOutBalanceTaskType{};
			int32_t original_pOutBalanceTaskType{};
			int8_t a1{};

			const auto setup_data = [](
				int32_t& pOutBalanceTaskType
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOutBalanceTaskType);
			setup_data(original_pOutBalanceTaskType);

			// Call both implementations
			auto moo_result = sut(a1, &moo_pOutBalanceTaskType);
			auto original_result = original(a1, &original_pOutBalanceTaskType);
			
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
			int8_t nTaskNumber{};

			// Call both implementations
			auto moo_result = sut(nTaskNumber);
			auto original_result = original(nTaskNumber);
			
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
			// Input data
			D2TaskStrc moo_ptTask{};
			D2TaskStrc original_ptTask{};
			char nTaskNumber{};

			const auto setup_data = [](
				D2TaskStrc& ptTask
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ptTask);
			setup_data(original_ptTask);

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
			// Input data
			D2TaskStrc moo_ptTaskQueue{};
			int32_t moo_pTaskType{};
			D2TaskStrc original_ptTaskQueue{};
			int32_t original_pTaskType{};
			int nTaskTypeIncrement{};

			const auto setup_data = [](
				D2TaskStrc& ptTaskQueue,
				int32_t& pTaskType
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ptTaskQueue, moo_pTaskType);
			setup_data(original_ptTaskQueue, original_pTaskType);

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
			// Input data
			D2LinkStrc moo_pPrev{};
			D2LinkStrc moo_pLink{};
			D2LinkStrc original_pPrev{};
			D2LinkStrc original_pLink{};

			const auto setup_data = [](
				D2LinkStrc& pPrev,
				D2LinkStrc& pLink
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPrev, moo_pLink);
			setup_data(original_pPrev, original_pLink);

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
			// Input data
			D2LinkStrc moo_pList{};
			D2LinkStrc moo_pLink{};
			D2LinkStrc original_pList{};
			D2LinkStrc original_pLink{};

			const auto setup_data = [](
				D2LinkStrc& pList,
				D2LinkStrc& pLink
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pList, moo_pLink);
			setup_data(original_pList, original_pLink);

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
			// Input data
			D2LinkStrc moo_pLink{};
			D2LinkStrc original_pLink{};

			const auto setup_data = [](
				D2LinkStrc& pLink
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pLink);
			setup_data(original_pLink);

			// Call both implementations
			sut(&moo_pLink);
			original(&original_pLink);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLink, original_pLink, "Comparing pLink");
		}
	}
}
