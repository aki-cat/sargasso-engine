#ifndef SARGASSO_COMMON_IO_H_
#define SARGASSO_COMMON_IO_H_

#include <filesystem>
#include <string>

namespace sargasso {
namespace common {

class IO {
   public:
    IO() = delete;
    static void write(const std::filesystem::path& filePath, const char* data, size_t dataSize);
    static const std::string read(const std::filesystem::path& filePath);
};

}  // namespace common
}  // namespace sargasso

#endif
