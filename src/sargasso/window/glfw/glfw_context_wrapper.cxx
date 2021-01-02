
#include "sargasso/window/glfw/glfw_context_wrapper.h"

#include "sargasso/common/log.h"
#include "sargasso/window/icontext_wrapper.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <cstdlib>

using sargasso::common::Log;
using sargasso::window::WindowConfig;
using sargasso::window::glfw::GLFWContextWrapper;

static Log logger = Log("GLFWContextWrapper");

static void init_glfw();
static GLFWwindow* init_window(WindowConfig config);
static void init_gl_context(GLFWwindow* window);
static void error_callback(int error_code, const char* error_description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

GLFWContextWrapper::GLFWContextWrapper(WindowConfig config) {
    init_glfw();

    _window = init_window(config);

    init_gl_context(_window);

    glfwSetWindowUserPointer(_window, this);
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(_window, key_callback);

    logger.info("Graphics API: %s | %s", glGetString(GL_VERSION), glfwGetVersionString());
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
        glViewport(0, 0, width, height);
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Swap frame buffer
        glfwSwapBuffers(_window);
    }
    logger.info("Loop ended");
}

void GLFWContextWrapper::key_action_handler(int key, int action) const {
    std::string action_name = "happened???";

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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
    GLFWContextWrapper& contextWrapper =
        *static_cast<GLFWContextWrapper*>(glfwGetWindowUserPointer(window));
    contextWrapper.key_action_handler(key, action);
}
