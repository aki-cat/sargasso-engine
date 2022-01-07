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
    {Log::LogLevel::DEBUG, "\033[0m"}};

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
