#ifndef SARGASSO_PROJECT_CONFIG_H_
#define SARGASSO_PROJECT_CONFIG_H_

#include "sargasso/config/window_config.h"

namespace sargasso {
namespace config {

struct ProjectConfig {
    char projectName[128];
    char version[32];
    WindowConfig window;
};

}  // namespace config
}  // namespace sargasso

#endif  // SARGASSO_PROJECT_CONFIG_H_
