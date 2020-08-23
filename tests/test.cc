
#include "common/containers.h"
#include "common/log.h"
#include "common/math.h"
#include "geometry/mesh.h"
#include "geometry/pool.h"
#include "geometry/vertex.h"

#include <cassert>
#include <stdio.h>

using namespace SargassoEngine;
using namespace Common;
using namespace Geometry;

#define _SARGASSO_TEST(CLASS_NAME, METHOD_NAME, SITUATION, EXPECTED) \
    printf("\n%s::%s It should %s when %s\n", CLASS_NAME, METHOD_NAME, EXPECTED, SITUATION)

#define _SARGASSO_TEST_PASSED() printf("...OK!\n")

void vertex_pool_tests() {
    // Test block
    _SARGASSO_TEST("Pool<Vertex>", "create", "AddedConsecutiveVertices", "ReturnDifferentIds");
    Pool<Vertex> vertex_pool{};

    const Vertex v1_original = Vertex(0.0f, 0.0f, 0.0f);
    const Vertex v2_original = Vertex(1.0f, 0.0f, 0.0f);
    const Vertex v3_original = Vertex(1.0f, 1.0f, 0.0f);

    const VertexID v1_id = vertex_pool.create(v1_original);
    const VertexID v2_id = vertex_pool.create(v2_original);
    const VertexID v3_id = vertex_pool.create(v3_original);

    assert(v1_id != v2_id);
    assert(v1_id != v3_id);
    assert(v2_id != v3_id);

    _SARGASSO_TEST_PASSED();

    // Test block
    _SARGASSO_TEST("Pool<Vertex>", "get", "AddedConsecutiveVertices", "ReturnEquivalentVertices");

    const Vertex& v1 = vertex_pool.get(v1_id);
    const Vertex& v2 = vertex_pool.get(v2_id);
    const Vertex& v3 = vertex_pool.get(v3_id);

    assert(v1.position == Vector3(0.0f, 0.0f, 0.0f));
    assert(v2.position == Vector3(1.0f, 0.0f, 0.0f));
    assert(v3.position == Vector3(1.0f, 1.0f, 0.0f));

    _SARGASSO_TEST_PASSED();

    // Test block
    _SARGASSO_TEST("Pool<Vertex>", "get", "AddedConsecutiveVertices",
                   "ReturnDifferentReferenceOfEquivalentAddedVertices");

    assert(&v1 != &v1_original);
    assert(&v1 != &v1_original);
    assert(&v2 != &v2_original);

    _SARGASSO_TEST_PASSED();
}

int main(int argc, char const* argv[]) {
    vertex_pool_tests();

    return 0;
}
