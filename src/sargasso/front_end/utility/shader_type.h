#ifndef SARGASSO_ENGINE_FRONT_END_UTILITY_SHADER_TYPE_H
#define SARGASSO_ENGINE_FRONT_END_UTILITY_SHADER_TYPE_H

#include <glad/glad.h>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

enum ShaderType {
    SHADER_TYPE_FRAGMENT = GL_FRAGMENT_SHADER,
    SHADER_TYPE_VERTEX = GL_VERTEX_SHADER
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
