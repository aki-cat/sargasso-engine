
#include <array>
#include <glm/vec4.hpp>

namespace SargassoEngine {
namespace Geometry {

class MeshGenerator {
   public:
    MeshGenerator() = delete;
    ~MeshGenerator() = delete;
    static std::array<glm::vec4, 6> generate_square();
};

}  // namespace Geometry
}  // namespace SargassoEngine
