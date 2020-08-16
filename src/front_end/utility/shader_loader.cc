
#include "shader_loader.h"

#include <GL/glew.h>
#include <iostream>
#include <stdio.h>
#include <string>

using SargassoEngine::FrontEnd::Utility::ShaderLoader;

constexpr const char* SHADER_VERTEX_FILE_PATH = "src/front_end/utility/shaders/basic_vertex.glsl";
constexpr const char* SHADER_FRAGMENT_FILE_PATH =
    "src/front_end/utility/shaders/basic_fragment.glsl";

constexpr const int MAX_LOG_LENGTH = 128;

GLuint ShaderLoader::load() {
    GLint result = GL_FALSE;
    int log_length;

    std::cout << "Creating shaders" << std::endl;
    // Create the shaders
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    const std::string& vertex_shader_code = File::read_file(SHADER_VERTEX_FILE_PATH);

    // Compile Vertex Shader
    std::cout << "Compiling shader: " << SHADER_VERTEX_FILE_PATH << std::endl;
    char const* vertex_source = vertex_shader_code.c_str();
    glShaderSource(vertex_shader_id, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader_id);

    // Check Vertex Shader
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        if (log_length > MAX_LOG_LENGTH) {
            throw "Log Size Overflow: Error log bigger than allocated log size";
        }
        char vertex_shader_error_message[MAX_LOG_LENGTH];
        glGetShaderInfoLog(vertex_shader_id, log_length, NULL, vertex_shader_error_message);
        std::cerr << vertex_shader_error_message << std::endl;
    }

    // Read the Fragment Shader code from the file
    const std::string& frag_shader_code = File::read_file(SHADER_FRAGMENT_FILE_PATH);

    // Compile Fragment Shader
    std::cout << "Compiling shader: " << SHADER_FRAGMENT_FILE_PATH << std::endl;
    char const* frag_source = frag_shader_code.c_str();
    glShaderSource(frag_shader_id, 1, &frag_source, NULL);
    glCompileShader(frag_shader_id);

    // Check Fragment Shader
    glGetShaderiv(frag_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(frag_shader_id, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        if (log_length > MAX_LOG_LENGTH) {
            throw "Log Size Overflow: Error log bigger than allocated log size";
        }
        char frag_shader_error_message[MAX_LOG_LENGTH];
        glGetShaderInfoLog(frag_shader_id, log_length, NULL, frag_shader_error_message);
        std::cerr << frag_shader_error_message << std::endl;
    }

    // Link the program
    std::cout << "Linking program" << std::endl;
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, frag_shader_id);
    glLinkProgram(program_id);

    // Check the program
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        if (log_length > MAX_LOG_LENGTH) {
            throw "Log Size Overflow: Error log bigger than allocated log size";
        }
        char program_error_message[MAX_LOG_LENGTH];
        glGetProgramInfoLog(program_id, log_length, NULL, program_error_message);
        std::cerr << program_error_message << std::endl;
    }

    glDetachShader(program_id, vertex_shader_id);
    glDeleteShader(vertex_shader_id);

    glDetachShader(program_id, frag_shader_id);
    glDeleteShader(frag_shader_id);

    return program_id;
}
