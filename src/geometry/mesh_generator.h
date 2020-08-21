
#include <GL/glew.h>
#include <glm/vec3.hpp>

namespace SargassoEngine {
namespace Geometry {

static const int POINTS_PER_VERTEX = 3;

template <size_t N>
struct MeshRaw {
    GLfloat vertex_points[N];
};

using SquareMesh = MeshRaw<18>;

class MeshGenerator {
   public:
    MeshGenerator() = delete;
    ~MeshGenerator() = delete;
    static SquareMesh generate_square();
};

}  // namespace Geometry
}  // namespace SargassoEngine
