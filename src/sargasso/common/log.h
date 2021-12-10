#ifndef SARGASSO_COMMON_LOG_H_
#define SARGASSO_COMMON_LOG_H_

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>

namespace sargasso {
namespace common {

#ifndef LOG_VERBOSITY_LEVEL
#define LOG_VERBOSITY_LEVEL LogLevel::INFO
#endif

class Log {
   public:
    // Log Level enum
    enum LogLevel { SILENT = 0, ERROR = 1, WARNING = 2, INFO = 3, DEBUG = 4 };

    static const LogLevel VERBOSITY = static_cast<LogLevel>(LOG_VERBOSITY_LEVEL);
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
    constexpr void print(LogLevel level, const char* str) const;

    // Global helper for laziness
    static const size_t buffer_size = 1024;

    // Output setters
    static void set_log_stream(const std::string& file_path);
    static void unset_log_stream();
    static void set_err_stream(const std::string& file_path);
    static void unset_err_stream();

   private:
    // Data
    const std::string _name;

    // Formatting buffer
    static char fmt_buffer[buffer_size];

    // Output pointers
    static std::FILE* out;
    static std::FILE* err;

    static const std::unordered_map<LogLevel, const char*> text_color;
};

// Constructors

inline Log::Log() : _name("<unnamed>") {}
inline Log::Log(const std::string& name) : _name(name) {}

// Log Methods

template <typename... T>
inline void Log::error(const char* fmt, T... data) const {
    printf(LogLevel::ERROR, fmt, data...);
}

inline void Log::error(const char* str) const {
    print(LogLevel::ERROR, str);
}

template <typename... T>
inline void Log::warning(const char* fmt, T... data) const {
    printf(LogLevel::WARNING, fmt, data...);
}
inline void Log::warning(const char* str) const {
    print(LogLevel::WARNING, str);
}

template <typename... T>
inline void Log::info(const char* fmt, T... data) const {
    printf(LogLevel::INFO, fmt, data...);
}
inline void Log::info(const char* str) const {
    print(LogLevel::INFO, str);
}

template <typename... T>
inline void Log::debug(const char* fmt, T... data) const {
    printf(LogLevel::DEBUG, fmt, data...);
}
inline void Log::debug(const char* str) const {
    print(LogLevel::DEBUG, str);
}

template <typename... T>
constexpr void Log::printf(Log::LogLevel level, const char* fmt, T... data) const {
    if (level > Log::VERBOSITY) {
        return;
    }
    std::sprintf(fmt_buffer, fmt, data...);
    print(level, fmt_buffer);
}

constexpr void Log::print(Log::LogLevel level, const char* str) const {
    if (level > Log::VERBOSITY) {
        return;
    }
    FILE* output = (level <= LogLevel::WARNING) ? Log::err : Log::out;
    bool colored_text = (output == stdout || output == stderr);
    const char* start = colored_text ? Log::text_color.at(level) : "";
    const char* end = colored_text ? "\033[0m" : "";
    std::fprintf(output, "%s[%s] %s%s\n", start, _name.c_str(), str, end);
}

// Output stream methods

inline void Log::set_log_stream(const std::string& file_path) {
    std::FILE* file = std::fopen(file_path.c_str(), "w");

    if (file == nullptr) {
        Log("Log").error("Failed to open file '%s' for writing: %s", file_path.c_str(),
                         std::strerror(errno));
        return;
    }

    std::fclose(out);
    out = file;
}

inline void Log::unset_log_stream() {
    std::fclose(out);
    out = stdout;
}

inline void Log::set_err_stream(const std::string& file_path) {
    std::FILE* file = std::fopen(file_path.c_str(), "w");

    if (file == nullptr) {
        Log("Log").error("Failed to open file '%s' for writing: %s", file_path.c_str(),
                         std::strerror(errno));
        return;
    }

    std::fclose(err);
    err = file;
}

inline void Log::unset_err_stream() {
    std::fclose(err);
    err = stderr;
}

}  // namespace common
}  // namespace sargasso

#undef LOG_VERBOSITY_LEVEL

#endif  // SARGASSO_COMMON_LOG_H_
