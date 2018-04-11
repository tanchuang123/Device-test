#include "ConFiguration.h"
#include "ui_ConFiguration.h"
#include <QtDebug>

ConFiguration::ConFiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConFiguration)
{
    ui->setupUi(this);
     ui->lineEdit_all_frames->setEnabled(false);
}

ConFiguration::~ConFiguration()
{
    if(close())
    {
      delete ui;
    }

}

void ConFiguration::on_pushButton_ok_clicked()
{
    init();
    close();
}

void ConFiguration::on_pushButton_cancle_clicked()
{
    close();
}
void ConFiguration::init()
{
    vci_config.AccCode=ui->lineEdit_accode->text().toULong(Q_NULLPTR,16);
    vci_config.AccMask=ui->lineEdit_AccMask->text().toULong(Q_NULLPTR,16);
    //    QString value=ui->lineEdit_accode->text();
    //    vci_config.AccCode=value.toULong();
    qDebug()<<vci_config.AccCode<<"vci_config.AccCode"<<ui->lineEdit_accode->text().toULong(Q_NULLPTR,16)<<vci_config.AccMask;

    VCI.Filter_value=ui->comboBox_receive_type->currentIndex();
    VCI.Mode_value=ui->comboBox_work_type->currentIndex();
    //qDebug()<<QString("%1").arg(vci_config.AccCode)
    //    vci_config.Mode=ui->comboBox_work_type->currentIndex();
    //    qDebug()<<"VCI.Mode_value"<<vci_config.Mode;
    VCI.kbs_value=ui->comboBox_bps->currentIndex();
    VCI.nCANInd_value=ui->comboBox_can->currentIndex();
    VCI.ID_value=ui->lineEdit_ID->text().toUInt();

//    int value;
//    value=ui->lineEdit_ID->text().toInt();

    if(ui->lineEdit_all_frames->text().isEmpty())
    {
//        VCI.num=48;
        _size_num=48;
    }
    else
    {
        _size_num=ui->lineEdit_all_frames->text().toUInt();
    }
    for(int i=0;i<_size_num;i++)

    {
        if(ui->checkBox_IDadd->checkState())
        {
             p_vci_obj[i].ID=VCI.ID_value++;
             ui->lineEdit_ID->setText(tr("%1").arg(p_vci_obj[i].ID));
//             qDebug()<<"p_vci_obj[i].ID"<<p_vci_obj[i].ID;
        }
        else {
            p_vci_obj[i].ID=VCI.ID_value;
            ui->lineEdit_ID->setText(tr("%1").arg(p_vci_obj[i].ID));
          //   qDebug()<<"p_vci_obj[i].ID"<<p_vci_obj[i].ID;
        }
    }


    //    VCI.SendType_value=ui->comboBox_2->currentIndex();

    VCI.RemoteFlag_value=ui->comboBox_2->currentIndex();
    VCI.ExternFlag_value=ui->comboBox->currentIndex();

    if(VCI.RemoteFlag_value==0)
    {
         for(int i=0;i<_size_num;i++)
        p_vci_obj[i].RemoteFlag=0;

    }
    else {
         for(int i=0;i<_size_num;i++)
        p_vci_obj[i].RemoteFlag=1;
    }
    if(VCI.ExternFlag_value==0)
    {
         for(int i=0;i<_size_num;i++)
        p_vci_obj[i].ExternFlag=0;
    }
    else {
         for(int i=0;i<_size_num;i++)
        p_vci_obj[i].ExternFlag=1;
    }

//    VCI.DataLen_value=8;
    p_vci_obj->DataLen=8;
    switch (VCI.Mode_value)
    {
    case 0:
        vci_config.Mode=0;
        break;
    case 1:
        vci_config.Mode=1;
        break;
    case 2:
        vci_config.Mode=2;
        break;
    default:
        break;
    }

    switch (VCI.Filter_value)
    {
    case 0:
        vci_config.Filter=1;
        break;
    case 1:
        vci_config.Filter=2;
        break;
    case 2:
        vci_config.Filter=3;
        break;
    default:
        break;
    }
    switch (VCI.kbs_value)
    {
    case 0:
        vci_config.Timing0=0x01;
        vci_config.Timing1=0x1C;
        break;
    case 1:
        vci_config.Timing0=0x31;
        vci_config.Timing1=0x1C;
        break;
    case 2:
        vci_config.Timing0=0x18;
        vci_config.Timing1=0x1C;
        break;
    case 3:
        vci_config.Timing0=0x87;
        vci_config.Timing1=0xFF;
        break;
    case 4:
        vci_config.Timing0=0x09;
        vci_config.Timing1=0x1C;
        break;
    case 5:
        vci_config.Timing0=0x83;
        vci_config.Timing1=0xFF;
        break;
    case 6:
        vci_config.Timing0=0x04;
        vci_config.Timing1=0x1C;
        break;
    case 7:
        vci_config.Timing0=0x03;
        vci_config.Timing1=0x1C;
        break;
    case 8:
        vci_config.Timing0=0x81;
        vci_config.Timing1=0xFA;
        break;
    case 9:
        vci_config.Timing0=0x01;
        vci_config.Timing1=0x1C;
        break;
    case 10:
        vci_config.Timing0=0x80;
        vci_config.Timing1=0xFA;
        break;
    case 11:
        vci_config.Timing0=0x00;
        vci_config.Timing1=0x1C;
        break;
    case 12:
        vci_config.Timing0=0x80;
        vci_config.Timing1=0xB6;
        break;
    case 13:
        vci_config.Timing0=0x00;
        vci_config.Timing1=0x16;
        break;
    case 14:
        vci_config.Timing0=0x00;
        vci_config.Timing1=0x14;
        break;
    case 15:
        vci_config.Timing0=0x09;
        vci_config.Timing1=0x6F;
        break;
    case 16:
        vci_config.Timing0=0x04;
        vci_config.Timing1=0x6F;
        break;
    case 17:
        vci_config.Timing0=0x03;
        vci_config.Timing1=0x6F;
        break;

    default:

        break;
    }


//    ControlCanDll::init()->init_Device(VCI.nCANInd_value,vci_config,vci_obj,VCI.num);
//    qDebug()<<"---------:"<<VCI.nCANInd_value;
    qDebug()<<"22222222222222"<<VCI.nCANInd_value<<"";
//    ControlCanDll::init()->init_can_num( VCI.nCANInd_value);
//    ControlCanDll::init()->init_config(vci_config);
//    ControlCanDll::init()->init_Device_can_obj(p_vci_obj,_size_num);
    
    
    //    qDebug()<<ui->comboBox_can->currentIndex()<<"canindex"<<vci_config.Timing0<<vci_config.Timing1;
}
