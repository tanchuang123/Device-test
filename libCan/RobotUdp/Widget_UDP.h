#ifndef WIDGET_UDP_H
#define WIDGET_UDP_H

#include <QWidget>
#include <QUdpSocket>
#include <QMessageBox>
#include "CanFrame/HelpByteArray.h"
namespace Ui {
class Widget_UDP;
}

class Widget_UDP : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_UDP(QWidget *parent = 0);
    ~Widget_UDP();
private slots:
    void dataReceived();
    void on_CloseBtn_clicked();

    void on_pushButton_send_clicked();

private:
    Ui::Widget_UDP *ui;
    int _port;
    QUdpSocket *_udpSocket;
};

#endif // WIDGET_UDP_H
