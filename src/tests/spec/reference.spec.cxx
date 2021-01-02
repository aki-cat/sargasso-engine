#include "sargasso/common/reference.h"

#include <btl.h>
#include <type_traits>

using sargasso::common::Reference;

struct Example {
    int x, y;
};

DESCRIBE_CLASS(Reference<Example>) {
    DESCRIBE_TEST(operator->, Accessed public member, Return expected value) {
        Example foo = {3, 4};
        auto foo_reference = Reference<Example>(0, foo);
        ASSERT_ARE_EQUAL(foo_reference->x, 3);
    };

    DESCRIBE_TEST(operator->, Accessed public member, Return same reference value) {
        Example foo = {3, 4};
        auto foo_reference = Reference<Example>(0, foo);
        ASSERT_ARE_SAME(foo_reference->x, foo.x);
    };

    DESCRIBE_TEST(operator->, Original data changed, Update data inside reference) {
        Example foo = {3, 4};
        auto foo_reference = Reference<Example>(0, foo);
        foo.x = 99;
        ASSERT_ARE_EQUAL(foo_reference->x, 99);
    };

    DESCRIBE_TEST(operator->, Changed data via reference, Update original data) {
        Example foo = {3, 4};
        auto foo_reference = Reference<Example>(0, foo);
        foo_reference->x = 99;
        ASSERT_ARE_EQUAL(foo.x, 99);
    };

    DESCRIBE_TEST(std::is_trivially_copyable, Checked by compiler, Return true) {
        ASSERT_IS_TRUE(std::is_trivially_copyable<Reference<Example>>());
    };
}
