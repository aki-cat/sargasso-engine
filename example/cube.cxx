
#include "sml/matrix4.h"
#include "sml/vector3.h"

#include <cstdlib>
#include <sargasso/common/log.h>
#include <sargasso/engine.h>
#include <sml/color.h>
#include <sml/sml.h>
#include <string>
#include <vector>

using sargasso::Engine;
using sargasso::ProjectConfig;
using sargasso::uint;
using sargasso::common::Log;
using sargasso::geometry::Mesh;

static const uint WINDOW_WIDTH = 576;
static const uint WINDOW_HEIGHT = 576;
static const uint PPU = 32;

static const float rotationSpeed = 1.5f;
static sml::Vec3 rotationAxis = sml::Vec3(.2f, .8f, .6f);

struct ObjectMesh {
    Mesh mesh;
    sml::Mat4 transform;
};

static std::vector<ObjectMesh> meshes{};

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
    logger.info("[%s] Starting example project CUBE...", argv[0]);

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

    logger.info("Generating cube data");
    meshes.push_back({Mesh(
                          {
                              {{-.5f, -.5f, -.5f}, sml::Color::white(), {}, {}},
                              {{+.5f, -.5f, -.5f}, sml::Color::white(), {}, {}},
                              {{+.5f, +.5f, -.5f}, sml::Color::white(), {}, {}},
                              {{-.5f, +.5f, -.5f}, sml::Color::white(), {}, {}},
                              {{-.5f, -.5f, +.5f}, sml::Color::gray(), {}, {}},
                              {{+.5f, -.5f, +.5f}, sml::Color::gray(), {}, {}},
                              {{+.5f, +.5f, +.5f}, sml::Color::gray(), {}, {}},
                              {{-.5f, +.5f, +.5f}, sml::Color::gray(), {}, {}},
                          },
                          {// front
                           {0, 1, 2},
                           {2, 3, 0},
                           // top
                           {5, 4, 1},
                           {1, 0, 4},
                           // right
                           {1, 5, 6},
                           {6, 2, 1},
                           // back
                           {5, 4, 7},
                           {7, 6, 5},
                           // bottom
                           {3, 2, 6},
                           {6, 7, 3},
                           // left
                           {4, 0, 3},
                           {3, 7, 4}}),
                      sml::Mat4::identity()});
    ObjectMesh& cube = meshes.back();
    cube.transform.scale(6.f);
    logger.info("Sending cube data to GPU (%x)", &cube.mesh);
    logger.info("Game loading OK");
}

void Game::update(const double dt) {
    static const Log logger("Game::update()");
    logger.debug("FPS = %.3f", 1.0 / dt);
    for (auto& cube : meshes) {
        cube.transform.rotate(rotationAxis, rotationSpeed * dt);
    }
}

void Game::draw() {
    static const Log logger("Game::draw()");
    for (const auto& cube : meshes) {
        _graphics.drawMesh(cube.mesh, cube.transform);
    }
}

void Game::onKeyPressed(int key) {
    if (key == GLFW_KEY_Y) {
        rotationAxis =
            sml::Vec3(std::rand() % 0xff * 1.f, std::rand() % 0xff * 1.f, std::rand() % 0xff * 1.f)
                .normalized();
    }
}

void Game::onKeyReleased(int key) {
    if (key == GLFW_KEY_F8) {
        requestQuit();
    }
}
