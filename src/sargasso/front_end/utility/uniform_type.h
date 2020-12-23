#ifndef SARGASSO_ENGINE_FRONT_END_UTILITY_UNIFORM_TYPE_H
#define SARGASSO_ENGINE_FRONT_END_UTILITY_UNIFORM_TYPE_H

#include <glad/glad.h>

#include <functional>
#include <unordered_map>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

enum UniformType {
    UNIFORM_FLOAT1,
    UNIFORM_FLOAT2,
    UNIFORM_FLOAT3,
    UNIFORM_FLOAT4,
    UNIFORM_INT1,
    UNIFORM_INT2,
    UNIFORM_INT3,
    UNIFORM_INT4,
    UNIFORM_UINT1,
    UNIFORM_UINT2,
    UNIFORM_UINT3,
    UNIFORM_UINT4,
    UNIFORM_FLOAT1_ARRAY,
    UNIFORM_FLOAT2_ARRAY,
    UNIFORM_FLOAT3_ARRAY,
    UNIFORM_FLOAT4_ARRAY,
    UNIFORM_INT1_ARRAY,
    UNIFORM_INT2_ARRAY,
    UNIFORM_INT3_ARRAY,
    UNIFORM_INT4_ARRAY,
    UNIFORM_UINT1_ARRAY,
    UNIFORM_UINT2_ARRAY,
    UNIFORM_UINT3_ARRAY,
    UNIFORM_UINT4_ARRAY,
    UNIFORM_MATRIX2,
    UNIFORM_MATRIX3,
    UNIFORM_MATRIX4,
    UNIFORM_MATRIX23,
    UNIFORM_MATRIX32,
    UNIFORM_MATRIX24,
    UNIFORM_MATRIX42,
    UNIFORM_MATRIX34,
    UNIFORM_MATRIX43
};

using UniformSendingFunction = std::function<void(const GLint, const void*, const size_t)>;

class UniformDataSender {
   public:
    UniformDataSender() = delete;
    static const std::unordered_map<UniformType, UniformSendingFunction> send_data;
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
