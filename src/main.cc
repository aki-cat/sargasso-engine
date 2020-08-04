
#include <time.h>

#include <iostream>

#include "glfw.h"

using SargassoEngine::GLFW;

int main() {
  std::cout << "Hello world" << std::endl;

  GLFW glfw_instance = GLFW();
  if (!glfw_instance.is_initialized()) {
    return -1;
  }

  glfw_instance.create_window();

  double delta = 0.0;
  uint64_t frame_number = 0;

  while (!glfw_instance.should_window_close()) {
    // main loop
    double frame_start = glfwGetTime();

    frame_number++;

    delta = glfwGetTime() - frame_start;
  }

  std::cout << "Done!" << std::endl;

  return 0;
}
