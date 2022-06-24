#ifndef SARGASSO_GRAPHICS_H_
#define SARGASSO_GRAPHICS_H_

#include "sargasso/common/reference.h"
#include "sargasso/geometry/mesh.h"
#include "sargasso/geometry/rect.h"
#include "sargasso/shader.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <map>

namespace sargasso {

namespace {
using RectRef = common::Reference<geometry::Rect>;
}

class Graphics {
   public:
    explicit Graphics();

    Graphics(Graphics&&) = delete;
    Graphics(const Graphics&&) = delete;
    Graphics&& operator=(Graphics&&) = delete;
    Graphics&& operator=(const Graphics&&) = delete;

    // methods

    void initShader();
    RectRef newRect(float w, float h);
    void loadMesh(const geometry::Mesh& mesh);
    void drawRect(const RectRef& rect) const;
    void drawMesh(const geometry::Mesh& mesh) const;

   private:
    common::Reference<ShaderProgram> _shaderProgram;
    std::map<const geometry::Mesh*, unsigned int> _vaoIds;
};

inline Graphics::Graphics() {}

inline void Graphics::initShader() {
    _shaderProgram = new ShaderProgram();
}

inline RectRef Graphics::newRect(float w, float h) {
    RectRef rect = new geometry::Rect(w, h);
    loadMesh(rect->getMesh());
    return rect;
}

inline void Graphics::loadMesh(const geometry::Mesh& mesh) {
    unsigned int vertexBuffer, indexBuffer, vaoId;

    glGenVertexArrays(1, &vaoId);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &indexBuffer);

    glBindVertexArray(vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glBufferData(GL_ARRAY_BUFFER, mesh.getVertexDataSize(), mesh.getVertexData(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getTriPlaneDataSize(), mesh.getTriPlaneData(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(geometry::Vertex), 0);
    glEnableVertexAttribArray(0);

    _vaoIds.emplace(&mesh, vaoId);
}

inline void Graphics::Graphics::drawRect(const RectRef& rect) const {
    const geometry::Mesh& rectMesh = rect->getMesh();
    drawMesh(rectMesh);
}

inline void Graphics::drawMesh(const geometry::Mesh& mesh) const {
    _shaderProgram->use();
    unsigned int vaoId = _vaoIds.at(&mesh);
    glBindVertexArray(vaoId);
    glDrawElements(GL_TRIANGLES, mesh.getTriPlaneCount() * 3, GL_UNSIGNED_INT, NULL);
}

}  // namespace sargasso

#endif  // SARGASSO_GRAPHICS_H_
