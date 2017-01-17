#include <atomic>
#include <auto_memory.hpp>
#include "../../thread/ShadowThread.hpp"

namespace  {

void __memory_clean_thread_function(void(*fun)(void *),void * data) {
    thread::runInShadowThread(fun,data);
}/*__memory_clean_thread_function*/

}/*namespace*/

namespace memory {

_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void clean(){

    static  std::atomic_flag isOnRun = ATOMIC_FLAG_INIT;
    if( isOnRun.test_and_set() == false ){
        __memory_clean_thread_function([](void *arg){
            auto data = reinterpret_cast<std::atomic_flag *>(arg);
            try{
                auto_memory_gc();
            }catch(...){}
            data->clear();
        },&isOnRun);
    }

}/*void clean()*/

}/*memory*/





