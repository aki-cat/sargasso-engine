#ifndef SARGASSO_GRAPHICS_VULKAN_H_
#define SARGASSO_GRAPHICS_VULKAN_H_

#include "sargasso/graphics/graphics.h"

#include <sml/color.h>

namespace sargasso {
namespace graphics {

class VulkanGraphics : virtual public IGraphicsManager {
   public:
    VulkanGraphics() : IGraphicsManager() {}
    VulkanGraphics(const VulkanGraphics&) = delete;
    VulkanGraphics(const VulkanGraphics&&) = delete;

    bool initialize() override;
    void setViewport(int x, int y, uint32_t width, uint32_t height) override;
    void setClearColor(sml::Color color) override;
    void clear() override;
    void present(void*) override {}

    const EGraphicsBackend getType() const override;
    const char* getName() const override;
    const char* getVersionString() const override;
    const int getVersionMajor() const override;
    const int getVersionMinor() const override;
    const EGraphicsBackend backendType = EGraphicsBackend::kVulkan;
};

}  // namespace graphics
}  // namespace sargasso

#endif  // SARGASSO_GRAPHICS_VULKAN_H_
