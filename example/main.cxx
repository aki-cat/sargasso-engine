
#include <sargasso/common/log.h>
#include <sargasso/engine.h>
#include <sargasso/project_config.h>

static const sargasso::common::Log logger("Sample");

class Game : public sargasso::Engine {
   public:
    Game(const sargasso::ProjectConfig& projectConfig) : sargasso::Engine(projectConfig) {}
    void load() override;
    void update(const double dt) override;
    void draw() override;
};

int main() {
    logger.info("Starting example project...");

    const sargasso::ProjectConfig projectConfig = {"Example Project\0", "1.0", 1280, 720, 4};

    Game game(projectConfig);
    game.run();

    logger.info("Closing example project...");
}

void Game::load() {
    logger.debug("load()");
}

void Game::update(const double dt) {
    logger.debug("update()");
}

void Game::draw() {
    logger.debug("draw()");
}
