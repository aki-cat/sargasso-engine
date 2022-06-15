
#include "sargasso/engine.h"

#include "sargasso/common/log.h"
#include "sargasso/config.h"
#include "sargasso/project_config.h"
#include "sargasso/window/window_config.h"

#include "sargasso/window/window_manager.h"
#include SARGASSO_GRAPHICS_BACKEND_HEADER

using sargasso::Engine;
using sargasso::ProjectConfig;
using sargasso::common::Log;
using sargasso::window::WindowConfig;
using sargasso::window::WindowManager;

static const Log logger(sargasso::ENGINE_NAME);

Engine::Engine(const ProjectConfig& projectConfig) : _projectConfig(projectConfig) {
    logger.info("Version: %s", sargasso::ENGINE_VERSION);
}

void Engine::setup() {
    _graphics = new SargassoGraphicsBackend();
    _windowManager = new WindowManager(_projectConfig.window, *_graphics);
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
