#ifndef SARGASSO_COMMON_COUNTER_H
#define SARGASSO_COMMON_COUNTER_H

#include <cstdint>

namespace sargasso {
namespace common {

class Counter {
   public:
    void reset();
    void increase();
    void decrease();
    bool operator==(uint64_t n) const;
    bool operator>(uint64_t n) const;
    bool operator>=(uint64_t n) const;
    bool operator<=(uint64_t n) const;
    bool operator<(uint64_t n) const;
    uint64_t get() const;

   private:
    uint64_t _count = 0;
};

}  // namespace common
}  // namespace sargasso

#endif  // SARGASSO_COMMON_COUNTER_H
