
#ifndef _SPIN_BOX_HPP__0x0098
#define _SPIN_BOX_HPP__0x0098

#include <mutex>
#include <atomic>
//#include <iostream>
//static int test = 0;

namespace _pm_file {

class spin_mutex {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    spin_mutex() = default;
    spin_mutex(const spin_mutex&) = delete;
    spin_mutex& operator= (const spin_mutex&) = delete;
    void lock() noexcept(true){
        while(flag.test_and_set()){
            //std::cout<<"."<<++test;
        }
    }
    void unlock() noexcept(true){
        flag.clear();
    }
    bool try_lock() noexcept(true){
        return (flag.test_and_set()==false);
    }
};

}/*_pm_file*/

#endif
