cmake_minimum_required(VERSION 3.12.0)
project(SargassoEngine VERSION 0.1.0)

cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (RELEASE)
    set(CMAKE_CXX_FLAGS "-pedantic -Wall -Werror -Ofast")
else(RELEASE)
    set(CMAKE_CXX_FLAGS "-pedantic -Wall -Werror -O0 -g")
endif(RELEASE)

# GLFW flags
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/glad")
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/btl")
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/sml")

file(GLOB_RECURSE ALL_SOURCE_FILES "${PROJECT_SOURCE_DIR}/sargasso/*.cc")

message(STATUS "Including files: ${ALL_SOURCE_FILES}")

# ENGINE LIBRARY
add_library(SargassoEngine ${ALL_SOURCE_FILES})

set_target_properties(SargassoEngine
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

find_package(OpenGL REQUIRED)
find_library(sml third_party/sml)

target_compile_definitions(SargassoEngine PRIVATE
        "SARGASSO_ENGINE_VERSION=${CMAKE_PROJECT_VERSION}")

# Utility libraries
target_link_libraries(SargassoEngine sml)

# Rendering libraries
target_link_libraries(SargassoEngine glad)
target_link_libraries(SargassoEngine glfw)
target_link_libraries(SargassoEngine OpenGL::GL)

target_include_directories(SargassoEngine PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}")

# ENGINE TESTS
if (SARGASSO_RUN_TESTS)
    set(CMAKE_CXX_FLAGS "-pedantic -Wall -Werror -O0 -g")

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

    add_custom_command(
        TARGET SargassoTests
        DEPENDS SargassoTests SargassoEngine
        COMMAND "${CMAKE_BINARY_DIR}/SargassoTests"
    )
endif(SARGASSO_RUN_TESTS)
