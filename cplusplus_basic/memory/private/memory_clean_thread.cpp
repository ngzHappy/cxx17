
#include "../../thread/ShadowThread.hpp"

extern void __memory_clean_thread_function(void(*)(void *),void *);
void __memory_clean_thread_function(void(*fun)(void *),void * data) {
    thread::runInShadowThread(fun,data);
}

