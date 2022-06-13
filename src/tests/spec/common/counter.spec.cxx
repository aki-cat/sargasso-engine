#include "sargasso/common/counter.h"

#include <btl.h>

using sargasso::common::Counter;

DESCRIBE_CLASS(sargasso::common::Counter) {
    DESCRIBE_TEST(decrease(), Subtracted at zero, Avoid underflow) {
        Counter foo{};
        foo.decrease();
        ASSERT_IS_TRUE(foo == 0);
    };
}
