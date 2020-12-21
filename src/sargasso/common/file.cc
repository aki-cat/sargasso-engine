
#include "sargasso/common/file.h"

#include "sargasso/common/log.h"

#include <sstream>
#include <stdexcept>

using namespace SargassoEngine::Common;

constexpr const char* FILE_READ_ERROR = "Could not open file: %";

const std::string File::read_file(const std::string& file_path) {
    std::string contents;
    std::ifstream contents_stream = std::ifstream(file_path, std::ios::in);
    if (contents_stream.is_open()) {
        std::stringstream sstr;
        sstr << contents_stream.rdbuf();
        contents = sstr.str();
        contents_stream.close();
    } else {
        throw std::runtime_error(format(FILE_READ_ERROR, file_path));
    }
    return contents;
}
