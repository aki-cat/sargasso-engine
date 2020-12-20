
#include "sargasso/engine.h"

#include "sargasso/common/log.h"
#include "sargasso/front_end/front_end_system.h"

using namespace SargassoEngine;
using namespace SargassoEngine::Common;
using namespace SargassoEngine::FrontEnd;
using namespace SargassoEngine::FrontEnd::Modules;

void Game::load() {}

void Game::update(double delta) {}

void Game::key_pressed(int key_code) {}

void Game::key_released(int key_code) {}

void Game::exit() { _should_quit = true; }

int Game::run(Game& game) {
    logf("% v%\n", SargassoEngine::ENGINE_NAME, SargassoEngine::ENGINE_VERSION);

    FrontEndSystem front_end = FrontEndSystem();
    if (!front_end.is_initialized()) {
        return -1;
    }

    front_end.start();

    Graphics& graphics = front_end.get_module<Graphics>();
    Events& events = front_end.get_module<Events>();
    Time& time = front_end.get_module<Time>();

    game.load();
    uint64_t frame_count = 0;

    do {
        time.start_frame();
        frame_count++;

        events.poll_events();
        game.update(time.get_delta());

        graphics.render_buffers();

        time.end_frame();
    } while (!(graphics.should_window_close() || game._should_quit));

    front_end.stop();

    return 0;
}
