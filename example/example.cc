
#include <sargasso/engine.h>

using namespace SargassoEngine;

// Define your class inheriting from Game
class Example : public Game {
   public:
    Example() : Game() {}
};

// Then define a main and run Game::run() passing a simple instance of your class, like so:
int main() {
    Example example;
    return Game::run(example);
}
