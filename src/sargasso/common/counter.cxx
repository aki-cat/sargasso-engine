#include "sargasso/common/counter.h"

#include <cstdlib>

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

bool Counter::operator==(size_t n) const {
    return _count == n;
}

bool Counter::operator>(size_t n) const {
    return _count > n;
}

bool Counter::operator>=(size_t n) const {
    return _count >= n;
}

bool Counter::operator<=(size_t n) const {
    return _count <= n;
}

bool Counter::operator<(size_t n) const {
    return _count <= n;
}

size_t Counter::get() const {
    return _count;
}

}  // namespace common
}  // namespace sargasso
