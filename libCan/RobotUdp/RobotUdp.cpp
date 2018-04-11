
#include "RobotUdp.h"

RobotUdp::RobotUdp(QObject *parent) : QObject(parent)
{
//    pRobotUdp = new RobotUdp(this);
//    connect(pRobotUdp,SIGNAL(sigReceiveData(int,QByteArray&)), this,SLOT(slotUdpReceiveData(int,QByteArray&)));
}
RobotUdp::~RobotUdp()
{
    releaseUdpSocket();
    if(_udpSocketSend){
        _udpSocketSend->deleteLater();
    }
}
void RobotUdp::releaseUdpSocket()
{
    if(_udpSocketSend){
        _udpSocketSend->abort();
    }
}
void RobotUdp::slotReadyRead()
{
    //hasPendingDatagrams返回true时表示至少有一个数据报在等待被读取
    while(_udpSocketSend->hasPendingDatagrams())
    {
        QByteArray datagram;
        //pendingDatagramSize为返回第一个在等待读取报文的size，resize函数是把datagram的size归一化到参数size的大小一样
        datagram.resize(_udpSocketSend->pendingDatagramSize());
        //将读取到的不大于datagram.size()大小数据输入到datagram.data()中，datagram.data()返回的是一个字节数组中存储
        //数据位置的指针
        QHostAddress sender;
        quint16 senderPort;
        _udpSocketSend->readDatagram(datagram.data(), datagram.size(),&sender,&senderPort);
        emit sigReceiveData(0,datagram);
    }
}

QString RobotUdp::lastError() const
{
    return _lastError;
}
//
////------------------------------
///** 开启/关闭rbk日志监听 * @brief RoTcpManager::openRbkLogListen * @return */
//bool RoTcpManager::openRbkLogListen(){

//    //初始化udp
//    pRobotUdp = new RobotUdp(this);
//    connect(pRobotUdp,SIGNAL(sigReceiveData(int,QByteArray&)), this,SLOT(slotUdpReceiveData(int,QByteArray&)));
//    //

//    bool isOn = false;
//    if(pRobotUdp && pRobotUdp->isOpened()){
//        isOn = true;
//    }
//    if(!pRobotUdp->connectUdpSocket(getIp(),19200,19000)){
//        RoWarning(4)<<pRobotUdp->lastError();
//        return false;
//    }
//    if(!isOn){//on
//        pRobotUdp->sendMessage("robokit_log_start",QHostAddress(getIp()),19200);
//    }else{//off
//        pRobotUdp->sendMessage("robokit_log_stop",QHostAddress(getIp()),19200);
//        pRobotUdp->releaseUdpSocket();
//    }    return true;
//}
//
void RobotUdp::setLastError(const QString &lastError)
{
    _lastError = lastError;
}
bool RobotUdp::isOpened()
{
    if(_udpSocketSend && _udpSocketSend->isOpen()){
        return true;
    }
    return false;
}
//向制定ip和端口发送字符,sendPort ==0时表示不发送，只监听
bool RobotUdp::connectUdpSocket(const QString&ip,quint64 sendPort,quint64 receivePort)
{
    //

    if(!_udpSocketSend){
        _udpSocketSend = new QUdpSocket(this);//创建一个QUdpSocket类对象，该类提供了Udp的许多相关操作
        //readyRead()信号是每当有新的数据来临时就被触发
        connect(_udpSocketSend, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    }
    if(!_udpSocketSend->isValid()){
        if(_udpSocketSend->bind(receivePort,QUdpSocket::DontShareAddress)){
            qDebug()<<QString("_udpSocketSend->bind:localHost,port:%1 success").arg(receivePort);
        }else{
            qDebug()<<QString("_udpSocketSend->bind:localHost,port:%1 failed: %2").arg(receivePort).arg(_udpSocketSend->errorString());
        }
    }
    return true;
}
bool RobotUdp::sendMessage(QString data, QHostAddress serverAddress,quint64 port)
{
    QByteArray array = data.toLatin1();
    qint64 size = _udpSocketSend->writeDatagram(array,array.length(),serverAddress, port);//将data中的数据发送
    qDebug()<<tr("RobotUdp::sendMessage:writeDatagram:%1 %2 : %3").arg(QString(array)).arg(serverAddress.toString()).arg(port);
    return true;
}
