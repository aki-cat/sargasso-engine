#ifndef SARGASSO_GRAPHICS_H_
#define SARGASSO_GRAPHICS_H_

#include "sargasso/common/reference.h"
#include "sargasso/geometry/mesh.h"
#include "sargasso/geometry/rect.h"
#include "sargasso/shader.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <map>
#include <sml/constants.h>
#include <sml/matrix4.h>

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
    void drawMesh(const geometry::Mesh& mesh, const sml::Mat4& transform) const;

    unsigned int getWidth() const {
        return _width;
    }

    unsigned int getHeight() const {
        return _height;
    }

    void setWidth(const float width) {
        _width = width;
    }

    void setHeight(const float height) {
        _height = height;
    }

    float getAspect() const {
        return 1.f * _width / _height;
    }

    float getUnitSize() const {
        return _heightInUnits / (.5f * _height);
    }

    sml::Mat4 getProjection() const {
        const float aspect = getAspect();
        const float unit = getUnitSize();
        const float halfWidth = aspect * _height * unit;
        const float halfHeight = _height * unit;
        const sml::Mat4 projMatrix = sml::Mat4::orthogonal_projection(
            -halfWidth, halfHeight, halfWidth, -halfHeight, 0, 1000);
        return projMatrix;
    }

   private:
    common::Reference<ShaderProgram> _shaderProgram;
    std::map<const geometry::Mesh*, unsigned int> _vaoIds;
    unsigned int _width, _height;
    const float _heightInUnits = 5.f;
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
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(geometry::Vertex),
                          (void*) sizeof(sml::Vec3));
    glEnableVertexAttribArray(1);

    _vaoIds.emplace(&mesh, vaoId);
}

inline void Graphics::Graphics::drawRect(const RectRef& rect) const {
    const geometry::Mesh& rectMesh = rect->getMesh();
    drawMesh(rectMesh, rect->getTransform());
}

inline void Graphics::drawMesh(const geometry::Mesh& mesh, const sml::Mat4& transform) const {
    _shaderProgram->use();
    _shaderProgram->setMat4Uniform("projMatrix", getProjection());
    _shaderProgram->setMat4Uniform("transform", transform);
    unsigned int vaoId = _vaoIds.at(&mesh);
    glBindVertexArray(vaoId);
    glDrawElements(GL_TRIANGLES, mesh.getTriPlaneCount() * 3, GL_UNSIGNED_INT, NULL);
}

}  // namespace sargasso

#endif  // SARGASSO_GRAPHICS_H_
