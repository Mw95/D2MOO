# Note :
# Tests in static libraries might not get registered, see https://github.com/onqtam/doctest/blob/master/doc/markdown/faq.md#why-are-my-tests-in-a-static-library-not-getting-registered
# For this reason, and because it is interesting to have individual
# test executables for each library, it is suggested not to put tests directly in the libraries (even though doctest advocates this usage)
# Creating multiple executables is of course not mandatory, and one could use the same executable with various command lines to filter what tests to run.

add_executable(VisitorFrameworkTests VisitorFrameworkTests.cpp)
target_link_libraries(VisitorFrameworkTests PRIVATE doctest::doctest VisitorFramework)
target_compile_features(VisitorFrameworkTests PRIVATE cxx_std_17)

set_target_properties(VisitorFrameworkTests PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/workingDirectory
)

target_sources(VisitorFrameworkTests
  PRIVATE
    TestDataStructs.h
    BinaryReaderTests.cpp
    BinaryWriterTests.cpp
    DeserializerTests.cpp
    DiffVisitorTests.cpp
    ObjectRegistryTests.cpp
    PointerFixupsTests.cpp
    SerializerTests.cpp
)    

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME VisitorFrameworkTests.unittests
    COMMAND VisitorFrameworkTests ${TEST_RUNNER_PARAMS}
    WORKING_DIRECTORY $<TARGET_PROPERTY:VisitorFrameworkTests,VS_DEBUGGER_WORKING_DIRECTORY>
)
