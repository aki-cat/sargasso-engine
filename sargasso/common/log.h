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

inline void log_error(const std::string& str) { std::cerr << str << std::endl; }

template <typename... Args>
inline void logf_error(const std::string& fmt, Args... args) {
    log_error(format(fmt, args...));
}

}  // namespace Common
}  // namespace SargassoEngine

#endif
