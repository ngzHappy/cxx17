
TARGET = qt_basic_library
TEMPLATE = lib

QT += core
QT += gui
QT += concurrent

DEFINES += QT_BASIC_LIBRARY

SOURCES += QtBasicLibrary.cpp \
    QtBasicLibraryStart.cpp \
    QObjectsWatcher.cpp \
    QSingleThreadPool.cpp \
    QApplicationWatcher.cpp \
    QNotifyObject.cpp

HEADERS += QtBasicLibrary.hpp\
        qt_basic_global.hpp \
    QObjectsWatcher.hpp \
    _PrivateQObjectsWatcher.hpp \
    QSingleThreadPool.hpp \
    QApplicationWatcher.hpp \
    QNotifyObject.hpp \
    QRunOnce.hpp

include($$PWD/private_qt3rd_base_library/zlib.pri)
include($$PWD/quazip/quazip.pri)
include($$PWD/text/text.pri)

include($$PWD/../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lauto_memory
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library





