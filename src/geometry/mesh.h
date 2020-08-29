#ifndef SARGASSO_ENGINE_MESH_H
#define SARGASSO_ENGINE_MESH_H

#include "common/containers.h"
#include "geometry/mesh_raw.h"
#include "geometry/vertex.h"

namespace SargassoEngine {
namespace Geometry {

using namespace Common;

class Mesh {
   public:
    explicit Mesh(const Vertex* vertices, int vertex_count);
    Mesh(const Mesh&) = delete;
    Mesh(const Mesh&&) = delete;
    const MeshRaw raw() const;

   private:
    DynamicArray<Vertex> _vertices;
};

}  // namespace Geometry
}  // namespace SargassoEngine

#endif
