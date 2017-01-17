#ifndef _lm3_DEEP_COPY_TABLE_HPP
#define _lm3_DEEP_COPY_TABLE_HPP

#include "../lua.hpp"

namespace luaL {

LUA_API lua::ThreadStatus deep_copy_table(lua::State*,int/*from*/,int/*to*/);
LUA_API int function_deep_copy_table(lua::State*);

}

#endif

