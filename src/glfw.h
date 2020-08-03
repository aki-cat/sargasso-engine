#ifndef COFFEE_ENGINE_GLFW_H
#define COFFEE_ENGINE_GLFW_H

namespace CoffeeEngine {
namespace GLFW {

void error_callback(int, const char*);
bool init();
void terminate();

}  // namespace GLFW
}  // namespace CoffeeEngine

#endif
