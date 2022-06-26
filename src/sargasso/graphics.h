#ifndef SARGASSO_GRAPHICS_H_
#define SARGASSO_GRAPHICS_H_

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

class Graphics {
   public:
    explicit Graphics();

    Graphics(Graphics&&) = delete;
    Graphics(const Graphics&&) = delete;
    Graphics&& operator=(Graphics&&) = delete;
    Graphics&& operator=(const Graphics&&) = delete;

    // shader methods
    void initShader();

    // general drawing methods
    void loadMesh(const geometry::Mesh& mesh);
    void drawMesh(const geometry::Mesh& mesh, const sml::Mat4& transform);

    // specific drawing methods
    common::Reference<geometry::Rect> newRect(float w, float h);
    void drawRect(const common::Reference<geometry::Rect>& rect);

    // mutable viewport methods
    void setDefaultViewport();
    void newViewport(uint width, uint height, uint unit);
    void setWidth(const uint width);
    void setHeight(const uint height);

    // immutable viewport methods
    uint getWidth() const;
    uint getHeight() const;
    float getAspect() const;
    float getUnitSize() const;
    const sml::Mat4& getProjection() const;

   private:
    common::Reference<ShaderProgram> _shaderProgram;
    common::Reference<Viewport> _viewport;
    std::map<const geometry::Mesh*, uint> _vaoIds;
};

}  // namespace sargasso

#endif  // SARGASSO_GRAPHICS_H_
