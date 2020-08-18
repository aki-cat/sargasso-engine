#include "front_end/modules/time.h"

#include <GLFW/glfw3.h>
#include <cassert>

using SargassoEngine::FrontEnd::Modules::Time;

void Time::reset() { glfwSetTime(0.0); }

void Time::start_frame() {
    assert(!_frame_started);
    _frame_started = true;
    _start_frame_time = glfwGetTime();
}

void Time::end_frame() {
    assert(_frame_started);
    _frame_started = false;
    _delta = glfwGetTime() - _start_frame_time;
}

double Time::get_delta() { return _delta; }
