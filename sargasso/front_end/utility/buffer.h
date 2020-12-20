#ifndef SARGASSO_ENGINE_BUFFER_H
#define SARGASSO_ENGINE_BUFFER_H

#include <GL/glew.h>
#include <vector>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

class Buffer {
   public:
    Buffer(const std::vector<Vec3>& points);
    ~Buffer();
    void render() const;
    GLuint get_id() const;
    size_t get_buffer_size() const;

   private:
    GLuint _buffer_id;
    size_t _point_count;
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
