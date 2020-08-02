#include "glfw.h"

#include <GLFW/glfw3.h>

#include <iostream>

namespace CoffeeEngine {
namespace GLFW {

void error_callback(int error, const char* description) {
  std::cerr << std::string("Error: ") + std::string(description) << std::endl;
}

bool init() {
  if (!glfwInit()) {
    // Initialization failed
    return false;
  }
  glfwSetErrorCallback(error_callback);
  glfwTerminate();
  return true;
}

}  // namespace GLFW
}  // namespace CoffeeEngine
