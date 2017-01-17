#ifndef _vector_HASH_CONTAINERS_HPP_0x1222
#define _vector_HASH_CONTAINERS_HPP_0x1222

#include <vector>
#include "../cplusplus_basic.hpp"

namespace containers {

template<typename T>
using vector=std::vector<T,memory::Allocator<T>>;

}/*containers*/

#endif
