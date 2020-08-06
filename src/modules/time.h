#ifndef SARGASSO_ENGINE_MODULES_TIME_H
#define SARGASSO_ENGINE_MODULES_TIME_H

#include <GLFW/glfw3.h>

#include <cassert>

namespace SargassoEngine {
namespace Modules {

class Time {
 public:
  Time();
  double get_delta();
  void start_frame();
  void end_frame();

 private:
  double _delta;
  double _start_frame_time;
  bool _frame_started;
};

inline double Time::get_delta() { return _delta; }

inline void Time::start_frame() {
  assert(!_frame_started);
  _frame_started = true;
  _start_frame_time = glfwGetTime();
}

inline void Time::end_frame() {
  assert(_frame_started);
  _frame_started = false;
  _delta = glfwGetTime() - _start_frame_time;
}

}  // namespace Modules
}  // namespace SargassoEngine

#endif
