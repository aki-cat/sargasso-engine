
#include "sargasso/engine.h"

#include "sargasso/common/log.h"
#include "sargasso/config.h"
#include "sargasso/config/project_config.h"
#include "sargasso/config/window_config.h"
#include "sargasso/window/glfw/glfw_context_wrapper.h"

#include SARGASSO_GRAPHICS_BACKEND_HEADER

using sargasso::Engine;
using sargasso::common::Log;
using sargasso::config::ProjectConfig;
using sargasso::config::WindowConfig;
using sargasso::window::glfw::GLFWContextWrapper;

static const Log logger(sargasso::ENGINE_NAME);

Engine::Engine(const ProjectConfig& projectConfig) : _projectConfig(projectConfig) {
    logger.info("Version: %s", sargasso::ENGINE_VERSION);
}

void Engine::setup() {
    _graphics = new SargassoGraphicsBackend();
    _windowManager = new GLFWContextWrapper(_projectConfig.window, *_graphics);
    logger.info("Backend %s-%s", _graphics->getName(), _graphics->getVersion());
}

void Engine::terminate() {
    delete _windowManager;
    delete _graphics;
}

void Engine::run() {
    _windowManager->run();
}
