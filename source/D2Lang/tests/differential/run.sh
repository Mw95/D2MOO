#!/bin/bash
# Builds and runs the differential tests of D2MOO's D2Lang against the original 1.10f D2Lang.dll, under wine.
#
# Usage: run.sh <path to the original 1.10f D2Lang.dll> [group]
# Without a group, runs all the groups, then the "locale" and "strtable" groups again with other settings.
# Environment variables: SEED, TEST_LANGUAGE, TEST_EXPANSION (see D2LangDiffTests.cpp), BUILD_DIR, CXX_MINGW.
set -e
source "$(dirname "${BASH_SOURCE[0]}")/common.sh"

if [ $# -lt 1 ] || [ ! -f "$1" ]; then
    echo "Usage: $0 <path to the original 1.10f D2Lang.dll> [group]" >&2
    exit 2
fi
ORIGINAL_DLL="$1"; shift

cp "$ORIGINAL_DLL" "$BUILD_DIR/D2Lang.dll"
python3 -I "$SCRIPT_DIR/generate_data.py" "$BUILD_DIR" > /dev/null

# Fog.dll and Storm.dll stubs, loaded by the original D2Lang.dll
"$CXX_MINGW" -O1 -shared -static-libgcc -static-libstdc++ "$SCRIPT_DIR/FogStub.cpp" "$SCRIPT_DIR/Fog.def" -o "$BUILD_DIR/Fog.dll" -Wl,--enable-stdcall-fixup
"$CXX_MINGW" -O1 -shared -static-libgcc -static-libstdc++ "$SCRIPT_DIR/StormStub.cpp" "$SCRIPT_DIR/Storm.def" -o "$BUILD_DIR/Storm.dll" -Wl,--enable-stdcall-fixup

build_with_d2lang "$BUILD_DIR/D2LangDiffTests.exe" "$SCRIPT_DIR/D2LangDiffTests.cpp"

if [ $# -ge 1 ]; then
    run_wine D2LangDiffTests.exe "$@"
    exit $?
fi

status=0
run_wine D2LangDiffTests.exe || status=1
for language in 3 6 7 12 13; do
    TEST_LANGUAGE=$language run_wine D2LangDiffTests.exe locale || status=1
done
TEST_EXPANSION=0 run_wine D2LangDiffTests.exe strtable || status=1
# Restore the default language
printf '\0' > "$BUILD_DIR/data/local/use"
exit $status
