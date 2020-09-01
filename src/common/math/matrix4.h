/*

Parts of this code were on the Hypatia C math library, developed by Darryl T. Agostinelli.
Licensed under MIT license.

*/
#ifndef SARGASSO_ENGINE_COMMON_MATH_MATRIX4_H
#define SARGASSO_ENGINE_COMMON_MATH_MATRIX4_H

#include "common/math/points.h"
#include "common/math/quaternion.h"
#include "common/math/transform.h"
#include "common/math/vector3.h"

namespace SargassoEngine {
namespace Common {
namespace Math {

using Points16 = Points<16>;

class Mat4 {
   public:
    Mat4();
    Mat4(Points16 points);

    // transformation methods
    Mat4 translated(const Vec3& v) const;
    Mat4& translate(const Vec3& v);
    Mat4& scale(const float a);
    Mat4 scaled(const float a) const;
    Mat4 rotated(const Vec3& axis, const float angle) const;
    Mat4& rotate(const Vec3& axis, const float angle);

    // misc methods
    std::string to_string() const;
    Mat4& round();
    Mat4& copy(const Mat4& m);

    // useful constant matrices
    static Mat4 identity();
    static Mat4 zero();

    // useful dynamic matrices
    static Mat4 perspective_projection(float fov, float aspect, float z_near, float z_far);
    static Mat4 look_at(const Vec3& from, const Vec3& target, const Vec3& up);
    static Mat4 look_at(const Vec3& from, const Vec3& target);

    operator std::string();
    float operator[](const uint32_t n) const;
    float& operator[](const uint32_t n);

