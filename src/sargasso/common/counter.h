#ifndef SARGASSO_COMMON_COUNTER_H
#define SARGASSO_COMMON_COUNTER_H

#include <cstdint>

namespace sargasso {
namespace common {

class Counter {
   public:
    Counter() = default;
    void reset();
    Counter& operator++();
    Counter& operator--();
    Counter operator++(int);
    Counter operator--(int);
    uint64_t operator*() const;
    bool operator==(uint64_t n) const;
    bool operator>(uint64_t n) const;
    bool operator>=(uint64_t n) const;
    bool operator<=(uint64_t n) const;
    bool operator<(uint64_t n) const;

   private:
    uint64_t _count = 0;
};

}  // namespace common
}  // namespace sargasso

#endif  // SARGASSO_COMMON_COUNTER_H
