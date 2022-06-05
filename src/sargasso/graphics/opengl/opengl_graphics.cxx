#include "sargasso/graphics/opengl/opengl_graphics.h"

#include "sargasso/common/log.h"

#include <GL/gl3w.h>

#include <cstdint>
#include <sml/color.h>

using sargasso::common::Log;
using sargasso::graphics::opengl::OpenGLGraphics;
using sml::Color;

const static Log logger = Log("OpenGLGraphics");

bool OpenGLGraphics::initialize(void* proc_address) {
    logger.debug("Initializing OpenGL context...");

    if (gl3wInit()) {
        logger.error("GL3W init failed.");
        throw;
    }

    if (!gl3wIsSupported(4, 3)) {
        logger.error("GL3W incompatible with OpenGL %.%", 4, 3);
        throw;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_ARRAY);

    logger.debug("OpenGL context initialized!");
    return true;
}

void OpenGLGraphics::set_viewport(int x, int y, uint32_t width, uint32_t height) {
    glViewport(x, y, width, height);
}

void OpenGLGraphics::set_clear_color(Color color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLGraphics::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

std::string OpenGLGraphics::get_version() const {
    std::string version_string = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    return version_string;
}
