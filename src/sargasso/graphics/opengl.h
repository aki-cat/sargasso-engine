#ifndef SARGASSO_GRAPHICS_OPENGL_H_
#define SARGASSO_GRAPHICS_OPENGL_H_

#include "sargasso/graphics/graphics.h"

#include <cstdint>
#include <sml/color.h>

namespace sargasso {
namespace graphics {

using sml::Color;

class OpenGLGraphics : virtual public IGraphicsManager {
   public:
    OpenGLGraphics() : IGraphicsManager() {}
    OpenGLGraphics(const OpenGLGraphics&) = delete;
    OpenGLGraphics(const OpenGLGraphics&&) = delete;

    // Initialization
    bool initialize() override;

    // Imperative rendering
    void present(void* params) override;
    void setViewport(int x, int y, uint32_t width, uint32_t height) override;
    void setClearColor(Color color) override;
    void clear() override;

    // Meta information
    const EGraphicsBackend getType() const override;
    const char* getName() const override;
    const char* getVersionString() const override;
    const int getVersionMajor() const override;
    const int getVersionMinor() const override;
    const EGraphicsBackend backendType = EGraphicsBackend::kOpenGL;
};

}  // namespace graphics
}  // namespace sargasso

#endif  // SARGASSO_GRAPHICS_OPENGL_H_
