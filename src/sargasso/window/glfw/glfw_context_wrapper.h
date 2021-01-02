#ifndef SARGASSO_WINDOW_GLFW_GLFW_CONTEXT_WRAPPER_H_
#define SARGASSO_WINDOW_GLFW_GLFW_CONTEXT_WRAPPER_H_

#define GLFW_INCLUDE_NONE

#include "sargasso/graphics/igraphics.h"
#include "sargasso/window/icontext_wrapper.h"
#include "sargasso/window/window_config.h"

#include <GLFW/glfw3.h>
#include <sml/color.h>

namespace sargasso {
namespace window {
namespace glfw {

class GLFWContextWrapper : virtual public IContextWrapper {
   public:
    GLFWContextWrapper(const GLFWContextWrapper&) = delete;
    GLFWContextWrapper(const GLFWContextWrapper&&) = delete;
    GLFWContextWrapper(WindowConfig config, IGraphics& graphics);
    ~GLFWContextWrapper() override;

    void run() override;
    void key_action_handler(int key, int action) const;

   private:
    GLFWwindow* _window;
};

}  // namespace glfw
}  // namespace window
}  // namespace sargasso

#endif
