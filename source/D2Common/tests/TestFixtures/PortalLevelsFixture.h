#pragma once


#include <cstdarg>
#include <memory>

#include <Windows.h>

#include <D2DataTbls.h>

#include <TestUtilities.h>


template<class Fixture>
struct PortalLevelsFixture : Fixture
{
	std::unique_ptr<int[]> portal_levels;
	int count;

	PortalLevelsFixture()
	{
		const auto working_directory = std::filesystem::current_path();
		const auto d2common_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

		const auto original_sgptDataTables = reinterpret_cast<D2DataTablesStrc**>(d2common_base + 0x00096A20);

		count = random_unsigned_integer(1, 136);

		portal_levels = std::make_unique<int[]>(count);

		for (auto i = 1; i < count; ++i)
		{
			portal_levels[i] = random_unsigned_integer(0, 137);
		}

		sgptDataTables->nPortalLevels = count;
		sgptDataTables->pPortalLevels = portal_levels.get();

		*original_sgptDataTables = sgptDataTables;

		const auto original_count = reinterpret_cast<int*>(d2common_base + 0x000A9608 + 0x00001020);
		*original_count = count;

		const auto original_portal_levels = reinterpret_cast<int**>(d2common_base + 0x000A9608 + 0x0000101C);
		*original_portal_levels = portal_levels.get();
	};
};
