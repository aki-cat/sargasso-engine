
#include "sargasso/front_end/utility/shader.h"

#include "sargasso/common/log.h"

#include <glad/glad.h>

using namespace SargassoEngine::FrontEnd::Utility;
using namespace SargassoEngine;

Shader::Shader(ShaderType shader_type, const char* code) : _shader_type(shader_type) {
    _shader_id = glCreateShader(shader_type);
    glShaderSource(_shader_id, 1, &code, NULL);
    compile();
}

Shader::~Shader() { glDeleteShader(_shader_id); }

const Shader& Shader::default_vertex() {
    static const Shader default_vertex_shader =
        Shader(ShaderType::SHADER_TYPE_VERTEX, DEFAULT_VERTEX_SHADER);
    return default_vertex_shader;
}
const Shader& Shader::default_fragment() {
    static const Shader default_fragment_shader =
        Shader(ShaderType::SHADER_TYPE_FRAGMENT, DEFAULT_FRAGMENT_SHADER);
    return default_fragment_shader;
}

GLuint Shader::get_id() const { return _shader_id; }

ShaderType Shader::get_type() const { return _shader_type; }

void Shader::compile() const {
    glCompileShader(_shader_id);

    GLint success = GL_FALSE;
    glGetShaderiv(_shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        const size_t MAX_LOG_LENGTH = 256;
        char error_message[MAX_LOG_LENGTH];
        glGetShaderInfoLog(_shader_id, MAX_LOG_LENGTH, NULL, error_message);
        throw std::runtime_error(error_message);
    }
}
