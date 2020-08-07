#ifndef SARGASSO_ENGINE_FRONT_END_H
#define SARGASSO_ENGINE_FRONT_END_H

#include <GLFW/glfw3.h>

#include "front_end/modules/events.h"
#include "front_end/modules/graphics.h"
#include "front_end/modules/time.h"

namespace SargassoEngine {
namespace FrontEnd {

using SargassoEngine::FrontEnd::Modules::Events;
using SargassoEngine::FrontEnd::Modules::Graphics;
using SargassoEngine::FrontEnd::Modules::Time;

class FrontEndSystem {
 public:
  FrontEndSystem();
  ~FrontEndSystem();
  bool is_initialized();
  void start();
  void stop();

  template <typename T>
  T &get_module();

 private:
  bool _initialized;
  Graphics *_graphics;
  Events *_events;
  Time *_time;
};

inline void FrontEndSystem::start() {
  _events->register_window(_graphics->get_window());
}

inline void FrontEndSystem::stop() {
  _events->deregister_window(_graphics->get_window());
}

inline bool FrontEndSystem::is_initialized() { return _initialized; }

template <>
inline Graphics &FrontEndSystem::get_module() {
  return *_graphics;
}

template <>
inline Events &FrontEndSystem::get_module() {
  return *_events;
}

template <>
inline Time &FrontEndSystem::get_module() {
  return *_time;
}

}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
