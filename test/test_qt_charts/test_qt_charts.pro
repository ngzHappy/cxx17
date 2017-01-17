###test_qt_charts.pro

QT += core
QT += gui
QT += widgets
QT += charts
#QT += script
#QT += network

TARGET = test_qt_charts
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    TestQtCharts.cpp

HEADERS  += MainWindow.hpp

FORMS    += MainWindow.ui

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lauto_memory
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

RESOURCES += \
    image.qrc

