/**
 * Copyright (c) 2020 W. Akira Mizutani
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "sargasso/front_end/utility/buffer.h"

#include "sargasso/common/log.h"

using SargassoEngine::FrontEnd::Utility::Buffer;
using SargassoEngine::Geometry::Vertex;

Buffer::Buffer(const Vertex* vertices, const size_t vertex_count) : _vertex_count(vertex_count) {
    _vertices = new Vertex[_vertex_count];

    const char* raw_data = reinterpret_cast<const char*>(_vertices);

    glGenBuffers(1, &_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glBufferData(GL_ARRAY_BUFFER, get_size(), raw_data, GL_STATIC_DRAW);

    Common::logf("Generating buffer #% (% bytes)", _buffer_id, get_size());
}

Buffer::~Buffer() {
    delete[] _vertices;
    glDeleteBuffers(1, &_buffer_id);
}

GLuint Buffer::get_id() const { return _buffer_id; }

size_t Buffer::get_size() const { return _vertex_count * sizeof(Vertex); }

void Buffer::render(const ShaderProgram& shader_program) const {
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);

    // send buffer data to shader attribute variables
    shader_program.set_attribute("vertex_position", GL_FLOAT, sizeof(Vertex), 3, 0);
    shader_program.set_attribute("vertex_color", GL_FLOAT, sizeof(Vertex), 4, sizeof(GLfloat) * 3);

    glDrawArrays(GL_TRIANGLES, 0, _vertex_count);
}
