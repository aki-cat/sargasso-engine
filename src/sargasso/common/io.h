#ifndef SARGASSO_COMMON_IO_H_
#define SARGASSO_COMMON_IO_H_

#include <string>

namespace sargasso {
namespace common {

class IO {
   public:
    IO() = delete;
    static void write(const std::string& file_path, const char* data, size_t data_size);
    static const std::string read(const std::string& file_path);
};

}  // namespace common
}  // namespace sargasso

#endif
