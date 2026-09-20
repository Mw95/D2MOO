#!/usr/bin/env python3

import argparse
import re
from dataclasses import dataclass
from typing import Optional
from pathlib import Path


TYPE_HEADERS = {
    # D2CMP
    "D2TileLibraryEntryStrc": "D2CMP.h",

    # D2Common
    "D2ActiveRoomStrc": "Drlg/D2DrlgDrlg.h",
    "D2UnitStrc": "Units/Units.h",
    "D2StatListStrc": "D2StatList.h",
    "D2SkillStrc": "D2Skills.h",
    "D2ShrinesTxt": "DataTbls/ObjectsTbls.h",
    "D2SkillsTxt": "DataTbls/SkillsTbls.h",
    "D2InventoryGridInfoStrc": "DataTbls/InvTbls.h",
    "D2RoomCollisionGridStrc": "D2Collision.h",

    # D2Game
    "D2AiControlStrc": "AI/AiGeneral.h",
    "D2AiParamStrc": "AI/AiGeneral.h",
    "D2ClientStrc": "GAME/Clients.h",
    "D2TimerArgStrc": "GAME/Event.h",
    "D2GameStrc": "GAME/Game.h",
    "D2UnkMonCreateStrc2": "MONSTER/MonsterSpawn.h",
    "D2AuraCallbackStrc": "SKILLS/Skills.h",
    "D2UnitInfoStrc": "UNIT/SUnit.h",
    "D2NpcRecordStrc": "UNIT/SUnitNpc.h",
}

UNIMPLEMENTED_FUNCTIONS = {
    # D2Game
    "sub_6FC71F60",
}


# Matches:
# //Dll.0xXXXXXXXX or //Dll.0xXXXXXXXX (#YYYYY)
COMMENT_RE = re.compile(
    r'^\s*//\s*'
    r'(?P<module>[^.]+)'
    r'\.0x(?P<address>[0-9A-Fa-f]+)'
    r'(?:\s+\(#(?P<ordinal>\d+)\))?'
    r'\s*$'
)


# Matches:
# //1.10f: Dll.0xXXXXXXXX or //1.10f: Dll.0xXXXXXXXX (#YYYYY)
VERSIONED_COMMENT_RE = re.compile(
    r'^\s*//\s*'
    r'(?P<version>[^:]+)'
    r'\s*:\s*'
    r'(?P<module>[^.]+)'
    r'\.0x(?P<address>[0-9A-Fa-f]+)'
    r'(?:\s+\(#(?P<ordinal>\d+)\))?'
    r'\s*$'
)


# Matches function declarations
FUNCTION_RE = re.compile(
    r'''
    ^\s*
    (?:
        (?:D2GAME_DLL_DECL|D2COMMON_DLL_DECL)
        \s+
    )?
    (?P<return_type>.+?)
    \s+
    __(?:fastcall|stdcall|cdecl|vectorcall|thiscall)
    \s+
    (?P<name>[A-Za-z_]\w*)
    \s*
    \(
        (?P<args>.*)
    \)
    \s*;
    \s*$
    ''',
    re.VERBOSE
)


@dataclass
class Parameter:
    type: str
    name: str
    is_pointer: bool = False
    is_reference: bool = False
    is_const: bool = False
    is_void_pointer: bool = False
    is_function_pointer: bool = False

    @property
    def is_mutable(self):
        """
        Whether the function could modify the argument's underlying data.
        """
        if self.is_pointer or self.is_reference:
            return not self.is_const

        return False

    @property
    def needs_duplicate(self):
        """
        Whether MOO and the original function need independent copies.

        Value parameters are passed by value and therefore don't need
        independent copies.

        Mutable pointers/references do need independent copies because
        either implementation could modify the pointed-to object.
        """
        return self.is_mutable and not self.is_void_pointer


@dataclass
class Function:
    module_name: str
    address: int
    ordinal: Optional[int]
    return_type: str
    name: str
    parameters: list[Parameter]


def get_additional_headers(functions, own_header):
    headers = set()

    headers.add(own_header)

    for function in functions:
        types = [function.return_type]

        for parameter in function.parameters:
            types.append(parameter.type)

        for type_name in types:
            for mapped_type, header in TYPE_HEADERS.items():
                # Match the type name as a C++ identifier rather than
                # accidentally matching a substring of another type.
                if re.search(rf'\b{re.escape(mapped_type)}\b', type_name):
                    headers.add(header)

    return sorted(headers)


def is_function_body_commented(function):
    return function.name in UNIMPLEMENTED_FUNCTIONS


def normalize_path(path):
    # Normalize separators
    path = path.replace("\\", "/")

    # Remove leading "./"
    while path.startswith("./"):
        path = path[2:]

    # Remove leading "include/"
    if path.startswith("include/"):
        path = path[len("include/"):]

    return path


