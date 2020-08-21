#include "front_end/front_end_system.h"
#include "front_end/modules/events.h"
#include "front_end/modules/graphics.h"
#include "front_end/modules/time.h"
#include "front_end/utility/shader_loader.h"
#include "geometry/mesh_generator.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <glm/vec4.hpp>
#include <iostream>
#include <stdio.h>

using SargassoEngine::FrontEnd::FrontEndSystem;
using SargassoEngine::FrontEnd::Modules::Events;
using SargassoEngine::FrontEnd::Modules::Graphics;
using SargassoEngine::FrontEnd::Modules::Time;
using SargassoEngine::FrontEnd::Utility::ShaderLoader;
using SargassoEngine::Geometry::MeshGenerator;
using SargassoEngine::Geometry::SquareMesh;

static GLuint vao_id;
static GLuint vertex_buffer;

const static int VERTEX_DATA_SIZE = 4;

void render_triangle(const GLuint vertex_buffer, const int vertex_buffer_size) {
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(
        0,  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        VERTEX_DATA_SIZE,  // size
        GL_FLOAT,          // type
        GL_FALSE,          // normalized?
        0,                 // stride
        (void*)0           // array buffer offset
    );

    // Draw the triangle !

    // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_size / VERTEX_DATA_SIZE);
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

    SquareMesh square_mesh = MeshGenerator::generate_square();

    std::cout << "Creating vertex buffer..." << std::endl;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_mesh.vertex_points), square_mesh.vertex_points,
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
        render_triangle(vertex_buffer, sizeof(square_mesh.vertex_points) / sizeof(GLfloat));
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
