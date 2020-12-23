#ifndef SARGASSO_ENGINE_OPENGL_SHADER_H
#define SARGASSO_ENGINE_OPENGL_SHADER_H

#include "sargasso/front_end/utility/shader_type.h"

#include <glad/glad.h>

#include <string>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

constexpr const char* DEFAULT_FRAGMENT_SHADER =
    "#version 110\n"
    "varying vec4 color;\n"
    "void main() { gl_FragColor = color; }\n\0";

constexpr const char* DEFAULT_VERTEX_SHADER =
    "#version 110\n"
    "uniform mat4 mvp;\n"
    "varying vec4 color;\n"
    "attribute vec3 vertex_position;\n"
    "attribute vec4 vertex_color;\n"
    "void main() {\n"
    "gl_Position = mvp * vec4(vertex_position, 1.0);\n"
    "color = vertex_color;\n"
    "}\n\0";

class Shader {
   public:
    Shader(ShaderType shader_type, const char* code);
    ~Shader();

    GLuint get_id() const;
    ShaderType get_type() const;
    void compile() const;

    static const Shader& default_vertex();
    static const Shader& default_fragment();

   private:
    GLuint _shader_id;
    ShaderType _shader_type;
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
