
#include "sargasso/front_end/utility/buffer.h"

#include "sargasso/common/log.h"

using namespace SargassoEngine::FrontEnd::Utility;
using namespace SargassoEngine::Geometry;

Buffer::Buffer(const char* raw_data, const size_t raw_data_size) : _buffer_size(raw_data_size) {
    glGenBuffers(1, &_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glBufferData(GL_ARRAY_BUFFER, _buffer_size, raw_data, GL_STATIC_DRAW);
    Common::logf("Generating buffer #% (% bytes)", _buffer_id, _buffer_size);
}

Buffer::Buffer(const Vertex* vertices, const size_t vertex_count)
    : Buffer(reinterpret_cast<const char*>(vertices), vertex_count * sizeof(Vertex)) {
    for (size_t i = 0; i < vertex_count; i++) {
        Common::log(vertices[i].position.to_string());
    }
}

Buffer::~Buffer() { glDeleteBuffers(1, &_buffer_id); }

GLuint Buffer::get_id() const { return _buffer_id; }

size_t Buffer::get_size() const { return _buffer_size; }

void Buffer::render(const ShaderProgram& shader_program) const {
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);

    // send buffer data to shader attribute variables
    shader_program.set_attribute("vertex_position", GL_FLOAT, sizeof(Vertex), 3, 0);
    shader_program.set_attribute("vertex_color", GL_FLOAT, sizeof(Vertex), 4, sizeof(GLfloat) * 3);

    glDrawArrays(GL_TRIANGLES, 0, _buffer_size);
}
