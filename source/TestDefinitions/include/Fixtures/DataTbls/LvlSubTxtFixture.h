#pragma once


#include <cstdarg>
#include <memory>
#include <utility>

#include <Windows.h>

#include <D2DataTbls.h>


template<class Fixture>
struct LvlSubTxtFixture : Fixture
{
	std::unique_ptr<D2LvlSubTxt[]> lvlsub_txt;
	int lvlsub_record_count;

	LvlSubTxtFixture()
	{
		const auto working_directory = std::filesystem::current_path();
		const auto d2common_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

		const auto original_sgptDataTables = reinterpret_cast<D2DataTablesStrc**>(d2common_base + 0x00096A20);

		auto [record_count, lvlsub] = read_bin_file<D2LvlSubTxt>(working_directory / "excel" / "LvlSub.bin");

		sgptDataTables->nLvlSubTxtRecordCount = record_count;
		sgptDataTables->pLvlSubTxt = lvlsub.get();

		*original_sgptDataTables = sgptDataTables;

		const auto original_lvlsub = reinterpret_cast<D2LvlSubTxt**>(d2common_base + 0x000A9608 + 0x00001038);
		*original_lvlsub = lvlsub.get();

		const auto original_record_count = reinterpret_cast<int*>(d2common_base + 0x000A9608 + 0x0000103C);
		*original_record_count = record_count;

		lvlsub_txt = std::move(lvlsub);
		lvlsub_record_count = record_count;
	};
};
