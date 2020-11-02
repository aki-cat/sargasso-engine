#include "front_end/modules/graphics.h"

#include "common/log.h"
#include "engine.h"
#include "front_end/utility/shader_loader.h"
#include "geometry/mesh_generator.h"

#include <GL/glew.h>

using namespace SargassoEngine::FrontEnd::Modules;
using namespace SargassoEngine::FrontEnd::Utility;
using namespace SargassoEngine::Geometry;
using namespace SargassoEngine::Common;

Graphics::Graphics() {
    log("Initializing window...");

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    _width = 960;
    _height = 540;

    _window = glfwCreateWindow(_width, _height, SargassoEngine::ENGINE_NAME, NULL, NULL);
    log("Window created!");

    // Initialize window
    log("Setting GL context..");
    glfwMakeContextCurrent(_window);
    glfwFocusWindow(_window);

    log("Setting swap interval...");
    glfwSwapInterval(1);

    log("Initializing glew...");
    glewInit();

    log("Loading shaders...");
    try {
        _program_id = ShaderLoader::load_default_shaders();
    } catch (const std::string& exception) {
        logf_error("Failed to load shaders:\n\t%", exception);
    }

    logf("window size = (%, %)", _width, _height);
}

Graphics::~Graphics() {
    if (_window) {
        glfwDestroyWindow(_window);
    }
}

void Graphics::start_rendering_buffer() {
    // Called before rendering a frame
    glfwGetFramebufferSize(_window, &_width, &_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _set_shader_camera();
    glUseProgram(_program_id);
}

void Graphics::stop_rendering_buffer() {
    // Called after rendering a frame
    glfwSwapBuffers(_window);
}

void Graphics::_set_shader_camera() {
    const float fov = static_cast<float>(M_PI_2);
    const float aspect = static_cast<float>(_width) / static_cast<float>(_height);

    // Mat4 projection = Mat4::perspective_projection(fov, aspect, 0.01f, 1000.0f);
    Mat4 projection = Mat4::identity();
    Mat4 view = Mat4::look_at(Vec3(2, 3, -1), Vec3::zero());

    logf("projection\n%", projection.to_string());
    logf("view\n%", view.to_string());

    GLint projection_matrix_id = glGetUniformLocation(_program_id, "projection");
    GLint view_matrix_id = glGetUniformLocation(_program_id, "view");
    glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, &projection[0]);
    glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, &view[0]);
}
