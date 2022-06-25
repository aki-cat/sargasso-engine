
#include "sargasso/shader.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace sargasso {

ShaderProgram::ShaderProgram() : ShaderProgram(DEFAULT_VERTEX_SHADER, DEFAULT_FRAG_SHADER) {}

ShaderProgram::ShaderProgram(const std::string& vertexShaderCode,
                             const std::string& fragShaderCode) {
    uint vertexShader = ShaderProgram::compileShader(ShaderType::kVertex, vertexShaderCode);
    uint fragShader = ShaderProgram::compileShader(ShaderType::kFrag, fragShaderCode);

    _shaderProgram = linkShader(vertexShader, fragShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

void ShaderProgram::use() const {
    glUseProgram(_shaderProgram);
}

void ShaderProgram::setMat4Uniform(const std::string& var, const sml::Mat4& value) const {
    const int mat4Location = glGetUniformLocation(_shaderProgram, var.c_str());
    glUniformMatrix4fv(mat4Location, 1, false, (const float*) &value);
}

uint ShaderProgram::compileShader(const ShaderType shaderType, const std::string& shaderCode) {
    uint shader = glCreateShader(shaderType);
    const char* rawCode = shaderCode.c_str();
    glShaderSource(shader, 1, &rawCode, NULL);
    glCompileShader(shader);

    if (!getShaderCompilationStatus(shader)) {
        throw std::runtime_error("SHADER LINK ERROR");
    }

    return shader;
}

uint ShaderProgram::linkShader(uint sVertex, uint sFrag) {
    uint program = glCreateProgram();
    glAttachShader(program, sVertex);
    glAttachShader(program, sFrag);
    glLinkProgram(program);
    if (!getShaderLinkingStatus(program)) {
        throw std::runtime_error("SHADER LINK ERROR");
    }
    return program;
}

bool ShaderProgram::getShaderCompilationStatus(uint shader) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        common::Log("Shader").error("Error compiling shader: %s", infoLog);
        return false;
    }
    return true;
}

bool ShaderProgram::getShaderLinkingStatus(uint shaderProgram) {
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        common::Log("Shader").error("Error linking shader: %s", infoLog);
        return false;
    }
    return true;
}

}  // namespace sargasso
