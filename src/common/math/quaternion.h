#ifndef SARGASSO_ENGINE_COMMON_MATH_QUATERNION_H
#define SARGASSO_ENGINE_COMMON_MATH_QUATERNION_H

#include "common/format.h"
#include "common/math/points.h"

#include <cfloat>
#include <cmath>
#include <string>

/*

e ^ (theta * normal_quat) = cos(theta) + sin(theta) * normal_quat

sin(theta) * normal_quat = sin(theta) * (0, normal_x, normal_y, normal_z)

v3_rotated_quat = e ^ (theta/2 * normal_quat) * v3_quat * e ^ (-theta/2 * normal_quat)

e ^ (theta/2 * normal_quat) =
    (cos(theta/2), sin(theta/2) * normal_x, sin(theta/2) * normal_y, sin(theta/2) * normal_z)

e ^ (-theta/2 * normal_quat) =
    (cos(theta/2), -sin(theta/2) * normal_x, -sin(theta/2) * normal_y, -sin(theta/2) * normal_z)

*/

namespace SargassoEngine {
namespace Common {
namespace Math {

class Vec3;

class Quat {
   public:
    Quat(float _w, float _x, float _y, float _z);
    Quat(const float _w, const Vec3& vector);
    Quat(const Vec3& vector);
    Quat();

    // data
    float &w, &x, &y, &z;

    // constructor methods
    static Quat from_rotation(const Vec3& axis, const float angle);

    // methods
    const std::string to_string() const;

    Quat& add(const Quat& q);
    Quat added(const Quat& q) const;

    Quat& scale(const float a);
    Quat scaled(const float a) const;

    Quat multiplied(const Quat& q) const;

    Vec3 vector() const;

    // convenient
    static const Quat& identity;
    static const Quat& zero;
    static const Quat& i;
    static const Quat& j;
    static const Quat& k;

    // conversions
    operator std::string();

   private:
    Points4 _points;
};

// Imutable operators

bool operator==(const Quat& a, const Quat& b);
bool operator!=(const Quat& a, const Quat& b);

Quat operator*(const float a, const Quat& q);
Quat operator*(const Quat& q, const float a);
Quat operator/(const Quat& q, const float a);

Quat operator*(const Quat& a, const Vec3& b);
Quat operator*(const Vec3& a, const Quat& b);

Quat operator*(const Quat& a, const Quat& b);
Quat operator+(const Quat& a, const Quat& b);
Quat operator-(const Quat& a, const Quat& b);

Quat operator-(const Quat& q);

// Mutable operators

Quat& operator*=(Quat& q, const float a);
Quat& operator/=(Quat& q, const float a);
Quat& operator+=(Quat& a, const Quat& b);
Quat& operator-=(Quat& a, const Quat& b);

}  // namespace Math
}  // namespace Common
}  // namespace SargassoEngine

#endif
