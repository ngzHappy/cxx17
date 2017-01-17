
#ifndef BOOST_POOL_MUTEX_HPP
#define BOOST_POOL_MUTEX_HPP

#include <mutex>

namespace boost{
namespace details{
namespace pool{

class default_mutex :public std::recursive_mutex {
    using super=std::recursive_mutex;
public:
    using super::super;
    using super::unlock;
    using super::try_lock;
    void lock(){ while(false==try_lock()){} }
};

} // namespace pool
} // namespace details
} // namespace boost

#endif
