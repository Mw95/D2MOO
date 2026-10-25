# Note :
# Tests in static libraries might not get registered, see https://github.com/onqtam/doctest/blob/master/doc/markdown/faq.md#why-are-my-tests-in-a-static-library-not-getting-registered
# For this reason, and because it is interesting to have individual
# test executables for each library, it is suggested not to put tests directly in the libraries (even though doctest advocates this usage)
# Creating multiple executables is of course not mandatory, and one could use the same executable with various command lines to filter what tests to run.

add_executable(D2WinTests D2WinTests.cpp D2WinTestDefines.h D2WinTestHelpers.h)

target_sources(D2WinTests
  PRIVATE
    D2WinAccountListTests.cpp
    D2WinAnimImageTests.cpp
    D2WinArchiveTests.cpp
    D2WinButtonTests.cpp
    D2WinCompTests.cpp
    D2WinEditBoxTests.cpp
    D2WinFontTests.cpp
    D2WinImageTests.cpp
    D2WinListTests.cpp
    D2WinMainTests.cpp
    D2WinPaletteTests.cpp
    D2WinPopUpTests.cpp
    D2WinProgressBarTests.cpp
    D2WinScrollBarTests.cpp
    D2WinSmackTests.cpp
    D2WinTextBoxTests.cpp
    D2WinTimerTests.cpp
    D2WRegisterTests.cpp
)

get_target_property(D2WinTestsSources D2WinTests SOURCES)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${D2WinTestsSources})

if(MSVC)
    target_compile_options(D2WinTests PRIVATE /bigobj)
endif()

target_include_directories(D2WinTests PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(D2WinTests PRIVATE doctest::doctest TestDefinitions TestUtilities VisitorFramework Fog D2CMP D2Gfx D2Lang Storm D2Sound ${D2WinImplName})
target_compile_features(D2WinTests PRIVATE cxx_std_17)

set_target_properties(D2WinTests PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../testWorkingDirectory
)

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME D2WinTests.unittests
    COMMAND D2WinTests ${TEST_RUNNER_PARAMS}
    WORKING_DIRECTORY $<TARGET_PROPERTY:D2WinTests,VS_DEBUGGER_WORKING_DIRECTORY>
)
