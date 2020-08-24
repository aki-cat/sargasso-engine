
#include "geometry/mesh_generator.h"

#include "geometry/mesh_raw.h"
#include "geometry/vertex.h"

using namespace SargassoEngine::Geometry;

const MeshRaw MeshGenerator::generate_square() {
    const Vertex square_vertices[6] = {Vertex(0.0f, 0.0f, 0.0f), Vertex(1.0f, 0.0f, 0.0f),
                                       Vertex(1.0f, 1.0f, 0.0f), Vertex(1.0f, 1.0f, 0.0f),
                                       Vertex(0.0f, 1.0f, 0.0f), Vertex(0.0f, 0.0f, 0.0f)};

    return MeshRaw(square_vertices, 6);
}
