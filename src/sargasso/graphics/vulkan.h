#ifndef SARGASSO_GRAPHICS_VULKAN_H_
#define SARGASSO_GRAPHICS_VULKAN_H_

#include "sargasso/graphics/graphics.h"

namespace sargasso {
namespace graphics {

class VulkanGraphics : virtual public IGraphicsManager {
   public:
    VulkanGraphics() : IGraphicsManager() {}
    VulkanGraphics(const VulkanGraphics&) = delete;
    VulkanGraphics(const VulkanGraphics&&) = delete;

    bool initialize(void* proc_address) override;
    void setViewport(int x, int y, uint32_t width, uint32_t height) override;
    void setClearColor(Color color) override;
    void clear() override;

    const char* getName() const override;
    const char* getVersionString() const override;
    int getVersionMajor() const override;
    int getVersionMinor() const override;

   private:
    /* data */
};

}  // namespace graphics
}  // namespace sargasso

#endif  // SARGASSO_GRAPHICS_VULKAN_H_