def split_arguments(argument_string):
    """
    Split a C++ argument list on commas while respecting nested (), <>, [].

    This isn't intended to be a complete C++ parser, but handles common
    declarations such as:

        int a, D2Foo* pFoo
        void (*callback)(int, int)
        std::vector<int> values
    """

    arguments = []
    current = []

    paren_depth = 0
    angle_depth = 0
    bracket_depth = 0

    for char in argument_string:
        if char == ',' and paren_depth == 0 and angle_depth == 0 and bracket_depth == 0:
            arguments.append("".join(current).strip())
            current = []
            continue

        current.append(char)

        if char == '(':
            paren_depth += 1
        elif char == ')':
            paren_depth -= 1
        elif char == '<':
            angle_depth += 1
        elif char == '>':
            angle_depth = max(0, angle_depth - 1)
        elif char == '[':
            bracket_depth += 1
        elif char == ']':
            bracket_depth -= 1

    final = "".join(current).strip()

    if final:
        arguments.append(final)

    return arguments


def parse_parameter(argument):
    """
    Parse a basic C++ parameter declaration.

    Examples:
        D2UnitStrc* pTarget
        const D2UnitStrc* pTarget
        int nLevel
        BOOL bUpdate
        void* ppUnitArg
        void (__fastcall* pCallback)(D2UnitStrc*)
    """

    argument = argument.strip()

    if not argument or argument == "void":
        return None

    # Remove a default argument.
    argument = argument.split("=", 1)[0].strip()

    # Function pointer:
    #
    #   void (__fastcall* pCallback)(...)
    #   int (*pCallback)(int)
    #   int32_t(__fastcall* pfCull)(D2UnitStrc*, D2UnitStrc*)
    #
    # The parameter name is between '*' and ')'.
    function_pointer_match = re.search(
        r'\(\s*(?:__(?:fastcall|stdcall|cdecl|vectorcall|thiscall)\s*)?\*'
        r'\s*(?P<name>[A-Za-z_]\w*)\s*\)',
        argument,
    )

    if function_pointer_match:
        return Parameter(
            type=argument,
            name=function_pointer_match.group("name"),
            is_function_pointer=True,
        )

    # Normal parameter.
    name_match = re.search(r'([A-Za-z_]\w*)\s*$', argument)

    if not name_match:
        return None

    name = name_match.group(1)
    type_part = argument[:name_match.start()].strip()

    is_pointer = "*" in type_part
    is_reference = "&" in type_part
    is_const = bool(re.search(r'\bconst\b', type_part))

    # Normalize whitespace around pointer/reference operators.
    type_part = re.sub(r'\s+', ' ', type_part)
    type_part = re.sub(r'\s*([*&])\s*', r'\1', type_part)

    is_void_pointer = bool(
        re.fullmatch(r'(?:const\s+)?void\*', type_part)
    )

    return Parameter(
        type=type_part,
        name=name,
        is_pointer=is_pointer,
        is_reference=is_reference,
        is_const=is_const,
        is_void_pointer=is_void_pointer,
    )


def parse_parameters(argument_string):
    parameters = []

    for argument in split_arguments(argument_string):
        parameter = parse_parameter(argument)

        if parameter is not None:
            parameters.append(parameter)

    return parameters


def parse_function(module_name, address, ordinal, match):
    return Function(
        module_name=module_name,
        address=address,
        ordinal=ordinal,
        return_type=match.group("return_type").strip(),
        name=match.group("name"),
        parameters=parse_parameters(match.group("args")),
    )


def is_trivial_type(type_name):
    """
    Types which can safely use a simple zero-initialized value.

    This is deliberately conservative. Unknown types are considered
    non-trivial so they get normal C++ value initialization.
    """

    normalized = type_name.replace("const ", "").strip()

    trivial_types = {
        "bool",
        "BOOL",
        "char",
        "signed char",
        "unsigned char",
        "short",
        "unsigned short",
        "int",
        "unsigned int",
        "long",
        "unsigned long",
        "long long",
        "unsigned long long",
        "float",
        "double",
        "long double",

        "int8_t",
        "uint8_t",
        "int16_t",
        "uint16_t",
        "int32_t",
        "uint32_t",
        "int64_t",
        "uint64_t",

        "uint8",
        "uint16",
        "uint32",
        "uint64",

        "size_t",
        "uintptr_t",
        "intptr_t",
    }

    return normalized in trivial_types


