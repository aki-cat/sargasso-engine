#ifndef SARGASSO_ENGINE_CONTAINERS_H
#define SARGASSO_ENGINE_CONTAINERS_H

#include <unordered_map>
#include <vector>

namespace SargassoEngine {
namespace Common {

template <typename T>
using DynamicArray = std::vector<T>;

template <typename K, typename V>
using Dictionary = std::unordered_map<K, V>;

}  // namespace Common
}  // namespace SargassoEngine
#endif
