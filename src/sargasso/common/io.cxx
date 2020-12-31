#include "sargasso/common/io.h"

#include "sargasso/common/log.h"

#include <fstream>
#include <sstream>
#include <string>

using sargasso::common::IO;
using sargasso::common::Log;

void IO::write(const std::string& file_path, const char* data, size_t data_size) {
    std::fstream file(file_path, std::ios::out);

    if (!file.is_open()) {
        Log("IO").error("Failed to open file '%s' for writing.", file_path.c_str());
        return;
    }
    file.write(data, data_size);
    file.close();
}

const std::string IO::read(const std::string& file_path) {
    std::fstream file(file_path, std::ios::in);

    if (!file.is_open()) {
        Log("IO").error("Failed to open file '%s' for reading: %s", file_path.c_str());
        return "";
    }

    std::stringstream stream;
    std::string line;
    while (file) {
        std::getline(file, line);
        stream << line;
    }

    file.close();
    return stream.str();
}
