#ifndef COFFEE_ENGINE_GLFW_H
#define COFFEE_ENGINE_GLFW_H

#include <GLFW/glfw3.h>

namespace SargassoEngine {

class GLFW {
 public:
  GLFW();
  ~GLFW();
  void create_window();
  int get_width();
  int get_height();
  bool is_initialized();
  bool should_window_close();
  void render();

  class Callbacks {
   public:
    static void error_callback(int error, const char* description);
    static void key_action_callback(GLFWwindow* window, int key, int scancode,
                                    int action, int mods);
  };

 private:
  GLFWwindow* _window;
  bool _initialized;
  int _width;
  int _height;
};
}  // namespace SargassoEngine

#endif
