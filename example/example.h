#ifndef SARGASSO_SAMPLE_EXAMPLE_H
#define SARGASSO_SAMPLE_EXAMPLE_H

#include <sargasso/engine.h>

using namespace SargassoEngine;

// Define your class inheriting from Game
class Example : public Game {
   public:
    Example();
    void load() override;
    void update(double delta) override;
    void key_pressed(int key_code) override;
    void key_released(int key_code) override;
};

#endif
