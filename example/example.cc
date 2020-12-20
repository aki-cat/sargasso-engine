
#include <sargasso/engine.h>

// Define your class inheriting from Game

class Example : public SargassoEngine::Game {
   public:
    Example() : SargassoEngine::Game() {}
};

// Then define a main and run Game::run() passing a simple instance of your class, like so:

int main() {
    Example example;
    return SargassoEngine::Game::run(example);
}
