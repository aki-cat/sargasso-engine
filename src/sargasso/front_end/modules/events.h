#ifndef SARGASSO_ENGINE_FRONT_END_EVENTS_H
#define SARGASSO_ENGINE_FRONT_END_EVENTS_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace SargassoEngine {
namespace FrontEnd {
namespace Modules {

class Events {
   public:
    explicit Events();
    Events(const Events&) = delete;
    Events(const Events&&) = delete;
    ~Events();
    void register_window(GLFWwindow* window);
    void deregister_window(GLFWwindow* window);
    void poll_events();
    class Callbacks {
       public:
        static void error_callback(int error, const char* description);
        static void key_action_callback(GLFWwindow* window, int key, int scancode, int action,
                                        int mods);
    };
};

inline void Events::poll_events() { glfwPollEvents(); }

}  // namespace Modules
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
