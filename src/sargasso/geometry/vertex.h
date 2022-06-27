#ifndef SARGASSO_GEOMETRY_VERTEX_H_
#define SARGASSO_GEOMETRY_VERTEX_H_

#include <sml/color.h>
#include <sml/vector3.h>

namespace sargasso {
namespace geometry {

struct Vertex {
    sml::Vec3 position;
    sml::Color color;
    sml::Vec3 normal;
    struct {
        float x, y;
    } uv;
};

}  // namespace geometry
}  // namespace sargasso

#endif  // SARGASSO_GEOMETRY_VERTEX_H_
