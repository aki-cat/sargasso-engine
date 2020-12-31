#ifndef SARGASSO_ENGINE_CONFIG_H
#define SARGASSO_ENGINE_CONFIG_H

#define AS_STRING(v)       #v
#define MACRO_AS_STRING(v) AS_STRING(v)

namespace sargasso {

constexpr const char* ENGINE_NAME = "Sargasso Engine";

constexpr const char* ENGINE_VERSION =
#ifdef SARGASSO_ENGINE_VERSION
    MACRO_AS_STRING(SARGASSO_ENGINE_VERSION);
#else
    "Unknown";
#endif

}  // namespace sargasso

#undef AS_STRING
#undef MACRO_AS_STRING

#endif
