#ifndef SARGASSO_COMMON_REFERENCE_H_
#define SARGASSO_COMMON_REFERENCE_H_

#include <cstdint>
#include <stdexcept>

namespace sargasso {
namespace common {

class Counter;

template <typename T>
class Reference {
   public:
    explicit Reference(const uint64_t id, T* data);
    Reference(const Reference&);  // copy
    ~Reference();

    T* operator->();
    const T* operator->() const;

    const uint64_t get_id() const;

    bool is_alive() const;
    bool is_dead() const;
    void destroy();

   private:
    const uint64_t _id;
    Counter* _ref_count;
    T* _ref;
};

class Counter {
   public:
    Counter() = default;

    void reset() {
        _count = 0;
    }

    Counter& operator++() {
        _count++;
        return *this;
    }

    Counter& operator--() {
        if (_count - 1 != UINT64_MAX) {
            _count--;
        } else {
            _count = 0;
        }
        return *this;
    }

    bool operator==(uint64_t n) const {
        return _count == n;
    }

    bool operator>(uint64_t n) const {
        return _count > n;
    }

    bool operator>=(uint64_t n) const {
        return _count >= n;
    }

    bool operator<=(uint64_t n) const {
        return _count <= n;
    }

    bool operator<(uint64_t n) const {
        return _count <= n;
    }

   private:
    uint64_t _count;
};

template <typename T>
Reference<T>::Reference(const uint64_t id, T* data) : _id(id), _ref(data) {
    _ref_count = new Counter();
    if (_ref) {
        ++(*_ref_count);
    }
}

template <typename T>
Reference<T>::Reference(const Reference<T>& original) : _id(original._id) {
    _ref = original._ref;
    _ref_count = original._ref_count;
    ++(*_ref_count);
}

template <typename T>
Reference<T>::~Reference() {
    --(*_ref_count);

    if (!is_alive()) {

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
const uint64_t Reference<T>::get_id() const {
    return _id;
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
    // doesn't immediately destroy, but object is destroyed as soon as the Reference is destroyed.
    _ref_count->reset();
}

}  // namespace common
}  // namespace sargasso

#endif
