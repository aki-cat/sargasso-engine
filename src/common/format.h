#ifndef SARGASSO_ENGINE_FORMAT_H
#define SARGASSO_ENGINE_FORMAT_H

#include <sstream>
#include <string>

namespace SargassoEngine {
namespace Common {

constexpr char ESCAPE_CHAR = '%';

template <typename... Args>
struct Format {
    static std::string format(const std::string& fmt, Args... args);
};

template <>
struct Format<> {
    static std::string format(const std::string& fmt) { return fmt; }
};

template <typename T, typename... Args>
struct Format<T, Args...> {
    static std::string format(const std::string& fmt, T value, Args... args);
    Format() = delete;
    Format(const Format&) = delete;
    Format(const Format&&) = delete;
    Format(Format&) = delete;
    Format operator=(Format&) = delete;
};

template <typename... Args>
inline std::string Format<Args...>::format(const std::string& fmt, Args... args) {
    return Format<Args...>::format(fmt, args...);
}

// inline std::string Format<>::format(const std::string& fmt)

template <typename T, typename... Args>
inline std::string Format<T, Args...>::format(const std::string& fmt, T value, Args... args) {
    // Find first escape character
    const uint64_t escape_index = fmt.find(ESCAPE_CHAR);

    // Base case: no escape character
    if (escape_index == std::string::npos) {
        return fmt;
    }

    // Corner case: escape character is escaped
    char next_char = 0;
    if (escape_index + 1 < fmt.size()) {
        next_char = fmt[escape_index + 1];
        if (next_char == ESCAPE_CHAR) {
            std::string before = fmt.substr(0, escape_index + 1);
            std::string after =
                Format<T, Args...>::format(fmt.substr(escape_index + 2), value, args...);
            return before + after;
        }
    }

    // Generic case: escape character is substituted
    std::ostringstream stream{};
    stream << fmt.substr(0, escape_index) << value << fmt.substr(escape_index + 1);
    return Format<Args...>::format(stream.str(), args...);
}

template <typename... Args>
std::string format(const std::string& fmt, Args... args) {
    return Format<Args...>::format(fmt, args...);
}

}  // namespace Common
}  // namespace SargassoEngine

#endif
