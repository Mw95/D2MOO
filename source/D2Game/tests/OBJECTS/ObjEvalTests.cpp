#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <OBJECTS/ObjEval.h>
#include <Units/Units.h>


TEST_SUITE("ObjEvalTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC745D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJEVAL_ApplyTrapObjectDamage, dll_base + 0x000445D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pSrcUnit{};
			D2UnitStrc moo_pTargetUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pSrcUnit{};
			D2UnitStrc original_pTargetUnit{};
			int32_t nDamageType{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pSrcUnit,
				D2UnitStrc& pTargetUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pSrcUnit, moo_pTargetUnit);
			setup_data(original_pGame, original_pSrcUnit, original_pTargetUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pSrcUnit, &moo_pTargetUnit, nDamageType);
			original(&original_pGame, &original_pSrcUnit, &original_pTargetUnit, nDamageType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pSrcUnit, original_pSrcUnit, "Comparing pSrcUnit");
			SKIP_MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
		}
	}
}
