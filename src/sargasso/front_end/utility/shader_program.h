#ifndef SARGASSO_ENGINE_SHADER_PROGRAM_H
#define SARGASSO_ENGINE_SHADER_PROGRAM_H

#include "sargasso/front_end/utility/shader.h"
#include "sargasso/front_end/utility/uniform_type.h"

#include <glad/glad.h>

#include <string>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

class ShaderProgram {
   public:
    explicit ShaderProgram();
    ~ShaderProgram();

    void attach(const Shader& shader);
    void detach(const ShaderType shader_type);
    void link() const;

    void use() const;

    void set_uniform(UniformType uniform_type, const std::string& uniform_symbol, void* data,
                     size_t data_count) const;
    void set_attribute(const std::string& attribute_symbol, const GLenum attribute_type,
                       size_t buffer_unit_size, size_t data_count, size_t data_offset) const;

   private:
    GLuint _shader_program;
    GLuint _vertex_shader;
    GLuint _fragment_shader;
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
