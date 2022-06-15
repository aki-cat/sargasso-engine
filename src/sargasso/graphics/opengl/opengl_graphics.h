#ifndef SARGASSO_GRAPHICS_OPENGL_OPENGL_GRAPHICS_H_
#define SARGASSO_GRAPHICS_OPENGL_OPENGL_GRAPHICS_H_

#include "sargasso/graphics/graphics.h"

#include <cstdint>
#include <sml/color.h>

namespace sargasso {
namespace graphics {
namespace opengl {

using sml::Color;

class OpenGLGraphics : virtual public IGraphicsManager {
   public:
    OpenGLGraphics() : IGraphicsManager() {}
    OpenGLGraphics(const OpenGLGraphics&) = delete;
    OpenGLGraphics(const OpenGLGraphics&&) = delete;

    ~OpenGLGraphics() override {}

    bool initialize(void* proc_address) override;
    void setViewport(int x, int y, uint32_t width, uint32_t height) override;
    void setClearColor(Color color) override;
    void clear() override;

    const char* getName() const override;
    const char* getVersionString() const override;
    const int getVersionMajor() const override;
    const int getVersionMinor() const override;

   private:
    static const char* NAME;
};

}  // namespace opengl
}  // namespace graphics
}  // namespace sargasso

#endif
