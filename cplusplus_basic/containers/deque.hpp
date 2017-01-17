#ifndef _deque_HASH_CONTAINERS_HPP_0x1222
#define _deque_HASH_CONTAINERS_HPP_0x1222

#include <deque>
#include "../cplusplus_basic.hpp"

namespace containers {

template<typename T>
using deque=std::deque<T,memory::Allocator<T>>;

}/*containers*/

#endif

