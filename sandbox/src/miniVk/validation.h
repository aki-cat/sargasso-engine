#if !defined(MINIVK_VULKAN_VALIDATION_MANAGER)
#define MINIVK_VULKAN_VALIDATION_MANAGER

#include <vulkan/vulkan.h>

namespace miniVk {

class VulkanValidationManager {
   public:
    VulkanValidationManager() = default;
    void initValidators(VkInstance instance);

   private:
    VkDebugUtilsMessengerEXT _debugMessenger;

    static VKAPI_ATTR VkBool32 VKAPI_CALL
    debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                  VkDebugUtilsMessageTypeFlagsEXT messageType,
                  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
};

}  // namespace miniVk

#endif  // MINIVK_VULKAN_VALIDATION_MANAGER
