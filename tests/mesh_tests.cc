
// #include "mesh_tests.h"

// #include "assertion.h"
// #include "geometry/mesh.h"

// using namespace SargassoEngine::Common::Math;
// using namespace SargassoEngine::Geometry;
// using namespace SargassoEngine;

// void Tests::mesh_tests() {
//     // translate
//     translate_zeroVector_equalMesh();
//     translate_anyVector_copiedInstance();
//     translate_anyVector_expectedTranslation();
// }

// void Tests::translate_zeroVector_equalMesh() {
//     _SARGASSO_TEST("Mesh", "translate", "ZeroVector", "EqualMesh");

//     const Vector3 vertices[3] = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
//     Mesh mesh = Mesh(vertices, 3);

//     const Mesh translated_mesh = mesh.translate(Vector3());

//     assert(translated_mesh.get_vertex(0) == vertices[0]);
//     assert(translated_mesh.get_vertex(1) == vertices[1]);
//     assert(translated_mesh.get_vertex(2) == vertices[2]);

//     _SARGASSO_TEST_PASSED();
// }
// void Tests::translate_anyVector_copiedInstance() {
//     _SARGASSO_TEST("Mesh", "translate", "AnyVector", "CopiedInstance");
//     // TODO: tests
//     _SARGASSO_TEST_PASSED();
// }
// void Tests::translate_anyVector_expectedTranslation() {
//     _SARGASSO_TEST("Mesh", "translate", "AnyVector", "ExpectedTranslation");
//     // TODO: tests
//     _SARGASSO_TEST_PASSED();
// }
