#ifndef SARGASSO_ENGINE_MESH_RAW_H
#define SARGASSO_ENGINE_MESH_RAW_H

#include <cstdint>
#include <sml/vector3.h>

using namespace sml;

namespace SargassoEngine {
namespace Geometry {

struct MeshRaw {
    MeshRaw(const Vec3* vertices, const uint32_t vertex_count);
    ~MeshRaw();

    float* points;
    const uint32_t point_count;

    void print() const;
};

}  // namespace Geometry
}  // namespace SargassoEngine

#endif
