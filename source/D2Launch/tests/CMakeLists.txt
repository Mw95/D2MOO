# Tests comparing the D2MOO implementation of D2Launch with the original D2Launch.dll (1.10f),
# which must be present in the test working directory.

add_executable(D2LaunchTests
  D2LaunchTests.cpp
  D2LaunchTestFixtures.h
)

if(D2MOO_ORDINALS_VERSION STREQUAL "1.10f")
  target_sources(D2LaunchTests
    PRIVATE
      D2LaunchCharListTests.cpp
      D2LaunchCharSelTests.cpp
      D2LaunchDataTests.cpp
      D2LaunchFilterTests.cpp
      D2LaunchMenuTests.cpp
      D2LaunchSaveTests.cpp
  )
endif()

# Only the header-only parts of TestDefinitions (MOO_CHECK_EQ) are used, it is not linked to avoid depending on D2Common
target_include_directories(D2LaunchTests PRIVATE ${CMAKE_CURRENT_LIST_DIR} $<TARGET_PROPERTY:TestDefinitions,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(D2LaunchTests PRIVATE doctest::doctest TestUtilities VisitorFramework D2CommonDefinitions Fog Storm D2Gfx D2Lang D2Net D2Sound D2MCPClient Bnclient D2Win ${D2LaunchImplName})
target_compile_features(D2LaunchTests PRIVATE cxx_std_17)

set_target_properties(D2LaunchTests PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../testWorkingDirectory
)

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME D2LaunchTests.unittests
    COMMAND D2LaunchTests ${TEST_RUNNER_PARAMS}
    WORKING_DIRECTORY $<TARGET_PROPERTY:D2LaunchTests,VS_DEBUGGER_WORKING_DIRECTORY>
)
set_tests_properties(D2LaunchTests.unittests PROPERTIES LABELS "requires-original-dlls")
