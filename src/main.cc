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

void run(const FrontEndSystem& front_end, const GLuint buffer_id, const uint32_t buffer_size);
void render_buffer(const GLuint vertex_buffer, const uint32_t vertex_buffer_size);

GLuint generate_vertex_array();
GLuint generate_buffer(const MeshRaw& mesh);

int main(int argc, char const* argv[]) {
    std::cout << "Hello world" << std::endl;

    const MeshRaw& sample_mesh = MeshGenerator::generate_square();
    sample_mesh.print();

    FrontEndSystem front_end = FrontEndSystem();
    if (!front_end.is_initialized()) {
        return -1;
    }

    // GLuint vao_id =
    generate_vertex_array();
    GLuint vertex_buffer = generate_buffer(sample_mesh);

    std::cout << "Init successful!" << std::endl;

    front_end.start();
    run(front_end, vertex_buffer, sample_mesh.point_count);
    front_end.stop();

    std::cout << "Done!" << std::endl;

    return 0;
}

void run(const FrontEndSystem& front_end, const GLuint buffer_id, const uint32_t buffer_size) {
    Graphics& graphics = front_end.get_module<Graphics>();
    Events& events = front_end.get_module<Events>();
    Time& time = front_end.get_module<Time>();

    std::cout << "Starting main loop..." << std::endl;
    uint64_t frame_number = 0;

    while (!graphics.should_window_close()) {
        time.start_frame();
        frame_number++;

        graphics.start_rendering_buffer();

        render_buffer(buffer_id, buffer_size);

        graphics.stop_rendering_buffer();

        events.poll_events();

        time.end_frame();
    }

    std::cout << "Main loop stopped!" << std::endl;
    std::cout << "Ran " << frame_number << " frames!" << std::endl;
}

void render_buffer(const GLuint vertex_buffer, const uint32_t vertex_buffer_size) {
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
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertex_buffer_size));
    glDisableVertexAttribArray(0);
}

GLuint generate_vertex_array() {
    std::cout << "Creating vertex array object..." << std::endl;
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);
    return vao_id;
}

GLuint generate_buffer(const MeshRaw& mesh) {
    std::cout << "Creating vertex buffer..." << std::endl;
    GLuint buffer_id;

    GLsizeiptr byte_count = static_cast<GLsizeiptr>(mesh.point_count * (uint32_t)sizeof(GLfloat));

    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, byte_count, mesh.points, GL_STATIC_DRAW);

    return buffer_id;
}
