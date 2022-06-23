#ifndef SARGASSO_GEOMETRY_MESH_H_
#define SARGASSO_GEOMETRY_MESH_H_

#include "sargasso/geometry/vertex.h"

#include <cstdlib>
#include <vector>

namespace sargasso {
namespace geometry {

using Triangle = unsigned int[3];

class Mesh {
   public:
    explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<Triangle>& triangles)
        : _vertices(vertices), _triangles(triangles) {}

    ~Mesh() {}

    const size_t getVertexCount() const {
        return _vertices.size();
    }

    const size_t getTriangleCount() const {
        return _triangles.size();
    }

    const float* getVertexData() const {
        return reinterpret_cast<const float*>(_vertices.data());
    }

    const unsigned int* getTriangleData() const {
        return reinterpret_cast<const unsigned int*>(_triangles.data());
    }

    const size_t getVertexDataSize() const {
        return getVertexCount() * sizeof(Vertex);
    }

    const size_t getTriangleDataSize() const {
        return getTriangleCount() * sizeof(Triangle);
    }

   private:
    const std::vector<Vertex> _vertices;
    const std::vector<Triangle> _triangles;
};

}  // namespace geometry
}  // namespace sargasso

#endif  // SARGASSO_GEOMETRY_MESH_H_
