
#include "front_end/front_end_system.h"

#include <iostream>

using SargassoEngine::FrontEnd::FrontEndSystem;

FrontEndSystem::FrontEndSystem() {
  std::cout << "Initializing GLFW..." << std::endl;

  if (!glfwInit()) {
    std::cerr << "Init failed!" << std::endl;
    _initialized = false;
    return;
  }

  _graphics = new Graphics();
  _events = new Events();
  _initialized = true;
}

FrontEndSystem::~FrontEndSystem() {
  std::cout << "Terminating GLFW..." << std::endl;

  delete _events;
  delete _graphics;

  if (_initialized) {
    glfwTerminate();
  }
}
