#ifndef ____AUTO_MEMORY_HPP
#define ____AUTO_MEMORY_HPP

#include <stdlib.h>
#include <boost/config.hpp>

#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/

BOOST_SYMBOL_IMPORT void * auto_malloc(size_t);
BOOST_SYMBOL_IMPORT void * auto_realloc(void*,size_t,size_t);
BOOST_SYMBOL_IMPORT void * auto_calloc(size_t,size_t);
BOOST_SYMBOL_IMPORT void auto_free(void *);
BOOST_SYMBOL_IMPORT void auto_out_of_memory()/*no return*/;

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif // AUTO_MEMORY_HPP


