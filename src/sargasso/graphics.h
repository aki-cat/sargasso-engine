#ifndef SARGASSO_GRAPHICS_H_
#define SARGASSO_GRAPHICS_H_

#include "sargasso/common/reference.h"
#include "sargasso/geometry/mesh.h"
#include "sargasso/geometry/rect.h"
#include "sargasso/shader.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <cstdint>
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

    uint getWidth() const;
    uint getHeight() const;
    void setWidth(const uint width);
    void setHeight(const uint height);
    float getAspect() const;
    float getUnitSize() const;
    sml::Mat4 getProjection() const;

   private:
    common::Reference<ShaderProgram> _shaderProgram;
    std::map<const geometry::Mesh*, uint> _vaoIds;
    uint _width, _height;
    const float _heightInUnits = 5.f;
};

}  // namespace sargasso

#endif  // SARGASSO_GRAPHICS_H_
