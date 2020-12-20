
#include "sargasso/front_end/utility/shader_loader.h"

#include "sargasso/common/containers.h"
#include "sargasso/common/log.h"

#include <GL/glew.h>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <vector>

using namespace SargassoEngine::FrontEnd::Utility;
using namespace SargassoEngine::Common;

using ShaderType = ShaderLoader::ShaderType;

constexpr const char* SHADER_VERTEX_FILE_PATH = "src/front_end/utility/shaders/basic_vertex.glsl";
constexpr const char* SHADER_FRAGMENT_FILE_PATH =
    "src/front_end/utility/shaders/basic_fragment.glsl";

GLuint ShaderLoader::load_default_shaders() {
    log("Creating shaders");

    // Create the shaders
    GLuint vertex_shader_id = load_shader(SHADER_VERTEX_FILE_PATH, ShaderType::Vertex);
    logf("Vertex shader id #%", vertex_shader_id);
    GLuint frag_shader_id = load_shader(SHADER_FRAGMENT_FILE_PATH, ShaderType::Fragment);
    logf("Fragment shader id #%", frag_shader_id);

    // Link the program
    log("Linking program");
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, frag_shader_id);
    glLinkProgram(program_id);
    logf("Program shader id #%", program_id);

    // Check the program
    GLint success = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);

    if (!success) {
        int log_length;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
        DynamicArray<char> program_error_message((size_t)log_length);
        glGetProgramInfoLog(program_id, log_length, NULL, program_error_message.data());
        throw std::runtime_error(program_error_message.data());
    }

    glDetachShader(program_id, vertex_shader_id);
    glDeleteShader(vertex_shader_id);

    glDetachShader(program_id, frag_shader_id);
    glDeleteShader(frag_shader_id);

    return program_id;
}

GLuint ShaderLoader::load_shader(const std::string& shader_path, ShaderType shader_type) {
    try {
        const std::string& shader = File::read_file(shader_path);
        return create_shader(shader.c_str(), shader_type);
    } catch (const std::string& exception) {
        logf_error("Failed to load shader '%'\n> Error: %", shader_path, exception);
        return 0;
    }
}

GLuint ShaderLoader::create_shader(const char* shader_code, ShaderType shader_type) {
    GLuint shader_id = glCreateShader(shader_type);

    glShaderSource(shader_id, 1, &shader_code, NULL);
    glCompileShader(shader_id);

    GLint success = GL_FALSE;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (!success) {
        int log_length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

        DynamicArray<char> vertex_shader_error_message((size_t)log_length);
        glGetShaderInfoLog(shader_id, log_length, NULL, vertex_shader_error_message.data());

        throw std::string(vertex_shader_error_message.data());
    }

    return shader_id;
}
