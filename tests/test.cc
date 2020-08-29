#include "assertion.h"
#include "mesh_tests.h"
#include "pool_tests.h"

using namespace SargassoEngine::Tests;

int main(int argc, char const* argv[]) {
    pool_tests();
    mesh_tests();

    return 0;
}
