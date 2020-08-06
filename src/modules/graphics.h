#ifndef SARGASSO_ENGINE_MODULES_GRAPHICS_H
#define SARGASSO_ENGINE_MODULES_GRAPHICS_H

#include <GLFW/glfw3.h>

namespace SargassoEngine {
namespace Modules {

class Graphics {
 public:
  Graphics();
  ~Graphics();
  GLFWwindow* get_window();
  const int get_width();
  const int get_height();
  const bool should_window_close();
  void render();

 private:
  GLFWwindow* _window;
  int _width;
  int _height;
};

inline GLFWwindow* Graphics::get_window() { return _window; }

inline const int Graphics::get_width() { return _width; }

inline const int Graphics::get_height() { return _height; }

inline const bool Graphics::should_window_close() {
  return glfwWindowShouldClose(_window);
}

}  // namespace Modules
}  // namespace SargassoEngine

#endif
