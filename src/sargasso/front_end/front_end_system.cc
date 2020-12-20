
#include "sargasso/front_end/front_end_system.h"

#include "sargasso/common/log.h"
#include "sargasso/front_end/modules/events.h"
#include "sargasso/front_end/modules/graphics.h"
#include "sargasso/front_end/modules/time.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

using SargassoEngine::FrontEnd::FrontEndSystem;
using namespace SargassoEngine::Common;

FrontEndSystem::FrontEndSystem(Game& game) : _game(game) {
    log(glfwGetVersionString());
    log("Initializing GLFW...");

    glewExperimental = GL_TRUE;

    if (!glfwInit()) {
        _initialized = false;
        throw std::runtime_error("Init failed!");
    }

    log("Init succesful!");

    _graphics = new Graphics();
    _events = new Events(_game);
    _time = new Time();
    _initialized = true;
}

FrontEndSystem::~FrontEndSystem() {
    log("Terminating GLFW...");

    delete _events;
    delete _graphics;
    delete _time;

    if (_initialized) {
        glfwTerminate();
    }
}

void FrontEndSystem::start() {
    log("Registering window callbacks...");
    _events->register_window(_graphics->get_window());
    _time->reset();
}

void FrontEndSystem::stop() {
    log("Deregistering window callbacks...");
    _events->deregister_window(_graphics->get_window());
}

bool FrontEndSystem::is_initialized() { return _initialized; }
