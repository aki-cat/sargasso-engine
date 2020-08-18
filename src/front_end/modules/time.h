#ifndef SARGASSO_ENGINE_FRONT_END_TIME_H
#define SARGASSO_ENGINE_FRONT_END_TIME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace SargassoEngine {
namespace FrontEnd {
namespace Modules {

class Time {
   public:
    Time() : _delta(0.0), _start_frame_time(0.0), _frame_started(false) {}
    void reset();
    void start_frame();
    void end_frame();
    double get_delta();

   private:
    double _delta;
    double _start_frame_time;
    bool _frame_started;
};

}  // namespace Modules
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
