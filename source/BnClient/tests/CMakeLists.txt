# Tests comparing the D2MOO implementation of Bnclient with the original Bnclient.dll (1.10f),
# which must be present in the test working directory.

add_executable(BnclientTests
  BnclientTests.cpp
  BnclientTestFixtures.h
)

if(D2MOO_ORDINALS_VERSION STREQUAL "1.10f")
  target_sources(BnclientTests
    PRIVATE
      BnclientCryptoTests.cpp
  )
endif()

# Only the header-only parts of TestDefinitions (MOO_CHECK_EQ) are used, it is not linked to avoid depending on D2Common
target_include_directories(BnclientTests PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/../include/SRP $<TARGET_PROPERTY:TestDefinitions,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(BnclientTests PRIVATE doctest::doctest TestUtilities VisitorFramework D2CommonDefinitions Fog Storm D2Lang wsock32 user32 ${BnclientImplName})
target_compile_features(BnclientTests PRIVATE cxx_std_17)

set_target_properties(BnclientTests PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../testWorkingDirectory
)

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME BnclientTests.unittests
    COMMAND BnclientTests ${TEST_RUNNER_PARAMS}
    WORKING_DIRECTORY $<TARGET_PROPERTY:BnclientTests,VS_DEBUGGER_WORKING_DIRECTORY>
)
set_tests_properties(BnclientTests.unittests PROPERTIES LABELS "requires-original-dlls")
