cmake_minimum_required(VERSION 3.12.0)
project(Sample VERSION 0.1.0)
cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "CMAKE_BUILD_TYPE is '${CMAKE_BUILD_TYPE}'")

add_subdirectory("${PROJECT_SOURCE_DIR}/src")

add_executable(SampleRect "${PROJECT_SOURCE_DIR}/example/rect.cxx")
add_executable(SampleCube "${PROJECT_SOURCE_DIR}/example/cube.cxx")

if(MSVC)
    target_compile_options(SampleRect PRIVATE /W3 /WX /Od)
    target_compile_options(SampleCube PRIVATE /W3 /WX /Od)
else(MSVC)
    target_compile_options(SampleRect PRIVATE -Wextra -pedantic -Werror -Wall -static-libgcc -static-libstdc++ -O0)
    target_compile_options(SampleCube PRIVATE -Wextra -pedantic -Werror -Wall -static-libgcc -static-libstdc++ -O0)
endif(MSVC)

target_link_libraries(SampleRect SargassoEngine)
target_link_libraries(SampleCube SargassoEngine)
