#include "sargasso/graphics/mesh_manager.h"

#include "sargasso/geometry/mesh.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace sargasso {
namespace graphcis {

GlMeshManager::GlMeshManager() {}
GlMeshManager::~GlMeshManager() {}

MeshId GlMeshManager::addMesh(const geometry::Mesh& meshData) {
    GlMeshBuffer meshBuffer;

    glGenVertexArrays(1, &meshBuffer.vaoId);
    glBindVertexArray(meshBuffer.vaoId);

    glGenBuffers(1, &meshBuffer.vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, meshBuffer.vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, meshData.getVertexDataSize(), meshData.getVertexData(),
                 GL_STATIC_DRAW);

    glGenBuffers(1, &meshBuffer.indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffer.indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData.getTriangleDataSize(),
                 meshData.getTriangleData(), GL_STATIC_DRAW);

    // unbind generated buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    meshBuffer.triCount = meshData.getTriangleCount();
    MeshId meshId = _meshCount;
    _meshes[_meshCount] = meshBuffer;
    _meshCount++;
    return meshId;
}

void GlMeshManager::draw() {
    for (size_t i = 0; i < _meshCount; i++) {
        const GlMeshBuffer& meshBuffer = _meshes[i];
        glBindVertexArray(meshBuffer.vaoId);
        glDrawElements(GL_TRIANGLES, meshBuffer.triCount, GL_UNSIGNED_INT, 0);
    }
}

}  // namespace graphcis

}  // namespace sargasso
