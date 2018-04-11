#include "ChartView.h"

#include <QDateTime>
#include <QHBoxLayout>
#include <QtDebug>
ChartView::ChartView(QWidget *parent)
    : QWidget(parent)
{


    setting=new Setting();
//    axisX = new QCategoryAxis();//X轴
//    axisY = new QCategoryAxis();//Y轴
//    series=new QSplineSeries();
//    scatterSeries1= new QScatterSeries();

    splineSeries  = new QSplineSeries();//曲线图
    scatterSeries = new QScatterSeries();//散点图


    chart = new QChart();
    chartView = new QChartView(chart);

    maxSize = 31; // 只存储最新的 31 个数据
    maxX = 600;
    maxY = 200;
    //背景色
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);//设置自动填充背景
    setPalette(pal);//设置该调色板
    QPen axisPen(QColor("#000000"));//轴
    QBrush axisBrush(Qt::white);
    QFont labelsFont;
    labelsFont.setPixelSize(12);//标签字体大小

//    QPainter p(this);
    QBrush penText;
    penText.setColor(Qt::red);
    QFont fontText;//画text的大小 QFont 类代表字体
    fontText.setPixelSize(20);//请画家并给画家一支调好的笔 设置字号
//    p.setPen(penText);
//    p.setFont(fontText);
//    p.drawText(QPoint(300, 150), "X");//横坐标 drawText绘制文本
//    p.drawText(QPoint(50, 50), "Y");//纵坐标
  //自定义显示窗
//    axisX = new QCategoryAxis();//X轴
//    axisY = new QCategoryAxis();//Y轴
//    QFont labelsFont;
//    labelsFont.setPixelSize(12);//标签字体大小
//    axisX->setLabelsFont(labelsFont);
//    axisY->setLabelsFont(labelsFont);

//    // Customize axis colors
//    QPen axisPen(QColor("#000000"));//轴
//    axisPen.setWidth(2);
//    axisX->setLinePen(axisPen);//设置轴颜色
//    axisY->setLinePen(axisPen);

//    // Customize axis label colors轴标签的颜色
//    QBrush axisBrush(Qt::white);
//    axisX->setLabelsBrush(axisBrush);
//    axisY->setLabelsBrush(axisBrush);

    // Customize grid lines and shades网格线和阴影
//    axisX->setGridLineVisible(false);
//    axisY->setGridLineVisible(false);
//    axisY->setShadesPen(Qt::NoPen);
////    axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
//    axisY->setShadesVisible(true);//Y轴网格线可见



//    *splineSeries<< QPointF(0, 0) << QPointF(90, 40) << QPointF(150, 200) << QPointF(250, 120) << QPointF(290, 26);
//    *series<<QPointF(0, 0) << QPointF(30, 40) << QPointF(60, 50) << QPointF(90, 60) << QPointF(300, 100);

//    axisX->append("0", 0);
//    axisX->append("100", 100);
//    axisX->append("200", 200);
//    axisX->append("300",300);
//    axisX->append("400",400);
//    axisX->append("500",500);
//    axisX->append("600",600);
//    axisX->setRange(0, maxX);

//    axisY->append("0", 0);
//    axisY->append("50",50);
//    axisY->append("100", 100);
//    axisY->append("150",150);
//    axisY->append("200", 200);
//    axisY->setRange(0, maxY);

//    chart->setAxisX(axisX, splineSeries);
//    chart->setAxisY(axisY, splineSeries);

