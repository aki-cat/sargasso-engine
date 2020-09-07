#include "common/math/vector3.h"

#include "common/math/quaternion.h"

using SargassoEngine::Common::Math::Quat;
using SargassoEngine::Common::Math::Vec3;

#include <cfloat>
#include <cmath>
#include <string>

/*

====================
== IMPLEMENTATION ==
====================

*/

Vec3::Vec3(float _x, float _y, float _z)
    : x{_points.p[0]}, y{_points.p[1]}, z{_points.p[2]}, _points{} {
    _points.p[0] = _x;
    _points.p[1] = _y;
    _points.p[2] = _z;
}

Vec3::Vec3() : Vec3(0.0f, 0.0f, 0.0f) {}

// Static members

const Vec3& Vec3::zero = Vec3();
const Vec3& Vec3::up = Vec3(+0.0f, +1.0f, +0.0f);
const Vec3& Vec3::down = Vec3(+0.0f, -1.0f, +0.0f);
const Vec3& Vec3::front = Vec3(+0.0f, +0.0f, -1.0f);
const Vec3& Vec3::back = Vec3(+0.0f, +0.0f, +1.0f);
const Vec3& Vec3::left = Vec3(-1.0f, +0.0f, +0.0f);
const Vec3& Vec3::right = Vec3(+1.0f, +0.0f, +0.0f);
const Vec3& Vec3::x_axis = Vec3(+1.0f, +0.0f, +0.0f);
const Vec3& Vec3::y_axis = Vec3(+0.0f, +1.0f, +0.0f);
const Vec3& Vec3::z_axis = Vec3(+0.0f, +0.0f, +1.0f);

// Methods

inline const std::string Vec3::to_string() const { return format("Vec3(%, %, %)", x, y, z); }

/*
Dot product
ux * vx + uy * vy + uz * vz
*/
inline float Vec3::dot(const Vec3& v) const { return (x * v.x) + (y * v.y) + (z * v.z); }

/*
Cross product
|  i  j  k   |
|  a1 a2 a3  |
|  b1 b2 b3  |
*/
inline Vec3 Vec3::cross(const Vec3& v) const {
    return Vec3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
}

inline Vec3 Vec3::normalized() const { return *this / magnitude(); }
inline Vec3& Vec3::normalize() { return *this /= static_cast<float>(sqrt(*this * *this)); }

inline Vec3 Vec3::clamped(const float s) const { return normalized() * s; }
inline Vec3& Vec3::clamp(const float s) { return normalize() *= s; }

inline float Vec3::magnitude() const { return static_cast<float>(sqrt((*this) * (*this))); }
inline float Vec3::magnitude_squared() const { return *this * *this; }

inline Vec3 Vec3::translated(const Vec3& v) const { return *this + v; }
inline Vec3& Vec3::translate(const Vec3& v) { return *this += v; }

inline Vec3 Vec3::rotated(const Vec3& axis, const float angle) const {
    const float sine = static_cast<float>(sin(angle));
    const float cosine = static_cast<float>(cos(angle));
    const Vec3 normal = axis.normalized();
    return (1 - cosine) * (dot(normal)) * normal + cosine * (*this) + sine * (normal.cross(*this));
}

inline Vec3& Vec3::rotate(const Vec3& axis, const float angle) {
    const Vec3 result = rotated(axis, angle);
    x = result.x;
    y = result.y;
    z = result.z;
    return *this;
}

Vec3 Vec3::rotated(const Quat& q) const {
    const Vec3 v = *this;
    const Vec3& qv = q.vector();
    return v + 2 * (qv ^ ((qv ^ v) + q.w * v));
}

Vec3& Vec3::rotate(const Quat& q) {
    Vec3& v = *this;
    const Vec3& qv = q.vector();
    return v += (2 * (qv ^ ((qv ^ v) + q.w * v)));
}

inline Vec3 Vec3::scaled(const float s) const { return *this * s; }
inline Vec3& Vec3::scale(const float s) { return *this *= s; }

// Conversion operators

Vec3::operator std::string() { return to_string(); }

// Imutable operators

bool operator==(const Vec3& a, const Vec3& b) {
    return fabs(a.x - b.x) < FLT_EPSILON && fabs(a.y - b.y) < FLT_EPSILON &&
           fabs(a.z - b.z) < FLT_EPSILON;
}

bool operator!=(const Vec3& a, const Vec3& b) {
    return !(fabs(a.x - b.x) < FLT_EPSILON && fabs(a.y - b.y) < FLT_EPSILON &&
             fabs(a.z - b.z) < FLT_EPSILON);
}

Vec3 operator*(const float a, const Vec3& v) { return Vec3(v.x * a, v.y * a, v.z * a); }
Vec3 operator*(const Vec3& v, const float a) { return Vec3(v.x * a, v.y * a, v.z * a); }
Vec3 operator/(const Vec3& v, const float a) {
    const float factor = 1 / a;
    return Vec3(v.x * factor, v.y * factor, v.z * factor);
}

Vec3 operator+(const Vec3& a, const Vec3& b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
Vec3 operator-(const Vec3& a, const Vec3& b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
Vec3 operator-(const Vec3& v) { return Vec3(-v.x, -v.y, -v.z); }

float operator*(const Vec3& a, const Vec3& b) { return a.dot(b); }

Vec3 operator^(const Vec3& a, const Vec3& b) { return a.cross(b); }

// Mutable operators

Vec3& operator*=(Vec3& v, const float& a) {
    v.x *= a;
    v.y *= a;
    v.z *= a;
    return v;
}

Vec3& operator/=(Vec3& v, const float& a) {
    v.x /= a;
    v.y /= a;
    v.z /= a;
    return v;
}

Vec3& operator+=(Vec3& a, const Vec3& b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

Vec3& operator-=(Vec3& a, const Vec3& b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}
