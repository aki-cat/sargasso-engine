
#include "sargasso/engine.h"

#include "sargasso/config.h"
#include "sargasso/graphics/opengl/opengl_graphics.h"
#include "sargasso/window/glfw/glfw_context_wrapper.h"

using sargasso::Engine;
using sargasso::graphics::opengl::OpenGLGraphics;
using sargasso::window::WindowConfig;
using sargasso::window::glfw::GLFWContextWrapper;

Engine::Engine() {
    WindowConfig config;

    _graphics = new OpenGLGraphics();
    _contextWrapper = new GLFWContextWrapper(config, *_graphics);
}

Engine::~Engine() {
    delete _contextWrapper;
    delete _graphics;
}

void Engine::run() {
    _contextWrapper->run();
}
