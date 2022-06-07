#include "miniVk/vulkan_manager.h"

#include <GLFW/glfw3.h>
#include <vector>
#include <vulkan/vulkan.h>
#include <sstream>

namespace miniVk {

static std::vector<const char*> loadRequiredExtensions();
static bool isDeviceSuitable(VkPhysicalDevice device);

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

void VulkanManager::setPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());

    std::stringstream deviceList;
    deviceList << "Device list:";
    for (const auto& device : devices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        deviceList << "\n  + " << deviceProperties.deviceName;
        if (isDeviceSuitable(device)) {
            _physicalDevice = device;
            break;
        }
    }
    _logger.info(deviceList.str().c_str());

    if (_physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
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

static bool isDeviceSuitable(VkPhysicalDevice device) {
    // TODO: Device suitability algorithm
    return true;
    // VkPhysicalDeviceProperties deviceProperties;
    // VkPhysicalDeviceFeatures deviceFeatures;
    // vkGetPhysicalDeviceProperties(device, &deviceProperties);
    // vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    // return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
    //        deviceFeatures.geometryShader;
}

}  // namespace miniVk
