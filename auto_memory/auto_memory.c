#include <stdlib.h>
#include <boost/config.hpp>

#ifdef HAS_TCMALLOC_CONCEPT

BOOST_SYMBOL_IMPORT void * tc_malloc(size_t size);
BOOST_SYMBOL_IMPORT void   tc_free(void* ptr);
BOOST_SYMBOL_IMPORT void * tc_realloc(void* ptr, size_t size);
BOOST_SYMBOL_IMPORT void * tc_calloc(size_t nmemb, size_t size);
BOOST_SYMBOL_IMPORT size_t tc_malloc_size(void* ptr);

#define std_malloc        tc_malloc
#define std_calloc        tc_calloc
#define std_realloc       tc_realloc
#define std_free          tc_free
#define std_out_of_memory exit
#define std_size          tc_malloc_size

#else

/*change the functions to your define*/
#define std_malloc        malloc
#define std_calloc        calloc
#define std_realloc       realloc
#define std_free          free
#define std_out_of_memory exit
#if defined(WIN32)||defined(_WIN32)
#define std_size          _msize
#else
#define std_size          malloc_usable_size
#endif

#endif

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

BOOST_SYMBOL_EXPORT size_t auto_size(void *arg){
    if ((arg==&null_data)||(arg==0)) {
        return 0;
    }
    return (size_t)(std_size(arg));
}

BOOST_SYMBOL_EXPORT void auto_memory_gc() {

}

/****************************************************************/






