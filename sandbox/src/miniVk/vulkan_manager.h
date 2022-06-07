#if !defined(MINIVK_VULKAN_MANAGER)
#define MINIVK_VULKAN_MANAGER

#include "miniVk/validation.h"

#include <sargasso/common/log.h>
#include <vulkan/vulkan.h>

namespace miniVk {

class VulkanManager {
   public:
    explicit VulkanManager();
    ~VulkanManager();
    void setPhysicalDevice();

   private:
    VkInstance _instance;
    VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
    VulkanValidationManager _validatorManager{};
    sargasso::common::Log _logger{"miniVk::VulkanManager"};
};

}  // namespace miniVk

#endif  // MINIVK_VULKAN_MANAGER
