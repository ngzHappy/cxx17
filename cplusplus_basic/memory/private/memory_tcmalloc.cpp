#include <Qt/boost/config.hpp>

#ifndef HAS_TCMALLOC_CONCEPT

#else
/*has tcmalloc*/

extern "C" {
BOOST_SYMBOL_IMPORT void __tcmalloc();
}

namespace  {

class ForceLoadTCMalloc{
public:
    ForceLoadTCMalloc(){
        /*调用此函数,强制加载tcmalloc dll*/
        __tcmalloc();
    }
}____;

}

#endif


