cmake_minimum_required(VERSION 3.12.0)
project(SargassoEngine VERSION 0.1.0)

cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "Compile flags: ${CMAKE_CXX_FLAGS}")

# GLFW flags
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

execute_process(
    COMMAND
    python gl3w_gen.py --ext --root
    ${PROJECT_BINARY_DIR}/third_party/gl3w WORKING_DIRECTORY
    ${PROJECT_SOURCE_DIR}/third_party/gl3w)

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
find_library(sml third_party/sml)

target_compile_definitions(SargassoEngine
    PRIVATE
    SARGASSO_ENGINE_VERSION=${CMAKE_PROJECT_VERSION}
)

# BACKEND DEFINITION
target_compile_definitions(SargassoEngine
    PRIVATE
    SARGASSO_ENGINE_BACKEND=1
)
# /BACKEND DEFINITION


target_compile_options(SargassoEngine PRIVATE -Werror -Wall -Wno-unknown-pragmas -O0 -g -static-libgcc -static-libstdc++)

if(NOT DEFINED SARGASSO_VERBOSE_LOGS)
    set(SARGASSO_VERBOSE_LOGS 3)
endif(NOT DEFINED SARGASSO_VERBOSE_LOGS)

target_compile_definitions(SargassoEngine
    PRIVATE
    "LOG_VERBOSITY_LEVEL=${SARGASSO_VERBOSE_LOGS}"
)
message(STATUS "Verbosity set to level ${SARGASSO_VERBOSE_LOGS}")

# Utility libraries
target_link_libraries(SargassoEngine sml)

# Rendering libraries
target_link_libraries(SargassoEngine gl3w)
target_link_libraries(SargassoEngine glfw)
target_link_libraries(SargassoEngine OpenGL::GL)

target_include_directories(SargassoEngine PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}")

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
