#ifndef _list_HASH_CONTAINERS_HPP_0x1222
#define _list_HASH_CONTAINERS_HPP_0x1222

#include <list>
#include "../cplusplus_basic.hpp"

namespace containers {

template<typename T>
using list=std::list<T,memory::Allocator<T>>;

}/*containers*/

#endif
