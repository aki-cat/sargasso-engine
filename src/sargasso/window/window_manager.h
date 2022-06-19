#ifndef SARGASSO_WINDOW_MANAGER_H_
#define SARGASSO_WINDOW_MANAGER_H_

#include "sargasso/graphics/graphics.h"
#include "sargasso/window/window_config.h"

#include <GLFW/glfw3.h>

namespace sargasso {
namespace window {

template <typename T>
class WindowManager {
   public:
    WindowManager(const WindowConfig& config, graphics::GraphicsManager<T>& graphics)
        : _config{config}, _graphics{graphics} {}

    // Deleted constructors
    WindowManager(WindowManager&) = delete;
    WindowManager(WindowManager&&) = delete;
    WindowManager(const WindowManager&) = delete;
    WindowManager(const WindowManager&&) = delete;

    void init();
    void terminate();
    void run();
    void keyActionHandler(int key, int action) const;

   private:
    const WindowConfig& _config;
    graphics::GraphicsManager<T>& _graphics;
    GLFWwindow* _window;
};

}  // namespace window
}  // namespace sargasso

#endif  // SARGASSO_WINDOW_MANAGER_H_
