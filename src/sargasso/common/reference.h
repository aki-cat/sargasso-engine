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
    Reference() = delete;
    explicit Reference(T* data);
    Reference(const Reference&);  // copy
    ~Reference();

    T* operator->();
    const T* operator->() const;
    uint64_t copy_count() const;

    bool is_alive() const;
    bool is_dead() const;
    void clear();

   private:
    Counter* _ref_count = nullptr;
    T* _ref = nullptr;
};

template <typename T>
Reference<T>::Reference(T* data) : _ref(data) {
    Log("Reference").debug("Reference<0x%x> created", _ref);

    _ref_count = new Counter();
    if (_ref) {
        _ref_count->increase();
    }
}

template <typename T>
Reference<T>::Reference(const Reference<T>& original) {
    Log("Reference")
        .debug("Reference<0x%x> copied (copy#%ld).", original._ref, original._ref_count->get());
    if (original._ref) {
        _ref = original._ref;
        _ref_count = original._ref_count;
        _ref_count->increase();
    } else {
        throw std::runtime_error("Attempted to copy invalid reference.");
    }
}

template <typename T>
Reference<T>::~Reference() {
    if (is_dead()) {
        return;
    }

    _ref_count->decrease();
    if (_ref_count->get() == 0) {
        Log("Reference").debug("Reference<0x%x> deleted.", _ref);
        delete _ref;
        delete _ref_count;
    }
}

template <typename T>
T* Reference<T>::operator->() {
    if (is_dead()) {
        throw std::runtime_error("Attempt to access dead reference.");
    }
    return _ref;
}

template <typename T>
const T* Reference<T>::operator->() const {
    if (is_dead()) {
        throw std::runtime_error("Attempt to access dead reference.");
    }
    return _ref;
}

template <typename T>
uint64_t Reference<T>::copy_count() const {
    if (is_dead()) {
        return 0;
    }
    return _ref_count->get();
}

template <typename T>
bool Reference<T>::is_alive() const {
    return !is_dead();
}

template <typename T>
bool Reference<T>::is_dead() const {
    return _ref == nullptr || _ref_count == nullptr || _ref_count->get() == 0;
}

template <typename T>
void Reference<T>::clear() {
    if (is_dead()) {
        return;
    }
    _ref_count->decrease();

    _ref = nullptr;
    _ref_count = nullptr;
}

}  // namespace common
}  // namespace sargasso

#endif
