#ifndef SARGASSO_ENGINE_H_
#define SARGASSO_ENGINE_H_

#include "sargasso/graphics/graphics.h"
#include "sargasso/graphics/opengl.h"
#include "sargasso/project_config.h"
#include "sargasso/window/window_manager.h"

namespace sargasso {

class Engine {
   public:
    Engine(const ProjectConfig& projectConfig);
    void initialize();
    void terminate();
    void run();

    template <typename T>
    const graphics::GraphicsManager<T>& getGraphics() const;
    template <typename T>
    graphics::GraphicsManager<T>& getGraphics();

   private:
    const ProjectConfig& _projectConfig;

    // If you implement new backends, add specializations for them here.
    window::WindowManager<graphics::OpenGL>* _glWindowManager;
    graphics::GraphicsManager<graphics::OpenGL>* _glGraphics;
};

}  // namespace sargasso

#endif
