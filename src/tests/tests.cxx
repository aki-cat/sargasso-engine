// Force verbosity to be level INFO
#undef LOG_VERBOSITY_LEVEL
#define LOG_VERBOSITY_LEVEL 3
#include "sargasso/common/log.h"

// Include tests now

#include "spec/sample.spec.cxx"

#include <btl.h>

using btl::TestRunner;
using sargasso::common::Log;

int main() {
    Log("TEST RUNNER").info("Starting up...\n");

    // TBD: Remove Dummy class and substitute tests for real ones
    TestRunner<Dummy>::run();

    if (btl::has_errors()) {
        Log("TEST RUNNER").error("Errors occurred!");
        return -1;
    }

    Log("TEST RUNNER").info("Success!");
    return 0;
}
