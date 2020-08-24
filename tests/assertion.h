#ifndef SARGASSO_ENGINE_TESTS_ASSERTION_H
#define SARGASSO_ENGINE_TESTS_ASSERTION_H

#include <cassert>
#include <stdio.h>

namespace SargassoEngine {
namespace Tests {

#define _SARGASSO_TEST(CLASS_NAME, METHOD_NAME, SITUATION, EXPECTED) \
    printf("\n%s::%s It should %s when %s\n", CLASS_NAME, METHOD_NAME, EXPECTED, SITUATION)

#define _SARGASSO_TEST_PASSED() printf("...OK!\n")

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
