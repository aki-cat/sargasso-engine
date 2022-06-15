#ifndef SARGASSO_GRAPHICS_IGRAPHICS_H_
#define SARGASSO_GRAPHICS_IGRAPHICS_H_

#include <sml/color.h>

namespace sargasso {
namespace graphics {

using sml::Color;

class IGraphicsManager {
   public:
    IGraphicsManager() {}
    IGraphicsManager(const IGraphicsManager&) = delete;
    IGraphicsManager(const IGraphicsManager&&) = delete;
    virtual ~IGraphicsManager() {}
    virtual bool initialize(void* proc_address) = 0;
    virtual void setViewport(int x, int y, uint32_t width, uint32_t height) = 0;
    virtual void setClearColor(Color color) = 0;
    virtual void clear() = 0;
    virtual const char* getName() const = 0;
    virtual const char* getVersion() const = 0;
};

}  // namespace graphics
}  // namespace sargasso

#endif
