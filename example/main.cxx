
#include <sargasso/common/log.h>
#include <sargasso/config/project_config.h>
#include <sargasso/config/window_config.h>
#include <sargasso/engine.h>

using sargasso::common::Log;

int main() {
    Log logger = Log("Sample");
    logger.info("Starting example project...");

    const sargasso::config::ProjectConfig projectConfig = {
        "Example Project\0", "1.0", {"Example Project Window\0", 960, 540, 1}};

    sargasso::Engine engine = sargasso::Engine(projectConfig);
    engine.setup();
    engine.run();
    engine.terminate();

    logger.info("Closing example project...");
}
