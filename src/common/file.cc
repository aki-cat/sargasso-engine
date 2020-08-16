
#include "common/file.h"

#include <iostream>
#include <sstream>

using SargassoEngine::Common::File;

constexpr const char* FILE_READ_ERROR = "Could not open file: ";

const std::string File::read_file(const std::string& file_path) {
    std::cout << "Reading file: " << file_path << std::endl;

    std::string contents;
    std::ifstream contents_stream = std::ifstream(file_path, std::ios::in);
    if (contents_stream.is_open()) {
        std::stringstream sstr;
        sstr << contents_stream.rdbuf();
        contents = sstr.str();
        contents_stream.close();
    } else {
        std::cerr << FILE_READ_ERROR << file_path << std ::endl;
        return 0;
    }
    return contents;
}
