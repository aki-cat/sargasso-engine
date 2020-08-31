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

    Points3 points;
    float &x, &y, &z;

    // convenient orthogonal directions
    static Vec3 zero() { return Vec3(); }
    static Vec3 up() { return Vec3(+0.0f, +1.0f, +0.0f); }
    static Vec3 down() { return Vec3(+0.0f, -1.0f, +0.0f); }
    static Vec3 front() { return Vec3(+0.0f, +0.0f, -1.0f); }
    static Vec3 back() { return Vec3(+0.0f, +0.0f, +1.0f); }
    static Vec3 left() { return Vec3(-1.0f, +0.0f, +0.0f); }
    static Vec3 right() { return Vec3(+1.0f, +0.0f, +0.0f); }

    // operators
    bool operator==(const Vec3& v) {
        return abs(x - v.x) < FLT_EPSILON && abs(y - v.y) < FLT_EPSILON &&
               abs(z - v.z) < FLT_EPSILON;
    }

    float operator*(const Vec3& v) { return (x * v.x) + (y * v.y) + (z * v.z); }

    Vec3 operator*(const float& s) { return Vec3(x * s, y * s, z * s); }

    operator std::string() const { return to_string(); }
    // methods

    const std::string to_string() const { return format("(%, %, %)", x, y, z); }
};

}  // namespace Math
}  // namespace Common
}  // namespace SargassoEngine

#endif
