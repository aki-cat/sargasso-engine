
#include "sargasso/engine.h"

#include "sargasso/common/log.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <cstdlib>
#include <exception>

namespace sargasso {

static constexpr const int GL_VERSION_MAJOR = 4;
static constexpr const int GL_VERSION_MINOR = 5;

static const common::Log logger("SargassoEngine");

Engine::Engine(const ProjectConfig& projectConfig) : _projectConfig(projectConfig) {
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

    if (gl3wInit()) {
        throw std::runtime_error("Unable to initialize OpenGL functions.");
    }

    if (!gl3wIsSupported(GL_VERSION_MAJOR, GL_VERSION_MINOR)) {
        logger.error("GL3W incompatible with OpenGL %.%", GL_VERSION_MAJOR, GL_VERSION_MINOR);
        throw;
    }
}

void Engine::run() {
    init();
    load();

    const double toSeconds =
        1.0 * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;

    double dt = 0.0;
    while (!quitRequested()) {
        auto frameStart = std::chrono::steady_clock::now();

        pollEvents();
        update(dt);
        draw();
        swapBuffer();

        auto frameDuration = std::chrono::steady_clock::now() - frameStart;
        dt = 1.0 * frameDuration.count() * toSeconds;
    }

    quit();
}

void Engine::load() {}

void Engine::update(const double dt) {}

void Engine::draw() {}

void Engine::swapBuffer() {
    glfwSwapBuffers(glfwGetCurrentContext());
}

void Engine::pollEvents() {
    glfwPollEvents();
}

void Engine::init() {
    glfwSwapInterval(1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetErrorCallback(Engine::error);
    glfwSetKeyCallback(window, Engine::keyAction);
}

void Engine::quit() {
    glfwDestroyWindow(glfwGetCurrentContext());
    glfwTerminate();
}

bool Engine::quitRequested() const {
    GLFWwindow* window = glfwGetCurrentContext();
    return glfwWindowShouldClose(window);
}

void Engine::error(int errorCode, const char* errorMessage) {
    common::Log("GLFW").error("Code 0x%X: %s", errorCode, errorMessage);
}

void Engine::keyAction(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F8 && action == GLFW_RELEASE) {
        glfwSetWindowShouldClose(window, true);
    }
}

}  // namespace sargasso
