#include "sargasso/common/log.h"

#include <cstdio>
#include <unordered_map>

using sargasso::common::Log;

const char* Log::_unused = "\0";
std::string Log::_out = Log::_unused;
std::string Log::_err = Log::_unused;

static constexpr const char* getTextColor(Log::LogLevel level) {
    switch (level) {
        case Log::LogLevel::kError:
            return "\033[91m";
        case Log::LogLevel::kWarning:
            return "\033[93m";
        case Log::LogLevel::kInfo:
            return "\033[96m";
        case Log::LogLevel::kDebug:
            return "\033[94m";
        default:
            throw std::out_of_range("Invalid LogLevel value");
    }
}

static constexpr const char* getVerbosityName(Log::LogLevel level) {
    switch (level) {
        case Log::LogLevel::kError:
            return "ERROR";
        case Log::LogLevel::kWarning:
            return "WARNING";
        case Log::LogLevel::kInfo:
            return "INFO";
        case Log::LogLevel::kDebug:
            return "DEBUG";
        default:
            throw std::out_of_range("Invalid LogLevel value");
    }
}

void Log::setLogStream(const std::string& file_path) {
    Log::_out = file_path;
}

void Log::unsetLogStream() {
    Log::_out = Log::_unused;
}

void Log::setErrorStream(const std::string& file_path) {
    Log::_err = file_path;
}

void Log::unsetErrorStream() {
    Log::_err = Log::_unused;
}

void Log::print(Log::LogLevel level, const char* str) const {
    if (level > Log::VERBOSITY) {
        return;
    }

    bool isError = level <= LogLevel::kWarning;
    const std::string& targetPath = isError ? Log::_err : Log::_out;
    bool isStd = targetPath == Log::_unused;

    const char* start = isStd ? getTextColor(level) : "";
    const char* end = isStd ? "\033[0m" : "";

    std::stringstream stream{};
    stream << start << "[" << getVerbosityName(level) << "|" << _name.c_str() << "] " << str << end
           << std::endl;

    if (isStd) {
        (isError ? std::cerr : std::cout) << stream.str();
    } else {
        std::ofstream output(targetPath, std::ios_base::app);
        output << stream.str();
    }
}
