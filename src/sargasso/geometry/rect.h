#ifndef SARGASSO_GEOMETRY_RECT_H_
#define SARGASSO_GEOMETRY_RECT_H_

#include "sargasso/geometry/mesh.h"
#include "sargasso/geometry/vertex.h"

#include <sml/color.h>
#include <sml/vector3.h>

namespace sargasso {
namespace geometry {

class Rect {
   public:
    Rect(float width, float height)
        : _mesh(std::vector<Vertex>{Vertex{sml::Vec3(-.5f * width, -.5f * height, 0),
                                           sml::Color::white(), sml::Vec3::zero(), 0.f, 0.f},
                                    Vertex{sml::Vec3(+.5f * width, -.5f * height, 0),
                                           sml::Color::white(), sml::Vec3::zero(), 0.f, 0.f},
                                    Vertex{sml::Vec3(+.5f * width, +.5f * height, 0),
                                           sml::Color::white(), sml::Vec3::zero(), 0.f, 0.f},
                                    Vertex{sml::Vec3(-.5f * width, +.5f * height, 0),
                                           sml::Color::white(), sml::Vec3::zero(), 0.f, 0.f}},
                std::vector<Triangle>{{0, 1, 2}, {2, 3, 0}}) {}

   private:
    Mesh _mesh;
    float _width;
    float _height;
};

}  // namespace geometry
}  // namespace sargasso

#endif // SARGASSO_GEOMETRY_RECT_H_
