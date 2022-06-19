#include "sargasso/graphics/opengl.h"

#include "sargasso/common/log.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <sml/color.h>

namespace sargasso {
namespace graphics {

const static common::Log logger("GraphicsManager<OpenGL>");

/* ==================
 * | Initialization |
 * ==================
 * */

template <>
const EGraphicsBackend GraphicsManager<OpenGL>::BACKEND_TYPE = EGraphicsBackend::kOpenGL;
template <>
const char* GraphicsManager<OpenGL>::BACKEND_NAME = "OpenGL";
template <>
const uint32_t GraphicsManager<OpenGL>::BACKEND_VERSION_MAJOR = 4;
template <>
const uint32_t GraphicsManager<OpenGL>::BACKEND_VERSION_MINOR = 3;

template <>
bool GraphicsManager<OpenGL>::initialize() {
    logger.debug("Initializing OpenGL context...");

    if (gl3wInit()) {
        logger.error("GL3W init failed.");
        throw;
    }

    if (!gl3wIsSupported(GraphicsManager<OpenGL>::BACKEND_VERSION_MAJOR,
                         GraphicsManager<OpenGL>::BACKEND_VERSION_MINOR)) {
        logger.error("GL3W incompatible with OpenGL %.%",
                     GraphicsManager<OpenGL>::BACKEND_VERSION_MAJOR,
                     GraphicsManager<OpenGL>::BACKEND_VERSION_MINOR);
        throw;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    logger.debug("OpenGL context initialized!");
    return true;
}

/* ========================
 * | Imperative rendering |
 * ======================== */

template <>
void GraphicsManager<OpenGL>::present() {
    GLFWwindow* windowPointer = glfwGetCurrentContext();
    glfwSwapBuffers((GLFWwindow*) windowPointer);
}

template <>
void GraphicsManager<OpenGL>::setViewport(int x, int y, uint32_t width, uint32_t height) {
    glViewport(x, y, width, height);
}

template <>
void GraphicsManager<OpenGL>::setClearColor(sml::Color color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

template <>
void GraphicsManager<OpenGL>::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/* ====================
 * | Meta information |
 * ==================== */

}  // namespace graphics
}  // namespace sargasso
