/*
 * 此文件只能在一个项目中被编译一次
 * 最好被写在main或者Application定义的文件里
*/
#include <Qt/boost/config.hpp>

#if defined(HAS_TCMALLOC_CONCEPT)

extern "C" {/*extern "C"*/
BOOST_SYMBOL_IMPORT void __tcmalloc();
}/*extern "C"*/

namespace  {

class _c__init_tcmalloc{
public:
    _c__init_tcmalloc(){
    __tcmalloc();
    }
}_v_init_tcmalloc_;

}/*namespace*/

#endif

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

