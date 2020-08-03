#include "glfw.h"

#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>

namespace SargassoEngine {

GLFW::GLFW() {
  std::cout << "Initializing GLFW..." << std::endl;
  _window = nullptr;
  if (!glfwInit()) {
    // Initialization failed
    _initialized = false;
  }
  _initialized = true;
  glfwSetErrorCallback(error_callback);
}

void GLFW::create_window() {
  if (_window) {
    throw std::exception();
  }
  _window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
}

bool GLFW::is_window_valid() { return !!_window; }

bool GLFW::is_initialized() { return _initialized; }

GLFW::~GLFW() {
  std::cout << "Terminating GLFW..." << std::endl;
  if (_window) {
    glfwDestroyWindow(_window);
  }
  if (_initialized) {
    glfwTerminate();
  }
}

void error_callback(int error, const char* description) {
  std::cerr << std::string("Error: ") + std::string(description) << std::endl;
}

}  // namespace SargassoEngine
