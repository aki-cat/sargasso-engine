#ifndef SARGASSO_ENGINE_COMMON_MATH_VECTOR3_H
#define SARGASSO_ENGINE_COMMON_MATH_VECTOR3_H

#include "common/format.h"
#include "common/math/points.h"

namespace SargassoEngine {
namespace Common {
namespace Math {

class Quat;

class Vec3 {
   public:
    Vec3(float _x, float _y, float _z);
    Vec3();

    // data
    float &x, &y, &z;

    // methods
    const std::string to_string() const;

    float dot(const Vec3& v) const;
    Vec3 cross(const Vec3& v) const;

    Vec3 normalized() const;
    Vec3& normalize();

    Vec3 clamped(const float s) const;
    Vec3& clamp(const float s);

    float magnitude() const;
    float magnitude_squared() const;

    Vec3 translated(const Vec3& v) const;
    Vec3& translate(const Vec3& v);

    Vec3& rotate(const Vec3& axis, const float angle);
    Vec3 rotated(const Vec3& axis, const float angle) const;

    Vec3 rotated(const Quat& q) const;
    Vec3& rotate(const Quat& q);

    Vec3 scaled(const float s) const;
    Vec3& scale(const float s);

    // convenient
    static const Vec3& zero;
    static const Vec3& up;
    static const Vec3& down;
    static const Vec3& front;
    static const Vec3& back;
    static const Vec3& left;
    static const Vec3& right;

    // convenient axes
    static const Vec3& x_axis;
    static const Vec3& y_axis;
    static const Vec3& z_axis;

    // conversions
    operator std::string();

   private:
    Points3 _points;
};

// Imutable operators

bool operator==(const Vec3& a, const Vec3& b);
bool operator!=(const Vec3& a, const Vec3& b);

Vec3 operator*(const float a, const Vec3& v);
Vec3 operator*(const Vec3& v, const float a);
Vec3 operator/(const Vec3& v, const float a);

float operator*(const Vec3& a, const Vec3& b);
Vec3 operator^(const Vec3& a, const Vec3& b);
Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);

Vec3 operator-(const Vec3& v);

// Mutable operators

Vec3& operator*=(Vec3& v, const float a);
Vec3& operator/=(Vec3& v, const float a);
Vec3& operator+=(Vec3& a, const Vec3& b);
Vec3& operator-=(Vec3& a, const Vec3& b);

}  // namespace Math
}  // namespace Common
}  // namespace SargassoEngine

#endif
