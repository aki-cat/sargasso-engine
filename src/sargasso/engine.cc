
#include "sargasso/engine.h"

#include "sargasso/common/log.h"
#include "sargasso/config.h"
#include "sargasso/front_end/front_end_system.h"

#include <glad/glad.h>

using namespace SargassoEngine;
using namespace SargassoEngine::Common;
using namespace SargassoEngine::FrontEnd;
using namespace SargassoEngine::FrontEnd::Modules;

Game::Game() {}

void Game::load() {}

void Game::update(double delta) {}

void Game::key_pressed(int key_code) {}

void Game::key_released(int key_code) {}

void Game::exit() { _should_quit = true; }

FrontEndSystem& Game::get_front_end_system() { return *_front_end; }

int Game::run(Game& game) {
    logf("% v%\n", ENGINE_NAME, ENGINE_VERSION);

    FrontEndSystem front_end = FrontEndSystem();
    game._front_end = &front_end;

    if (!front_end.is_initialized()) {
        return -1;
    }

    front_end.start();

#ifndef RELEASE
    glEnable(GL_DEBUG_OUTPUT);
#endif

    Graphics& graphics = front_end.get_module<Graphics>();
    Events& events = front_end.get_module<Events>();
    Time& time = front_end.get_module<Time>();

    game.load();
    uint64_t frame_count = 0;

    glfwSetWindowUserPointer(graphics.get_window(), &game);

    do {
        time.start_frame();
        frame_count++;

        events.poll_events();
        game.update(time.get_delta());

        graphics.render_buffers();

        time.end_frame();
    } while (!(graphics.should_window_close() || game._should_quit));

    glfwSetWindowUserPointer(graphics.get_window(), NULL);

    front_end.stop();

    return 0;
}
