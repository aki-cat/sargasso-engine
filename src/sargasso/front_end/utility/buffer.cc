
#include "sargasso/front_end/utility/buffer.h"

#include "sargasso/common/log.h"
#include "sargasso/geometry/constants.h"

using namespace SargassoEngine::FrontEnd::Utility;
using namespace SargassoEngine::Geometry;

Buffer::Buffer(const char* raw_data, const size_t raw_data_size) : _buffer_size(raw_data_size) {
    glGenBuffers(1, &_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glBufferData(GL_ARRAY_BUFFER, _buffer_size, raw_data, GL_STATIC_DRAW);
    Common::logf("Generating buffer #% (% bytes)", _buffer_id, _buffer_size);
}

Buffer::Buffer(const Vec3* vertices, const size_t vertex_count)
    : Buffer(reinterpret_cast<const char*>(vertices), vertex_count * sizeof(Vec3)) {
    for (size_t i = 0; i < vertex_count; i++) {
        Common::log(vertices[i].to_string());
    }
}

Buffer::~Buffer() { glDeleteBuffers(1, &_buffer_id); }

GLuint Buffer::get_id() const { return _buffer_id; }

size_t Buffer::get_size() const { return _buffer_size; }

void Buffer::render() const {
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glVertexAttribPointer(0, POINTS_PER_VERTEX, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    // Rendering buffer
    glDrawArrays(GL_TRIANGLES, 0, _buffer_size);
    glDisableVertexAttribArray(0);
}
