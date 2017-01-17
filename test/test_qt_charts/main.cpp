/*main.cpp*/

#include "MainWindow.hpp"
#include <QtCore/qtimer.h>
#include <QtBasicLibrary.hpp>
#include <cplusplus_basic.hpp>
#include <QtWidgets/QApplication>

extern std::shared_ptr<void> test_qt_charts();

int main(int argc, char *argv[])try{

    /*init memory*/
    memory::Application mapp;
    /*init qt basic library*/
    QtBasicLibrary qtBasicLibrary;

    QApplication app(argc, argv);

    /*每隔一段时间清理内存*/
    QTimer gcTimer;
    gcTimer.connect(&gcTimer,&QTimer::timeout,
                    [](){memory::clean();});
    gcTimer.start(512);

    std::unique_ptr<MainWindow> window{new MainWindow};
    window->show();

    auto test_data=test_qt_charts();

    {
        auto ans = app.exec();
        mapp.quit();
        return ans;
    }

}catch(...){
    CPLUSPLUS_EXCEPTION(true);
    return -1;
}

#include <memory/MemoryApplication.hpp>
