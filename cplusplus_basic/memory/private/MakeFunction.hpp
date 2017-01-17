#ifndef _m_MAKEFUNCTION_HPP_CPP_
#define _m_MAKEFUNCTION_HPP_CPP_() 1

#include "../Memory.hpp"
#include "Allocator.hpp"
#include <functional>

namespace memory {

template<typename _m_FunctionType_>
inline auto make_function() ->std::function<_m_FunctionType_> { return{}; }

template<typename _m_FunctionType_,typename _m0_Args_>
inline auto make_function(_m0_Args_&&_m_args_)->std::function<_m_FunctionType_> {
    return std::forward<_m0_Args_>(_m_args_);
}

}/*memory*/


#endif

