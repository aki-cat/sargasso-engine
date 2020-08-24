
#include "common/pool.h"

namespace SargassoEngine {
namespace Tests {

using namespace Common;

struct Dummy {
    const char* name;
    int age;
};

void pool_tests() {
    // Test block
    _SARGASSO_TEST("Pool<Dummy>", "create", "AddedConsecutiveElements", "ReturnDifferentIds");
    Pool<Dummy> dummy_pool{};

    Dummy v1_original = Dummy{"banana", 6};
    Dummy v2_original = Dummy{"mango", 12};
    Dummy v3_original = Dummy{"apple", 18};

    const Pool<Dummy>::ID v1_id = dummy_pool.create(v1_original);
    const Pool<Dummy>::ID v2_id = dummy_pool.create(v2_original);
    const Pool<Dummy>::ID v3_id = dummy_pool.create(v3_original);

    assert(v1_id != v2_id);
    assert(v1_id != v3_id);
    assert(v2_id != v3_id);

    _SARGASSO_TEST_PASSED();

    // Test block
    _SARGASSO_TEST("Pool<Dummy>", "get", "AddedConsecutiveElements", "ReturnEquivalentElements");

    const Dummy& v1 = dummy_pool.get(v1_id);
    const Dummy& v2 = dummy_pool.get(v2_id);
    const Dummy& v3 = dummy_pool.get(v3_id);

    assert(v1.name == v1_original.name && v1.age == v1_original.age);
    assert(v2.name == v2_original.name && v2.age == v2_original.age);
    assert(v3.name == v3_original.name && v3.age == v3_original.age);

    _SARGASSO_TEST_PASSED();

    // Test block
    _SARGASSO_TEST("Pool<Dummy>", "get", "AddedConsecutiveElements",
                   "ReturnDifferentReferenceOfEquivalentAddedElements");

    v1_original.age = 58;
    assert(&v1 != &v1_original);
    assert(v1.age != v1_original.age);

    _SARGASSO_TEST_PASSED();

    // Test block
    _SARGASSO_TEST("Pool<Dummy>", "get", "ChangedMutableElementReference", "ChangeAllReferences");

    Dummy& v2_mut = dummy_pool.get(v2_id);
    v2_mut.name = "Charles";
    v2_mut.age = 97;
    assert(v2_mut.age == v2.age && v2_mut.name == v2.name);

    _SARGASSO_TEST_PASSED();

    // Test block
    _SARGASSO_TEST("Pool<Dummy>", "destroy", "DestroyAddedElement", "ThrowsWhenTryingToAccessIt");

    dummy_pool.destroy(v1_id);
    assert_throws({ dummy_pool.get(v1_id); }, ...);

    _SARGASSO_TEST_PASSED();
}

}  // namespace Tests

}  // namespace SargassoEngine
