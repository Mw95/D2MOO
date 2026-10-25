#include <D2WinTestDefines.h>

#ifdef WREGISTER_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WRegister.h>


TEST_SUITE("D2WRegisterTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// Types 0 to 3 are registered with Storm, other types are ignored.
	// NOTE: Type 0 asserts that the id is not WM_COMMAND, WM_KEYUP or WM_KEYDOWN, those are not tested.
	const D2WinCommandRegisterStrc gTestCommands[] =
	{
		{ 0, WM_MOUSEMOVE, D2WinCallbacks::VoidCallback },
		{ 0, WM_CHAR, D2WinCallbacks::VoidCallback },
		{ 1, 1234, D2WinCallbacks::VoidCallback },
		{ 2, VK_SNAPSHOT, D2WinCallbacks::VoidCallback },
		{ 3, VK_RETURN, D2WinCallbacks::VoidCallback },
		{ 3, VK_ESCAPE, nullptr },
		{ 4, VK_ESCAPE, D2WinCallbacks::VoidCallback },
		{ -1, 0, D2WinCallbacks::VoidCallback },
	};


	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1DC0 (#10020)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WREGISTER_RegisterCommand, dll_base + 0x00011DC0);

		for (const auto& command : gTestCommands)
		{
			CAPTURE(command.nType);
			CAPTURE(command.nId);

			// Call both implementations
			D2WinCallLog::clear();
			sut(D2WinMock::hWindow, command.nType, command.nId, command.pCallback);
			const auto moo_calls = D2WinCallLog::take();
			original(D2WinMock::hWindow, command.nType, command.nId, command.pCallback);
			const auto original_calls = D2WinCallLog::take();

			// Compare the registered handlers
			CHECK_EQ(moo_calls, original_calls);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1EC0 (#10021)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WREGISTER_UnregisterCommand, dll_base + 0x00011EC0);

		for (const auto& command : gTestCommands)
		{
			CAPTURE(command.nType);
			CAPTURE(command.nId);

			// Call both implementations
			D2WinCallLog::clear();
			sut(D2WinMock::hWindow, command.nType, command.nId, command.pCallback);
			const auto moo_calls = D2WinCallLog::take();
			original(D2WinMock::hWindow, command.nType, command.nId, command.pCallback);
			const auto original_calls = D2WinCallLog::take();

			// Compare the unregistered handlers
			CHECK_EQ(moo_calls, original_calls);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1FC0 (#10022)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WREGISTER_RegisterCommands, dll_base + 0x00011FC0);

		const int32_t nCommands = GENERATE(0, 1, static_cast<int32_t>(std::size(gTestCommands)));
		CAPTURE(nCommands);

		// Input data
		D2WinCommandRegisterStrc moo_pCommandRegister[std::size(gTestCommands)] = {};
		D2WinCommandRegisterStrc original_pCommandRegister[std::size(gTestCommands)] = {};
		std::copy(std::begin(gTestCommands), std::end(gTestCommands), moo_pCommandRegister);
		std::copy(std::begin(gTestCommands), std::end(gTestCommands), original_pCommandRegister);

		// Call both implementations
		D2WinCallLog::clear();
		sut(D2WinMock::hWindow, moo_pCommandRegister, nCommands);
		const auto moo_calls = D2WinCallLog::take();
		original(D2WinMock::hWindow, original_pCommandRegister, nCommands);
		const auto original_calls = D2WinCallLog::take();

		// Compare the registered handlers
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		for (size_t i = 0; i < std::size(gTestCommands); ++i)
		{
			MOO_CHECK_EQ(moo_pCommandRegister[i], original_pCommandRegister[i], "Comparing pCommandRegister");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B2010")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WREGISTER_UnregisterCommands, dll_base + 0x00012010);

		const int32_t nCommands = GENERATE(0, 1, static_cast<int32_t>(std::size(gTestCommands)));
		CAPTURE(nCommands);

		// Input data
		D2WinCommandRegisterStrc moo_pCommandRegister[std::size(gTestCommands)] = {};
		D2WinCommandRegisterStrc original_pCommandRegister[std::size(gTestCommands)] = {};
		std::copy(std::begin(gTestCommands), std::end(gTestCommands), moo_pCommandRegister);
		std::copy(std::begin(gTestCommands), std::end(gTestCommands), original_pCommandRegister);

		// Call both implementations
		D2WinCallLog::clear();
		sut(D2WinMock::hWindow, moo_pCommandRegister, nCommands);
		const auto moo_calls = D2WinCallLog::take();
		original(D2WinMock::hWindow, original_pCommandRegister, nCommands);
		const auto original_calls = D2WinCallLog::take();

		// Compare the unregistered handlers
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		for (size_t i = 0; i < std::size(gTestCommands); ++i)
		{
			MOO_CHECK_EQ(moo_pCommandRegister[i], original_pCommandRegister[i], "Comparing pCommandRegister");
		}
	}
}

#endif
