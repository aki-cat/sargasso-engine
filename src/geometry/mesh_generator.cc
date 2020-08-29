
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

const Matrix4 MeshGenerator::generate_sample_camera() {
    const float width = 960.0f, height = 540.0f;
    Matrix4 projection = glm::perspective(glm::radians(45.0f), width / height, 0.01f, 1000.0f);
    Matrix4 view = glm::lookAt(glm::vec3(4, 3, 3),   // Position
                               glm::vec3(0, 0, 0),   // Target
                               glm::vec3(0, 1, 0));  // Up vector

    return projection * view;
}
