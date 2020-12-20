
#include "example.h"

#include <GLFW/glfw3.h>
#include <sargasso/common/log.h>
#include <sargasso/engine.h>
#include <sargasso/front_end/front_end_system.h>
#include <sml/vector3.h>

using namespace SargassoEngine;
using namespace SargassoEngine::FrontEnd;
using namespace SargassoEngine::FrontEnd::Modules;
using namespace SML;

Example::Example() : Game() {}

void Example::load() {
    Common::log("Welcome!");

    // Add 100x100 square
    std::vector<Vec3> square = {Vec3(-50, -50, 0), Vec3(+50, -50, 0), Vec3(+50, +50, 0),
                                Vec3(+50, +50, 0), Vec3(-50, +50, 0), Vec3(-50, -50, 0)};

    FrontEndSystem& front_end = get_front_end_system();
    Graphics& graphics = front_end.get_module<Graphics>();

    graphics.register_buffer(square);
}

void Example::update(double delta) {}

void Example::key_pressed(int key_code) {
    if (key_code == GLFW_KEY_F8) {
        Common::log("Exit action requested.");
        exit();
    }
}

void Example::key_released(int key_code) {}
