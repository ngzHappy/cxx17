/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QtCore>
#include <QtWidgets>
#include <QtGui/qpainter.h>

namespace {

class TestWindow :public QWidget{
public:
    TestWindow() {
        this->resize(200,20);
    }

    void paintEvent(QPaintEvent*)override {
        QPainter painter(this);
        painter.fillRect(this->rect(),QColor(255,3,2));
    }

    ~TestWindow() {
        //qDebug()<<"~TestWindow()";
    }

private:
    CPLUSPLUS_OBJECT(TestWindow)
};

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto test=new TestWindow;

    test->setParent(this);

    test->move(100,100);
    test->setWindowFlags(
        Qt::Dialog
        | Qt::WindowTitleHint
        | Qt::CustomizeWindowHint
        | Qt::WindowMinimizeButtonHint
        | Qt::WindowMaximizeButtonHint);
    test->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

