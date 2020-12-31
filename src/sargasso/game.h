#ifndef SARGASSO_GAME_H_
#define SARGASSO_GAME_H_

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

   private:
    bool should_quit() const;
    bool _should_quit = false;
};

}  // namespace sargasso

#endif
