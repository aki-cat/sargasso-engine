#include "sargasso/common/io.h"

#include "sargasso/common/log.h"

#include <fstream>
#include <sstream>
#include <string>

using sargasso::common::IO;
using sargasso::common::Log;

static const Log logger("IO");

void IO::write(const std::string& filePath, const char* data, size_t dataSize) {
    std::fstream file(filePath, std::ios::out);

    if (!file.is_open()) {
        logger.error("Failed to open file '%s' for writing.", filePath.c_str());
        return;
    }
    file.write(data, dataSize);
    file.close();
}

const std::string IO::read(const std::string& filePath) {
    std::fstream file(filePath, std::ios::in);

    if (!file.is_open()) {
        logger.error("Failed to open file '%s' for reading: %s", filePath.c_str());
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
