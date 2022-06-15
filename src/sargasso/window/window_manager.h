#ifndef SARGASSO_WINDOW_MANAGER_H_
#define SARGASSO_WINDOW_MANAGER_H_

#include "sargasso/graphics/graphics.h"
#include "sargasso/window/window_config.h"

#include <GLFW/glfw3.h>
#include <cstdint>

namespace sargasso {
namespace window {

using graphics::IGraphicsManager;

class IWindowManager {
   public:
    IWindowManager(const IWindowManager&) = delete;
    IWindowManager(const IWindowManager&&) = delete;
    IWindowManager(const WindowConfig& config, IGraphicsManager& graphics)
        : _config(config), _graphics(graphics) {}
    virtual ~IWindowManager() {}

    virtual void init() = 0;
    virtual void terminate() = 0;
    virtual void run() = 0;

   protected:
    const WindowConfig _config;
    IGraphicsManager& _graphics;
};

class WindowManager : virtual public IWindowManager {
   public:
    WindowManager(const WindowManager&) = delete;
    WindowManager(const WindowManager&&) = delete;
    WindowManager(const WindowConfig& config, IGraphicsManager& graphics)
        : IWindowManager(config, graphics) {}

    void init() override;
    void terminate() override;
    void run() override;

    void keyActionHandler(int key, int action) const;

   private:
    GLFWwindow* _window;
};

}  // namespace window
}  // namespace sargasso

#endif  // SARGASSO_WINDOW_MANAGER_H_
