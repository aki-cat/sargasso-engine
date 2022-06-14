#include "sargasso/common/log.h"

#include <cstdio>
#include <unordered_map>

using sargasso::common::Log;

const char* Log::_unused = "\0";

std::string Log::_out = Log::_unused;
std::string Log::_err = Log::_unused;

static const std::unordered_map<Log::LogLevel, const char*> TEXT_COLOR = {
    {Log::LogLevel::ERROR, "\033[91m"},
    {Log::LogLevel::WARNING, "\033[93m"},
    {Log::LogLevel::INFO, "\033[96m"},
    {Log::LogLevel::DEBUG, "\033[94m"}};

static const std::unordered_map<Log::LogLevel, const char*> VERBOSITY_NAME = {
    {Log::LogLevel::ERROR, "ERROR"},
    {Log::LogLevel::WARNING, "WARNING"},
    {Log::LogLevel::INFO, "INFO"},
    {Log::LogLevel::DEBUG, "DEBUG"}};

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

    bool isError = level <= LogLevel::WARNING;
    const std::string& targetPath = isError ? Log::_err : Log::_out;
    bool isStd = targetPath == Log::_unused;

    const char* start = isStd ? TEXT_COLOR.at(level) : "";
    const char* end = isStd ? "\033[0m" : "";

    std::stringstream stream{};
    stream << start << "[" << VERBOSITY_NAME.at(level) << "|" << _name.c_str() << "] " << str << end
           << std::endl;

    if (isStd) {
        (isError ? std::cerr : std::cout) << stream.str();
    } else {
        std::ofstream output(targetPath, std::ios_base::app);
        output << stream.str();
    }
}
