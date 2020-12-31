

#include "dummy.h"

#include <btl.h>

DESCRIBE_CLASS(Dummy) {
    DESCRIBE_TEST(operator+=, OnePlusOne, ReturnTwo) {
        Dummy dummy;
        dummy.foo = 1;
        dummy.foo += 1;
        ASSERT_ARE_EQUAL(dummy.foo, 2);
    };

    DESCRIBE_TEST(operator-=, OneMinusOne, ReturnZero) {
        Dummy dummy;
        dummy.foo = 1;
        dummy.foo -= 1;
        ASSERT_ARE_EQUAL(dummy.foo, 0);
    };
}
