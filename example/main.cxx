
#include <sargasso/common/log.h>
#include <sargasso/engine.h>
#include <sargasso/project_config.h>
#include <sargasso/window/window_config.h>

int main() {
    sargasso::common::Log logger("Sample");
    logger.info("Starting example project...");

    const sargasso::ProjectConfig projectConfig = {"Example Project\0",
                                                   "1.0",
                                                   sargasso::graphics::EGraphicsBackend::kOpenGL,
                                                   {"Example Project Window\0", 960, 540, 1}};

    sargasso::Engine engine = sargasso::Engine(projectConfig);
    engine.initialize();
    engine.run();
    engine.terminate();

    logger.info("Closing example project...");
}
