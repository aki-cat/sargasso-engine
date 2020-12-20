
#include "sargasso/front_end/utility/camera.h"

using namespace SargassoEngine::FrontEnd::Utility;
using namespace SML;

Camera::Camera(float width, float height, float z_near, float z_far, float fov)
    : _transform(Mat4::identity()), _projection() {
    _projection = Mat4::conical_projection(fov, width / height, z_near, z_far);
}

Camera::Camera(float width, float height, float z_near, float z_far)
    : _transform(Mat4::identity()), _projection() {
    _projection - Mat4::orthogonal_projection(width, height, z_near, z_far);
}

Camera& Camera::look_at(const Vec3& target) {
    _transform = Mat4::look_at(get_position(), target);
    return *this;
}

Camera& Camera::look_at(const Vec3& from, const Vec3& target) {
    _transform = Mat4::look_at(from, target);
    return *this;
}

Camera& Camera::set_position(const Vec3& position) {
    const Vec3 translation = position - get_position();
    _transform.translate(translation);
    return *this;
}

Vec3 Camera::get_position() const {
    // Translate a zero Vec3 using the view matrix
    return _transform * Vec3::zero();
}

Camera& Camera::make_conical(float width, float height, float z_near, float z_far, float fov) {
    _projection = Mat4::conical_projection(fov, width / height, z_near, z_far);
    return *this;
}

Camera& Camera::make_orthogonal(float width, float height, float z_near, float z_far) {
    _projection - Mat4::orthogonal_projection(width, height, z_near, z_far);
    return *this;
}

Mat4 Camera::get_transform() const {
    // Join the projection and view matrix
    return _projection * _transform;
}
