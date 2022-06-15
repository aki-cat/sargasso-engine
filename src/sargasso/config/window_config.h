#ifndef SARGASSO_WINDOW_WINDOW_CONFIG_H
#define SARGASSO_WINDOW_WINDOW_CONFIG_H

#include <cstdint>

namespace sargasso {
namespace config {

struct WindowConfig {
    char title[128] = "Sargasso Project\0";
    uint32_t width = 960;
    uint32_t height = 540;
    uint8_t msaa = 0;
};

}  // namespace window
}  // namespace sargasso

#endif