   private:
    Points16 _points;
    /* data */
};

// Operators

bool operator==(const Mat4& a, const Mat4& b);
bool operator!=(const Mat4& a, const Mat4& b);

Mat4 operator+(const Mat4& a, const Mat4& b);
Mat4 operator-(const Mat4& a, const Mat4& b);
Mat4 operator-(const Mat4& m);

Mat4 operator*(const Mat4& a, const Mat4& b);
Vec3 operator*(const Mat4& m, const Vec3& v);
Mat4 operator*(const Mat4& m, const float a);
Mat4 operator*(const float a, const Mat4& m);

Mat4& operator+=(Mat4& a, const Mat4& b);
Mat4& operator-=(Mat4& a, const Mat4& b);
Mat4& operator*=(Mat4& a, const Mat4& b);
Mat4& operator*=(Mat4& m, const float a);

/*

====================
== IMPLEMENTATION ==
====================

*/

// Constructors

inline Mat4::Mat4() : Mat4({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}) {}

inline Mat4::Mat4(Points16 points) : _points{points} {}

// Useful static members

inline Mat4 Mat4::identity() {
    static const Mat4 m = Mat4({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
    return m;
}

inline Mat4 Mat4::zero() {
    static const Mat4 m = Mat4({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    return m;
}

// Useful dynamic matrices

inline Mat4 Mat4::perspective_projection(float fov, float aspect, float z_near, float z_far) {
    float rect_height;
    float rect_width;
    float z_dist = z_near - z_far;
    float z_far_per_dist = z_far / z_dist;

    rect_height = 1.0f / static_cast<float>(tan(fov * 0.5));
    rect_width = rect_height * aspect;

    Mat4 m = Mat4::zero();

    m[0] = rect_width;
    m[5] = rect_height;
    m[10] = z_far_per_dist;
    m[11] = -1.0f;
    m[14] = 2.0f * z_near * z_far_per_dist;

    return m;
}

inline Mat4 Mat4::look_at(const Vec3& from, const Vec3& target, const Vec3& up) {
    Vec3 zaxis = Vec3({target.x - from.x, target.y - from.y, target.z - from.z}).normalized();

    // xaxis = zaxis x up
    Vec3 xaxis = zaxis.cross(up).normalized();

    // yaxis = xaxis x zaxis
    Vec3 yaxis = xaxis.cross(zaxis);

    Mat4 m = Mat4::identity();

    m[0] = xaxis.x;
    m[1] = xaxis.y;
    m[2] = xaxis.z;

    m[4] = yaxis.x;
    m[5] = yaxis.y;
    m[6] = yaxis.z;

    m[8] = -zaxis.x;
    m[9] = -zaxis.y;
    m[10] = -zaxis.z;

    m[3] = -xaxis.dot(from);
    m[7] = -yaxis.dot(from);
    m[11] = -zaxis.dot(from);

    return m;
}

inline Mat4 Mat4::look_at(const Vec3& from, const Vec3& target) {
    return look_at(from, target, Vec3::up());
}

// Methods

inline Mat4 Mat4::translated(const Vec3& v) const {
    Mat4 m = Mat4::identity();
    m[3] += v.x;
    m[7] += v.y;
    m[11] += v.z;
    return (*this) * m;
}

inline Mat4& Mat4::translate(const Vec3& v) {
    Mat4 m = Mat4::identity();
    m[3] += v.x;
    m[7] += v.y;
    m[11] += v.z;
    return (*this) *= m;
}

inline Mat4 Mat4::scaled(const float a) const { return (*this) * a; }

inline Mat4& Mat4::scale(const float a) {
    for (uint32_t i = 0; i < Points16::len; i++) {
        _points[i] *= a;
    }
    return *this;
}

inline Mat4 Mat4::rotated(const Vec3& axis, const float angle) const {
    Quat q = Transform::quaternion_from_rotation(axis, angle);
    Mat4 m = Mat4::identity();

    m[0] = 1 - 2 * (q.y * q.y + q.z * q.z);
    m[1] = 2 * (q.x * q.y - q.z * q.w);
    m[2] = 2 * (q.x * q.z + q.y * q.w);

    m[4] = 2 * (q.x * q.y + q.z * q.w);
    m[5] = 1 - 2 * (q.x * q.x + q.z * q.z);
    m[6] = 2 * (q.y * q.z - q.x * q.w);

    m[8] = 2 * (q.x * q.z - q.y * q.w);
    m[9] = 2 * (q.y * q.z + q.x * q.w);
    m[10] = 1 - 2 * (q.x * q.x + q.y * q.y);

    return (*this) * m.round();
}

inline Mat4& Mat4::rotate(const Vec3& axis, const float angle) {
    Quat q = Transform::quaternion_from_rotation(axis, angle);
    Mat4 m = Mat4::identity();

    m[0] = 1 - 2 * (q.y * q.y + q.z * q.z);
    m[1] = 2 * (q.x * q.y - q.z * q.w);
    m[2] = 2 * (q.x * q.z + q.y * q.w);

    m[4] = 2 * (q.x * q.y + q.z * q.w);
    m[5] = 1 - 2 * (q.x * q.x + q.z * q.z);
    m[6] = 2 * (q.y * q.z - q.x * q.w);

    m[8] = 2 * (q.x * q.z - q.y * q.w);
    m[9] = 2 * (q.y * q.z + q.x * q.w);
    m[10] = 1 - 2 * (q.x * q.x + q.y * q.y);

    return (*this) *= m.round();
}

inline Mat4& Mat4::round() {
    for (uint32_t i = 0; i < Points16::len; i++) {
        if (fabs(_points[i]) <= FLT_EPSILON) {
            _points[i] = 0;
        }
    }
    return (*this);
}

inline Mat4& Mat4::copy(const Mat4& m) {
    for (uint32_t i = 0; i < Points16::len; i++) {
        _points[i] = m[i];
    }
    return (*this);
}

inline std::string Mat4::to_string() const {
    return format("Mat4 { % % % % }\n", _points[0], _points[1], _points[2], _points[3]) +
           format("     { % % % % }\n", _points[4], _points[5], _points[6], _points[7]) +
           format("     { % % % % }\n", _points[8], _points[9], _points[10], _points[11]) +
           format("     { % % % % }\n", _points[12], _points[13], _points[14], _points[15]);
}

// Conversion operators

inline Mat4::operator std::string() { return to_string(); }

inline float Mat4::operator[](const uint32_t n) const { return _points[n]; }

inline float& Mat4::operator[](const uint32_t n) { return _points[n]; }

// Imutable operators

inline bool operator==(const Mat4& a, const Mat4& b) {
    for (uint32_t i = 0; i < Points16::len; i++) {
        if (fabs(a[i] - b[i]) > FLT_EPSILON) {
            return false;
        }
    }
    return true;
}

inline bool operator!=(const Mat4& a, const Mat4& b) {
    for (uint32_t i = 0; i < Points16::len; i++) {
        if (fabs(a[i] - b[i]) > FLT_EPSILON) {
            return true;
        }
    }
    return false;
}

inline Mat4 operator+(const Mat4& a, const Mat4& b) {
    Mat4 m{};
    for (uint32_t i = 0; i < Points16::len; i++) {
        m[i] = a[i] + b[i];
    }
    return m;
}

inline Mat4 operator-(const Mat4& a, const Mat4& b) {
    Mat4 m{};
    for (uint32_t i = 0; i < Points16::len; i++) {
        m[i] = a[i] - b[i];
    }
    return m;
}

inline Mat4 operator*(const Mat4& a, const Mat4& b) {
    return Mat4({a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12],
                 a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13],
                 a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14],
                 a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15],
                 a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12],
                 a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13],
                 a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14],
                 a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15],
                 a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12],
                 a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13],
                 a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14],
                 a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15],
                 a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12],
                 a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13],
                 a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14],
                 a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]});
}

