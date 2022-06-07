#include "miniVk/vulkan_manager.h"

#include <GLFW/glfw3.h>
#include <vector>
#include <vulkan/vulkan.h>

namespace miniVk {

static std::vector<const char*> loadRequiredExtensions();

VulkanManager::VulkanManager() {
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

    _validatorManager.initValidators(_instance);
}

VulkanManager::~VulkanManager() {
    vkDestroyInstance(_instance, nullptr);
}

static std::vector<const char*> loadRequiredExtensions() {
    uint32_t extensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + extensionCount);

#ifndef NDEBUG
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
    return extensions;
}

}  // namespace miniVk
