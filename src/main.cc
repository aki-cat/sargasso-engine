
#include <GL/glew.h>

#include <iostream>

#include "GLFW/glfw3.h"
#include "front_end/front_end_system.h"
#include "front_end/modules/events.h"
#include "front_end/modules/graphics.h"
#include "front_end/modules/time.h"

using SargassoEngine::FrontEnd::FrontEndSystem;
using SargassoEngine::FrontEnd::Modules::Events;
using SargassoEngine::FrontEnd::Modules::Graphics;
using SargassoEngine::FrontEnd::Modules::Time;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,

    1.0f,  -1.0f, 0.0f,

    0.0f,  1.0f,  0.0f,
};

GLuint create_vertex_array_object() {
  GLuint vertex_array_id;
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);
  return vertex_array_id;
}

GLuint create_triangle_buffer() {
  // This will identify our vertex buffer
  GLuint vertex_buffer;
  // Generate 1 buffer, put the resulting identifier in vertex_buffer
  glGenBuffers(1, &vertex_buffer);
  // The following commands will talk about our 'vertex_buffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  // Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);
  return vertex_buffer;
}

void render_triangle(const GLuint &vertex_buffer) {
  // 1st attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glVertexAttribPointer(0,  // attribute 0. No particular reason for 0, but must
                            // match the layout in the shader.
                        3,  // size
                        GL_FLOAT,  // type
                        GL_FALSE,  // normalized?
                        0,         // stride
                        (void *)0  // array buffer offset
  );

  // Draw the triangle !

  // Starting from vertex 0; 3 vertices total -> 1 triangle
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
}

int main() {
  std::cout << "Hello world" << std::endl;

  FrontEndSystem front_end = FrontEndSystem();
  if (!front_end.is_initialized()) {
    return -1;
  }

  const GLuint vao = create_vertex_array_object();
  const GLuint buffer = create_triangle_buffer();

  std::cout << "Init successful!" << std::endl;

  uint64_t frame_number = 0;

  front_end.start();

  Graphics &graphics = front_end.get_module<Graphics>();
  Events &events = front_end.get_module<Events>();
  Time &time = front_end.get_module<Time>();
  while (!graphics.should_window_close()) {
    // main loop
    time.start_frame();
    std::cout << "Frame time: " << time.get_delta() << std::endl;

    frame_number++;
    graphics.render();
    render_triangle(buffer);

    events.poll_events();

    time.end_frame();
  }

  front_end.stop();

  std::cout << "Ran " << frame_number << " frames!" << std::endl;
  std::cout << "Done!" << std::endl;

  return 0;
}
