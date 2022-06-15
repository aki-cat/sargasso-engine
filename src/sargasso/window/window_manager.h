#ifndef SARGASSO_WINDOW_CONTEXT_WRAPPER_H_
#define SARGASSO_WINDOW_CONTEXT_WRAPPER_H_

#include "sargasso/config/window_config.h"
#include "sargasso/graphics/graphics.h"

#include <cstdint>

namespace sargasso {

using graphics::IGraphicsManager;

namespace window {

class IWindowManager {
   public:
    IWindowManager(const IWindowManager&) = delete;
    IWindowManager(const IWindowManager&&) = delete;
    IWindowManager(const config::WindowConfig& config, IGraphicsManager& graphics)
        : _config(config), _graphics(graphics) {}
    virtual ~IWindowManager() {}
    virtual void run() = 0;

   protected:
    const config::WindowConfig _config;
    IGraphicsManager& _graphics;
};

}  // namespace window
}  // namespace sargasso

#endif  // SARGASSO_WINDOW_CONTEXT_WRAPPER_H_
