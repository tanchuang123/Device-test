#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QMessageBox>
#include <Windows.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   /*  pRobotUdp = new RobotUdp(this);
     pRobotUdp->connectUdpSocket("127.0.0.1",6666,7777);
     connect(pRobotUdp,SIGNAL(sigReceiveData(int,QByteArray&)), this,SLOT(slotUdpReceiveData(int,QByteArray&)))*/;

    device_Menu =new QMenu(this);
    Parameter_Menu =new QMenu(this);
    createActions();
    //再来创建菜单目录，把下拉菜单的内容addaction加入到menu中
    createMenus();

    dialog=new messageDialog(this);
    ControlCanDll::init();
//   QObject:: connect(ControlCanDll::init(),SIGNAL(sigControlCanDllType(int ,const QString )),this,SLOT(slotshow(int ,const QString)));
}
MainWindow::~MainWindow()
{
    delete dialog;
    delete ui;
}
void MainWindow::Widget_OpenDevice()
{

    bool opentrue;
    opentrue=ControlCanDll::init()->OpenDevice();
    if(opentrue)
    {
        QMessageBox::information(NULL, "Title", "true", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    }
    else {
        QMessageBox::information(NULL, "Title", "false", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}
void MainWindow::createActions()
{
    open_ = new QAction( tr("&OpenDevice"), this);
    can = new QAction(tr("Can"));
    udp_can =new QAction(tr("udp_can"));

    //     newAct->setStatusTip(tr("%1").arg(control->FindUsbDevice()));
    connect(can, SIGNAL(triggered()), this, SLOT(open_device())); //New点击事件调用test
    connect(udp_can,SIGNAL(triggered()),this,SLOT(open_udp_can()));
    close_ = new QAction(tr("&CloseDevice"), this);
    //     open->setShortcuts(QKeySequence::Open);
    //     open->setStatusTip(tr("open a new file"));
    connect(close_, SIGNAL(triggered()), this, SLOT(close_device())); //点击Open事件调用test

    Parameter_configuration=new QAction(tr("configuration"),this);
    Parameter_configuration->setEnabled(false);
    connect(Parameter_configuration,SIGNAL(triggered()),this,SLOT(configuration()));

}
void MainWindow::createMenus()
{
    //创建一个name为file的菜单栏
    device_Menu = menuBar()->addMenu(tr("&Device"));
    open_style_menu=device_Menu->addMenu(tr("&OpenDevice"));
    Parameter_Menu=menuBar()->addMenu(tr("&Parameter"));

    //     QMenu *menu=menuBar()->addMenu(tr("&保存"));
    //     menu->addAction(open);
    //在这个菜单栏添加action即下拉菜单
//    device_Menu->addAction(open_);
    open_style_menu->addAction(can);
    open_style_menu->addAction(udp_can);
    device_Menu->addAction(close_);
    //     fileMenu->addAction(Save);
    //     fileMenu->addAction(saveAs);
    //添加一个分割器
    device_Menu->addSeparator();
    //推出下拉菜单
    Parameter_Menu->addAction(Parameter_configuration);
}
void MainWindow::open_device()
{

    if(!ControlCanDll::init()->OpenDevice())
    {
        dialog->message_show(tr("Hint"),tr("open filed"));
    }
    else {
        dialog->message_show(tr("Hint"),tr("open sucessful!"));
    }

}
void MainWindow::open_udp_can()
{
    pWidget_udp= new Widget_UDP;
    pWidget_udp->show();

}
void MainWindow::close_device()
{
    if(!ControlCanDll::init()->CloseDevice())
    {
        dialog->message_show(tr("Hint"),tr("close filed"));
    }
    else {
        dialog->message_show(tr("Hint"),tr("close sucessful!"));
    }

}


void MainWindow::configuration()
{
    if(!configWidget){
        configWidget=new ConFiguration();
        configWidget->setWindowModality(Qt::ApplicationModal);
    }

    configWidget->show();
}
void MainWindow::slotUdpReceiveData(int type, const QByteArray &b)
{
//qDebug()<<b;
}
void MainWindow::slotshow(int type,const QString &str)
{

}
