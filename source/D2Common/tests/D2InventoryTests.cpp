#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <memory>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Composit.h>
#include <D2DataTbls.h>
#include <D2Inventory.h>
#include <D2Items.h>
#include <DataTbls/InvTbls.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>

// Mirrors the definition in D2Inventory.cpp to access its component arrays
struct D2InventoryComponentItemTypeStrc
{
	int dwCode;
	int nItemType;
};

extern D2InventoryComponentItemTypeStrc gTxtComponentItemTypeMap[255];
extern int gnComponentArrayRecordCount;
extern BOOL gbComponentArrayInitialized;


TEST_SUITE("D2InventoryTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	constexpr int belt_grid_size = 16;

	const auto get_item_id = [](const std::unique_ptr<D2ItemsTxt[]>& items_txt, int items_record_count, uint32_t dwCode)
	{
		for (auto i = 0; i < items_record_count; ++i)
		{
			if (items_txt[i].dwCode == dwCode)
			{
				return i;
			}
		}

		FAIL("Unknown item code");
		return -1;
	};

	const auto check_grid_occupancy = [](const D2InventoryGridStrc& moo_grid, const D2InventoryGridStrc& original_grid)
	{
		REQUIRE_EQ(moo_grid.nGridWidth, original_grid.nGridWidth);
		REQUIRE_EQ(moo_grid.nGridHeight, original_grid.nGridHeight);

		for (auto i = 0; i < moo_grid.nGridWidth * moo_grid.nGridHeight; ++i)
		{
			CHECK_EQ(moo_grid.ppItems[i] == nullptr, original_grid.ppItems[i] == nullptr);
		}
	};

	// The items linker is not set up by the fixtures but required to look up items by code
	struct ItemsLinkerScope
	{
		ItemsLinkerScope(const std::unique_ptr<D2ItemsTxt[]>& items_txt, int items_record_count)
		{
			sgptDataTables->pItemsLinker = static_cast<D2TxtLinkStrc*>(FOG_AllocLinker(__FILE__, __LINE__));
			for (auto i = 0; i < items_record_count; ++i)
			{
				FOG_10215(sgptDataTables->pItemsLinker, static_cast<int>(items_txt[i].dwCode));
			}
		}

		~ItemsLinkerScope()
		{
			FOG_FreeLinker(sgptDataTables->pItemsLinker);
			sgptDataTables->pItemsLinker = nullptr;
		}
	};

	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD8E210")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_RemoveItem, dll_base + 0x0004E210);

		SUBCASE("cursor item")
		{
			// Input data
			const auto item_id = random_unsigned_integer();
			const auto owner_id = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2InventoryStrc original_pInventory{};

			const auto setup_data = [item_id, owner_id](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2InventoryStrc& pInventory
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;

				pItemData.dwOwnerGUID = owner_id;
				pItemData.pExtraData.pParentInv = &pInventory;
				pItemData.pExtraData.nNodePosOther = 1;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pCursorItem = &pItem;
				pInventory.dwLeftItemGUID = item_id;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pInventory);
			setup_data(original_pItem, original_pItemData, original_pInventory);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}

		SUBCASE("item in body location")
		{
			// Input data
			const auto item_id = random_unsigned_integer();
			const auto owner_id = random_unsigned_integer();
			const auto body_loc = static_cast<int>(random_unsigned_integer(BODYLOC_HEAD, NUM_BODYLOC - 1));

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StaticPathStrc moo_pStaticPath{};
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StaticPathStrc original_pStaticPath{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};

			const auto setup_data = [item_id, owner_id, body_loc](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StaticPathStrc& pStaticPath,
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC]
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
				pItem.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = body_loc;

				pItemData.dwOwnerGUID = owner_id;
				pItemData.pExtraData.pParentInv = &pInventory;
				pItemData.pExtraData.nNodePos = INVGRID_BODYLOC + 1;
				pItemData.pExtraData.nNodePosOther = 3;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstItem = &pItem;
				pInventory.pLastItem = &pItem;
				pInventory.dwItemCount = 1;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].pItem = &pItem;
				pGrids[INVGRID_BODYLOC].pLastItem = &pItem;
				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;
				ppBodyLocItems[body_loc] = &pItem;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStaticPath, moo_pInventory, moo_pGrids, moo_ppBodyLocItems);
			setup_data(original_pItem, original_pItemData, original_pStaticPath, original_pInventory, original_pGrids, original_ppBodyLocItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_BODYLOC], original_pGrids[INVGRID_BODYLOC], "Comparing body location grid");
			check_grid_occupancy(moo_pGrids[INVGRID_BODYLOC], original_pGrids[INVGRID_BODYLOC]);
		}

		SUBCASE("item in backpack")
		{
			// Input data
			static constexpr int grid_width = 10;
			static constexpr int grid_height = 4;

			const auto item_id = random_unsigned_integer();
			const auto previous_item_id = random_unsigned_integer();
			const auto next_item_id = random_unsigned_integer();
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const int item_width = items_txt[short_sword_id].nInvWidth;
			const int item_height = items_txt[short_sword_id].nInvHeight;

			D2UnitStrc moo_pPreviousItem{};
			D2ItemDataStrc moo_pPreviousItemData{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc moo_pNextItem{};
			D2ItemDataStrc moo_pNextItemData{};
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* moo_ppItems[grid_width * grid_height]{};
			D2UnitStrc original_pPreviousItem{};
			D2ItemDataStrc original_pPreviousItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StaticPathStrc original_pStaticPath{};
			D2UnitStrc original_pNextItem{};
			D2ItemDataStrc original_pNextItemData{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* original_ppItems[grid_width * grid_height]{};

			const auto setup_data = [item_id, previous_item_id, next_item_id, short_sword_id, item_width, item_height](
				D2UnitStrc& pPreviousItem,
				D2ItemDataStrc& pPreviousItemData,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StaticPathStrc& pStaticPath,
				D2UnitStrc& pNextItem,
				D2ItemDataStrc& pNextItemData,
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				D2UnitStrc* (&ppItems)[grid_width * grid_height]
			) {
				constexpr int item_x = 2;
				constexpr int item_y = 0;

				pPreviousItem.dwUnitType = UNIT_ITEM;
				pPreviousItem.dwUnitId = previous_item_id;
				pPreviousItem.pItemData = &pPreviousItemData;
				pPreviousItemData.pExtraData.pParentInv = &pInventory;
				pPreviousItemData.pExtraData.pNextItem = &pItem;
				pPreviousItemData.pExtraData.pNextGridItem = &pItem;
				pPreviousItemData.pExtraData.nNodePos = INVGRID_INVENTORY + 1;
				pPreviousItemData.pExtraData.nNodePosOther = 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = short_sword_id;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
				pItem.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = item_x;
				pStaticPath.tGameCoords.nY = item_y;
				pItemData.pExtraData.pParentInv = &pInventory;
				pItemData.pExtraData.pPreviousItem = &pPreviousItem;
				pItemData.pExtraData.pNextItem = &pNextItem;
				pItemData.pExtraData.pPreviousGridItem = &pPreviousItem;
				pItemData.pExtraData.pNextGridItem = &pNextItem;
				pItemData.pExtraData.nNodePos = INVGRID_INVENTORY + 1;
				pItemData.pExtraData.nNodePosOther = 1;

				pNextItem.dwUnitType = UNIT_ITEM;
				pNextItem.dwUnitId = next_item_id;
				pNextItem.pItemData = &pNextItemData;
				pNextItemData.pExtraData.pParentInv = &pInventory;
				pNextItemData.pExtraData.pPreviousItem = &pItem;
				pNextItemData.pExtraData.pPreviousGridItem = &pItem;
				pNextItemData.pExtraData.nNodePos = INVGRID_INVENTORY + 1;
				pNextItemData.pExtraData.nNodePosOther = 1;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstItem = &pPreviousItem;
				pInventory.pLastItem = &pNextItem;
				pInventory.dwItemCount = 3;
				pInventory.dwLeftItemGUID = item_id;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pGrids[INVGRID_INVENTORY].pItem = &pPreviousItem;
				pGrids[INVGRID_INVENTORY].pLastItem = &pNextItem;
				pGrids[INVGRID_INVENTORY].nGridWidth = grid_width;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_height;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems;

				ppItems[0] = &pPreviousItem;
				ppItems[grid_width * grid_height - 1] = &pNextItem;
				for (auto y = item_y; y < item_y + item_height; ++y)
				{
					for (auto x = item_x; x < item_x + item_width; ++x)
					{
						ppItems[x + y * grid_width] = &pItem;
					}
				}
			};

			setup_data(moo_pPreviousItem, moo_pPreviousItemData, moo_pItem, moo_pItemData, moo_pStaticPath, moo_pNextItem, moo_pNextItemData, moo_pInventory, moo_pGrids, moo_ppItems);
			setup_data(original_pPreviousItem, original_pPreviousItemData, original_pItem, original_pItemData, original_pStaticPath, original_pNextItem, original_pNextItemData, original_pInventory, original_pGrids, original_ppItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pPreviousItem, original_pPreviousItem, "Comparing pPreviousItem");
			MOO_CHECK_EQ(moo_pNextItem, original_pNextItem, "Comparing pNextItem");
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_INVENTORY], original_pGrids[INVGRID_INVENTORY], "Comparing inventory grid");
			check_grid_occupancy(moo_pGrids[INVGRID_INVENTORY], original_pGrids[INVGRID_INVENTORY]);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E4A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetItemExtraDataFromItem, dll_base + 0x0004E4A0);
		
		SUBCASE("")
		{
			// Input data
			const auto node_pos = random_unsigned_integer(0, 127);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [node_pos](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.pExtraData.nNodePos = node_pos;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E4C0 (#10240)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_AllocInventory, dll_base + 0x0004E4C0);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();

			D2UnitStrc moo_pOwner{};
			D2UnitStrc original_pOwner{};

			const auto setup_data = [unit_id](
				D2UnitStrc& pOwner
			) {
				pOwner.dwUnitId = unit_id;
			};

			setup_data(moo_pOwner);
			setup_data(original_pOwner);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pOwner);
			const auto original_result = original(nullptr, &original_pOwner);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E520 (#10241)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_FreeInventory, dll_base + 0x0004E520);
		const auto [moo_alloc, original_alloc] = make_function_pair(INVENTORY_AllocInventory, dll_base + 0x0004E4C0);

		SUBCASE("")
		{
			// Input data
			D2InventoryStrc* moo_pInventory = moo_alloc(nullptr, nullptr);
			D2InventoryStrc* original_pInventory = original_alloc(nullptr, nullptr);

			// Call both implementations
			sut(moo_pInventory);
			original(original_pInventory);

			// Input can not be compared since it was freed
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E620 (#10244)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_CompareWithItemsParentInventory, dll_base + 0x0004E620);
		
		SUBCASE("is equal")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2InventoryStrc& pParentInventory
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.pExtraData.pParentInv = &pParentInventory;
				pInventory.dwSignature = D2C_InventoryHeader;
				pParentInventory.dwSignature = D2C_InventoryHeader;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData, moo_pInventory);
			setup_data(original_pInventory, original_pItem, original_pItemData, original_pInventory);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem);
			const auto original_result = original(&original_pInventory, &original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, true);
		}

		SUBCASE("is not equal")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryStrc moo_pParentInventory{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2InventoryStrc original_pParentInventory{};

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2InventoryStrc& pParentInventory
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.pExtraData.pParentInv = &pParentInventory;
				pInventory.dwSignature = D2C_InventoryHeader;
				pParentInventory.dwSignature = D2C_InventoryHeader;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData, moo_pParentInventory);
			setup_data(original_pInventory, original_pItem, original_pItemData, original_pParentInventory);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem);
			const auto original_result = original(&original_pInventory, &original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, false);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E660 (#10243)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_RemoveItemFromInventory, dll_base + 0x0004E660);

		SUBCASE("item in inventory")
		{
			// Input data
			const auto item_id = random_unsigned_integer();
			const auto owner_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [item_id, owner_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstItem = &pItem;
				pInventory.pLastItem = &pItem;
				pInventory.dwItemCount = 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
				pItemData.dwOwnerGUID = owner_id;
				pItemData.pExtraData.pParentInv = &pInventory;
				pItemData.pExtraData.nNodePosOther = 1;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData);
			setup_data(original_pInventory, original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem);
			const auto original_result = original(&original_pInventory, &original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, &moo_pItem);
		}

		SUBCASE("item in other inventory")
		{
			// Input data
			const auto item_id = random_unsigned_integer();
			const auto owner_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryStrc moo_pParentInventory{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2InventoryStrc original_pParentInventory{};

			const auto setup_data = [item_id, owner_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2InventoryStrc& pParentInventory
			) {
				pInventory.dwSignature = D2C_InventoryHeader;

				pParentInventory.dwSignature = D2C_InventoryHeader;
				pParentInventory.pFirstItem = &pItem;
				pParentInventory.pLastItem = &pItem;
				pParentInventory.dwItemCount = 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
				pItemData.dwOwnerGUID = owner_id;
				pItemData.pExtraData.pParentInv = &pParentInventory;
				pItemData.pExtraData.nNodePosOther = 1;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData, moo_pParentInventory);
			setup_data(original_pInventory, original_pItem, original_pItemData, original_pParentInventory);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem);
			const auto original_result = original(&original_pInventory, &original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, nullptr);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E6A0 (#10242)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_PlaceItemInSocket, dll_base + 0x0004E6A0);

		SUBCASE("owner is an item")
		{
			// Input data
			const auto owner_id = random_unsigned_integer();
			const auto socketed_item_id = random_unsigned_integer();
			const auto item_id = random_unsigned_integer();
			const auto item_owner_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pSocketedItem{};
			D2ItemDataStrc moo_pSocketedItemData{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StaticPathStrc moo_pStaticPath{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pSocketedItem{};
			D2ItemDataStrc original_pSocketedItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StaticPathStrc original_pStaticPath{};
			int nUnused = random_unsigned_integer();

			const auto setup_data = [owner_id, socketed_item_id, item_id, item_owner_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pOwner,
				D2UnitStrc& pSocketedItem,
				D2ItemDataStrc& pSocketedItemData,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StaticPathStrc& pStaticPath
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pOwner;
				pInventory.pFirstItem = &pSocketedItem;
				pInventory.pLastItem = &pSocketedItem;
				pInventory.dwItemCount = 1;

				pOwner.dwUnitType = UNIT_ITEM;
				pOwner.dwUnitId = owner_id;

				pSocketedItem.dwUnitType = UNIT_ITEM;
				pSocketedItem.dwUnitId = socketed_item_id;
				pSocketedItem.pItemData = &pSocketedItemData;
				pSocketedItemData.dwOwnerGUID = D2UnitInvalidGUID;
				pSocketedItemData.pExtraData.pParentInv = &pInventory;
				pSocketedItemData.pExtraData.nNodePosOther = 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
				pItem.pStaticPath = &pStaticPath;
				pItemData.dwOwnerGUID = item_owner_id;
			};

			setup_data(moo_pInventory, moo_pOwner, moo_pSocketedItem, moo_pSocketedItemData, moo_pItem, moo_pItemData, moo_pStaticPath);
			setup_data(original_pInventory, original_pOwner, original_pSocketedItem, original_pSocketedItemData, original_pItem, original_pItemData, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem, nUnused);
			const auto original_result = original(&original_pInventory, &original_pItem, nUnused);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pSocketedItem, original_pSocketedItem, "Comparing pSocketedItem");
		}

		SUBCASE("owner is not an item")
		{
			// Input data
			const auto owner_id = random_unsigned_integer();
			const auto item_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int nUnused = random_unsigned_integer();

			const auto setup_data = [owner_id, item_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pOwner,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pOwner;

				pOwner.dwUnitType = UNIT_PLAYER;
				pOwner.dwUnitId = owner_id;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pInventory, moo_pOwner, moo_pItem, moo_pItemData);
			setup_data(original_pInventory, original_pOwner, original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem, nUnused);
			const auto original_result = original(&original_pInventory, &original_pItem, nUnused);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E7A0 (#10277)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetFirstItem, dll_base + 0x0004E7A0);
		
		SUBCASE("")
		{
			// Input data
			const auto item_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pFirstItem{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pFirstItem{};

			const auto setup_data = [item_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pFirstItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstItem = &pFirstItem;
				pFirstItem.dwUnitId = item_id;
			};

			setup_data(moo_pInventory, moo_pFirstItem);
			setup_data(original_pInventory, original_pFirstItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8E7C0 (#10278)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetLastItem, dll_base + 0x0004E7C0);
		
		SUBCASE("")
		{
			// Input data
			const auto item_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pLastItem{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pLastItem{};

			const auto setup_data = [item_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pLastItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pLastItem = &pLastItem;
				pLastItem.dwUnitId = item_id;
			};

			setup_data(moo_pInventory, moo_pLastItem);
			setup_data(original_pInventory, original_pLastItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<ItemsTxtFixture<NoopFixture>>, "D2Common.0x6FD8E7E0 (#10245)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetFreePosition, dll_base + 0x0004E7E0);

		SUBCASE("")
		{
			// Input data
			const auto owner_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);
			const auto item_code = GENERATE(' nir', ' xah', ' iuq');
			const auto item_id = get_item_id(items_txt, items_record_count, item_code);
			const auto& grid_info = inventory_txt[INVENTORYRECORD_AMAZON].pGridInfo;
			const int grid_size = grid_info.nGridX * grid_info.nGridY;

			std::vector<bool> occupied(grid_size);
			for (auto i = 0; i < grid_size; ++i)
			{
				occupied[i] = random_unsigned_integer(0, 2) == 0;
			}

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_size);
			D2UnitStrc moo_pOtherItem{};
			int moo_pFreeX = -1;
			int moo_pFreeY = -1;
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> original_ppItems(grid_size);
			D2UnitStrc original_pOtherItem{};
			int original_pFreeX = -1;
			int original_pFreeY = -1;
			int nInventoryRecordId = INVENTORYRECORD_AMAZON;
			uint8_t nPage = INVPAGE_INVENTORY;

			const auto setup_data = [owner_type, item_id, &grid_info, &occupied](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pOwner,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc& pOtherItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pOwner;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pOwner.dwUnitType = owner_type;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = item_id;
				pItem.pItemData = &pItemData;

				pGrids[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems.data();

				pOtherItem.dwUnitType = UNIT_ITEM;
				for (size_t i = 0; i < ppItems.size(); ++i)
				{
					if (occupied[i])
					{
						ppItems[i] = &pOtherItem;
					}
				}
			};

			setup_data(moo_pInventory, moo_pOwner, moo_pItem, moo_pItemData, moo_pGrids, moo_ppItems, moo_pOtherItem);
			setup_data(original_pInventory, original_pOwner, original_pItem, original_pItemData, original_pGrids, original_ppItems, original_pOtherItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem, nInventoryRecordId, &moo_pFreeX, &moo_pFreeY, nPage);
			const auto original_result = original(&original_pInventory, &original_pItem, nInventoryRecordId, &original_pFreeX, &original_pFreeY, nPage);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pFreeX, original_pFreeX, "Comparing pFreeX");
			MOO_CHECK_EQ(moo_pFreeY, original_pFreeY, "Comparing pFreeY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8EAF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetGrid, dll_base + 0x0004EAF0);

		SUBCASE("new grid")
		{
			// Input data
			const auto grid_x = static_cast<uint8_t>(random_unsigned_integer(1, 10));
			const auto grid_y = static_cast<uint8_t>(random_unsigned_integer(1, 10));

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridInfoStrc moo_pInventoryGridInfo{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridInfoStrc original_pInventoryGridInfo{};
			int nInventoryGrid = random_unsigned_integer(0, 4);

			const auto setup_data = [grid_x, grid_y](
				D2InventoryStrc& pInventory,
				D2InventoryGridInfoStrc& pInventoryGridInfo
			) {
				pInventory.dwSignature = D2C_InventoryHeader;

				pInventoryGridInfo.nGridX = grid_x;
				pInventoryGridInfo.nGridY = grid_y;
			};

			setup_data(moo_pInventory, moo_pInventoryGridInfo);
			setup_data(original_pInventory, original_pInventoryGridInfo);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nInventoryGrid, &moo_pInventoryGridInfo);
			const auto original_result = original(&original_pInventory, nInventoryGrid, &original_pInventoryGridInfo);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pInventoryGridInfo, original_pInventoryGridInfo, "Comparing pInventoryGridInfo");
		}

		SUBCASE("existing grid")
		{
			// Input data
			const auto grid_x = random_unsigned_integer(1, 10);
			const auto grid_y = random_unsigned_integer(1, 10);
			const auto size_mismatch = GENERATE(0, 1);

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridInfoStrc moo_pInventoryGridInfo{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_x * grid_y);
			D2InventoryStrc original_pInventory{};
			D2InventoryGridInfoStrc original_pInventoryGridInfo{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> original_ppItems(grid_x * grid_y);
			int nInventoryGrid = random_unsigned_integer(INVGRID_BODYLOC, INVGRID_INVENTORY);

			const auto setup_data = [grid_x, grid_y, size_mismatch, nInventoryGrid](
				D2InventoryStrc& pInventory,
				D2InventoryGridInfoStrc& pInventoryGridInfo,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				std::vector<D2UnitStrc*>& ppItems
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pGrids[nInventoryGrid].nGridWidth = grid_x;
				pGrids[nInventoryGrid].nGridHeight = grid_y;
				pGrids[nInventoryGrid].ppItems = ppItems.data();

				pInventoryGridInfo.nGridX = static_cast<uint8_t>(grid_x + size_mismatch);
				pInventoryGridInfo.nGridY = grid_y;
			};

			setup_data(moo_pInventory, moo_pInventoryGridInfo, moo_pGrids, moo_ppItems);
			setup_data(original_pInventory, original_pInventoryGridInfo, original_pGrids, original_ppItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nInventoryGrid, &moo_pInventoryGridInfo);
			const auto original_result = original(&original_pInventory, nInventoryGrid, &original_pInventoryGridInfo);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pInventoryGridInfo, original_pInventoryGridInfo, "Comparing pInventoryGridInfo");
			MOO_CHECK_EQ(moo_pGrids[nInventoryGrid], original_pGrids[nInventoryGrid], "Comparing grid");
		}

		SUBCASE("missing grid without grid info")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2InventoryStrc original_pInventory{};
			int nInventoryGrid = random_unsigned_integer(0, 4);

			const auto setup_data = [](
				D2InventoryStrc& pInventory
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
			};

			setup_data(moo_pInventory);
			setup_data(original_pInventory);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nInventoryGrid, nullptr);
			const auto original_result = original(&original_pInventory, nInventoryGrid, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8EC70")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_CanItemBePlacedAtPos, dll_base + 0x0004EC70);

		SUBCASE("")
		{
			REPEAT_10();

			// Input data
			const auto grid_width = static_cast<int>(random_unsigned_integer(1, 10));
			const auto grid_height = static_cast<int>(random_unsigned_integer(1, 8));

			std::vector<bool> occupied(grid_width * grid_height);
			for (auto i = 0; i < grid_width * grid_height; ++i)
			{
				occupied[i] = random_unsigned_integer(0, 2) == 0;
			}

			D2InventoryGridStrc moo_pInventoryGrid{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_width * grid_height);
			D2UnitStrc moo_pOtherItem{};
			D2InventoryGridStrc original_pInventoryGrid{};
			std::vector<D2UnitStrc*> original_ppItems(grid_width * grid_height);
			D2UnitStrc original_pOtherItem{};
			uint8_t nItemWidth = static_cast<uint8_t>(random_unsigned_integer(1, 4));
			uint8_t nItemHeight = static_cast<uint8_t>(random_unsigned_integer(1, 4));

			const auto setup_data = [grid_width, grid_height, &occupied](
				D2InventoryGridStrc& pInventoryGrid,
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc& pOtherItem
			) {
				pInventoryGrid.nGridWidth = static_cast<uint8_t>(grid_width);
				pInventoryGrid.nGridHeight = static_cast<uint8_t>(grid_height);
				pInventoryGrid.ppItems = ppItems.data();

				pOtherItem.dwUnitType = UNIT_ITEM;
				for (size_t i = 0; i < ppItems.size(); ++i)
				{
					if (occupied[i])
					{
						ppItems[i] = &pOtherItem;
					}
				}
			};

			setup_data(moo_pInventoryGrid, moo_ppItems, moo_pOtherItem);
			setup_data(original_pInventoryGrid, original_ppItems, original_pOtherItem);

			for (int nY = 0; nY <= grid_height; ++nY)
			{
				for (int nX = 0; nX <= grid_width; ++nX)
				{
					// Call both implementations
					const auto moo_result = sut(&moo_pInventoryGrid, nX, nY, nItemWidth, nItemHeight);
					const auto original_result = original(&original_pInventoryGrid, nX, nY, nItemWidth, nItemHeight);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventoryGrid, original_pInventoryGrid, "Comparing pInventoryGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8ECF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_FindFreePositionBottomRightToTopLeftWithWeight, dll_base + 0x0004ECF0);

		SUBCASE("")
		{
			REPEAT_10();

			// Input data
			const auto grid_width = static_cast<int>(random_unsigned_integer(1, 10));
			const auto grid_height = static_cast<int>(random_unsigned_integer(1, 8));

			std::vector<bool> occupied(grid_width * grid_height);
			for (auto i = 0; i < grid_width * grid_height; ++i)
			{
				occupied[i] = random_unsigned_integer(0, 2) == 0;
			}

			D2InventoryGridStrc moo_pInventoryGrid{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_width * grid_height);
			D2UnitStrc moo_pOtherItem{};
			int moo_pFreeX = -1;
			int moo_pFreeY = -1;
			D2InventoryGridStrc original_pInventoryGrid{};
			std::vector<D2UnitStrc*> original_ppItems(grid_width * grid_height);
			D2UnitStrc original_pOtherItem{};
			int original_pFreeX = -1;
			int original_pFreeY = -1;
			uint8_t nItemWidth = static_cast<uint8_t>(random_unsigned_integer(1, 4));
			uint8_t nItemHeight = static_cast<uint8_t>(random_unsigned_integer(1, 4));

			const auto setup_data = [grid_width, grid_height, &occupied](
				D2InventoryGridStrc& pInventoryGrid,
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc& pOtherItem
			) {
				pInventoryGrid.nGridWidth = static_cast<uint8_t>(grid_width);
				pInventoryGrid.nGridHeight = static_cast<uint8_t>(grid_height);
				pInventoryGrid.ppItems = ppItems.data();

				pOtherItem.dwUnitType = UNIT_ITEM;
				for (size_t i = 0; i < ppItems.size(); ++i)
				{
					if (occupied[i])
					{
						ppItems[i] = &pOtherItem;
					}
				}
			};

			setup_data(moo_pInventoryGrid, moo_ppItems, moo_pOtherItem);
			setup_data(original_pInventoryGrid, original_ppItems, original_pOtherItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventoryGrid, &moo_pFreeX, &moo_pFreeY, nItemWidth, nItemHeight);
			const auto original_result = original(&original_pInventoryGrid, &original_pFreeX, &original_pFreeY, nItemWidth, nItemHeight);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventoryGrid, original_pInventoryGrid, "Comparing pInventoryGrid");
			MOO_CHECK_EQ(moo_pFreeX, original_pFreeX, "Comparing pFreeX");
			MOO_CHECK_EQ(moo_pFreeY, original_pFreeY, "Comparing pFreeY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8EE20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetPlacementWeight, dll_base + 0x0004EE20);

		SUBCASE("")
		{
			REPEAT_10();

			// Input data
			const auto grid_width = static_cast<int>(random_unsigned_integer(1, 10));
			const auto grid_height = static_cast<int>(random_unsigned_integer(1, 8));

			std::vector<bool> occupied(grid_width * grid_height);
			for (auto i = 0; i < grid_width * grid_height; ++i)
			{
				occupied[i] = random_unsigned_integer(0, 2) == 0;
			}

			D2InventoryGridStrc moo_pInventoryGrid{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_width * grid_height);
			D2UnitStrc moo_pOtherItem{};
			D2InventoryGridStrc original_pInventoryGrid{};
			std::vector<D2UnitStrc*> original_ppItems(grid_width * grid_height);
			D2UnitStrc original_pOtherItem{};
			// The item has to fit into the grid, otherwise cells outside of the grid would be accessed
			uint8_t nItemWidth = static_cast<uint8_t>(random_unsigned_integer(1, std::min(grid_width, 4)));
			uint8_t nItemHeight = static_cast<uint8_t>(random_unsigned_integer(1, std::min(grid_height, 4)));

			const auto setup_data = [grid_width, grid_height, &occupied](
				D2InventoryGridStrc& pInventoryGrid,
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc& pOtherItem
			) {
				pInventoryGrid.nGridWidth = static_cast<uint8_t>(grid_width);
				pInventoryGrid.nGridHeight = static_cast<uint8_t>(grid_height);
				pInventoryGrid.ppItems = ppItems.data();

				pOtherItem.dwUnitType = UNIT_ITEM;
				for (size_t i = 0; i < ppItems.size(); ++i)
				{
					if (occupied[i])
					{
						ppItems[i] = &pOtherItem;
					}
				}
			};

			setup_data(moo_pInventoryGrid, moo_ppItems, moo_pOtherItem);
			setup_data(original_pInventoryGrid, original_ppItems, original_pOtherItem);

			for (int nYPos = 0; nYPos + nItemHeight <= grid_height; ++nYPos)
			{
				for (int nXPos = 0; nXPos + nItemWidth <= grid_width; ++nXPos)
				{
					// Call both implementations
					const auto moo_result = sut(&moo_pInventoryGrid, nXPos, nYPos, nItemWidth, nItemHeight);
					const auto original_result = original(&original_pInventoryGrid, nXPos, nYPos, nItemWidth, nItemHeight);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventoryGrid, original_pInventoryGrid, "Comparing pInventoryGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8EFB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_FindFreePositionTopLeftToBottomRightWithWeight, dll_base + 0x0004EFB0);

		SUBCASE("")
		{
			REPEAT_10();

			// Input data
			const auto grid_width = static_cast<int>(random_unsigned_integer(1, 10));
			const auto grid_height = static_cast<int>(random_unsigned_integer(1, 8));

			std::vector<bool> occupied(grid_width * grid_height);
			for (auto i = 0; i < grid_width * grid_height; ++i)
			{
				occupied[i] = random_unsigned_integer(0, 2) == 0;
			}

			D2InventoryGridStrc moo_pInventoryGrid{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_width * grid_height);
			D2UnitStrc moo_pOtherItem{};
			int moo_pFreeX = -1;
			int moo_pFreeY = -1;
			D2InventoryGridStrc original_pInventoryGrid{};
			std::vector<D2UnitStrc*> original_ppItems(grid_width * grid_height);
			D2UnitStrc original_pOtherItem{};
			int original_pFreeX = -1;
			int original_pFreeY = -1;
			uint8_t nItemWidth = static_cast<uint8_t>(random_unsigned_integer(1, 4));
			uint8_t nItemHeight = static_cast<uint8_t>(random_unsigned_integer(1, 4));

			const auto setup_data = [grid_width, grid_height, &occupied](
				D2InventoryGridStrc& pInventoryGrid,
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc& pOtherItem
			) {
				pInventoryGrid.nGridWidth = static_cast<uint8_t>(grid_width);
				pInventoryGrid.nGridHeight = static_cast<uint8_t>(grid_height);
				pInventoryGrid.ppItems = ppItems.data();

				pOtherItem.dwUnitType = UNIT_ITEM;
				for (size_t i = 0; i < ppItems.size(); ++i)
				{
					if (occupied[i])
					{
						ppItems[i] = &pOtherItem;
					}
				}
			};

			setup_data(moo_pInventoryGrid, moo_ppItems, moo_pOtherItem);
			setup_data(original_pInventoryGrid, original_ppItems, original_pOtherItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventoryGrid, &moo_pFreeX, &moo_pFreeY, nItemWidth, nItemHeight);
			const auto original_result = original(&original_pInventoryGrid, &original_pFreeX, &original_pFreeY, nItemWidth, nItemHeight);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventoryGrid, original_pInventoryGrid, "Comparing pInventoryGrid");
			MOO_CHECK_EQ(moo_pFreeX, original_pFreeX, "Comparing pFreeX");
			MOO_CHECK_EQ(moo_pFreeY, original_pFreeY, "Comparing pFreeY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8F0E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_FindFreePositionTopLeftToBottomRight, dll_base + 0x0004F0E0);

		SUBCASE("")
		{
			REPEAT_10();

			// Input data
			const auto grid_width = static_cast<int>(random_unsigned_integer(1, 10));
			const auto grid_height = static_cast<int>(random_unsigned_integer(1, 8));

			std::vector<bool> occupied(grid_width * grid_height);
			for (auto i = 0; i < grid_width * grid_height; ++i)
			{
				occupied[i] = random_unsigned_integer(0, 2) == 0;
			}

			D2InventoryGridStrc moo_pInventoryGrid{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_width * grid_height);
			D2UnitStrc moo_pOtherItem{};
			int moo_pFreeX = -1;
			int moo_pFreeY = -1;
			D2InventoryGridStrc original_pInventoryGrid{};
			std::vector<D2UnitStrc*> original_ppItems(grid_width * grid_height);
			D2UnitStrc original_pOtherItem{};
			int original_pFreeX = -1;
			int original_pFreeY = -1;
			uint8_t nItemWidth = static_cast<uint8_t>(random_unsigned_integer(1, 4));
			uint8_t nItemHeight = static_cast<uint8_t>(random_unsigned_integer(1, 4));

			const auto setup_data = [grid_width, grid_height, &occupied](
				D2InventoryGridStrc& pInventoryGrid,
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc& pOtherItem
			) {
				pInventoryGrid.nGridWidth = static_cast<uint8_t>(grid_width);
				pInventoryGrid.nGridHeight = static_cast<uint8_t>(grid_height);
				pInventoryGrid.ppItems = ppItems.data();

				pOtherItem.dwUnitType = UNIT_ITEM;
				for (size_t i = 0; i < ppItems.size(); ++i)
				{
					if (occupied[i])
					{
						ppItems[i] = &pOtherItem;
					}
				}
			};

			setup_data(moo_pInventoryGrid, moo_ppItems, moo_pOtherItem);
			setup_data(original_pInventoryGrid, original_ppItems, original_pOtherItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventoryGrid, &moo_pFreeX, &moo_pFreeY, nItemWidth, nItemHeight);
			const auto original_result = original(&original_pInventoryGrid, &original_pFreeX, &original_pFreeY, nItemWidth, nItemHeight);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventoryGrid, original_pInventoryGrid, "Comparing pInventoryGrid");
			MOO_CHECK_EQ(moo_pFreeX, original_pFreeX, "Comparing pFreeX");
			MOO_CHECK_EQ(moo_pFreeY, original_pFreeY, "Comparing pFreeY");
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<ItemsTxtFixture<NoopFixture>>, "D2Common.0x6FD8F1E0 (#10246)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_PlaceItemAtFreePosition, dll_base + 0x0004F1E0);

		SUBCASE("")
		{
			// Input data
			const auto owner_id = random_unsigned_integer();
			const auto item_id = random_unsigned_integer();
			const auto other_item_id = random_unsigned_integer();
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto ring_id = get_item_id(items_txt, items_record_count, ' nir');
			const auto& grid_info = inventory_txt[INVENTORYRECORD_AMAZON].pGridInfo;
			const int grid_size = grid_info.nGridX * grid_info.nGridY;

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc moo_pOtherItem{};
			D2ItemDataStrc moo_pOtherItemData{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_size);
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StaticPathStrc original_pStaticPath{};
			D2UnitStrc original_pOtherItem{};
			D2ItemDataStrc original_pOtherItemData{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> original_ppItems(grid_size);
			int nInventoryRecordId = INVENTORYRECORD_AMAZON;
			BOOL bUnused = FALSE;
			uint8_t nPage = INVPAGE_INVENTORY;
			const char* szFile = __FILE__;
			int nLine = __LINE__;

			const auto setup_data = [owner_id, item_id, other_item_id, short_sword_id, ring_id, &grid_info](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pOwner,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StaticPathStrc& pStaticPath,
				D2UnitStrc& pOtherItem,
				D2ItemDataStrc& pOtherItemData,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				std::vector<D2UnitStrc*>& ppItems
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pOwner;
				pInventory.pFirstItem = &pOtherItem;
				pInventory.pLastItem = &pOtherItem;
				pInventory.dwItemCount = 1;
				pInventory.dwOwnerGuid = owner_id;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pOwner.dwUnitType = UNIT_PLAYER;
				pOwner.dwUnitId = owner_id;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = short_sword_id;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
				pItem.pStaticPath = &pStaticPath;

				// A ring in the top left corner of the inventory
				pOtherItem.dwUnitType = UNIT_ITEM;
				pOtherItem.dwClassId = ring_id;
				pOtherItem.dwUnitId = other_item_id;
				pOtherItem.pItemData = &pOtherItemData;
				pOtherItemData.dwOwnerGUID = owner_id;
				pOtherItemData.pExtraData.pParentInv = &pInventory;
				pOtherItemData.pExtraData.nNodePos = INVGRID_INVENTORY + 1;
				pOtherItemData.pExtraData.nNodePosOther = 1;

				pGrids[INVGRID_INVENTORY].pItem = &pOtherItem;
				pGrids[INVGRID_INVENTORY].pLastItem = &pOtherItem;
				pGrids[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems.data();
				ppItems[0] = &pOtherItem;
			};

			setup_data(moo_pInventory, moo_pOwner, moo_pItem, moo_pItemData, moo_pStaticPath, moo_pOtherItem, moo_pOtherItemData, moo_pGrids, moo_ppItems);
			setup_data(original_pInventory, original_pOwner, original_pItem, original_pItemData, original_pStaticPath, original_pOtherItem, original_pOtherItemData, original_pGrids, original_ppItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem, nInventoryRecordId, bUnused, nPage, szFile, nLine);
			const auto original_result = original(&original_pInventory, &original_pItem, nInventoryRecordId, bUnused, nPage, szFile, nLine);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pOtherItem, original_pOtherItem, "Comparing pOtherItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_INVENTORY], original_pGrids[INVGRID_INVENTORY], "Comparing inventory grid");
			check_grid_occupancy(moo_pGrids[INVGRID_INVENTORY], original_pGrids[INVGRID_INVENTORY]);
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<ItemsTxtFixture<NoopFixture>>, "D2Common.0x6FD8F250")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_PlaceItemInGrid, dll_base + 0x0004F250);

		SUBCASE("")
		{
			// Input data
			const auto owner_id = random_unsigned_integer();
			const auto item_id = random_unsigned_integer();
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto& grid_info = inventory_txt[INVENTORYRECORD_AMAZON].pGridInfo;
			const int grid_size = grid_info.nGridX * grid_info.nGridY;

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StaticPathStrc moo_pStaticPath{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc* moo_ppBeltItems[belt_grid_size]{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_size);
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StaticPathStrc original_pStaticPath{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc* original_ppBeltItems[belt_grid_size]{};
			std::vector<D2UnitStrc*> original_ppItems(grid_size);
			int nInventoryGrid = GENERATE(INVGRID_BODYLOC, INVGRID_BELT, INVGRID_INVENTORY);
			int nInventoryRecordId = INVENTORYRECORD_AMAZON;
			BOOL bUnused = FALSE;
			int nXPos = 0;
			int nYPos = 0;

			switch (nInventoryGrid)
			{
			case INVGRID_BODYLOC:
				nXPos = random_unsigned_integer(BODYLOC_HEAD, NUM_BODYLOC - 1);
				break;

			case INVGRID_BELT:
				nXPos = random_unsigned_integer(0, belt_grid_size - 1);
				break;

			default:
				nXPos = random_unsigned_integer(0, grid_info.nGridX - items_txt[short_sword_id].nInvWidth);
				nYPos = random_unsigned_integer(0, grid_info.nGridY - items_txt[short_sword_id].nInvHeight);
				break;
			}

			const auto setup_data = [owner_id, item_id, short_sword_id, &grid_info](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pOwner,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StaticPathStrc& pStaticPath,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc* (&ppBeltItems)[belt_grid_size],
				std::vector<D2UnitStrc*>& ppItems
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pOwner;
				pInventory.dwOwnerGuid = owner_id;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pOwner.dwUnitType = UNIT_PLAYER;
				pOwner.dwUnitId = owner_id;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = short_sword_id;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
				pItem.pStaticPath = &pStaticPath;
				pItemData.nInvPage = INVPAGE_NULL;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pGrids[INVGRID_BELT].nGridWidth = belt_grid_size;
				pGrids[INVGRID_BELT].nGridHeight = 1;
				pGrids[INVGRID_BELT].ppItems = ppBeltItems;

				pGrids[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems.data();
			};

			setup_data(moo_pInventory, moo_pOwner, moo_pItem, moo_pItemData, moo_pStaticPath, moo_pGrids, moo_ppBodyLocItems, moo_ppBeltItems, moo_ppItems);
			setup_data(original_pInventory, original_pOwner, original_pItem, original_pItemData, original_pStaticPath, original_pGrids, original_ppBodyLocItems, original_ppBeltItems, original_ppItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem, nXPos, nYPos, nInventoryGrid, nInventoryRecordId, bUnused);
			const auto original_result = original(&original_pInventory, &original_pItem, nXPos, nYPos, nInventoryGrid, nInventoryRecordId, bUnused);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pGrids[nInventoryGrid], original_pGrids[nInventoryGrid], "Comparing grid");
			check_grid_occupancy(moo_pGrids[nInventoryGrid], original_pGrids[nInventoryGrid]);
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<ItemsTxtFixture<NoopFixture>>, "D2Common.0x6FD8F600 (#10247)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_CanItemBePlaced, dll_base + 0x0004F600);

		SUBCASE("")
		{
			// Input data
			const auto quilted_armor_id = get_item_id(items_txt, items_record_count, ' iuq');
			const auto& grid_info = inventory_txt[INVENTORYRECORD_AMAZON].pGridInfo;
			const int grid_size = grid_info.nGridX * grid_info.nGridY;

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_size);
			D2UnitStrc moo_pOtherItems[2]{};
			D2UnitStrc* moo_ppExchangeItem{};
			unsigned int moo_pHoveredItems{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> original_ppItems(grid_size);
			D2UnitStrc original_pOtherItems[2]{};
			D2UnitStrc* original_ppExchangeItem{};
			unsigned int original_pHoveredItems{};
			int nInventoryRecordId = INVENTORYRECORD_AMAZON;
			uint8_t nPage = INVPAGE_INVENTORY;

			const auto setup_data = [quilted_armor_id, &grid_info](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc(&pOtherItems)[2]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = quilted_armor_id;

				pGrids[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems.data();

				// A 1x2 item at (2, 0) and a 1x1 item at (4, 1)
				pOtherItems[0].dwUnitType = UNIT_ITEM;
				pOtherItems[0].dwUnitId = 1;
				ppItems[2 + 0 * grid_info.nGridX] = &pOtherItems[0];
				ppItems[2 + 1 * grid_info.nGridX] = &pOtherItems[0];

				pOtherItems[1].dwUnitType = UNIT_ITEM;
				pOtherItems[1].dwUnitId = 2;
				ppItems[4 + 1 * grid_info.nGridX] = &pOtherItems[1];
			};

			setup_data(moo_pInventory, moo_pItem, moo_pGrids, moo_ppItems, moo_pOtherItems);
			setup_data(original_pInventory, original_pItem, original_pGrids, original_ppItems, original_pOtherItems);

			for (int nYPos = 0; nYPos < grid_info.nGridY; ++nYPos)
			{
				for (int nXPos = 0; nXPos < grid_info.nGridX; ++nXPos)
				{
					moo_ppExchangeItem = nullptr;
					moo_pHoveredItems = 0;
					original_ppExchangeItem = nullptr;
					original_pHoveredItems = 0;

					// Call both implementations
					const auto moo_result = sut(&moo_pInventory, &moo_pItem, nXPos, nYPos, nInventoryRecordId, &moo_ppExchangeItem, &moo_pHoveredItems, nPage);
					const auto original_result = original(&original_pInventory, &original_pItem, nXPos, nYPos, nInventoryRecordId, &original_ppExchangeItem, &original_pHoveredItems, nPage);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_ppExchangeItem, original_ppExchangeItem, "Comparing ppExchangeItem");
					MOO_CHECK_EQ(moo_pHoveredItems, original_pHoveredItems, "Comparing pHoveredItems");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<ItemsTxtFixture<NoopFixture>>, "D2Common.0x6FD8F780 (#10248)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_CanItemsBeExchanged, dll_base + 0x0004F780);

		SUBCASE("")
		{
			// Input data
			const auto quilted_armor_id = get_item_id(items_txt, items_record_count, ' iuq');
			const auto ring_id = get_item_id(items_txt, items_record_count, ' nir');
			const auto horadric_cube_id = get_item_id(items_txt, items_record_count, ' xob');
			const auto& grid_info = inventory_txt[INVENTORYRECORD_AMAZON].pGridInfo;
			const int grid_size = grid_info.nGridX * grid_info.nGridY;

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_size);
			D2UnitStrc moo_pOtherItems[2]{};
			D2UnitStrc* moo_ppExchangeItem{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> original_ppItems(grid_size);
			D2UnitStrc original_pOtherItems[2]{};
			D2UnitStrc* original_ppExchangeItem{};
			int nInventoryRecordId = INVENTORYRECORD_AMAZON;
			uint8_t nPage = INVPAGE_INVENTORY;
			BOOL bCheckIfCube = GENERATE(true, false);

			const auto setup_data = [quilted_armor_id, ring_id, horadric_cube_id, &grid_info](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc(&pOtherItems)[2]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = quilted_armor_id;

				pGrids[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems.data();

				// A ring at (2, 0) and a horadric cube at (4, 1)
				pOtherItems[0].dwUnitType = UNIT_ITEM;
				pOtherItems[0].dwClassId = ring_id;
				pOtherItems[0].dwUnitId = 1;
				ppItems[2 + 0 * grid_info.nGridX] = &pOtherItems[0];

				pOtherItems[1].dwUnitType = UNIT_ITEM;
				pOtherItems[1].dwClassId = horadric_cube_id;
				pOtherItems[1].dwUnitId = 2;
				ppItems[4 + 1 * grid_info.nGridX] = &pOtherItems[1];
			};

			setup_data(moo_pInventory, moo_pItem, moo_pGrids, moo_ppItems, moo_pOtherItems);
			setup_data(original_pInventory, original_pItem, original_pGrids, original_ppItems, original_pOtherItems);

			for (int nYPos = 0; nYPos < grid_info.nGridY; ++nYPos)
			{
				for (int nXPos = 0; nXPos < grid_info.nGridX; ++nXPos)
				{
					moo_ppExchangeItem = nullptr;
					original_ppExchangeItem = nullptr;

					// Call both implementations
					const auto moo_result = sut(&moo_pInventory, &moo_pItem, nXPos, nYPos, nInventoryRecordId, &moo_ppExchangeItem, nPage, bCheckIfCube);
					const auto original_result = original(&original_pInventory, &original_pItem, nXPos, nYPos, nInventoryRecordId, &original_ppExchangeItem, nPage, bCheckIfCube);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_ppExchangeItem, original_ppExchangeItem, "Comparing ppExchangeItem");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<ItemsTxtFixture<NoopFixture>>, "D2Common.0x6FD8F930 (#10249)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_PlaceItemAtInventoryPage, dll_base + 0x0004F930);

		SUBCASE("")
		{
			// Input data
			const auto owner_id = random_unsigned_integer();
			const auto item_id = random_unsigned_integer();
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto& grid_info = inventory_txt[INVENTORYRECORD_AMAZON].pGridInfo;
			const int grid_size = grid_info.nGridX * grid_info.nGridY;
			const int max_x = grid_info.nGridX - items_txt[short_sword_id].nInvWidth;
			const int max_y = grid_info.nGridY - items_txt[short_sword_id].nInvHeight;
			// Also place the item partially outside of the grid
			const auto is_inside = GENERATE(true, false);

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StaticPathStrc moo_pStaticPath{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_size);
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StaticPathStrc original_pStaticPath{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> original_ppItems(grid_size);
			int nXPos = is_inside ? random_unsigned_integer(0, max_x) : max_x + 1;
			int nYPos = random_unsigned_integer(0, max_y);
			int nInventoryRecordId = INVENTORYRECORD_AMAZON;
			BOOL bUnused = FALSE;
			uint8_t nPage = INVPAGE_INVENTORY;

			const auto setup_data = [owner_id, item_id, short_sword_id, &grid_info](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pOwner,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StaticPathStrc& pStaticPath,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				std::vector<D2UnitStrc*>& ppItems
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pOwner;
				pInventory.dwOwnerGuid = owner_id;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pOwner.dwUnitType = UNIT_PLAYER;
				pOwner.dwUnitId = owner_id;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = short_sword_id;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
				pItem.pStaticPath = &pStaticPath;
				pItemData.nInvPage = INVPAGE_NULL;

				pGrids[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems.data();
			};

			setup_data(moo_pInventory, moo_pOwner, moo_pItem, moo_pItemData, moo_pStaticPath, moo_pGrids, moo_ppItems);
			setup_data(original_pInventory, original_pOwner, original_pItem, original_pItemData, original_pStaticPath, original_pGrids, original_ppItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem, nXPos, nYPos, nInventoryRecordId, bUnused, nPage);
			const auto original_result = original(&original_pInventory, &original_pItem, nXPos, nYPos, nInventoryRecordId, bUnused, nPage);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_INVENTORY], original_pGrids[INVGRID_INVENTORY], "Comparing inventory grid");
			check_grid_occupancy(moo_pGrids[INVGRID_INVENTORY], original_pGrids[INVGRID_INVENTORY]);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8F970 (#10250)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_Return, dll_base + 0x0004F970);
		
		SUBCASE("")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2InventoryStrc original_pInventory{};
			char szFile{};
			int nLine{};
			int nX{};
			int nY{};
			int nInventoryRecordId{};
			BOOL bClient{};
			uint8_t nPage{};

			// Call both implementations
			sut(&szFile, nLine, &moo_pInventory, nX, nY, nInventoryRecordId, bClient, nPage);
			original(&szFile, nLine, &original_pInventory, nX, nY, nInventoryRecordId, bClient, nPage);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");

			// NOTE: This function just returns so there's nothing to observe here anyway
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<NoopFixture>, "D2Common.0x6FD8F980 (#10252)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetItemFromInventoryPage, dll_base + 0x0004F980);

		SUBCASE("")
		{
			// Input data
			const auto& grid_info = inventory_txt[INVENTORYRECORD_AMAZON].pGridInfo;
			const int grid_size = grid_info.nGridX * grid_info.nGridY;

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_size);
			D2UnitStrc moo_pItems[2]{};
			D2StaticPathStrc moo_pStaticPaths[2]{};
			int moo_pX{};
			int moo_pY{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> original_ppItems(grid_size);
			D2UnitStrc original_pItems[2]{};
			D2StaticPathStrc original_pStaticPaths[2]{};
			int original_pX{};
			int original_pY{};
			int nInventoryRecordId = INVENTORYRECORD_AMAZON;
			uint8_t nPage = INVPAGE_INVENTORY;

			const auto setup_data = [&grid_info](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc(&pItems)[2],
				D2StaticPathStrc(&pStaticPaths)[2]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pGrids[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems.data();

				// A 1x3 item at (1, 0) and a 1x1 item at (5, 2)
				pItems[0].dwUnitType = UNIT_ITEM;
				pItems[0].dwUnitId = 1;
				pItems[0].pStaticPath = &pStaticPaths[0];
				pStaticPaths[0].tGameCoords.nX = 1;
				pStaticPaths[0].tGameCoords.nY = 0;
				for (auto y = 0; y < 3; ++y)
				{
					ppItems[1 + y * grid_info.nGridX] = &pItems[0];
				}

				pItems[1].dwUnitType = UNIT_ITEM;
				pItems[1].dwUnitId = 2;
				pItems[1].pStaticPath = &pStaticPaths[1];
				pStaticPaths[1].tGameCoords.nX = 5;
				pStaticPaths[1].tGameCoords.nY = 2;
				ppItems[5 + 2 * grid_info.nGridX] = &pItems[1];
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppItems, moo_pItems, moo_pStaticPaths);
			setup_data(original_pInventory, original_pGrids, original_ppItems, original_pItems, original_pStaticPaths);

			for (int nGridY = 0; nGridY < grid_info.nGridY; ++nGridY)
			{
				for (int nGridX = 0; nGridX < grid_info.nGridX; ++nGridX)
				{
					moo_pX = -1;
					moo_pY = -1;
					original_pX = -1;
					original_pY = -1;

					// Call both implementations
					const auto moo_result = sut(&moo_pInventory, nGridX, nGridY, &moo_pX, &moo_pY, nInventoryRecordId, nPage);
					const auto original_result = original(&original_pInventory, nGridX, nGridY, &original_pX, &original_pY, nInventoryRecordId, nPage);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
					MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD8FAB0 (#10253)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_PlaceItemInBodyLoc, dll_base + 0x0004FAB0);

		SUBCASE("")
		{
			// Input data
			const auto item_id = random_unsigned_integer();
			const auto item_owner_id = random_unsigned_integer();
			const auto cap_id = get_item_id(items_txt, items_record_count, ' pac');

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StaticPathStrc moo_pStaticPath{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StaticPathStrc original_pStaticPath{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			int nBodyLoc = GENERATE(BODYLOC_NONE, BODYLOC_HEAD, BODYLOC_NECK, BODYLOC_TORSO, BODYLOC_RARM, BODYLOC_LARM, BODYLOC_RRIN, BODYLOC_LRIN, BODYLOC_BELT, BODYLOC_FEET, BODYLOC_GLOVES, BODYLOC_SWRARM, BODYLOC_SWLARM, NUM_BODYLOC);

			const auto setup_data = [item_id, item_owner_id, cap_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StaticPathStrc& pStaticPath,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = cap_id;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
				pItem.pStaticPath = &pStaticPath;
				pItemData.dwOwnerGUID = item_owner_id;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData, moo_pStaticPath, moo_pGrids, moo_ppBodyLocItems);
			setup_data(original_pInventory, original_pItem, original_pItemData, original_pStaticPath, original_pGrids, original_ppBodyLocItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem, nBodyLoc);
			const auto original_result = original(&original_pInventory, &original_pItem, nBodyLoc);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_BODYLOC], original_pGrids[INVGRID_BODYLOC], "Comparing body location grid");
			check_grid_occupancy(moo_pGrids[INVGRID_BODYLOC], original_pGrids[INVGRID_BODYLOC]);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8FAE0 (#10257)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetItemFromBodyLoc, dll_base + 0x0004FAE0);

		SUBCASE("")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pItems[4]{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pItems[4]{};

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc(&pItems)[4]
			) {
				constexpr int body_locs[4] = { BODYLOC_HEAD, BODYLOC_RARM, BODYLOC_LARM, BODYLOC_FEET };

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				for (auto i = 0; i < 4; ++i)
				{
					pItems[i].dwUnitType = UNIT_ITEM;
					pItems[i].dwUnitId = i + 1;
					ppBodyLocItems[body_locs[i]] = &pItems[i];
				}
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pItems);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pItems);

			for (int nBodyLoc = -1; nBodyLoc <= NUM_BODYLOC; ++nBodyLoc)
			{
				// Call both implementations
				const auto moo_result = sut(&moo_pInventory, nBodyLoc);
				const auto original_result = original(&original_pInventory, nBodyLoc);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD8FB20 (#10255)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetSecondWieldingWeapon, dll_base + 0x0004FB20);

		SUBCASE("")
		{
			// Input data
			const auto short_bow_id = get_item_id(items_txt, items_record_count, ' wbs');
			const auto arrows_id = get_item_id(items_txt, items_record_count, ' vqa');

			D2UnitStrc moo_pPlayer{};
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pRightHandItem{};
			D2UnitStrc moo_pLeftHandItem{};
			D2UnitStrc* moo_ppItem{};
			D2UnitStrc original_pPlayer{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pRightHandItem{};
			D2UnitStrc original_pLeftHandItem{};
			D2UnitStrc* original_ppItem{};
			int nBodyLoc = GENERATE(BODYLOC_HEAD, BODYLOC_RARM, BODYLOC_LARM);

			const auto setup_data = [short_bow_id, arrows_id](
				D2UnitStrc& pPlayer,
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pRightHandItem,
				D2UnitStrc& pLeftHandItem
			) {
				pPlayer.dwUnitType = UNIT_PLAYER;
				pPlayer.dwClassId = PCLASS_AMAZON;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				// A two handed bow in the right hand and arrows in the left hand
				pRightHandItem.dwUnitType = UNIT_ITEM;
				pRightHandItem.dwClassId = short_bow_id;
				pRightHandItem.dwUnitId = 1;
				ppBodyLocItems[BODYLOC_RARM] = &pRightHandItem;

				pLeftHandItem.dwUnitType = UNIT_ITEM;
				pLeftHandItem.dwClassId = arrows_id;
				pLeftHandItem.dwUnitId = 2;
				ppBodyLocItems[BODYLOC_LARM] = &pLeftHandItem;
			};

			setup_data(moo_pPlayer, moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pRightHandItem, moo_pLeftHandItem);
			setup_data(original_pPlayer, original_pInventory, original_pGrids, original_ppBodyLocItems, original_pRightHandItem, original_pLeftHandItem);

			// Call both implementations
			sut(&moo_pPlayer, &moo_pInventory, &moo_ppItem, nBodyLoc);
			original(&original_pPlayer, &original_pInventory, &original_ppItem, nBodyLoc);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_ppItem, original_ppItem, "Comparing ppItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD8FBB0 (#10256)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_CheckEquipmentForWeaponByClass, dll_base + 0x0004FBB0);

		SUBCASE("")
		{
			// Input data
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto short_bow_id = get_item_id(items_txt, items_record_count, ' wbs');

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pRightHandItem{};
			D2UnitStrc moo_pLeftHandItem{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pRightHandItem{};
			D2UnitStrc original_pLeftHandItem{};
			int nWeaponClass = GENERATE(' sh1', ' wob', ' th2', ' fts');

			const auto setup_data = [short_sword_id, short_bow_id](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pRightHandItem,
				D2UnitStrc& pLeftHandItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pRightHandItem.dwUnitType = UNIT_ITEM;
				pRightHandItem.dwClassId = short_sword_id;
				pRightHandItem.dwUnitId = 1;
				ppBodyLocItems[BODYLOC_RARM] = &pRightHandItem;

				pLeftHandItem.dwUnitType = UNIT_ITEM;
				pLeftHandItem.dwClassId = short_bow_id;
				pLeftHandItem.dwUnitId = 2;
				ppBodyLocItems[BODYLOC_LARM] = &pLeftHandItem;
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pRightHandItem, moo_pLeftHandItem);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pRightHandItem, original_pLeftHandItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nWeaponClass);
			const auto original_result = original(&original_pInventory, nWeaponClass);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD8FC60 (#10258)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetLeftHandWeapon, dll_base + 0x0004FC60);

		SUBCASE("")
		{
			// Input data
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto left_hand_item_code = GENERATE(' xah', ' cub');
			const auto left_hand_item_id = get_item_id(items_txt, items_record_count, left_hand_item_code);
			const D2UnitGUID left_item_guid = GENERATE(1u, 2u, 3u, D2UnitInvalidGUID);

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pRightHandItem{};
			D2UnitStrc moo_pLeftHandItem{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pRightHandItem{};
			D2UnitStrc original_pLeftHandItem{};

			const auto setup_data = [short_sword_id, left_hand_item_id, left_item_guid](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pRightHandItem,
				D2UnitStrc& pLeftHandItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.dwLeftItemGUID = left_item_guid;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pRightHandItem.dwUnitType = UNIT_ITEM;
				pRightHandItem.dwClassId = short_sword_id;
				pRightHandItem.dwUnitId = 1;
				ppBodyLocItems[BODYLOC_RARM] = &pRightHandItem;

				pLeftHandItem.dwUnitType = UNIT_ITEM;
				pLeftHandItem.dwClassId = left_hand_item_id;
				pLeftHandItem.dwUnitId = 2;
				ppBodyLocItems[BODYLOC_LARM] = &pLeftHandItem;
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pRightHandItem, moo_pLeftHandItem);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pRightHandItem, original_pLeftHandItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD8FD10 (#11301)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetSecondaryWeapon, dll_base + 0x0004FD10);

		SUBCASE("")
		{
			// Input data
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto left_hand_item_code = GENERATE(' xah', ' cub');
			const auto left_hand_item_id = get_item_id(items_txt, items_record_count, left_hand_item_code);
			const D2UnitGUID left_item_guid = GENERATE(1u, 2u, 3u, D2UnitInvalidGUID);

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pRightHandItem{};
			D2UnitStrc moo_pLeftHandItem{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pRightHandItem{};
			D2UnitStrc original_pLeftHandItem{};

			const auto setup_data = [short_sword_id, left_hand_item_id, left_item_guid](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pRightHandItem,
				D2UnitStrc& pLeftHandItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.dwLeftItemGUID = left_item_guid;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pRightHandItem.dwUnitType = UNIT_ITEM;
				pRightHandItem.dwClassId = short_sword_id;
				pRightHandItem.dwUnitId = 1;
				ppBodyLocItems[BODYLOC_RARM] = &pRightHandItem;

				pLeftHandItem.dwUnitType = UNIT_ITEM;
				pLeftHandItem.dwClassId = left_hand_item_id;
				pLeftHandItem.dwUnitId = 2;
				ppBodyLocItems[BODYLOC_LARM] = &pLeftHandItem;
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pRightHandItem, moo_pLeftHandItem);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pRightHandItem, original_pLeftHandItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD8FDD0 (#10259)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetCompositItem, dll_base + 0x0004FDD0);

		SUBCASE("")
		{
			// Input data
			const int item_ids[4] =
			{
				get_item_id(items_txt, items_record_count, ' pac'),
				get_item_id(items_txt, items_record_count, ' iuq'),
				get_item_id(items_txt, items_record_count, ' dss'),
				get_item_id(items_txt, items_record_count, ' cub'),
			};
			// The short sword in the right hand may be the left hand weapon
			const D2UnitGUID left_item_guid = GENERATE(3u, D2UnitInvalidGUID);

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pItems[4]{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pItems[4]{};
			int nComponent = GENERATE(COMPOSIT_HEAD, COMPOSIT_TORSO, COMPOSIT_RIGHTHAND, COMPOSIT_LEFTHAND, COMPOSIT_SHIELD);

			const auto setup_data = [&item_ids, left_item_guid](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc(&pItems)[4]
			) {
				constexpr int body_locs[4] = { BODYLOC_HEAD, BODYLOC_TORSO, BODYLOC_RARM, BODYLOC_LARM };

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.dwLeftItemGUID = left_item_guid;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				for (auto i = 0; i < 4; ++i)
				{
					pItems[i].dwUnitType = UNIT_ITEM;
					pItems[i].dwClassId = item_ids[i];
					pItems[i].dwUnitId = i + 1;
					ppBodyLocItems[body_locs[i]] = &pItems[i];
				}
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pItems);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nComponent);
			const auto original_result = original(&original_pInventory, nComponent);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8FE80 (#10260)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetBodyLocFromEquippedItem, dll_base + 0x0004FE80);

		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer(0, NUM_BODYLOC - 1);
			const auto item_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2StaticPathStrc moo_pStaticPath{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2StaticPathStrc original_pStaticPath{};

			const auto setup_data = [x, item_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2StaticPathStrc& pStaticPath
			) {
				pInventory.dwSignature = D2C_InventoryHeader;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = item_id;
				pItem.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = x;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pStaticPath);
			setup_data(original_pInventory, original_pItem, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem);
			const auto original_result = original(&original_pInventory, &original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8FED0 (#11278)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetItemsXPosition, dll_base + 0x0004FED0);
		
		SUBCASE("")
		{
			// Input data
			const auto x = random_unsigned_integer(0, 11);
			const auto item_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2StaticPathStrc moo_pStaticPath{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2StaticPathStrc original_pStaticPath{};

			const auto setup_data = [x, item_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2StaticPathStrc& pStaticPath
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = item_id;
				pItem.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = x;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pStaticPath);
			setup_data(original_pInventory, original_pItem, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem);
			const auto original_result = original(&original_pInventory, &original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8FF20 (#10261)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_SetCursorItem, dll_base + 0x0004FF20);

		SUBCASE("set cursor item")
		{
			// Input data
			const auto item_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [item_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pInventory.dwSignature = D2C_InventoryHeader;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData);
			setup_data(original_pInventory, original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pInventory, &moo_pItem);
			original(&original_pInventory, &original_pItem);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}

		SUBCASE("remove cursor item")
		{
			// Input data
			const auto cursor_item_id = random_unsigned_integer();
			const auto owner_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pCursorItem{};
			D2ItemDataStrc moo_pCursorItemData{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pCursorItem{};
			D2ItemDataStrc original_pCursorItemData{};

			const auto setup_data = [cursor_item_id, owner_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pCursorItem,
				D2ItemDataStrc& pCursorItemData
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pCursorItem = &pCursorItem;

				pCursorItem.dwUnitType = UNIT_ITEM;
				pCursorItem.dwUnitId = cursor_item_id;
				pCursorItem.pItemData = &pCursorItemData;
				pCursorItemData.dwOwnerGUID = owner_id;
				pCursorItemData.pExtraData.pParentInv = &pInventory;
			};

			setup_data(moo_pInventory, moo_pCursorItem, moo_pCursorItemData);
			setup_data(original_pInventory, original_pCursorItem, original_pCursorItemData);

			// Call both implementations
			sut(&moo_pInventory, nullptr);
			original(&original_pInventory, nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pCursorItem, original_pCursorItem, "Comparing pCursorItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8FF80 (#10262)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetCursorItem, dll_base + 0x0004FF80);
		
		SUBCASE("")
		{
			// Input data
			const auto item_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pCursorItem{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pCursorItem{};

			const auto setup_data = [item_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pCursorItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pCursorItem = &pCursorItem;
				pCursorItem.dwUnitId = item_id;
			};

			setup_data(moo_pInventory, moo_pCursorItem);
			setup_data(original_pInventory, original_pCursorItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD8FFA0 (#10263)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_FindBackPackItemForStack, dll_base + 0x0004FFA0);

		SUBCASE("")
		{
			// Input data
			static constexpr int grid_width = 10;
			static constexpr int grid_height = 4;

			const auto bolts_id = get_item_id(items_txt, items_record_count, ' vqc');
			const auto arrows_id = get_item_id(items_txt, items_record_count, ' vqa');
			// Magic arrows can't be stacked with normal arrows
			const auto check_item_quality = GENERATE(ITEMQUAL_NORMAL, ITEMQUAL_MAGIC);

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* moo_ppItems[grid_width * grid_height]{};
			D2UnitStrc moo_pFirstItem{};
			D2ItemDataStrc moo_pFirstItemData{};
			D2UnitStrc moo_pCheckItem{};
			D2ItemDataStrc moo_pCheckItemData{};
			D2UnitStrc moo_pLastItem{};
			D2ItemDataStrc moo_pLastItemData{};
			D2UnitStrc moo_pStackable{};
			D2ItemDataStrc moo_pStackableData{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* original_ppItems[grid_width * grid_height]{};
			D2UnitStrc original_pFirstItem{};
			D2ItemDataStrc original_pFirstItemData{};
			D2UnitStrc original_pCheckItem{};
			D2ItemDataStrc original_pCheckItemData{};
			D2UnitStrc original_pLastItem{};
			D2ItemDataStrc original_pLastItemData{};
			D2UnitStrc original_pStackable{};
			D2ItemDataStrc original_pStackableData{};

			const auto setup_data = [bolts_id, arrows_id, check_item_quality](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				D2UnitStrc* (&ppItems)[grid_width * grid_height],
				D2UnitStrc& pFirstItem,
				D2ItemDataStrc& pFirstItemData,
				D2UnitStrc& pCheckItem,
				D2ItemDataStrc& pCheckItemData,
				D2UnitStrc& pLastItem,
				D2ItemDataStrc& pLastItemData,
				D2UnitStrc& pStackable,
				D2ItemDataStrc& pStackableData
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				// The grid contains bolts, followed by the check item and the last item (both arrows)
				pGrids[INVGRID_INVENTORY].pItem = &pFirstItem;
				pGrids[INVGRID_INVENTORY].pLastItem = &pLastItem;
				pGrids[INVGRID_INVENTORY].nGridWidth = grid_width;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_height;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems;

				pFirstItem.dwUnitType = UNIT_ITEM;
				pFirstItem.dwClassId = bolts_id;
				pFirstItem.dwUnitId = 1;
				pFirstItem.pItemData = &pFirstItemData;
				pFirstItemData.dwQualityNo = ITEMQUAL_NORMAL;
				pFirstItemData.pExtraData.pNextGridItem = &pCheckItem;

				pCheckItem.dwUnitType = UNIT_ITEM;
				pCheckItem.dwClassId = arrows_id;
				pCheckItem.dwUnitId = 2;
				pCheckItem.pItemData = &pCheckItemData;
				pCheckItemData.dwQualityNo = check_item_quality;
				pCheckItemData.pExtraData.pPreviousGridItem = &pFirstItem;
				pCheckItemData.pExtraData.pNextGridItem = &pLastItem;

				pLastItem.dwUnitType = UNIT_ITEM;
				pLastItem.dwClassId = arrows_id;
				pLastItem.dwUnitId = 3;
				pLastItem.pItemData = &pLastItemData;
				pLastItemData.dwQualityNo = ITEMQUAL_NORMAL;
				pLastItemData.pExtraData.pPreviousGridItem = &pCheckItem;

				pStackable.dwUnitType = UNIT_ITEM;
				pStackable.dwClassId = arrows_id;
				pStackable.dwUnitId = 4;
				pStackable.pItemData = &pStackableData;
				pStackableData.dwQualityNo = ITEMQUAL_NORMAL;
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppItems, moo_pFirstItem, moo_pFirstItemData, moo_pCheckItem, moo_pCheckItemData, moo_pLastItem, moo_pLastItemData, moo_pStackable, moo_pStackableData);
			setup_data(original_pInventory, original_pGrids, original_ppItems, original_pFirstItem, original_pFirstItemData, original_pCheckItem, original_pCheckItemData, original_pLastItem, original_pLastItemData, original_pStackable, original_pStackableData);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pStackable, &moo_pCheckItem);
			const auto original_result = original(&original_pInventory, &original_pStackable, &original_pCheckItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pStackable, original_pStackable, "Comparing pStackable");
			MOO_CHECK_EQ(moo_pCheckItem, original_pCheckItem, "Comparing pCheckItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_INVENTORY], original_pGrids[INVGRID_INVENTORY], "Comparing inventory grid");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD90080 (#10264)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_FindEquippedItemForStack, dll_base + 0x00050080);

		SUBCASE("")
		{
			// Input data
			const auto bolts_id = get_item_id(items_txt, items_record_count, ' vqc');
			const auto arrows_id = get_item_id(items_txt, items_record_count, ' vqa');
			// Magic arrows can't be stacked with normal arrows
			const auto check_item_quality = GENERATE(ITEMQUAL_NORMAL, ITEMQUAL_MAGIC);

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pFirstItem{};
			D2ItemDataStrc moo_pFirstItemData{};
			D2UnitStrc moo_pCheckItem{};
			D2ItemDataStrc moo_pCheckItemData{};
			D2UnitStrc moo_pLastItem{};
			D2ItemDataStrc moo_pLastItemData{};
			D2UnitStrc moo_pStackable{};
			D2ItemDataStrc moo_pStackableData{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pFirstItem{};
			D2ItemDataStrc original_pFirstItemData{};
			D2UnitStrc original_pCheckItem{};
			D2ItemDataStrc original_pCheckItemData{};
			D2UnitStrc original_pLastItem{};
			D2ItemDataStrc original_pLastItemData{};
			D2UnitStrc original_pStackable{};
			D2ItemDataStrc original_pStackableData{};

			const auto setup_data = [bolts_id, arrows_id, check_item_quality](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pFirstItem,
				D2ItemDataStrc& pFirstItemData,
				D2UnitStrc& pCheckItem,
				D2ItemDataStrc& pCheckItemData,
				D2UnitStrc& pLastItem,
				D2ItemDataStrc& pLastItemData,
				D2UnitStrc& pStackable,
				D2ItemDataStrc& pStackableData
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				// The grid contains bolts, followed by the check item and the last item (both arrows)
				pGrids[INVGRID_BODYLOC].pItem = &pFirstItem;
				pGrids[INVGRID_BODYLOC].pLastItem = &pLastItem;
				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pFirstItem.dwUnitType = UNIT_ITEM;
				pFirstItem.dwClassId = bolts_id;
				pFirstItem.dwUnitId = 1;
				pFirstItem.pItemData = &pFirstItemData;
				pFirstItemData.dwQualityNo = ITEMQUAL_NORMAL;
				pFirstItemData.pExtraData.pNextGridItem = &pCheckItem;
				ppBodyLocItems[BODYLOC_LARM] = &pFirstItem;

				pCheckItem.dwUnitType = UNIT_ITEM;
				pCheckItem.dwClassId = arrows_id;
				pCheckItem.dwUnitId = 2;
				pCheckItem.pItemData = &pCheckItemData;
				pCheckItemData.dwQualityNo = check_item_quality;
				pCheckItemData.pExtraData.pPreviousGridItem = &pFirstItem;
				pCheckItemData.pExtraData.pNextGridItem = &pLastItem;
				ppBodyLocItems[BODYLOC_SWRARM] = &pCheckItem;

				pLastItem.dwUnitType = UNIT_ITEM;
				pLastItem.dwClassId = arrows_id;
				pLastItem.dwUnitId = 3;
				pLastItem.pItemData = &pLastItemData;
				pLastItemData.dwQualityNo = ITEMQUAL_NORMAL;
				pLastItemData.pExtraData.pPreviousGridItem = &pCheckItem;
				ppBodyLocItems[BODYLOC_SWLARM] = &pLastItem;

				pStackable.dwUnitType = UNIT_ITEM;
				pStackable.dwClassId = arrows_id;
				pStackable.dwUnitId = 4;
				pStackable.pItemData = &pStackableData;
				pStackableData.dwQualityNo = ITEMQUAL_NORMAL;
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pFirstItem, moo_pFirstItemData, moo_pCheckItem, moo_pCheckItemData, moo_pLastItem, moo_pLastItemData, moo_pStackable, moo_pStackableData);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pFirstItem, original_pFirstItemData, original_pCheckItem, original_pCheckItemData, original_pLastItem, original_pLastItemData, original_pStackable, original_pStackableData);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pStackable, &moo_pCheckItem);
			const auto original_result = original(&original_pInventory, &original_pStackable, &original_pCheckItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pStackable, original_pStackable, "Comparing pStackable");
			MOO_CHECK_EQ(moo_pCheckItem, original_pCheckItem, "Comparing pCheckItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_BODYLOC], original_pGrids[INVGRID_BODYLOC], "Comparing body location grid");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD90130 (#10265)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_FindFillableBook, dll_base + 0x00050130);

		SUBCASE("")
		{
			// Input data
			static constexpr int grid_width = 10;
			static constexpr int grid_height = 4;

			const auto identify_book_id = get_item_id(items_txt, items_record_count, ' kbi');
			const auto town_portal_book_id = get_item_id(items_txt, items_record_count, ' kbt');
			const auto town_portal_scroll_id = get_item_id(items_txt, items_record_count, ' cst');
			// Only books with the same suffix as the scrolls can be filled
			const auto scrolls_suffix = GENERATE(1, 2);

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* moo_ppItems[grid_width * grid_height]{};
			D2UnitStrc moo_pFirstItem{};
			D2ItemDataStrc moo_pFirstItemData{};
			D2UnitStrc moo_pCheckItem{};
			D2ItemDataStrc moo_pCheckItemData{};
			D2UnitStrc moo_pLastItem{};
			D2ItemDataStrc moo_pLastItemData{};
			D2UnitStrc moo_pScrolls{};
			D2ItemDataStrc moo_pScrollsData{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* original_ppItems[grid_width * grid_height]{};
			D2UnitStrc original_pFirstItem{};
			D2ItemDataStrc original_pFirstItemData{};
			D2UnitStrc original_pCheckItem{};
			D2ItemDataStrc original_pCheckItemData{};
			D2UnitStrc original_pLastItem{};
			D2ItemDataStrc original_pLastItemData{};
			D2UnitStrc original_pScrolls{};
			D2ItemDataStrc original_pScrollsData{};

			const auto setup_data = [identify_book_id, town_portal_book_id, town_portal_scroll_id, scrolls_suffix](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				D2UnitStrc* (&ppItems)[grid_width * grid_height],
				D2UnitStrc& pFirstItem,
				D2ItemDataStrc& pFirstItemData,
				D2UnitStrc& pCheckItem,
				D2ItemDataStrc& pCheckItemData,
				D2UnitStrc& pLastItem,
				D2ItemDataStrc& pLastItemData,
				D2UnitStrc& pScrolls,
				D2ItemDataStrc& pScrollsData
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				// The grid contains an identify book, followed by the check item and the last item (both town portal books)
				pGrids[INVGRID_INVENTORY].pItem = &pFirstItem;
				pGrids[INVGRID_INVENTORY].pLastItem = &pLastItem;
				pGrids[INVGRID_INVENTORY].nGridWidth = grid_width;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_height;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems;

				pFirstItem.dwUnitType = UNIT_ITEM;
				pFirstItem.dwClassId = identify_book_id;
				pFirstItem.dwUnitId = 1;
				pFirstItem.pItemData = &pFirstItemData;
				pFirstItemData.wMagicSuffix[0] = 1;
				pFirstItemData.pExtraData.pNextGridItem = &pCheckItem;

				pCheckItem.dwUnitType = UNIT_ITEM;
				pCheckItem.dwClassId = town_portal_book_id;
				pCheckItem.dwUnitId = 2;
				pCheckItem.pItemData = &pCheckItemData;
				pCheckItemData.wMagicSuffix[0] = 2;
				pCheckItemData.pExtraData.pPreviousGridItem = &pFirstItem;
				pCheckItemData.pExtraData.pNextGridItem = &pLastItem;

				pLastItem.dwUnitType = UNIT_ITEM;
				pLastItem.dwClassId = town_portal_book_id;
				pLastItem.dwUnitId = 3;
				pLastItem.pItemData = &pLastItemData;
				pLastItemData.wMagicSuffix[0] = 2;
				pLastItemData.pExtraData.pPreviousGridItem = &pCheckItem;

				pScrolls.dwUnitType = UNIT_ITEM;
				pScrolls.dwClassId = town_portal_scroll_id;
				pScrolls.dwUnitId = 4;
				pScrolls.pItemData = &pScrollsData;
				pScrollsData.wMagicSuffix[0] = static_cast<uint16_t>(scrolls_suffix);
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppItems, moo_pFirstItem, moo_pFirstItemData, moo_pCheckItem, moo_pCheckItemData, moo_pLastItem, moo_pLastItemData, moo_pScrolls, moo_pScrollsData);
			setup_data(original_pInventory, original_pGrids, original_ppItems, original_pFirstItem, original_pFirstItemData, original_pCheckItem, original_pCheckItemData, original_pLastItem, original_pLastItemData, original_pScrolls, original_pScrollsData);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pScrolls, &moo_pCheckItem);
			const auto original_result = original(&original_pInventory, &original_pScrolls, &original_pCheckItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pScrolls, original_pScrolls, "Comparing pScrolls");
			MOO_CHECK_EQ(moo_pCheckItem, original_pCheckItem, "Comparing pCheckItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_INVENTORY], original_pGrids[INVGRID_INVENTORY], "Comparing inventory grid");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD90230 (#10266)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_PlaceItemInBeltSlot, dll_base + 0x00050230);

		SUBCASE("")
		{
			// Input data
			const auto item_id = random_unsigned_integer();
			const auto item_owner_id = random_unsigned_integer();
			const auto item_code = GENERATE(' 1ph', ' iuq');
			const auto item_class_id = get_item_id(items_txt, items_record_count, item_code);

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StaticPathStrc moo_pStaticPath{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* moo_ppBeltItems[belt_grid_size]{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StaticPathStrc original_pStaticPath{};
			D2InventoryGridStrc original_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* original_ppBeltItems[belt_grid_size]{};
			int nSlot = GENERATE(-1, 0, 5, belt_grid_size - 1, belt_grid_size);

			const auto setup_data = [item_id, item_owner_id, item_class_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StaticPathStrc& pStaticPath,
				D2InventoryGridStrc(&pGrids)[INVGRID_BELT + 1],
				D2UnitStrc* (&ppBeltItems)[belt_grid_size]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BELT + 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = item_class_id;
				pItem.dwUnitId = item_id;
				pItem.pItemData = &pItemData;
				pItem.pStaticPath = &pStaticPath;
				pItemData.dwOwnerGUID = item_owner_id;

				pGrids[INVGRID_BELT].nGridWidth = belt_grid_size;
				pGrids[INVGRID_BELT].nGridHeight = 1;
				pGrids[INVGRID_BELT].ppItems = ppBeltItems;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData, moo_pStaticPath, moo_pGrids, moo_ppBeltItems);
			setup_data(original_pInventory, original_pItem, original_pItemData, original_pStaticPath, original_pGrids, original_ppBeltItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem, nSlot);
			const auto original_result = original(&original_pInventory, &original_pItem, nSlot);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_BELT], original_pGrids[INVGRID_BELT], "Comparing belt grid");
			check_grid_occupancy(moo_pGrids[INVGRID_BELT], original_pGrids[INVGRID_BELT]);
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD902B0 (#10268)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_HasSimilarPotionInBelt, dll_base + 0x000502B0);

		SUBCASE("")
		{
			// Input data
			const auto healing_potion_id = get_item_id(items_txt, items_record_count, ' 2ph');
			const auto rejuvenation_potion_id = get_item_id(items_txt, items_record_count, ' svr');
			const auto potion_code = GENERATE(' 1ph', ' 1pm', ' lvr', ' csi');
			const auto potion_id = get_item_id(items_txt, items_record_count, potion_code);

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pPotion{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* moo_ppBeltItems[belt_grid_size]{};
			D2UnitStrc moo_pBeltItems[2]{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pPotion{};
			D2InventoryGridStrc original_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* original_ppBeltItems[belt_grid_size]{};
			D2UnitStrc original_pBeltItems[2]{};

			const auto setup_data = [healing_potion_id, rejuvenation_potion_id, potion_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pPotion,
				D2InventoryGridStrc(&pGrids)[INVGRID_BELT + 1],
				D2UnitStrc* (&ppBeltItems)[belt_grid_size],
				D2UnitStrc(&pBeltItems)[2]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BELT + 1;

				pPotion.dwUnitType = UNIT_ITEM;
				pPotion.dwClassId = potion_id;

				pGrids[INVGRID_BELT].nGridWidth = belt_grid_size;
				pGrids[INVGRID_BELT].nGridHeight = 1;
				pGrids[INVGRID_BELT].ppItems = ppBeltItems;

				// A healing potion in the first and a rejuvenation potion in the second column
				pBeltItems[0].dwUnitType = UNIT_ITEM;
				pBeltItems[0].dwClassId = healing_potion_id;
				pBeltItems[0].dwUnitId = 1;
				ppBeltItems[0] = &pBeltItems[0];

				pBeltItems[1].dwUnitType = UNIT_ITEM;
				pBeltItems[1].dwClassId = rejuvenation_potion_id;
				pBeltItems[1].dwUnitId = 2;
				ppBeltItems[1] = &pBeltItems[1];
			};

			setup_data(moo_pInventory, moo_pPotion, moo_pGrids, moo_ppBeltItems, moo_pBeltItems);
			setup_data(original_pInventory, original_pPotion, original_pGrids, original_ppBeltItems, original_pBeltItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pPotion);
			const auto original_result = original(&original_pInventory, &original_pPotion);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pPotion, original_pPotion, "Comparing pPotion");
		}
	}
	
	TEST_CASE_FIXTURE(BeltsTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD90340 (#10269)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetFreeBeltSlot, dll_base + 0x00050340);

		SUBCASE("")
		{
			// Input data
			const auto sash_id = get_item_id(items_txt, items_record_count, ' lbl');
			const auto healing_potion_id = get_item_id(items_txt, items_record_count, ' 2ph');
			const auto item_code = GENERATE(' 1ph', ' 1pm', ' lvr', ' iuq');
			const auto item_id = get_item_id(items_txt, items_record_count, item_code);
			// Without a belt, the default belt type is used
			const auto has_belt = GENERATE(0, 1);

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc* moo_ppBeltItems[belt_grid_size]{};
			D2UnitStrc moo_pBelt{};
			D2UnitStrc moo_pBeltItems[2]{};
			int moo_pFreeSlotId = -1;
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2InventoryGridStrc original_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc* original_ppBeltItems[belt_grid_size]{};
			D2UnitStrc original_pBelt{};
			D2UnitStrc original_pBeltItems[2]{};
			int original_pFreeSlotId = -1;

			const auto setup_data = [sash_id, healing_potion_id, item_id, has_belt](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2InventoryGridStrc(&pGrids)[INVGRID_BELT + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc* (&ppBeltItems)[belt_grid_size],
				D2UnitStrc& pBelt,
				D2UnitStrc(&pBeltItems)[2]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BELT + 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = item_id;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pBelt.dwUnitType = UNIT_ITEM;
				pBelt.dwClassId = sash_id;
				pBelt.dwUnitId = 1;
				if (has_belt)
				{
					ppBodyLocItems[BODYLOC_BELT] = &pBelt;
				}

				pGrids[INVGRID_BELT].nGridWidth = belt_grid_size;
				pGrids[INVGRID_BELT].nGridHeight = 1;
				pGrids[INVGRID_BELT].ppItems = ppBeltItems;

				// Healing potions in the first two rows of the first column
				for (auto i = 0; i < 2; ++i)
				{
					pBeltItems[i].dwUnitType = UNIT_ITEM;
					pBeltItems[i].dwClassId = healing_potion_id;
					pBeltItems[i].dwUnitId = i + 2;
					ppBeltItems[i * 4] = &pBeltItems[i];
				}
			};

			setup_data(moo_pInventory, moo_pItem, moo_pGrids, moo_ppBodyLocItems, moo_ppBeltItems, moo_pBelt, moo_pBeltItems);
			setup_data(original_pInventory, original_pItem, original_pGrids, original_ppBodyLocItems, original_ppBeltItems, original_pBelt, original_pBeltItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem, &moo_pFreeSlotId);
			const auto original_result = original(&original_pInventory, &original_pItem, &original_pFreeSlotId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pFreeSlotId, original_pFreeSlotId, "Comparing pFreeSlotId");
		}
	}
	
	TEST_CASE_FIXTURE(BeltsTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD904F0 (#10270)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_PlaceItemInFreeBeltSlot, dll_base + 0x000504F0);

		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();
			const auto item_owner_id = random_unsigned_integer();
			const auto sash_id = get_item_id(items_txt, items_record_count, ' lbl');
			const auto healing_potion_id = get_item_id(items_txt, items_record_count, ' 2ph');
			const auto item_code = GENERATE(' 1ph', ' 1pm', ' lvr', ' iuq');
			const auto item_id = get_item_id(items_txt, items_record_count, item_code);

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StaticPathStrc moo_pStaticPath{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc* moo_ppBeltItems[belt_grid_size]{};
			D2UnitStrc moo_pBelt{};
			D2UnitStrc moo_pBeltItems[2]{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StaticPathStrc original_pStaticPath{};
			D2InventoryGridStrc original_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc* original_ppBeltItems[belt_grid_size]{};
			D2UnitStrc original_pBelt{};
			D2UnitStrc original_pBeltItems[2]{};

			const auto setup_data = [unit_id, item_owner_id, sash_id, healing_potion_id, item_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StaticPathStrc& pStaticPath,
				D2InventoryGridStrc(&pGrids)[INVGRID_BELT + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc* (&ppBeltItems)[belt_grid_size],
				D2UnitStrc& pBelt,
				D2UnitStrc(&pBeltItems)[2]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BELT + 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = item_id;
				pItem.dwUnitId = unit_id;
				pItem.pItemData = &pItemData;
				pItem.pStaticPath = &pStaticPath;
				pItemData.dwOwnerGUID = item_owner_id;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pBelt.dwUnitType = UNIT_ITEM;
				pBelt.dwClassId = sash_id;
				pBelt.dwUnitId = 1;
				ppBodyLocItems[BODYLOC_BELT] = &pBelt;

				pGrids[INVGRID_BELT].nGridWidth = belt_grid_size;
				pGrids[INVGRID_BELT].nGridHeight = 1;
				pGrids[INVGRID_BELT].ppItems = ppBeltItems;

				// Healing potions in the first two rows of the first column
				for (auto i = 0; i < 2; ++i)
				{
					pBeltItems[i].dwUnitType = UNIT_ITEM;
					pBeltItems[i].dwClassId = healing_potion_id;
					pBeltItems[i].dwUnitId = i + 2;
					ppBeltItems[i * 4] = &pBeltItems[i];
				}
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData, moo_pStaticPath, moo_pGrids, moo_ppBodyLocItems, moo_ppBeltItems, moo_pBelt, moo_pBeltItems);
			setup_data(original_pInventory, original_pItem, original_pItemData, original_pStaticPath, original_pGrids, original_ppBodyLocItems, original_ppBeltItems, original_pBelt, original_pBeltItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem);
			const auto original_result = original(&original_pInventory, &original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_BELT], original_pGrids[INVGRID_BELT], "Comparing belt grid");
			check_grid_occupancy(moo_pGrids[INVGRID_BELT], original_pGrids[INVGRID_BELT]);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD90550 (#10271)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetItemFromBeltSlot, dll_base + 0x00050550);

		SUBCASE("")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* moo_ppBeltItems[belt_grid_size]{};
			D2UnitStrc moo_pBeltItems[3]{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* original_ppBeltItems[belt_grid_size]{};
			D2UnitStrc original_pBeltItems[3]{};

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BELT + 1],
				D2UnitStrc* (&ppBeltItems)[belt_grid_size],
				D2UnitStrc(&pBeltItems)[3]
			) {
				constexpr int slots[3] = { 0, 6, belt_grid_size - 1 };

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BELT + 1;

				pGrids[INVGRID_BELT].nGridWidth = belt_grid_size;
				pGrids[INVGRID_BELT].nGridHeight = 1;
				pGrids[INVGRID_BELT].ppItems = ppBeltItems;

				for (auto i = 0; i < 3; ++i)
				{
					pBeltItems[i].dwUnitType = UNIT_ITEM;
					pBeltItems[i].dwUnitId = i + 1;
					ppBeltItems[slots[i]] = &pBeltItems[i];
				}
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBeltItems, moo_pBeltItems);
			setup_data(original_pInventory, original_pGrids, original_ppBeltItems, original_pBeltItems);

			for (int nSlotId = -1; nSlotId <= belt_grid_size; ++nSlotId)
			{
				// Call both implementations
				const auto moo_result = sut(&moo_pInventory, nSlotId);
				const auto original_result = original(&original_pInventory, nSlotId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD90590 (#10272)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetUseableItemFromBeltSlot, dll_base + 0x00050590);

		SUBCASE("")
		{
			// Input data
			const auto healing_potion_id = get_item_id(items_txt, items_record_count, ' 2ph');
			const auto item_code = GENERATE(' 1ph', ' iuq');
			const auto item_id = get_item_id(items_txt, items_record_count, item_code);

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* moo_ppBeltItems[belt_grid_size]{};
			D2UnitStrc moo_pBeltItems[2]{};
			D2UnitStrc* moo_ppItem{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2InventoryGridStrc original_pGrids[INVGRID_BELT + 1]{};
			D2UnitStrc* original_ppBeltItems[belt_grid_size]{};
			D2UnitStrc original_pBeltItems[2]{};
			D2UnitStrc* original_ppItem{};
			int nSlotId = GENERATE(-1, 0, 1, 4, belt_grid_size);

			const auto setup_data = [healing_potion_id, item_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2InventoryGridStrc(&pGrids)[INVGRID_BELT + 1],
				D2UnitStrc* (&ppBeltItems)[belt_grid_size],
				D2UnitStrc(&pBeltItems)[2]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BELT + 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = item_id;

				pGrids[INVGRID_BELT].nGridWidth = belt_grid_size;
				pGrids[INVGRID_BELT].nGridHeight = 1;
				pGrids[INVGRID_BELT].ppItems = ppBeltItems;

				// Healing potions in the first two rows of the first column
				for (auto i = 0; i < 2; ++i)
				{
					pBeltItems[i].dwUnitType = UNIT_ITEM;
					pBeltItems[i].dwClassId = healing_potion_id;
					pBeltItems[i].dwUnitId = i + 1;
					ppBeltItems[i * 4] = &pBeltItems[i];
				}
			};

			setup_data(moo_pInventory, moo_pItem, moo_pGrids, moo_ppBeltItems, moo_pBeltItems);
			setup_data(original_pInventory, original_pItem, original_pGrids, original_ppBeltItems, original_pBeltItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem, nSlotId, &moo_ppItem);
			const auto original_result = original(&original_pInventory, &original_pItem, nSlotId, &original_ppItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_ppItem, original_ppItem, "Comparing ppItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD90690 (#10273)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetEquippedShield, dll_base + 0x00050690);

		SUBCASE("")
		{
			// Input data
			const auto right_hand_item_code = GENERATE(' dss', ' cub');
			const auto left_hand_item_code = GENERATE(' xah', ' cub');
			const auto right_hand_item_id = get_item_id(items_txt, items_record_count, right_hand_item_code);
			const auto left_hand_item_id = get_item_id(items_txt, items_record_count, left_hand_item_code);

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pRightHandItem{};
			D2UnitStrc moo_pLeftHandItem{};
			D2UnitStrc* moo_ppItem{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pRightHandItem{};
			D2UnitStrc original_pLeftHandItem{};
			D2UnitStrc* original_ppItem{};

			const auto setup_data = [right_hand_item_id, left_hand_item_id](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pRightHandItem,
				D2UnitStrc& pLeftHandItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pRightHandItem.dwUnitType = UNIT_ITEM;
				pRightHandItem.dwClassId = right_hand_item_id;
				pRightHandItem.dwUnitId = 1;
				ppBodyLocItems[BODYLOC_RARM] = &pRightHandItem;

				pLeftHandItem.dwUnitType = UNIT_ITEM;
				pLeftHandItem.dwClassId = left_hand_item_id;
				pLeftHandItem.dwUnitId = 2;
				ppBodyLocItems[BODYLOC_LARM] = &pLeftHandItem;
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pRightHandItem, moo_pLeftHandItem);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pRightHandItem, original_pLeftHandItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_ppItem);
			const auto original_result = original(&original_pInventory, &original_ppItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_ppItem, original_ppItem, "Comparing ppItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD90760 (#10274)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetEquippedWeapon, dll_base + 0x00050760);

		SUBCASE("")
		{
			// Input data
			const auto right_hand_item_code = GENERATE(' dss', ' cub');
			const auto right_hand_item_id = get_item_id(items_txt, items_record_count, right_hand_item_code);
			const auto hand_axe_id = get_item_id(items_txt, items_record_count, ' xah');
			const D2UnitGUID left_item_guid = GENERATE(1u, 2u);

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pRightHandItem{};
			D2UnitStrc moo_pLeftHandItem{};
			D2UnitStrc* moo_ppItem{};
			int moo_pBodyLoc = -1;
			BOOL moo_pIsLeftHandItem = -1;
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pRightHandItem{};
			D2UnitStrc original_pLeftHandItem{};
			D2UnitStrc* original_ppItem{};
			int original_pBodyLoc = -1;
			BOOL original_pIsLeftHandItem = -1;

			const auto setup_data = [right_hand_item_id, hand_axe_id, left_item_guid](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pRightHandItem,
				D2UnitStrc& pLeftHandItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.dwLeftItemGUID = left_item_guid;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pRightHandItem.dwUnitType = UNIT_ITEM;
				pRightHandItem.dwClassId = right_hand_item_id;
				pRightHandItem.dwUnitId = 1;
				ppBodyLocItems[BODYLOC_RARM] = &pRightHandItem;

				pLeftHandItem.dwUnitType = UNIT_ITEM;
				pLeftHandItem.dwClassId = hand_axe_id;
				pLeftHandItem.dwUnitId = 2;
				ppBodyLocItems[BODYLOC_LARM] = &pLeftHandItem;
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pRightHandItem, moo_pLeftHandItem);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pRightHandItem, original_pLeftHandItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_ppItem, &moo_pBodyLoc, &moo_pIsLeftHandItem);
			const auto original_result = original(&original_pInventory, &original_ppItem, &original_pBodyLoc, &original_pIsLeftHandItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_ppItem, original_ppItem, "Comparing ppItem");
			MOO_CHECK_EQ(moo_pBodyLoc, original_pBodyLoc, "Comparing pBodyLoc");
			MOO_CHECK_EQ(moo_pIsLeftHandItem, original_pIsLeftHandItem, "Comparing pIsLeftHandItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD90850 (#10275)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_HasBodyArmorEquipped, dll_base + 0x00050850);

		SUBCASE("")
		{
			// Input data
			// An item code of 0 leaves the torso empty
			const auto torso_item_code = GENERATE(0, ' iuq', ' pac');
			const auto torso_item_id = torso_item_code ? get_item_id(items_txt, items_record_count, torso_item_code) : -1;

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pTorsoItem{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pTorsoItem{};

			const auto setup_data = [torso_item_id](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pTorsoItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				if (torso_item_id >= 0)
				{
					pTorsoItem.dwUnitType = UNIT_ITEM;
					pTorsoItem.dwClassId = torso_item_id;
					pTorsoItem.dwUnitId = 1;
					ppBodyLocItems[BODYLOC_TORSO] = &pTorsoItem;
				}
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pTorsoItem);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pTorsoItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<ItemsTxtFixture<NoopFixture>>, "D2Common.0x6FD908A0 (#10276)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_IsItemBodyLocFree, dll_base + 0x000508A0);

		SUBCASE("")
		{
			// Input data
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto hand_axe_id = get_item_id(items_txt, items_record_count, ' xah');
			const auto& grid_info = inventory_txt[INVENTORYRECORD_AMAZON].pGridInfo;
			const int grid_size = grid_info.nGridX * grid_info.nGridY;
			// Fill up the backpack, so the equipped item does not always fit into it
			const auto fill_rate = GENERATE(0, 1, 2);

			std::vector<bool> occupied(grid_size);
			for (auto i = 0; i < grid_size; ++i)
			{
				occupied[i] = fill_rate > 0 && random_unsigned_integer(0, 3 - fill_rate) == 0;
			}

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pItem{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_size);
			D2UnitStrc moo_pEquippedItem{};
			D2ItemDataStrc moo_pEquippedItemData{};
			D2UnitStrc moo_pOtherItem{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pItem{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			std::vector<D2UnitStrc*> original_ppItems(grid_size);
			D2UnitStrc original_pEquippedItem{};
			D2ItemDataStrc original_pEquippedItemData{};
			D2UnitStrc original_pOtherItem{};
			int nBodyLoc = GENERATE(BODYLOC_HEAD, BODYLOC_RARM);
			int nInventoryRecordId = INVENTORYRECORD_AMAZON;

			const auto setup_data = [short_sword_id, hand_axe_id, &grid_info, &occupied](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pOwner,
				D2UnitStrc& pItem,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc& pEquippedItem,
				D2ItemDataStrc& pEquippedItemData,
				D2UnitStrc& pOtherItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pOwner;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pOwner.dwUnitType = UNIT_PLAYER;
				pOwner.dwClassId = PCLASS_AMAZON;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = hand_axe_id;
				pItem.dwUnitId = 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pEquippedItem.dwUnitType = UNIT_ITEM;
				pEquippedItem.dwClassId = short_sword_id;
				pEquippedItem.dwUnitId = 2;
				pEquippedItem.pItemData = &pEquippedItemData;
				pEquippedItemData.nBodyLoc = BODYLOC_RARM;
				ppBodyLocItems[BODYLOC_RARM] = &pEquippedItem;

				pGrids[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems.data();

				pOtherItem.dwUnitType = UNIT_ITEM;
				pOtherItem.dwUnitId = 3;
				for (size_t i = 0; i < ppItems.size(); ++i)
				{
					if (occupied[i])
					{
						ppItems[i] = &pOtherItem;
					}
				}
			};

			setup_data(moo_pInventory, moo_pOwner, moo_pItem, moo_pGrids, moo_ppBodyLocItems, moo_ppItems, moo_pEquippedItem, moo_pEquippedItemData, moo_pOtherItem);
			setup_data(original_pInventory, original_pOwner, original_pItem, original_pGrids, original_ppBodyLocItems, original_ppItems, original_pEquippedItem, original_pEquippedItemData, original_pOtherItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem, nBodyLoc, nInventoryRecordId);
			const auto original_result = original(&original_pInventory, &original_pItem, nBodyLoc, nInventoryRecordId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pEquippedItem, original_pEquippedItem, "Comparing pEquippedItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD90910 (#10279)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_RemoveInventoryItems, dll_base + 0x00050910);

		SUBCASE("")
		{
			// Input data
			const auto owner_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItems[3]{};
			D2ItemDataStrc moo_pItemDatas[3]{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItems[3]{};
			D2ItemDataStrc original_pItemDatas[3]{};

			const auto setup_data = [owner_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc(&pItems)[3],
				D2ItemDataStrc(&pItemDatas)[3]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstItem = &pItems[0];
				pInventory.pLastItem = &pItems[2];
				pInventory.dwItemCount = 3;
				pInventory.dwLeftItemGUID = 2;

				for (auto i = 0; i < 3; ++i)
				{
					pItems[i].dwUnitType = UNIT_ITEM;
					pItems[i].dwUnitId = i + 1;
					pItems[i].pItemData = &pItemDatas[i];
					pItemDatas[i].dwOwnerGUID = owner_id;
					pItemDatas[i].pExtraData.pParentInv = &pInventory;
					pItemDatas[i].pExtraData.pPreviousItem = i > 0 ? &pItems[i - 1] : nullptr;
					pItemDatas[i].pExtraData.pNextItem = i < 2 ? &pItems[i + 1] : nullptr;
					pItemDatas[i].pExtraData.nNodePosOther = 1;
				}
			};

			setup_data(moo_pInventory, moo_pItems, moo_pItemDatas);
			setup_data(original_pInventory, original_pItems, original_pItemDatas);

			// Call both implementations
			sut(&moo_pInventory);
			original(&original_pInventory);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			for (auto i = 0; i < 3; ++i)
			{
				MOO_CHECK_EQ(moo_pItems[i], original_pItems[i], "Comparing pItems");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD90940 (#10280)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetTradeInventory, dll_base + 0x00050940);
		
		SUBCASE("")
		{
			// Input data
			const auto item_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2InventoryNodeStrc moo_pFirstNode{};
			D2InventoryStrc original_pInventory{};
			D2InventoryNodeStrc original_pFirstNode{};

			const auto setup_data = [item_id](
				D2InventoryStrc& pInventory,
				D2InventoryNodeStrc& pInventoryNode
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstNode = &pInventoryNode;
				pInventoryNode.nItemId = item_id;
			};

			setup_data(moo_pInventory, moo_pFirstNode);
			setup_data(original_pInventory, original_pFirstNode);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD90960 (#10281)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_FreeTradeInventory, dll_base + 0x00050960);

		SUBCASE("")
		{
			// Input data
			const int item_ids[3] = { static_cast<int>(random_unsigned_integer()), static_cast<int>(random_unsigned_integer()), static_cast<int>(random_unsigned_integer()) };

			D2InventoryStrc moo_pInventory{};
			D2InventoryStrc original_pInventory{};
			// The nodes are freed by the function, so they have to be allocated from the memory pool
			D2InventoryNodeStrc* moo_pNodes[3] = { D2_ALLOC_STRC_POOL(nullptr, D2InventoryNodeStrc), D2_ALLOC_STRC_POOL(nullptr, D2InventoryNodeStrc), D2_ALLOC_STRC_POOL(nullptr, D2InventoryNodeStrc) };
			D2InventoryNodeStrc* original_pNodes[3] = { D2_ALLOC_STRC_POOL(nullptr, D2InventoryNodeStrc), D2_ALLOC_STRC_POOL(nullptr, D2InventoryNodeStrc), D2_ALLOC_STRC_POOL(nullptr, D2InventoryNodeStrc) };

			const auto setup_data = [&item_ids](
				D2InventoryStrc& pInventory,
				D2InventoryNodeStrc* (&pNodes)[3]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstNode = pNodes[0];
				pInventory.pLastNode = pNodes[2];

				for (auto i = 0; i < 3; ++i)
				{
					pNodes[i]->nItemId = item_ids[i];
					pNodes[i]->pNext = i < 2 ? pNodes[i + 1] : nullptr;
				}
			};

			setup_data(moo_pInventory, moo_pNodes);
			setup_data(original_pInventory, original_pNodes);

			// Call both implementations
			sut(&moo_pInventory);
			original(&original_pInventory);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD909B0 (#10282)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_CheckForItemInTradeInventory, dll_base + 0x000509B0);
		
		SUBCASE("is inside")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2InventoryStrc original_pInventory{};
			D2InventoryNodeStrc moo_nodes[5]{};
			D2InventoryNodeStrc original_nodes[5]{};
			int nItemId = random_unsigned_integer(1, 5);

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				D2InventoryNodeStrc(& nodes)[5]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstNode = &nodes[0];
				nodes[0].nItemId = 1;

				for (auto i = 1; i < 5; ++i)
				{
					nodes[i].nItemId = i + 1;
					nodes[i - 1].pNext = &nodes[i];
				}
			};

			setup_data(moo_pInventory, moo_nodes);
			setup_data(original_pInventory, original_nodes);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nItemId);
			const auto original_result = original(&original_pInventory, nItemId);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}

		SUBCASE("is not inside")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2InventoryStrc original_pInventory{};
			D2InventoryNodeStrc moo_nodes[5]{};
			D2InventoryNodeStrc original_nodes[5]{};
			int nItemId = 10;

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				D2InventoryNodeStrc(&nodes)[5]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstNode = &nodes[0];
				nodes[0].nItemId = 1;
				
				for (auto i = 1; i < 5; ++i)
				{
					nodes[i].nItemId = i + 1;
					nodes[i - 1].pNext = &nodes[i];
				}
			};

			setup_data(moo_pInventory, moo_nodes);
			setup_data(original_pInventory, original_nodes);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nItemId);
			const auto original_result = original(&original_pInventory, nItemId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD909F0 (#10283)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_AddItemToTradeInventory, dll_base + 0x000509F0);

		SUBCASE("")
		{
			// Input data
			// Items with the ids 1 and 2 already are in the trade inventory
			const auto item_id = GENERATE(1, 2, 3);
			const auto has_nodes = GENERATE(0, 1);

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2InventoryNodeStrc moo_pNodes[2]{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2InventoryNodeStrc original_pNodes[2]{};

			const auto setup_data = [item_id, has_nodes](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2InventoryNodeStrc(&pNodes)[2]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;

				if (has_nodes)
				{
					pInventory.pFirstNode = &pNodes[0];
					pInventory.pLastNode = &pNodes[1];

					pNodes[0].nItemId = 1;
					pNodes[0].pNext = &pNodes[1];
					pNodes[1].nItemId = 2;
				}

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = item_id;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pNodes);
			setup_data(original_pInventory, original_pItem, original_pNodes);

			// Call both implementations
			sut(&moo_pInventory, &moo_pItem);
			original(&original_pInventory, &original_pItem);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD90AB0 (#10316)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10316, dll_base + 0x00050AB0);
		
		SUBCASE("")
		{
			// Input data
			const auto value = random_unsigned_integer();

			D2CorpseStrc moo_pCorpse{};
			D2CorpseStrc original_pCorpse{};

			const auto setup_data = [value](
				D2CorpseStrc& pCorpse
			) {
				pCorpse.unk0x00 = value;
			};

			setup_data(moo_pCorpse);
			setup_data(original_pCorpse);

			// Call both implementations
			const auto moo_result = sut(&moo_pCorpse);
			const auto original_result = original(&original_pCorpse);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pCorpse, original_pCorpse, "Comparing pCorpse");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD90AC0 (#10284)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetItemCount, dll_base + 0x00050AC0);
		
		SUBCASE("")
		{
			// Input data
			const auto item_count = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2InventoryStrc original_pInventory{};

			const auto setup_data = [item_count](
				D2InventoryStrc& pInventory
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.dwItemCount = item_count;
			};

			setup_data(moo_pInventory);
			setup_data(original_pInventory);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD90AE0 (#10285)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetBackPackItemByType, dll_base + 0x00050AE0);

		SUBCASE("")
		{
			// Input data
			static constexpr int grid_width = 10;
			static constexpr int grid_height = 4;

			const int item_ids[4] =
			{
				get_item_id(items_txt, items_record_count, ' dss'),
				get_item_id(items_txt, items_record_count, ' iuq'),
				get_item_id(items_txt, items_record_count, ' xah'),
				get_item_id(items_txt, items_record_count, ' 1ph'),
			};

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* moo_ppItems[grid_width * grid_height]{};
			D2UnitStrc moo_pItems[4]{};
			D2ItemDataStrc moo_pItemDatas[4]{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* original_ppItems[grid_width * grid_height]{};
			D2UnitStrc original_pItems[4]{};
			D2ItemDataStrc original_pItemDatas[4]{};
			int nItemType = GENERATE(ITEMTYPE_WEAPON, ITEMTYPE_ANY_ARMOR, ITEMTYPE_POTION, ITEMTYPE_RING);

			const auto setup_data = [&item_ids](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				D2UnitStrc* (&ppItems)[grid_width * grid_height],
				D2UnitStrc(&pItems)[4],
				D2ItemDataStrc(&pItemDatas)[4]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pGrids[INVGRID_INVENTORY].pItem = &pItems[0];
				pGrids[INVGRID_INVENTORY].pLastItem = &pItems[3];
				pGrids[INVGRID_INVENTORY].nGridWidth = grid_width;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_height;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems;

				for (auto i = 0; i < 4; ++i)
				{
					pItems[i].dwUnitType = UNIT_ITEM;
					pItems[i].dwClassId = item_ids[i];
					pItems[i].dwUnitId = i + 1;
					pItems[i].pItemData = &pItemDatas[i];
					pItemDatas[i].pExtraData.pPreviousGridItem = i > 0 ? &pItems[i - 1] : nullptr;
					pItemDatas[i].pExtraData.pNextGridItem = i < 3 ? &pItems[i + 1] : nullptr;
				}
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppItems, moo_pItems, moo_pItemDatas);
			setup_data(original_pInventory, original_pGrids, original_ppItems, original_pItems, original_pItemDatas);

			// The search starts after the check item
			D2UnitStrc& moo_pCheckItem = moo_pItems[1];
			D2UnitStrc& original_pCheckItem = original_pItems[1];

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nItemType, &moo_pCheckItem);
			const auto original_result = original(&original_pInventory, nItemType, &original_pCheckItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pCheckItem, original_pCheckItem, "Comparing pCheckItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_INVENTORY], original_pGrids[INVGRID_INVENTORY], "Comparing inventory grid");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD90BC0 (#10286)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetEquippedItemByType, dll_base + 0x00050BC0);

		SUBCASE("")
		{
			// Input data
			const int item_ids[4] =
			{
				get_item_id(items_txt, items_record_count, ' pac'),
				get_item_id(items_txt, items_record_count, ' dss'),
				get_item_id(items_txt, items_record_count, ' xah'),
				get_item_id(items_txt, items_record_count, ' cub'),
			};

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pItems[4]{};
			D2ItemDataStrc moo_pItemDatas[4]{};
			D2StaticPathStrc moo_pStaticPaths[4]{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pItems[4]{};
			D2ItemDataStrc original_pItemDatas[4]{};
			D2StaticPathStrc original_pStaticPaths[4]{};
			int nItemType = GENERATE(ITEMTYPE_WEAPON, ITEMTYPE_ANY_SHIELD, ITEMTYPE_HELM, ITEMTYPE_RING);

			const auto setup_data = [&item_ids](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc(&pItems)[4],
				D2ItemDataStrc(&pItemDatas)[4],
				D2StaticPathStrc(&pStaticPaths)[4]
			) {
				// The hand axe is placed on the weapon switch
				constexpr int body_locs[4] = { BODYLOC_HEAD, BODYLOC_RARM, BODYLOC_SWRARM, BODYLOC_LARM };

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].pItem = &pItems[0];
				pGrids[INVGRID_BODYLOC].pLastItem = &pItems[3];
				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				for (auto i = 0; i < 4; ++i)
				{
					pItems[i].dwUnitType = UNIT_ITEM;
					pItems[i].dwClassId = item_ids[i];
					pItems[i].dwUnitId = i + 1;
					pItems[i].pItemData = &pItemDatas[i];
					pItems[i].pStaticPath = &pStaticPaths[i];
					pStaticPaths[i].tGameCoords.nX = body_locs[i];
					pItemDatas[i].nBodyLoc = static_cast<uint8_t>(body_locs[i]);
					pItemDatas[i].pExtraData.pPreviousGridItem = i > 0 ? &pItems[i - 1] : nullptr;
					pItemDatas[i].pExtraData.pNextGridItem = i < 3 ? &pItems[i + 1] : nullptr;
					ppBodyLocItems[body_locs[i]] = &pItems[i];
				}
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pItems, moo_pItemDatas, moo_pStaticPaths);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pItems, original_pItemDatas, original_pStaticPaths);

			// The search starts at the check item
			D2UnitStrc& moo_pCheckItem = moo_pItems[1];
			D2UnitStrc& original_pCheckItem = original_pItems[1];

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nItemType, &moo_pCheckItem);
			const auto original_result = original(&original_pInventory, nItemType, &original_pCheckItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pCheckItem, original_pCheckItem, "Comparing pCheckItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_BODYLOC], original_pGrids[INVGRID_BODYLOC], "Comparing body location grid");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD90C80 (#10287)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetEquippedItemByCode, dll_base + 0x00050C80);

		SUBCASE("")
		{
			// Input data
			const ItemsLinkerScope items_linker(items_txt, items_record_count);

			const int item_ids[4] =
			{
				get_item_id(items_txt, items_record_count, ' pac'),
				get_item_id(items_txt, items_record_count, ' dss'),
				get_item_id(items_txt, items_record_count, ' xah'),
				get_item_id(items_txt, items_record_count, ' cub'),
			};

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pItems[4]{};
			D2ItemDataStrc moo_pItemDatas[4]{};
			D2StaticPathStrc moo_pStaticPaths[4]{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pItems[4]{};
			D2ItemDataStrc original_pItemDatas[4]{};
			D2StaticPathStrc original_pStaticPaths[4]{};
			// The last item code does not exist
			int nItemCode = GENERATE(' pac', ' dss', ' xah', ' cub', ' nir', ' zzz');

			const auto setup_data = [&item_ids](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc(&pItems)[4],
				D2ItemDataStrc(&pItemDatas)[4],
				D2StaticPathStrc(&pStaticPaths)[4]
			) {
				// The hand axe is placed on the weapon switch
				constexpr int body_locs[4] = { BODYLOC_HEAD, BODYLOC_RARM, BODYLOC_SWRARM, BODYLOC_LARM };

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].pItem = &pItems[0];
				pGrids[INVGRID_BODYLOC].pLastItem = &pItems[3];
				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				for (auto i = 0; i < 4; ++i)
				{
					pItems[i].dwUnitType = UNIT_ITEM;
					pItems[i].dwClassId = item_ids[i];
					pItems[i].dwUnitId = i + 1;
					pItems[i].pItemData = &pItemDatas[i];
					pItems[i].pStaticPath = &pStaticPaths[i];
					pStaticPaths[i].tGameCoords.nX = body_locs[i];
					pItemDatas[i].nBodyLoc = static_cast<uint8_t>(body_locs[i]);
					pItemDatas[i].pExtraData.pPreviousGridItem = i > 0 ? &pItems[i - 1] : nullptr;
					pItemDatas[i].pExtraData.pNextGridItem = i < 3 ? &pItems[i + 1] : nullptr;
					ppBodyLocItems[body_locs[i]] = &pItems[i];
				}
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pItems, moo_pItemDatas, moo_pStaticPaths);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pItems, original_pItemDatas, original_pStaticPaths);

			// The search starts at the check item
			D2UnitStrc& moo_pCheckItem = moo_pItems[1];
			D2UnitStrc& original_pCheckItem = original_pItems[1];

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nItemCode, &moo_pCheckItem);
			const auto original_result = original(&original_pInventory, nItemCode, &original_pCheckItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pCheckItem, original_pCheckItem, "Comparing pCheckItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_BODYLOC], original_pGrids[INVGRID_BODYLOC], "Comparing body location grid");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD90D50 (#11306)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetBackPackItemByCode, dll_base + 0x00050D50);

		SUBCASE("")
		{
			// Input data
			const ItemsLinkerScope items_linker(items_txt, items_record_count);

			const int item_ids[4] =
			{
				get_item_id(items_txt, items_record_count, ' pac'),
				get_item_id(items_txt, items_record_count, ' dss'),
				get_item_id(items_txt, items_record_count, ' xah'),
				get_item_id(items_txt, items_record_count, ' cub'),
			};

			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* moo_ppItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pItems[4]{};
			D2ItemDataStrc moo_pItemDatas[4]{};
			D2StaticPathStrc moo_pStaticPaths[4]{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			D2UnitStrc* original_ppItems[NUM_BODYLOC]{};
			D2UnitStrc original_pItems[4]{};
			D2ItemDataStrc original_pItemDatas[4]{};
			D2StaticPathStrc original_pStaticPaths[4]{};
			// The last item code does not exist
			int nItemCode = GENERATE(' pac', ' dss', ' xah', ' cub', ' nir', ' zzz');

			const auto setup_data = [&item_ids](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				D2UnitStrc* (&ppItems)[NUM_BODYLOC],
				D2UnitStrc(&pItems)[4],
				D2ItemDataStrc(&pItemDatas)[4],
				D2StaticPathStrc(&pStaticPaths)[4]
			) {
				// The hand axe is placed beyond the x position limit of the function
				constexpr int x_positions[4] = { 0, 3, 11, 7 };

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				// The function requests the backpack grid with the size of the body location grid
				pGrids[INVGRID_INVENTORY].pItem = &pItems[0];
				pGrids[INVGRID_INVENTORY].pLastItem = &pItems[3];
				pGrids[INVGRID_INVENTORY].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_INVENTORY].nGridHeight = 1;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems;

				for (auto i = 0; i < 4; ++i)
				{
					pItems[i].dwUnitType = UNIT_ITEM;
					pItems[i].dwClassId = item_ids[i];
					pItems[i].dwUnitId = i + 1;
					pItems[i].pItemData = &pItemDatas[i];
					pItems[i].pStaticPath = &pStaticPaths[i];
					pStaticPaths[i].tGameCoords.nX = x_positions[i];
					pItemDatas[i].pExtraData.pPreviousGridItem = i > 0 ? &pItems[i - 1] : nullptr;
					pItemDatas[i].pExtraData.pNextGridItem = i < 3 ? &pItems[i + 1] : nullptr;
					ppItems[x_positions[i]] = &pItems[i];
				}
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppItems, moo_pItems, moo_pItemDatas, moo_pStaticPaths);
			setup_data(original_pInventory, original_pGrids, original_ppItems, original_pItems, original_pItemDatas, original_pStaticPaths);

			// The search starts at the check item
			D2UnitStrc& moo_pCheckItem = moo_pItems[1];
			D2UnitStrc& original_pCheckItem = original_pItems[1];

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nItemCode, &moo_pCheckItem);
			const auto original_result = original(&original_pInventory, nItemCode, &original_pCheckItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pCheckItem, original_pCheckItem, "Comparing pCheckItem");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_INVENTORY], original_pGrids[INVGRID_INVENTORY], "Comparing inventory grid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD90E20 (#10288)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetSetItemEquipCountByFileIndex, dll_base + 0x00050E20);

		SUBCASE("")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pItems[4]{};
			D2ItemDataStrc moo_pItemDatas[4]{};
			D2StaticPathStrc moo_pStaticPaths[4]{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pItems[4]{};
			D2ItemDataStrc original_pItemDatas[4]{};
			D2StaticPathStrc original_pStaticPaths[4]{};
			int nItemFileIndex = GENERATE(0, 3, 7);

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc(&pItems)[4],
				D2ItemDataStrc(&pItemDatas)[4],
				D2StaticPathStrc(&pStaticPaths)[4]
			) {
				// Set items on the body, a set item on the weapon switch and a unique item with a set item file index
				constexpr int body_locs[4] = { BODYLOC_HEAD, BODYLOC_SWRARM, BODYLOC_TORSO, BODYLOC_FEET };
				constexpr int qualities[4] = { ITEMQUAL_SET, ITEMQUAL_SET, ITEMQUAL_SET, ITEMQUAL_UNIQUE };
				constexpr int file_indices[4] = { 7, 7, 3, 7 };

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].pItem = &pItems[0];
				pGrids[INVGRID_BODYLOC].pLastItem = &pItems[3];
				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				for (auto i = 0; i < 4; ++i)
				{
					pItems[i].dwUnitType = UNIT_ITEM;
					pItems[i].dwUnitId = i + 1;
					pItems[i].pItemData = &pItemDatas[i];
					pItems[i].pStaticPath = &pStaticPaths[i];
					pStaticPaths[i].tGameCoords.nX = body_locs[i];
					pItemDatas[i].dwQualityNo = qualities[i];
					pItemDatas[i].dwFileIndex = file_indices[i];
					pItemDatas[i].pExtraData.pPreviousGridItem = i > 0 ? &pItems[i - 1] : nullptr;
					pItemDatas[i].pExtraData.pNextGridItem = i < 3 ? &pItems[i + 1] : nullptr;
					ppBodyLocItems[body_locs[i]] = &pItems[i];
				}
			};

			setup_data(moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pItems, moo_pItemDatas, moo_pStaticPaths);
			setup_data(original_pInventory, original_pGrids, original_ppBodyLocItems, original_pItems, original_pItemDatas, original_pStaticPaths);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nItemFileIndex);
			const auto original_result = original(&original_pInventory, nItemFileIndex);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pGrids[INVGRID_BODYLOC], original_pGrids[INVGRID_BODYLOC], "Comparing body location grid");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD90ED0 (#10289)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_UpdateWeaponGUIDOnInsert, dll_base + 0x00050ED0);

		SUBCASE("")
		{
			// Input data
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto hand_axe_id = get_item_id(items_txt, items_record_count, ' xah');
			// The equipped hand axe has the id 1, the inserted short sword the id 2
			const D2UnitGUID left_item_guid = GENERATE(D2UnitInvalidGUID, 1u, 2u);
			const auto body_loc = GENERATE(BODYLOC_RARM, BODYLOC_LARM, BODYLOC_HEAD);

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pEquippedItem{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pEquippedItem{};

			const auto setup_data = [short_sword_id, hand_axe_id, left_item_guid, body_loc](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pEquippedItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.dwLeftItemGUID = left_item_guid;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = short_sword_id;
				pItem.dwUnitId = 2;
				pItem.pItemData = &pItemData;
				pItemData.nBodyLoc = static_cast<uint8_t>(body_loc);

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pEquippedItem.dwUnitType = UNIT_ITEM;
				pEquippedItem.dwClassId = hand_axe_id;
				pEquippedItem.dwUnitId = 1;
				ppBodyLocItems[BODYLOC_LARM] = &pEquippedItem;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData, moo_pGrids, moo_ppBodyLocItems, moo_pEquippedItem);
			setup_data(original_pInventory, original_pItem, original_pItemData, original_pGrids, original_ppBodyLocItems, original_pEquippedItem);

			// Call both implementations
			sut(&moo_pInventory, &moo_pItem);
			original(&original_pInventory, &original_pItem);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD90F80 (#10290)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_UpdateWeaponGUIDOnRemoval, dll_base + 0x00050F80);

		SUBCASE("")
		{
			// Input data
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto hand_axe_id = get_item_id(items_txt, items_record_count, ' xah');
			// The equipped hand axe has the id 1, the removed short sword the id 2
			const D2UnitGUID left_item_guid = GENERATE(1u, 2u);
			const auto body_loc = GENERATE(BODYLOC_RARM, BODYLOC_LARM, BODYLOC_HEAD);

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pEquippedItem{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pEquippedItem{};

			const auto setup_data = [short_sword_id, hand_axe_id, left_item_guid, body_loc](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pEquippedItem
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.dwLeftItemGUID = left_item_guid;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = short_sword_id;
				pItem.dwUnitId = 2;
				pItem.pItemData = &pItemData;
				pItemData.nBodyLoc = static_cast<uint8_t>(body_loc);

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pEquippedItem.dwUnitType = UNIT_ITEM;
				pEquippedItem.dwClassId = hand_axe_id;
				pEquippedItem.dwUnitId = 1;
				ppBodyLocItems[BODYLOC_LARM] = &pEquippedItem;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData, moo_pGrids, moo_ppBodyLocItems, moo_pEquippedItem);
			setup_data(original_pInventory, original_pItem, original_pItemData, original_pGrids, original_ppBodyLocItems, original_pEquippedItem);

			// Call both implementations
			sut(&moo_pInventory, &moo_pItem);
			original(&original_pInventory, &original_pItem);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD91050 (#10291)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetWieldType, dll_base + 0x00051050);

		SUBCASE("")
		{
			// Input data
			// An item code of 0 leaves the hand empty
			const auto player_class = GENERATE(PCLASS_AMAZON, PCLASS_BARBARIAN);
			const auto right_hand_item_code = GENERATE(0, ' dss', ' xag', ' sh2', ' wbs');
			const auto left_hand_item_code = GENERATE(0, ' cub', ' vqa', ' dss');
			const auto right_hand_item_id = right_hand_item_code ? get_item_id(items_txt, items_record_count, right_hand_item_code) : -1;
			const auto left_hand_item_id = left_hand_item_code ? get_item_id(items_txt, items_record_count, left_hand_item_code) : -1;

			D2UnitStrc moo_pPlayer{};
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pRightHandItem{};
			D2UnitStrc moo_pLeftHandItem{};
			D2UnitStrc original_pPlayer{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pRightHandItem{};
			D2UnitStrc original_pLeftHandItem{};

			const auto setup_data = [player_class, right_hand_item_id, left_hand_item_id](
				D2UnitStrc& pPlayer,
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pRightHandItem,
				D2UnitStrc& pLeftHandItem
			) {
				pPlayer.dwUnitType = UNIT_PLAYER;
				pPlayer.dwClassId = player_class;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				if (right_hand_item_id >= 0)
				{
					pRightHandItem.dwUnitType = UNIT_ITEM;
					pRightHandItem.dwClassId = right_hand_item_id;
					pRightHandItem.dwUnitId = 1;
					ppBodyLocItems[BODYLOC_RARM] = &pRightHandItem;
				}

				if (left_hand_item_id >= 0)
				{
					pLeftHandItem.dwUnitType = UNIT_ITEM;
					pLeftHandItem.dwClassId = left_hand_item_id;
					pLeftHandItem.dwUnitId = 2;
					ppBodyLocItems[BODYLOC_LARM] = &pLeftHandItem;
				}
			};

			setup_data(moo_pPlayer, moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pRightHandItem, moo_pLeftHandItem);
			setup_data(original_pPlayer, original_pInventory, original_pGrids, original_ppBodyLocItems, original_pRightHandItem, original_pLeftHandItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, &moo_pInventory);
			const auto original_result = original(&original_pPlayer, &original_pInventory);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD91140 (#10292)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_SetOwnerId, dll_base + 0x00051140);
		
		SUBCASE("")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2InventoryStrc original_pInventory{};
			D2UnitGUID nOwnerGuid = random_unsigned_integer();

			const auto setup_data = [](
				D2InventoryStrc& pInventory
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
			};

			setup_data(moo_pInventory);
			setup_data(original_pInventory);

			// Call both implementations
			sut(&moo_pInventory, nOwnerGuid);
			original(&original_pInventory, nOwnerGuid);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD91160 (#10293)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetOwnerId, dll_base + 0x00051160);
		
		SUBCASE("")
		{
			// Input data
			const auto owner_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2InventoryStrc original_pInventory{};

			const auto setup_data = [owner_id](
				D2InventoryStrc& pInventory
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.dwOwnerGuid = owner_id;
			};

			setup_data(moo_pInventory);
			setup_data(original_pInventory);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD91190 (#10294)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_CreateCorpseForPlayer, dll_base + 0x00051190);

		SUBCASE("")
		{
			// Input data
			const auto has_corpse = GENERATE(0, 1);
			const auto corpse_unit_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2CorpseStrc moo_pCorpse{};
			D2InventoryStrc original_pInventory{};
			D2CorpseStrc original_pCorpse{};
			int nUnitId = random_unsigned_integer();
			int a3 = random_unsigned_integer();
			// Only corpses with a non-zero value are counted
			int a4 = GENERATE(0, 1);

			const auto setup_data = [has_corpse, corpse_unit_id](
				D2InventoryStrc& pInventory,
				D2CorpseStrc& pCorpse
			) {
				pInventory.dwSignature = D2C_InventoryHeader;

				if (has_corpse)
				{
					pInventory.pFirstCorpse = &pCorpse;
					pInventory.pLastCorpse = &pCorpse;
					pInventory.nCorpseCount = 1;

					pCorpse.unk0x00 = 1;
					pCorpse.dwUnitId = corpse_unit_id;
				}
			};

			setup_data(moo_pInventory, moo_pCorpse);
			setup_data(original_pInventory, original_pCorpse);

			// Call both implementations
			sut(&moo_pInventory, nUnitId, a3, a4);
			original(&original_pInventory, nUnitId, a3, a4);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD91210 (#10295)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_FreeCorpse, dll_base + 0x00051210);

		SUBCASE("")
		{
			// Input data
			// The corpses have the unit ids 10, 20 and 30, a unit id of 40 doesn't exist
			const auto corpse_index = GENERATE(0, 1, 2, 3);

			D2InventoryStrc moo_pInventory{};
			D2InventoryStrc original_pInventory{};
			// The corpses are freed by the function, so they have to be allocated from the memory pool
			D2CorpseStrc* moo_pCorpses[3] = { D2_ALLOC_STRC_POOL(nullptr, D2CorpseStrc), D2_ALLOC_STRC_POOL(nullptr, D2CorpseStrc), D2_ALLOC_STRC_POOL(nullptr, D2CorpseStrc) };
			D2CorpseStrc* original_pCorpses[3] = { D2_ALLOC_STRC_POOL(nullptr, D2CorpseStrc), D2_ALLOC_STRC_POOL(nullptr, D2CorpseStrc), D2_ALLOC_STRC_POOL(nullptr, D2CorpseStrc) };
			int nUnitId = (corpse_index + 1) * 10;
			int a3 = corpse_index % 2 == 0 ? 1 : 0;

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				D2CorpseStrc* (&pCorpses)[3]
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstCorpse = pCorpses[0];
				pInventory.pLastCorpse = pCorpses[2];
				pInventory.nCorpseCount = 2;

				for (auto i = 0; i < 3; ++i)
				{
					pCorpses[i]->unk0x00 = i % 2 == 0 ? 1 : 0;
					pCorpses[i]->dwUnitId = (i + 1) * 10;
					pCorpses[i]->unk0x08 = i;
					pCorpses[i]->pNextCorpse = i < 2 ? pCorpses[i + 1] : nullptr;
				}
			};

			setup_data(moo_pInventory, moo_pCorpses);
			setup_data(original_pInventory, original_pCorpses);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, nUnitId, a3);
			const auto original_result = original(&original_pInventory, nUnitId, a3);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD91290 (#10296)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetFirstCorpse, dll_base + 0x00051290);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2CorpseStrc moo_pCorpse{};
			D2InventoryStrc original_pInventory{};
			D2CorpseStrc original_pCorpse{};

			const auto setup_data = [unit_id](
				D2InventoryStrc& pInventory,
				D2CorpseStrc& pCorpse
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstCorpse = &pCorpse;

				pCorpse.dwUnitId = unit_id;
			};

			setup_data(moo_pInventory, moo_pCorpse);
			setup_data(original_pInventory, original_pCorpse);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD912B0 (#10297)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetCorpseCount, dll_base + 0x000512B0);
		
		SUBCASE("")
		{
			// Input data
			const auto corpse_count = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2InventoryStrc original_pInventory{};

			const auto setup_data = [corpse_count](
				D2InventoryStrc& pInventory
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.nCorpseCount = corpse_count;
			};

			setup_data(moo_pInventory);
			setup_data(original_pInventory);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD912D0 (#10313)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetNextCorpse, dll_base + 0x000512D0);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();
			const auto next_unit_id = random_unsigned_integer();

			D2CorpseStrc moo_pCorpse{};
			D2CorpseStrc moo_pNextCorpse{};
			D2CorpseStrc original_pCorpse{};
			D2CorpseStrc original_pNextCorpse{};

			const auto setup_data = [unit_id, next_unit_id](
				D2CorpseStrc& pCorpse,
				D2CorpseStrc& pNextCorpse
			) {
				pCorpse.dwUnitId = unit_id;
				pCorpse.pNextCorpse = &pNextCorpse;
				pNextCorpse.dwUnitId = next_unit_id;
			};

			setup_data(moo_pCorpse, moo_pNextCorpse);
			setup_data(original_pCorpse, original_pNextCorpse);

			// Call both implementations
			const auto moo_result = sut(&moo_pCorpse);
			const auto original_result = original(&original_pCorpse);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pCorpse, original_pCorpse, "Comparing pCorpse");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAFEA0 (#10314)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetUnitGUIDFromCorpse, dll_base + 0x0006FEA0);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();

			D2CorpseStrc moo_pCorpse{};
			D2CorpseStrc original_pCorpse{};

			const auto setup_data = [unit_id](
				D2CorpseStrc& pCorpse
			) {
				pCorpse.dwUnitId = unit_id;
			};

			setup_data(moo_pCorpse);
			setup_data(original_pCorpse);

			// Call both implementations
			const auto moo_result = sut(&moo_pCorpse);
			const auto original_result = original(&original_pCorpse);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pCorpse, original_pCorpse, "Comparing pCorpse");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB18D0 (#10315)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10315, dll_base + 0x000718D0);
		
		SUBCASE("")
		{
			// Input data
			const auto value = random_unsigned_integer();

			D2CorpseStrc moo_pCorpse{};
			D2CorpseStrc original_pCorpse{};

			const auto setup_data = [value](
				D2CorpseStrc& pCorpse
			) {
				pCorpse.unk0x08 = value;
			};

			setup_data(moo_pCorpse);
			setup_data(original_pCorpse);

			// Call both implementations
			const auto moo_result = sut(&moo_pCorpse);
			const auto original_result = original(&original_pCorpse);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pCorpse, original_pCorpse, "Comparing pCorpse");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD912F0 (#10298)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetItemSaveGfxInfo, dll_base + 0x000512F0);

		SUBCASE("")
		{
			// Input data
			// NOTE: Items in composit body locations are not covered, because they require the item color tables
			const auto boots_id = get_item_id(items_txt, items_record_count, ' tbl');
			const auto ring_id = get_item_id(items_txt, items_record_count, ' nir');

			uint8_t components[NUM_COMPONENTS]{};
			uint8_t colors[NUM_COMPONENTS]{};
			for (auto i = 0; i < NUM_COMPONENTS; ++i)
			{
				components[i] = static_cast<uint8_t>(random_unsigned_integer(0, 255));
				colors[i] = static_cast<uint8_t>(random_unsigned_integer(0, 255));
			}

			D2UnitStrc moo_pPlayer{};
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItems[2]{};
			D2ItemDataStrc moo_pItemDatas[2]{};
			uint8_t moo_pComponents[NUM_COMPONENTS]{};
			uint8_t moo_pColor[NUM_COMPONENTS]{};
			D2UnitStrc original_pPlayer{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItems[2]{};
			D2ItemDataStrc original_pItemDatas[2]{};
			uint8_t original_pComponents[NUM_COMPONENTS]{};
			uint8_t original_pColor[NUM_COMPONENTS]{};

			const auto setup_data = [boots_id, ring_id, &components, &colors](
				D2UnitStrc& pPlayer,
				D2InventoryStrc& pInventory,
				D2UnitStrc(&pItems)[2],
				D2ItemDataStrc(&pItemDatas)[2],
				uint8_t(&pComponents)[NUM_COMPONENTS],
				uint8_t(&pColor)[NUM_COMPONENTS]
			) {
				pPlayer.dwUnitType = UNIT_PLAYER;
				pPlayer.dwClassId = PCLASS_AMAZON;
				pPlayer.pInventory = &pInventory;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pPlayer;
				pInventory.pFirstItem = &pItems[0];
				pInventory.pLastItem = &pItems[1];
				pInventory.dwItemCount = 2;

				// Equipped boots, followed by a ring in the backpack
				pItems[0].dwUnitType = UNIT_ITEM;
				pItems[0].dwClassId = boots_id;
				pItems[0].dwUnitId = 1;
				pItems[0].dwAnimMode = IMODE_EQUIP;
				pItems[0].pItemData = &pItemDatas[0];
				pItemDatas[0].nBodyLoc = BODYLOC_FEET;
				pItemDatas[0].pExtraData.pParentInv = &pInventory;
				pItemDatas[0].pExtraData.pNextItem = &pItems[1];

				pItems[1].dwUnitType = UNIT_ITEM;
				pItems[1].dwClassId = ring_id;
				pItems[1].dwUnitId = 2;
				pItems[1].dwAnimMode = IMODE_STORED;
				pItems[1].pItemData = &pItemDatas[1];
				pItemDatas[1].pExtraData.pParentInv = &pInventory;
				pItemDatas[1].pExtraData.pPreviousItem = &pItems[0];

				std::memcpy(pComponents, components, sizeof(components));
				std::memcpy(pColor, colors, sizeof(colors));
			};

			setup_data(moo_pPlayer, moo_pInventory, moo_pItems, moo_pItemDatas, moo_pComponents, moo_pColor);
			setup_data(original_pPlayer, original_pInventory, original_pItems, original_pItemDatas, original_pComponents, original_pColor);

			// Call both implementations
			sut(&moo_pPlayer, moo_pComponents, moo_pColor);
			original(&original_pPlayer, original_pComponents, original_pColor);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			for (auto i = 0; i < NUM_COMPONENTS; ++i)
			{
				CHECK_EQ(moo_pComponents[i], original_pComponents[i]);
				CHECK_EQ(moo_pColor[i], original_pColor[i]);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD915C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_InitializeComponentArray, dll_base + 0x000515C0);

		SUBCASE("")
		{
			// The component arrays are global, so they are accessed directly
			auto* original_gTxtComponentItemTypeMap = reinterpret_cast<D2InventoryComponentItemTypeStrc*>(dll_base + 0x000AA708);
			auto* original_gnComponentArrayRecordCount = reinterpret_cast<int*>(dll_base + 0x000AAF00);
			auto* original_gbComponentArrayInitialized = reinterpret_cast<BOOL*>(dll_base + 0x000AAF04);

			// Force both implementations to (re-)initialize their component arrays
			gbComponentArrayInitialized = FALSE;
			*original_gbComponentArrayInitialized = FALSE;

			// Call both implementations
			sut();
			original();

			// Compare global data
			CHECK_EQ(gbComponentArrayInitialized, *original_gbComponentArrayInitialized);
			CHECK_EQ(gnComponentArrayRecordCount, *original_gnComponentArrayRecordCount);
			for (auto i = 0; i < ARRAY_SIZE(gTxtComponentItemTypeMap); ++i)
			{
				CHECK_EQ(gTxtComponentItemTypeMap[i].dwCode, original_gTxtComponentItemTypeMap[i].dwCode);
				CHECK_EQ(gTxtComponentItemTypeMap[i].nItemType, original_gTxtComponentItemTypeMap[i].nItemType);
			}
		}
	}
	
	TEST_CASE_FIXTURE(CharStatsTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD917B0" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD917B0, dll_base + 0x000517B0);

		SUBCASE("")
		{
			// Input data
			const ItemsLinkerScope items_linker(items_txt, items_record_count);

			const auto weapon_code = GENERATE(' bxl', ' wbs', ' dss');
			const auto weapon_id = get_item_id(items_txt, items_record_count, weapon_code);

			uint8_t components[NUM_COMPONENTS]{};
			uint8_t colors[NUM_COMPONENTS]{};
			for (auto i = 0; i < NUM_COMPONENTS; ++i)
			{
				components[i] = static_cast<uint8_t>(random_unsigned_integer(0, 255));
				colors[i] = static_cast<uint8_t>(random_unsigned_integer(0, 255));
			}

			D2UnitStrc moo_pUnit{};
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			uint8_t moo_a2[NUM_COMPONENTS]{};
			uint8_t moo_pColor[NUM_COMPONENTS]{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pUnit{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			uint8_t original_a2[NUM_COMPONENTS]{};
			uint8_t original_pColor[NUM_COMPONENTS]{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [weapon_id, &components, &colors](
				D2UnitStrc& pUnit,
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				uint8_t(&a2)[NUM_COMPONENTS],
				uint8_t(&pColor)[NUM_COMPONENTS],
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.dwClassId = PCLASS_AMAZON;
				pUnit.dwAnimMode = PLRMODE_NEUTRAL;
				pUnit.pInventory = &pInventory;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pUnit;
				pInventory.dwLeftItemGUID = D2UnitInvalidGUID;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].pItem = &pItem;
				pGrids[INVGRID_BODYLOC].pLastItem = &pItem;
				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = weapon_id;
				pItem.dwUnitId = 1;
				pItem.dwAnimMode = IMODE_EQUIP;
				pItem.pItemData = &pItemData;
				pItemData.nBodyLoc = BODYLOC_RARM;
				pItemData.pExtraData.pParentInv = &pInventory;
				pItemData.pExtraData.nNodePos = INVGRID_BODYLOC + 1;
				pItemData.pExtraData.nNodePosOther = 3;
				ppBodyLocItems[BODYLOC_RARM] = &pItem;

				std::memcpy(a2, components, sizeof(components));
				std::memcpy(pColor, colors, sizeof(colors));
			};

			setup_data(moo_pUnit, moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_a2, moo_pColor, moo_pItem, moo_pItemData);
			setup_data(original_pUnit, original_pInventory, original_pGrids, original_ppBodyLocItems, original_a2, original_pColor, original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pUnit, moo_a2, moo_pColor, &moo_pItem);
			original(&original_pUnit, original_a2, original_pColor, &original_pItem);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			for (auto i = 0; i < NUM_COMPONENTS; ++i)
			{
				CHECK_EQ(moo_a2[i], original_a2[i]);
				CHECK_EQ(moo_pColor[i], original_pColor[i]);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD91B60 (#10299)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10299, dll_base + 0x00051B60);

		SUBCASE("armor location")
		{
			// Input data
			const auto cap_id = get_item_id(items_txt, items_record_count, ' pac');
			// The short sword can't be placed on the head
			const auto item_code = GENERATE(' pac', ' dss');
			const auto item_id = get_item_id(items_txt, items_record_count, item_code);
			const auto is_occupied = GENERATE(0, 1);

			D2UnitStrc moo_pUnit{};
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pEquippedItem{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pUnit{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pEquippedItem{};
			D2UnitStrc original_pItem{};
			int nBodyLoc = BODYLOC_HEAD;
			// The requirements would need the item stats
			BOOL bDontCheckReqs = TRUE;

			const auto setup_data = [cap_id, item_id, is_occupied](
				D2UnitStrc& pUnit,
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pEquippedItem,
				D2UnitStrc& pItem
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.dwClassId = PCLASS_AMAZON;
				pUnit.pInventory = &pInventory;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pUnit;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				pEquippedItem.dwUnitType = UNIT_ITEM;
				pEquippedItem.dwClassId = cap_id;
				pEquippedItem.dwUnitId = 1;
				if (is_occupied)
				{
					ppBodyLocItems[BODYLOC_HEAD] = &pEquippedItem;
				}

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = item_id;
				pItem.dwUnitId = 2;
			};

			setup_data(moo_pUnit, moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pEquippedItem, moo_pItem);
			setup_data(original_pUnit, original_pInventory, original_pGrids, original_ppBodyLocItems, original_pEquippedItem, original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nBodyLoc, &moo_pItem, bDontCheckReqs);
			const auto original_result = original(&original_pUnit, nBodyLoc, &original_pItem, bDontCheckReqs);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}

		SUBCASE("weapon location")
		{
			// Input data
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			// An item code of 0 leaves the other hand empty
			const auto other_hand_item_code = GENERATE(0, ' cub', ' dss');
			const auto other_hand_item_id = other_hand_item_code ? get_item_id(items_txt, items_record_count, other_hand_item_code) : -1;

			D2UnitStrc moo_pUnit{};
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* moo_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc moo_pOtherHandItem{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pUnit{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
			D2UnitStrc* original_ppBodyLocItems[NUM_BODYLOC]{};
			D2UnitStrc original_pOtherHandItem{};
			D2UnitStrc original_pItem{};
			int nBodyLoc = GENERATE(BODYLOC_RARM, BODYLOC_LARM, BODYLOC_SWRARM, BODYLOC_SWLARM);
			// The requirements would need the item stats
			BOOL bDontCheckReqs = TRUE;

			int other_body_loc = BODYLOC_NONE;
			switch (nBodyLoc)
			{
			case BODYLOC_RARM: other_body_loc = BODYLOC_LARM; break;
			case BODYLOC_LARM: other_body_loc = BODYLOC_RARM; break;
			case BODYLOC_SWRARM: other_body_loc = BODYLOC_SWLARM; break;
			case BODYLOC_SWLARM: other_body_loc = BODYLOC_SWRARM; break;
			}

			const auto setup_data = [short_sword_id, other_hand_item_id, other_body_loc](
				D2UnitStrc& pUnit,
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_BODYLOC + 1],
				D2UnitStrc* (&ppBodyLocItems)[NUM_BODYLOC],
				D2UnitStrc& pOtherHandItem,
				D2UnitStrc& pItem
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.dwClassId = PCLASS_AMAZON;
				pUnit.pInventory = &pInventory;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pUnit;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_BODYLOC + 1;

				pGrids[INVGRID_BODYLOC].nGridWidth = NUM_BODYLOC;
				pGrids[INVGRID_BODYLOC].nGridHeight = 1;
				pGrids[INVGRID_BODYLOC].ppItems = ppBodyLocItems;

				if (other_hand_item_id >= 0)
				{
					pOtherHandItem.dwUnitType = UNIT_ITEM;
					pOtherHandItem.dwClassId = other_hand_item_id;
					pOtherHandItem.dwUnitId = 1;
					ppBodyLocItems[other_body_loc] = &pOtherHandItem;
				}

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = short_sword_id;
				pItem.dwUnitId = 2;
			};

			setup_data(moo_pUnit, moo_pInventory, moo_pGrids, moo_ppBodyLocItems, moo_pOtherHandItem, moo_pItem);
			setup_data(original_pUnit, original_pInventory, original_pGrids, original_ppBodyLocItems, original_pOtherHandItem, original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nBodyLoc, &moo_pItem, bDontCheckReqs);
			const auto original_result = original(&original_pUnit, nBodyLoc, &original_pItem, bDontCheckReqs);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD91D50" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD91D50, dll_base + 0x00051D50);

		SUBCASE("occupied body location")
		{
			// Input data
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto other_hand_item_code = GENERATE(' cub', ' dss');
			const auto other_hand_item_id = get_item_id(items_txt, items_record_count, other_hand_item_code);

			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_a3{};
			D2UnitStrc moo_a4{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_a3{};
			D2UnitStrc original_a4{};
			D2UnitStrc original_pItem{};
			int a2 = BODYLOC_RARM;
			int nBodyLoc = BODYLOC_LARM;
			int nUnused = random_unsigned_integer();

			const auto setup_data = [short_sword_id, other_hand_item_id](
				D2UnitStrc& pPlayer,
				D2UnitStrc& a3,
				D2UnitStrc& a4,
				D2UnitStrc& pItem
			) {
				// The player has no inventory, so the equipped item can't be moved into it
				pPlayer.dwUnitType = UNIT_PLAYER;
				pPlayer.dwClassId = PCLASS_AMAZON;

				// The new item
				a3.dwUnitType = UNIT_ITEM;
				a3.dwClassId = short_sword_id;
				a3.dwUnitId = 1;

				// The item which is equipped at the body location
				a4.dwUnitType = UNIT_ITEM;
				a4.dwClassId = short_sword_id;
				a4.dwUnitId = 2;

				// The item in the other hand
				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = other_hand_item_id;
				pItem.dwUnitId = 3;
			};

			setup_data(moo_pPlayer, moo_a3, moo_a4, moo_pItem);
			setup_data(original_pPlayer, original_a3, original_a4, original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, a2, nBodyLoc, &moo_a3, &moo_a4, &moo_pItem, nUnused);
			const auto original_result = original(&original_pPlayer, a2, nBodyLoc, &original_a3, &original_a4, &original_pItem, nUnused);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}

		SUBCASE("empty body location")
		{
			// Input data
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto other_hand_item_code = GENERATE(' cub', ' dss');
			const auto other_hand_item_id = get_item_id(items_txt, items_record_count, other_hand_item_code);

			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_a3{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_a3{};
			D2UnitStrc original_pItem{};
			int a2 = BODYLOC_RARM;
			int nBodyLoc = BODYLOC_LARM;
			int nUnused = random_unsigned_integer();

			const auto setup_data = [short_sword_id, other_hand_item_id](
				D2UnitStrc& pPlayer,
				D2UnitStrc& a3,
				D2UnitStrc& pItem
			) {
				pPlayer.dwUnitType = UNIT_PLAYER;
				pPlayer.dwClassId = PCLASS_AMAZON;

				// The new item
				a3.dwUnitType = UNIT_ITEM;
				a3.dwClassId = short_sword_id;
				a3.dwUnitId = 1;

				// The item in the other hand
				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = other_hand_item_id;
				pItem.dwUnitId = 3;
			};

			setup_data(moo_pPlayer, moo_a3, moo_pItem);
			setup_data(original_pPlayer, original_a3, original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, a2, nBodyLoc, &moo_a3, nullptr, &moo_pItem, nUnused);
			const auto original_result = original(&original_pPlayer, a2, nBodyLoc, &original_a3, nullptr, &original_pItem, nUnused);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}

		SUBCASE("no new item")
		{
			// Input data
			const auto short_sword_id = get_item_id(items_txt, items_record_count, ' dss');
			const auto great_axe_id = get_item_id(items_txt, items_record_count, ' xag');
			const auto is_occupied = GENERATE(true, false);

			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_a4{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_a4{};
			D2UnitStrc original_pItem{};
			int a2 = BODYLOC_RARM;
			int nBodyLoc = BODYLOC_LARM;
			int nUnused = random_unsigned_integer();

			const auto setup_data = [short_sword_id, great_axe_id](
				D2UnitStrc& pPlayer,
				D2UnitStrc& a4,
				D2UnitStrc& pItem
			) {
				pPlayer.dwUnitType = UNIT_PLAYER;
				pPlayer.dwClassId = PCLASS_AMAZON;

				// The item which is equipped at the body location
				a4.dwUnitType = UNIT_ITEM;
				a4.dwClassId = short_sword_id;
				a4.dwUnitId = 2;

				// A two handed weapon in the other hand
				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = great_axe_id;
				pItem.dwUnitId = 3;
			};

			setup_data(moo_pPlayer, moo_a4, moo_pItem);
			setup_data(original_pPlayer, original_a4, original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, a2, nBodyLoc, nullptr, is_occupied ? &moo_a4 : nullptr, &moo_pItem, nUnused);
			const auto original_result = original(&original_pPlayer, a2, nBodyLoc, nullptr, is_occupied ? &original_a4 : nullptr, &original_pItem, nUnused);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD91E80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD91E80, dll_base + 0x00051E80);

		SUBCASE("")
		{
			// Input data
			// Pairs of items, which may or may not be wielded together
			constexpr int item_codes[][2] =
			{
				{ ' dss', ' dss' },
				{ ' dss', ' cub' },
				{ ' cub', ' cub' },
				{ ' wbs', ' vqa' },
				{ ' xag', ' dss' },
				{ ' sh2', ' dss' },
				{ ' rtk', ' rtk' },
				{ ' rtk', ' dss' },
			};

			const auto player_class = GENERATE(PCLASS_AMAZON, PCLASS_BARBARIAN, PCLASS_ASSASSIN);
			const auto item_pair = GENERATE(0, 1, 2, 3, 4, 5, 6, 7);
			const auto item1_id = get_item_id(items_txt, items_record_count, item_codes[item_pair][0]);
			const auto item2_id = get_item_id(items_txt, items_record_count, item_codes[item_pair][1]);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem1{};
			D2UnitStrc moo_pItem2{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem1{};
			D2UnitStrc original_pItem2{};

			const auto setup_data = [player_class, item1_id, item2_id](
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem1,
				D2UnitStrc& pItem2
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.dwClassId = player_class;

				pItem1.dwUnitType = UNIT_ITEM;
				pItem1.dwClassId = item1_id;
				pItem1.dwUnitId = 1;

				pItem2.dwUnitType = UNIT_ITEM;
				pItem2.dwClassId = item2_id;
				pItem2.dwUnitId = 2;
			};

			setup_data(moo_pUnit, moo_pItem1, moo_pItem2);
			setup_data(original_pUnit, original_pItem1, original_pItem2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pItem1, &moo_pItem2);
			const auto original_result = original(&original_pUnit, &original_pItem1, &original_pItem2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pItem1, original_pItem1, "Comparing pItem1");
			MOO_CHECK_EQ(moo_pItem2, original_pItem2, "Comparing pItem2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD92080 (#10304)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetNextItem, dll_base + 0x00052080);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();
			const auto next_unit_id = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc moo_pNextItem{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2UnitStrc original_pNextItem{};

			const auto setup_data = [unit_id, next_unit_id](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2UnitStrc& pNextItem
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = unit_id;
				pItem.pItemData = &pItemData;
				pItemData.pExtraData.pNextItem = &pNextItem;

				pNextItem.dwUnitType = UNIT_ITEM;
				pNextItem.dwUnitId = next_unit_id;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pNextItem);
			setup_data(original_pItem, original_pItemData, original_pNextItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD920C0 (#10305)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_UnitIsItem, dll_base + 0x000520C0);

		SUBCASE("")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM);

			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [unit_type](
				D2UnitStrc& pItem
			) {
				pItem.dwUnitType = unit_type;
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD920E0 (#10306)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetItemGUID, dll_base + 0x000520E0);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [unit_id](
				D2UnitStrc& pItem
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = unit_id;
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD92100 (#10307)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetItemNodePage, dll_base + 0x00052100);
		
		SUBCASE("")
		{
			// Input data
			const auto node_page = random_unsigned_integer(0, 127);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [node_page](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;

				pItemData.pExtraData.nNodePosOther = node_page;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, node_page);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD92140 (#10310)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_IsItemInInventory, dll_base + 0x00052140);

		SUBCASE("in inventory")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pInventory.dwSignature = D2C_InventoryHeader;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;

				pItemData.pExtraData.pParentInv = &pInventory;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData);
			setup_data(original_pInventory, original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem);
			const auto original_result = original(&original_pInventory, &original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, &moo_pItem);
		}

		SUBCASE("not in inventory")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pInventory.dwSignature = D2C_InventoryHeader;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pInventory, moo_pItem, moo_pItemData);
			setup_data(original_pInventory, original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem);
			const auto original_result = original(&original_pInventory, &original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, nullptr);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAFEA0 (#10311)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetNextNode, dll_base + 0x0006FEA0);
		
		SUBCASE("")
		{
			// Input data
			const auto item_id = random_unsigned_integer();
			const auto next_item_id = random_unsigned_integer();

			D2InventoryNodeStrc moo_pNode{};
			D2InventoryNodeStrc moo_pNextNode{};
			D2InventoryNodeStrc original_pNode{};
			D2InventoryNodeStrc original_pNextNode{};

			const auto setup_data = [item_id, next_item_id](
				D2InventoryNodeStrc& pNode,
				D2InventoryNodeStrc& pNextNode
			) {
				pNode.nItemId = item_id;
				pNode.pNext = &pNextNode;
				pNextNode.nItemId = next_item_id;
			};

			setup_data(moo_pNode, moo_pNextNode);
			setup_data(original_pNode, original_pNextNode);

			// Call both implementations
			const auto moo_result = sut(&moo_pNode);
			const auto original_result = original(&original_pNode);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pNode, original_pNode, "Comparing pNode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD90AB0 (#10312)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_GetItemGUIDFromNode, dll_base + 0x00050AB0);
		
		SUBCASE("")
		{
			// Input data
			const auto item_id = random_unsigned_integer();

			D2InventoryNodeStrc moo_pNode{};
			D2InventoryNodeStrc original_pNode{};

			const auto setup_data = [item_id](
				D2InventoryNodeStrc& pNode
			) {
				pNode.nItemId = item_id;
			};

			setup_data(moo_pNode);
			setup_data(original_pNode);

			// Call both implementations
			const auto moo_result = sut(&moo_pNode);
			const auto original_result = original(&original_pNode);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pNode, original_pNode, "Comparing pNode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD92180 (#10300)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_RemoveAllItems, dll_base + 0x00052180);

		SUBCASE("")
		{
			// Input data
			const auto owner_id = random_unsigned_integer();

			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItems[2]{};
			D2ItemDataStrc moo_pItemDatas[2]{};
			D2UnitStrc moo_pCursorItem{};
			D2ItemDataStrc moo_pCursorItemData{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItems[2]{};
			D2ItemDataStrc original_pItemDatas[2]{};
			D2UnitStrc original_pCursorItem{};
			D2ItemDataStrc original_pCursorItemData{};

			const auto setup_data = [owner_id](
				D2InventoryStrc& pInventory,
				D2UnitStrc(&pItems)[2],
				D2ItemDataStrc(&pItemDatas)[2],
				D2UnitStrc& pCursorItem,
				D2ItemDataStrc& pCursorItemData
			) {
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pFirstItem = &pItems[0];
				pInventory.pLastItem = &pItems[1];
				pInventory.dwItemCount = 2;
				pInventory.pCursorItem = &pCursorItem;
				pInventory.dwLeftItemGUID = 1;

				for (auto i = 0; i < 2; ++i)
				{
					pItems[i].dwUnitType = UNIT_ITEM;
					pItems[i].dwUnitId = i + 1;
					pItems[i].pItemData = &pItemDatas[i];
					pItemDatas[i].dwOwnerGUID = owner_id;
					pItemDatas[i].pExtraData.pParentInv = &pInventory;
					pItemDatas[i].pExtraData.pPreviousItem = i > 0 ? &pItems[i - 1] : nullptr;
					pItemDatas[i].pExtraData.pNextItem = i < 1 ? &pItems[i + 1] : nullptr;
					pItemDatas[i].pExtraData.nNodePosOther = 1;
				}

				pCursorItem.dwUnitType = UNIT_ITEM;
				pCursorItem.dwUnitId = 3;
				pCursorItem.pItemData = &pCursorItemData;
				pCursorItemData.dwOwnerGUID = owner_id;
				pCursorItemData.pExtraData.pParentInv = &pInventory;
			};

			setup_data(moo_pInventory, moo_pItems, moo_pItemDatas, moo_pCursorItem, moo_pCursorItemData);
			setup_data(original_pInventory, original_pItems, original_pItemDatas, original_pCursorItem, original_pCursorItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory);
			const auto original_result = original(&original_pInventory);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pCursorItem, original_pCursorItem, "Comparing pCursorItem");
			for (auto i = 0; i < 2; ++i)
			{
				MOO_CHECK_EQ(moo_pItems[i], original_pItems[i], "Comparing pItems");
			}
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<ItemsTxtFixture<NoopFixture>>, "D2Common.0x6FD921D0 (#10302)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_CanItemsBeTraded, dll_base + 0x000521D0);

		SUBCASE("")
		{
			// Input data
			const auto quilted_armor_id = get_item_id(items_txt, items_record_count, ' iuq');
			const auto& grid_info = inventory_txt[INVENTORYRECORD_AMAZON].pGridInfo;
			const int grid_size = grid_info.nGridX * grid_info.nGridY;
			// The traded item only fits into an empty backpack of the second player
			const auto is_full = GENERATE(0, 1);

			D2UnitStrc moo_pPlayer1{};
			D2InventoryStrc moo_pInventory1{};
			D2InventoryGridStrc moo_pGrids1[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> moo_ppItems1(grid_size);
			D2UnitStrc moo_pTradeItem{};
			D2ItemDataStrc moo_pTradeItemData{};
			D2UnitStrc moo_pPlayer2{};
			D2InventoryStrc moo_pInventory2{};
			D2InventoryGridStrc moo_pGrids2[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> moo_ppItems2(grid_size);
			D2UnitStrc moo_pOtherItem{};
			D2TradeStates moo_pTradeState = static_cast<D2TradeStates>(-1);
			D2UnitStrc original_pPlayer1{};
			D2InventoryStrc original_pInventory1{};
			D2InventoryGridStrc original_pGrids1[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> original_ppItems1(grid_size);
			D2UnitStrc original_pTradeItem{};
			D2ItemDataStrc original_pTradeItemData{};
			D2UnitStrc original_pPlayer2{};
			D2InventoryStrc original_pInventory2{};
			D2InventoryGridStrc original_pGrids2[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> original_ppItems2(grid_size);
			D2UnitStrc original_pOtherItem{};
			D2TradeStates original_pTradeState = static_cast<D2TradeStates>(-1);

			const auto setup_data = [quilted_armor_id, &grid_info, is_full](
				D2UnitStrc& pPlayer1,
				D2InventoryStrc& pInventory1,
				D2InventoryGridStrc(&pGrids1)[INVGRID_INVENTORY + 1],
				std::vector<D2UnitStrc*>& ppItems1,
				D2UnitStrc& pTradeItem,
				D2ItemDataStrc& pTradeItemData,
				D2UnitStrc& pPlayer2,
				D2InventoryStrc& pInventory2,
				D2InventoryGridStrc(&pGrids2)[INVGRID_INVENTORY + 1],
				std::vector<D2UnitStrc*>& ppItems2,
				D2UnitStrc& pOtherItem
			) {
				// The first player offers an item on the trade page
				pPlayer1.dwUnitType = UNIT_PLAYER;
				pPlayer1.dwClassId = PCLASS_AMAZON;
				pPlayer1.dwUnitId = 1;
				pPlayer1.pInventory = &pInventory1;

				pInventory1.dwSignature = D2C_InventoryHeader;
				pInventory1.pOwner = &pPlayer1;
				pInventory1.pFirstItem = &pTradeItem;
				pInventory1.pLastItem = &pTradeItem;
				pInventory1.dwItemCount = 1;
				pInventory1.pGrids = pGrids1;
				pInventory1.nGridCount = INVGRID_INVENTORY + 1;

				pGrids1[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids1[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids1[INVGRID_INVENTORY].ppItems = ppItems1.data();

				pTradeItem.dwUnitType = UNIT_ITEM;
				pTradeItem.dwClassId = quilted_armor_id;
				pTradeItem.dwUnitId = 3;
				pTradeItem.pItemData = &pTradeItemData;
				pTradeItemData.nInvPage = INVPAGE_TRADE;
				pTradeItemData.pExtraData.pParentInv = &pInventory1;
				pTradeItemData.pExtraData.nNodePosOther = 1;

				// The second player doesn't offer anything
				pPlayer2.dwUnitType = UNIT_PLAYER;
				pPlayer2.dwClassId = PCLASS_AMAZON;
				pPlayer2.dwUnitId = 2;
				pPlayer2.pInventory = &pInventory2;

				pInventory2.dwSignature = D2C_InventoryHeader;
				pInventory2.pOwner = &pPlayer2;
				pInventory2.pGrids = pGrids2;
				pInventory2.nGridCount = INVGRID_INVENTORY + 1;

				pGrids2[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids2[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids2[INVGRID_INVENTORY].ppItems = ppItems2.data();

				pOtherItem.dwUnitType = UNIT_ITEM;
				pOtherItem.dwUnitId = 4;
				if (is_full)
				{
					for (auto& pItem : ppItems2)
					{
						pItem = &pOtherItem;
					}
				}
			};

			setup_data(moo_pPlayer1, moo_pInventory1, moo_pGrids1, moo_ppItems1, moo_pTradeItem, moo_pTradeItemData, moo_pPlayer2, moo_pInventory2, moo_pGrids2, moo_ppItems2, moo_pOtherItem);
			setup_data(original_pPlayer1, original_pInventory1, original_pGrids1, original_ppItems1, original_pTradeItem, original_pTradeItemData, original_pPlayer2, original_pInventory2, original_pGrids2, original_ppItems2, original_pOtherItem);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pPlayer1, &moo_pPlayer2, &moo_pTradeState);
			const auto original_result = original(nullptr, &original_pPlayer1, &original_pPlayer2, &original_pTradeState);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
			MOO_CHECK_EQ(moo_pTradeState, original_pTradeState, "Comparing pTradeState");
			MOO_CHECK_EQ(moo_pTradeItem, original_pTradeItem, "Comparing pTradeItem");
			check_grid_occupancy(moo_pGrids1[INVGRID_INVENTORY], original_pGrids1[INVGRID_INVENTORY]);
			check_grid_occupancy(moo_pGrids2[INVGRID_INVENTORY], original_pGrids2[INVGRID_INVENTORY]);
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<NoopFixture>, "D2Common.0x6FD923C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_CopyUnitItemsToTradeInventory, dll_base + 0x000523C0);

		SUBCASE("unit with inventory")
		{
			// Input data
			const auto& grid_info = inventory_txt[INVENTORYRECORD_AMAZON].pGridInfo;
			const int grid_size = grid_info.nGridX * grid_info.nGridY;

			std::vector<bool> occupied(grid_size);
			for (auto i = 0; i < grid_size; ++i)
			{
				occupied[i] = random_unsigned_integer(0, 2) == 0;
			}

			D2InventoryStrc moo_pTradeInventory{};
			D2UnitStrc moo_pUnit{};
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_size);
			D2UnitStrc moo_pOtherItem{};
			D2InventoryStrc original_pTradeInventory{};
			D2UnitStrc original_pUnit{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> original_ppItems(grid_size);
			D2UnitStrc original_pOtherItem{};

			const auto setup_data = [&grid_info, &occupied](
				D2InventoryStrc& pTradeInventory,
				D2UnitStrc& pUnit,
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc& pOtherItem
			) {
				// The grid of the trade inventory gets allocated by the function
				pTradeInventory.dwSignature = D2C_InventoryHeader;

				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.dwClassId = PCLASS_AMAZON;
				pUnit.pInventory = &pInventory;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pUnit;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pGrids[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems.data();

				pOtherItem.dwUnitType = UNIT_ITEM;
				for (size_t i = 0; i < ppItems.size(); ++i)
				{
					if (occupied[i])
					{
						ppItems[i] = &pOtherItem;
					}
				}
			};

			setup_data(moo_pTradeInventory, moo_pUnit, moo_pInventory, moo_pGrids, moo_ppItems, moo_pOtherItem);
			setup_data(original_pTradeInventory, original_pUnit, original_pInventory, original_pGrids, original_ppItems, original_pOtherItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pTradeInventory, &moo_pUnit);
			const auto original_result = original(&original_pTradeInventory, &original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTradeInventory, original_pTradeInventory, "Comparing pTradeInventory");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			REQUIRE_EQ(moo_pTradeInventory.nGridCount, INVGRID_INVENTORY + 1);
			REQUIRE_EQ(original_pTradeInventory.nGridCount, INVGRID_INVENTORY + 1);
			MOO_CHECK_EQ(moo_pTradeInventory.pGrids[INVGRID_INVENTORY], original_pTradeInventory.pGrids[INVGRID_INVENTORY], "Comparing trade inventory grid");
			check_grid_occupancy(moo_pTradeInventory.pGrids[INVGRID_INVENTORY], original_pTradeInventory.pGrids[INVGRID_INVENTORY]);
		}

		SUBCASE("unit without inventory")
		{
			// Input data
			D2InventoryStrc moo_pTradeInventory{};
			D2UnitStrc moo_pUnit{};
			D2InventoryStrc original_pTradeInventory{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2InventoryStrc& pTradeInventory,
				D2UnitStrc& pUnit
			) {
				// The grid of the trade inventory gets allocated by the function
				pTradeInventory.dwSignature = D2C_InventoryHeader;

				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.dwClassId = PCLASS_AMAZON;
			};

			setup_data(moo_pTradeInventory, moo_pUnit);
			setup_data(original_pTradeInventory, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pTradeInventory, &moo_pUnit);
			const auto original_result = original(&original_pTradeInventory, &original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTradeInventory, original_pTradeInventory, "Comparing pTradeInventory");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<ItemsTxtFixture<NoopFixture>>, "D2Common.0x6FD92490")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(INVENTORY_CanItemBePlacedInInventory, dll_base + 0x00052490);

		SUBCASE("")
		{
			REPEAT_5();

			// Input data
			const auto item_code = GENERATE(' nir', ' iuq');
			const auto item_id = get_item_id(items_txt, items_record_count, item_code);
			const auto& grid_info = inventory_txt[INVENTORYRECORD_AMAZON].pGridInfo;
			const int grid_size = grid_info.nGridX * grid_info.nGridY;
			// Cells reserved by the function are marked with this value
			const auto reserved_cell = reinterpret_cast<D2UnitStrc*>(static_cast<uintptr_t>(0xFFFFFFFF));

			std::vector<bool> occupied(grid_size);
			for (auto i = 0; i < grid_size; ++i)
			{
				occupied[i] = random_unsigned_integer(0, 2) == 0;
			}

			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2InventoryStrc moo_pInventory{};
			D2InventoryGridStrc moo_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> moo_ppItems(grid_size);
			D2UnitStrc moo_pOtherItem{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2InventoryStrc original_pInventory{};
			D2InventoryGridStrc original_pGrids[INVGRID_INVENTORY + 1]{};
			std::vector<D2UnitStrc*> original_ppItems(grid_size);
			D2UnitStrc original_pOtherItem{};

			const auto setup_data = [item_id, &grid_info, &occupied](
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2InventoryStrc& pInventory,
				D2InventoryGridStrc(&pGrids)[INVGRID_INVENTORY + 1],
				std::vector<D2UnitStrc*>& ppItems,
				D2UnitStrc& pOtherItem
			) {
				pPlayer.dwUnitType = UNIT_PLAYER;
				pPlayer.dwClassId = PCLASS_AMAZON;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = item_id;
				pItem.dwUnitId = 1;
				pItem.pItemData = &pItemData;

				// A trade inventory, which has no owner
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pGrids = pGrids;
				pInventory.nGridCount = INVGRID_INVENTORY + 1;

				pGrids[INVGRID_INVENTORY].nGridWidth = grid_info.nGridX;
				pGrids[INVGRID_INVENTORY].nGridHeight = grid_info.nGridY;
				pGrids[INVGRID_INVENTORY].ppItems = ppItems.data();

				pOtherItem.dwUnitType = UNIT_ITEM;
				pOtherItem.dwUnitId = 2;
				for (size_t i = 0; i < ppItems.size(); ++i)
				{
					if (occupied[i])
					{
						ppItems[i] = &pOtherItem;
					}
				}
			};

			setup_data(moo_pPlayer, moo_pItem, moo_pItemData, moo_pInventory, moo_pGrids, moo_ppItems, moo_pOtherItem);
			setup_data(original_pPlayer, original_pItem, original_pItemData, original_pInventory, original_pGrids, original_ppItems, original_pOtherItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, &moo_pItem, &moo_pInventory);
			const auto original_result = original(&original_pPlayer, &original_pItem, &original_pInventory);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			for (auto i = 0; i < grid_size; ++i)
			{
				CHECK_EQ(moo_ppItems[i] == reserved_cell, original_ppItems[i] == reserved_cell);
				CHECK_EQ(moo_ppItems[i] == nullptr, original_ppItems[i] == nullptr);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD925E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetXPosition, dll_base + 0x000525E0);
		
		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto x = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [unit_type, x](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto x = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};

			const auto setup_data = [unit_type, x](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = x;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD92610")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetYPosition, dll_base + 0x00052610);
		
		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [unit_type, y](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosY = y;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};

			const auto setup_data = [unit_type, y](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nY = y;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
