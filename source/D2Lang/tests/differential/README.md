# D2Lang differential tests

These tests compare D2MOO's D2Lang with the original 1.10f `D2Lang.dll` by calling both with the same inputs and
comparing the results, including the full contents of output buffers (to catch differences in null terminators or
buffer overruns). They run on Linux, using mingw-w64 to build the tests and wine to run them.

- D2MOO's D2Lang (and D2Hell's `Archive.cpp`) is linked statically into `D2LangDiffTests.exe`.
- The original `D2Lang.dll` is loaded at runtime, and its functions are retrieved by ordinal.
- Stub `Fog.dll` and `Storm.dll` (`FogStub.cpp`, `StormStub.cpp`) export the functions imported by the original DLL
  with the same ordinals. Both implementations use the same fake allocator and file functions (`FakeImpl.h`); files
  are read from the working directory, `build/`.
- `generate_data.py` generates the game data used by the tests: string tables (`.tbl`), system code page maps and
  `data\local\use`.

The original `D2Lang.dll` is not part of the repository, its path must be given to the scripts.

## Requirements

- mingw-w64 (`i686-w64-mingw32-g++`), e.g. `apt install g++-mingw-w64-i686`
- 32-bit wine, e.g. `dpkg --add-architecture i386 && apt update && apt install wine32:i386 wine`
- python 3
- For `check_exports.sh`: clang, llvm-nm and the `pefile` python module
- For `unittests.sh`: the `external/doctest` submodule

## Scripts

| Script | Description |
| --- | --- |
| `run.sh <D2Lang.dll> [group]` | Builds and runs the differential tests. Without a group, also runs the `locale` group for several languages and the `strtable` group without the expansion strings. |
| `unittests.sh [doctest arguments]` | Builds and runs the unit tests of `../D2LangTests.cpp` under wine. |
| `check_exports.sh <D2Lang.dll>` | Compiles D2Lang with clang for the MSVC ABI and checks that each ordinal of `definitions/D2Lang.1.10f.def` is defined, with the same mangled name as in the original DLL, and that no export of the original is missing. |

The build output goes to `build/` (or `$BUILD_DIR`).

## Test groups

| Group | Functions |
| --- | --- |
| `locale` | `STRTABLE_GetLanguage`, `STRTABLE_GetSystemLanguage`, `STRTABLE_GetLanguageCode`, `STR_GroupInt64Digits`, `STR_GroupUint64DigitsWithSuffix`. Must be the first group run by a process, as the language is cached; set the language with `TEST_LANGUAGE`. |
| `collation` | `strcoll`, `strncoll`, `strstri`, `isLeftToRight` |
| `audit_char` | Character classification, case conversion and comparison of every UCS-2 character |
| `audit_str` | String functions (`strcmp`, `strncpy`, `strstr`, `isLineBreak`, ...) |
| `audit_conv` | `toUnicode`, `toUtf`, `utf8ToUnicode`, `win2Unicode`, `unicode2Win` |
| `audit_misc` | `sprintf`, `CRC16_CalculateChecksum`, `STR_GroupIntDigits`, `STR_GroupUintDigits` |
| `widths` | `utfwidth`, `utfnwidth`, `unicodenwidth` |
| `sysmap` | `loadSysMap`, `unloadSysMap`, `sys2Unicode`, `unicode2Sys`, `sysWidth`, `unicodeWidth` with and without a map |
| `personalize` | `Personalize` |
| `strtable` | `D2LANG_LoadStrings`, `D2LANG_FreeStrings`, `D2LANG_GetStringHash`, `D2LANG_GetStringFromTblIndex`, `D2LANG_GetTblIndex`, `D2LANG_GetStringByReferenceString`. Set `TEST_EXPANSION=0` to test without the expansion strings. |

The inputs are random; use `SEED` to try other inputs. Inputs for which the original has undefined behavior (such as
reading past the end of a string) are not tested.
