#include "sargasso/front_end/modules/graphics.h"

#include "sargasso/common/log.h"
#include "sargasso/config.h"
#include "sargasso/front_end/utility/buffer.h"
#include "sargasso/front_end/utility/shader_loader.h"
#include "sargasso/front_end/utility/shader_program.h"
#include "sargasso/front_end/utility/uniform_type.h"
#include "sargasso/geometry/vertex.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <utility>

using namespace SargassoEngine::FrontEnd::Modules;
using namespace SargassoEngine::FrontEnd::Utility;
using namespace SargassoEngine::Common;

Graphics::Graphics() : _camera() {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    _width = 960;
    _height = 540;
    _camera.make_orthogonal(_width, _height, 0.01f, 1000);
    _camera.look_at(Vec3(0, 0, -10), Vec3(0, 0, 0));
    logf("Camera @ poisition: %", _camera.get_position().to_string());

    _window = glfwCreateWindow(_width, _height, SargassoEngine::ENGINE_NAME, NULL, NULL);
    if (_window == NULL) {
        log_error("Window was not created");
    }

    // Initialize window
    glfwMakeContextCurrent(_window);

    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        log_error("Failed to initialize GLAD");
        throw;
    }

    glfwFocusWindow(_window);

    constexpr const char* default_shader_name = "default_shader";

    create_shader(default_shader_name);
    use_shader(default_shader_name);
}

Graphics::~Graphics() {
    for (std::pair<std::string, ShaderProgram*> key_pair : _shaders) {
        delete key_pair.second;
    }
    _shaders.clear();

    for (Buffer* buffer : _buffers) {
        delete buffer;
    }
    _buffers.clear();

    if (_window) {
        glfwDestroyWindow(_window);
    }
}

GLFWwindow* Graphics::get_window() const { return _window; }

int Graphics::get_width() const { return _width; }

int Graphics::get_height() const { return _height; }

bool Graphics::should_window_close() const { return glfwWindowShouldClose(_window); }

void Graphics::render_buffers() {
    // Called before rendering a frame
    glfwGetFramebufferSize(_window, &_width, &_height);

    glViewport(0, 0, _width, _height);
    glClearColor(0.1f, 0.1f, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _set_shader_camera();

    for (const Buffer* buffer : _buffers) {
        buffer->render(get_shader(_current_shader));
    }

    glfwSwapBuffers(_window);
}

void Graphics::register_buffer(const Vertex* vertices, const size_t vertex_count) {
    _buffers.push_back(new Buffer(vertices, vertex_count));
}

ShaderProgram& Graphics::get_shader(const std::string& shader_name) {
    return *_shaders.at(shader_name);
}

void Graphics::use_shader(const std::string& shader_name) {
    // No error treatment
    _current_shader = std::string(shader_name);
    get_shader(shader_name).use();
}

void Graphics::create_shader(const std::string& shader_name) {
    if (_shaders.find(shader_name) != _shaders.end()) {
        logf_error("Shader of name '%' already exists, cannot create another with same name.",
                   shader_name);
        return;
    }
    _shaders[shader_name] = new ShaderProgram();
}

void Graphics::set_camera(const Camera& camera) { _camera = camera; }

Camera Graphics::get_camera() const { return _camera; }

void Graphics::_set_shader_camera() {
    Mat4 transform = _camera.get_transform();
    ShaderProgram& shader_program = get_shader(_current_shader);
    shader_program.set_uniform(UniformType::UNIFORM_MATRIX4, "mvp", &transform, 1);
}
