#ifndef SARGASSO_COMMON_LOG_H_
#define SARGASSO_COMMON_LOG_H_

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace sargasso {
namespace common {

#ifndef LOG_VERBOSITY_LEVEL
#define LOG_VERBOSITY_LEVEL LogLevel::INFO
#endif

class Log {
   public:
    // Enum
    enum LogLevel { SILENT = 0, ERROR = 1, WARNING = 2, INFO = 3, DEBUG = 4 };

    // Class constants
    static const LogLevel VERBOSITY = static_cast<LogLevel>(LOG_VERBOSITY_LEVEL);
    static const uint64_t BUFFER_SIZE = 1024;

    // Constructors
    Log();
    Log(const std::string& name);

    // Methods
    template <typename... T>
    void error(const char* fmt, T... data) const;
    void error(const char* str) const;

    template <typename... T>
    void warning(const char* fmt, T... data) const;
    void warning(const char* str) const;

    template <typename... T>
    void info(const char* fmt, T... data) const;
    void info(const char* str) const;

    template <typename... T>
    void debug(const char* fmt, T... data) const;
    void debug(const char* str) const;

    // Generic log method (covers all cases)
    template <typename... T>
    constexpr void printf(LogLevel level, const char* fmt, T... data) const;
    void print(LogLevel level, const char* str) const;

    // Output setters
    static void setLogStream(const std::string& file_path);
    static void unsetLogStream();
    static void setErrorStream(const std::string& file_path);
    static void unsetErrorStream();

   private:
    // Data
    const std::string _name;

    // Output pointers
    static std::string _out;
    static std::string _err;

    static const char* _unused;
};

// Constructors

inline Log::Log() : _name("<unnamed>") {}
inline Log::Log(const std::string& name) : _name(name) {}

// Log Methods

template <typename... T>
inline void Log::error(const char* fmt, T... data) const {
    this->printf(LogLevel::ERROR, fmt, data...);
}

inline void Log::error(const char* str) const {
    this->print(LogLevel::ERROR, str);
}

template <typename... T>
inline void Log::warning(const char* fmt, T... data) const {
    this->printf(LogLevel::WARNING, fmt, data...);
}
inline void Log::warning(const char* str) const {
    this->print(LogLevel::WARNING, str);
}

template <typename... T>
inline void Log::info(const char* fmt, T... data) const {
    this->printf(LogLevel::INFO, fmt, data...);
}
inline void Log::info(const char* str) const {
    this->print(LogLevel::INFO, str);
}

template <typename... T>
inline void Log::debug(const char* fmt, T... data) const {
    this->printf(LogLevel::DEBUG, fmt, data...);
}
inline void Log::debug(const char* str) const {
    this->print(LogLevel::DEBUG, str);
}

template <typename... T>
constexpr void Log::printf(Log::LogLevel level, const char* fmt, T... data) const {
    if (level > Log::VERBOSITY) {
        return;
    }
    char fmt_buffer[Log::BUFFER_SIZE]{};
    std::snprintf(fmt_buffer, Log::BUFFER_SIZE, fmt, data...);
    this->print(level, fmt_buffer);
}

// Output stream methods

}  // namespace common
}  // namespace sargasso

#undef LOG_VERBOSITY_LEVEL

#endif  // SARGASSO_COMMON_LOG_H_
