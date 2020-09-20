
#include "geometry/mesh_generator.h"

#include "common/math/matrix4.h"
#include "common/math/vector3.h"
#include "geometry/mesh_raw.h"

using namespace SargassoEngine::Geometry;
using namespace SargassoEngine::Common::Math;

MeshRaw MeshGenerator::generate_square() {
    const Vec3 square_vertices[6] = {Vec3(-0.5f, -0.5f, +0.0f), Vec3(+0.5f, -0.5f, +0.0f),
                                     Vec3(+0.5f, +0.5f, +0.0f), Vec3(+0.5f, +0.5f, +0.0f),
                                     Vec3(-0.5f, +0.5f, +0.0f), Vec3(-0.5f, -0.5f, +0.0f)};

    return MeshRaw(square_vertices, 6);
}

Mat4 MeshGenerator::generate_sample_camera(const float width, const float height) {
    Mat4 projection =
        Mat4::perspective_projection(static_cast<float>(M_PI_4), width / height, 0.01f, 1000.0f);
    Mat4 view = Mat4::look_at(Vec3(4.0f, 3.0f, 3.0f),   // Position
                              Vec3(0.0f, 0.0f, 0.0f));  // Up vector

    return projection * view;
}
