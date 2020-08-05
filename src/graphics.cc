#include "graphics.h"

#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>

namespace SargassoEngine {

Graphics::Graphics() {
  std::cout << "Initializing GLFW..." << std::endl;
  _window = nullptr;
  if (!glfwInit()) {
    // Initialization failed
    _initialized = false;
  }
  _initialized = true;
  glfwSetErrorCallback(Graphics::Callbacks::error_callback);
}

void Graphics::create_window() {
  if (_window) {
    throw std::exception();
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

  _window = glfwCreateWindow(960, 540, "Sargasso Engine", NULL, NULL);

  // Initialize window
  glfwMakeContextCurrent(_window);
  glfwSetKeyCallback(_window, Graphics::Callbacks::key_action_callback);
  glfwFocusWindow(_window);
  glfwSwapInterval(1);
}

int Graphics::get_width() { return _width; }
int Graphics::get_height() { return _height; }
bool Graphics::is_initialized() { return _initialized; }
bool Graphics::should_window_close() { return glfwWindowShouldClose(_window); }

void Graphics::render() {
  glfwGetFramebufferSize(_window, &_width, &_height);
  glViewport(0, 0, _width, _height);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

Graphics::~Graphics() {
  std::cout << "Terminating GLFW..." << std::endl;
  if (_window) {
    glfwDestroyWindow(_window);
  }
  if (_initialized) {
    glfwTerminate();
  }
}

void Graphics::Callbacks::error_callback(int error, const char* description) {
  std::cerr << std::string("Error: ") + std::string(description) << std::endl;
}

void Graphics::Callbacks::key_action_callback(GLFWwindow* window, int key,
                                              int scancode, int action,
                                              int mods) {
  if (key == GLFW_KEY_F8 && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

}  // namespace SargassoEngine
