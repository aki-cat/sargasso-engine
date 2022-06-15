
#include "sargasso/window/glfw/glfw_context_wrapper.h"

#include "sargasso/common/log.h"
#include "sargasso/config/window_config.h"
#include "sargasso/graphics/graphics.h"
#include "sargasso/window/window_manager.h"

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <sml/color.h>

using sargasso::common::Log;
using sargasso::config::WindowConfig;
using sargasso::graphics::IGraphicsManager;
using sargasso::window::glfw::GLFWContextWrapper;
using sml::Color;

static Log logger = Log("GLFWContextWrapper");

static void init_glfw();
static GLFWwindow* init_window(WindowConfig config);
static void init_graphics(GLFWwindow* window, IGraphicsManager& graphics);
static void error_callback(int error_code, const char* error_description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

GLFWContextWrapper::GLFWContextWrapper(const WindowConfig& config, IGraphicsManager& graphics)
    : IWindowManager(config, graphics) {
    init_glfw();

    _window = init_window(_config);

    init_graphics(_window, _graphics);

    glfwSetWindowUserPointer(_window, this);
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(_window, key_callback);

    logger.info("Graphics API: %s | %s", _graphics.getVersion(), glfwGetVersionString());
}

GLFWContextWrapper::~GLFWContextWrapper() {
    logger.info("Closing window and terminating GLFW...");

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void GLFWContextWrapper::run() {
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

void GLFWContextWrapper::keyActionHandler(int key, int action) const {
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

static void init_glfw() {
    logger.debug("Initializing GLFW...");
    if (!glfwInit()) {
        logger.error("GLFW initialization failed!");
        std::exit(EXIT_FAILURE);
    }
    logger.debug("GLFW initialized!");
}

static GLFWwindow* init_window(WindowConfig config) {
    logger.debug("Setting up GLFW window config...");

    // Setup window config hints
    glfwWindowHint(GLFW_SAMPLES, config.msaa);
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif

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

static void init_graphics(GLFWwindow* window, IGraphicsManager& graphics) {
    glfwMakeContextCurrent(window);

    if (!graphics.initialize((void*) glfwGetProcAddress)) {
        logger.error("Graphics initialization failed! Terminating application...");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    logger.debug("Graphics initialized!");
}

static void error_callback(int error_code, const char* error_description) {
    Log("GLFWContextWrapper").error("Error #%d: %s", error_code, error_description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GLFWContextWrapper& contextWrapper =
        *static_cast<GLFWContextWrapper*>(glfwGetWindowUserPointer(window));
    contextWrapper.keyActionHandler(key, action);
}
