// Include this before everything
#include <GL/glew.h>
// Include this before everything

#include "front_end/front_end_system.h"
#include "front_end/modules/events.h"
#include "front_end/modules/graphics.h"
#include "front_end/modules/time.h"
#include "front_end/utility/shader_loader.h"

#include <GLFW/glfw3.h>
#include <iostream>

using SargassoEngine::FrontEnd::FrontEndSystem;
using SargassoEngine::FrontEnd::Modules::Events;
using SargassoEngine::FrontEnd::Modules::Graphics;
using SargassoEngine::FrontEnd::Modules::Time;
using SargassoEngine::FrontEnd::Utility::ShaderLoader;

static const GLfloat g_vertex_buffer_data[] = {
    // front face
    +0.0f,
    +0.0f,
    +0.0f,
    +1.0f,

    +0.5f,
    +0.0f,
    +0.0f,
    +1.0f,

    +0.5f,
    +0.5f,
    +0.0f,
    +1.0f,

    +0.5f,
    +0.5f,
    +0.0f,
    +1.0f,

    +0.0f,
    +0.5f,
    +0.0f,
    +1.0f,

    +0.0f,
    +0.0f,
    +0.0f,
    +1.0f,

    // left face
    +0.0f,
    +0.0f,
    -0.5f,
    +1.0f,

    +0.0f,
    +0.0f,
    +0.0f,
    +1.0f,

    +0.0f,
    +0.5f,
    +0.0f,
    +1.0f,

    +0.0f,
    +0.5f,
    +0.0f,
    +1.0f,

    +0.0f,
    -0.5f,
    +0.5f,
    +1.0f,

    +0.0f,
    +0.0f,
    -0.5f,
    +1.0f,
};

static GLuint vao_id;
static GLuint vertex_buffer;

void render_triangle(const GLuint& vertex_buffer) {
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(
        0,  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        4,  // size
        GL_FLOAT,  // type
        GL_FALSE,  // normalized?
        0,         // stride
        (void*)0   // array buffer offset
    );

    // Draw the triangle !

    // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDrawArrays(GL_TRIANGLES, 0, sizeof(g_vertex_buffer_data));
    glDisableVertexAttribArray(0);
}

int main() {
    std::cout << "Hello world" << std::endl;

    glewExperimental = GL_TRUE;

    FrontEndSystem front_end = FrontEndSystem();
    if (!front_end.is_initialized()) {
        return -1;
    }

    std::cout << "Creating vertex array object..." << std::endl;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    std::cout << "Creating vertex buffer..." << std::endl;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data,
                 GL_STATIC_DRAW);

    std::cout << "Init successful!" << std::endl;

    uint64_t frame_number = 0;

    front_end.start();

    Graphics& graphics = front_end.get_module<Graphics>();
    Events& events = front_end.get_module<Events>();
    Time& time = front_end.get_module<Time>();

    std::cout << "Starting main loop..." << std::endl;
    while (!graphics.should_window_close()) {
        // main loop
        time.start_frame();

        frame_number++;
        graphics.start_rendering_buffer();
        render_triangle(vertex_buffer);
        graphics.stop_rendering_buffer();

        events.poll_events();

        time.end_frame();
    }
    std::cout << "Main loop stopped!" << std::endl;

    front_end.stop();

    std::cout << "Ran " << frame_number << " frames!" << std::endl;
    std::cout << "Done!" << std::endl;

    return 0;
}
