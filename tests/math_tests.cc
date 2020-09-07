
#include "math_tests.h"

#include "assertion.h"
#include "common/log.h"
#include "common/math/matrix4.h"
#include "common/math/quaternion.h"
#include "common/math/transform.h"
#include "common/math/vector3.h"

#include <cfloat>

using namespace SargassoEngine;
using namespace SargassoEngine::Common;
using namespace SargassoEngine::Common::Math;

void Tests::math_tests() {
    _SARGASSO_TEST_CLASS("Vec3");
    Tests::operatorMul_dotProduct_expectedResult();
    Tests::operatorMul_scalarProduct_expectedResult();
    Tests::operatorMul_scalarProduct_differentInstance();
    _SARGASSO_TEST_CLASS("Mat4");
    Tests::operatorMul_twoMatrices_expectedResult();
    Tests::operatorMul_matrixAndVec3_expectedResult();
    _SARGASSO_TEST_CLASS("Transform");
    Tests::rotated_quarterCircle_expectedResult();
}

// vector multiplication
void Tests::operatorMul_dotProduct_expectedResult() {
    _SARGASSO_TEST_START("Vec3", "operator*", "WithAnotherVector", "ReturnDotProductResult");

    Vec3 v(2, 3, 5);
    Vec3 u(7, -1, -6);

    assert(v * u + 19 < FLT_EPSILON);
    assert(v * Vec3::zero - 0 < FLT_EPSILON);
    assert(u * Vec3::zero - 0 < FLT_EPSILON);
    assert(u * Vec3(1, 1, 1) - 10 < FLT_EPSILON);

    _SARGASSO_TEST_PASSED();
}

void Tests::operatorMul_scalarProduct_expectedResult() {
    _SARGASSO_TEST_START("Vec3", "operator*", "WithNumber", "ReturnScallingResult");

    Vec3 v(2, 3, 5);

    assert(v * 5 == Vec3(10, 15, 25));
    assert(v * 0 == Vec3::zero);
    assert(v * -1 == Vec3(-2, -3, -5));

    _SARGASSO_TEST_PASSED();
}

void Tests::operatorMul_scalarProduct_differentInstance() {
    _SARGASSO_TEST_START("Vec3", "operator*", "WithNumber", "ReturnDifferentInstance");

    Vec3 v(2, 3, 5);
    Vec3 u = 1 * v;

    assert(&u != &v);

    _SARGASSO_TEST_PASSED();
}

void Tests::rotated_quarterCircle_expectedResult() {
    _SARGASSO_TEST_START("Transform", "rotated", "QuarterCircleRotationWithQuaternion",
                         "ReturnExpectedResult");

    Vec3 v(1, 1, 1);
    Quat q = Transform::quaternion_from_rotation(Vec3::y_axis, static_cast<float>(M_PI) / 2);

    Vec3 result = Transform::rotated(v, q);

    assert(result == Vec3(1, 1, -1));

    _SARGASSO_TEST_PASSED();
}

void Tests::operatorMul_twoMatrices_expectedResult() {
    _SARGASSO_TEST_START("Mat4", "operator*", "WithMatrix", "ReturnExpectedResult");

    Mat4 m1({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
    Mat4 m2({2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32});

    Mat4 result = m1 * m2;
    Mat4 expected(
        {180, 200, 220, 240, 404, 456, 508, 560, 628, 712, 796, 880, 852, 968, 1084, 1200});

    assert(result == expected);

    _SARGASSO_TEST_PASSED();
}

void Tests::operatorMul_matrixAndVec3_expectedResult() {
    _SARGASSO_TEST_START("Mat4", "operator*", "WithVector", "ReturnExpectedResult");

    Mat4 m({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
    Vec3 v(11, 22, 33);

    Vec3 result = m * v;
    Vec3 expected(158, 426, 694);

    assert(result == expected);

    _SARGASSO_TEST_PASSED();
}
