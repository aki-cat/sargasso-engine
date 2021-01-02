
#include "sargasso/engine.h"

#include "sargasso/config.h"
#include "sargasso/window/glfw/glfw_context_wrapper.h"
#include "sargasso/window/icontext_wrapper.h"

using sargasso::Engine;
using sargasso::window::WindowConfig;
using sargasso::window::glfw::GLFWContextWrapper;

Engine::Engine() {
    WindowConfig config;
    _contextWrapper = new GLFWContextWrapper(config);
}

Engine::~Engine() {
    delete _contextWrapper;
}

void Engine::run() {
    _contextWrapper->run();
}
