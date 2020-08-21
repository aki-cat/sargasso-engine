
#include "geometry/mesh_generator.h"

#include <GL/glew.h>
#include <glm/vec4.hpp>

using SargassoEngine::Geometry::MeshGenerator;
using SargassoEngine::Geometry::SquareMesh;

SquareMesh MeshGenerator::generate_square() {
    SquareMesh mesh{};

    static const int POINTS_PER_VERTEX = 4;
    static const int VERTICES_IN_SQUARE = 6;

    glm::vec4 vertices[] = {glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
                            glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
                            glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)};

    for (int i = 0; i < POINTS_PER_VERTEX * VERTICES_IN_SQUARE; i++) {
        int j = i / POINTS_PER_VERTEX;
        int k = i % POINTS_PER_VERTEX;
        mesh.vertex_points[i] = vertices[j][k];
    }

    return mesh;
}
