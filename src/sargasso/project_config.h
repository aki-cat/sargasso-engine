#ifndef SARGASSO_PROJECT_CONFIG_H_
#define SARGASSO_PROJECT_CONFIG_H_

#include <cstdint>

namespace sargasso {

struct ProjectConfig {
    const char projectName[128];
    const char organizationName[128];
    const char version[32];
    const uint windowWidth;
    const uint windowHeight;
    const uint ppu; // pixels per unit
    const uint msaa;
};

}  // namespace sargasso

#endif  // SARGASSO_PROJECT_CONFIG_H_
