#ifndef SARGASSO_COMMON_COUNTER_H
#define SARGASSO_COMMON_COUNTER_H

#include <cstdlib>

namespace sargasso {
namespace common {

class Counter {
   public:
    void reset();
    void increase();
    void decrease();
    bool operator==(size_t n) const;
    bool operator>(size_t n) const;
    bool operator>=(size_t n) const;
    bool operator<=(size_t n) const;
    bool operator<(size_t n) const;
    size_t get() const;

   private:
    size_t _count = 0;
};

}  // namespace common
}  // namespace sargasso

#endif  // SARGASSO_COMMON_COUNTER_H
