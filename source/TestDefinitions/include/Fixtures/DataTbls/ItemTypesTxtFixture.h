#pragma once


#include <cstdarg>
#include <memory>
#include <utility>

#include <Windows.h>

#include <D2DataTbls.h>


template<class Fixture>
struct ItemTypesTxtFixture : Fixture
{
	std::unique_ptr<D2ItemTypesTxt[]> itemtypes_txt;
	int itemtypes_record_count;

	ItemTypesTxtFixture()
	{
		const auto working_directory = std::filesystem::current_path();
		const auto d2common_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

		const auto original_sgptDataTables = reinterpret_cast<D2DataTablesStrc**>(d2common_base + 0x00096A20);

		auto [record_count, itemtypes] = read_bin_file<D2ItemTypesTxt>(working_directory / "excel" / "ItemTypes.bin");

		sgptDataTables->nItemTypesTxtRecordCount = record_count;
		sgptDataTables->pItemTypesTxt = itemtypes.get();

		*original_sgptDataTables = sgptDataTables;

		const auto original_itemtypes = reinterpret_cast<D2ItemTypesTxt**>(d2common_base + 0x000A9608 + 0x00000BF8);
		*original_itemtypes = itemtypes.get();

		const auto original_record_count = reinterpret_cast<int*>(d2common_base + 0x000A9608 + 0x00000BFC);
		*original_record_count = record_count;

		itemtypes_txt = std::move(itemtypes);
		itemtypes_record_count = record_count;
	};
};
