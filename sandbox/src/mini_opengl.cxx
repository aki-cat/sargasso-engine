#include <GL/gl3w.h>

#define GLFW_INCLUDE_NONE

#define MINIMAL_OPENGL_VERSION_MAJOR 4
#define MINIMAL_OPENGL_VERSION_MINOR 5

#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

// math library
#include <sargasso/common/io.h>
#include <sargasso/common/log.h>
#include <sml/color.h>
#include <sml/constants.h>
#include <sml/matrix4.h>
#include <sml/vector3.h>

using sml::Color;
using sml::Mat4;
using sml::Vec3;

using sargasso::common::IO;
using sargasso::common::Log;

static const std::string vertex_shader_text =
#ifdef __APPLE__
    "#version 120\n"
#else
    "#version 330\n"
#endif
    "uniform mat4 MVP;\n"
    "attribute vec3 vPos;\n"
    "attribute vec4 vCol;\n"
    "varying vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = MVP * vec4(vPos, 1.0);\n"
    "    color = vCol;\n"
    "}\n";

static const std::string fragment_shader_text =
#ifdef __APPLE__
    "#version 120\n"
#else
    "#version 330\n"
#endif
    "varying vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = color;\n"
    "}\n";

namespace state {

static float eye_angle = 0.f;
static float eye_height = 0.f;
static float eye_zoom = 1.f;
static bool use_conical = true;

}  // namespace state

struct Vertex {
    Vec3 position;
    Color color;
};

static Vertex triangle_vertices[] = {
    {Vec3(-1.f, -1.f, 0.f), Color::white()},
    {Vec3(+1.f, -1.f, 0.f), Color::white()},
    {Vec3(-1.f, +1.f, 0.f), Color::white()},
    //
    {Vec3(-1.f, +1.f, 0.f), Color::white()},
    {Vec3(+1.f, +1.f, 0.f), Color::white()},
    {Vec3(+1.f, -1.f, 0.f), Color::white()},
};

static Vertex cube_vertices[] = {
    {Vec3(-.5f, -.5f, -.5f), Color::red()}, {Vec3(.5f, -.5f, -.5f), Color::red()},
    {Vec3(.5f, .5f, -.5f), Color::green()}, {Vec3(-.5f, .5f, -.5f), Color::green()},

    {Vec3(-.5f, -.5f, .5f), Color::blue()}, {Vec3(.5f, -.5f, .5f), Color::blue()},
    {Vec3(.5f, .5f, .5f), Color::gray()},   {Vec3(-.5f, .5f, .5f), Color::gray()}};

static const uint32_t cube_vertex_indices[] = {
    // front
    0, 1, 2, 2, 3, 0,
    // top
    5, 4, 1, 1, 0, 4,
    // right
    1, 5, 6, 6, 2, 1,
    // back
    5, 4, 7, 7, 6, 5,
    // bottom
    3, 2, 6, 6, 7, 3,
    // left
    4, 0, 3, 3, 7, 4};

static void error_callback(int error, const char* description) {
    Log("GLFW").error("Error #%d: %s", error, description);
}

void nothing() {}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (scancode | mods) {
        nothing();
    }

    if (key == GLFW_KEY_F8 && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        state::use_conical = !state::use_conical;
    }

    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        state::eye_angle =
            std::fmod(state::eye_angle + (float) sml::PI / 12.f, 2.f * (float) sml::PI);
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        state::eye_angle =
            std::fmod(state::eye_angle - (float) sml::PI / 12.f, 2.f * (float) sml::PI);
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        state::eye_height = std::min(5.f, state::eye_height + .25f);
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        state::eye_height = std::max(-5.f, state::eye_height - .25f);
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        state::eye_zoom = std::max(1.f / 16.f, state::eye_zoom / 2.f);
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        state::eye_zoom = std::min(16.f, state::eye_zoom * 2);
    }
}

constexpr const uint32_t WINDOW_WIDTH = 960, WINDOW_HEIGHT = 540;
// constexpr const float WINDOW_ASPECT = 1.f * WINDOW_WIDTH / WINDOW_HEIGHT;
// constexpr const float CAMERA_HEIGHT = 2.f;
// constexpr const float CAMERA_WIDTH = CAMERA_HEIGHT * WINDOW_ASPECT;

#define POINTER_CAST(value) reinterpret_cast<void*>(value)

GLFWwindow* create_window() {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MINIMAL_OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINIMAL_OPENGL_VERSION_MINOR);
#endif

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Minimal", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return window;
}

