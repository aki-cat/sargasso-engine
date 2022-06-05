#include <GLFW/glfw3.h>
#include <exception>
#include <sargasso/common/log.h>
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
    Log _logger{"miniVk"};

    void init() {
        if (!glfwInit()) {
            throw "GLFW Initialization failed.";
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        _window = glfwCreateWindow(1280, 720, "Vulkan window", nullptr, nullptr);
        glfwSetKeyCallback(_window, key_callback);
        createVkInstance();

    }

    void createVkInstance() {
        // application general info
        VkApplicationInfo app_info{};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "miniVk";
        app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName = "sargasso";
        app_info.apiVersion = VK_API_VERSION_1_0;

        // load extensions?
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        _logger.info("%d extensions available!", extensionCount);
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);
        _logger.info("%d extensions used:", extensionCount);
        for (size_t i = 0; i < extensionCount; i++)
        {
            _logger.info("  [%d]: %s", i, glfwExtensions[i]);
        }

        // instance info
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &app_info;
        createInfo.enabledExtensionCount = extensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create vulkan instance!");
        };
    }

    void loop() {
        while (!glfwWindowShouldClose(_window)) {
            glfwPollEvents();
        }
    }

    void teardown() {
        glfwDestroyWindow(_window);

        glfwTerminate();
    }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_F8 && action == GLFW_RELEASE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
};

}  // namespace miniVk
