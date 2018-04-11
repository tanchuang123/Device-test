#include "wavewidget.h"
#include <QDateTime>
WaveWidget::WaveWidget(QWidget *parent)
    : QWidget(parent)

{
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);//设置自动填充背景
    setPalette(pal);//设置该调色板
    path.moveTo(QPoint(10, height()-5));//坐标点 moveTo设置下一次path的起点。lineTo()：通过直线连接上个点与参数指定点。没有上一个点的话，上一个点就是(0,0)。
    set_path.moveTo(QPoint(10, height()-5));
    vote = 0;
    setval = height()-10;
    x = 0;
    set_x = 10;
    fresh = 0;
    set_fresh = 0;
    setFixedHeight(300);//设置固定高度
    setFixedWidth(600);


//    splineSeries = new QSplineSeries();//曲线图
//    scatterSeries = new QScatterSeries();//散点图

//    timerId = startTimer(200);//刷新计时器，定时器
//    qsrand(QDateTime::currentDateTime().toTime_t());//随机数
}
WaveWidget::~WaveWidget()
{

}

//void WaveWidget::timerEvent(QTimerEvent *event)
//{
//    // 产生一个数据，模拟不停的接收到新数据

//    if (event->timerId() == timerId) {
//        int newData = qrand() % (maxY + 1);
////        for(int newData=0;newData<100000;newData++)
//        qDebug()<<newData<<"newData";
//        dataReceived(newData);
//    }
//}
//void WaveWidget::dataReceived(int value) {
//    data << value;
//    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
//    while (data.size() > maxSize) {
//        data.removeFirst();//删除最初接收到的数据
//    }
//    // 界面被隐藏后就没有必要绘制数据的曲线了
//    if (isVisible()) {
//        splineSeries->clear();
//        scatterSeries->clear();
//        int dx = maxX / (maxSize-1);
//        int less = maxSize - data.size();
//        for (int i = 0; i < data.size(); ++i) {
//            splineSeries->append(less*dx+i*dx, data.at(i));
//            scatterSeries->append(less*dx+i*dx, data.at(i));
//        }
//    }
//}
void WaveWidget::paintEvent(QPaintEvent *event)//绘图
{
    QPainter p(this);
    QPen pen;
    pen.setColor(QColor("yellow"));//笔的颜色
    pen.setWidth(3);//笔的粗细
    p.setPen(pen);
    QFont font;//画text的大小 QFont 类代表字体
    font.setPixelSize(30);//请画家并给画家一支调好的笔 设置字号
    p.drawLine(0, 250, width(), 250);//X轴
    qDebug()<<"width"<<width();
//    p.drawLine(30,250,80,90);
    p.drawLine(0, height()-5, 0, 5);//Y轴
    p.drawLine(0,0,5,10);
    p.drawLine(600,250,590,245);
    pen.setColor(QColor("white"));//创建笔的颜色
    p.setPen(pen);
    p.setFont(font);
    p.drawText(QPoint(width()-15, 240), "X");//横坐标 drawText绘制文本
    p.drawText(QPoint(10, 30), "Y");//纵坐标



//    p.drawEllipse(50,　150,　300,　200);
    pen.setColor(QColor("gray"));//网格
    pen.setWidth(1);
    p.setPen(pen);
    for(int i=10; i<width(); i+=10)
        p.drawLine(i, 0, i, height()-50);
    for(int j=10;j<height()-50; j+=10)
        p.drawLine(0, j, width(), j);
    pen.setColor(QColor("red"));

    pen.setWidth(10);
    p.setPen(pen);
    font.setPixelSize(16);
    p.setFont(font);
    p.drawText(QPoint(5, height()-50), "0");
    float a= 10;
    for(int k= 50;k<width();k+=50)
     {
        pen.setColor(QColor("white"));
        pen.setWidth(3);
        p.setPen(pen);
       // p.drawLine(k, 0, k, height()-50);
        QString data = QString("%1").arg(a);
        pen.setColor(QColor("red"));
        pen.setWidth(10);
        p.setPen(pen);
        p.drawText(QPoint(k+5, height()-50), data);
        a=a+10;//横轴代表时间，每小格0.04s，每大格0.2s
    }

    p.translate(-fresh, 0);//将点（x，y）设为原点
    pen.setColor(QColor("red"));
    pen.setWidth(penwidth);
    p.setPen(pen);
    p.drawPath(path);//曲线图（波形）
    QPainter set_p(this);
    //QPen set_pen;
    set_p.translate(-set_fresh, 0);
//        set_pen.setColor(QColor("green"));
//        set_pen.setWidth(3);
//        set_p.setPen(set_pen);
//        set_p.drawPath(set_path);//参考线
    //set_p.drawLine(QPoint(0, height()-setval), QPoint(width(), height()-setval));
}
void WaveWidget::draw()
{
    if(statu == 1)
    {
        path.lineTo(QPoint(x+=penwidth, height()/2-vote));//每个数据的纵坐标路径
        if(x > width())//画满
        fresh+=penwidth;
//        set_path.lineTo(QPoint(set_x+=set_penwidth, height()-vote-10));
//        if(set_x > width())//画满
//            set_fresh+=set_penwidth;
        update();//自动刷新
    }
}
void WaveWidget::setvote(float value, int set,int status)//最关键的一个方法！！！要向显示电压信号直接调这个方法就可以了
{
    vote = value;//传入的数据值
    setval = set;
    statu = status;
    draw();
}
