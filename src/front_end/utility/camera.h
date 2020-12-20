#ifndef SARGASSO_ENGINE_CAMERA_H
#define SARGASSO_ENGINE_CAMERA_H

#include <GL/glew.h>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

using namespace SML;

class Camera {
   public:
    Camera() = default;
    Camera(float width, float height, float z_near, float z_far, float fov);
    Camera(float width, float height, float z_near, float z_far);

    Camera& look_at(const Vec3& target);
    Camera& look_at(const Vec3& from, const Vec3& target);

    Camera& set_position(const Vec3& position);
    Vec3 get_position(const Vec3& position) const;

    Camera& make_conical(float width, float height, float z_near, float z_far, float fov);
    Camera& make_orthogonal(float width, float height, float z_near, float z_far);

    Mat4 get_transform() const;

   private:
    Mat4 _transform;
    Mat4 _lens;
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
