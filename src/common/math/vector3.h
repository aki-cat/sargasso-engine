#ifndef SARGASSO_ENGINE_COMMON_MATH_VECTOR3_H
#define SARGASSO_ENGINE_COMMON_MATH_VECTOR3_H

#include <cfloat>
#include <cmath>
#include <string>

namespace SargassoEngine {
namespace Common {
namespace Math {

struct Points3 {
    float x, y, z;
};

class Vec3 {
   public:
    Vec3(float _x, float _y, float _z) : x{_points.x}, y{_points.y}, z{_points.z}, _points{} {
        _points.x = _x;
        _points.y = _y;
        _points.z = _z;
    }
    Vec3() : Vec3(0.0f, 0.0f, 0.0f) {}

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

    Vec3 scaled(const float s) const;
    Vec3& scale(const float s);

    // convenient ;
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
    float operator[](const uint32_t n);

   private:
    Points3 _points;
};

// Imutable Operators

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

// Mutable Operators

Vec3& operator*=(Vec3& v, const float a);
Vec3& operator/=(Vec3& v, const float a);
Vec3& operator+=(Vec3& a, const Vec3& b);
Vec3& operator-=(Vec3& a, const Vec3& b);

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

inline const std::string Vec3::to_string() const { return format("(%, %, %)", x, y, z); }

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
inline Vec3& Vec3::normalize() { return *this /= sqrt(*this * *this); }

inline Vec3 Vec3::clamped(const float s) const { return normalized() * s; }
inline Vec3& Vec3::clamp(const float s) { return normalize() *= s; }

inline float Vec3::magnitude() const { return sqrt((*this) * (*this)); }
inline float Vec3::magnitude_squared() const { return *this * *this; }

inline Vec3 Vec3::translated(const Vec3& v) const { return *this + v; }
inline Vec3& Vec3::translate(const Vec3& v) { return *this += v; }

inline Vec3 Vec3::rotated(const Vec3& axis, const float angle) const {
    // TBD
    return Vec3(*this);
}
inline Vec3& Vec3::rotate(const Vec3& axis, const float angle) {
    // TBD
    return *this;
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

bool operator!=(const Vec3& a, const Vec3& b) { return !(a == b); }

Vec3 operator*(const float a, const Vec3& v) { return Vec3(v.x * a, v.y * a, v.z * a); }
Vec3 operator*(const Vec3& v, const float a) { return a * v; }
Vec3 operator/(const Vec3& v, const float a) { return (1 / a) * v; }

Vec3 operator+(const Vec3& a, const Vec3& b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
Vec3 operator-(const Vec3& b) { return -1 * b; }
Vec3 operator-(const Vec3& a, const Vec3& b) { return a + -b; }

float Vec3::operator[](const uint32_t n) {
    switch (n) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        default:
            throw std::out_of_range("Out of range of vector size (0 <= n < 3)");
    }
}

float operator*(const Vec3& a, const Vec3& b) { return a.dot(b); }

Vec3 operator^(const Vec3& a, const Vec3& b) { return a.cross(b); }

// Mutable Operators

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

}  // namespace Math
}  // namespace Common
}  // namespace SargassoEngine

#endif
