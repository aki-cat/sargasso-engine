#ifndef SARGASSO_ENGINE_H_
#define SARGASSO_ENGINE_H_

#include "sargasso/graphics/igraphics.h"
#include "sargasso/window/icontext_wrapper.h"

using sargasso::graphics::IGraphics;
using sargasso::window::IContextWrapper;

namespace sargasso {

class Engine {
   public:
    Engine();
    ~Engine();
    void run();

   private:
    IContextWrapper* _contextWrapper;
    IGraphics* _graphics;
};

}  // namespace sargasso

#endif
