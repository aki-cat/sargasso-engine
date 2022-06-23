#ifndef SARGASSO_GEOMETRY_MESH_H_
#define SARGASSO_GEOMETRY_MESH_H_

#include "sargasso/geometry/vertex.h"

#include <cstdlib>
#include <vector>

namespace sargasso {
namespace geometry {

struct IndexTriPlane {
    unsigned int indices[3];
};

class Mesh {
   public:
    explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<IndexTriPlane>& triPlanes)
        : _vertices(vertices), _triPlanes(triPlanes) {}

    Mesh(Mesh&) = delete;
    Mesh(const Mesh&) = delete;
    Mesh& operator=(Mesh&) = delete;
    const Mesh& operator=(const Mesh&) = delete;

    const size_t getVertexCount() const {
        return _vertices.size();
    }

    const size_t getTriPlaneCount() const {
        return _triPlanes.size();
    }

    const float* getVertexData() const {
        return reinterpret_cast<const float*>(_vertices.data());
    }

    const unsigned int* getTriPlaneData() const {
        return reinterpret_cast<const unsigned int*>(_triPlanes.data());
    }

    const size_t getVertexDataSize() const {
        return getVertexCount() * sizeof(Vertex);
    }

    const size_t getTriPlaneDataSize() const {
        return getTriPlaneCount() * sizeof(IndexTriPlane);
    }

   private:
    const std::vector<Vertex> _vertices;
    const std::vector<IndexTriPlane> _triPlanes;
};

}  // namespace geometry
}  // namespace sargasso

#endif  // SARGASSO_GEOMETRY_MESH_H_
