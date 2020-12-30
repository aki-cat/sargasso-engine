#include "sargasso/common/log.h"

#include <cstdio>
#include <unordered_map>

using sargasso::common::Log;

// Global helper for laziness
const Log Log::global = Log();

char Log::fmt_buffer[Log::buffer_size] = {};

std::FILE* Log::out = stdout;
std::FILE* Log::err = stderr;

const std::unordered_map<Log::LogLevel, const char*> Log::text_color = {
    {Log::LogLevel::ERROR, "\033[91m"},
    {Log::LogLevel::WARNING, "\033[93m"},
    {Log::LogLevel::INFO, "\033[96m"},
    {Log::LogLevel::DEBUG, "\033[0m"}};
