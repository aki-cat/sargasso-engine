#ifndef SARGASSO_ENGINE_MESH_H
#define SARGASSO_ENGINE_MESH_H

#include "common/containers.h"
#include "geometry/mesh_raw.h"

namespace SargassoEngine {
namespace Geometry {

using namespace Common;

static const uint32_t POINTS_PER_VERTEX = 3;

class Mesh {
   public:
    // Constructors
    explicit Mesh(const Vector3* vertices, uint32_t vertex_count);
    // Methods
    const MeshRaw raw() const;
    // Operations
    Mesh translate(const Vector3& translation) const;
    Mesh rotate(const Vector3& axis, float angle) const;
    Mesh scale(float scale) const;

   private:
    Mesh(const Mesh&);
    Mesh(const Mesh&&);
    DynamicArray<Vector3> _vertices;
};

}  // namespace Geometry
}  // namespace SargassoEngine

#endif
