#ifndef SARGASSO_ENGINE_FRONT_END_GRAPHICS_H
#define SARGASSO_ENGINE_FRONT_END_GRAPHICS_H

#include "front_end/utility/buffer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sml/matrix4.h>
#include <vector>

namespace SargassoEngine {
namespace FrontEnd {
namespace Modules {

using namespace SML;

class Graphics {
   public:
    explicit Graphics();
    Graphics(const Graphics&) = delete;
    Graphics(const Graphics&&) = delete;
    ~Graphics();
    GLFWwindow* get_window() const;
    int get_width() const;
    int get_height() const;
    bool should_window_close() const;
    void render_buffers();

    void set_camera(const Camera& camera);
    Camera get_camera() const;

   private:
    GLFWwindow* _window;
    int _width;
    int _height;
    GLuint _program_id;
    GLuint _vao_id;
    Camera _camera;
    std::vector<Buffer> _buffers;
    void _set_shader_camera();
};

}  // namespace Modules
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
