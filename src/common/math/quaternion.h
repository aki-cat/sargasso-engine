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

class Quat {
   public:
    Quat(float _w, float _x, float _y, float _z);
    Quat();

    // data
    float &w, &x, &y, &z;

    // methods
    const std::string to_string() const;

    Quat& add(const Quat& q);
    Quat added(const Quat& q) const;

    Quat& scale(const float a);
    Quat scaled(const float a) const;

    Quat multiplied(const Quat& q) const;

    Quat& normalize();
    Quat normalized() const;

    Quat& conjugate();
    Quat conjugated() const;

    float norm() const;
    float norm_squared() const;

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

Quat operator*(const Quat& a, const Quat& b);
Quat operator+(const Quat& a, const Quat& b);
Quat operator-(const Quat& a, const Quat& b);

Quat operator-(const Quat& q);

// Mutable operators

Quat& operator*=(Quat& q, const float a);
Quat& operator/=(Quat& q, const float a);
Quat& operator+=(Quat& a, const Quat& b);
Quat& operator-=(Quat& a, const Quat& b);

/*

====================
== IMPLEMENTATION ==
====================

*/

Quat::Quat(float _w, float _x, float _y, float _z)
    : w{_points.p[0]}, x{_points.p[1]}, y{_points.p[2]}, z{_points.p[3]}, _points{} {
    _points.p[0] = _w;
    _points.p[1] = _x;
    _points.p[2] = _y;
    _points.p[3] = _z;
}

Quat::Quat() : Quat(1.0f, 0.0f, 0.0f, 0.0f) {}

// Static members

const Quat& Quat::identity = Quat(1.0f, 0.0f, 0.0f, 0.0f);
const Quat& Quat::zero = Quat(0.0f, 0.0f, 0.0f, 0.0f);
const Quat& Quat::i = Quat(0.0f, 1.0f, 0.0f, 0.0f);
const Quat& Quat::j = Quat(0.0f, 0.0f, 1.0f, 0.0f);
const Quat& Quat::k = Quat(0.0f, 0.0f, 0.0f, 1.0f);

// Methods

inline const std::string Quat::to_string() const {
    return format("Quat(%, %i, %j, %k)", w, x, y, z);
}

inline Quat& Quat::add(const Quat& q) { return (*this) += q; }
inline Quat Quat::added(const Quat& q) const { return (*this) + q; }

inline Quat& Quat::scale(const float a) { return (*this) *= a; }
inline Quat Quat::scaled(const float a) const { return (*this) * a; }

inline Quat Quat::multiplied(const Quat& q) const { return (*this) * q; }

inline Quat& Quat::normalize() {
    float factor = 1 / norm();
    w *= factor;
    x *= factor;
    y *= factor;
    z *= factor;
    return (*this);
}

inline Quat Quat::normalized() const {
    float factor = 1 / norm();
    return Quat(w * factor, x * factor, y * factor, z * factor);
}

inline Quat& Quat::conjugate() {
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

inline Quat Quat::conjugated() const { return Quat(w, -x, -y, -z); }

inline float Quat::norm() const { return sqrt(w * w + x * x + y * y + z * z); }

inline float Quat::norm_squared() const { return w * w + x * x + y * y + z * z; }

// Conversion operators

Quat::operator std::string() { return to_string(); }

// Imutable operators

bool operator==(const Quat& a, const Quat& b) {
    return fabs(a.w - b.w) <= FLT_EPSILON && fabs(a.x - b.x) <= FLT_EPSILON &&
           fabs(a.y - b.y) <= FLT_EPSILON && fabs(a.z - b.z) <= FLT_EPSILON;
}

bool operator!=(const Quat& a, const Quat& b) {
    return fabs(a.w - b.w) > FLT_EPSILON || fabs(a.x - b.x) > FLT_EPSILON ||
           fabs(a.y - b.y) > FLT_EPSILON || fabs(a.z - b.z) > FLT_EPSILON;
}

Quat operator*(const float a, const Quat& q) { return Quat(a * q.w, a * q.x, a * q.y, a * q.z); }

Quat operator*(const Quat& q, const float a) { return Quat(a * q.w, a * q.x, a * q.y, a * q.z); }

Quat operator/(const Quat& q, const float a) {
    const float factor = 1 / a;
    return Quat(factor * q.w, factor * q.x, factor * q.y, factor * q.z);
}

/*
Quaternion multiplication
a | w -x -y -z |   b | w |
  | x  w -z -y |     | x |
  | y  z  w -x | x   | y |
  | z  y  x  w |     | z |

*/
Quat operator*(const Quat& a, const Quat& b) {
    return Quat(a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
                a.x * b.w + a.w * b.x - a.z * b.y - a.y * b.z,
                a.y * b.w + a.z * b.x + a.w * b.y - a.x * b.z,
                a.z * b.w + a.y * b.x + a.x * b.y + a.w * b.z);
}

Quat operator+(const Quat& a, const Quat& b) {
    return Quat(a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z);
}

Quat operator-(const Quat& a, const Quat& b) {
    return Quat(a.w - b.w, a.x - b.x, a.y - b.y, a.z - b.z);
}

Quat operator-(const Quat& q) { return Quat(-q.w, -q.x, -q.y, -q.z); }

// Mutable operators

Quat& operator*=(Quat& q, const float a) {
    q.w *= a;
    q.x *= a;
    q.y *= a;
    q.z *= a;
    return q;
}

Quat& operator/=(Quat& q, const float a) {
    q.w /= a;
    q.x /= a;
    q.y /= a;
    q.z /= a;
    return q;
}

Quat& operator+=(Quat& a, const Quat& b) {
    a.w += b.w;
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

Quat& operator-=(Quat& a, const Quat& b) {
    a.w -= b.w;
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

}  // namespace Math
}  // namespace Common
}  // namespace SargassoEngine

#endif
