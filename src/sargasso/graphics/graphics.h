#ifndef SARGASSO_GRAPHICS_IGRAPHICS_H_
#define SARGASSO_GRAPHICS_IGRAPHICS_H_

// #define GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_NONE  // Change this when using vulkan.

#include <sml/color.h>

namespace sargasso {
namespace graphics {

enum EGraphicsBackend {
    kDummy = 0x00,
    kOpenGL = 0x01,
    kVulkan = 0x02,  // Not implemented.
    kUndefined = 0xff
};

class IGraphicsManager {
   public:
    IGraphicsManager() {}
    IGraphicsManager(const IGraphicsManager&) = delete;
    IGraphicsManager(const IGraphicsManager&&) = delete;
    virtual ~IGraphicsManager() {}

    // Initialization
    virtual bool initialize() = 0;

    // Imperative rendering
    virtual void present(void* params) = 0;
    virtual void setViewport(int x, int y, uint32_t width, uint32_t height) = 0;
    virtual void setClearColor(sml::Color color) = 0;
    virtual void clear() = 0;

    // Meta information
    virtual const EGraphicsBackend getType() const = 0;
    virtual const char* getName() const = 0;
    virtual const char* getVersionString() const = 0;
    virtual const int getVersionMajor() const = 0;
    virtual const int getVersionMinor() const = 0;
};

}  // namespace graphics
}  // namespace sargasso

#endif
