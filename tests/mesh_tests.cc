
#include "mesh_tests.h"

#include "assertion.h"
#include "common/math/vector3.h"
#include "geometry/mesh.h"

using namespace SargassoEngine::Common::Math;
using namespace SargassoEngine::Geometry;
using namespace SargassoEngine;

void Tests::mesh_tests() {
    // translate
    _SARGASSO_TEST_CLASS("Mesh");
    translate_zeroVector_equalMesh();
    translate_anyVector_copiedInstance();
    translate_anyVector_expectedTranslation();
}

void Tests::translate_zeroVector_equalMesh() {
    _SARGASSO_TEST_START("Mesh", "translate", "ZeroVector", "EqualMesh");

    const Vec3 vertices[3] = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
    Mesh mesh = Mesh(vertices, 3);

    const Mesh translated_mesh = mesh.translate(Vec3::zero());

    logf("expected %; got %", vertices[0].to_string(), translated_mesh.get_vertex(0).to_string());
    logf("expected %; got %", vertices[1].to_string(), translated_mesh.get_vertex(1).to_string());
    logf("expected %; got %", vertices[2].to_string(), translated_mesh.get_vertex(2).to_string());

    assert(translated_mesh.get_vertex(0) == vertices[0]);
    assert(translated_mesh.get_vertex(1) == vertices[1]);
    assert(translated_mesh.get_vertex(2) == vertices[2]);

    _SARGASSO_TEST_PASSED();
}

void Tests::translate_anyVector_copiedInstance() {
    _SARGASSO_TEST_START("Mesh", "translate", "AnyVector", "CopiedInstance");

    Vec3 vertices[3] = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
    Mesh mesh = Mesh(vertices, 3);

    Mesh translated_mesh = mesh.translate(Vec3(2.0f, 2.0f, 2.0f));

    assert(&translated_mesh != &mesh);

    _SARGASSO_TEST_PASSED();
}

void Tests::translate_anyVector_expectedTranslation() {
    _SARGASSO_TEST_START("Mesh", "translate", "AnyVector", "ExpectedTranslation");

    const Vec3 vertices[3] = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
    Mesh mesh = Mesh(vertices, 3);

    const Mesh translated_mesh = mesh.translate(Vec3(2.0f, 2.0f, 2.0f));

    assert(translated_mesh.get_vertex(0) == Vec3(3.0f, 4.0f, 5.0f));
    assert(translated_mesh.get_vertex(1) == Vec3(6.0f, 7.0f, 8.0f));
    assert(translated_mesh.get_vertex(2) == Vec3(9.0f, 10.0f, 11.0f));

    _SARGASSO_TEST_PASSED();
}
