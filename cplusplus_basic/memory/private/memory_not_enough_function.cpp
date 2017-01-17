#include "../Memory.hpp"
#include <iostream>
#include <mutex>
#include <shared_mutex>

namespace memory{

namespace {
namespace _memory_private_not_enough {

typedef std::shared_timed_mutex _mutex_t;
typedef std::unique_lock<_mutex_t> _ulock_t;
typedef std::shared_lock<_mutex_t> _slock_t;

class Data {
    _mutex_t _pm_mutex;
    function_memory_not_enough _pm_function;
public:

    function_memory_not_enough get() {
        _slock_t _{ _pm_mutex };
        return _pm_function;
    }

    function_memory_not_enough set(function_memory_not_enough arg) {
        if (arg==nullptr) { return get(); }
        _ulock_t _{ _pm_mutex };
        auto old=_pm_function;
        _pm_function=arg;
        return old;
    }

    Data() {
        _pm_function=[]() {
            std::cout<<"memory is not enough"<<std::endl;
        };
    }

};

static char _psd_[sizeof(Data)];
Data * get() {
    static auto ans=::new(_psd_)Data;
    return ans;
}

}/*_memory_private_not_enough*/
}/*namespace*/

function_memory_not_enough get_memory_not_enough() {
    return _memory_private_not_enough::get()->get();
}

function_memory_not_enough set_memory_not_enough(function_memory_not_enough arg) {
    return _memory_private_not_enough::get()->set(arg);
}

}/*memory*/
