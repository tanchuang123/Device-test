#include "PlayWindow.h"
#include <QApplication>

//#include <QtDebug>
//#include <QFile>
//#include <QTextStream>
//#include <QtMessageHandler>

//#include <stdio.h>
//#include <stdlib.h>
//#include <QCoreApplication>
//#include <QSettings>
//#include <QDebug>
//#include <QTime>
//#include <QDir>
//void customMessageHandler(QtMsgType type, const char *msg)      //在main函数之前定义回调函数
//{
//        QString txt;
//        switch (type) {
//        //调试信息提示
//        case QtDebugMsg:
//                txt = QString("Debug: %1").arg(msg);
//                break;

//        //一般的warning提示
//        case QtWarningMsg:
//                txt = QString("Warning: %1").arg(msg);
//        break;
//        //严重错误提示
//        case QtCriticalMsg:
//                txt = QString("Critical: %1").arg(msg);
//        break;
//        //致命错误提示
//        case QtFatalMsg:
//                txt = QString("Fatal: %1").arg(msg);
//                abort();
//        }

//        QFile outFile("debuglog.txt");
//        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
//        QTextStream ts(&outFile);
//        ts << txt << endl;
//}
//QtMessageHandler qInstallMsgHandler(QtMessageHandler handler)
//{

//    //以后就可以像下面这样直接打日志到文件中，而且日志也会包含时间信息
//    qDebug("This is a debug message at thisisqt.com");
//    qWarning("This is a warning message  at thisisqt.com");
//    qCritical("This is a critical message  at thisisqt.com");
//    qFatal("This is a fatal message at thisisqt.com");
//    return handler;
//}


//#define _TIME_ qPrintable(QTime::currentTime().toString("hh:mm:ss:zzz"))

//static FILE *q_fileStream = NULL;
//static int   g_logLevel   = 0;

//enum TraceLevel
//{
//    TL_NULL = 0,
//    TL_CRIT,
//    TL_ERRO,
//    TL_WARN,
//    TL_INFO
//};

//static const int g_TraceLevel [] = { TL_INFO, TL_WARN, TL_ERRO, TL_CRIT, TL_NULL };

//static void SoftWareShutDown ()
//{
//    if (NULL != q_fileStream)
//    {
//        qDebug("Close log file.");
//        fclose (q_fileStream);
//        q_fileStream = NULL;
//    }
//}

//void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
//    Q_UNUSED(type);
//    QByteArray localMsg = msg.toLocal8Bit();
//    if (g_logLevel && q_fileStream)
//    {
//        int iLevel = g_TraceLevel[type];
//        if (g_logLevel < iLevel)
//        {
//            return;
//        }

//        fprintf (q_fileStream, "%s: %s (%s:%u, %s)\n", _TIME_, localMsg.constData(), context.file, context.line, context.function);
//        fflush (q_fileStream);
//    }
//}

//static void installMsgHandler(QString strLogFile)
//{
//    QByteArray byteArrayLogFile = strLogFile.toLatin1();

//    if (NULL != q_fileStream)
//    {
//        fclose (q_fileStream);
//        q_fileStream = NULL;
//    }

//    q_fileStream = fopen (byteArrayLogFile.constData (), "w+");
//    if (NULL != q_fileStream)
//    {
//        qDebug("Opened log file.");
//        qInstallMessageHandler(myMessageOutput);
//    }
//    else
//    {
//        qDebug("Failed to open log file.");
//    }
//}

//static void installReleaseMsgHandler ()
//{
//    QString strAppPath = QCoreApplication::applicationDirPath();
//    QString strIniFile = strAppPath + "/RunInfo.ini";
//    QString strLogFile = strAppPath + "/log.txt";
//    QSettings pSettings(strIniFile, QSettings::IniFormat);
//    g_logLevel = pSettings.value("TraceSet/TraceLevel", 1).toInt();
//    installMsgHandler (strLogFile);
//}

int main(int argc, char *argv[])
{
    //在面函数中注册自己的MsgHandler
//      qInstallMsgHandler(customMessageHandler);

//           //以后就可以像下面这样直接打日志到文件中，而且日志也会包含时间信息
//           qDebug("This is a debug message at thisisqt.com");
//           qWarning("This is a warning message  at thisisqt.com");
//           qCritical("This is a critical message  at thisisqt.com");
//           qFatal("This is a fatal message at thisisqt.com");
    QApplication a(argc, argv);


//#ifndef QT_DEBUG
//    bool bAddQuitFunc = false;
//    installReleaseMsgHandler();
//    if (!bAddQuitFunc)
//    {
//        qAddPostRoutine (SoftWareShutDown);
//        bAddQuitFunc = true;
//    }
//#endif
    PlayWindow w;
    w.show();


    return a.exec();
}
