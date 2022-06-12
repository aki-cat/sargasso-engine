#include "sargasso/common/counter.h"

#include <btl.h>

using sargasso::common::Counter;

DESCRIBE_CLASS(sargasso::common::Counter) {
    DESCRIBE_TEST(operator--, Subtracted at zero, Avoid underflow) {
        Counter foo{};
        --foo;
        ASSERT_IS_TRUE(foo == 0);
    };
}
