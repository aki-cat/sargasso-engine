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

   private:
    VkInstance _instance;
    VulkanValidationManager _validatorManager{};
    sargasso::common::Log _logger{"miniVk::VulkanManager"};
};

}  // namespace miniVk

#endif  // MINIVK_VULKAN_MANAGER
