#include <stdlib.h>
#include <boost/config.hpp>

/*change the functions to your define*/
#define std_malloc        malloc
#define std_calloc        calloc
#define std_realloc       realloc
#define std_free          free
#define std_out_of_memory exit

/****************************************************************/

static struct { int _unamed_[4]; } null_data;

BOOST_SYMBOL_EXPORT void auto_out_of_memory() {
    std_out_of_memory(-7777);
}

BOOST_SYMBOL_EXPORT void * auto_malloc(size_t arg) {
    if (arg<1) { return &null_data; }
    void * ans=std_malloc(arg);
    if (ans==0) {
        auto_out_of_memory();
    }
    return ans;
}

BOOST_SYMBOL_EXPORT void * auto_realloc(void* argO,size_t argOSize,size_t argNSize) {
    if (argO==&null_data) {
        return auto_malloc(argNSize);
    }
    void * ans=std_realloc(argO,argNSize);
    if (ans==0) {
        auto_out_of_memory();
    }
    return ans;
    (void)argOSize;
}

BOOST_SYMBOL_EXPORT void * auto_calloc(size_t argN,size_t argS) {
    if ((argN<1)||(argS<1)) {
        return &null_data;
    }
    void * ans=std_calloc(argN,argS);
    if (ans==0) {
        auto_out_of_memory();
    }
    return ans;
}

BOOST_SYMBOL_EXPORT void auto_free(void* arg) {
    if (arg==&null_data) {
        return;
    }
    std_free(arg);
}

BOOST_SYMBOL_EXPORT void auto_memory_gc() {

}

/****************************************************************/






