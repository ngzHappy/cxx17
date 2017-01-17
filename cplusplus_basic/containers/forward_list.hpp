#ifndef _forward_list_HASH_CONTAINERS_HPP_0x1222
#define _forward_list_HASH_CONTAINERS_HPP_0x1222

#include <forward_list>
#include "../cplusplus_basic.hpp"

namespace containers {

template<typename T>
using forward_list=std::forward_list<T,memory::Allocator<T>>;

}/*containers*/

#endif