def parameter_variable_type(parameter):
    """
    Return the type used for a local variable representing a parameter.

    For pointers, remove exactly one level of indirection.

        D2UnitStrc*  -> D2UnitStrc
        D2UnitStrc** -> D2UnitStrc*
        D2UnitStrc*** -> D2UnitStrc**
        int*          -> int
        int**         -> int*
    """

    type_name = parameter.type

    # Remove const from the type itself.
    type_name = re.sub(r'\bconst\s+', '', type_name)

    # Remove exactly one pointer/reference level.
    if parameter.is_pointer:
        type_name = type_name.rstrip()
        if type_name.endswith("*"):
            type_name = type_name[:-1].rstrip()

    elif parameter.is_reference:
        type_name = type_name.rstrip()
        if type_name.endswith("&"):
            type_name = type_name[:-1].rstrip()

    return type_name


def default_value_for(parameter):
    """
    Return a suitable initializer for a parameter.
    """

    if parameter.is_void_pointer:
        return "nullptr"

    if parameter.is_pointer or parameter.is_reference:
        underlying_type = parameter_variable_type(parameter)

        if is_trivial_type(underlying_type):
            return "{}"

        return "{}"

    return "{}"


def parameter_setup_lines(function):
    lines = []
    moo_arguments = []
    original_arguments = []
    comparison_lines = []
    function_pointer_parameters = []
    duplicate_parameters = []

    for parameter in function.parameters:
        variable_name = parameter.name

        if parameter.is_function_pointer:
            function_pointer_parameters.append(parameter)
            moo_arguments.append("nullptr")
            original_arguments.append("nullptr")
            continue

        if parameter.is_void_pointer:
            lines.append(f"\t\t\tvoid* moo_{variable_name} = nullptr;")
            lines.append(f"\t\t\tvoid* original_{variable_name} = nullptr;")
            moo_arguments.append(f"moo_{variable_name}")
            original_arguments.append(f"original_{variable_name}")
            comparison_lines.append(f'\t\t\tSKIP_MOO_CHECK_EQ(moo_{variable_name}, original_{variable_name}, "Comparing {variable_name}");')
            continue

        if parameter.needs_duplicate:
            type_name = parameter_variable_type(parameter)
            duplicate_parameters.append((type_name, variable_name))

            if parameter.is_pointer:
                moo_arguments.append(f"&moo_{variable_name}")
                original_arguments.append(f"&original_{variable_name}")
            else:
                moo_arguments.append(f"moo_{variable_name}")
                original_arguments.append(f"original_{variable_name}")

            comparison_lines.append(f'\t\t\tSKIP_MOO_CHECK_EQ(moo_{variable_name}, original_{variable_name}, "Comparing {variable_name}");')
            continue

        if parameter.is_pointer or parameter.is_reference:
            type_name = parameter_variable_type(parameter)
            lines.append(f"\t\t\t{type_name} {variable_name}{{}};")
            if parameter.is_pointer:
                moo_arguments.append(f"&{variable_name}")
                original_arguments.append(f"&{variable_name}")
            else:
                moo_arguments.append(variable_name)
                original_arguments.append(variable_name)
            continue

        type_name = parameter_variable_type(parameter)
        lines.append(f"\t\t\t{type_name} {variable_name}{{}};")
        moo_arguments.append(variable_name)
        original_arguments.append(variable_name)

    if duplicate_parameters:
        setup_parameters = ",\n".join(
            f"\t\t\t\t{type_name}& {variable_name}"
            for type_name, variable_name in duplicate_parameters
        )

        input_declarations = [
            f"\t\t\t{type_name} moo_{variable_name}{{}};"
            for type_name, variable_name in duplicate_parameters
        ]
        input_declarations.extend(
            f"\t\t\t{type_name} original_{variable_name}{{}};"
            for type_name, variable_name in duplicate_parameters
        )

        moo_names = ", ".join(
            f"moo_{variable_name}" for _, variable_name in duplicate_parameters
        )
        original_names = ", ".join(
            f"original_{variable_name}" for _, variable_name in duplicate_parameters
        )

        lines = [
            "\t\t\t// Input data",
            *input_declarations,
            *lines,
            "",
            "\t\t\tconst auto setup_data = [](",
            setup_parameters,
            "\t\t\t) {",
            "\t\t\t\t// TODO: Setup as needed",
            "\t\t\t};",
            "",
            f"\t\t\tsetup_data({moo_names});",
            f"\t\t\tsetup_data({original_names});",
        ]

    return (lines, moo_arguments, original_arguments, comparison_lines, function_pointer_parameters)

