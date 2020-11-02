#ifndef SARGASSO_ENGINE_COMMON_MATH_POINTS_H
#define SARGASSO_ENGINE_COMMON_MATH_POINTS_H

#include <cassert>
#include <cstdint>

namespace SargassoEngine {
namespace Common {
namespace Math {

template <uint32_t N>
struct Points {
    float p[N]{};
    static const uint32_t len = N;
    float& operator[](const uint32_t i) {
        assert(i >= 0 && i < len);
        return p[i];
    }
    float operator[](const uint32_t i) const {
        assert(i >= 0 && i < len);
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
