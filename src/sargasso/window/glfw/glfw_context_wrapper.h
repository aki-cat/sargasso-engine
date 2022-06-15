#ifndef SARGASSO_WINDOW_GLFW_GLFW_CONTEXT_WRAPPER_H_
#define SARGASSO_WINDOW_GLFW_GLFW_CONTEXT_WRAPPER_H_

#define GLFW_INCLUDE_NONE

#include "sargasso/config/window_config.h"
#include "sargasso/graphics/graphics.h"
#include "sargasso/window/window_manager.h"

#include <GLFW/glfw3.h>
#include <sml/color.h>

namespace sargasso {
namespace window {
namespace glfw {

class GLFWContextWrapper : virtual public IWindowManager {
   public:
    GLFWContextWrapper(const GLFWContextWrapper&) = delete;
    GLFWContextWrapper(const GLFWContextWrapper&&) = delete;
    GLFWContextWrapper(const config::WindowConfig& config, IGraphicsManager& graphics);
    ~GLFWContextWrapper() override;

    void run() override;
    void keyActionHandler(int key, int action) const;

   private:
    GLFWwindow* _window;
};

}  // namespace glfw
}  // namespace window
}  // namespace sargasso

#endif