def generate_test(function, dll_base_address):
    offset = function.address - int(dll_base_address, 16)

    is_body_commented = is_function_body_commented(function)

    (
        setup_lines,
        moo_arguments,
        original_arguments,
        comparison_lines,
        function_pointer_parameters,
    ) = parameter_setup_lines(function)

    moo_call = ", ".join(moo_arguments)
    original_call = ", ".join(original_arguments)

    lines = []
    function_body_lines = []

    test_name = (f"{function.module_name}.0x{function.address:08X}")

    if function.ordinal is not None:
        test_name += f" (#{function.ordinal})"

    lines.append("\t")
    lines.append(f'\tTEST_CASE_FIXTURE(NoopFixture, "{test_name}" * doctest::skip(""))')
    lines.append("\t{")

    function_body_lines.append("\t\t// Set up function pointers")
    function_body_lines.append(f"\t\tconst auto [sut, original] = make_function_pair({function.name}, dll_base + 0x{offset:08X});")
    function_body_lines.append("\t\t")

    if setup_lines:
        function_body_lines.append("\t\tSUBCASE(\"\")")
        function_body_lines.append("\t\t{")
        function_body_lines.extend(setup_lines)
        function_body_lines.append("")
    else:
        function_body_lines.append("\t\tSUBCASE(\"\")")
        function_body_lines.append("\t\t{")

    function_body_lines.append("\t\t\t// Call both implementations")

    if function.return_type == "void":
        function_body_lines.append(f"\t\t\tsut({moo_call});")
        function_body_lines.append(f"\t\t\toriginal({original_call});")
    else:
        function_body_lines.append(f"\t\t\tconst auto moo_result = sut({moo_call});")
        function_body_lines.append(f"\t\t\tconst auto original_result = original({original_call});")
        function_body_lines.append("\t\t\t")
        function_body_lines.append("\t\t\t// Compare return values")
        function_body_lines.append("\t\t\tSKIP_MOO_CHECK_EQ(moo_result, original_result, \"Comparing results\");")

    if comparison_lines:
        function_body_lines.append("")
        function_body_lines.append("\t\t\t// Compare potentially modified input data")
        function_body_lines.extend(comparison_lines)

    for body_line in function_body_lines:
        if is_body_commented:
            lines.append(f"//{body_line}")
        else:
            lines.append(body_line)

    if is_body_commented:
        lines.append("//\t\t}")
    else:
        lines.append("\t\t}")

    lines.append("\t}")

    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description="Generate doctest skeletons from D2MOO header files.")

    parser.add_argument("dll_name", help="Name of the .dll to be tested")

    parser.add_argument("dll_base_address", help="Base address of the .dll to be tested")

    parser.add_argument("test_suite_name", help="Name of the test suite")

    parser.add_argument("input", help="Input header file")

    parser.add_argument("output", help="Output cpp file")

    args = parser.parse_args()

    functions = []

    pending_comment = None

    with open(args.input, "r", encoding="utf-8") as f:
        for line in f:
            # Old format:
            #
            # //D2Common.0x6FDA6D10
            m = COMMENT_RE.match(line)

            if m:
                module = m.group("module")
                address = int(m.group("address"), 16)

                ordinal = m.group("ordinal")
                if ordinal is not None:
                    ordinal = int(ordinal)

                pending_comment = (module, address, ordinal)
                continue

            # Versioned format:
            #
            # //1.00:  D2Common.0x10057A10
            # //1.10f: D2Common.0x6FDA7280
            # //1.13c: D2Common.0x6FDCAF20
            m = VERSIONED_COMMENT_RE.match(line)

            if m:
                if m.group("version").strip() == "1.10f":
                    module = m.group("module")
                    address = int(m.group("address"), 16)

                    ordinal = m.group("ordinal")
                    if ordinal is not None:
                        ordinal = int(ordinal)

                    pending_comment = (module, address, ordinal)

                # Keep looking: more version comments may follow before
                # the function declaration.
                continue

            # Ignore blank lines between version comments and declarations.
            if not line.strip():
                continue

            if pending_comment is None:
                continue

            m = FUNCTION_RE.match(line)

            if not m:
                pending_comment = None
                continue

            function = parse_function(
                pending_comment[0],
                pending_comment[1],
                pending_comment[2],
                m
            )

            functions.append(function)
            pending_comment = None

    additional_headers = get_additional_headers(functions, normalize_path(args.input))

    output = []

    output.append("#include <doctest.h>")
    output.append("")
    output.append("#include <Windows.h>")
    output.append("")
    output.append("#include <cstdarg>")
    output.append("#include <filesystem>")
    output.append("")
    output.append("#include <TestDefinitions.h>")
    output.append("#include <TestUtilities.h>")
    output.append("")

    for header in additional_headers:
        output.append(f"#include <{header}>")
    
    output.append("")
    output.append("")

    output.append(f'TEST_SUITE("{args.test_suite_name}")')
    output.append("{")

    output.append('\tconst auto working_directory = std::filesystem::current_path();')
    output.append(f'\tconst auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / \"{args.dll_name}.dll\").string().c_str()));')
    output.append("")

    for function in functions:
        output.append(generate_test(function, args.dll_base_address))

    output.append("}")
    output.append("")

    output_path = Path(args.output)
    output_path.parent.mkdir(parents=True, exist_ok=True)

    with open(args.output, "w", encoding="utf-8") as f:
        f.write("\n".join(output))


if __name__ == "__main__":
    main()
