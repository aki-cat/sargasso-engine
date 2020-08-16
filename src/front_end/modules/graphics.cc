#include "front_end/modules/graphics.h"

#include "engine.h"
#include "front_end/utility/shader_loader.h"

#include <GL/glew.h>
#include <exception>
#include <iostream>

using SargassoEngine::FrontEnd::Modules::Graphics;
using SargassoEngine::FrontEnd::Utility::ShaderLoader;

Graphics::Graphics() {
    std::cout << "Initializing window..." << std::endl;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    _window = glfwCreateWindow(960, 540, SargassoEngine::ENGINE_NAME, NULL, NULL);
    std::cout << "Window created!" << std::endl;

    // Initialize window
    std::cout << "Setting GL context.." << std::endl;
    glfwMakeContextCurrent(_window);
    glfwFocusWindow(_window);

    std::cout << "Setting swap interval..." << std::endl;
    glfwSwapInterval(1);

    std::cout << "Initializing glew..." << std::endl;
    glewInit();

    std::cout << "Loading shaders..." << std::endl;
    _program_id = ShaderLoader::load_defult_shaders();
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
    glUseProgram(_program_id);
}

void Graphics::stop_rendering_buffer() {
    // Called after rendering a frame
    glfwSwapBuffers(_window);
}
