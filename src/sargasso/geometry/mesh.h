#ifndef SARGASSO_GEOMETRY_MESH_H_
#define SARGASSO_GEOMETRY_MESH_H_

#include "sargasso/geometry/vertex.h"

#include <cstdint>
#include <cstring>

namespace sargasso {
namespace geometry {

using Triangle = uint32_t[3];

class Mesh {
   public:
    Mesh() = default;

    // Deleted constructors
    Mesh(Mesh&) = delete;
    Mesh(Mesh&&) = delete;
    Mesh(const Mesh&) = delete;
    Mesh(const Mesh&&) = delete;

    Mesh(const Vertex* vertices, const size_t vertexCount, const Triangle* triangles,
         const size_t triCount) {
        setVertices(vertices, vertexCount);
        setTriangles(triangles, triCount);
    }

    ~Mesh() {
        unsetVertices();
        unsetTriangles();
    }

    void setVertices(const Vertex* vertices, const size_t vertexCount) {
        unsetVertices();
        _vertices = new Vertex[vertexCount];
        _vertexCount = vertexCount;
        std::memcpy(_vertices, vertices, vertexCount * sizeof(Vertex));
    }

    void setTriangles(const Triangle* triangles, const size_t triCount) {
        unsetTriangles();
        _triangles = new Triangle[triCount];
        _triCount = triCount;
        std::memcpy(_triangles, triangles, triCount * sizeof(Triangle));
    }

    void unsetVertices() {
        if (_vertices != nullptr) {
            delete[] _vertices;
            _vertices = nullptr;
            _vertexCount = 0;
        }
    }

    void unsetTriangles() {
        if (_triangles != nullptr) {
            delete[] _triangles;
            _triangles = nullptr;
            _triCount = 0;
        }
    }

    const size_t getVertexCount() const {
        return _vertexCount;
    }

    const size_t getTriangleCount() const {
        return _triCount;
    }

    const void* getVertexData() const {
        return reinterpret_cast<void*>(_vertices);
    }

    const void* getTriangleData() const {
        return reinterpret_cast<void*>(_triangles);
    }

    const size_t getVertexDataSize() const {
        return _vertexCount * sizeof(Vertex);
    }

    const size_t getTriangleDataSize() const {
        return _triCount * sizeof(Triangle);
    }

   private:
    size_t _vertexCount = 0, _triCount = 0;
    Vertex* _vertices = nullptr;
    Triangle* _triangles = nullptr;
};

}  // namespace geometry
}  // namespace sargasso

#endif  // SARGASSO_GEOMETRY_MESH_H_
