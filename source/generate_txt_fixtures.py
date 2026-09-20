#!/usr/bin/env python3

import argparse
from pathlib import Path


TEMPLATE = """#pragma once


#include <cstdarg>
#include <memory>
#include <utility>

#include <Windows.h>

#include <D2DataTbls.h>


template<class Fixture>
struct {prefix}TxtFixture : Fixture
{{
\tstd::unique_ptr<{type}[]> {variable_name}_txt;
\tint {variable_name}_record_count;

\t{prefix}TxtFixture()
\t{{
\t\tconst auto working_directory = std::filesystem::current_path();
\t\tconst auto d2common_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

\t\tconst auto original_sgptDataTables = reinterpret_cast<D2DataTablesStrc**>(d2common_base + 0x00096A20);

\t\tauto [record_count, {variable_name}] = read_bin_file<{type}>(working_directory / "excel" / "{prefix}.bin");
{record_count_code}
\t\tsgptDataTables->p{prefix}Txt = {variable_name}.get();

\t\t*original_sgptDataTables = sgptDataTables;

\t\tconst auto original_{variable_name} = reinterpret_cast<{type}**>(d2common_base + 0x000A9608 + {record_offset});
\t\t*original_{variable_name} = {variable_name}.get();
{original_record_count_code}
\t\t{variable_name}_txt = std::move({variable_name});
\t\t{variable_name}_record_count = record_count;
\t}};
}};
"""


def to_variable_name(prefix: str) -> str:
    """Convert a prefix such as CompCode to compcode."""
    return prefix.lower()


def generate_code(
    prefix: str,
    type_name: str,
    record_offset: str,
    record_count_offset: str | None,
) -> str:
    variable_name = to_variable_name(prefix)

    if record_count_offset is not None:
        record_count_code = f'\n\t\tsgptDataTables->n{prefix}TxtRecordCount = record_count;'
        original_record_count_code = (
            f'\n\t\tconst auto original_record_count = '
            f'reinterpret_cast<int*>(d2common_base + 0x000A9608 + '
            f'{record_count_offset});'
            f'\n\t\t*original_record_count = record_count;\n'
        )
    else:
        record_count_code = ""
        original_record_count_code = ""

    return TEMPLATE.format(
        prefix=prefix,
        type=type_name,
        variable_name=variable_name,
        record_offset=record_offset,
        record_count_code=record_count_code,
        original_record_count_code=original_record_count_code,
    )


def main():
    parser = argparse.ArgumentParser(
        description="Generate a D2*TxtFixture C++ struct."
    )

    parser.add_argument(
        "output",
        type=Path,
        help="Path to the output file",
    )
    parser.add_argument(
        "prefix",
        help="Table prefix, e.g. CompCode",
    )
    parser.add_argument(
        "type",
        help="C++ data type, e.g. D2CompCodeTxt",
    )
    parser.add_argument(
        "record_offset",
        help="Record pointer offset, e.g. 0x0000007C",
    )
    parser.add_argument(
        "record_count_offset",
        nargs="?",
        help="Optional record count offset, e.g. 0x00000084",
    )

    args = parser.parse_args()

    # Create the containing directory (and any missing parents).
    args.output.parent.mkdir(parents=True, exist_ok=True)

    code = generate_code(
        args.prefix,
        args.type,
        args.record_offset,
        args.record_count_offset,
    )

    args.output.write_text(code, encoding="utf-8")


if __name__ == "__main__":
    main()
