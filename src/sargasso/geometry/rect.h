#ifndef SARGASSO_GEOMETRY_RECT_H_
#define SARGASSO_GEOMETRY_RECT_H_

#include "sargasso/geometry/mesh.h"
#include "sargasso/geometry/vertex.h"

#include <random>
#include <sml/color.h>
#include <sml/matrix4.h>
#include <sml/vector3.h>

namespace sargasso {
namespace geometry {

inline float randf() {
    return std::rand() % 0xff * 1.f / 0xff;
}

inline sml::Color randColor() {
    return sml::Color(randf(), randf(), randf(), 1.f);
}

class Rect {
   public:
    Rect(float width, float height)
        : _width(width),
          _height(height),
          _transform(sml::Mat4::identity()),
          _mesh(std::vector<Vertex>{Vertex{sml::Vec3(-.5f * width, -.5f * height, 0), randColor(),
                                           sml::Vec3::zero(), 0.f, 0.f},
                                    Vertex{sml::Vec3(+.5f * width, -.5f * height, 0), randColor(),
                                           sml::Vec3::zero(), 0.f, 0.f},
                                    Vertex{sml::Vec3(+.5f * width, +.5f * height, 0), randColor(),
                                           sml::Vec3::zero(), 0.f, 0.f},
                                    Vertex{sml::Vec3(-.5f * width, +.5f * height, 0), randColor(),
                                           sml::Vec3::zero(), 0.f, 0.f}},
                std::vector<IndexTriPlane>{IndexTriPlane{0, 1, 2}, IndexTriPlane{2, 3, 0}}) {}

    const Mesh& getMesh() const {
        return *&_mesh;
    }

    const sml::Mat4& getTransform() const {
        return _transform;
    }

    void setTransform(const sml::Mat4& transform) {
        _transform.copy(transform);
    }

   private:
    const float _width;
    const float _height;
    sml::Mat4 _transform;
    const Mesh _mesh;
};

}  // namespace geometry
}  // namespace sargasso

#endif  // SARGASSO_GEOMETRY_RECT_H_
