#ifndef ____AUTO_MEMORY_HPP
#define ____AUTO_MEMORY_HPP

#include <stddef.h>
#include <stdlib.h>
#include <boost/config.hpp>

struct cplusplus_unnamed_ojbect {};

#ifndef CPLUSPLUS_OBJECT
#ifdef __cplusplus
#define CPLUSPLUS_OBJECT(x)private: \
    static constexpr size_t __0x21_size() noexcept(true) {return sizeof(x);} \
    public: \
    static void * operator new(size_t n){return auto_malloc(n);} \
    static void operator delete(void * a){return auto_free(a);} \
    static void * operator new[](size_t n){return auto_malloc(n);} \
    static void operator delete[](void * a){return auto_free(a);} \
    static void * operator new(std::size_t,void * arg) { return arg; } \
    static void * operator new[](std::size_t,void * arg) { return arg; } \
    static void operator delete[](void *,void *){} \
    static void operator delete(void *,void *){}
#else/*__cplusplus*/
#define CPLUSPLUS_OBJECT(x)
#endif/*__cplusplus*/
#endif/*CPLUSPLUS_OBJECT*/

#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/

BOOST_SYMBOL_IMPORT void * auto_malloc(size_t);
BOOST_SYMBOL_IMPORT void * auto_realloc(void*,size_t,size_t);
BOOST_SYMBOL_IMPORT void * auto_calloc(size_t,size_t);
BOOST_SYMBOL_IMPORT void auto_free(void *);
BOOST_SYMBOL_IMPORT size_t auto_size(void *);
BOOST_SYMBOL_IMPORT void auto_out_of_memory()/*no return*/;
BOOST_SYMBOL_IMPORT void auto_memory_gc()/*启动一次gc*/;

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif // AUTO_MEMORY_HPP


