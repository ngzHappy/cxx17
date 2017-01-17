#include "../Memory.hpp"
#include <atomic>

namespace {
namespace __cpp {
namespace __private{
namespace __memory {
namespace memory {

std::atomic_bool _d_is_construct_static;
char _d_once_flag[sizeof(std::once_flag)];

}/*memory*/
}/*__memory*/
}/*__private*/
}/*__cpp*/
}/*namespace*/

namespace memory {

bool __memory__construct_static::__is_construct_static() noexcept(true) {
    return __cpp::__private::__memory::memory::_d_is_construct_static.load();
}

void __memory__construct_static::__set_construct_static() noexcept(true) {
    return __cpp::__private::__memory::memory::_d_is_construct_static.store(true);
}

bool __memory__construct_static::__run_once(void(*arg)(void)) noexcept(true) {
    if (arg==nullptr) { return false; }
    /*it will not be deleted*/
    static auto * _d_run_once_flag=
        new(__cpp::__private::__memory::memory::_d_once_flag) std::once_flag;
    try {

        const auto call_funcs=[](void(*fun)(void)) {
            /*初始化malloc free函数*/
            memory::free(memory::malloc(1));
            /*执行用户自定义函数*/
            fun();
        };

        std::call_once(*_d_run_once_flag,call_funcs,arg);
    }
    catch (...) {
        /*do nothing*/
        return false;
    }
    return true;
}

}/*namespace memory*/


