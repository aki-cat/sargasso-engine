#include "sargasso/graphics.h"

#include "sargasso/common/reference.h"
#include "sargasso/geometry/mesh.h"
#include "sargasso/geometry/rect.h"
#include "sargasso/shader.h"
#include "sargasso/viewport.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <map>
#include <sml/constants.h>
#include <sml/matrix4.h>

namespace sargasso {

Graphics::Graphics() {}

void Graphics::initShader() {
    _shaderProgram = new ShaderProgram();
}

void Graphics::loadMesh(const geometry::Mesh& mesh) {
    uint vertexBuffer, indexBuffer, vaoId;

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

void Graphics::drawMesh(const geometry::Mesh& mesh, const sml::Mat4& transform) {
    _viewport->clearDirty();
    _shaderProgram->use();
    _shaderProgram->setMat4Uniform("projMatrix", getProjection());
    _shaderProgram->setMat4Uniform("transform", transform);
    uint vaoId = _vaoIds.at(&mesh);
    glBindVertexArray(vaoId);
    glDrawElements(GL_TRIANGLES, mesh.getTriPlaneCount() * 3, GL_UNSIGNED_INT, NULL);
}

common::Reference<geometry::Rect> Graphics::newRect(float w, float h) {
    common::Reference<geometry::Rect> rect = new geometry::Rect(w, h);
    loadMesh(rect->getMesh());
    return rect;
}

void Graphics::Graphics::drawRect(const common::Reference<geometry::Rect>& rect) {
    const geometry::Mesh& rectMesh = rect->getMesh();
    drawMesh(rectMesh, rect->getTransform());
}

void Graphics::setDefaultViewport() {
    _viewport->clearDirty();
    glViewport(0, 0, getWidth(), getHeight());
}

void Graphics::newViewport(uint width, uint height, uint unit, float, float) {
    _viewport.clear();
    Viewport viewport = Viewport::ortho(width, height, unit);
    // Viewport viewport = Viewport::conical(width, height, sml::PI / 2, .001f, 1000.f);
    _viewport = new Viewport(viewport);
}

uint Graphics::getWidth() const {
    return _viewport->getWidth();
}

uint Graphics::getHeight() const {
    return _viewport->getHeight();
}

void Graphics::setWidth(const uint width) {
    _viewport->setWidth(width);
}

void Graphics::setHeight(const uint height) {
    _viewport->setHeight(height);
}

float Graphics::getAspect() const {
    return _viewport->getAspect();
}

float Graphics::getUnitSize() const {
    return _viewport->getUnitSize();
}

const sml::Mat4& Graphics::getProjection() const {
    return _viewport->getProjMatrix();
}

}  // namespace sargasso
