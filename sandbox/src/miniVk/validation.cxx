
#include <exception>
#include <sargasso/common/log.h>
#include <vulkan/vulkan.h>

namespace miniVk {

using sargasso::common::Log;

VkResult createDebugUtilsMessengerEXT(VkInstance instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                      const VkAllocationCallbacks* pAllocator,
                                      VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
        instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

class Validator {
   public:
    Validator() = default;

    void initValidators(VkInstance instance) {
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;  // Optional

        if (createDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &_debugMessenger) !=
            VK_SUCCESS) {
            throw std::runtime_error("Failed to set up debug messenger!");
        }
    }

   private:
    VkDebugUtilsMessengerEXT _debugMessenger;

#define DEBUG_CALLBACK_RETURN VKAPI_ATTR VkBool32 VKAPI_CALL
    static DEBUG_CALLBACK_RETURN debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        Log debugLogger("VULKAN DEBUG");
        if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
            debugLogger.debug(pCallbackData->pMessage);
        } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
            debugLogger.info(pCallbackData->pMessage);
        } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            debugLogger.warning(pCallbackData->pMessage);
        } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            debugLogger.error(pCallbackData->pMessage);
            return VK_TRUE;
        }

        return VK_FALSE;
    }
#undef DEBUG_CALLBACK_RETURN
};

}  // namespace miniVk
