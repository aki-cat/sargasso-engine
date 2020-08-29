
#include "geometry/mesh.h"

#include "common/containers.h"
#include "common/math.h"
#include "common/pool.h"

#include <iostream>

using namespace SargassoEngine::Geometry;
using namespace SargassoEngine::Common::Math;

Mesh::Mesh(const Vector3* vertices, uint32_t vertex_count) {
    _vertices = DynamicArray<Vector3>();

    std::cout << "size of vertex array: " << vertex_count << std::endl;
    for (int i = 0; i < vertex_count; i++) {
        _vertices.push_back(vertices[i]);
    }
}

const MeshRaw Mesh::raw() const {
    DynamicArray<Vector3> raw_vertices{};
    uint32_t count = 0;

    for (const Vector3& vertex : _vertices) {
        raw_vertices.push_back(vertex);
        count++;
    }

    return MeshRaw(raw_vertices.data(), count);
}

Mesh Mesh::translate(const Vector3& translation) const {
    // TODO: translate
    DynamicArray<Vector3> vertices{};

    for (const Vector3& vertex : _vertices) {
        vertices.push_back(vertex + translation);
    }

    return Mesh(vertices.data(), static_cast<uint32_t>(_vertices.size()));
}

Mesh Mesh::rotate(const Vector3& axis, float angle) const {
    // TODO: rotate
    return Mesh(&_vertices[0], static_cast<uint32_t>(_vertices.size()));
}

Mesh Mesh::scale(float scale) const {
    // TODO: scale
    return Mesh(&_vertices[0], static_cast<uint32_t>(_vertices.size()));
}
