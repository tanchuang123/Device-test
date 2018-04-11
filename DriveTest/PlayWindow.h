#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include "TabBar/BaseTabWidget.h"
#include "View/wavewidget.h"
#include "View/ChartView.h"
#include <QColorDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QMessageBox>
#include "Define/definitions.h"
namespace Ui {
class PlayWindow;
}

class PlayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayWindow(QWidget *parent = 0);
    ~PlayWindow();
    void selectColor();

private slots:



    void on_pushButton_save_ini_clicked();

    void open_button();

    void on_pushButton_connect_clicked();


    void ReadSerialBuffer();
    void ScanSerialPorts();
    void Reflesh();
    void closeCallBack();

    void on_pushButton_clearCache_clicked();


    void on_pushButton_resetStoreLength_clicked();


    void on_toolButton_color_clicked();

    void on_add_tabWidget_clicked();



private:
    Ui::PlayWindow *ui;

//自己定义的成员变量
    QSerialPort *mySerialPort;
    QTimer *timerScan;//扫描
    QTimer *timerReceive;//接收数据
    QTimer *timerReflesh;//刷新
    QVector<int> rawData;
    bool serialOpenStatus;//串口开放状态
    QByteArray bufferData;
    char tailTemp;

//    QCustomPlot *historyPlot,*realtimePlot;
//    QCPGraph *realtimeGraph,*historyGraph;

    long storeLength;
    long realtimeShowLength;
    int sampleSpeed;

//自己定义的成员函数
//    void InitPlotTheme();
    int ProtocolDecode(QByteArray);
    void PlotRealtimeData();
};

#endif // PLAYWINDOW_H
