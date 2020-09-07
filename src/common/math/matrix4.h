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

    Mat4 multiplied(const Vec3& v) const;
    Mat4& multiply(const Vec3& v);
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
Mat4 operator*(const Mat4& m, const Vec3& v);

Mat4& operator+=(const Mat4& a, const Mat4& b);
Mat4& operator-=(const Mat4& a, const Mat4& b);
Mat4& operator*=(const Mat4& a, const Mat4& b);

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
    Mat4 m{*this};
    m[3] += v.x;
    m[7] += v.y;
    m[11] += v.z;
    return m;
}

Mat4& Mat4::translate(const Vec3& v) {
    _points[3] += v.x;
    _points[7] += v.y;
    _points[11] += v.z;
    return *this;
}

Mat4 Mat4::scaled(const float a) const {
    // TBD
    return Mat4();
}

Mat4& Mat4::scale(const float a) {
    // TBD
    return *this;
}

Mat4 Mat4::rotated(const Vec3& axis, const float angle) const {
    // TBD
    return Mat4();
}

Mat4& Mat4::rotate(const Vec3& axis, const float angle) {
    // TBD
    return *this;
}

Mat4 Mat4::multiplied(const Vec3& v) const {
    // TBD
    return Mat4();
}

Mat4& Mat4::multiply(const Vec3& v) {
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
    // TBD
    return Mat4();
}

Mat4 operator-(const Mat4& a, const Mat4& b) {
    // TBD
    return Mat4();
}

Mat4 operator*(const Mat4& a, const Mat4& b) {
    // TBD
    return Mat4();
}

Mat4 operator*(const Mat4& m, const Vec3& v) {
    // TBD
    return Mat4();
}

Mat4 operator-(const Mat4& m) {
    // TBD
    return Mat4();
}

// Mutable operators

Mat4& operator+=(Mat4& a, const Mat4& b) {
    // TBD
    return a;
}

Mat4& operator-=(Mat4& a, const Mat4& b) {
    // TBD
    return a;
}

Mat4& operator*=(Mat4& a, const Mat4& b) {
    // TBD
    return a;
}

}  // namespace Math
}  // namespace Common
}  // namespace SargassoEngine

#endif
