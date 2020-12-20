#ifndef SARGASSO_ENGINE_H
#define SARGASSO_ENGINE_H

#define AS_STRING(v) #v
#define MACRO_AS_STRING(v) AS_STRING(v)

namespace SargassoEngine {

constexpr const char* ENGINE_NAME = "Sargasso Engine";

#ifdef SARGASSO_ENGINE_VERSION
constexpr const char* ENGINE_VERSION = MACRO_AS_STRING(SARGASSO_ENGINE_VERSION);
#else
constexpr const char* ENGINE_VERSION = "Unknown";
#endif

class Game {
   public:
    virtual void load();
    virtual void update(double delta);
    virtual void key_pressed(int key_code);
    virtual void key_released(int key_code);

    static int run(Game& game);
    void exit();

   protected:
    Game(){};

   private:
    bool _should_quit = false;
};

}  // namespace SargassoEngine

#undef AS_STRING
#undef MACRO_AS_STRING

#endif
