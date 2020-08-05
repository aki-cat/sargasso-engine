
#include <time.h>

#include <iostream>

#include "modules/graphics.h"

using SargassoEngine::Modules::Graphics;

int main() {
  std::cout << "Hello world" << std::endl;

  Graphics graphics = Graphics();
  if (!graphics.is_initialized()) {
    return -1;
  }

  graphics.create_window();

  double delta = 0.0;
  uint64_t frame_number = 0;

  while (!graphics.should_window_close()) {
    // main loop
    double frame_start = glfwGetTime();

    frame_number++;
    graphics.render();

    delta = glfwGetTime() - frame_start;
  }

  std::cout << "Done!" << std::endl;

  return 0;
}
