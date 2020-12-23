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

#ifndef SARGASSO_ENGINE_FRONT_END_UTILITY_BUFFER_H_
#define SARGASSO_ENGINE_FRONT_END_UTILITY_BUFFER_H_

#include "sargasso/front_end/utility/shader_program.h"
#include "sargasso/geometry/vertex.h"

#include <glad/glad.h>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

using Geometry::Vertex;

class Buffer {
   public:
    Buffer(const Vertex* vertices, const size_t vertex_count);
    ~Buffer();
    void render(const ShaderProgram& shader_program) const;
    GLuint get_id() const;
    size_t get_size() const;

   private:
    Vertex* _vertices;
    size_t _vertex_count;
    GLuint _buffer_id;
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif  // SARGASSO_ENGINE_FRONT_END_UTILITY_BUFFER_H_
