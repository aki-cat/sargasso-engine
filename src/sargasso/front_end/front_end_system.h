#ifndef SARGASSO_ENGINE_FRONT_END_H
#define SARGASSO_ENGINE_FRONT_END_H

#include "sargasso/front_end/modules/events.h"
#include "sargasso/front_end/modules/graphics.h"
#include "sargasso/front_end/modules/time.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace SargassoEngine {
namespace FrontEnd {

using SargassoEngine::FrontEnd::Modules::Events;
using SargassoEngine::FrontEnd::Modules::Graphics;
using SargassoEngine::FrontEnd::Modules::Time;

class FrontEndSystem {
   public:
    explicit FrontEndSystem();
    ~FrontEndSystem();
    bool is_initialized();
    void start();
    void stop();

    template <typename T>
    T& get_module() const;

   private:
    bool _initialized;
    Graphics* _graphics;
    Events* _events;
    Time* _time;
};

template <>
inline Graphics& FrontEndSystem::get_module() const {
    return *_graphics;
}

template <>
inline Events& FrontEndSystem::get_module() const {
    return *_events;
}

template <>
inline Time& FrontEndSystem::get_module() const {
    return *_time;
}

}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
