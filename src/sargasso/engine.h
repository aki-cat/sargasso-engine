#ifndef SARGASSO_ENGINE_H_
#define SARGASSO_ENGINE_H_

#include "sargasso/config/project_config.h"
#include "sargasso/graphics/graphics.h"
#include "sargasso/window/window_manager.h"

#if SARGASSO_ENGINE_BACKEND_OPENGL
#define SARGASSO_GRAPHICS_BACKEND_HEADER "sargasso/graphics/opengl/opengl_graphics.h"
#define SargassoGraphicsBackend          sargasso::graphics::opengl::OpenGLGraphics
#else
#define SARGASSO_GRAPHICS_BACKEND_HEADER "sargasso/graphics/dummy_graphics.h"
#define SargassoGraphicsBackend          sargasso::graphics::DummyGraphics
#endif

using sargasso::graphics::IGraphicsManager;
using sargasso::window::IWindowManager;

namespace sargasso {

class Engine {
   public:
    Engine(const config::ProjectConfig& projectConfig);
    void setup();
    void terminate();
    void run();

   private:
    const config::ProjectConfig& _projectConfig;
    IWindowManager* _windowManager;
    IGraphicsManager* _graphics;
};

}  // namespace sargasso

#endif
