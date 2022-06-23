#ifndef SARGASSO_PROJECT_CONFIG_H_
#define SARGASSO_PROJECT_CONFIG_H_

#include <cstdint>

namespace sargasso {

struct ProjectConfig {
    const char projectName[128];
    const char version[32];
    const unsigned int windowWidth;
    const unsigned int windowHeight;
    const unsigned int msaa;
};

}  // namespace sargasso

#endif  // SARGASSO_PROJECT_CONFIG_H_
