#ifndef COFFEE_ENGINE_GLFW_H
#define COFFEE_ENGINE_GLFW_H

#include <GLFW/glfw3.h>

namespace CoffeeEngine {

class GLFW {
 public:
  GLFW();
  void create_window();
  bool is_window_valid();
  bool is_initialized();
  ~GLFW();

 private:
  GLFWwindow* _window;
  bool _initialized;
};

void error_callback(int error, const char* description);

}  // namespace CoffeeEngine

#endif
