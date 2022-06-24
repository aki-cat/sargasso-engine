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
        : _width(width),
          _height(height),
          _mesh(std::vector<Vertex>{Vertex{sml::Vec3(-.5f * width, -.5f * height, 0),
                                           sml::Color::white(), sml::Vec3::zero(), 0.f, 0.f},
                                    Vertex{sml::Vec3(+.5f * width, -.5f * height, 0),
                                           sml::Color::white(), sml::Vec3::zero(), 0.f, 0.f},
                                    Vertex{sml::Vec3(+.5f * width, +.5f * height, 0),
                                           sml::Color::white(), sml::Vec3::zero(), 0.f, 0.f},
                                    Vertex{sml::Vec3(-.5f * width, +.5f * height, 0),
                                           sml::Color::white(), sml::Vec3::zero(), 0.f, 0.f}},
                std::vector<IndexTriPlane>{IndexTriPlane{0, 1, 2}, IndexTriPlane{2, 3, 0}}) {}

    const Mesh& getMesh() const {
        return *&_mesh;
    }

   private:
    const float _width;
    const float _height;
    const Mesh _mesh;
};

}  // namespace geometry
}  // namespace sargasso

#endif  // SARGASSO_GEOMETRY_RECT_H_
