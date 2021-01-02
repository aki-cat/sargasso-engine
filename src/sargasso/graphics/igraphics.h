#ifndef SARGASSO_GRAPHICS_IGRAPHICS_H_
#define SARGASSO_GRAPHICS_IGRAPHICS_H_

#include <sml/color.h>

namespace sargasso {
namespace graphics {

using sml::Color;

class IGraphics {
   public:
    IGraphics() {}
    IGraphics(const IGraphics&) = delete;
    IGraphics(const IGraphics&&) = delete;
    virtual ~IGraphics() {}
    virtual bool initialize(void* proc_address) = 0;
    virtual void set_viewport(int x, int y, uint width, uint height) = 0;
    virtual void set_clear_color(Color color) = 0;
    virtual void clear() = 0;
    virtual std::string get_version() const = 0;
};

}  // namespace graphics
}  // namespace sargasso

#endif
