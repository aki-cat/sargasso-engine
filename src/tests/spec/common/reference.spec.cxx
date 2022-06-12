#include "sargasso/common/reference.h"

#include <btl.h>

using sargasso::common::Reference;

namespace test {
struct Type {
    int x, y;
};
}  // namespace test

DESCRIBE_CLASS(sargasso::common::Reference<test::Type>) {
    DESCRIBE_TEST(operator->, Accessed public member, Return expected value) {
        test::Type* foo = new test::Type{3, 4};
        auto foo_reference = Reference<test::Type>(foo);
        ASSERT_ARE_EQUAL(foo_reference->x, 3);
    };

    DESCRIBE_TEST(operator->, Accessed public member, Return same reference value) {
        test::Type* foo = new test::Type{3, 4};
        auto foo_reference = Reference<test::Type>(foo);
        ASSERT_ARE_SAME(foo_reference->x, foo->x);
    };

    DESCRIBE_TEST(operator->, Original data changed, Update data inside reference) {
        test::Type* foo = new test::Type{3, 4};
        auto foo_reference = Reference<test::Type>(foo);
        foo->x = 99;
        ASSERT_ARE_EQUAL(foo_reference->x, 99);
    };

    DESCRIBE_TEST(operator->, Changed data via reference, Update original data) {
        test::Type* foo = new test::Type{3, 4};
        auto foo_reference = Reference<test::Type>(foo);
        foo_reference->x = 99;
        ASSERT_ARE_EQUAL(foo->x, 99);
    };

    DESCRIBE_TEST(destroy, Method called, Destroy object) {
        test::Type* foo = new test::Type{3, 4};
        auto foo_reference = Reference<test::Type>(foo);
        const Reference<test::Type> second_ref = foo_reference;

        foo_reference.destroy();

        ASSERT_IS_TRUE(second_ref.is_dead());
    };
}
