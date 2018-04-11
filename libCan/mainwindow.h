#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "lib/ControlCAN.h"
#include "ControlCanDll.h"
#include "message/messagedialog.h"
#include "ConFiguration.h"
#include "RobotUdp/RobotUdp.h"
#include "RobotUdp/Widget_UDP.h"
#include <QMenu>
#include <QAction>
#include "ControlCanDllForm.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Widget_OpenDevice();
private slots:
    void open_device();
    void open_udp_can();
    void close_device();
    void configuration();

    void slotUdpReceiveData(int type, const QByteArray &b);
    void slotshow(int type,const QString &str);
private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenus();
    //文本框
    //file菜单
    QMenu * device_Menu = Q_NULLPTR;
    QMenu *Parameter_Menu = Q_NULLPTR;
    QMenu *open_style_menu = Q_NULLPTR;
    //定义了file的下拉菜单为 new  open  save  saveAS  exit
    QAction *open_ = Q_NULLPTR;
    QAction *close_ = Q_NULLPTR;
    QAction *can = Q_NULLPTR;
    QAction *udp_can = Q_NULLPTR;
//    QAction *exit;
    QAction *Parameter_configuration = Q_NULLPTR;
    messageDialog *dialog = Q_NULLPTR;
    ConFiguration *configWidget = Q_NULLPTR;
     RobotUdp* pRobotUdp = Q_NULLPTR;
     Widget_UDP *pWidget_udp = Q_NULLPTR ;
     ControlCanDllForm *dllform=Q_NULLPTR;
};

#endif // MAINWINDOW_H
