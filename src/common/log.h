#ifndef SARGASSO_ENGINE_LOG_H
#define SARGASSO_ENGINE_LOG_H

#include <stdio.h>

template <typename... Ts>
void Log(const char* fmt, Ts... args) {
    printf(fmt, args...);
}

#endif
