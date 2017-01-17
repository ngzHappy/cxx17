
#ifndef BOOST_SMART_PTR_DETAIL_LIGHTWEIGHT_MUTEX_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_LIGHTWEIGHT_MUTEX_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <mutex>

namespace boost
{

namespace detail
{

class lightweight_mutex :public std::recursive_mutex {
    using super=std::recursive_mutex;
public:
    using super::super;
    using super::unlock;
    using super::try_lock;
    void lock(){ while(false==try_lock()){} }
    typedef std::unique_lock<lightweight_mutex> scoped_lock;
};

}/*detail*/

}/*boost*/

#endif // #ifndef BOOST_SMART_PTR_DETAIL_LIGHTWEIGHT_MUTEX_HPP_INCLUDED
