
#include <GLFW/glfw3.h>
#include <sargasso/common/log.h>
#include <sargasso/engine.h>

using namespace SargassoEngine;

// Define your class inheriting from Game
class Example : public Game {
   public:
    Example() : Game() {}

    void load() override {}

    void update(double delta) override {}
    void key_pressed(int key_code) override {
        if (key_code == GLFW_KEY_F8) {
            Common::log("Exit action requested.");
            exit();
        }
    }

    void key_released(int key_code) override {}
};

// Then define a main and run Game::run() passing a simple instance of your class, like so:
int main() {
    Example example;
    return Game::run(example);
}
