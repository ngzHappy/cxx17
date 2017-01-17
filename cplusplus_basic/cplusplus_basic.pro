QT -= core gui

include($$PWD/cplusplus_basic.pri)

TARGET = cplusplus_basic_library
TEMPLATE = lib

include($$PWD/_private_cplusplus_basic_headers.pri)
include($$PWD/_private_cplusplus_basic_files.pri)
include($$PWD/containers/containers.pri)
include($$PWD/botan/botan.pri)
DEFINES*=CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT

include($$PWD/lua/lua.pri)

include($$PWD/gumbo/gumbo.pri)

include($$PWD/../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

CONFIG += precompile_header
win32-msvc*{
PRECOMPILED_HEADER  += $$PWD/private/_msvc_core_utility_prebuild.hpp
}else{
PRECOMPILED_HEADER  += $$PWD/private/_core_utility_prebuild.hpp
}










