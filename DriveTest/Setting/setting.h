#ifndef SETTING_H
#define SETTING_H
#include <QSettings>
#include <QCoreApplication>
#include <QDateTime>
#include <QFile>
class Setting : public QSettings
{
public:
    Setting();
    void setIni(QList<double> data,QString IniName);
    void ReadIni();
    void writeIni();
private:
    QSettings *Ini;
    QSettings *pIni;
    QString  ininame;
};

#endif // SETTING_H
