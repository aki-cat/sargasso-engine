#ifndef SARGASSO_GEOMETRY_MESH_H_
#define SARGASSO_GEOMETRY_MESH_H_

#include "sargasso/geometry/vertex.h"

#include <cstdlib>
#include <cstdint>
#include <vector>

namespace sargasso {
namespace geometry {

struct IndexTriPlane {
    uint indices[3];
};

class Mesh {
   public:
    explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<IndexTriPlane>& triPlanes)
        : _vertices(vertices), _triPlanes(triPlanes) {}

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    size_t getVertexCount() const {
        return _vertices.size();
    }

    size_t getTriPlaneCount() const {
        return _triPlanes.size();
    }

    const float* getVertexData() const {
        return reinterpret_cast<const float*>(_vertices.data());
    }

    const uint* getTriPlaneData() const {
        return reinterpret_cast<const uint*>(_triPlanes.data());
    }

    size_t getVertexDataSize() const {
        return getVertexCount() * sizeof(Vertex);
    }

    size_t getTriPlaneDataSize() const {
        return getTriPlaneCount() * sizeof(IndexTriPlane);
    }

   private:
    const std::vector<Vertex> _vertices;
    const std::vector<IndexTriPlane> _triPlanes;
};

}  // namespace geometry
}  // namespace sargasso

#endif  // SARGASSO_GEOMETRY_MESH_H_
