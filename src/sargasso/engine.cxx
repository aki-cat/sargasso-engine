
#include "sargasso/engine.h"

#include "sargasso/common/log.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <cstdlib>
#include <exception>

namespace sargasso {

static constexpr const int GL_VERSION_MAJOR = 3;
static constexpr const int GL_VERSION_MINOR = 3;

static const common::Log logger("SargassoEngine");

// constructor
Engine::Engine(const ProjectConfig& projectConfig)
    : _projectConfig(projectConfig),
      _windowWidth(projectConfig.windowWidth),
      _windowHeight(projectConfig.windowHeight) {
    if (!glfwInit()) {
        throw std::runtime_error("Unable to initialize GLFW.");
    }
    glfwWindowHint(GLFW_SAMPLES, _projectConfig.msaa);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);

    GLFWwindow* window =
        glfwCreateWindow(_windowWidth, _windowHeight, _projectConfig.projectName, NULL, NULL);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Unable to initialize Window.");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    if (gl3wInit()) {
        throw std::runtime_error("Unable to initialize OpenGL functions.");
    }

    if (!gl3wIsSupported(GL_VERSION_MAJOR, GL_VERSION_MINOR)) {
        logger.error("GL3W incompatible with OpenGL %.%", GL_VERSION_MAJOR, GL_VERSION_MINOR);
        throw;
    }
}

// public methods

void Engine::run() {
    init();
    load();

    const double toSeconds =
        1.0 * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;

    double dt = 0.0;
    while (!quitRequested()) {
        auto frameStart = std::chrono::steady_clock::now();

        resetViewport();
        clear();
        update(dt);
        draw();
        swapBuffer();
        pollEvents();

        auto frameDuration = std::chrono::steady_clock::now() - frameStart;
        dt = 1.0 * frameDuration.count() * toSeconds;
    }

    quit();
}

// virtual methods

void Engine::load() {}

void Engine::update(const double dt) {}

void Engine::draw() {}

// private methods

void Engine::pollEvents() {
    glfwPollEvents();
}

void Engine::swapBuffer() {
    glfwSwapBuffers(glfwGetCurrentContext());
}

void Engine::resetViewport() {
    glViewport(0, 0, _windowWidth, _windowHeight);
}

void Engine::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::init() {
    glfwSwapInterval(1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetErrorCallback(Engine::onError);
    glfwSetKeyCallback(window, Engine::onKeyAction);
    glfwSetFramebufferSizeCallback(window, Engine::onWindowResize);

    glClearColor(0.4f, 0.3f, 0.2f, 1.0f);

    _graphics.initShader();
}

void Engine::quit() {
    glfwDestroyWindow(glfwGetCurrentContext());
    glfwTerminate();
}

bool Engine::quitRequested() {
    GLFWwindow* window = glfwGetCurrentContext();
    return glfwWindowShouldClose(window);
}

void Engine::requestQuit() {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetWindowShouldClose(window, true);
}

// instance callbacks

void Engine::onKeyPressed(int key) {}

void Engine::onKeyReleased(int key) {
    if (key == GLFW_KEY_F8) {
        requestQuit();
    }
}

// static callbacks

void Engine::onError(int errorCode, const char* errorMessage) {
    common::Log("GLFW").error("Code 0x%X: %s", errorCode, errorMessage);
}

void Engine::onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Engine* instance = (Engine*) glfwGetWindowUserPointer(window);
    if (action == GLFW_PRESS) {
        instance->onKeyPressed(key);
    }
    if (action == GLFW_RELEASE) {
        instance->onKeyReleased(key);
    }
}

void Engine::onWindowResize(GLFWwindow* window, int width, int height) {
    Engine* instance = (Engine*) glfwGetWindowUserPointer(window);
    instance->_windowWidth = width;
    instance->_windowHeight = height;
}

}  // namespace sargasso
