#include "sargasso/common/log.h"

#include <cstdio>
#include <unordered_map>

using sargasso::common::Log;

const char* Log::_unused = "\0";

std::string Log::_out = Log::_unused;
std::string Log::_err = Log::_unused;

const std::unordered_map<Log::LogLevel, const char*> Log::_text_color = {
    {Log::LogLevel::ERROR, "\033[91m"},
    {Log::LogLevel::WARNING, "\033[93m"},
    {Log::LogLevel::INFO, "\033[96m"},
    {Log::LogLevel::DEBUG, "\033[94m"}};

const std::unordered_map<Log::LogLevel, const char*> VERBOSITY_NAME = {
    {Log::LogLevel::ERROR, "ERROR"},
    {Log::LogLevel::WARNING, "WARNING"},
    {Log::LogLevel::INFO, "INFO"},
    {Log::LogLevel::DEBUG, "DEBUG"}};

void Log::set_log_stream(const std::string& file_path) {
    Log::_out = file_path;
}

void Log::unset_log_stream() {
    Log::_out = Log::_unused;
}

void Log::set_err_stream(const std::string& file_path) {
    Log::_err = file_path;
}

void Log::unset_err_stream() {
    Log::_err = Log::_unused;
}

bool Log::is_stdout() {
    return Log::_out == Log::_unused;
}

bool Log::is_stderr() {
    return Log::_err == Log::_unused;
}

void Log::print(Log::LogLevel level, const char* str) const {
    if (level > Log::VERBOSITY) {
        return;
    }

    bool is_error = level <= LogLevel::WARNING;
    const std::string& target_path = is_error ? Log::_err : Log::_out;
    bool is_std = target_path == Log::_unused;

    const char* start = is_std ? Log::_text_color.at(level) : "";
    const char* end = is_std ? "\033[0m" : "";

    std::stringstream stream{};
    stream << start << "[" << VERBOSITY_NAME.at(level) << "|" << _name.c_str() << "] " << str << end
           << std::endl;

    if (is_std) {
        (is_error ? std::cerr : std::cout) << stream.str();
    } else {
        std::ofstream output(target_path, std::ios_base::app);
        output << stream.str();
    }
}
