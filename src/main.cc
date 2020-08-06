
#include <iostream>

#include "front_end.h"
#include "modules/events.h"
#include "modules/graphics.h"

using SargassoEngine::FrontEnd;
using SargassoEngine::Modules::Events;
using SargassoEngine::Modules::Graphics;

int main() {
  std::cout << "Hello world" << std::endl;

  FrontEnd front_end = FrontEnd();
  if (!front_end.is_initialized()) {
    return -1;
  }

  std::cout << "Init successful!" << std::endl;

  double delta = 0.0;
  uint64_t frame_number = 0;

  front_end.start();

  Graphics &graphics = front_end.get_module<Graphics>();
  Events &events = front_end.get_module<Events>();
  while (!graphics.should_window_close()) {
    // main loop
    double frame_start = glfwGetTime();

    frame_number++;
    graphics.render();
    events.poll_events();

    delta = glfwGetTime() - frame_start;
  }

  front_end.stop();

  std::cout << "Done!" << std::endl;

  return 0;
}
