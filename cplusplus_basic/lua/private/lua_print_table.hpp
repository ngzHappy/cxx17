#ifndef _lm_PRINT_TABLE_1HPP
#define _lm_PRINT_TABLE_1HPP

#include "../lua.hpp"

namespace luaL {

class PrintTableCallback{
public:

    class TempStringData{
    public:
        char * data;
        int length/*at least 128*/;
    };

    virtual ~PrintTableCallback()=default;
    PrintTableCallback()=default;
    PrintTableCallback(const PrintTableCallback&)=default;
    PrintTableCallback(PrintTableCallback&&)=default;
    PrintTableCallback&operator=(const PrintTableCallback&)=default;
    PrintTableCallback&operator=(PrintTableCallback&&)=default;
    virtual TempStringData temp_space()const =0;
    virtual void write_string(const char*,std::size_t)=0;
    virtual void begin() {}
    virtual void finished() {}
    virtual void end() {}
};

LUA_API lua::ThreadStatus print_table(lua::State*,int,PrintTableCallback*);

LUA_API int function_print_table(lua::State*);
LUA_API int function_table_tostring(lua::State*);
}/*luaL*/

#endif
