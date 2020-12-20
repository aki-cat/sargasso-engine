
#include "sargasso/geometry/mesh_raw.h"

#include "sargasso/common/log.h"
#include "sargasso/geometry/constants.h"

#include <sstream>

using namespace SargassoEngine::Common;
using namespace SargassoEngine::Geometry;

MeshRaw::MeshRaw(const Vec3* vertices, const uint32_t vertex_count)
    : points(new float[(vertex_count * POINTS_PER_VERTEX)]),
      point_count(vertex_count * POINTS_PER_VERTEX) {
    logf("Instantiating Mesh %.\n- Points: %\n- Vertices: %", this, point_count, vertex_count);

    for (uint32_t vertex_index = 0; vertex_index < vertex_count; vertex_index++) {
        const Vec3& vertex = vertices[vertex_index];
        std::memcpy(&points[vertex_index * 3], &vertex, sizeof(float) * 3);
    }
}

MeshRaw::~MeshRaw() { delete[] points; }

void MeshRaw::print() const {
    const uint32_t vertex_count = point_count / POINTS_PER_VERTEX;

    logf("Printing Mesh %.\n- Points: %\n- Vertices: %", this, point_count, vertex_count);

    std::ostringstream sstream;
    for (uint32_t i = 0; i < vertex_count; i++) {
        sstream << "( " << points[i * POINTS_PER_VERTEX + 0] << ", ";
        sstream << points[i * POINTS_PER_VERTEX + 1] << ", ";
        sstream << points[i * POINTS_PER_VERTEX + 2] << " )" << std::endl;
    }

    log(sstream.str());
}
