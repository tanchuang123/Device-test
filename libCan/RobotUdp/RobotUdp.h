#ifndef RobotUdp_H
#define RobotUdp_H

#include <QObject>

#include <QUdpSocket>


class  RobotUdp : public QObject
{
    Q_OBJECT
public:
    explicit RobotUdp(QObject *parent = 0);

    bool connectUdpSocket(const QString &ip, quint64 sendPort, quint64 receivePort);
    void releaseUdpSocket();
    ~RobotUdp();
    bool sendMessage(QString data, QHostAddress serverAddress, quint64 port);
    QString lastError() const;
    void setLastError(const QString &lastError);

    bool isOpened();
signals:
    void sigReceiveData(int,QByteArray&);
public slots:
    void slotReadyRead();

private slots:
private:

    QUdpSocket *_udpSocketSend = Q_NULLPTR;
    quint64 _port;
    QString _lastError;
};

#endif // RobotUdp_H
