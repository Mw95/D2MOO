#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Composit.h>
#include <Units/Units.h>


TEST_SUITE("D2CompositTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD466C0 (#10884)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10884_COMPOSIT_unk, dll_base + 0x000066C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2InventoryStrc pInventory{};
				char szPath{};
				int pWeaponClassCode{};
				
				return std::tuple{ pUnit, pInventory, szPath, pWeaponClassCode };
			};
			
			// Input data
			auto [moo_pUnit, moo_pInventory, moo_szPath, moo_pWeaponClassCode] = setup_data();
			auto [original_pUnit, original_pInventory, original_szPath, original_pWeaponClassCode] = setup_data();
			int nClass{};
			int nMode{};
			int nUnitType{};
			BOOL bAddPathPrefix{};
			int a9{};

			// Call both implementations
			sut(&moo_pUnit, nClass, nMode, nUnitType, &moo_pInventory, &moo_szPath, &moo_pWeaponClassCode, bAddPathPrefix, a9);
			original(&original_pUnit, nClass, nMode, nUnitType, &original_pInventory, &original_szPath, &original_pWeaponClassCode, bAddPathPrefix, a9);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			SKIP_MOO_CHECK_EQ(moo_szPath, original_szPath, "Comparing szPath");
			SKIP_MOO_CHECK_EQ(moo_pWeaponClassCode, original_pWeaponClassCode, "Comparing pWeaponClassCode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD46BC0 (#10885)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10885_COMPOSIT_unk, dll_base + 0x00006BC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				char szPath{};
				int pWeaponClassCode{};
				D2InventoryStrc pInventory{};
				
				return std::tuple{ pUnit, szPath, pWeaponClassCode, pInventory };
			};
			
			// Input data
			auto [moo_pUnit, moo_szPath, moo_pWeaponClassCode, moo_pInventory] = setup_data();
			auto [original_pUnit, original_szPath, original_pWeaponClassCode, original_pInventory] = setup_data();
			BOOL bAddPathPrefix{};
			int a5{};
			int nAnimMode{};

			// Call both implementations
			sut(&moo_pUnit, &moo_szPath, &moo_pWeaponClassCode, bAddPathPrefix, a5, &moo_pInventory, nAnimMode);
			original(&original_pUnit, &original_szPath, &original_pWeaponClassCode, bAddPathPrefix, a5, &original_pInventory, nAnimMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_szPath, original_szPath, "Comparing szPath");
			SKIP_MOO_CHECK_EQ(moo_pWeaponClassCode, original_pWeaponClassCode, "Comparing pWeaponClassCode");
			SKIP_MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD46C60 (#10886)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_GetWeaponClassIdFromCode, dll_base + 0x00006C60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nWeaponClassCode{};

			// Call both implementations
			const auto moo_result = sut(nWeaponClassCode);
			const auto original_result = original(nWeaponClassCode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD46C90 (#10887)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_GetWeaponClassCode, dll_base + 0x00006C90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2InventoryStrc pInventory{};
				int pWeaponClassId{};
				
				return std::tuple{ pUnit, pInventory, pWeaponClassId };
			};
			
			// Input data
			auto [moo_pUnit, moo_pInventory, moo_pWeaponClassId] = setup_data();
			auto [original_pUnit, original_pInventory, original_pWeaponClassId] = setup_data();
			int nUnitType{};
			int nClass{};
			int nMode{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nUnitType, nClass, nMode, &moo_pInventory, &moo_pWeaponClassId);
			const auto original_result = original(&original_pUnit, nUnitType, nClass, nMode, &original_pInventory, &original_pWeaponClassId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			SKIP_MOO_CHECK_EQ(moo_pWeaponClassId, original_pWeaponClassId, "Comparing pWeaponClassId");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD47150 (#10888)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_GetWeaponClassId, dll_base + 0x00007150);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2InventoryStrc pInventory{};
				int pWeaponClassId{};
				
				return std::tuple{ pUnit, pInventory, pWeaponClassId };
			};
			
			// Input data
			auto [moo_pUnit, moo_pInventory, moo_pWeaponClassId] = setup_data();
			auto [original_pUnit, original_pInventory, original_pWeaponClassId] = setup_data();
			int nAnimMode{};
			BOOL a5{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pInventory, &moo_pWeaponClassId, nAnimMode, a5);
			const auto original_result = original(&original_pUnit, &original_pInventory, &original_pWeaponClassId, nAnimMode, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			SKIP_MOO_CHECK_EQ(moo_pWeaponClassId, original_pWeaponClassId, "Comparing pWeaponClassId");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD47200 (#10889)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_IsArmorComponent, dll_base + 0x00007200);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nComponent{};

			// Call both implementations
			const auto moo_result = sut(nComponent);
			const auto original_result = original(nComponent);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD47230 (#10890)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_IsWeaponBowOrXBow, dll_base + 0x00007230);
		
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

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD472E0 (#10891)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_GetArmorTypeFromComponent, dll_base + 0x000072E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				uint8_t pArmorComponents{};
				
				return std::tuple{ pArmorComponents };
			};
			
			// Input data
			auto [moo_pArmorComponents] = setup_data();
			auto [original_pArmorComponents] = setup_data();
			int nComponent{};

			// Call both implementations
			const auto moo_result = sut(nComponent, &moo_pArmorComponents);
			const auto original_result = original(nComponent, &original_pArmorComponents);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pArmorComponents, original_pArmorComponents, "Comparing pArmorComponents");
		}
	}
}
