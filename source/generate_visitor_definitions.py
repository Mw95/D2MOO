#!/usr/bin/env python3

import argparse
import re
from pathlib import Path


PREPROCESSOR_RE = re.compile(
    r"^[ \t]*#\s*(?:if|ifdef|ifndef|elif|else|endif)\b.*$",
    re.MULTILINE,
)


def strip_comments(text: str) -> str:
    """Remove // and /* */ comments while preserving preprocessor directives."""
    text = re.sub(r"//.*?$", "", text, flags=re.MULTILINE)
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.DOTALL)
    return text


def normalize_include_path(path: str) -> str:
    """Convert a Windows-style include path to a project-relative include path."""
    if not path:
        return path

    normalized = path.replace("\\", "/")
    segments = [
        segment
        for segment in normalized.split("/")
        if segment and segment != "."
    ]

    while segments and segments[0] == "..":
        segments.pop(0)

    for index, segment in enumerate(segments):
        if segment.lower() == "include":
            return "/".join(segments[index + 1:])

    if segments and segments[0].lower() == "include":
        return "/".join(segments[1:])

    return "/".join(segments)


def extract_name(declaration: str):
    """
    Extract the variable name from a declaration.

    Examples:
        uint32_t value        -> value
        Foo* pFoo             -> pFoo
        uint32_t values[10]   -> values
    """
    declaration = declaration.strip().rstrip(";")

    # Remove array dimensions.
    declaration = re.sub(r"\[[^\]]*\]", "", declaration)

    match = re.search(r"([A-Za-z_]\w*)\s*$", declaration)
    if not match:
        return None

    return match.group(1)


def classify_field(declaration: str):
    """
    Return (macro_type, field_name).

    macro_type is one of:
        OMIT
        POINTER
        ARRAY
        OBJECT
        FIELD
    """
    declaration = declaration.strip().rstrip(";")

    if not declaration:
        return None

    name = extract_name(declaration)
    if not name:
        return None

    before_name = declaration[:declaration.rfind(name)].strip()

    # Array.
    if re.search(r"\[[^\]]*\]", declaration):
        return "ARRAY", name

    normalized_type = re.sub(r"\s+", " ", before_name).strip()

    # void* -> OMIT()
    pointer_type = normalized_type.replace(" ", "")

    if pointer_type in (
        "void*",
        "constvoid*",
        "volatilevoid*",
        "constvolatilevoid*",
    ):
        return "OMIT", name

    # Pointer.
    if "*" in declaration:
        return "POINTER", name

    primitive_types = {
        "bool",
        "char",
        "signed char",
        "unsigned char",
        "short",
        "short int",
        "signed short",
        "signed short int",
        "unsigned short",
        "unsigned short int",
        "int",
        "signed",
        "signed int",
        "unsigned",
        "unsigned int",
        "long",
        "long int",
        "signed long",
        "signed long int",
        "unsigned long",
        "unsigned long int",
        "long long",
        "long long int",
        "signed long long",
        "signed long long int",
        "unsigned long long",
        "unsigned long long int",
        "float",
        "double",
        "long double",
        "size_t",
        "intptr_t",
        "uintptr_t",
        "int8_t",
        "uint8_t",
        "int16_t",
        "uint16_t",
        "int32_t",
        "uint32_t",
        "int64_t",
        "uint64_t",
        "DWORD",
        "WORD",
        "BYTE",
        "BOOL",
        "D2UnitGUID",
    }

    if normalized_type in primitive_types or normalized_type.endswith("_t"):
        return "FIELD", name

    # Unknown types are treated as embedded objects.
    return "OBJECT", name


def find_matching_brace(text: str, open_pos: int):
    """Find the matching closing brace for text[open_pos] == '{'."""
    depth = 0

    for i in range(open_pos, len(text)):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1

            if depth == 0:
                return i

    return None


def is_preprocessor_line(text: str, pos: int):
    """
    Return the complete preprocessor directive at pos, or None.

    Handles:
        #ifdef FOO
        #ifndef FOO
        #if ...
        #elif ...
        #else
        #endif
    """
    if pos > 0 and text[pos - 1] != "\n":
        return None

    match = re.match(
        r"[ \t]*#\s*(?:if|ifdef|ifndef|elif|else|endif)\b[^\n]*",
        text[pos:],
    )

    if not match:
        return None

    return match.group(0).strip()


def parse_block(body: str):
    """
    Parse fields, unions, embedded structs/classes, and preprocessor
    directives inside a struct/union body.
    """
    items = []
    i = 0
    length = len(body)

    while i < length:
        # Skip whitespace.
        while i < length and body[i].isspace():
            i += 1

        if i >= length:
            break

        # Preserve preprocessor directives.
        directive = is_preprocessor_line(body, i)

        if directive:
            items.append({
                "type": "PREPROCESSOR",
                "value": directive,
            })

            newline = body.find("\n", i)

            if newline == -1:
                break

            i = newline + 1
            continue

        # Anonymous union.
        union_match = re.match(r"union\s*\{", body[i:])

        if union_match:
            open_brace = i + body[i:].find("{")
            close_brace = find_matching_brace(body, open_brace)

            if close_brace is None:
                raise ValueError("Unmatched brace in union.")

            union_body = body[open_brace + 1:close_brace]

            i = close_brace + 1

            # Skip optional union name/attributes until semicolon.
            while i < length and body[i] != ";":
                i += 1

            if i < length:
                i += 1

            items.append({
                "type": "union",
                "items": parse_block(union_body),
            })

            continue

        # Explicitly embedded struct/class.
        embedded_match = re.match(
            r"(struct|class)\s+([A-Za-z_]\w*)\s*\{",
            body[i:],
        )

        if embedded_match:
            open_brace = i + body[i:].find("{")
            close_brace = find_matching_brace(body, open_brace)

            if close_brace is None:
                raise ValueError("Unmatched brace in embedded struct.")

            end = close_brace + 1

            while end < length and body[end].isspace():
                end += 1

            semicolon = body.find(";", end)

            if semicolon == -1:
                raise ValueError(
                    "Missing semicolon after embedded struct."
                )

            trailing = body[end:semicolon].strip()
            name_match = re.match(r"([A-Za-z_]\w*)", trailing)

            if name_match:
                items.append({
                    "type": "OBJECT",
                    "name": name_match.group(1),
                })

            i = semicolon + 1
            continue

        # Normal declaration.
        semicolon = body.find(";", i)

        if semicolon == -1:
            break

        declaration = body[i:semicolon].strip()
        i = semicolon + 1

        if not declaration:
            continue

        field = classify_field(declaration)

        if field:
            macro, name = field

            items.append({
                "type": macro,
                "name": name,
            })

    return items


