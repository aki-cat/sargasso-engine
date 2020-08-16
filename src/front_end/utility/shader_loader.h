
#include "common/file.h"

#include <GL/glew.h>
#include <string>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

using SargassoEngine::Common::File;

class ShaderLoader {
   public:
    enum ShaderType { Fragment = GL_FRAGMENT_SHADER, Vertex = GL_VERTEX_SHADER };
    static GLuint load_defult_shaders();
    static GLuint load_shader(const std::string& shader_path, ShaderType shader_type);
    static GLuint create_shader(const char* shader_code, ShaderType shader_type);
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine
