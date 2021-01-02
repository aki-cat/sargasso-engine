#ifndef SARGASSO_WINDOW_ICONTEXT_WRAPPER_H_
#define SARGASSO_WINDOW_ICONTEXT_WRAPPER_H_

#include "sargasso/graphics/igraphics.h"
#include "sargasso/window/window_config.h"

#include <cstdint>

namespace sargasso {

using graphics::IGraphics;

namespace window {

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
