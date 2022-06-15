#ifndef SARGASSO_CONFIG_H_
#define SARGASSO_CONFIG_H_

#include <cstdint>

namespace sargasso {
namespace window {

struct WindowConfig {
    char title[128] = "Sargasso Project\0";
    uint32_t width = 960;
    uint32_t height = 540;
    uint8_t msaa = 0;
};

}  // namespace window
}  // namespace sargasso

#endif  // SARGASSO_CONFIG_H_
