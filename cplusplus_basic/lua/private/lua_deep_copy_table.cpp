#ifndef LUA_LIB
#define LUA_LIB
#endif

#include "lua_deep_copy_table.hpp"
#include "lua_default_error_function.hpp"
#include <list>
#include <set>
#include <map>

namespace luaL {
extern int default_error_function(lua_State * L);
}/*luaL*/

namespace {

namespace _luaL {
inline auto get_default_lua_error_function() {
    return &luaL::default_error_function;
}
}/*luaL*/

namespace __private {

typedef int IntType;

class CopyTableItem {
public:
    IntType source;
    IntType target;
    CopyTableItem():source(0),target(0) {}
    CopyTableItem(IntType _1,IntType _2):source(_1),target(_2) {}
};

using Duties=std::list<CopyTableItem,memory::Allocator<CopyTableItem>>;
using AllTables=std::map<
    const void *,IntType,
    std::less<const void*>,
    memory::Allocator<CopyTableItem>
>;

class CopyData {
    CopyData()=delete;
    CopyData(const CopyData&)=delete;
    CopyData(CopyData&&)=delete;
    CopyData&operator=(const CopyData&)=delete;
    CopyData&operator=(CopyData&&)=delete;
public:
    lua::State*L;
    IntType sources;
    IntType targets;
    Duties & duties;
    AllTables &allTables;
    IntType &s;
    IntType & t;
};

void copy(
    CopyTableItem*item,
    CopyData&copy_data
) {

    lua::State*L=copy_data.L;
    const IntType &sources=copy_data.sources;
    const IntType &targets=copy_data.targets;
    Duties & duties=copy_data.duties;
    AllTables &allTables=copy_data.allTables;
    IntType & s=copy_data.s;
    IntType & t=copy_data.t;

    const auto lock_top=lua::gettop(L);

#ifndef function_return
#define function_return() lua::settop(L,lock_top);return
#endif 

    lua::rawgeti(L,sources,item->source);
    const auto source=lua::gettop(L);

    lua::rawgeti(L,targets,item->target);
    const auto target=lua::gettop(L);

    {
        constexpr auto _key=-2;
        constexpr auto _value=-1;
        lua::pushnil(L);
        while (lua::next(L,source)) {
            if (lua::istable(L,_value)) {
                auto table_id=lua::topointer(L,_value);
                auto pos=allTables.find(table_id);
                if (pos==allTables.end()) {/*find a new talbe*/
                    ++s; ++t;

                    /*set the table to sources*/
                    lua::rawseti(L,sources,s);

                    /*create a new table as target*/
                    lua::newtable(L);

                    /*set the table to targets*/
                    lua::pushvalue(L,-1);
                    lua::rawseti(L,targets,t);

                    /*set the talbe to target*/
                    lua::pushvalue(L,_key);
                    lua::pushvalue(L,_value-1);
                    lua::settable(L,target);

                    /*pop the value*/
                    lua::pop(L,1);

                    /*add the table to know table*/
                    duties.emplace_back(s,t);
                    allTables.emplace(table_id,t);
                }
                else {
                    lua::pushvalue(L,_key);
                    lua::rawgeti(L,targets,pos->second);
                    lua::settable(L,target);
                    lua::pop(L,1);
                }
            }
            else {
                lua::pushvalue(L,_key);
                lua::pushvalue(L,_value-1);
                lua::settable(L,target);
                lua::pop(L,1);
            }
        }
    }

    {
        /*item->souce never used*/
        lua_pushnil(L);
        lua_rawseti(L,sources,item->source);
    }

    function_return();
#undef function_return
}

int deep_copy_table(lua::State*L) {

    constexpr auto source_table=1;
    constexpr auto target_table=2;

    if (lua::istable(L,source_table)==false) {
        lua::pushlstring(L,"source is not a table");
        lua::error(L);
        return 0;
    }

    if (lua::istable(L,target_table)==false) {
        lua::pushlstring(L,"target is not a table");
        lua::error(L);
        return 0;
    }

    lua::checkstack(L,36);
    lua::newtable(L);
    const auto source_tmp_table=lua::gettop(L);

    lua::newtable(L);
    const auto target_tmp_table=lua::gettop(L);

    Duties duties;
    AllTables allTables;
    IntType source_count=1;
    IntType target_count=1;

    {
        /*init duties*/
        lua::pushvalue(L,source_table);
        lua::rawseti(L,source_tmp_table,1);

        lua::pushvalue(L,target_table);
        lua::rawseti(L,target_tmp_table,1);

        duties.emplace_back(1,1);
    }

    CopyData copy_data{ L,
            source_tmp_table,target_tmp_table,
            duties,allTables,
            source_count,target_count };

    while (false==duties.empty()) {
        auto item=std::move(*duties.begin());
        duties.pop_front();
        copy(&item,copy_data);
    }

    return 0;
}

}/*__private*/
}/*namespace*/

namespace luaL {

lua::ThreadStatus deep_copy_table(lua::State*L,int/*from*/argFrom,int/*to*/argTo) {
    /*确保堆栈够用*/
    lua::checkstack(L,8);
    
    if (argFrom==argTo) { return lua::OK; }

    argFrom=lua::absindex(L,argFrom);
    argTo=lua::absindex(L,argTo);

    {
        lua::pushcfunction(L,&__private::deep_copy_table);
        lua::pushvalue(L,argFrom)/*from table*/;
        lua::pushvalue(L,argTo)/*to table*/;
        lua::pushcfunction(L,_luaL::get_default_lua_error_function())/*error function*/;
        auto epos=lua::gettop(L);
        return lua::pcall(L,3,lua::MULTRET,epos);
    }

}

int function_deep_copy_table(lua::State*L) {
    return __private::deep_copy_table(L);
}

}

/**/

