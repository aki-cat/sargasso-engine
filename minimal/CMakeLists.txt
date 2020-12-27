cmake_minimum_required(VERSION 3.12.0)
project(Minimal VERSION 0.1.0)
cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Werror")

file(GLOB_RECURSE EXAMPLE_ALL_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cc")
add_executable(Minimal ${EXAMPLE_ALL_SOURCE_FILES})

add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/glad")
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/sml")
find_package(OpenGL REQUIRED)

target_link_libraries(Minimal SML)
target_link_libraries(Minimal glad)
target_link_libraries(Minimal glfw)
target_link_libraries(Minimal OpenGL::GL)

set_target_properties(Minimal
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(Minimal PUBLIC "${PROJECT_BINARY_DIR}"
                                          "${PROJECT_SOURCE_DIR}"
                                          "${PROJECT_SOURCE_DIR}/third_party/glfw/deps")
