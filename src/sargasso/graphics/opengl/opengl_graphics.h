#ifndef SARGASSO_GRAPHICS_OPENGL_OPENGL_GRAPHICS_H_
#define SARGASSO_GRAPHICS_OPENGL_OPENGL_GRAPHICS_H_

#include "sargasso/graphics/igraphics.h"

#include <cstdint>
#include <sml/color.h>

namespace sargasso {
namespace graphics {
namespace opengl {

using sml::Color;

class OpenGLGraphics : virtual public IGraphics {
   public:
    OpenGLGraphics() : IGraphics() {}
    OpenGLGraphics(const OpenGLGraphics&) = delete;
    OpenGLGraphics(const OpenGLGraphics&&) = delete;

    ~OpenGLGraphics() override {}

    bool initialize(void* proc_address) override;
    void set_viewport(int x, int y, uint width, uint height) override;
    void set_clear_color(Color color) override;
    void clear() override;
    std::string get_version() const override;
};

}  // namespace opengl
}  // namespace graphics
}  // namespace sargasso

#endif
