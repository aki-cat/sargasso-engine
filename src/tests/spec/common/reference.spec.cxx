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
        auto fooRef = Reference<test::Type>(foo);
        ASSERT_ARE_EQUAL(fooRef->x, 3);
    };

    DESCRIBE_TEST(operator->(), Accessed public member, Return same reference value) {
        test::Type* foo = new test::Type{3, 4};
        auto fooRef = Reference<test::Type>(foo);
        ASSERT_ARE_SAME(fooRef->x, foo->x);
    };

    DESCRIBE_TEST(operator->(), Original data changed, Update data inside reference) {
        test::Type* foo = new test::Type{3, 4};
        auto fooRef = Reference<test::Type>(foo);
        foo->x = 99;
        ASSERT_ARE_EQUAL(fooRef->x, 99);
    };

    DESCRIBE_TEST(operator->(), Changed data via reference, Update original data) {
        test::Type* foo = new test::Type{3, 4};
        auto fooRef = Reference<test::Type>(foo);
        fooRef->x = 99;
        ASSERT_ARE_EQUAL(foo->x, 99);
    };

    DESCRIBE_TEST(Reference(const Reference&), Copied N times, Increase reference count by N) {
        using Ref = Reference<test::Type>;
        auto foo = Ref(new test::Type{3, 4});

        // copying
        const size_t copyCount = 100;
        Ref* copyRefs[copyCount];
        for (size_t i = 0; i < copyCount; i++) {
            copyRefs[i] = new Ref(foo);
        }

        ASSERT_ARE_EQUAL(copyRefs[copyCount - 1]->copyCount(), copyCount + 1);

        // cleanup
        for (size_t i = 0; i < copyCount; i++) {
            delete copyRefs[i];
        }
    };

    DESCRIBE_TEST(clear(), Copy is cleared, Decrease reference counter) {
        using Ref = Reference<test::Type>;
        auto foo = Ref(new test::Type{3, 4});

        // copying
        const size_t copyCount = 3;
        Ref* copyRefs[copyCount];
        for (size_t i = 0; i < copyCount; i++) {
            copyRefs[i] = new Ref(foo);
        }

        copyRefs[copyCount - 1]->clear();
        ASSERT_ARE_EQUAL(foo.copyCount(), copyCount);

        // cleanup
        for (size_t i = 0; i < copyCount; i++) {
            delete copyRefs[i];
        }
    };
}
