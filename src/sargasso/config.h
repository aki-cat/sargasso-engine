#ifndef SARGASSO_ENGINE_CONFIG_H
#define SARGASSO_ENGINE_CONFIG_H

#define ECHO(v)      #v
#define TO_STRING(v) ECHO(v)

#if defined(WIN32) || defined(_WIN32)
#define SARGASSO_WINDOWS 1
#include <windows.h>
#endif

namespace sargasso {

constexpr const char* ENGINE_NAME = "Sargasso Engine";

constexpr const char* ENGINE_VERSION =
#ifdef SARGASSO_ENGINE_VERSION
    TO_STRING(SARGASSO_ENGINE_VERSION);
#else
    "dev";
#endif

}  // namespace sargasso

#undef ECHO
#undef TO_STRING

#endif
