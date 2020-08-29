#ifndef SARGASSO_ENGINE_TESTS_ASSERTION_H
#define SARGASSO_ENGINE_TESTS_ASSERTION_H

#include "common/log.h"

#include <cassert>

namespace SargassoEngine {
namespace Tests {

#define _SARGASSO_TEST(CLASS_NAME, METHOD_NAME, SITUATION, EXPECTED) \
    logf("%::%() -> It should % when %", CLASS_NAME, METHOD_NAME, EXPECTED, SITUATION)

#define _SARGASSO_TEST_PASSED() log("...OK!")

#define assert_throws(expr, exception_t) \
    {                                    \
        int throws = -1;                 \
        try {                            \
            expr;                        \
            throws = 0;                  \
        } catch (exception_t) {          \
            throws = 1;                  \
        }                                \
        assert(throws == 1);             \
    }

}  // namespace Tests
}  // namespace SargassoEngine

#endif
