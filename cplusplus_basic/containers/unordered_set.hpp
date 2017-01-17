#ifndef _unordered_set_HASH_CONTAINERS_HPP_0x1222
#define _unordered_set_HASH_CONTAINERS_HPP_0x1222

#include "hash.hpp"
#include <unordered_set>
#include "../cplusplus_basic.hpp"

namespace containers {

template < typename K,
    typename H=containers::MixHash<K>,
    class P=std::equal_to<void> >
    using unordered_set=std::unordered_set<K,H,P,
    memory::Allocator< K >>;

template < typename K,
    typename H=containers::MixHash<K>,
    class P=std::equal_to<void> >
    using unordered_multiset=std::unordered_multiset<K,H,P,
    memory::Allocator<K>>;

}/*containers*/

#endif
