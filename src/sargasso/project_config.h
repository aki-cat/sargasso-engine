#ifndef SARGASSO_PROJECT_CONFIG_H_
#define SARGASSO_PROJECT_CONFIG_H_

#include "sargasso/graphics/graphics.h"
#include "sargasso/window/window_config.h"

namespace sargasso {

struct ProjectConfig {
    const char projectName[128];
    const char version[32];
    const graphics::EGraphicsBackend graphicsBackend;
    const window::WindowConfig window;
};

}  // namespace sargasso

#endif  // SARGASSO_PROJECT_CONFIG_H_
