#ifndef SARGASSO_ENGINE_MATH_TESTS_H
#define SARGASSO_ENGINE_MATH_TESTS_H

namespace SargassoEngine {
namespace Tests {

void math_tests();

// vector multiplication
void operatorMul_dotProduct_expectedResult();
void operatorMul_scalarProduct_expectedResult();
void operatorMul_scalarProduct_differentInstance();

// vector quaternion rotation
void rotated_quarterCircle_expectedResult();

// matrix transformation
void operatorMul_twoMatrices_expectedResult();
void operatorMul_matrixAndVec3_expectedResult();

}  // namespace Tests
}  // namespace SargassoEngine

#endif
