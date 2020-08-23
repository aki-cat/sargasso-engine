
#include "geometry/mesh.h"

#include "common/containers.h"

#include <iostream>

using namespace SargassoEngine::Geometry;

Pool<Vertex> Mesh::vertex_pool = Pool<Vertex>();

Mesh::Mesh(const Vertex* vertices, int vertex_count) {
    _vertices = DynamicArray<VertexID>();

    std::cout << "size of vertex array: " << vertex_count << std::endl;
    for (int i = 0; i < vertex_count; i++) {
        VertexID vertex_id = vertex_pool.create(vertices[i]);
        _vertices.push_back(vertex_id);
    }
}

const MeshRaw Mesh::raw() const {
    DynamicArray<Vertex> raw_vertices{};
    int count = 0;

    for (const VertexID vertex_id : _vertices) {
        raw_vertices.push_back(vertex_pool.get(vertex_id));
        count++;
    }

    return MeshRaw(raw_vertices.data(), count);
}
