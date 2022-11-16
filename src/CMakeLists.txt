cmake_minimum_required(VERSION 3.12.0)
project(SargassoEngine VERSION 0.1.0)

include(ExternalProject)

cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0002 NEW)
cmake_policy(SET CMP0048 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(ALLOW_DUPLICATE_CUSTOM_TARGETS True)

message(STATUS "Compile flags: ${CMAKE_CXX_FLAGS}")

# GLFW flags
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(PHYSFS_BUILD_STATIC ON)
set(PHYSFS_BUILD_SHARED OFF)
set(PHYSFS_BUILD_TEST OFF)

execute_process(
    COMMAND
    python gl3w_gen.py --ext --root
    ${PROJECT_BINARY_DIR}/third_party/gl3w WORKING_DIRECTORY
    ${PROJECT_SOURCE_DIR}/third_party/gl3w
)

add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/physfs")

add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/gl3w")
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/btl")
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/sml")

file(GLOB_RECURSE
    ALL_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/sargasso/*.cc"
        "${PROJECT_SOURCE_DIR}/sargasso/*.cxx")

message(STATUS "Including files: ${ALL_SOURCE_FILES}")

# ENGINE LIBRARY
add_library(SargassoEngine STATIC ${ALL_SOURCE_FILES})

set_target_properties(SargassoEngine
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

find_package(OpenGL REQUIRED)

if(MSVC)
    target_compile_options(SargassoEngine PRIVATE /W3 /WX /Od)
else(MSVC)
    target_compile_options(SargassoEngine
        PUBLIC -static-libgcc -static-libstdc++
        PRIVATE -Wextra -Werror -Wall -Wno-unknown-pragmas -O0 -g
    )
endif(MSVC)


if(NOT DEFINED SARGASSO_VERBOSE_LOGS)
    set(SARGASSO_VERBOSE_LOGS 3)
endif(NOT DEFINED SARGASSO_VERBOSE_LOGS)

target_compile_definitions(SargassoEngine
    PUBLIC
    "LOG_VERBOSITY_LEVEL=${SARGASSO_VERBOSE_LOGS}"
)
message(STATUS "Verbosity set to level ${SARGASSO_VERBOSE_LOGS}")

target_compile_definitions(SargassoEngine
    PRIVATE
    SARGASSO_ENGINE_VERSION=${CMAKE_PROJECT_VERSION}
)

# Utility libraries
target_link_libraries(SargassoEngine PUBLIC physfs-static)
target_link_libraries(SargassoEngine PUBLIC sml)

# Rendering libraries
target_link_libraries(SargassoEngine PUBLIC gl3w)
target_link_libraries(SargassoEngine PUBLIC glfw)
target_link_libraries(SargassoEngine PUBLIC OpenGL::GL)

target_include_directories(SargassoEngine PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/third_party/physfs/src")

set(SOURCE_SHADER_DIRECTORY ${PROJECT_SOURCE_DIR}/sargasso/shaders)
set(BINARY_SHADER_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)

add_custom_target(SargassoShaders
    COMMENT "Copying built-in shaders to build directory... (${SOURCE_SHADER_DIRECTORY} -> ${BINARY_SHADER_DIRECTORY})"
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SOURCE_SHADER_DIRECTORY} ${BINARY_SHADER_DIRECTORY}
)

add_dependencies(SargassoEngine SargassoShaders)

# ENGINE TESTS
if (SARGASSO_RUN_TESTS)
    add_executable(SargassoTests "${PROJECT_SOURCE_DIR}/tests/tests.cxx")
    target_link_libraries(SargassoTests SargassoEngine)
    target_link_libraries(SargassoTests btl)
    target_link_libraries(SargassoTests sml)

    set_target_properties(SargassoTests
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    )

    target_include_directories(SargassoTests
        PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_SOURCE_DIR}/tests"
    )

    target_compile_definitions(SargassoTests
        PRIVATE
        "LOG_VERBOSITY_LEVEL=${SARGASSO_VERBOSE_LOGS}"
    )

    add_custom_command(
        TARGET SargassoTests
        DEPENDS SargassoTests SargassoEngine
        COMMAND "${CMAKE_BINARY_DIR}/SargassoTests"
    )
endif(SARGASSO_RUN_TESTS)

message(STATUS "Flags: ${CMAKE_CXX_FLAGS}")
