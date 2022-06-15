#ifndef SARGASSO_GRAPHICS_IGRAPHICS_H_
#define SARGASSO_GRAPHICS_IGRAPHICS_H_

#define SARGASSO_BACKEND_ENUM_DUMMY   0
#define SARGASSO_BACKEND_ENUM_OPEN_GL 1
#define SARGASSO_BACKEND_ENUM_VULKAN  2  // not implemented

#if SARGASSO_ENGINE_BACKEND == SARGASSO_BACKEND_ENUM_DUMMY
#define SARGASSO_GRAPHICS_BACKEND_HEADER "sargasso/graphics/dummy.h"
#define SargassoGraphicsBackend          sargasso::graphics::DummyGraphics
#include <GL/gl3w.h>  // GL loader must be included BEFORE glfw
#elif SARGASSO_ENGINE_BACKEND == SARGASSO_BACKEND_ENUM_OPEN_GL
#define GLFW_INCLUDE_NONE
#define SARGASSO_GRAPHICS_BACKEND_HEADER "sargasso/graphics/opengl.h"
#define SargassoGraphicsBackend          sargasso::graphics::OpenGLGraphics
#elif SARGASSO_ENGINE_BACKEND == SARGASSO_BACKEND_ENUM_VULKAN
#define GLFW_INCLUDE_VULKAN
#define SARGASSO_GRAPHICS_BACKEND_HEADER "sargasso/graphics/vulkan.h"
#define SargassoGraphicsBackend          sargasso::graphics::VulkanGraphics
#endif

#include <sml/color.h>

namespace sargasso {
namespace graphics {

using sml::Color;

class IGraphicsManager {
   public:
    IGraphicsManager() {}
    IGraphicsManager(const IGraphicsManager&) = delete;
    IGraphicsManager(const IGraphicsManager&&) = delete;
    virtual ~IGraphicsManager() {}
    virtual bool initialize(void* proc_address) = 0;
    virtual void setViewport(int x, int y, uint32_t width, uint32_t height) = 0;
    virtual void setClearColor(Color color) = 0;
    virtual void clear() = 0;
    virtual const char* getName() const = 0;
    virtual const char* getVersionString() const = 0;
    virtual const int getVersionMajor() const = 0;
    virtual const int getVersionMinor() const = 0;
};

}  // namespace graphics
}  // namespace sargasso

#endif
