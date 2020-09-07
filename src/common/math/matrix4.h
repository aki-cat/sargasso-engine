#ifndef SARGASSO_ENGINE_COMMON_MATH_MATRIX4_H
#define SARGASSO_ENGINE_COMMON_MATH_MATRIX4_H

#include "common/math/points.h"
#include "common/math/vector3.h"

namespace SargassoEngine {
namespace Common {
namespace Math {

using Points16 = Points<16>;

class Mat4 {
   public:
    Mat4();
    Mat4(Points16 points);

    // useful matrices
    static const Mat4& identity;
    static const Mat4& zero;

    // methods
    Mat4 translated(const Vec3& v) const;
    Mat4& translate(const Vec3& v);
    Mat4 scaled(const float a) const;
    Mat4& scale(const float a);
    Mat4 rotated(const Vec3& axis, const float angle) const;
    Mat4& rotate(const Vec3& axis, const float angle);

    std::string to_string() const;

    operator std::string();
    float operator[](const uint32_t n) const;
    float& operator[](const uint32_t n);

   private:
    Points16 _points;
    /* data */
};

// Operators

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

Mat4::Mat4() : _points{{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}} {}

Mat4::Mat4(Points16 points) : _points{points} {}

// Useful static members

const Mat4& Mat4::identity = Mat4(Points16{{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}});

const Mat4& Mat4::zero = Mat4(Points16{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

// Methods

Mat4 Mat4::translated(const Vec3& v) const {
    Mat4 m = Mat4::identity;
    m[3] += v.x;
    m[7] += v.y;
    m[11] += v.z;
    return (*this) * m;
}

Mat4& Mat4::translate(const Vec3& v) {
    Mat4 m = Mat4::identity;
    m[3] += v.x;
    m[7] += v.y;
    m[11] += v.z;
    return (*this) *= m;
}

Mat4 Mat4::scaled(const float a) const { return (*this) * a; }

Mat4& Mat4::scale(const float a) {
    for (uint32_t i = 0; i < Points16::len; i++) {
        _points[i] *= a;
    }
    return *this;
}

Mat4 Mat4::rotated(const Vec3& axis, const float angle) const {
    // TBD
    Mat4 m{*this};
    return m;
}

Mat4& Mat4::rotate(const Vec3& axis, const float angle) {
    // TBD
    return *this;
}

std::string Mat4::to_string() const {
    return format("Mat4 { % % % % }\n", _points[0], _points[1], _points[2], _points[3]) +
           format("     { % % % % }\n", _points[4], _points[5], _points[6], _points[7]) +
           format("     { % % % % }\n", _points[8], _points[9], _points[10], _points[11]) +
           format("     { % % % % }\n", _points[12], _points[13], _points[14], _points[15]);
}

// Conversion operators

Mat4::operator std::string() { return to_string(); }

float Mat4::operator[](const uint32_t n) const { return _points[n]; }

float& Mat4::operator[](const uint32_t n) { return _points[n]; }

// Imutable operators

Mat4 operator+(const Mat4& a, const Mat4& b) {
    Mat4 m{};
    for (uint32_t i = 0; i < Points16::len; i++) {
        m[i] = a[i] + b[i];
    }
    return m;
}

Mat4 operator-(const Mat4& a, const Mat4& b) {
    Mat4 m{};
    for (uint32_t i = 0; i < Points16::len; i++) {
        m[i] = a[i] - b[i];
    }
    return m;
}

Mat4 operator*(const Mat4& a, const Mat4& b) {
    return Mat4{Points16{a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12],
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
                         a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]}};
}

// We always assume vector is susceptible to translations (w = 1)
Vec3 operator*(const Mat4& m, const Vec3& v) {
    // TBD
    return Vec3{m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3],
                m[4] * v.x + m[5] * v.y + m[6] * v.z + m[7],
                m[8] * v.x + m[9] * v.y + m[10] * v.z + m[11]};
}

Mat4 operator*(const Mat4& m, const float a) {
    Mat4 n{};
    for (uint32_t i = 0; i < Points16::len; i++) {
        n[i] = m[i] * a;
    }
    return n;
}

Mat4 operator*(const float a, const Mat4& m) {
    Mat4 n{};
    for (uint32_t i = 0; i < Points16::len; i++) {
        n[i] = m[i] * a;
    }
    return n;
}

Mat4 operator-(const Mat4& m) {
    Mat4 n{};
    for (uint32_t i = 0; i < Points16::len; i++) {
        n[i] = -m[i];
    }
    return n;
}

// Mutable operators

Mat4& operator+=(Mat4& a, const Mat4& b) {
    for (uint32_t i = 0; i < Points16::len; i++) {
        a[i] += b[i];
    }
    return a;
}

Mat4& operator-=(Mat4& a, const Mat4& b) {
    for (uint32_t i = 0; i < Points16::len; i++) {
        a[i] -= b[i];
    }
    return a;
}

Mat4& operator*=(Mat4& a, const Mat4& b) {
    Mat4 m{Points16{a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12],
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
                    a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]}};
    for (uint32_t i = 0; i < Points16::len; i++) {
        a[i] = m[i];
    }
    return a;
}

Mat4& operator*=(Mat4& m, const float a) {
    for (uint32_t i = 0; i < Points16::len; i++) {
        m[i] *= a;
    }
    return m;
}

}  // namespace Math
}  // namespace Common
}  // namespace SargassoEngine

#endif
