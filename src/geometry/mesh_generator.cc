
#include "geometry/mesh_generator.h"

#include <GL/glew.h>
#include <glm/vec3.hpp>

using SargassoEngine::Geometry::MeshGenerator;
using SargassoEngine::Geometry::POINTS_PER_VERTEX;
using SargassoEngine::Geometry::SquareMesh;

SquareMesh MeshGenerator::generate_square() {
    SquareMesh mesh{};

    static const int VERTICES_IN_SQUARE = 6;

    glm::vec3 vertices[] = {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                            glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)};

    for (int i = 0; i < POINTS_PER_VERTEX * VERTICES_IN_SQUARE; i++) {
        int j = i / POINTS_PER_VERTEX;
        int k = i % POINTS_PER_VERTEX;
        mesh.vertex_points[i] = vertices[j][k];
    }

    return mesh;
}
