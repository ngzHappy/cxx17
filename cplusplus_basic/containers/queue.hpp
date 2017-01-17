#ifndef _queue_HASH_CONTAINERS_HPP_0x1222
#define _queue_HASH_CONTAINERS_HPP_0x1222

#include <queue>
#include "deque.hpp"
#include "vector.hpp"

namespace containers {

template<typename T,typename C=containers::deque<T>>
using queue=std::queue<T,C>;

template <typename T,
    typename C=containers::vector<T>,
    typename Cp=std::less<void>>
    using priority_queue=std::priority_queue<T,C,Cp>;

}/*containers*/

#endif
