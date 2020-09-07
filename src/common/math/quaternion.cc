
#include "common/math/quaternion.h"

#include "common/math/vector3.h"

using SargassoEngine::Common::Math::Quat;
using SargassoEngine::Common::Math::Vec3;

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

Quat::Quat(const float _w, const Vec3& vector) : Quat(_w, vector.x, vector.y, vector.z) {}

Quat::Quat(const Vec3& vector) : Quat(0.0f, vector) {}

Quat::Quat() : Quat(1.0f, 0.0f, 0.0f, 0.0f) {}

// Static members

const Quat& Quat::identity = Quat(1.0f, 0.0f, 0.0f, 0.0f);
const Quat& Quat::zero = Quat(0.0f, 0.0f, 0.0f, 0.0f);
const Quat& Quat::i = Quat(0.0f, 1.0f, 0.0f, 0.0f);
const Quat& Quat::j = Quat(0.0f, 0.0f, 1.0f, 0.0f);
const Quat& Quat::k = Quat(0.0f, 0.0f, 0.0f, 1.0f);

// Constructor methods
inline Quat Quat::from_rotation(const Vec3& axis, const float angle) {
    float sine = static_cast<float>(sin(angle / 2));
    float cosine = static_cast<float>(cos(angle / 2));
    const Vec3 vector_component = sine * axis.normalized();
    return Quat(cosine, vector_component.x, vector_component.y, vector_component.z);
}

// Methods

inline const std::string Quat::to_string() const {
    return format("Quat(%, %i, %j, %k)", w, x, y, z);
}

inline Quat& Quat::add(const Quat& q) { return (*this) += q; }
inline Quat Quat::added(const Quat& q) const { return (*this) + q; }

inline Quat& Quat::scale(const float a) { return (*this) *= a; }
inline Quat Quat::scaled(const float a) const { return (*this) * a; }

inline Quat Quat::multiplied(const Quat& q) const { return (*this) * q; }

inline Vec3 Quat::vector() const { return Vec3(x, y, z); }

// Conversion operators

Quat::operator std::string() { return to_string(); }

// Imutable operators

bool operator==(const Quat& a, const Quat& b) {
    return fabs(a.w - b.w) < FLT_EPSILON && fabs(a.x - b.x) < FLT_EPSILON &&
           fabs(a.y - b.y) < FLT_EPSILON && fabs(a.z - b.z) < FLT_EPSILON;
}

bool operator!=(const Quat& a, const Quat& b) {
    return !(fabs(a.w - b.w) < FLT_EPSILON && fabs(a.x - b.x) < FLT_EPSILON &&
             fabs(a.y - b.y) < FLT_EPSILON && fabs(a.z - b.z) < FLT_EPSILON);
}

Quat operator*(const float a, const Quat& q) { return Quat(a * q.w, a * q.x, a * q.y, a * q.z); }

Quat operator*(const Quat& q, const float a) { return Quat(a * q.w, a * q.x, a * q.y, a * q.z); }

Quat operator/(const Quat& q, const float a) {
    const float factor = 1 / a;
    return Quat(factor * q.w, factor * q.x, factor * q.y, factor * q.z);
}

Quat operator*(const Quat& a, const Vec3& b) {
    Quat qb = Quat(b);
    return a * qb;
}

Quat operator*(const Vec3& a, const Quat& b) {
    Quat qa = Quat(a);
    return qa * b;
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
