
#include <iostream>

#include "glfw.h"

using std::cout;
using std::endl;
using std::time;

using CoffeeEngine::GLFW;

const int DELAY_SECONDS = 15;

int main() {
  cout << "Hello world" << endl;

  GLFW glfw_instance = GLFW();
  if (!glfw_instance.is_initialized()) {
    return -1;
  }

  glfw_instance.create_window();
  if (!glfw_instance.is_window_valid()) {
    return -1;
  }

  time_t start_time = time(nullptr);
  cout << "Start!" << endl;

  time_t current_time = start_time;

  time_t now = time(nullptr);
  while (now - start_time <= DELAY_SECONDS) {
    if (now > current_time) {
      current_time = now;
      cout << current_time - start_time << endl;
    }
    now = time(nullptr);
  }

  cout << "Done!" << endl;

  return 0;
}
