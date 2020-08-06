
#include "modules/events.h"

#include <GLFW/glfw3.h>

#include <iostream>

using SargassoEngine::Modules::Events;

Events::Events() { glfwSetErrorCallback(Events::Callbacks::error_callback); }
Events::~Events() {}

void Events::register_window(GLFWwindow* window) {
  glfwSetKeyCallback(window, Events::Callbacks::key_action_callback);
}

void Events::deregister_window(GLFWwindow* window) {
  glfwSetKeyCallback(window, NULL);
}

void Events::Callbacks::error_callback(int error, const char* description) {
  std::cerr << "Error: " << description << std::endl;
}

void Events::Callbacks::key_action_callback(GLFWwindow* window, int key,
                                            int scancode, int action,
                                            int mods) {
  if (window == nullptr) {
    return;
  }

  if (key == GLFW_KEY_F8 && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}
