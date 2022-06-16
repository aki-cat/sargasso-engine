
#include "sargasso/engine.h"

#include "sargasso/common/log.h"
#include "sargasso/config.h"
#include "sargasso/graphics/graphics.h"
#include "sargasso/project_config.h"
#include "sargasso/window/window_config.h"
#include "sargasso/window/window_manager.h"

// Importing these last
#include "sargasso/graphics/dummy.h"
#include "sargasso/graphics/opengl.h"
#include "sargasso/graphics/vulkan.h"

namespace sargasso {
namespace graphics {

IGraphicsManager* instantiateBackend(const EGraphicsBackend backend) {
    IGraphicsManager* graphicsBackend = nullptr;
    switch (backend) {
        case EGraphicsBackend::kOpenGL:
            graphicsBackend = new OpenGLGraphics();
            break;
        case EGraphicsBackend::kVulkan:
            graphicsBackend = new VulkanGraphics();
            break;
        case EGraphicsBackend::kDummy:
        default:
            graphicsBackend = new DummyGraphics();
            break;
    }
    return graphicsBackend;
}

}  // namespace graphics

static const common::Log logger(sargasso::ENGINE_NAME);

Engine::Engine(const ProjectConfig& projectConfig) : _projectConfig(projectConfig) {
    logger.info("Version: %s", sargasso::ENGINE_VERSION);
}

void Engine::initialize() {
    _graphics = graphics::instantiateBackend(_projectConfig.graphicsBackend);
    _windowManager = new window::WindowManager(_projectConfig.window, *_graphics);
    _windowManager->init();
    logger.info("Backend %s-%s", _graphics->getName(), _graphics->getVersionString());
}

void Engine::terminate() {
    _windowManager->terminate();
    delete _windowManager;
    delete _graphics;
}

void Engine::run() {
    _windowManager->run();
}
}  // namespace sargasso
