#ifndef SARGASSO_COMMON_IO_H_
#define SARGASSO_COMMON_IO_H_

#include <string>

namespace sargasso {
namespace common {

class IO {
   public:
    IO() = delete;
    static void write(const std::string& filePath, const char* data, size_t dataSize);
    static const std::string read(const std::string& filePath);
};

}  // namespace common
}  // namespace sargasso

#endif
