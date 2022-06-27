
#include "sargasso/engine.h"

#include "sargasso/common/log.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <random>

namespace sargasso {

static constexpr const int GL_VERSION_MAJOR = 3;
static constexpr const int GL_VERSION_MINOR = 3;

static const common::Log logger("SargassoEngine");

// constructor
Engine::Engine(const ProjectConfig& projectConfig, const char* argv0)
    : _projectConfig(projectConfig), _fileSystem(projectConfig, argv0) {
    if (!glfwInit()) {
        throw std::runtime_error("Unable to initialize GLFW.");
    }
    glfwWindowHint(GLFW_SAMPLES, _projectConfig.msaa);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);

    GLFWwindow* window = glfwCreateWindow(_projectConfig.windowWidth, _projectConfig.windowHeight,
                                          _projectConfig.projectName, NULL, NULL);

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

void Engine::update(const double) {}

void Engine::draw() {}

// private methods

void Engine::pollEvents() {
    glfwPollEvents();
}

void Engine::swapBuffer() {
    glfwSwapBuffers(glfwGetCurrentContext());
}

void Engine::resetViewport() {
    _graphics.setDefaultViewport();
}

void Engine::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::init() {
    {
        auto time = std::chrono::steady_clock::now().time_since_epoch().count();
        std::string timeString = std::to_string(time);
        logger.info("seed: %s", timeString.c_str());
        std::reverse(timeString.rbegin(), timeString.rend());
        logger.info("Rseed: %s", timeString.substr(0, 8).c_str());
        long seed = std::atoi(timeString.c_str());
        std::srand(seed);
    }

    glfwSwapInterval(1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetErrorCallback(Engine::onError);
    glfwSetKeyCallback(window, Engine::onKeyAction);
    glfwSetFramebufferSizeCallback(window, Engine::onWindowResize);

    const sml::Color bgColor = sml::Color(.1f, .1f, .1f, 1.f);
    glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

    logger.info("Graphics API: %s | %s", glGetString(GL_VERSION), glfwGetVersionString());

    const uint width = _projectConfig.windowWidth;
    const uint height = _projectConfig.windowHeight;
    const uint ppu = _projectConfig.ppu;
    _graphics.initShader();
    _graphics.newViewport(width, height, ppu);
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

void Engine::onKeyPressed(int) {}

void Engine::onKeyReleased(int key) {
    if (key == GLFW_KEY_F8) {
        requestQuit();
    }
}

// static callbacks

void Engine::onError(int errorCode, const char* errorMessage) {
    common::Log("GLFW").error("Code 0x%X: %s", errorCode, errorMessage);
}

void Engine::onKeyAction(GLFWwindow* window, int key, int, int action, int) {
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
    instance->_graphics.setWidth(width);
    instance->_graphics.setHeight(height);
}

}  // namespace sargasso
