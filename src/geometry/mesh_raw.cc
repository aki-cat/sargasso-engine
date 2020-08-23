
#include "geometry/mesh_raw.h"

#include "geometry/vertex.h"

using namespace SargassoEngine::Geometry;

MeshRaw::MeshRaw(const Vertex* vertices, const int vertex_count)
    : points(new float[(size_t)(vertex_count * POINTS_PER_VERTEX)]),
      point_count(vertex_count * POINTS_PER_VERTEX) {
    int point_index = 0;
    for (int vertex_index = 0; vertex_index < vertex_count; vertex_index++) {
        for (int coord_index = 0; coord_index < POINTS_PER_VERTEX; coord_index++) {
            points[point_index++] = vertices[vertex_index].position[coord_index];
        }
    }
}

MeshRaw::~MeshRaw() { delete[] points; }
