/*
 * 此文件只能在一个项目中被编译一次
 * 最好被写在main或者Application定义的文件里
*/

//#define OPERATOR_NEW_DELETE
#if defined(OPERATOR_NEW_DELETE)

#include <cplusplus_basic.hpp>

/*new*/
void * operator new(std::size_t arg){
    return memory::malloc(arg);
}

/*new*/
void* operator new(std::size_t arg, const std::nothrow_t&){
    return memory::malloc(arg);
}

/*delete*/
void operator delete(void * arg){
    return memory::free(arg);
}

/*delete*/
void operator delete(void * arg,std::size_t){
    return memory::free(arg);
}

/*new[]*/
void * operator new[](std::size_t arg){
    return memory::malloc(arg);
}

/*new[]*/
void* operator new[] (std::size_t arg, const std::nothrow_t&){
    return memory::malloc(arg);
}

/*delete[]*/
void operator delete[](void * arg){
    return memory::free(arg);
}

/*delete[]*/
void operator delete[](void * arg,std::size_t){
    return memory::free(arg);
}

#endif

