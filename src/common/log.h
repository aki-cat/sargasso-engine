#ifndef SARGASSO_ENGINE_LOG_H
#define SARGASSO_ENGINE_LOG_H

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace SargassoEngine {
namespace Common {

template <typename... Args>
std::string format(const std::string& fmt, Args... args);

template <typename... Args>
struct Format {};

template <>
struct Format<> {
    static std::string format(const std::string& fmt);
};

template <typename T, typename... Args>
struct Format<T, Args...> {
    static std::string format(const std::string& fmt, T value, Args... args);
};

inline std::string Format<>::format(const std::string& fmt) { return fmt; }

template <typename T, typename... Args>
inline std::string Format<T, Args...>::format(const std::string& fmt, T value, Args... args) {
    size_t idx = fmt.find('%');
    char next = 0;
    if (idx != std::string::npos && fmt.size() > idx + 1) {
        next = fmt[idx + 1];
    }
    if (idx != std::string::npos && next != '%') {
        std::ostringstream os;
        os << fmt.substr(0, idx) << value << fmt.substr(idx + 1);
        return Format<Args...>::format(os.str(), args...);
    }
    if (next == '%') {
        std::string before = fmt.substr(0, idx + 1);
        std::string after = Format<T, Args...>::format(fmt.substr(idx + 2), value, args...);
        return before + after;
    }
    return fmt;
}

template <typename... Args>
inline std::string format(const std::string& fmt, Args... args) {
    return Format<Args...>::format(fmt, args...);
}

inline void log(const std::string& str) { std::cout << str << std::endl; }

template <typename... Args>
inline void logf(const std::string& fmt, Args... args) {
    log(format(fmt, args...));
}

}  // namespace Common
}  // namespace SargassoEngine

#endif
