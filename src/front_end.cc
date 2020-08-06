
#include "front_end.h"

#include <iostream>

using SargassoEngine::FrontEnd;

FrontEnd::FrontEnd() {
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

FrontEnd::~FrontEnd() {
  std::cout << "Terminating GLFW..." << std::endl;

  delete _events;
  delete _graphics;

  if (_initialized) {
    glfwTerminate();
  }
}
