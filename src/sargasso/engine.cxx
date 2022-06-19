
#include "sargasso/engine.h"

#include "sargasso/common/log.h"
#include "sargasso/config.h"
#include "sargasso/graphics/graphics.h"
#include "sargasso/project_config.h"
#include "sargasso/window/window_config.h"
#include "sargasso/window/window_manager.h"

// Importing these last
#include "sargasso/graphics/opengl.h"

namespace sargasso {

static const common::Log logger(sargasso::ENGINE_NAME);

Engine::Engine(const ProjectConfig& projectConfig) : _projectConfig(projectConfig) {
    logger.info("Version: %s", sargasso::ENGINE_VERSION);
}

void Engine::initialize() {
    switch (_projectConfig.graphicsBackend) {
        case graphics::EGraphicsBackend::kOpenGL:
            _glGraphics = new graphics::GraphicsManager<graphics::OpenGL>();
            _glWindowManager =
                new window::WindowManager<graphics::OpenGL>(_projectConfig.window, *_glGraphics);
            _glWindowManager->init();
            logger.info("Backend %s-%s", graphics::GraphicsManager<graphics::OpenGL>::BACKEND_NAME,
                        graphics::GraphicsManager<graphics::OpenGL>::getVersionString().c_str());
            break;
        case graphics::EGraphicsBackend::kVulkan:
        case graphics::EGraphicsBackend::kDummy:
        case graphics::EGraphicsBackend::kUndefined:
        default:
            logger.error("<initialize()> Specified backend not implemented.");
            break;
    }
}

void Engine::terminate() {
    switch (_projectConfig.graphicsBackend) {
        case graphics::EGraphicsBackend::kOpenGL:
            _glWindowManager->terminate();
            delete _glWindowManager;
            delete _glGraphics;
            break;
        case graphics::EGraphicsBackend::kVulkan:
        case graphics::EGraphicsBackend::kDummy:
        case graphics::EGraphicsBackend::kUndefined:
        default:
            logger.error("<terminate()> Specified backend not implemented.");
            break;
    }
}

void Engine::run() {
    switch (_projectConfig.graphicsBackend) {
        case graphics::EGraphicsBackend::kOpenGL:
            _glWindowManager->run();
            break;
        case graphics::EGraphicsBackend::kVulkan:
        case graphics::EGraphicsBackend::kDummy:
        case graphics::EGraphicsBackend::kUndefined:
        default:
            logger.error("<run()> Specified backend not implemented.");
            break;
    }
}

template <>
const graphics::GraphicsManager<graphics::OpenGL>& Engine::getGraphics() const {
    return *_glGraphics;
}

template <>
graphics::GraphicsManager<graphics::OpenGL>& Engine::getGraphics() {
    return *_glGraphics;
}

}  // namespace sargasso
