cmake_minimum_required(VERSION 3.12.0)
project(mini VERSION 0.1.0)
cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT DEFINED MINI_BACKEND_API)
    message(ERROR "No backend defined. Try 'opengl' or 'vulkan'")
endif(NOT DEFINED MINI_BACKEND_API)

if(${MINI_BACKEND_API} MATCHES opengl)
    find_package(OpenGL REQUIRED)
    set(MINI_TARGET_EXECUTABLE minigl)
    set(MINI_SOURCE_MAIN "${PROJECT_SOURCE_DIR}/mini_opengl.cxx")
endif(${MINI_BACKEND_API} MATCHES opengl)

if(${MINI_BACKEND_API} MATCHES vulkan)
    set(MINI_TARGET_EXECUTABLE minivk)
    set(MINI_SOURCE_MAIN "${PROJECT_SOURCE_DIR}/mini_vulkan.cxx")
endif(${MINI_BACKEND_API} MATCHES vulkan)

file(GLOB_RECURSE MINI_SOURCE_FILES ${MINI_SOURCE_MAIN}
                                    "${PROJECT_SOURCE_DIR}/sargasso/common/io.cxx"
                                    "${PROJECT_SOURCE_DIR}/sargasso/common/log.cxx")

message(STATUS "Source files: ${MINI_SOURCE_FILES}")
message(STATUS "TargetExecutable: ${MINI_TARGET_EXECUTABLE}")

add_executable(${MINI_TARGET_EXECUTABLE} ${MINI_SOURCE_FILES})

if(MSVC)
    target_compile_options(${MINI_TARGET_EXECUTABLE} PRIVATE /WX /W4 /Od)
else(MSVC)
    target_compile_options(${MINI_TARGET_EXECUTABLE} PRIVATE
        -Werror -Wall -Wno-unknown-pragmas -O0 -g -static-libgcc -static-libstdc++)
endif(MSVC)

if (DEFINED LOG_LEVEL)
    target_compile_definitions(${MINI_TARGET_EXECUTABLE} PUBLIC "-DLOG_VERBOSITY_LEVEL=${LOG_LEVEL}")
endif(DEFINED LOG_LEVEL)

add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/sml")
target_link_libraries(${MINI_TARGET_EXECUTABLE} sml)
target_link_libraries(${MINI_TARGET_EXECUTABLE} glfw)

if(${MINI_BACKEND_API} MATCHES opengl)
    execute_process(
        COMMAND
        python gl3w_gen.py --ext --root
        ${PROJECT_BINARY_DIR}/third_party/gl3w WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR}/third_party/gl3w)

    add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/gl3w")

    target_link_libraries(${MINI_TARGET_EXECUTABLE} gl3w)
    target_link_libraries(${MINI_TARGET_EXECUTABLE} OpenGL::GL)
endif(${MINI_BACKEND_API} MATCHES opengl)


if(${MINI_BACKEND_API} MATCHES vulkan)
    add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/vulkan")
    target_link_libraries(${MINI_TARGET_EXECUTABLE} vulkan)
endif(${MINI_BACKEND_API} MATCHES vulkan)

set_target_properties(${MINI_TARGET_EXECUTABLE}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(${MINI_TARGET_EXECUTABLE} PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/sargasso")
