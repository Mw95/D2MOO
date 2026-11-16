#!/bin/bash
# Builds and runs the D2LangTests unit tests (../D2LangTests.cpp) under wine.
# Requires the external/doctest submodule. Arguments are passed to doctest.
set -e
source "$(dirname "${BASH_SOURCE[0]}")/common.sh"

build_with_d2lang "$BUILD_DIR/D2LangTests.exe" -I"$REPO_DIR/external/doctest/doctest" "$SCRIPT_DIR/../D2LangTests.cpp"
run_wine D2LangTests.exe "$@"
