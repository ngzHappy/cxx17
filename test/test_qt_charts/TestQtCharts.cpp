namespace QtCharts {}

#include <QtGui>
#include <QtCore>
#include <QtCharts>
#include <QtWidgets>
#include <cmath>
#include <cstdlib>
#include <cplusplus_basic.hpp>

namespace MQtCharts {

class ChartView :public QtCharts::QChartView {
    using Super=QtCharts::QChartView;
public:
    using Super::Super;
private:
    CPLUSPLUS_OBJECT(ChartView)
};

class LineSeries :public QtCharts::QLineSeries {
    using Super=QtCharts::QLineSeries;
public:
    using Super::Super;
    virtual ~LineSeries() {
        //qDebug()<<"~LineSeries";
    }
private:
    CPLUSPLUS_OBJECT(LineSeries)
};

class Chart :public QtCharts::QChart {
    using Super=QtCharts::QChart;
public:
    using Super::Super;
private:
    CPLUSPLUS_OBJECT(Chart)
};

class ImageChart :
    public QtCharts::QChart {
    using Super=QtCharts::QChart;
private:
    QImage _pm_Image;
    QPixmap _pm_ImagePaint;
    template<typename _T_>
    inline void _p_setImage(_T_&&);
public:
    inline void setImage(QImage &&arg) { _p_setImage(std::move(arg)); }
    inline void setImage(const QImage &arg) { _p_setImage(arg); }
public:
    ImageChart();
protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override {
        Super::paint(painter,option,widget);
        if (painter) {
            if (_pm_Image.isNull()) { return; }
            const auto varPlotArea=this->plotArea();
            const auto varPlotAreaSize=varPlotArea.size().toSize();
            if (varPlotAreaSize==_pm_ImagePaint.size()) {
                painter->drawPixmap(varPlotArea.topLeft(),_pm_ImagePaint);
            }
            else {
                _pm_ImagePaint=QPixmap::fromImage(
                _pm_Image.scaled(varPlotAreaSize
                    ,Qt::IgnoreAspectRatio
                    ,Qt::SmoothTransformation));
                painter->drawPixmap(varPlotArea.topLeft(),_pm_ImagePaint);
            }
        }
    }/*void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)*/
private:
    CPLUSPLUS_OBJECT(Chart)
};

template<typename _T_>
inline void ImageChart::_p_setImage(_T_&&arg) {
    _pm_Image=std::forward<_T_>(arg);
    _pm_ImagePaint={};
    this->update();
}

ImageChart::ImageChart() {
    setBackgroundVisible(false);
}/*ImageChart::ImageChart*/

}/*MQtCharts*/

std::shared_ptr<void> test_qt_charts() {

    auto * chart=new MQtCharts::ImageChart;

    for (double i=0; i<(2*3.141592654); i+=(3.141592654/30)) {
        const QPen pen(QColor(
            (std::rand()&127)+32,
            (std::rand()&127)+32,
            (std::rand()&127)+32,
            (std::rand()&63)+(128+64)),
            1.5);
        auto * line=new MQtCharts::LineSeries;
        line->append(0.0,0.0);
        line->append(std::sin(i)/1.1,std::cos(i)/1.5);
        line->setPen(pen);
        chart->addSeries(line);
    }

    /*设置坐标轴*/
    chart->createDefaultAxes();
    chart->axisX()->setRange(-1,1);
    chart->axisY()->setRange(-1,1);
    chart->axisY()->setReverse(true);
    /*隐藏标题栏*/
    chart->legend()->hide();
    /*开启全部动画*/
    chart->setAnimationOptions(QChart::AllAnimations);

    auto view=new MQtCharts::ChartView ;
    view->setAttribute(Qt::WA_DeleteOnClose);

    view->resize(512,512);
    view->show();

    chart->setImage(QImage(":/image/0x000000.jpg"));

    view->setChart(chart);
    view->setRenderHints(
        QPainter::HighQualityAntialiasing|
        QPainter::SmoothPixmapTransform|
        QPainter::TextAntialiasing
    );

    qDebug()<<chart->mapToPosition(QPointF(0,0));
    qDebug()<<chart->mapToPosition(QPointF(1,1));

    return{};
}


