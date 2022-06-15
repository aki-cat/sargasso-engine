#include "sargasso/graphics/opengl.h"

#include "sargasso/common/log.h"

#include <GL/gl3w.h>
#include <cstdint>
#include <sml/color.h>

namespace sargasso {
namespace graphics {

using sml::Color;

const static common::Log logger("OpenGLGraphics");

const char* OpenGLGraphics::NAME = "OpenGL";

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

void OpenGLGraphics::setViewport(int x, int y, uint32_t width, uint32_t height) {
    glViewport(x, y, width, height);
}

void OpenGLGraphics::setClearColor(Color color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLGraphics::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

const char* OpenGLGraphics::getName() const {
    return NAME;
}

const char* OpenGLGraphics::getVersionString() const {
    return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

const int OpenGLGraphics::getVersionMajor() const {
#ifdef __APPLE__
    return 2;
#else
    return 4;
#endif
}

const int OpenGLGraphics::getVersionMinor() const {
#ifdef __APPLE__
    return 1;
#else
    return 3;
#endif
}

}  // namespace graphics
}  // namespace sargasso
