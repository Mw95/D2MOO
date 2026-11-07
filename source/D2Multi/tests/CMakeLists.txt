# Tests comparing the D2MOO implementation of D2Multi with the original D2Multi.dll (1.10f),
# which must be present in the test working directory.

add_executable(D2MultiTests
  D2MultiTests.cpp
  D2MultiTestFixtures.h
)

if(D2MOO_ORDINALS_VERSION STREQUAL "1.10f")
  target_sources(D2MultiTests
    PRIVATE
      D2MultiChatTests.cpp
      D2MultiDataTests.cpp
      D2MultiGateTests.cpp
      D2MultiLadderTests.cpp
      D2MultiMotdTests.cpp
      D2MultiTextTests.cpp
      D2MultiUserListTests.cpp
      D2MultiUserTests.cpp
  )
endif()

# Only the header-only parts of TestDefinitions (MOO_CHECK_EQ) are used, it is not linked to avoid depending on D2Common
target_include_directories(D2MultiTests PRIVATE ${CMAKE_CURRENT_LIST_DIR} $<TARGET_PROPERTY:TestDefinitions,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(D2MultiTests PRIVATE doctest::doctest TestUtilities VisitorFramework D2CommonDefinitions D2CMP D2Gfx D2Lang D2MCPClient D2Sound D2Win Fog Storm ${D2MultiImplName})
target_compile_features(D2MultiTests PRIVATE cxx_std_17)

set_target_properties(D2MultiTests PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../testWorkingDirectory
)

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME D2MultiTests.unittests
    COMMAND D2MultiTests ${TEST_RUNNER_PARAMS}
    WORKING_DIRECTORY $<TARGET_PROPERTY:D2MultiTests,VS_DEBUGGER_WORKING_DIRECTORY>
)
set_tests_properties(D2MultiTests.unittests PROPERTIES LABELS "requires-original-dlls")
