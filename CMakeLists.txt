cmake_minimum_required(VERSION 3.12.0)
project(Sample VERSION 0.1.0)
cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Werror")

add_subdirectory("${PROJECT_SOURCE_DIR}/src")

file(GLOB_RECURSE EXAMPLE_ALL_SOURCE_FILES "${PROJECT_SOURCE_DIR}/example/*.cc")

add_executable(Sample ${EXAMPLE_ALL_SOURCE_FILES})

target_link_libraries(Sample SargassoEngine)
