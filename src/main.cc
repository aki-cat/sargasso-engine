
#include <iostream>

#include "front_end.h"
#include "modules/events.h"
#include "modules/graphics.h"

using SargassoEngine::FrontEnd;
using SargassoEngine::Modules::Events;
using SargassoEngine::Modules::Graphics;
using SargassoEngine::Modules::Time;

int main() {
  std::cout << "Hello world" << std::endl;

  FrontEnd front_end = FrontEnd();
  if (!front_end.is_initialized()) {
    return -1;
  }

  std::cout << "Init successful!" << std::endl;

  uint64_t frame_number = 0;

  front_end.start();

  Graphics &graphics = front_end.get_module<Graphics>();
  Events &events = front_end.get_module<Events>();
  Time &time = front_end.get_module<Time>();
  while (!graphics.should_window_close()) {
    // main loop
    time.start_frame();
    std::cout << "Frame time: " << time.get_delta() << std::endl;

    frame_number++;
    graphics.render();
    events.poll_events();

    time.end_frame();
  }

  front_end.stop();

  std::cout << "Ran " << frame_number << " frames!" << std::endl;
  std::cout << "Done!" << std::endl;

  return 0;
}
