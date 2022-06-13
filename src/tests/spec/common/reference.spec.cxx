#include "sargasso/common/reference.h"

#include <btl.h>

using sargasso::common::Reference;

namespace test {
struct Type {
    int x, y;
};
}  // namespace test

DESCRIBE_CLASS(sargasso::common::Reference<test::Type>) {
    DESCRIBE_TEST(operator->(), Accessed public member, Return expected value) {
        test::Type* foo = new test::Type{3, 4};
        auto foo_reference = Reference<test::Type>(foo);
        ASSERT_ARE_EQUAL(foo_reference->x, 3);
    };

    DESCRIBE_TEST(operator->(), Accessed public member, Return same reference value) {
        test::Type* foo = new test::Type{3, 4};
        auto foo_reference = Reference<test::Type>(foo);
        ASSERT_ARE_SAME(foo_reference->x, foo->x);
    };

    DESCRIBE_TEST(operator->(), Original data changed, Update data inside reference) {
        test::Type* foo = new test::Type{3, 4};
        auto foo_reference = Reference<test::Type>(foo);
        foo->x = 99;
        ASSERT_ARE_EQUAL(foo_reference->x, 99);
    };

    DESCRIBE_TEST(operator->(), Changed data via reference, Update original data) {
        test::Type* foo = new test::Type{3, 4};
        auto foo_reference = Reference<test::Type>(foo);
        foo_reference->x = 99;
        ASSERT_ARE_EQUAL(foo->x, 99);
    };

    DESCRIBE_TEST(Reference(const Reference&), Copied N times, Increase reference count by N) {
        using Ref = Reference<test::Type>;
        auto foo = Ref(new test::Type{3, 4});

        // copying
        const uint64_t copy_count = 100;
        Ref* copy_refs[copy_count];
        for (uint64_t i = 0; i < copy_count; i++) {
            copy_refs[i] = new Ref(foo);
        }

        ASSERT_ARE_EQUAL(copy_refs[copy_count - 1]->copy_count(), copy_count + 1);

        // cleanup
        for (uint64_t i = 0; i < copy_count; i++) {
            delete copy_refs[i];
        }
    };

    DESCRIBE_TEST(clear(), Copy is cleared, Decrease reference counter) {
        using Ref = Reference<test::Type>;
        auto foo = Ref(new test::Type{3, 4});

        // copying
        const uint64_t copy_count = 3;
        Ref* copy_refs[copy_count];
        for (uint64_t i = 0; i < copy_count; i++) {
            copy_refs[i] = new Ref(foo);
        }

        copy_refs[copy_count - 1]->clear();
        ASSERT_ARE_EQUAL(foo.copy_count(), copy_count);

        // cleanup
        for (uint64_t i = 0; i < copy_count; i++) {
            delete copy_refs[i];
        }
    };
}