// We always assume vector is susceptible to translations (w = 1)
inline Vec3 operator*(const Mat4& m, const Vec3& v) {
    return Vec3(m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3],
                m[4] * v.x + m[5] * v.y + m[6] * v.z + m[7],
                m[8] * v.x + m[9] * v.y + m[10] * v.z + m[11]);
}

inline Mat4 operator*(const Mat4& m, const float a) {
    Mat4 n{};
    for (uint32_t i = 0; i < Points16::len; i++) {
        n[i] = m[i] * a;
    }
    return n;
}

inline Mat4 operator*(const float a, const Mat4& m) {
    Mat4 n{};
    for (uint32_t i = 0; i < Points16::len; i++) {
        n[i] = m[i] * a;
    }
    return n;
}

inline Mat4 operator-(const Mat4& m) {
    Mat4 n{};
    for (uint32_t i = 0; i < Points16::len; i++) {
        n[i] = -m[i];
    }
    return n;
}

// Mutable operators

inline Mat4& operator+=(Mat4& a, const Mat4& b) {
    for (uint32_t i = 0; i < Points16::len; i++) {
        a[i] += b[i];
    }
    return a;
}

inline Mat4& operator-=(Mat4& a, const Mat4& b) {
    for (uint32_t i = 0; i < Points16::len; i++) {
        a[i] -= b[i];
    }
    return a;
}

inline Mat4& operator*=(Mat4& a, const Mat4& b) {
    Points16 p({a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12],
                a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13],
                a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14],
                a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15],
                a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12],
                a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13],
                a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14],
                a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15],
                a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12],
                a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13],
                a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14],
                a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15],
                a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12],
                a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13],
                a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14],
                a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]});
    for (uint32_t i = 0; i < Points16::len; i++) {
        a[i] = p[i];
    }
    return a;
}

inline Mat4& operator*=(Mat4& m, const float a) {
    for (uint32_t i = 0; i < Points16::len; i++) {
        m[i] *= a;
    }
    return m;
}

}  // namespace Math
}  // namespace Common
}  // namespace SargassoEngine

#endif