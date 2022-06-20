#ifndef SARGASSO_GRAPHICS_GRAPHICS_H_
#define SARGASSO_GRAPHICS_GRAPHICS_H_

// #define GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_NONE  // Change this when using vulkan.

#include <sml/color.h>
#include <sstream>
#include <string>

namespace sargasso {
namespace graphics {

enum EGraphicsBackend {
    kDummy = 0x00,
    kOpenGL = 0x01,
    kVulkan = 0x02,  // Not implemented.
    kUndefined = 0xff
};

template <typename T>
class GraphicsManager {
   public:
    GraphicsManager() = default;

    // Deleted constructors
    GraphicsManager(GraphicsManager&) = delete;
    GraphicsManager(GraphicsManager&&) = delete;
    GraphicsManager(const GraphicsManager&) = delete;
    GraphicsManager(const GraphicsManager&&) = delete;

    // Initialization
    bool initialize() {
        return false;
    }

    // Imperative rendering
    void clear() {}
    void present() {}
    void setViewport(int x, int y, uint32_t width, uint32_t height) {}
    void setClearColor(sml::Color color) {}

    static const std::string getVersionString() {
        std::stringstream str;
        str << "v" << BACKEND_VERSION_MAJOR << "." << BACKEND_VERSION_MINOR;
        return str.str();
    }

    static const char* BACKEND_NAME;
    static const uint32_t BACKEND_VERSION_MAJOR;
    static const uint32_t BACKEND_VERSION_MINOR;
    static const EGraphicsBackend BACKEND_TYPE;

   private:
    MeshManager _meshManager;
};

}  // namespace graphics
}  // namespace sargasso

#endif  // SARGASSO_GRAPHICS_GRAPHICS_H_
