#ifndef SARGASSO_ENGINE_CONFIG_H
#define SARGASSO_ENGINE_CONFIG_H

#define AS_STRING(v) #v
#define MACRO_AS_STRING(v) AS_STRING(v)

namespace SargassoEngine {

constexpr const char* ENGINE_NAME = "Sargasso Engine";

#ifdef SARGASSO_ENGINE_VERSION
constexpr const char* ENGINE_VERSION = MACRO_AS_STRING(SARGASSO_ENGINE_VERSION);
#else
constexpr const char* ENGINE_VERSION = "Unknown";
#endif

}  // namespace SargassoEngine

#undef AS_STRING
#undef MACRO_AS_STRING

#endif
