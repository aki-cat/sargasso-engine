
#include "sargasso/common/log.h"
#include "sargasso/graphics/graphics.h"
#include "sargasso/graphics/opengl.h"
#include "sargasso/window/window_config.h"
#include "sargasso/window/window_manager.h"

#include <GLFW/glfw3.h>
#include <cstdint>
#include <cstdlib>
#include <sml/color.h>

namespace sargasso {
namespace window {

using graphics::OpenGL;

static const common::Log logger("WindowManager<OpenGL>");

/* ===========================================
 * | Forward declaration of helper functions |
 * =========================================== */

static void initGLFW();
static GLFWwindow& initWindow(WindowConfig config, uint32_t majorVersion, uint32_t minorVersion);
static void initGraphics(GLFWwindow& window, graphics::GraphicsManager<OpenGL>& graphics);
static void initCallbacks(WindowManager<OpenGL>& manager, GLFWwindow& window);
static void errorCallback(int32_t errorCode, const char* errorDescription);
static void keyActionCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action,
                              int32_t mods);

/* ======================================
 * | WindowManager class implementation |
 * ====================================== */

template <>
void WindowManager<OpenGL>::init() {
    initGLFW();

    _window = &initWindow(_config, graphics::GraphicsManager<OpenGL>::BACKEND_VERSION_MAJOR,
                          graphics::GraphicsManager<OpenGL>::BACKEND_VERSION_MINOR);

    initGraphics(*_window, _graphics);
    initCallbacks(*this, *_window);

    logger.info("Graphics API: %s | %s", _graphics.getVersionString().c_str(),
                glfwGetVersionString());
}

template <>
void WindowManager<OpenGL>::terminate() {
    logger.info("Closing window and terminating GLFW...");

    glfwDestroyWindow(_window);
    glfwTerminate();
}

template <>
void WindowManager<OpenGL>::run() {
    int width, height;
    while (!glfwWindowShouldClose(_window)) {
        // Get inputs
        glfwPollEvents();

        // Clear screen
        glfwGetFramebufferSize(_window, &width, &height);

        _graphics.setViewport(0, 0, width, height);
        _graphics.setClearColor(sml::Color::invisible());
        _graphics.clear();
        _graphics.present();
    }
    logger.info("Loop ended");
}

template <>
void WindowManager<OpenGL>::keyActionHandler(int key, int action) const {
    std::string actionName;

    if (action == GLFW_PRESS) {
        actionName = "pressed";
    } else if (action == GLFW_RELEASE) {
        actionName = "released";
    }

    if (key == GLFW_KEY_F8 && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
    }

    logger.debug("Key %s %s", glfwGetKeyName(key, glfwGetKeyScancode(key)), actionName.c_str());
}

/* ===================================
 * | Helper functions implementation |
 * =================================== */

static void initGLFW() {
    logger.debug("Initializing GLFW...");
    if (!glfwInit()) {
        logger.error("GLFW initialization failed!");
        std::exit(EXIT_FAILURE);
    }
    logger.debug("GLFW initialized!");
}

static GLFWwindow& initWindow(WindowConfig config, uint32_t majorVersion, uint32_t minorVersion) {
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
    return *window;
}

static void initGraphics(GLFWwindow& window, graphics::GraphicsManager<OpenGL>& graphics) {
    glfwMakeContextCurrent(&window);

    if (!graphics.initialize()) {
        logger.error("Graphics initialization failed! Terminating application...");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    logger.debug("Graphics initialized!");
}

static void initCallbacks(WindowManager<OpenGL>& manager, GLFWwindow& window) {
    glfwSetWindowUserPointer(&window, &manager);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(&window, keyActionCallback);
}

static void errorCallback(int errorCode, const char* errorDescription) {
    logger.error("Error #%d: %s", errorCode, errorDescription);
}

static void keyActionCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    WindowManager<OpenGL>& windowManager =
        *static_cast<WindowManager<OpenGL>*>(glfwGetWindowUserPointer(window));
    windowManager.keyActionHandler(key, action);
}

}  // namespace window
}  // namespace sargasso
