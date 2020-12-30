#ifndef SARGASSO_COMMON_IO_H_
#define SARGASSO_COMMON_IO_H_

namespace sargasso {
namespace common {

class IO {
   public:
    IO() = delete;
    static const std::string write(const std::string& file_path, const char* data);
    static const std::string read(const std::string& file_path);
};

}  // namespace common
}  // namespace sargasso

#endif
