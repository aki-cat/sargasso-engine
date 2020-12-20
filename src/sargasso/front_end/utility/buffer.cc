
#include "sargasso/front_end/utility/buffer.h"

#include "sargasso/common/log.h"
#include "sargasso/geometry/constants.h"

using namespace SargassoEngine::FrontEnd::Utility;
using namespace SargassoEngine::Geometry;

Buffer::Buffer(const std::vector<Vec3>& points) : _point_count(points.size() * POINTS_PER_VERTEX) {
    const Vec3* points_array = points.data();
    const float* data = reinterpret_cast<const float*>(points_array);

    glGenBuffers(1, &_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size() * 3, data, GL_STATIC_DRAW);

    Common::logf("Generating buffer #% (% points)", _buffer_id, _point_count);
}

Buffer::~Buffer() { glDeleteBuffers(1, &_buffer_id); }

GLuint Buffer::get_id() const { return _buffer_id; }

size_t Buffer::get_buffer_size() const { return _point_count * sizeof(float); }

void Buffer::render() const {
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glVertexAttribPointer(
        0,  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        POINTS_PER_VERTEX,  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*) 0           // array buffer offset
    );

    // Draw the buffer !
    Common::logf("Rendering buffer #% (% points)", _buffer_id, _point_count);

    // Starting from vertex 0; 3 vertices total -> 1 buffer
    glDrawArrays(GL_TRIANGLES, 0, get_buffer_size());
    glDisableVertexAttribArray(0);
}
