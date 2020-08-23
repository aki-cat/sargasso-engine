#ifndef SARGASSO_ENGINE_VERTEX_H
#define SARGASSO_ENGINE_VERTEX_H

#include <glm/vec3.hpp>

namespace SargassoEngine {
namespace Geometry {

struct Vertex {
    glm::vec3 position;

    // For now we're commenting these to avoid complexity:
    // glm::vec3 normal;
    // glm::vec2 uv;
};

}  // namespace Geometry
}  // namespace SargassoEngine

#endif
