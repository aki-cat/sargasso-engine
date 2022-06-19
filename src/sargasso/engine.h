#ifndef SARGASSO_ENGINE_H_
#define SARGASSO_ENGINE_H_

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
    void initialize();
    void terminate();
    void run();
    const IGraphicsManager& getGraphics() const;
    IGraphicsManager& getGraphics();

   private:
    const ProjectConfig& _projectConfig;
    IWindowManager* _windowManager;
    IGraphicsManager* _graphics;
};

}  // namespace sargasso

#endif
