#ifndef PARAMETER_CONFIGFORM_H
#define PARAMETER_CONFIGFORM_H

#include <QWidget>
#include <QMap>
#include "ControlCanDllForm.h"
#include "lib/ControlCAN.h"


namespace Ui {
class Parameter_configForm;
}

class Parameter_configForm : public QWidget
{
    Q_OBJECT

public:
    explicit Parameter_configForm(QWidget *parent = 0);
    ~Parameter_configForm();
    void Parameter_config_data();
    int getdata(int value);

    void init_command_config();
    QMap<BYTE, QVariant> getVariantMap() const;
    void setVariantMap(const QMap<BYTE, QVariant> &value);

private slots:
    void on_pushButton_enable_status_clicked();

private:

    Ui::Parameter_configForm *ui;
    int value_;

    QMap<BYTE,QVariant> VariantMap;
};

#endif // PARAMETER_CONFIGFORM_H
