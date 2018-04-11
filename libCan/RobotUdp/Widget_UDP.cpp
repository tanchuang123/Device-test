#include "Widget_UDP.h"
#include "ui_Widget_UDP.h"

Widget_UDP::Widget_UDP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_UDP)
{
     ui->setupUi(this);
    setWindowTitle(tr("UDP CLIENT"));
    _port=5555;//指定在此端口上监听数据
    _udpSocket=new QUdpSocket(this);
    connect(_udpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));

    bool result=_udpSocket->bind(_port);//绑定到指定端口，监听端口
    if(!result)
    {
        QMessageBox::information(this,tr("error"),tr("udp create error!"));
        return  ;
    }


}

Widget_UDP::~Widget_UDP()
{
    delete ui;
}

void Widget_UDP::dataReceived()
{
    while (_udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udpSocket->pendingDatagramSize());
        _udpSocket->readDatagram(datagram.data(),datagram.size());
        QString msg=datagram.data();
        ui->ReceiveTextEdit->insertPlainText(msg);
        ui->ReceiveTextEdit->append(msg);
    }
}
void Widget_UDP::on_CloseBtn_clicked()
{
    close();
}

void Widget_UDP::on_pushButton_send_clicked()
{
    unsigned int id=0x701;
    QString msg=ui->lineEdit_send->text();

    QByteArray datagram;
      QDataStream out(&datagram,QIODevice::WriteOnly);
       out.setVersion(QDataStream::Qt_4_8);
       out<<id<<msg;
//       qDebug()<<QDateTime::currentDateTime();
       QHostAddress address;
       address.setAddress("192.168.192.4");

//    QByteArray b = HelpByteArray::hexStrToByteArray(msg);
//     qDebug()<<"b:"<<QString(b)<<b.size()<<QString(b.toHex());
//    _udpSocket->writeDatagram(msg.toLatin1(),msg.length(),QHostAddress::LocalHost,6666);//写入端口
    _udpSocket->writeDatagram(datagram,QHostAddress::LocalHost,6666);//写入端口

    
}
