#pragma once


#include <cstdarg>
#include <memory>
#include <utility>

#include <Windows.h>

#include <D2DataTbls.h>


template<class Fixture>
struct SkillsTxtFixture : Fixture
{
	std::unique_ptr<D2SkillsTxt[]> skills_txt;
	int skills_record_count;

	SkillsTxtFixture()
	{
		const auto working_directory = std::filesystem::current_path();
		const auto d2common_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

		const auto original_sgptDataTables = reinterpret_cast<D2DataTablesStrc**>(d2common_base + 0x00096A20);

		auto [record_count, skills] = read_bin_file<D2SkillsTxt>(working_directory / "excel" / "Skills.bin");

		sgptDataTables->nSkillsTxtRecordCount = record_count;
		sgptDataTables->pSkillsTxt = skills.get();

		*original_sgptDataTables = sgptDataTables;

		const auto original_skills = reinterpret_cast<D2SkillsTxt**>(d2common_base + 0x000A9608 + 0x00000B98);
		*original_skills = skills.get();

		const auto original_record_count = reinterpret_cast<int*>(d2common_base + 0x000A9608 + 0x00000BA0);
		*original_record_count = record_count;

		skills_txt = std::move(skills);
		skills_record_count = record_count;
	};
};
