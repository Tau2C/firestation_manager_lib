# tests/CMakeLists.txt

# Gather all test files
file(GLOB TEST_SOURCES "*.cpp")

# Build test binary
add_executable(test_executable ${TEST_SOURCES})

# Link the library
target_link_libraries(test_executable
  PRIVATE
    firestation_manager_lib
    gtest
    gtest_main
    pqxx
)

# This automatically pulls in the library's include path
target_include_directories(test_executable PRIVATE
  ${CMAKE_SOURCE_DIR}/include/include  # this reflects your include/include/ path
)

# Google Test integration
include(GoogleTest)
gtest_discover_tests(test_executable)
