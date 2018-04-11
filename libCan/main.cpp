#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    unsigned char pMem[] = {0x01,0x02,0x03,0x04};
       float *p = (float*)pMem;



       qDebug()<<*p<<QStringLiteral("16进制");
    return a.exec();
}
