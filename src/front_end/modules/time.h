#ifndef SARGASSO_ENGINE_FRONT_END_TIME_H
#define SARGASSO_ENGINE_FRONT_END_TIME_H

namespace SargassoEngine {
namespace FrontEnd {
namespace Modules {

class Time {
   public:
    Time() : _delta(0.0), _start_frame_time(0.0), _frame_started(false) {}
    double get_delta();
    void start_frame();
    void end_frame();

   private:
    double _delta;
    double _start_frame_time;
    bool _frame_started;
};

}  // namespace Modules
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
