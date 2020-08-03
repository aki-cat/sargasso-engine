
#include <iostream>

#include "glfw.h"

using SargassoEngine::GLFW;

const int DELAY_SECONDS = 15;

int main() {
  std::cout << "Hello world" << std::endl;

  GLFW glfw_instance = GLFW();
  if (!glfw_instance.is_initialized()) {
    return -1;
  }

  glfw_instance.create_window();
  if (!glfw_instance.is_window_valid()) {
    return -1;
  }

  time_t start_time = std::time(nullptr);
  std::cout << "Start!" << std::endl;

  time_t current_time = start_time;

  time_t now = std::time(nullptr);
  while (now - start_time <= DELAY_SECONDS) {
    if (now > current_time) {
      current_time = now;
      std::cout << current_time - start_time << std::endl;
    }
    now = std::time(nullptr);
  }

  std::cout << "Done!" << std::endl;

  return 0;
}
