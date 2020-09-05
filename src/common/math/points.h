#ifndef SARGASSO_ENGINE_COMMON_MATH_POINTS_H
#define SARGASSO_ENGINE_COMMON_MATH_POINTS_H

namespace SargassoEngine {
namespace Common {
namespace Math {

template <uint32_t N>
struct Points {
    float p[N]{};
    static const uint32_t len = N;
    float& operator[](const uint32_t i) {
        static_assert(i >= 0 && i < len, "Point access is out of range.");
        return p[i];
    }
    float operator[](const uint32_t i) const {
        static_assert(i >= 0 && i < len, "Point access is out of range.");
        return p[i];
    }
};

using Points2 = Points<2>;
using Points3 = Points<3>;
using Points4 = Points<4>;

}  // namespace Math
}  // namespace Common
}  // namespace SargassoEngine

#endif
