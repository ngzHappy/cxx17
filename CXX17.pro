TEMPLATE = subdirs

library_auto_memory.file = $$PWD/auto_memory/auto_memory.pro
SUBDIRS += library_auto_memory

libray_cplusplus_basic.file = $$PWD/cplusplus_basic/cplusplus_basic.pro
libray_cplusplus_basic.depends+=library_auto_memory
SUBDIRS += libray_cplusplus_basic


