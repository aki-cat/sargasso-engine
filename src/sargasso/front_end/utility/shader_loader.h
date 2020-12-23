#ifndef SARGASSO_ENGINE_SHADER_LOADER_H
#define SARGASSO_ENGINE_SHADER_LOADER_H

#include "sargasso/front_end/utility/shader_type.h"

#include <glad/glad.h>

#include <string>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

class ShaderLoader {
   public:
    static GLuint load_default_shaders();
    static GLuint load_shader(const std::string& shader_path, ShaderType shader_type);
    static GLuint create_shader(const char* shader_code, ShaderType shader_type);
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
