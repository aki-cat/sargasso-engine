#ifndef SARGASSO_ENGINE_MODULES_EVENTS_H
#define SARGASSO_ENGINE_MODULES_EVENTS_H

#include <GLFW/glfw3.h>

namespace SargassoEngine {
namespace Modules {

class Events {
 public:
  Events();
  ~Events();
  void register_window(GLFWwindow* window);
  void deregister_window(GLFWwindow* window);
  void poll_events();
  class Callbacks {
   public:
    static void error_callback(int error, const char* description);
    static void key_action_callback(GLFWwindow* window, int key, int scancode,
                                    int action, int mods);
  };

 private:
};

inline void Events::poll_events() { glfwPollEvents(); }

}  // namespace Modules
}  // namespace SargassoEngine

#endif
