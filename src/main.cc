
#include <iostream>

#include "front_end/front_end_system.h"
#include "front_end/modules/events.h"
#include "front_end/modules/graphics.h"
#include "front_end/modules/time.h"

using SargassoEngine::FrontEnd::FrontEndSystem;
using SargassoEngine::FrontEnd::Modules::Events;
using SargassoEngine::FrontEnd::Modules::Graphics;
using SargassoEngine::FrontEnd::Modules::Time;

int main() {
  std::cout << "Hello world" << std::endl;

  FrontEndSystem front_end = FrontEndSystem();
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
