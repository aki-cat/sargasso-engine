
#include "geometry/mesh_raw.h"

#include "common/log.h"
#include "geometry/constants.h"

#include <sstream>

using namespace SargassoEngine::Common;
using namespace SargassoEngine::Geometry;

MeshRaw::MeshRaw(const Vector3* vertices, const uint32_t vertex_count)
    : points(new float[(vertex_count * POINTS_PER_VERTEX)]),
      point_count(vertex_count * POINTS_PER_VERTEX) {
    uint32_t point_index = 0;

    logf("Instantiating Mesh %.\n- Points: %\n- Vertices: %", this, point_count, vertex_count);

    for (uint32_t vertex_index = 0; vertex_index < vertex_count; vertex_index++) {
        for (uint32_t coord_index = 0; coord_index < POINTS_PER_VERTEX; coord_index++) {
            points[point_index++] = vertices[vertex_index][coord_index];
        }
    }
}

MeshRaw::~MeshRaw() { delete[] points; }

void MeshRaw::print() const {
    const uint32_t vertex_count = point_count / POINTS_PER_VERTEX;

    logf("Printing Mesh %.\n- Points: %\n- Vertices: %", this, point_count, vertex_count);

    std::ostringstream sstream;
    for (uint32_t i = 0; i < vertex_count; i++) {
        sstream << "( ";
        for (uint32_t j = 0; j < POINTS_PER_VERTEX; j++) {
            sstream << points[i * POINTS_PER_VERTEX + j] << " ";
        }
        sstream << ")" << std::endl;
    }

    log(sstream.str());
}
