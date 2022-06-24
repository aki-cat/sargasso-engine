#ifndef SARGASSO_SHADER_H_
#define SARGASSO_SHADER_H_

#include "sargasso/common/log.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace sargasso {

constexpr const char* DEFAULT_VERTEX_SHADER =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(vPos, 1.0);\n"
    "}\n";

constexpr const char* DEFAULT_FRAG_SHADER =
    "#version 330 core\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

class ShaderProgram {
   public:
    enum ShaderType { kVertex = GL_VERTEX_SHADER, kFrag = GL_FRAGMENT_SHADER };

    // constructors
    ShaderProgram();
    ShaderProgram(const char* vertexShaderCode, const char* fragShaderCode);

    void use() const {
        glUseProgram(_shaderProgram);
    }

    static unsigned int compileShader(const ShaderProgram::ShaderType shaderType,
                                      const char* shaderCode);
    static bool getShaderCompilationStatus(unsigned int shader);
    static bool getShaderLinkingStatus(unsigned int shaderProgram);

   private:
    unsigned int _shaderProgram;
};

inline ShaderProgram::ShaderProgram() {
    unsigned int vertexShader =
        ShaderProgram::compileShader(ShaderType::kVertex, DEFAULT_VERTEX_SHADER);
    unsigned int fragShader = ShaderProgram::compileShader(ShaderType::kFrag, DEFAULT_FRAG_SHADER);

    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragShader);
    glLinkProgram(_shaderProgram);

    if (!getShaderLinkingStatus(_shaderProgram)) {
        throw std::runtime_error("SHADER LINK ERROR");
    }
}

inline ShaderProgram::ShaderProgram(const char* vertexShaderCode, const char* fragShaderCode) {}

inline unsigned int ShaderProgram::compileShader(const ShaderProgram::ShaderType shaderType,
                                                 const char* shaderCode) {
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    if (!getShaderCompilationStatus(shader)) {
        throw std::runtime_error("SHADER LINK ERROR");
    }

    return shader;
}

inline bool ShaderProgram::getShaderCompilationStatus(unsigned int shader) {
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

inline bool ShaderProgram::getShaderLinkingStatus(unsigned int shaderProgram) {
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

#endif  // SARGASSO_SHADER_H_
