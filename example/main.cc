
#include <sargasso/common/log.h>
#include <sargasso/engine.h>

using sargasso::common::Log;

int main() {
    Log logger = Log("MAIN");
    logger.info("Starting sample...");

    sargasso::Engine engine = sargasso::Engine();
    engine.run();

    logger.info("Closing sample...");
}
