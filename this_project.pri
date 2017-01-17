CONFIG += c++14

!win32-msvc*{
QMAKE_CFLAGS*=-std=c11
#QMAKE_CFLAGS*=-fextended-identifiers
#QMAKE_CXXFLAGS*=-fextended-identifiers
}else{
DEFINES *= _SECURE_SCL=0
DEFINES *= _HAS_ITERATOR_DEBUGGING=0
DEFINES *=_CRT_SECURE_NO_DEPRECATE
}

CONFIG(debug,debug|release){
    DEFINES*=_DEBUG
    CONFIG += console
}else{
    DEFINES*=NDEBUG
    DEFINES*=QT_NO_DEBUG
}

win32-msvc*{
    CONFIG(debug,debug|release){
        THIS_PROJECT_DESTDIR=$$PWD/binlib/debug_msvc_bind
    }else{
        THIS_PROJECT_DESTDIR=$$PWD/binlib/release_msvc_bin
    }
}else{
    CONFIG(debug,debug|release){
        THIS_PROJECT_DESTDIR=$$PWD/binlib/debug_common_bind
    }else{
        THIS_PROJECT_DESTDIR=$$PWD/binlib/release_common_bin
    }
}

!win32 {
    LIBS += -ld
    DEFINES *= LUA_USE_LINUX
    QMAKE_LFLAGS += -Wl,-rpath .
}

win32{
    DEFINES *= LOCAL_CODEC_OF_THE_PROJECT=\\\"GBK\\\"
}else{
    DEFINES *= LOCAL_CODEC_OF_THE_PROJECT=\\\"UTF-8\\\"
}

HEADERS += $$PWD/auto_memory/headers

###########################################
#
#
#
#
###########################################
