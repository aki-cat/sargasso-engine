
#include "sargasso/graphics/vulkan.h"

#include <exception>
#include <sml/color.h>

namespace sargasso {
namespace graphics {

bool VulkanGraphics::initialize() {
    throw std::runtime_error("Not implemented yet.");
}

void VulkanGraphics::setViewport(int x, int y, uint32_t width, uint32_t height) {
    throw std::runtime_error("Not implemented yet.");
}

void VulkanGraphics::setClearColor(sml::Color color) {
    throw std::runtime_error("Not implemented yet.");
}

void VulkanGraphics::clear() {
    throw std::runtime_error("Not implemented yet.");
}

const EGraphicsBackend VulkanGraphics::getType() const {
    return EGraphicsBackend::kVulkan;
}

const char* VulkanGraphics::getName() const {
    throw std::runtime_error("Not implemented yet.");
}

const char* VulkanGraphics::getVersionString() const {
    throw std::runtime_error("Not implemented yet.");
}

const int VulkanGraphics::getVersionMajor() const {
    throw std::runtime_error("Not implemented yet.");
}

const int VulkanGraphics::getVersionMinor() const {
    throw std::runtime_error("Not implemented yet.");
}

}  // namespace graphics
}  // namespace sargasso
