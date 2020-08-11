
#include "front_end/modules/graphics.h"

#include <GLFW/glfw3.h>

#include <exception>

#include "engine.h"

using SargassoEngine::FrontEnd::Modules::Graphics;

Graphics::Graphics() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

  _window = glfwCreateWindow(960, 540, SargassoEngine::ENGINE_NAME, NULL, NULL);

  // Initialize window
  glfwMakeContextCurrent(_window);
  glfwFocusWindow(_window);
  glfwSwapInterval(1);
}

Graphics::~Graphics() {
  if (_window) {
    glfwDestroyWindow(_window);
  }
}

void Graphics::render() {
  glfwGetFramebufferSize(_window, &_width, &_height);
  glViewport(0, 0, _width, _height);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(_window);
}
