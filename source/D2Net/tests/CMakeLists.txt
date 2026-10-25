# Note :
# Tests in static libraries might not get registered, see https://github.com/onqtam/doctest/blob/master/doc/markdown/faq.md#why-are-my-tests-in-a-static-library-not-getting-registered
# For this reason, and because it is interesting to have individual
# test executables for each library, it is suggested not to put tests directly in the libraries (even though doctest advocates this usage)
# Creating multiple executables is of course not mandatory, and one could use the same executable with various command lines to filter what tests to run.

add_executable(D2NetTests D2NetTests.cpp D2NetTestDefines.h D2NetTestHelpers.h)

target_sources(D2NetTests
  PRIVATE
    ClientTests.cpp
    NetTests.cpp
    ServerTests.cpp
)

get_target_property(D2NetTestsSources D2NetTests SOURCES)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${D2NetTestsSources})

target_include_directories(D2NetTests PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(D2NetTests PRIVATE doctest::doctest TestDefinitions TestUtilities VisitorFramework D2CommonDefinitions Fog Storm ws2_32 ${D2NetImplName})
target_compile_features(D2NetTests PRIVATE cxx_std_17)

set_target_properties(D2NetTests PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../testWorkingDirectory
)

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME D2NetTests.unittests
    COMMAND D2NetTests ${TEST_RUNNER_PARAMS}
    WORKING_DIRECTORY $<TARGET_PROPERTY:D2NetTests,VS_DEBUGGER_WORKING_DIRECTORY>
)
