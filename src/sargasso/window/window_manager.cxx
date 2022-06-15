
#include "sargasso/window/window_manager.h"

#include "sargasso/common/log.h"
#include "sargasso/graphics/graphics.h"
#include "sargasso/window/window_config.h"
#include "sargasso/window/window_manager.h"

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <sml/color.h>

namespace sargasso {
namespace window {

using sml::Color;

static const common::Log logger("GLFW WindowManager");

static void initGLFW();
static GLFWwindow* initWindow(WindowConfig config, int majorVersion, int minorVersion);
static void initGraphics(GLFWwindow* window, graphics::IGraphicsManager& graphics);
static void errorCallback(int error_code, const char* error_description);
static void keyActionCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void WindowManager::init() {
    initGLFW();

    _window = initWindow(_config, _graphics.getVersionMajor(), _graphics.getVersionMinor());

    initGraphics(_window, _graphics);

    glfwSetWindowUserPointer(_window, this);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(_window, keyActionCallback);

    logger.info("Graphics API: %s | %s", _graphics.getVersionString(), glfwGetVersionString());
}

void WindowManager::terminate() {
    logger.info("Closing window and terminating GLFW...");

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void WindowManager::run() {
    int width, height;
    while (!glfwWindowShouldClose(_window)) {
        // Get inputs
        glfwPollEvents();

        // Clear screen
        glfwGetFramebufferSize(_window, &width, &height);

        _graphics.setViewport(0, 0, width, height);
        _graphics.setClearColor(Color::invisible());
        _graphics.clear();

        // Swap frame buffer
        glfwSwapBuffers(_window);
    }
    logger.info("Loop ended");
}

void WindowManager::keyActionHandler(int key, int action) const {
    std::string action_name;

    if (action == GLFW_PRESS) {
        action_name = "pressed";
    } else if (action == GLFW_RELEASE) {
        action_name = "released";
    }

    if (key == GLFW_KEY_F8 && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
    }

    logger.debug("Key %s %s", glfwGetKeyName(key, glfwGetKeyScancode(key)), action_name.c_str());
}

// Helper private functions

static void initGLFW() {
    logger.debug("Initializing GLFW...");
    if (!glfwInit()) {
        logger.error("GLFW initialization failed!");
        std::exit(EXIT_FAILURE);
    }
    logger.debug("GLFW initialized!");
}

static GLFWwindow* initWindow(WindowConfig config, int majorVersion, int minorVersion) {
    logger.debug("Setting up GLFW window config...");

    // Setup window config hints
    glfwWindowHint(GLFW_SAMPLES, config.msaa);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);

    // Create window
    logger.debug("Creating GLFW window...");

    GLFWwindow* window = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);
    if (!window) {
        logger.error("Window creation failed! Terminating application...");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    logger.debug("Window creation was successful!");
    return window;
}

static void initGraphics(GLFWwindow* window, graphics::IGraphicsManager& graphics) {
    glfwMakeContextCurrent(window);

    if (!graphics.initialize((void*) glfwGetProcAddress)) {
        logger.error("Graphics initialization failed! Terminating application...");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    logger.debug("Graphics initialized!");
}

static void errorCallback(int error_code, const char* error_description) {
    logger.error("Error #%d: %s", error_code, error_description);
}

static void keyActionCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    WindowManager& contextWrapper = *static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
    contextWrapper.keyActionHandler(key, action);
}

}  // namespace window
}  // namespace sargasso