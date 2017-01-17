QT -= core gui

TARGET = auto_memory
TEMPLATE = lib

DEFINES += AUTO_MEMORY_LIBRARY

SOURCES += auto_memory.c

HEADERS += $$PWD/headers/auto_memory.hpp

INCLUDEPATH+=$$PWD/headers

##########################

include($$PWD/../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/auto_memory.pri)
include($$PWD/jemalloc/jemalloc.pri)
