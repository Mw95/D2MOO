# Tests comparing the D2MOO implementation of D2Win with the original D2Win.dll (1.10f),
# which must be present in the test working directory.

add_executable(D2WinTests
  D2WinTests.cpp
  D2WinTestFixtures.h
  D2WinControlFixtures.h
  D2WinFontFixtures.h
)

if(D2MOO_ORDINALS_VERSION STREQUAL "1.10f")
  target_sources(D2WinTests
    PRIVATE
      D2WinButtonTests.cpp
      D2WinControlTests.cpp
      D2WinFontTests.cpp
      D2WinSimpleControlTests.cpp
  )
endif()

target_include_directories(D2WinTests PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(D2WinTests PRIVATE doctest::doctest TestUtilities VisitorFramework D2CommonDefinitions Fog Storm D2CMP D2Gfx D2Lang D2Sound ${D2WinImplName})
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
set_tests_properties(D2WinTests.unittests PROPERTIES LABELS "requires-original-dlls")
