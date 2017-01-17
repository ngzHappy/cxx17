#ifndef _unordered_map_HASH_CONTAINERS_HPP_0x1222
#define _unordered_map_HASH_CONTAINERS_HPP_0x1222

#include "hash.hpp"
#include <unordered_map>
#include "../cplusplus_basic.hpp"

namespace containers {

template < typename K,
    typename V,
    typename H=containers::MixHash<K>,
    class P=std::equal_to<void> >
    using unordered_map=std::unordered_map<K,V,H,P,
    memory::Allocator<std::pair<const K,V>>>;

template < typename K,
    typename V,
    typename H=containers::MixHash<K>,
    class P=std::equal_to<void> >
    using unordered_multimap=std::unordered_multimap<K,V,H,P,
    memory::Allocator<std::pair<const K,V>>>;

}/*containers*/

#endif
