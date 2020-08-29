#ifndef SARGASSO_ENGINE_POOL_H
#define SARGASSO_ENGINE_POOL_H

#include "common/containers.h"

namespace SargassoEngine {
namespace Common {

template <typename T>
class Pool {
   public:
    using ID = uint32_t;
    // class members
    static const uint32_t DEFAULT_SIZE = 16;
    static const uint32_t INVALID = 0xffffffff;

    // constructors/destructors
    Pool();
    ~Pool();

    // public methods
    ID create(const T& object);
    void destroy(ID id);
    const T& get(ID id) const;
    T& get(ID id);

   private:
    // private attributes
    T* _data;
    Dictionary<ID, bool> _used_slots;
    uint32_t _used;
    uint32_t _capacity;

    // private methods
    ID _next_free_id();
    void _grow();
};

template <typename T>
inline Pool<T>::Pool()
    : _data(new T[DEFAULT_SIZE]), _used_slots(), _used(0), _capacity(DEFAULT_SIZE) {}

template <typename T>
inline Pool<T>::~Pool() {
    delete[] _data;
}

template <typename T>
inline typename Pool<T>::ID Pool<T>::create(const T& object) {
    _used++;

    if (_used <= _capacity / 2) {
        _grow();
    }

    Pool<T>::ID slot = _next_free_id();
    _data[slot] = object;
    _used_slots.insert({slot, true});

    return slot;
}

template <typename T>
inline void Pool<T>::destroy(Pool<T>::ID slot) {
    if (!_used_slots.at(slot)) {
        return;
    }

    _used--;
    _used_slots.erase(slot);

    // TODO: free unused memory?
}

template <typename T>
inline const T& Pool<T>::get(Pool<T>::ID id) const {
    if (!_used_slots.at(id)) {
        throw "No such object";
    }
    return _data[id];
}

template <typename T>
inline T& Pool<T>::get(Pool<T>::ID id) {
    if (!_used_slots.at(id)) {
        throw "No such object";
    }
    return _data[id];
}

template <typename T>
inline typename Pool<T>::ID Pool<T>::_next_free_id() {
    for (Pool<T>::ID id = 0; id < _capacity; id++) {
        try {
            bool is_used = _used_slots.at(id);
            if (!is_used) {
                return id;
            }
        } catch (std::out_of_range) {
            return id;
        }
    }
    return INVALID;
}

template <typename T>
void Pool<T>::_grow() {
    // reference old data
    T* old_data = _data;
    uint32_t old_capacity = _capacity;

    // alloc space for new data
    _capacity *= 2;
    _data = new T[(size_t)_capacity];
    for (uint32_t index = 0; index < old_capacity; index++) {
        _data[index] = old_data[index];
    }

    // delete old data
    delete[] old_data;
}

}  // namespace Common
}  // namespace SargassoEngine

#endif
