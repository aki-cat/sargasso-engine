#ifndef SARGASSO_ENGINE_H_
#define SARGASSO_ENGINE_H_

#include "sargasso/window/icontext_wrapper.h"

using sargasso::window::IContextWrapper;

namespace sargasso {

class Engine {
   public:
    Engine();
    ~Engine();
    void run();

   private:
    IContextWrapper* _contextWrapper;
};

}  // namespace sargasso

#endif
