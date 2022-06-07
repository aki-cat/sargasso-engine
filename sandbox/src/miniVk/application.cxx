#include "miniVk/vulkan_manager.h"

#include <GLFW/glfw3.h>
#include <exception>
#include <sargasso/common/log.h>
#include <vector>
#include <vulkan/vulkan.h>

namespace miniVk {

using sargasso::common::Log;

class MiniVulkanApplication {
   public:
    void run() {
        init();
        loop();
        teardown();
    }

   private:
    GLFWwindow* _window;
    VulkanManager* _vulkanManager;

    void init() {
        if (!glfwInit()) {
            throw "GLFW Initialization failed.";
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        _window = glfwCreateWindow(1280, 720, "Vulkan window", nullptr, nullptr);
        glfwSetKeyCallback(_window, keyInputCallback);

        _vulkanManager = new VulkanManager();
    }

    void loop() {
        while (!glfwWindowShouldClose(_window)) {
            glfwPollEvents();
        }
    }

    void teardown() {
        delete _vulkanManager;
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    static void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_F8 && action == GLFW_RELEASE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
};

}  // namespace miniVk
