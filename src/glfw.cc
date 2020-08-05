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
  glfwSetErrorCallback(GLFW::Callbacks::error_callback);
}

void GLFW::create_window() {
  if (_window) {
    throw std::exception();
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  _window = glfwCreateWindow(640, 480, "Sargasso Engine", NULL, NULL);

  // Initialize window
  glfwMakeContextCurrent(_window);
  glfwSetKeyCallback(_window, GLFW::Callbacks::key_action_callback);
  glfwFocusWindow(_window);
  glfwSwapInterval(1);
}

int GLFW::get_width() { return _width; }
int GLFW::get_height() { return _height; }
bool GLFW::is_initialized() { return _initialized; }
bool GLFW::should_window_close() { return glfwWindowShouldClose(_window); }

void GLFW::render() {
  glfwGetFramebufferSize(_window, &_width, &_height);
  glViewport(0, 0, _width, _height);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

GLFW::~GLFW() {
  std::cout << "Terminating GLFW..." << std::endl;
  if (_window) {
    glfwDestroyWindow(_window);
  }
  if (_initialized) {
    glfwTerminate();
  }
}

void GLFW::Callbacks::error_callback(int error, const char* description) {
  std::cerr << std::string("Error: ") + std::string(description) << std::endl;
}

void GLFW::Callbacks::key_action_callback(GLFWwindow* window, int key,
                                          int scancode, int action, int mods) {
  if (key == GLFW_KEY_F8 && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

}  // namespace SargassoEngine
