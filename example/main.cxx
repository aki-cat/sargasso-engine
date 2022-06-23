
#include <cstdlib>
#include <sargasso/common/log.h>
#include <sargasso/common/reference.h>
#include <sargasso/engine.h>
#include <sargasso/geometry/rect.h>
#include <sargasso/graphics.h>
#include <sargasso/project_config.h>
#include <string>

using sargasso::Engine;
using sargasso::ProjectConfig;
using sargasso::common::Log;
using sargasso::common::Reference;
using sargasso::geometry::Rect;

Reference<Rect> sampleRect;

class Game : public Engine {
   public:
    Game(const ProjectConfig& projectConfig) : Engine(projectConfig) {}
    void load() override;
    void update(const double dt) override;
    void draw() override;
};

int main() {
    static const Log logger("main");
    logger.info("Starting example project...");

    try {
        const ProjectConfig projectConfig = {"Example Project\0", "1.0", 1280, 720, 4};
        Game game(projectConfig);
        game.run();
    } catch (const std::exception& e) {
        logger.error(e.what());
        return EXIT_FAILURE;
    } catch (...) {
        logger.error("Unknown error caught.");
        throw;
    }

    logger.info("Closing example project...");
    return EXIT_SUCCESS;
}

void Game::load() {
    static const Log logger("Game::load()");
    sampleRect = _graphics.newRect(5, 8);
}

void Game::update(const double dt) {
    static const Log logger("Game::update()");
}

void Game::draw() {
    static const Log logger("Game::draw()");
}
