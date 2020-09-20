#ifndef SARGASSO_ENGINE_MESH_H
#define SARGASSO_ENGINE_MESH_H

#include "common/containers.h"
#include "geometry/constants.h"
#include "geometry/mesh_raw.h"

using namespace SargassoEngine::Common;

namespace SargassoEngine {
namespace Geometry {

class Mesh {
   public:
    // Constructors
    explicit Mesh(const Vec3* vertices, const uint32_t vertex_count);
    // Methods
    const MeshRaw raw() const;
    Vec3 get_vertex(const uint32_t vertex_index) const;
    // Operations
    Mesh translate(const Vec3& translation) const;
    Mesh rotate(const Vec3& axis, float angle) const;
    Mesh scale(float scale) const;

   private:
    DynamicArray<Vec3> _vertices;
};

}  // namespace Geometry
}  // namespace SargassoEngine

#endif
