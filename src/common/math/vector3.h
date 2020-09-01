#ifndef SARGASSO_ENGINE_COMMON_MATH_VECTOR3_H
#define SARGASSO_ENGINE_COMMON_MATH_VECTOR3_H

#include <cfloat>
#include <string>

namespace SargassoEngine {
namespace Common {
namespace Math {

constexpr float abs(float v) { return v > 0.0f ? v : -v; }

struct Points3 {
    float x, y, z;
};

class Vec3 {
   public:
    Vec3(float _x, float _y, float _z) : points{}, x{points.x}, y{points.y}, z{points.z} {
        points.x = _x;
        points.y = _y;
        points.z = _z;
    }
    Vec3() : Vec3(0.0f, 0.0f, 0.0f) {}

    // data
    Points3 points;
    float &x, &y, &z;

    // methods
    const std::string to_string() const;

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
};

// Operators

bool operator==(const Vec3& u, const Vec3& v);

Vec3 operator*(const float& a, const Vec3& v);
Vec3 operator*(const Vec3& v, const float& a);

float operator*(const Vec3& u, const Vec3& v);
Vec3 operator^(const Vec3& u, const Vec3& v);

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

// Conversion operators

Vec3::operator std::string() { return to_string(); }

// Binary operators

bool operator==(const Vec3& u, const Vec3& v) {
    return abs(u.x - v.x) < FLT_EPSILON && abs(u.y - v.y) < FLT_EPSILON &&
           abs(u.z - v.z) < FLT_EPSILON;
}

float operator*(const Vec3& u, const Vec3& v) { return (u.x * v.x) + (u.y * v.y) + (u.z * v.z); }

Vec3 operator*(const float& a, const Vec3& v) { return Vec3(v.x * a, v.y * a, v.z * a); }

Vec3 operator*(const Vec3& v, const float& a) { return a * v; }

/*
Cross product

|  i  j  k   |
|  a1 a2 a3  |
|  b1 b2 b3  |
*/
Vec3 operator^(const Vec3& u, const Vec3& v) {
    return Vec3((u.y * v.z) - (u.z * v.y), (u.z * v.x) - (u.x * v.z), (u.x * v.y) - (u.y * v.x));
}

}  // namespace Math
}  // namespace Common
}  // namespace SargassoEngine

#endif
