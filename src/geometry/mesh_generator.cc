
#include "geometry/mesh_generator.h"

#include "common/math.h"
#include "geometry/mesh_raw.h"

using namespace SargassoEngine::Geometry;
using namespace SargassoEngine::Common::Math;

const MeshRaw MeshGenerator::generate_square() {
    const Vector3 square_vertices[6] = {Vector3(-0.5f, -0.5f, +0.0f), Vector3(+0.5f, -0.5f, +0.0f),
                                        Vector3(+0.5f, +0.5f, +0.0f), Vector3(+0.5f, +0.5f, +0.0f),
                                        Vector3(-0.5f, +0.5f, +0.0f), Vector3(-0.5f, -0.5f, +0.0f)};

    return MeshRaw(square_vertices, 6);
}

const Matrix4 MeshGenerator::generate_sample_camera() {
    const float width = 960.0f, height = 540.0f;
    Matrix4 projection = glm::perspective(glm::radians(45.0f), width / height, 0.01f, 1000.0f);
    Matrix4 view = glm::lookAt(Vector3(4.0f, 3.0f, 3.0f),   // Position
                               Vector3(0.0f, 0.0f, 0.0f),   // Target
                               Vector3(0.0f, 1.0f, 0.0f));  // Up vector

    return projection * view;
}
