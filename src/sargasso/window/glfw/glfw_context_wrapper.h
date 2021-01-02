#ifndef SARGASSO_WINDOW_GLFW_GLFW_WINDOW_H_
#define SARGASSO_WINDOW_GLFW_GLFW_WINDOW_H_

#define GLFW_INCLUDE_NONE

#include "sargasso/window/icontext_wrapper.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace sargasso {
namespace window {
namespace glfw {

class GLFWContextWrapper : public IContextWrapper {
   public:
    GLFWContextWrapper(WindowConfig config) override;
    ~GLFWContextWrapper();

    bool should_close() const override;

   private:
    GLFWWindow* _window;
    void key_callback(int key, int action) const;
};

}  // namespace glfw
}  // namespace window
}  // namespace sargasso

#endif
