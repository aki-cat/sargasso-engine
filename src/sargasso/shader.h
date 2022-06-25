#ifndef SARGASSO_SHADER_H_
#define SARGASSO_SHADER_H_

#include "sargasso/common/log.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <sml/matrix4.h>

namespace sargasso {

constexpr const char* DEFAULT_VERTEX_SHADER =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vPos;\n"
    "layout(location = 1) in vec4 vCol;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 transform;\n"
    "out vec4 color;\n"
    "void main() {\n"
    "   color = vCol;\n"
    "   gl_Position = projMatrix * transform * vec4(vPos, 1.0);\n"
    "}\n";

constexpr const char* DEFAULT_FRAG_SHADER =
    "#version 330 core\n"
    "in vec4 color;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    fragColor = color;\n"
    "}\n";

class ShaderProgram {
   public:
    enum ShaderType { kVertex = GL_VERTEX_SHADER, kFrag = GL_FRAGMENT_SHADER };

    // constructors
    ShaderProgram();
    ShaderProgram(const std::string& vertexShaderCode, const std::string& fragShaderCode);

    void use() const;
    void setMat4Uniform(const std::string& var, const sml::Mat4& value) const;

   private:
    uint _shaderProgram;

    static uint linkShader(uint vertexShader, uint fragShader);
    static uint compileShader(const ShaderType shaderType, const std::string& shaderCode);
    static bool getShaderCompilationStatus(uint shader);
    static bool getShaderLinkingStatus(uint shaderProgram);
};

}  // namespace sargasso

#endif  // SARGASSO_SHADER_H_
