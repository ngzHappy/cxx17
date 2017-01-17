win32-msvc*{

CONFIG(debug,debug|release){

DEFINES *= HAS_JEMALLOC_CONCEPT
LIBS += -ljemallocd

}else{

DEFINES *= HAS_JEMALLOC_CONCEPT
LIBS += -ljemalloc

}

}else{

}

