
#include "math_tests.h"

#include "assertion.h"
#include "common/log.h"
#include "common/math/vector3.h"

#include <cfloat>

using namespace SargassoEngine;
using namespace SargassoEngine::Common;
using namespace SargassoEngine::Common::Math;

void Tests::math_tests() {
    _SARGASSO_TEST_CLASS("Vector3");
    Tests::operatorMul_dotProduct_expectedResult();
    Tests::operatorMul_scalarProduct_expectedResult();
    Tests::operatorMul_scalarProduct_differentInstance();
}

// vector multiplication
void Tests::operatorMul_dotProduct_expectedResult() {
    _SARGASSO_TEST_START("Vec3", "operator*", "WithAnotherVector", "ReturnDotProductResult");

    Vec3 v(2.0f, 3.0f, 5.0f);
    Vec3 u(7.0f, -1.0f, -6.0f);

    assert(v * u + 19.0f < FLT_EPSILON);
    assert(v * Vec3::zero - 0.0f < FLT_EPSILON);
    assert(u * Vec3::zero - 0.0f < FLT_EPSILON);
    assert(u * Vec3(1.0f, 1.0f, 1.0f) - 10.0f < FLT_EPSILON);

    _SARGASSO_TEST_PASSED();
}

void Tests::operatorMul_scalarProduct_expectedResult() {
    _SARGASSO_TEST_START("Vec3", "operator*", "WithNumber", "ReturnScallingResult");

    Vec3 v(2.0f, 3.0f, 5.0f);

    assert(v * 5 == Vec3(10.0f, 15.0f, 25.0f));
    assert(v * 0 == Vec3::zero);
    assert(v * -1 == Vec3(-2.0f, -3.0f, -5.0f));

    _SARGASSO_TEST_PASSED();
}

void Tests::operatorMul_scalarProduct_differentInstance() {
    _SARGASSO_TEST_START("Vec3", "operator*", "WithNumber", "ReturnDifferentInstance");

    Vec3 v(2.0f, 3.0f, 5.0f);
    Vec3 u = 1 * v;

    assert(&u != &v);

    _SARGASSO_TEST_PASSED();
}
