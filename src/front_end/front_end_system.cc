
#include "front_end/front_end_system.h"

#include "front_end/modules/events.h"
#include "front_end/modules/graphics.h"
#include "front_end/modules/time.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using SargassoEngine::FrontEnd::FrontEndSystem;

FrontEndSystem::FrontEndSystem() {
    std::cout << glfwGetVersionString() << std::endl;
    std::cout << "Initializing GLFW..." << std::endl;

    glewExperimental = GL_TRUE;

    if (!glfwInit()) {
        std::cerr << "Init failed!" << std::endl;
        _initialized = false;
        return;
    }

    std::cerr << "Init succesful!" << std::endl;

    _graphics = new Graphics();
    _events = new Events();
    _time = new Time();
    _initialized = true;
}

FrontEndSystem::~FrontEndSystem() {
    std::cout << "Terminating GLFW..." << std::endl;

    delete _events;
    delete _graphics;
    delete _time;

    if (_initialized) {
        glfwTerminate();
    }
}

void FrontEndSystem::start() {
    std::cout << "Registering window callbacks..." << std::endl;
    _events->register_window(_graphics->get_window());
    _time->reset();
}

void FrontEndSystem::stop() {
    std::cout << "Deregistering window callbacks..." << std::endl;
    _events->deregister_window(_graphics->get_window());
}

bool FrontEndSystem::is_initialized() { return _initialized; }
