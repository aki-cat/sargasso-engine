
#include "geometry/mesh.h"

#include "common/containers.h"
#include "common/pool.h"

#include <iostream>

using namespace SargassoEngine::Geometry;

Mesh::Mesh(const Vertex* vertices, int vertex_count) {
    _vertices = DynamicArray<Vertex>();

    std::cout << "size of vertex array: " << vertex_count << std::endl;
    for (int i = 0; i < vertex_count; i++) {
        _vertices.push_back(vertices[i]);
    }
}

const MeshRaw Mesh::raw() const {
    DynamicArray<Vertex> raw_vertices{};
    int count = 0;

    for (const Vertex& vertex : _vertices) {
        raw_vertices.push_back(vertex);
        count++;
    }

    return MeshRaw(raw_vertices.data(), count);
}
