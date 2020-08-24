#include "front_end/front_end_system.h"
#include "front_end/modules/events.h"
#include "front_end/modules/graphics.h"
#include "front_end/modules/time.h"
#include "front_end/utility/shader_loader.h"
#include "geometry/mesh_generator.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace SargassoEngine::FrontEnd;
using namespace SargassoEngine::FrontEnd::Modules;
using namespace SargassoEngine::FrontEnd::Utility;
using namespace SargassoEngine::Geometry;

static GLuint vao_id;
static GLuint vertex_buffer;

void render_triangle(const GLuint vertex_buffer, const int vertex_buffer_size) {
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(
        0,  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        POINTS_PER_VERTEX,  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // Draw the triangle !

    // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_size);
    glDisableVertexAttribArray(0);
}

int main(int argc, char const* argv[]) {
    std::cout << "Hello world" << std::endl;

    glewExperimental = GL_TRUE;

    FrontEndSystem front_end = FrontEndSystem();
    if (!front_end.is_initialized()) {
        return -1;
    }

    std::cout << "Creating vertex array object..." << std::endl;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    const MeshRaw square_mesh = MeshGenerator::generate_square();

    std::cout << "--" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "( ";
        for (int j = 0; j < 3; j++) {
            std::cout << square_mesh.points[i * 3 + j] << " ";
        }
        std::cout << ")" << std::endl;
    }
    std::cout << "--" << std::endl;

    std::cout << "Creating vertex buffer..." << std::endl;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)square_mesh.point_count * (GLsizeiptr)sizeof(GLfloat),
                 square_mesh.points, GL_STATIC_DRAW);

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
        render_triangle(vertex_buffer, square_mesh.point_count);
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