//    chart->setAxisX(axisX, series);
//    chart->setAxisY(axisY, series);

    scatterSeries->setMarkerSize(2);//端点大小

    chart->addSeries(splineSeries);
    chart->addSeries(scatterSeries);

    chart->legend()->hide();//图层图标隐藏
    chart->setTitle(tr("Real time curve"));
    chart->createDefaultAxes();

    chart->axisX()->setRange(0, maxX);//X轴
    chart->axisY()->setRange(0, maxY);//Y轴

    chart->axisX()->setGridLineVisible(false);//隐藏辅助线
    chart->axisY()->setGridLineVisible(false);
    chart->axisY()->setShadesVisible(true);//Y轴渐变隔离
    chart->axisX()->setLabelsBrush(axisBrush);
    chart->axisY()->setLabelsBrush(axisBrush);
    chart->axisX()->setLinePen(axisPen);
    chart->axisY()->setLinePen(axisPen);
    chart->axisX()->setLabelsFont(labelsFont);
    chart->axisY()->setLabelsFont(labelsFont);
    chart->axisX()->setTitleFont(fontText);
    chart->axisY()->setTitleFont(fontText);
    chart->axisX()->setTitleText("X");
    chart->axisY()->setTitleText("Y");
    chart->axisX()->setTitleBrush(penText);
    chart->axisY()->setTitleBrush(penText);

    // Customize series
    QPen pen;
    pen.setColor("#ff0000");
    pen.setWidth(1);
    splineSeries->setPen(pen);


    // Customize chart title
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::white));

    // Customize chart background自定义背景图
    QLinearGradient backgroundGradient;//渐变色
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
    backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setBackgroundBrush(backgroundGradient);

    // Customize plot area background
    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QColor("#000000"));
    plotAreaGradient.setColorAt(1.0, QColor("#323232"));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    chart->setPlotAreaBackgroundVisible(true);



    chartView->setRenderHint(QPainter::Antialiasing);////渲染提示 抗锯齿
    QHBoxLayout *layout = new QHBoxLayout();//水平布局
    layout->setContentsMargins(0, 0, 0, 0);//设置外边距的值
    layout->addWidget(chartView);//图标视觉
    setLayout(layout);

    timerId = startTimer(200);//刷新计时器，定时器
    qsrand(QDateTime::currentDateTime().toTime_t());//随机数


}
ChartView::~ChartView()
{

}
void ChartView::Init()
{


}
void ChartView::AddSeries()
{
     timerId2=startTimer(200);
     qsrand(QDateTime::currentDateTime().toTime_t());
//     qDebug()<<"xxxxxxxxxxxx";
     series=new QSplineSeries();
     *series<<QPointF(0, 0) << QPointF(1, 20) << QPointF(2, 40) << QPointF(3, 60) << QPointF(4, 70);
     scatterSeries1= new QScatterSeries();
     scatterSeries1->setMarkerSize(2);
     chart->addSeries(series);
     chart->addSeries(scatterSeries1);
     QPen pen1;
     pen1.setColor(QRgb(0xd2d0d1));
     pen1.setWidth(1);
     series->setPen(pen1);


}

void ChartView::timerEvent(QTimerEvent *event)
{
//    qDebug()<<event->timerId()<<"timerID";
    // 产生一个数据，模拟不停的接收到新数据
    if (event->timerId() == timerId) {
        int newData = qrand() % (maxY + 1);
//        qDebug()<<newData<<"newData";
        dataReceived(newData);
    }
    else if (event->timerId() == timerId2){

        int newData = qrand() % (maxY + 1);
//        qDebug()<<newData<<"newData";
        dataReceived2(newData);
    }
}

void ChartView::dataReceived(int value) {
    data << value;
    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
    while (data.size() > maxSize) {

        setting->setIni(data,nameIni);
        setting->ReadIni();
        data.removeFirst();//删除最初接收到的数据
    }
    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible())
    {
        splineSeries->clear();
        scatterSeries->clear();
        int dx = maxX / (maxSize-1);
        int less = maxSize - data.size();
        for (int i = 0; i < data.size(); ++i) {
            splineSeries->append(less*dx+i*dx, data.at(i));
            scatterSeries->append(less*dx+i*dx, data.at(i));
        }
    }
}
void ChartView::dataReceived2(int value) {
    datalist << value;
    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
    while (datalist.size() > maxSize) {

        setting->setIni(datalist,nameIni);
        setting->ReadIni();
        datalist.removeFirst();//删除最初接收到的数据
    }
    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        series->clear();
        scatterSeries1->clear();
        int dx = maxX / (maxSize-1);
        int less = maxSize - datalist.size();
        for (int i = 0; i < datalist.size(); ++i) {
            series->append(less*dx+i*dx, datalist.at(i));
            scatterSeries1->append(less*dx+i*dx, datalist.at(i));
        }
    }
}
QString ChartView::setIniName(QString text)
{
     nameIni=text;
     return nameIni;
}
//void ChartView::mouseMoveEvent(QMouseEvent *event)
//{
//    m_coordX->setText(QString("X: %1").arg(m_chart->mapToValue(event->pos()).x()));
//    m_coordY->setText(QString("Y: %1").arg(m_chart->mapToValue(event->pos()).y()));
//    QGraphicsView::mouseMoveEvent(event);
//}

//void ChartView::keepCallout()
//{
//    m_callouts.append(m_tooltip);
//    m_tooltip = new Callout(m_chart);
//}

//void ChartView::tooltip(QPointF point, bool state)
//{
//    if (m_tooltip == 0)
//        m_tooltip = new Callout(m_chart);

//    if (state) {
//        m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
//        m_tooltip->setAnchor(point);
//        m_tooltip->setZValue(11);
//        m_tooltip->updateGeometry();
//        m_tooltip->show();
//    } else {
//        m_tooltip->hide();
//    }
//}
