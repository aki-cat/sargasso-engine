
#include "front_end/front_end_system.h"

#include <iostream>

using SargassoEngine::FrontEnd::FrontEndSystem;

FrontEndSystem::FrontEndSystem() {
    std::cout << glfwGetVersionString() << std::endl;
    std::cout << "Initializing GLFW..." << std::endl;

    if (!glfwInit()) {
        std::cerr << "Init failed!" << std::endl;
        _initialized = false;
        return;
    }

    std::cerr << "Init succesful!" << std::endl;

    _graphics = new Graphics();
    _events = new Events();
    _initialized = true;
}

FrontEndSystem::~FrontEndSystem() {
    std::cout << "Terminating GLFW..." << std::endl;

    delete _events;
    delete _graphics;

    if (_initialized) {
        glfwTerminate();
    }
}

void FrontEndSystem::start() { _events->register_window(_graphics->get_window()); }

void FrontEndSystem::stop() { _events->deregister_window(_graphics->get_window()); }

bool FrontEndSystem::is_initialized() { return _initialized; }
