#include "sargasso/common/reference.h"

#include <btl.h>
#include <type_traits>

using sargasso::common::Reference;

struct Example {
    int x, y;
};

DESCRIBE_CLASS(Reference<Example>) {
    DESCRIBE_TEST(operator->, Accessed public member, Return expected value) {
        Example* foo = new Example{3, 4};
        auto foo_reference = Reference<Example>(0, foo);
        ASSERT_ARE_EQUAL(foo_reference->x, 3);
    };

    DESCRIBE_TEST(operator->, Accessed public member, Return same reference value) {
        Example* foo = new Example{3, 4};
        auto foo_reference = Reference<Example>(1, foo);
        ASSERT_ARE_SAME(foo_reference->x, foo->x);
    };

    DESCRIBE_TEST(operator->, Original data changed, Update data inside reference) {
        Example* foo = new Example{3, 4};
        auto foo_reference = Reference<Example>(2, foo);
        foo->x = 99;
        ASSERT_ARE_EQUAL(foo_reference->x, 99);
    };

    DESCRIBE_TEST(operator->, Changed data via reference, Update original data) {
        Example* foo = new Example{3, 4};
        auto foo_reference = Reference<Example>(3, foo);
        foo_reference->x = 99;
        ASSERT_ARE_EQUAL(foo->x, 99);
    };

    DESCRIBE_TEST(destroy(), Method called, Destroy object) {
        Example* foo = new Example{3, 4};
        auto foo_reference = Reference<Example>(4, foo);
        const Reference<Example> second_ref = foo_reference;

        foo_reference.destroy();

        ASSERT_IS_TRUE(foo_reference.is_dead());
    };

    DESCRIBE_TEST(std::is_trivially_copy_assignable, Checked by compiler, Return false) {
        ASSERT_IS_FALSE(std::is_trivially_copy_assignable<Reference<Example>>());
    };

    DESCRIBE_TEST(operator--, Subtract at zero, Underflow does not happen) {
        sargasso::common::Counter foo{};
        --foo;
        ASSERT_IS_TRUE(foo == 0);
    };


}
