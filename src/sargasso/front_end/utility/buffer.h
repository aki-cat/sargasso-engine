#ifndef SARGASSO_ENGINE_BUFFER_H
#define SARGASSO_ENGINE_BUFFER_H

#include <glad/glad.h>

#include <sml/vector3.h>
#include <vector>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

using namespace SML;

class Buffer {
   public:
    Buffer(const char* raw_data, const size_t raw_data_size);
    Buffer(const Vec3* vertices, const size_t vertex_count);
    ~Buffer();
    void render() const;
    GLuint get_id() const;
    size_t get_size() const;

   private:
    GLuint _buffer_id;
    size_t _buffer_size;
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
