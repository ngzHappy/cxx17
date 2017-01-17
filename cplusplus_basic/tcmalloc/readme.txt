use vs2015 to build tcmalloc

windows mingw:

pexports libtcmalloc_minimal.dll > tcmalloc.def
dlltool -d tcmalloc.def -D libtcmalloc_minimal -l libtcmalloc_minimal.a

or

change port.h to 
//#if defined(_MSC_VER) && _MSC_VER >= 1900
#define _TIMESPEC_DEFINED
#include <time.h>
//#endif

http://sourceforge.net/projects/mingw/files/MSYS/
./autogen.sh
./configure CFLAGS=-O2 CXXFLAGS=-g0
make
if error make -i
