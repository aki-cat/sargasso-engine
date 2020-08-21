#ifndef SARGASSO_ENGINE_FRONT_END_GRAPHICS_H
#define SARGASSO_ENGINE_FRONT_END_GRAPHICS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace SargassoEngine {
namespace FrontEnd {
namespace Modules {

class Graphics {
   public:
    explicit Graphics();
    Graphics(const Graphics&) = delete;
    Graphics(const Graphics&&) = delete;
    ~Graphics();
    GLFWwindow* get_window() const;
    int get_width();
    int get_height();
    bool should_window_close();
    void start_rendering_buffer();
    void stop_rendering_buffer();

   private:
    GLFWwindow* _window;
    int _width;
    int _height;
    GLuint _program_id;
};

inline GLFWwindow* Graphics::get_window() const { return _window; }

inline int Graphics::get_width() { return _width; }

inline int Graphics::get_height() { return _height; }

inline bool Graphics::should_window_close() { return glfwWindowShouldClose(_window); }

}  // namespace Modules
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
