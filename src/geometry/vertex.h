#ifndef SARGASSO_ENGINE_VERTEX_H
#define SARGASSO_ENGINE_VERTEX_H

#include "common/math.h"

namespace SargassoEngine {
namespace Geometry {

using namespace Common;

static const uint32_t POINTS_PER_VERTEX = 3;

struct Vertex {
    Vertex() : position() {}
    Vertex(float x, float y, float z) : position(x, y, z) {}
    Vector3 position;

    // For now we're commenting these to avoid complexity:
    // Vector3 normal;
    // Vector2 uv;
};

}  // namespace Geometry
}  // namespace SargassoEngine

#endif
