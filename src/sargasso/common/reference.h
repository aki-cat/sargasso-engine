#ifndef SARGASSO_COMMON_REFERENCE_H_
#define SARGASSO_COMMON_REFERENCE_H_

#include "sargasso/common/counter.h"
#include "sargasso/common/log.h"

#include <cstdlib>
#include <stdexcept>

namespace sargasso {
namespace common {

template <typename T>
class Reference {
   public:
    Reference() = default;
    Reference(T* data);
    Reference(const Reference&);
    Reference& operator=(const Reference&);
    ~Reference();

    T* operator->();
    const T* operator->() const;
    size_t copyCount() const;

    const T& get() const;
    T& get();

    bool isAlive() const;
    bool isDead() const;
    void clear();

   private:
    Counter* _ref_count = nullptr;
    T* _ref = nullptr;
};

template <typename T>
Reference<T>::Reference(T* data) : _ref(data) {
    // Log("Reference").debug("Reference<%p> created", _ref);

    _ref_count = new Counter();
    if (_ref) {
        _ref_count->increase();
    }
}

template <typename T>
Reference<T>& Reference<T>::operator=(const Reference& assigned) {
    _ref = assigned._ref;
    _ref_count = assigned._ref_count;
    if (_ref_count) {
        // Log("Reference").debug("Reference<%p> copy-assigned (copy#%ld).", _ref, _ref_count->get());
        _ref_count->increase();
    }
    return *this;
}

template <typename T>
Reference<T>::Reference(const Reference<T>& original) {
    _ref = original._ref;
    _ref_count = original._ref_count;
    if (_ref_count) {
        // Log("Reference").debug("Reference<%p> copied (copy#%ld).", _ref, _ref_count->get());
        _ref_count->increase();
    }
}

template <typename T>
Reference<T>::~Reference() {
    // Log("Reference").debug("Reference<%p> destructor called.", _ref);

    if (_ref == nullptr || _ref_count == nullptr) {
        return;
    }

    _ref_count->decrease();
    if (_ref_count->get() == 0) {
        // Log("Reference").debug("Reference<%p> deleted.", _ref);
        delete _ref;
        delete _ref_count;
    }
}

template <typename T>
T* Reference<T>::operator->() {
    if (isDead()) {
        throw std::runtime_error("Attempt to access dead reference.");
    }
    return _ref;
}

template <typename T>
const T* Reference<T>::operator->() const {
    if (isDead()) {
        throw std::runtime_error("Attempt to access dead reference.");
    }
    return _ref;
}

template <typename T>
size_t Reference<T>::copyCount() const {
    if (isDead()) {
        return 0;
    }
    return _ref_count->get();
}

template <typename T>
const T& Reference<T>::get() const {
    if (isDead()) {
        throw std::runtime_error("Attempt to access dead reference.");
    }
    return *_ref;
}

template <typename T>
T& Reference<T>::get() {
    if (isDead()) {
        throw std::runtime_error("Attempt to access dead reference.");
    }
    return *_ref;
}

template <typename T>
bool Reference<T>::isAlive() const {
    return !isDead();
}

template <typename T>
bool Reference<T>::isDead() const {
    return _ref == nullptr || _ref_count == nullptr || _ref_count->get() == 0;
}

template <typename T>
void Reference<T>::clear() {
    if (isDead()) {
        return;
    }
    _ref_count->decrease();

    _ref = nullptr;
    _ref_count = nullptr;
}

}  // namespace common
}  // namespace sargasso

#endif  // SARGASSO_COMMON_REFERENCE_H_
