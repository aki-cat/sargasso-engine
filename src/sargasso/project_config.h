#ifndef SARGASSO_PROJECT_CONFIG_H_
#define SARGASSO_PROJECT_CONFIG_H_

#include "sargasso/window/window_config.h"

namespace sargasso {

struct ProjectConfig {
    char projectName[128];
    char version[32];
    window::WindowConfig window;
};

}  // namespace sargasso

#endif  // SARGASSO_PROJECT_CONFIG_H_
