#include "../gumbo.h"
#include "../../cplusplus_basic.hpp"

namespace  {
namespace __private {

static void* _malloc_wrapper(void* unused, size_t size) {
    return memory::malloc(size);
    (void)unused;
}

static void _free_wrapper(void* unused, void* ptr) {
    memory::free(ptr);
    (void)unused;
}

inline static GumboOptions * _cplusplusGumboDefaultOptions(){
    const static GumboOptions _kGumboDefaultOptions = {
        &_malloc_wrapper,
        &_free_wrapper,
        nullptr,
        8,
        false,
        -1,
        GUMBO_TAG_LAST,
        GUMBO_NAMESPACE_HTML};
    return const_cast<GumboOptions *>(&_kGumboDefaultOptions);
}

}/**/
}/**/

namespace gumbo {

GumboOptions * defaultOptions(){
    return __private::_cplusplusGumboDefaultOptions();
}

}/*gumbo*/
