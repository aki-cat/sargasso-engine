#ifndef SARGASSO_WINDOW_ICONTEXT_WRAPPER_H_
#define SARGASSO_WINDOW_ICONTEXT_WRAPPER_H_

#include "sargasso/graphics/igraphics.h"

#include <cstdint>

namespace sargasso {

using graphics::IGraphics;

namespace window {

struct WindowConfig {
    char title[128] = "Sample\0";
    uint32_t width = 960;
    uint32_t height = 540;
    uint8_t msaa = 0;
};

class IContextWrapper {
   public:
    IContextWrapper(const IContextWrapper&) = delete;
    IContextWrapper(const IContextWrapper&&) = delete;
    IContextWrapper(WindowConfig config, IGraphics& graphics)
        : _config(config), _graphics(graphics) {}
    virtual ~IContextWrapper() {}
    virtual void run() = 0;

   protected:
    WindowConfig _config;
    IGraphics& _graphics;
};

}  // namespace window
}  // namespace sargasso

#endif