def parse_struct_at(text: str, match):
    """
    Parse a struct beginning at a regex match.

    Returns:
        (struct_name, items, end_position)
    """
    struct_name = match.group(1)

    open_brace = text.find("{", match.start())

    if open_brace == -1:
        raise ValueError(
            f"Could not find opening brace for struct {struct_name}."
        )

    close_brace = find_matching_brace(text, open_brace)

    if close_brace is None:
        raise ValueError(
            f"Unmatched brace while parsing struct {struct_name}."
        )

    body = text[open_brace + 1:close_brace]

    # Include the trailing semicolon.
    end = close_brace + 1

    while end < len(text) and text[end].isspace():
        end += 1

    if end < len(text) and text[end] == ";":
        end += 1

    return (
        struct_name,
        parse_block(body),
        end,
    )


def parse_structs(text: str):
    """
    Parse all structs in the input.

    Returns:
        [(struct_name, items), ...]
    """
    text = strip_comments(text)

    structs = []

    pattern = re.compile(
        r"\bstruct\s+([A-Za-z_]\w*)\s*\{",
        re.MULTILINE,
    )

    search_pos = 0

    while True:
        match = pattern.search(text, search_pos)

        if not match:
            break

        struct_name, items, end = parse_struct_at(text, match)

        structs.append((struct_name, items))

        search_pos = end

    return structs


def generate_items(items, indent=1):
    """Generate visitor definitions recursively."""
    lines = []

    for item in items:
        prefix = "\t" * indent

        if item["type"] == "PREPROCESSOR":
            # Directives should not receive indentation.
            lines.append(item["value"])

        elif item["type"] == "union":
            lines.append(f"{prefix}//BEGIN_UNION()")
            lines.extend(generate_items(item["items"], indent + 1))
            lines.append(f"{prefix}//END_UNION()")

        else:
            lines.append(f"{prefix}//{item['type']}({item['name']})")

    return lines


def generate_struct(struct_name: str, items):
    """Generate one BEGIN_VISIT block."""
    lines = [f"BEGIN_VISIT({struct_name})"]

    lines.extend(generate_items(items))

    lines.append("END_VISIT()")

    return "\n".join(lines)


def convert(text: str) -> str:
    """
    Convert structs while preserving preprocessor directives that occur
    around structs.

    Example input:

        #ifdef FOO
        struct Foo
        {
            int value;
        };
        #else
        struct Bar
        {
            int value;
        };
        #endif

    Produces:

        #ifdef FOO
        BEGIN_VISIT(Foo)
            FIELD(value)
        END_VISIT()
        #else
        BEGIN_VISIT(Bar)
            FIELD(value)
        END_VISIT()
        #endif
    """
    text = strip_comments(text)

    output = []

    pattern = re.compile(
        r"\bstruct\s+([A-Za-z_]\w*)\s*\{",
        re.MULTILINE,
    )

    search_pos = 0

    while search_pos < len(text):
        struct_match = pattern.search(text, search_pos)

        # Find the next relevant preprocessor directive.
        directive_match = PREPROCESSOR_RE.search(text, search_pos)

        if struct_match is None and directive_match is None:
            break

        # Determine which comes first.
        if (
            directive_match is not None
            and (
                struct_match is None
                or directive_match.start() < struct_match.start()
            )
        ):
            directive = directive_match.group(0).strip()

            output.append(directive)

            search_pos = directive_match.end()

            continue

        # We have a struct.
        struct_name, items, end = parse_struct_at(text, struct_match)

        output.append(generate_struct(struct_name, items))

        search_pos = end

    return "\n\n".join(output)


def main():
    parser = argparse.ArgumentParser(description=("Generate visitor definitions from D2MOO C/C++ struct definitions."))

    parser.add_argument("input", help="Input file")

    parser.add_argument("output", help="Output file")

    args = parser.parse_args()

    with open(args.input, "r", encoding="utf-8") as f:
        input_text = f.read()

    output = []

    output.append("#pragma once")
    output.append("")
    output.append("")
    output.append("#include <DiffContext.h>")
    output.append("#include <DiffVisitor.h>")
    output.append("#include <Macros.h>")
    output.append("#include <TypeId.h>")
    output.append("#include <TypeRegistration.h>")
    output.append("")
    output.append("")

    output.append(
        f"#include <{normalize_include_path(args.input)}>"
    )

    output.append("")
    output.append("")

    output.append(convert(input_text))
    output.append("")

    output_path = Path(args.output)
    output_path.parent.mkdir(parents=True, exist_ok=True)

    with open(output_path, "w", encoding="utf-8") as f:
        f.write("\n".join(output))


if __name__ == "__main__":
    main()
