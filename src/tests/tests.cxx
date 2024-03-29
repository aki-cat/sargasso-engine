// Force verbosity to be level INFO
#undef LOG_VERBOSITY_LEVEL
#define LOG_VERBOSITY_LEVEL 3
#include "sargasso/common/log.h"

// Include tests now

#include "spec/common/counter.spec.cxx"
#include "spec/common/reference.spec.cxx"

#include <btl.h>

using btl::TestRunner;
using sargasso::common::Log;

int main() {
    Log logger("TestRunner");
    logger.info("Starting up...\n");

    TestRunner<sargasso::common::Counter>::run();
    TestRunner<sargasso::common::Reference<test::Type>>::run();

    if (btl::has_errors()) {
        logger.error("Errors occurred!\n");
        return -1;
    }

    logger.info("Success!\n");
    return 0;
}
