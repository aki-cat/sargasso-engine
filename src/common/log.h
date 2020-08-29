#ifndef SARGASSO_ENGINE_LOG_H
#define SARGASSO_ENGINE_LOG_H

#include "common/format.h"

#include <iostream>

namespace SargassoEngine {
namespace Common {

inline void log(const std::string& str) { std::cout << str << std::endl; }

template <typename... Args>
inline void logf(const std::string& fmt, Args... args) {
    log(format(fmt, args...));
}

}  // namespace Common
}  // namespace SargassoEngine

#endif
