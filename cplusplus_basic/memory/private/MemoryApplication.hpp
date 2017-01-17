#ifndef _m_MEMORY_APPLICATION_1_
#define _m_MEMORY_APPLICATION_1_

#include "../Memory.hpp"

#ifndef IS_PLUGIN_FIRE
#define IS_PLUGIN_FIRE false
#endif

namespace memory {
class _CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT Application {
    static void _p_setMainConstruct();
    static void _p_clearMainConstruct();
    static void _p_setMainQuit();
    static void _p_clearMainQuit();
    static void _p_main_construct();
    static void _p_main_destruct();
public:
    Application() { _p_setMainConstruct(); _p_main_construct(); }

    static bool isMainConstruct();
    static bool isMainQuit();
    inline void quit() { _p_setMainQuit(); _p_main_destruct(); }

    ~Application() { quit(); }
};

}/*namespace memory*/

#endif

