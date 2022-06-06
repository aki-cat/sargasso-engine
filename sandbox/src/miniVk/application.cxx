#include "miniVk/validation.cxx"

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
    VkInstance _instance;
    Validator _validator;
    Log _logger{"miniVk"};

    void init() {
        if (!glfwInit()) {
            throw "GLFW Initialization failed.";
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        _window = glfwCreateWindow(1280, 720, "Vulkan window", nullptr, nullptr);
        glfwSetKeyCallback(_window, keyInputCallback);
        createVkInstance();
        _validator.initValidators(_instance);
    }

    void loop() {
        while (!glfwWindowShouldClose(_window)) {
            glfwPollEvents();
        }
    }

    void teardown() {
        vkDestroyInstance(_instance, nullptr);
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void createVkInstance() {
        // application general info
        VkApplicationInfo app_info{};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "miniVk";
        app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName = "sargasso";
        app_info.apiVersion = VK_API_VERSION_1_0;

        // log available extensions
        const auto extensions = loadRequiredExtensions();

        // instance info
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &app_info;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();
        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create vulkan instance!");
        };
    }

    std::vector<const char*> loadRequiredExtensions() {
        uint32_t extensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + extensionCount);

#ifndef NDEBUG
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
        return extensions;
    }

    static void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_F8 && action == GLFW_RELEASE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
};

}  // namespace miniVk
