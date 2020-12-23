#ifndef SARGASSO_ENGINE_BUFFER_H
#define SARGASSO_ENGINE_BUFFER_H

#include "sargasso/front_end/utility/shader_program.h"
#include "sargasso/geometry/vertex.h"

#include <glad/glad.h>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

using namespace Geometry;

class Buffer {
   public:
    Buffer(const char* raw_data, const size_t raw_data_size);
    Buffer(const Vertex* vertices, const size_t vertex_count);
    ~Buffer();
    void render(const ShaderProgram& shader_program) const;
    GLuint get_id() const;
    size_t get_size() const;

   private:
    size_t _buffer_size;
    GLuint _buffer_id;
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
