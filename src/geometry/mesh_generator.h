
#include <GL/glew.h>
#include <glm/vec4.hpp>

namespace SargassoEngine {
namespace Geometry {

template <size_t n>
struct Mesh {
    GLfloat vertex_points[n];
};

using SquareMesh = Mesh<24>;

class MeshGenerator {
   public:
    MeshGenerator() = delete;
    ~MeshGenerator() = delete;
    static SquareMesh generate_square();
};

}  // namespace Geometry
}  // namespace SargassoEngine
