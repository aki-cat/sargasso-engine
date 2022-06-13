#include "sargasso/common/counter.h"

#include <cstdint>
#include <iostream>

namespace sargasso {
namespace common {

void Counter::reset() {
    _count = 0;
}

void Counter::increase() {
    _count++;
}

void Counter::decrease() {
    if (_count == 0) {
        return;
    }
    _count--;
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

uint64_t Counter::get() const {
    return _count;
}

}  // namespace common
}  // namespace sargasso
