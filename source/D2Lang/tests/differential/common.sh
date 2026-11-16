# Shared settings of the scripts of this directory (sourced, not executed).
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd "$SCRIPT_DIR/../../../.." && pwd)"
SOURCE_DIR="$REPO_DIR/source"
BUILD_DIR="${BUILD_DIR:-$SCRIPT_DIR/build}"

CXX_MINGW="${CXX_MINGW:-i686-w64-mingw32-g++}"

mkdir -p "$BUILD_DIR/shim"
# D2MOO includes <Windows.h>, mingw-w64 only provides <windows.h>
[ -f "$BUILD_DIR/shim/Windows.h" ] || echo '#include <windows.h>' > "$BUILD_DIR/shim/Windows.h"

D2LANG_INCLUDES=(
    -I"$BUILD_DIR/shim"
    -I"$SOURCE_DIR/D2Lang/include"
    -I"$SOURCE_DIR/D2CommonDefinitions/include"
    -I"$SOURCE_DIR/Fog/include"
    -I"$SOURCE_DIR/Storm/include"
    -I"$SOURCE_DIR/D2Hell/include"
)
D2LANG_STATIC_DEFINES=(
    -DD2LANG_DLL_DECL= -DFOG_DLL_DECL= -DSTORM_DLL_DECL= -DD2HELL_DLL_DECL=
    "-D_Analysis_assume_(x)=" -DNOMINMAX -DWIN32_LEAN_AND_MEAN -DD2_VERSION_110F
)
D2LANG_SOURCES=(
    "$SOURCE_DIR"/D2Lang/src/*.cpp
    "$SOURCE_DIR"/D2Lang/src/D2Unicode/*.cpp
    "$SOURCE_DIR"/D2Hell/src/Archive.cpp
)

# Builds an executable with D2MOO's D2Lang linked statically, using fake Fog/Storm functions.
build_with_d2lang() {
    local output="$1"; shift
    "$CXX_MINGW" -std=c++17 -O1 -g -fms-extensions -w \
        "${D2LANG_INCLUDES[@]}" "${D2LANG_STATIC_DEFINES[@]}" "$@" \
        "${D2LANG_SOURCES[@]}" "$SCRIPT_DIR/FakeFogStorm.cpp" \
        -o "$output" -static -Wl,--enable-stdcall-fixup
}

run_wine() {
    (cd "$BUILD_DIR" && WINEDEBUG=-all wine "$@")
}
