#include "assertion.h"
#include "math_tests.h"
#include "pool_tests.h"

using namespace SargassoEngine::Tests;

int main(int argc, char const* argv[]) {
    pool_tests();
    math_tests();

    return 0;
}
