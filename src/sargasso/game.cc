
#include "sargasso/game.h"

#include "sargasso/common/log.h"
#include "sargasso/config.h"

using sargasso::Game;
using sargasso::common::Log;

Game::Game() {}

void Game::load() {}

void Game::update(double delta) {}

void Game::key_pressed(int key_code) {}

void Game::key_released(int key_code) {}

void Game::exit() {
    _should_quit = true;
}

int Game::run(Game& game) {
    Log("Game").info("%s %s!", sargasso::ENGINE_NAME, sargasso::ENGINE_VERSION);

    do {
        //
    } while (!game.should_quit());

    return 0;
}

bool Game::should_quit() const {
    return _should_quit;
}
