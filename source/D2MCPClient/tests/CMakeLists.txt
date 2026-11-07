# Tests comparing the D2MOO implementation of D2MCPClient with the original D2MCPClient.dll (1.10f),
# which must be present in the test working directory.

add_executable(D2MCPClientTests
  D2MCPClientTests.cpp
  D2MCPClientTestFixtures.h
  D2MCPClientVisitorDefinitions.h
)

if(D2MOO_ORDINALS_VERSION STREQUAL "1.10f")
  target_sources(D2MCPClientTests
    PRIVATE
      D2MCPClientConnectionTests.cpp
      D2MCPClientMessageTests.cpp
      D2MCPClientRequestTests.cpp
      D2MCPClientStateTests.cpp
  )
endif()

# Only the header-only parts of TestDefinitions (MOO_CHECK_EQ) are used, it is not linked to avoid depending on D2Common
target_include_directories(D2MCPClientTests PRIVATE ${CMAKE_CURRENT_LIST_DIR} $<TARGET_PROPERTY:TestDefinitions,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(D2MCPClientTests PRIVATE doctest::doctest TestUtilities VisitorFramework Fog Storm ${D2MCPClientImplName})
target_compile_features(D2MCPClientTests PRIVATE cxx_std_17)

set_target_properties(D2MCPClientTests PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../testWorkingDirectory
)

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME D2MCPClientTests.unittests
    COMMAND D2MCPClientTests ${TEST_RUNNER_PARAMS}
    WORKING_DIRECTORY $<TARGET_PROPERTY:D2MCPClientTests,VS_DEBUGGER_WORKING_DIRECTORY>
)
set_tests_properties(D2MCPClientTests.unittests PROPERTIES LABELS "requires-original-dlls")