static void setup_context(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
    if (gl3wInit()) {
        Log("Minimal").error("GL3W init failed.");
        throw;
    }

    if (!gl3wIsSupported(MINIMAL_OPENGL_VERSION_MAJOR, MINIMAL_OPENGL_VERSION_MINOR)) {
        Log("Minimal").error("GL3W incompatible with OpenGL %.%", MINIMAL_OPENGL_VERSION_MAJOR,
                             MINIMAL_OPENGL_VERSION_MINOR);
        throw;
    }

    glfwSwapInterval(1);

    Log("Minimal").info("Graphics API: %s | %s", glGetString(GL_VERSION), glfwGetVersionString());
}

static void setup_context_flags() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_ARRAY);
}

static void setup_callbacks(GLFWwindow* window) {
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
}

static void terminate(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

#ifndef __APPLE__
static void setup_vertex_array_object() {
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);
}
#endif

static GLuint generate_vertex_array_buffer() {
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    return vertex_buffer;
}

static GLuint generate_cube_element_array_buffer() {
    GLuint ibo_buffer;
    glGenBuffers(1, &ibo_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_vertex_indices), cube_vertex_indices,
                 GL_STATIC_DRAW);
    return ibo_buffer;
}

static GLuint compile_vertex_shader() {
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char* shader_code = vertex_shader_text.c_str();
    glShaderSource(vertex_shader, 1, &shader_code, NULL);
    glCompileShader(vertex_shader);
    return vertex_shader;
}

static GLuint compile_fragment_shader() {
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* shader_code = fragment_shader_text.c_str();
    glShaderSource(fragment_shader, 1, &shader_code, NULL);
    glCompileShader(fragment_shader);
    return fragment_shader;
}

static GLuint create_and_link_shader_program(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    return shader_program;
}

static Mat4 generate_mvp_matrix() {
    double angle = std::fmod(glfwGetTime(), 2.0 * sml::PI);
    Mat4 model = Mat4::identity().rotated(Vec3(1, -1, 0), static_cast<float>(angle));

    Vec3 eye_position =
        (state::eye_zoom * Vec3(0, state::eye_height, 5)).rotated(Vec3::y_axis(), state::eye_angle);

    Mat4 view = Mat4::look_at(eye_position, Vec3(0, 0, 0), Vec3::y_axis());
    Mat4 projection;

    if (state::use_conical) {
        projection = Mat4::conical_projection(sml::PI * 0.25, 1.f * WINDOW_WIDTH / WINDOW_HEIGHT,
                                              0.001f, 1000.f);

    } else {
        const float aspect = 1.f * WINDOW_WIDTH / WINDOW_HEIGHT;
        const float unit = .5f;
        projection = Mat4::orthogonal_projection(-aspect * unit, -unit, aspect * unit, unit,
                                                 -1000.f, 1000.f);
    }

    return projection * view * model;
}

int main(void) {
    GLFWwindow* window = create_window();
    setup_context(window);
    setup_context_flags();
    setup_callbacks(window);

#ifndef __APPLE__
    setup_vertex_array_object();
#endif

    // Generate buffers
    GLuint vertex_buffer = generate_vertex_array_buffer();
    GLuint ibo_buffer = generate_cube_element_array_buffer();
    // generate_cube_element_array_buffer();

    // Compile and setup shaders
    GLuint vertex_shader = compile_vertex_shader();
    GLuint fragment_shader = compile_fragment_shader();
    GLuint shader_program = create_and_link_shader_program(vertex_shader, fragment_shader);

    GLint mvp_location;
    mvp_location = glGetUniformLocation(shader_program, "MVP");

    GLint vpos_location = glGetAttribLocation(shader_program, "vPos");
    GLint vcol_location = glGetAttribLocation(shader_program, "vCol");

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(vcol_location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          POINTER_CAST(sizeof(Vec3)));

    glEnableVertexAttribArray(vpos_location);
    glEnableVertexAttribArray(vcol_location);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Clear window

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Generate transformation matrices

        Mat4 mvp = generate_mvp_matrix();
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, reinterpret_cast<const float*>(&mvp));
        glUseProgram(shader_program);

        // Send data to shaders
        // glDrawArrays(GL_TRIANGLES, 0, 6);

        // Render element array buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_buffer);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, POINTER_CAST(0));
        glfwSwapBuffers(window);
    }

    terminate(window);
}
