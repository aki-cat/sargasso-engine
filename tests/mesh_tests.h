#ifndef SARGASSO_ENGINE_MESH_TESTS_H
#define SARGASSO_ENGINE_MESH_TESTS_H

namespace SargassoEngine {
namespace Tests {

void mesh_tests();

// translate
void translate_zeroVector_equalMesh();
void translate_anyVector_copiedInstance();
void translate_anyVector_expectedTranslation();

// rotate

// scale

}  // namespace Tests
}  // namespace SargassoEngine

#endif
