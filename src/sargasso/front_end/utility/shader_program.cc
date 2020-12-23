
#include "sargasso/front_end/utility/shader_program.h"

#include "sargasso/front_end/utility/shader_type.h"
#include "sargasso/front_end/utility/uniform_type.h"

using namespace SargassoEngine::FrontEnd::Utility;

ShaderProgram::ShaderProgram() {
    _shader_program = glCreateProgram();
    attach(Shader::default_vertex());
    attach(Shader::default_fragment());
    link();
}

ShaderProgram::~ShaderProgram() {
    glDetachShader(_shader_program, _vertex_shader);
    glDetachShader(_shader_program, _fragment_shader);
    glDeleteProgram(_shader_program);
}

void ShaderProgram::attach(const Shader& shader) {
    switch (shader.get_type()) {
        case ShaderType::SHADER_TYPE_FRAGMENT:
            _fragment_shader = shader.get_id();
            break;
        case ShaderType::SHADER_TYPE_VERTEX:
            _vertex_shader = shader.get_id();
            break;
    }
    glAttachShader(_shader_program, shader.get_id());
    link();
}

void ShaderProgram::detach(const ShaderType shader_type) {
    switch (shader_type) {
        case ShaderType::SHADER_TYPE_FRAGMENT:
            glDetachShader(_shader_program, _fragment_shader);
            break;
        case ShaderType::SHADER_TYPE_VERTEX:
            glDetachShader(_shader_program, _vertex_shader);
            break;
    }
    link();
}

void ShaderProgram::link() const {
    glLinkProgram(_shader_program);

    GLint success = GL_FALSE;
    glGetProgramiv(_shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        const size_t MAX_LOG_LENGTH = 256;
        char error_message[MAX_LOG_LENGTH];
        glGetProgramInfoLog(_shader_program, MAX_LOG_LENGTH, NULL, error_message);
        throw std::runtime_error(error_message);
    }
}

void ShaderProgram::use() const { glUseProgram(_shader_program); }

void ShaderProgram::set_uniform(UniformType uniform_type, const std::string& uniform_symbol,
                                void* data, size_t data_count) const {
    GLint uniform_location = glGetUniformLocation(_shader_program, uniform_symbol.c_str());
    UniformDataSender::send_data.at(uniform_type)(uniform_location, data, data_count);
}

void ShaderProgram::set_attribute(const std::string& attribute_symbol, const GLenum attribute_type,
                                  size_t buffer_unit_size, size_t data_count,
                                  size_t data_offset) const {
    GLint attribute_location = glGetAttribLocation(_shader_program, attribute_symbol.c_str());
    glEnableVertexAttribArray(attribute_location);
    glVertexAttribPointer(attribute_location, data_count, attribute_type, GL_FALSE,
                          buffer_unit_size, (void*) data_offset);
}
