
#include "sargasso/window/glfw/glfw_context_wrapper.h"

#include "sargasso/common/log.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <cstdlib>

using sargasso::common::Log;
using sargasso::window::glfw::GLFWContextWrapper;

static Log logger = Log("GLFWContextWrapper");

static void init_glfw();
static GLFWWindow* init_window();
static void init_gl_context(GLFWwindow* window);
static void error_callback(int error_code, const char* error_description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

GLFWContextWrapper::GLFWContextWrapper(WindowConfig config) {
    init_glfw();

    _window = init_window();

    init_gl_context(_window);

    glfwSetWindowPosCallback(this);
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(_window, NULL);

    logger.info("Graphics API: %s | %s", glGetString(GL_VERSION), glfwGetVersionString());
}

GLFWContextWrapper::~GLFWContextWrapper() {
    logger.info("Closing window and terminating GLFW...");

    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool GLFWContextWrapper::should_close() const {
    return glfwWindowShouldClose(_window);
}

void GLFWContextWrapper::key_callback(int key, int action) const {
    std::string action_name = "happened???";

    if (action == GLFW_PRESS) {
        action_name = "pressed";
    } else if (action == GLFW_RELEASE) {
        action_name = "released";
    }

    logger.debug("Key %d %s", key, action_name);
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

static GLFWWindow* init_window() {
    logger.debug("Setting up GLFW window config...");

    // Setup window config hints
    glfwWindowHint(GLFW_SAMPLES, config.msaa);
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif

    // Create window
    logger.debug("Creating GLFW window...");
    GLFW* window = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);
    if (!window) {
        logger.error("Window creation failed! Terminating application...");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    logger.debug("Window creation was successful!");
    return window
}

static void init_gl_context(GLFWwindow* window) {
    logger.debug("Initializing OpenGL context...");

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        logger.error("OpenGL context initializing failed! Terminating application...");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    logger.debug("Configuring context flags...");
    glfwSwapInterval(1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_ARRAY);

    logger.debug("OpenGL context initialized!");
}

static void error_callback(int error_code, const char* error_description) {
    Log("GLFWContextWrapper").error("Error #%d: %s", error_code, error_description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GLFWContextWrapper contextWrapper = glfwGetWindowUserPointer(window);
    contextWrapper.key_callback(key, action);
}
