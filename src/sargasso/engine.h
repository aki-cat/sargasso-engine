#ifndef SARGASSO_ENGINE_H_
#define SARGASSO_ENGINE_H_

#define SARGASSO_BACKEND_ENUM_DUMMY   0
#define SARGASSO_BACKEND_ENUM_OPEN_GL 1
#define SARGASSO_BACKEND_ENUM_VULKAN  2

#if SARGASSO_ENGINE_BACKEND == SARGASSO_BACKEND_ENUM_OPEN_GL
#define GLFW_INCLUDE_NONE
#define SARGASSO_GRAPHICS_BACKEND_HEADER "sargasso/graphics/opengl/opengl_graphics.h"
#define SargassoGraphicsBackend          sargasso::graphics::opengl::OpenGLGraphics
#include <GL/gl3w.h>  // GL loader must be included BEFORE glfw
#else
#define SARGASSO_GRAPHICS_BACKEND_HEADER "sargasso/graphics/dummy_graphics.h"
#define SargassoGraphicsBackend          sargasso::graphics::DummyGraphics
#endif

#include "sargasso/graphics/graphics.h"
#include "sargasso/project_config.h"
#include "sargasso/window/window_manager.h"

#include <GLFW/glfw3.h>

using sargasso::graphics::IGraphicsManager;
using sargasso::window::IWindowManager;

namespace sargasso {

class Engine {
   public:
    Engine(const ProjectConfig& projectConfig);
    void setup();
    void terminate();
    void run();

   private:
    const ProjectConfig& _projectConfig;
    IWindowManager* _windowManager;
    IGraphicsManager* _graphics;
};

}  // namespace sargasso

#endif
