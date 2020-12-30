#ifndef SARGASSO_ENGINE_H
#define SARGASSO_ENGINE_H

#include "sargasso/front_end/front_end_system.h"

namespace sargasso {

class Game {
   public:
    virtual void load();
    virtual void update(double delta);
    virtual void key_pressed(int key_code);
    virtual void key_released(int key_code);

    static int run(Game& game);
    void exit();

   protected:
    explicit Game();
    FrontEndSystem& get_front_end_system();

   private:
    bool _should_quit = false;
    FrontEndSystem* _front_end;
};

}  // namespace sargasso

#endif
