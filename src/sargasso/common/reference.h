#ifndef SARGASSO_COMMON_REFERENCE_H_
#define SARGASSO_COMMON_REFERENCE_H_

#include <cstdint>
#include <stdexcept>

namespace sargasso {
namespace common {

template <typename T>
class Reference {
   public:
    explicit Reference(const uint64_t id, T& data);

    T* operator->();
    const T* operator->() const;

    const uint64_t get_id() const;

    bool is_alive() const;

   private:
    const uint64_t _id;
    T& _data;
};

template <typename T>
Reference<T>::Reference(const uint64_t id, T& data) : _id(id), _data(data) {}

template <typename T>
T* Reference<T>::operator->() {
    if (!is_alive()) {
        throw std::runtime_error("Attempt to access dead reference.");
    }
    return &_data;
}

template <typename T>
const T* Reference<T>::operator->() const {
    if (!is_alive()) {
        throw std::runtime_error("Attempt to access dead reference.");
    }
    return _data;
}

template <typename T>
const uint64_t Reference<T>::get_id() const {
    return _id;
}

template <typename T>
bool Reference<T>::is_alive() const {
    // TBD
    return true;
}

}  // namespace common
}  // namespace sargasso

#endif
