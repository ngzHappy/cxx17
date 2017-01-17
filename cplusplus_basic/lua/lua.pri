SOURCES += \
    $$PWD/src/lapi.cpp \
    $$PWD/src/lauxlib.cpp \
    $$PWD/src/lbaselib.cpp \
    $$PWD/src/lbitlib.cpp \
    $$PWD/src/lcode.cpp \
    $$PWD/src/lcorolib.cpp \
    $$PWD/src/lctype.cpp \
    $$PWD/src/ldblib.cpp \
    $$PWD/src/ldebug.cpp \
    $$PWD/src/ldo.cpp \
    $$PWD/src/ldump.cpp \
    $$PWD/src/lfunc.cpp \
    $$PWD/src/lgc.cpp \
    $$PWD/src/linit.cpp \
    $$PWD/src/liolib.cpp \
    $$PWD/src/llex.cpp \
    $$PWD/src/lmathlib.cpp \
    $$PWD/src/lmem.cpp \
    $$PWD/src/loadlib.cpp \
    $$PWD/src/lobject.cpp \
    $$PWD/src/lopcodes.cpp \
    $$PWD/src/loslib.cpp \
    $$PWD/src/lparser.cpp \
    $$PWD/src/lstate.cpp \
    $$PWD/src/lstring.cpp \
    $$PWD/src/lstrlib.cpp \
    $$PWD/src/ltable.cpp \
    $$PWD/src/ltablib.cpp \
    $$PWD/src/ltm.cpp \
    $$PWD/src/lundump.cpp \
    $$PWD/src/lutf8lib.cpp \
    $$PWD/src/lvm.cpp \
    $$PWD/src/lzio.cpp \
    $$PWD/private/lua_default_error_function.cpp \
    $$PWD/private/lua_deep_copy_table.cpp \
    $$PWD/private/lua_print_table.cpp

HEADERS += \
    $$PWD/src/lapi.h \
    $$PWD/src/lauxlib.h \
    $$PWD/src/lcode.h \
    $$PWD/src/lctype.h \
    $$PWD/src/ldebug.h \
    $$PWD/src/ldo.h \
    $$PWD/src/lfunc.h \
    $$PWD/src/lgc.h \
    $$PWD/src/llex.h \
    $$PWD/src/llimits.h \
    $$PWD/src/lmem.h \
    $$PWD/src/lobject.h \
    $$PWD/src/lopcodes.h \
    $$PWD/src/lparser.h \
    $$PWD/src/lprefix.h \
    $$PWD/src/lstate.h \
    $$PWD/src/lstring.h \
    $$PWD/src/ltable.h \
    $$PWD/src/ltm.h \
    $$PWD/src/lua.h \
    $$PWD/src/luaconf.h \
    $$PWD/src/lualib.h \
    $$PWD/src/lundump.h \
    $$PWD/src/lvm.h \
    $$PWD/src/lzio.h \
    $$PWD/src/lua.hpp \
    $$PWD/lua.hpp \
    $$PWD/private/lua_deep_copy_table.hpp \
    $$PWD/private/lua_print_table.hpp

include($$PWD/private/3rd/double-conversion/double-conversion.pri)
