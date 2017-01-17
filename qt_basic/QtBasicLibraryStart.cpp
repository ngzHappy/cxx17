/*this function will run on app start up*/
#include <ctime>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <QtGui/qimage.h>
#include <cplusplus_basic.hpp>
#include <QtCore/qcoreapplication.h>

using namespace std::chrono_literals;

namespace {

static void _var() {

    {/*load image plugin*/
        QImage _image_{ "__________qt__.png" };
    }

};

}

static void _on_qt_start_up_0x99812() {

    std::srand(static_cast<int>(std::time(nullptr)));
    //std::thread(&_var).detach();
    _var();

}

Q_COREAPP_STARTUP_FUNCTION(_on_qt_start_up_0x99812)
