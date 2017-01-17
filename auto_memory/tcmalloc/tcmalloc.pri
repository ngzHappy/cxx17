CONFIG(debug,debug|release){

}else{

##windows
win32{

###########################################
win32-msvc*{

#libtcmalloc_minimal.lib
#libtcmalloc_minimal.dll
DEFINES *= HAS_TCMALLOC_CONCEPT
LIBS += -llibtcmalloc_minimal

}else : win32-g++{

#libtcmalloc_minimal.dll.a
#libtcmalloc_minimal-4.dll
DEFINES *= HAS_TCMALLOC_CONCEPT
LIBS += -ltcmalloc_minimal.dll

}
###########################################

}else{
##not windows

}

}##debug|release










