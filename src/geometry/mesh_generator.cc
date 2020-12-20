
#include "geometry/mesh_generator.h"

#include "geometry/mesh_raw.h"

#include <sml/matrix4.h>
#include <sml/vector3.h>

using namespace SargassoEngine::Geometry;
using namespace SML;

MeshRaw MeshGenerator::generate_square() {
    const Vec3 square_vertices[6] = {Vec3(-0.5f, -0.5f, +0.0f), Vec3(+0.5f, -0.5f, +0.0f),
                                     Vec3(+0.5f, +0.5f, +0.0f), Vec3(+0.5f, +0.5f, +0.0f),
                                     Vec3(-0.5f, +0.5f, +0.0f), Vec3(-0.5f, -0.5f, +0.0f)};

    return MeshRaw(square_vertices, 6);
}

Mat4 MeshGenerator::generate_sample_camera(const float width, const float height) {
    Mat4 projection =
        Mat4::conical_projection(static_cast<float>(M_PI_4), width / height, 0.01f, 1000.0f);
    Mat4 view = Mat4::look_at(Vec3(4.0f, 3.0f, 3.0f),  // Position
                              Vec3::zero());

    return projection * view;
}
