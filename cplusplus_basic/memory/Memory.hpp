#ifndef _MEMORY_HPP_0x877160
#define _MEMORY_HPP_0x877160

#include <auto_memory.hpp>
#include "../config/config.hpp"

namespace memory {

inline size_t size(void * arg){ return auto_size(arg); }
inline void out_of_memory() { auto_out_of_memory(); }
inline void * malloc(size_t arg) { return auto_malloc(arg); }
inline void free(void * arg) { return auto_free(arg); }
inline void * realloc(void * o,size_t os,size_t ns) { return auto_realloc(o,os,ns); }
inline void * calloc(size_t n,size_t s) { return auto_calloc(n,s); }
inline void free(const void *arg) { memory::free(const_cast<void*>(arg)); }
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void clean();
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void quick_exit(int=-2);
inline void freePoolMemory() { memory::clean(); }
inline size_t size(const void * arg){ return auto_size(const_cast<void*>(arg)); }

}/*memory*/

#if !defined(MEMORY_CLASS_NEW_DELETE)

#if defined(__cplusplus)
#define MEMORY_CLASS_NEW_DELETE public: \
static void operator delete(void *arg) { memory::free(arg); } \
static void operator delete[](void *arg) { memory::free(arg); } \
static void * operator new(std::size_t n) { return memory::malloc(n); } \
static void * operator new[](std::size_t n) { return memory::malloc(n); } \
static void * operator new(std::size_t,void * arg) { return arg; } \
static void * operator new[](std::size_t,void * arg) { return arg; } \
static void operator delete[](void *,void *){} \
static void operator delete(void *,void *){}
#else
#define MEMORY_CLASS_NEW_DELETE
#endif/*MEMORY_CLASS_NEW_DELETE*/

#endif

namespace memory {

class _CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT __memory__construct_static {
    friend void constructStatic();
protected:
    static bool __is_construct_static() noexcept(true);
    static void __set_construct_static() noexcept(true);
    static bool __run_once(void(*)(void)) noexcept(true);
};

}/*namespace memory*/

/*****************************************/
#include "private/_Allocator.hpp"
#include "private/_MakeShared.hpp"
#include "private/_MakeFunction.hpp"
#include "private/_MemoryStatic.hpp"
#include "private/_MemoryApplication.hpp"
#include "StackPointer.hpp"
/*****************************************/

#endif


