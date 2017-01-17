#ifndef _map_HASH_CONTAINERS_HPP_0x1222
#define _map_HASH_CONTAINERS_HPP_0x1222

#include <map>
#include "../cplusplus_basic.hpp"

namespace containers {

template<typename K,typename V,typename L=std::less<void>>
using map=std::map<K,V,L,
    memory::Allocator<std::pair<K,V> > >;

template<typename K,typename V,typename L=std::less<void>>
using multimap=std::multimap<K,V,L,
    memory::Allocator<std::pair<K,V> > >;

}/*containers*/

#endif
