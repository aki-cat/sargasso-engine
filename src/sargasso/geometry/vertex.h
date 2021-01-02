#ifndef SARGASSO_GEOMETRY_VERTEX_H
#define SARGASSO_GEOMETRY_VERTEX_H

#include <sml/color.h>
#include <sml/vector3.h>

namespace sargasso {
namespace geometry {

struct Vertex {
    Vec3 position;
    Color color;
    Vec3 normal;
    struct {
        float x, y;
    } uv;
};

}  // namespace geometry
}  // namespace sargasso

#endif
