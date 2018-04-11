#ifndef WAVEWIDGET_H
#define WAVEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QtDebug>
#include <QSplineSeries>
#include <QScatterSeries>
class WaveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WaveWidget(QWidget *parent = 0);
    ~WaveWidget();

    void paintEvent(QPaintEvent *event);


signals:

public slots:
    void draw();

    void setvote(float value, int set,int status);//最关键的一个方法！！！要向显示电压信号直接调这个方法就可以了
private:
    QPainterPath path, set_path;//提供了一个容器，用于绘图操作
    float fresh, set_fresh;//滚屏
    float penwidth, set_penwidth;//滚屏速度
    float x, set_x;
    int  setval,statu;
    float vote;

//     int timerId;
//     QSplineSeries *splineSeries;
};

#endif // WAVEWIDGET_H
