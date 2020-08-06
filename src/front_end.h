#ifndef SARGASSO_ENGINE_FRONT_END_H
#define SARGASSO_ENGINE_FRONT_END_H

#include <GLFW/glfw3.h>

#include "modules/events.h"
#include "modules/graphics.h"

namespace SargassoEngine {

using SargassoEngine::Modules::Events;
using SargassoEngine::Modules::Graphics;

class FrontEnd {
 public:
  FrontEnd();
  ~FrontEnd();
  bool is_initialized();
  void start();
  void stop();

  template <typename T>
  T &get_module();

 private:
  bool _initialized;
  Graphics *_graphics;
  Events *_events;
};

inline void FrontEnd::start() {
  _events->register_window(_graphics->get_window());
}

inline void FrontEnd::stop() {
  _events->deregister_window(_graphics->get_window());
}

inline bool FrontEnd::is_initialized() { return _initialized; }

template <>
inline Graphics &FrontEnd::get_module() {
  return *_graphics;
}

template <>
inline Events &FrontEnd::get_module() {
  return *_events;
}

}  // namespace SargassoEngine

#endif
