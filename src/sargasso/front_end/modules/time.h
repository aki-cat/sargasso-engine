#ifndef SARGASSO_ENGINE_FRONT_END_TIME_H
#define SARGASSO_ENGINE_FRONT_END_TIME_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace SargassoEngine {
namespace FrontEnd {
namespace Modules {

class Time {
   public:
    explicit Time() {}
    Time(const Time&) = delete;
    Time(const Time&&) = delete;
    void reset();
    void start_frame();
    void end_frame();
    double get_delta();

   private:
    double _delta{0.0};
    double _start_frame_time{0.0};
    bool _frame_started{false};
};

}  // namespace Modules
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
