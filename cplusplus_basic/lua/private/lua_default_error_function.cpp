#define LUA_CORE

#include "../lua.hpp"
#include "lua_default_error_function.hpp"

namespace luaL {

int default_error_function(lua_State * L) {
    if (L==nullptr) { return 0; }
    lua::checkstack(L,3);

    try {
        if (lua::isstring(L,-1)) {
            size_t varL;
            const char * varD=lua::tolstring(L,-1,&varL);
            exception::information_handle(varD,varL,0,"?lua","?lua.cpp");
        }
        else {
            size_t varL;
            const char * varD=luaL::tolstring(L,-1,&varL);
            if (varD&&(varL>0)) {
                exception::information_handle(varD,varL,0,"?lua","?lua.cpp");
            }
            else {
                exception::information_handle("?lua",4,0,"?lua","?lua.cpp");
            }
        }
    }catch(...){
        exception::information_handle("?",1,
            __LINE__,__func__,__FILE__);
    }

    return 0;
}

}/*namespace luaL*/


