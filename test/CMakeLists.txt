cmake_minimum_required(VERSION 3.16)
project(FirestationManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(lib)

add_subdirectory(tests)