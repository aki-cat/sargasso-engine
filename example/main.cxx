
#include <cstdint>
#include <cstdlib>
#include <sargasso/engine.h>
#include <sml/sml.h>
#include <string>

using sargasso::Engine;
using sargasso::ProjectConfig;
using sargasso::common::Log;
using sargasso::common::Reference;
using sargasso::geometry::Rect;

const uint WINDOW_WIDTH = 1024;
const uint WINDOW_HEIGHT = 576;
const uint PPU = 32;

const uint HEIGHT_UNITS = (uint) (1.f * WINDOW_HEIGHT / PPU);
const uint WIDTH_UNITS = (uint) (1.f * HEIGHT_UNITS * WINDOW_WIDTH / WINDOW_HEIGHT);

Reference<Rect> sampleRects[WIDTH_UNITS][HEIGHT_UNITS];
float rWidth, rHeight;

class Game : public Engine {
   public:
    Game(const ProjectConfig& projectConfig, const char* argv0) : Engine(projectConfig, argv0) {}
    void load() override;
    void update(const double dt) override;
    void draw() override;

    void onKeyPressed(int key) override;
    void onKeyReleased(int key) override;
};

int main(int, const char** argv) {
    static const Log logger("main");
    logger.info("[%s] Starting example project...", argv[0]);

    try {
        const ProjectConfig projectConfig = {"Example Project", "coffeecat", "1.0", WINDOW_WIDTH,
                                             WINDOW_HEIGHT,     PPU,         0};
        Game game(projectConfig, argv[0]);
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

    // window size debugging rects
    float unit = 1.f;
    for (uint x = 0; x < WIDTH_UNITS; x++) {
        for (uint y = 0; y < HEIGHT_UNITS; y++) {
            auto rect = _graphics.newRect(unit, unit);
            const float posX = .5f * unit + x * unit - unit * WIDTH_UNITS * .5f;
            const float posY = .5f * unit + y * unit - unit * HEIGHT_UNITS * .5f;
            const sml::Vec3 pos(posX, posY, 0);
            rect->setTransform(sml::Mat4().translated(pos));
            sampleRects[x][y] = rect;
        }
    }
}

void Game::update(const double) {
    static const Log logger("Game::update()");
}

void Game::draw() {
    static const Log logger("Game::draw()");
    for (uint x = 0; x < WIDTH_UNITS; x++) {
        for (uint y = 0; y < HEIGHT_UNITS; y++) {
            _graphics.drawRect(sampleRects[x][y]);
        }
    }
}

void Game::onKeyPressed(int) {}

void Game::onKeyReleased(int key) {
    if (key == GLFW_KEY_F8) {
        requestQuit();
    }
}
