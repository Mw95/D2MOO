#pragma once


#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

#include <Windows.h>

#include <Fog.h>
#include <Storm.h>
#include <D2DataTbls.h>


// Lets both D2MOO and the original D2Common.dll load their tables through the regular archive functions.
//
// The archive handle passed to the Load*Txt functions is never used: files are opened by name through Fog/Storm.
// Enabling direct access makes Storm read the loose files below the working directory
// (data/global/excel/*.bin, the same files the Txt fixtures use) instead of looking them up in MPQ archives.
//
// Each implementation also gets its own, zeroed data tables, so the results of both loads can be compared afterwards:
// D2MOO uses its gpDataTables and the original uses its static data tables (most Txt fixtures point the original to ours).
// Everything is restored when the fixture is destroyed.
//
// Not part of Fixtures.h on purpose, since it pulls in Storm.h.
template<class Fixture>
struct DataTablesLoadFixture : Fixture
{
	static constexpr uintptr_t original_sgptDataTables_offset = 0x00096A20;
	static constexpr uintptr_t original_data_tables_offset = 0x000A9608;

	uintptr_t d2common_base;

	D2DataTablesStrc* moo_tables;
	D2DataTablesStrc* original_tables;

	D2DataTablesStrc** original_sgptDataTables;
	D2DataTablesStrc* previous_original_sgptDataTables;

	std::vector<char> moo_tables_backup;
	std::vector<char> original_tables_backup;

	char previous_base_path[MAX_PATH]{};
	BOOL has_previous_base_path;

	DataTablesLoadFixture()
	{
		const auto working_directory = std::filesystem::current_path();
		d2common_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

		original_sgptDataTables = reinterpret_cast<D2DataTablesStrc**>(d2common_base + original_sgptDataTables_offset);
		previous_original_sgptDataTables = *original_sgptDataTables;

		moo_tables = sgptDataTables;
		original_tables = reinterpret_cast<D2DataTablesStrc*>(d2common_base + original_data_tables_offset);

		moo_tables_backup.resize(sizeof(D2DataTablesStrc));
		std::memcpy(moo_tables_backup.data(), moo_tables, sizeof(D2DataTablesStrc));
		original_tables_backup.resize(sizeof(D2DataTablesStrc));
		std::memcpy(original_tables_backup.data(), original_tables, sizeof(D2DataTablesStrc));

		// Zeroing also clears bCompileTxt, which would otherwise make CompileTxt overwrite the .bin files with ones compiled from .txt files
		std::memset(moo_tables, 0x00, sizeof(D2DataTablesStrc));
		std::memset(original_tables, 0x00, sizeof(D2DataTablesStrc));
		*original_sgptDataTables = original_tables;

		has_previous_base_path = SFileGetBasePath(previous_base_path, sizeof(previous_base_path));

		std::string base_path = working_directory.string() + "\\";
		SFileSetBasePath(base_path.data());
		FOG_MPQSetConfig(TRUE, FALSE);
	}

	~DataTablesLoadFixture()
	{
		FOG_MPQSetConfig(FALSE, FALSE);
		if (has_previous_base_path)
		{
			SFileSetBasePath(previous_base_path);
		}

		std::memcpy(moo_tables, moo_tables_backup.data(), sizeof(D2DataTablesStrc));
		std::memcpy(original_tables, original_tables_backup.data(), sizeof(D2DataTablesStrc));
		*original_sgptDataTables = previous_original_sgptDataTables;
	}

	// Loading a file that cannot be found triggers an assertion inside the loaders, which aborts the whole test run.
	// Check with this first so that a broken setup fails the test instead.
	static bool can_open_file(const char* szFilePath)
	{
		HSFILE hFile = nullptr;
		if (!FOG_FOpenFile(szFilePath, &hFile))
		{
			return false;
		}

		FOG_FCloseFile(hFile);
		return true;
	}

	// Swaps the content of both data tables, so that tables loaded by one implementation can be unloaded by the other one
	void swap_tables()
	{
		std::vector<char> temp(sizeof(D2DataTablesStrc));
		std::memcpy(temp.data(), moo_tables, sizeof(D2DataTablesStrc));
		std::memcpy(moo_tables, original_tables, sizeof(D2DataTablesStrc));
		std::memcpy(original_tables, temp.data(), sizeof(D2DataTablesStrc));
	}
};
