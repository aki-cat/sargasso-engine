#ifndef SARGASSO_ENGINE_MESH_RAW_H
#define SARGASSO_ENGINE_MESH_RAW_H

#include "geometry/vertex.h"

namespace SargassoEngine {
namespace Geometry {

struct MeshRaw {
    MeshRaw(const Vertex* vertices, const int vertex_count);
    ~MeshRaw();

    float* points;
    const int point_count;
};

}  // namespace Geometry
}  // namespace SargassoEngine

#endif
