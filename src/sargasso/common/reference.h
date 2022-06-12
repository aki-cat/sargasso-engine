#ifndef SARGASSO_COMMON_REFERENCE_H_
#define SARGASSO_COMMON_REFERENCE_H_

#include "sargasso/common/counter.h"
#include "sargasso/common/log.h"

#include <cstdint>
#include <stdexcept>

namespace sargasso {
namespace common {

template <typename T>
class Reference {
   public:
    explicit Reference(T* data);
    Reference(const Reference&);  // copy
    ~Reference();

    T* operator->();
    const T* operator->() const;

    bool is_alive() const;
    bool is_dead() const;
    void destroy();

   private:
    Counter* _ref_count;
    T* _ref;
};

template <typename T>
Reference<T>::Reference(T* data) : _ref(data) {
    Log("Reference").debug("Reference<0x%x> created", _ref);

    _ref_count = new Counter();
    if (_ref) {
        (*_ref_count)++;
    }
}

template <typename T>
Reference<T>::Reference(const Reference<T>& original) {
    Log("Reference")
        .debug("Reference<0x%x> copied (copy#%ld).", original._ref, *original._ref_count);
    _ref = original._ref;
    _ref_count = original._ref_count;
    (*_ref_count)++;
}

template <typename T>
Reference<T>::~Reference() {
    (*_ref_count)--;

    if (!is_alive()) {
        Log("Reference").debug("Reference<0x%x> deleted.", _ref);
        delete _ref;
        delete _ref_count;
    }
}

template <typename T>
T* Reference<T>::operator->() {
    if (!is_alive()) {
        throw std::runtime_error("Attempt to access dead reference.");
    }
    return _ref;
}

template <typename T>
const T* Reference<T>::operator->() const {
    if (!is_alive()) {
        throw std::runtime_error("Attempt to access dead reference.");
    }
    return _ref;
}

template <typename T>
bool Reference<T>::is_alive() const {
    return !is_dead();
}

template <typename T>
bool Reference<T>::is_dead() const {
    return !_ref || (*_ref_count) == 0;
}

template <typename T>
void Reference<T>::destroy() {
    Log("Reference").debug("Reference<0x%x> flagged for deletion.", _ref);

    // doesn't immediately destroy, but object is destroyed as soon as the Reference is destroyed.
    _ref_count->reset();
}

}  // namespace common
}  // namespace sargasso

#endif
