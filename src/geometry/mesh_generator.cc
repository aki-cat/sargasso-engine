
#include "geometry/mesh_generator.h"

#include <array>
#include <glm/vec4.hpp>

using SargassoEngine::Geometry::MeshGenerator;

std::array<glm::vec4, 6> MeshGenerator::generate_square() {
    std::array<glm::vec4, 6> vertices{};

    vertices[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vertices[1] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    vertices[2] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    vertices[3] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    vertices[4] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    vertices[5] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    return vertices;
}
