
#include "geometry/mesh.h"

#include "common/containers.h"
#include "common/format.h"
#include "common/log.h"
#include "common/math.h"
#include "common/pool.h"

#include <stdexcept>

using namespace SargassoEngine::Geometry;
using namespace SargassoEngine::Common;
using namespace SargassoEngine::Common::Math;

Mesh::Mesh(const Vector3* vertices, const uint32_t vertex_count) {
    _vertices = DynamicArray<Vector3>();

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

Vector3 Mesh::get_vertex(const uint32_t vertex_index) const {
    if (vertex_index >= _vertices.size()) {
        throw std::out_of_range(format("Vertex index out of range. Was {0}, expected n <= {1}",
                                       vertex_index, _vertices.size()));
    }
    return _vertices.at(vertex_index);
}

Mesh Mesh::translate(const Vector3& translation) const {
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
