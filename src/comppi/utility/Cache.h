#ifndef COMPPI_UTILITY_CACHE_H_
#define COMPPI_UTILITY_CACHE_H_

#include <deque>
#include <utility>

namespace comppi {
namespace utility {

template <typename Key, typename Value, size_t MaxSize>
class Cache {
public:
    Cache() {}

    bool get(const Key& key, Value& value) {
        for (auto it = _cache.rbegin(); it != _cache.rend(); ++it) {
            if (it->first == key) {
                value = it->second;
                return true;
            }
        }

        return false;
    }

    void add(const Key& key, const Value& value) {
        if (_cache.size() == MaxSize) {
            _cache.pop_front();
        }

        _cache.push_back(std::make_pair(key, value));
    }

private:
    std::deque<std::pair<Key, Value>> _cache;
};

} // namespace utility
} // namespace comppi

#endif // COMPPI_UTILITY_CACHE_H_
