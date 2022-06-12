#include "sargasso/common/counter.h"

#include <cstdint>

namespace sargasso {
namespace common {

void Counter::reset() {
    _count = 0;
}

Counter& Counter::operator++() {
    _count++;
    return *this;
}

Counter& Counter::operator--() {
    if (_count - 1 != UINT64_MAX) {
        _count--;
    } else {
        _count = 0;
    }
    return *this;
}

Counter Counter::operator++(int) {
    Counter temp = *this;
    _count++;
    return temp;
}

Counter Counter::operator--(int) {
    Counter temp = *this;
    if (_count - 1 != UINT64_MAX) {
        _count--;
    } else {
        _count = 0;
    }
    return temp;
}

uint64_t Counter::operator*() const {
    return _count;
}

bool Counter::operator==(uint64_t n) const {
    return _count == n;
}

bool Counter::operator>(uint64_t n) const {
    return _count > n;
}

bool Counter::operator>=(uint64_t n) const {
    return _count >= n;
}

bool Counter::operator<=(uint64_t n) const {
    return _count <= n;
}

bool Counter::operator<(uint64_t n) const {
    return _count <= n;
}

}  // namespace common
}  // namespace sargasso
