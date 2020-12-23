#ifndef SARGASSO_ENGINE_FRONT_END_GRAPHICS_H
#define SARGASSO_ENGINE_FRONT_END_GRAPHICS_H

#include "sargasso/front_end/utility/buffer.h"
#include "sargasso/front_end/utility/camera.h"
#include "sargasso/front_end/utility/shader_program.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <sml/matrix4.h>
#include <sml/vector3.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace SargassoEngine {
namespace FrontEnd {
namespace Modules {

using namespace SML;
using namespace Utility;

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

    void register_buffer(const Vertex* vertices, const size_t vertex_count);
    void render_buffers();

    ShaderProgram& get_shader(const std::string& shader_name);
    void use_shader(const std::string& shader_name);
    void create_shader(const std::string& shader_name);

    void set_camera(const Camera& camera);
    Camera get_camera() const;

   private:
    GLFWwindow* _window;
    int _width;
    int _height;
    Camera _camera;
    std::unordered_map<std::string, ShaderProgram*> _shaders;
    std::vector<Buffer*> _buffers;
    std::string _current_shader;
    void _set_shader_camera();
};

}  // namespace Modules
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
