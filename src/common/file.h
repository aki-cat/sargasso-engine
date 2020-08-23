#ifndef SARGASSO_ENGINE_FILE_H
#define SARGASSO_ENGINE_FILE_H

#include <fstream>

namespace SargassoEngine {
namespace Common {

class File {
   public:
    static const std::string read_file(const std::string& file_path);
};

}  // namespace Common
}  // namespace SargassoEngine

#endif
