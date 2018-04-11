#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QWidget>
#include <QList>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QChart>
#include <QChartView>
#include <QPushButton>
#include <QValueAxis>
#include <QCategoryAxis>
#include <QLineSeries>
#include <QFont>
#include "View/Callout.h"
#include "Setting/setting.h"
using namespace QtCharts;
class ChartView : public QWidget {
    Q_OBJECT
public:
    explicit ChartView(QWidget *parent = 0);
    ~ChartView();
    void AddSeries();
    QString setIniName(QString text);
protected:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
    void Init();
private:
    /**
     * 接收到数据源发送来的数据，数据源可以下位机，采集卡，传感器等。
     */
    void dataReceived(int value);
    void dataReceived2(int value);
    int timerId;
    int timerId2;
    int maxSize;  // data 最多存储 maxSize 个元素
    int maxX;
    int maxY;
    QList<double> data; // 存储业务数据的 list
    QList<double> datalist;
    QChart *chart;
    QChartView *chartView;
    QSplineSeries *splineSeries;
    QLineSeries *series;
    QCategoryAxis *axisX ;//X轴
    QCategoryAxis *axisY ;//Y轴
    QScatterSeries *scatterSeries;//QScatterSeries绘制散点图时,想实现点击选中这个点,再次点击取消选中的功能
    QScatterSeries *scatterSeries1;
    Setting *setting;
    QString nameIni;
};


#endif // CHARTVIEW_H
