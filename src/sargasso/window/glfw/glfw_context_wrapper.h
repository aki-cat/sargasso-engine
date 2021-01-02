#ifndef SARGASSO_WINDOW_GLFW_GLFW_WINDOW_H_
#define SARGASSO_WINDOW_GLFW_GLFW_WINDOW_H_

#define GLFW_INCLUDE_NONE

#include "sargasso/window/icontext_wrapper.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace sargasso {
namespace window {
namespace glfw {

class GLFWContextWrapper : virtual public IContextWrapper {
   public:
    GLFWContextWrapper(const GLFWContextWrapper&) = delete;
    GLFWContextWrapper(const GLFWContextWrapper&&) = delete;
    explicit GLFWContextWrapper(WindowConfig config);
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
