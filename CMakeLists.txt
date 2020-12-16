cmake_minimum_required(VERSION 3.12.0)
project(SargassoEngine VERSION 0.1.0)

cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GLFW flags
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/sml")

file(GLOB ALL_SOURCE_FILES src/**/*.cc src/**/*.cpp src/**/*.cxx src/**/*.c)

message(STATUS "Including files: ${ALL_SOURCE_FILES}")
add_executable(SargassoEngine ${ALL_SOURCE_FILES})

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_library(SML third_party/sml)

target_compile_definitions(SargassoEngine PUBLIC
        "SARGASSO_ENGINE_VERSION=${SargassoEngine_VERSION_MAJOR}.${SargassoEngine_VERSION_MINOR}")

# Utility libraries
target_link_libraries(SargassoEngine SML)

# Rendering libraries
target_link_libraries(SargassoEngine glfw)
target_link_libraries(SargassoEngine GLEW::GLEW)
target_link_libraries(SargassoEngine OpenGL::GL)

target_include_directories(SargassoEngine PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src")
