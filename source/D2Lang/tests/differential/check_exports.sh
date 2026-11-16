#!/bin/bash
# Compiles D2MOO's D2Lang with clang for the MSVC ABI and checks that every export of definitions/D2Lang.1.10f.def is
# defined, with the same (mangled) name as the export of the original D2Lang.dll with that ordinal.
#
# Usage: check_exports.sh <path to the original 1.10f D2Lang.dll>
# Requires clang, llvm-nm, the mingw-w64 headers and the pefile python module.
set -e
source "$(dirname "${BASH_SOURCE[0]}")/common.sh"

if [ $# -lt 1 ] || [ ! -f "$1" ]; then
    echo "Usage: $0 <path to the original 1.10f D2Lang.dll>" >&2
    exit 2
fi
ORIGINAL_DLL="$1"

MINGW_CXX_INCLUDE="$(ls -d /usr/lib/gcc/i686-w64-mingw32/*/include/c++ | head -1)"
OBJ_DIR="$BUILD_DIR/msvc_objects"
mkdir -p "$OBJ_DIR"; rm -f "$OBJ_DIR"/*.o
for source in "$SOURCE_DIR"/D2Lang/src/*.cpp "$SOURCE_DIR"/D2Lang/src/D2Unicode/*.cpp; do
    clang++ --target=i686-pc-windows-msvc -fms-extensions -fms-compatibility -fgnuc-version=13 -std=c++17 -w -c -D_X86_=1 \
        -isystem "$MINGW_CXX_INCLUDE" -isystem "$MINGW_CXX_INCLUDE/i686-w64-mingw32" -isystem /usr/share/mingw-w64/include \
        "${D2LANG_INCLUDES[@]}" -DD2LANG_DLL_DECL='__declspec(dllexport)' -DFOG_DLL_DECL= -DSTORM_DLL_DECL= -DD2HELL_DLL_DECL= \
        "-D_Analysis_assume_(x)=" -DNOMINMAX -DWIN32_LEAN_AND_MEAN \
        "$source" -o "$OBJ_DIR/$(basename "$source").o"
done
llvm-nm "$OBJ_DIR"/*.o | awk '$2 ~ /[TDBR]/ {print $3}' | sort -u > "$OBJ_DIR/defined.txt"

python3 -I - "$OBJ_DIR/defined.txt" "$ORIGINAL_DLL" "$SOURCE_DIR/D2Lang/definitions/D2Lang.1.10f.def" <<'PY'
import re, sys, pefile
defined = set(open(sys.argv[1]).read().split())
pe = pefile.PE(sys.argv[2])
original = {e.ordinal: (e.name.decode() if e.name else None) for e in pe.DIRECTORY_ENTRY_EXPORT.symbols}
ok = True
exported = set()
for line in open(sys.argv[3]):
    m = re.match(r'\s+(\S+)\s+@(\d+)', line)
    if not m:
        continue
    name, ordinal = m.group(1), int(m.group(2))
    exported.add(ordinal)
    if original.get(ordinal) and original[ordinal] != name:
        print("NAME MISMATCH", ordinal, name, original[ordinal]); ok = False
    # C++ functions (exported by mangled name) or functions exported by undecorated name
    if name not in defined and not any(d.startswith(p) for d in defined for p in ("_" + name + "@", "@" + name + "@", "?" + name + "@@")):
        print("NOT DEFINED", ordinal, name); ok = False
for ordinal in sorted(set(original) - exported):
    print("NOT EXPORTED", ordinal, original[ordinal] or "")
    ok = False
print("OK" if ok else "FAIL")
sys.exit(0 if ok else 1)
PY
