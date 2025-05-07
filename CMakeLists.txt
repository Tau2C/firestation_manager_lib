cmake_minimum_required(VERSION 3.16)
project(firestation_manager_lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find libpqxx
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

add_library(firestation_manager_lib STATIC
  src/utils.cpp
  src/db_manager.cpp
  src/firefighter_repository.cpp
  src/bank_repository.cpp
  src/medical_examination_repository.cpp
  src/examination_type.cpp
  src/training_repository.cpp
  src/firefighter_training_repository.cpp
)

target_include_directories(firestation_manager_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PQXX_INCLUDE_DIRS}
)

target_link_libraries(firestation_manager_lib
  PUBLIC
    ${PQXX_LIBRARIES}
)
