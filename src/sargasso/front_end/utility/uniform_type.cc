
#include "sargasso/front_end/utility/uniform_type.h"

using namespace SargassoEngine::FrontEnd::Utility;

const std::unordered_map<UniformType, UniformSendingFunction> UniformDataSender::send_data = {
    {UniformType::UNIFORM_FLOAT1,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniform1f(uniform_location, values[0]);
     }},
    {UniformType::UNIFORM_FLOAT2,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniform2f(uniform_location, values[0], values[1]);
     }},
    {UniformType::UNIFORM_FLOAT3,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniform3f(uniform_location, values[0], values[1], values[2]);
     }},
    {UniformType::UNIFORM_FLOAT4,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniform4f(uniform_location, values[0], values[1], values[2], values[3]);
     }},
    {UniformType::UNIFORM_INT1,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLint* values = reinterpret_cast<const GLint*>(data);
         glUniform1i(uniform_location, values[0]);
     }},
    {UniformType::UNIFORM_INT2,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLint* values = reinterpret_cast<const GLint*>(data);
         glUniform2i(uniform_location, values[0], values[1]);
     }},
    {UniformType::UNIFORM_INT3,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLint* values = reinterpret_cast<const GLint*>(data);
         glUniform3i(uniform_location, values[0], values[1], values[2]);
     }},
    {UniformType::UNIFORM_INT4,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLint* values = reinterpret_cast<const GLint*>(data);
         glUniform4i(uniform_location, values[0], values[1], values[2], values[3]);
     }},
    {UniformType::UNIFORM_UINT1,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLuint* values = reinterpret_cast<const GLuint*>(data);
         glUniform1ui(uniform_location, values[0]);
     }},
    {UniformType::UNIFORM_UINT2,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLuint* values = reinterpret_cast<const GLuint*>(data);
         glUniform2ui(uniform_location, values[0], values[1]);
     }},
    {UniformType::UNIFORM_UINT3,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLuint* values = reinterpret_cast<const GLuint*>(data);
         glUniform3ui(uniform_location, values[0], values[1], values[2]);
     }},
    {UniformType::UNIFORM_UINT4,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLuint* values = reinterpret_cast<const GLuint*>(data);
         glUniform4ui(uniform_location, values[0], values[1], values[2], values[3]);
     }},
    {UniformType::UNIFORM_FLOAT1_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniform1fv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_FLOAT2_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniform2fv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_FLOAT3_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniform3fv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_FLOAT4_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniform4fv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_INT1_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLint* values = reinterpret_cast<const GLint*>(data);
         glUniform1iv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_INT2_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLint* values = reinterpret_cast<const GLint*>(data);
         glUniform2iv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_INT3_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLint* values = reinterpret_cast<const GLint*>(data);
         glUniform3iv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_INT4_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLint* values = reinterpret_cast<const GLint*>(data);
         glUniform4iv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_UINT1_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLuint* values = reinterpret_cast<const GLuint*>(data);
         glUniform1uiv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_UINT2_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLuint* values = reinterpret_cast<const GLuint*>(data);
         glUniform2uiv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_UINT3_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLuint* values = reinterpret_cast<const GLuint*>(data);
         glUniform3uiv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_UINT4_ARRAY,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLuint* values = reinterpret_cast<const GLuint*>(data);
         glUniform4uiv(uniform_location, data_count, values);
     }},
    {UniformType::UNIFORM_MATRIX2,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniformMatrix2fv(uniform_location, data_count, GL_FALSE, values);
     }},
    {UniformType::UNIFORM_MATRIX3,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniformMatrix3fv(uniform_location, data_count, GL_FALSE, values);
     }},
    {UniformType::UNIFORM_MATRIX4,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniformMatrix4fv(uniform_location, data_count, GL_FALSE, values);
     }},
    {UniformType::UNIFORM_MATRIX23,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniformMatrix2x3fv(uniform_location, data_count, GL_FALSE, values);
     }},
    {UniformType::UNIFORM_MATRIX32,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniformMatrix3x2fv(uniform_location, data_count, GL_FALSE, values);
     }},
    {UniformType::UNIFORM_MATRIX24,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniformMatrix2x4fv(uniform_location, data_count, GL_FALSE, values);
     }},
    {UniformType::UNIFORM_MATRIX42,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniformMatrix4x2fv(uniform_location, data_count, GL_FALSE, values);
     }},
    {UniformType::UNIFORM_MATRIX34,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniformMatrix3x4fv(uniform_location, data_count, GL_FALSE, values);
     }},
    {UniformType::UNIFORM_MATRIX43,
     [](const GLint uniform_location, const void* data, const size_t data_count) {
         const GLfloat* values = reinterpret_cast<const GLfloat*>(data);
         glUniformMatrix4x3fv(uniform_location, data_count, GL_FALSE, values);
     }}};
