#include "ControlCanDllForm.h"
#include "ui_ControlCanDllForm.h"
#include <QByteArray>
using namespace std ;
ControlCanDllForm *ControlCanDllForm::pControlCanDllForm = Q_NULLPTR;

ControlCanDllForm::ControlCanDllForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlCanDllForm)
{

    initMenber();
    init_config();
    //    Feedback_type();
    ui->setupUi(this);
    dialog=new messageDialog(this);
    ui->lineEdit_START_buffer->setEnabled(false);
    ui->pushButton_A_request->setEnabled(false);
    ui->pushButton_B_request->setEnabled(false);
}

ControlCanDllForm::~ControlCanDllForm()
{
    delete ui;
}

ControlCanDllForm *ControlCanDllForm::init()
{
    if(!pControlCanDllForm){
        pControlCanDllForm = new ControlCanDllForm;
    }
    return pControlCanDllForm;
}
VCI_INIT_CONFIG ControlCanDllForm::init_config()
{
    _vic.AccCode=0x00000000;
    _vic.AccMask=0xFFFFFFFF;//屏蔽码
    _vic.Filter=0;//滤波方式
    _vic.Timing0=0x01;//波特率定时器 0（BTR0）
    _vic.Timing1=0x1c;//波特率定时器 1（BTR1）
    _vic.Mode=0;//模式。=0表示正常模式（相当于正常节点），=1表示只听模式（只接收，不影响总线），=2表示自发自收模式（环回模式）
    _vic.Reserved=0;
    return _vic;
}



_VCI_CAN_OBJ ControlCanDllForm::init_Device_can_obj2()
{

    p_vco.ID = 0x701;

    p_vco.RemoteFlag =0;//是否是远程帧
    p_vco.ExternFlag =0;//是否是扩展帧
    p_vco.DataLen = 8;
    p_vco.SendType=0;//发送类型
    for(int i=0;i<8;i++)
    {
        p_vco.Data[i]=i;
    }

    qDebug()<<p_vco.ID<<p_vco.DataLen<<"id datalen";
    return p_vco;
}
void ControlCanDllForm::initMenber()
{
    _nDeviceType = 4; /* USBCAN-2A或USBCAN-2C或CANalyst-II */
    _nDeviceInd = 0; /* 第1个设备 */
    _nCANInd=0;
}
bool ControlCanDllForm::OpenDevice()
{

    DWORD status_open;
    status_open = VCI_OpenDevice(_nDeviceType, _nDeviceInd, 0);
    //        qDebug()<<status_open<<"dwRelxxxxxx"<<_nDeviceType<<"nDeviceType"<<_nDeviceInd<<"nDeviceInd";
    if(status_open != 1)
    {
        //    MessageBox(_T("打开设备失败!"), _T("警告"), MB_OK|MB_ICONQUESTION);
        //       qDebug()<<"VCI_OpenDevice fault!"<<status_open;

        return false;
    }
    else {
        //         qDebug()<<"VCI_OpenDevice sucessful!"<<status_open;
        return true;
    }
}
bool ControlCanDllForm::CloseDevice()
{

    DWORD status_close;
    status_close = VCI_CloseDevice(_nDeviceType, _nDeviceInd);
    if(status_close != 1)
    {
        //    MessageBox(("关闭设备失败!"), ("警告"), MB_OK|MB_ICONQUESTION);
        //        qDebug()<<"error"<<"";
        return false;
    }
    else
    {
        //        qDebug()<<"close sucessful";
        return true;
    }
}
bool ControlCanDllForm::InitCAN()
{
    /* 第1个通道 */
    DWORD dwRel;

    //    dwRel = VCI_OpenDevice(nDeviceType, nDeviceInd, 0);
    if(!OpenDevice())
    {
        //    MessageBox(_T("打开设备失败!"), _T("警告"), MB_OK|MB_ICONQUESTION);

        return false;
    }

    dwRel = VCI_InitCAN(_nDeviceType, _nDeviceInd, _nCANInd, &_vic);
    //      qDebug() <<dwRel<<"dwrel initcan"<<_nDeviceType<<_nDeviceInd<<_nCANInd;

    if(dwRel !=1)
    {

        CloseDevice();
        //       qDebug()<<"VCI_InitCAN fault"<<dwRel;
        return false;
    }
    else
    {
        //        qDebug()<<"VCI_InitCAN sucessful"<<dwRel;
        return true;
    }
}
bool ControlCanDllForm::ReadBoardInfo()//获取设备信息
{
    VCI_BOARD_INFO vbi;
    DWORD dwRel;
    dwRel = VCI_ReadBoardInfo(_nDeviceType, _nDeviceInd, &vbi);
    if(dwRel != 1)
    {
        //    MessageBox(_T("获取设备信息失败!"), _T("警告"), MB_OK|MB_ICONQUESTION);
        return false;
    }
    else {
        return true;
    }
}
//打开can通道
bool ControlCanDllForm::StartCAN()
{
    DWORD dwRel;
    //    qDebug()<<"InitCAN()"<<InitCAN()<<_nCANInd;
    //    qDebug()<<"OpenDevice()"<<OpenDevice();
    if(!InitCAN()||!OpenDevice())
    {
        return false;

    }
    else
    {
        dwRel=VCI_StartCAN(_nDeviceType, _nDeviceInd, _nCANInd);

        if(dwRel!=1)
        {
            CloseDevice();
            return false;
        }
        else {

            //            qDebug()<<"VCI_StartCAN sucessful"<<dwRel<<"nCANInd"<<_nCANInd;
            return true;
        }

    }

}
bool ControlCanDllForm::Transmit(UINT id)//发送数据
{


    DWORD dwRel;
    VCI_CAN_OBJ vco[48];
    for(int i=0;i<48;i++)
    {
        vco[i].ID = id;
        vco[i].RemoteFlag = 0;
        vco[i].ExternFlag = 0;
        vco[i].DataLen = 8;
        for(int j = 0;j<8;j++)
            vco[i].Data[j] = j;
    }

    dwRel = VCI_Transmit(_nDeviceType, _nDeviceInd, _nCANInd, vco,_size_num);
    //    qDebug()<<dwRel<<"p_vco"<<_nDeviceType<<_nDeviceInd<< _nCANInd<< vco[0].ID<<vco[0].DataLen<<_size_num;
    //        qDebug()<<dwRel<<"VCI_Transmit"<<_nDeviceType<<_nDeviceInd<< _nCANInd<< _p_vco[0].ID<<_p_vco[0].DataLen<<_size_num;
    return dwRel;

}
VCI_CAN_OBJ  ControlCanDllForm::Receive()
{
    //    QTextEdit *textedit=new QTextEdit();

    VCI_CAN_OBJ receivedata;

    int len;
    len=VCI_Receive(_nDeviceType, _nDeviceInd, _nCANInd,&receivedata,2500,200);

    for(int a=0;a<len;a++)
    {
        for(int b=0;b<receivedata.DataLen;b++)
        {
            //                         qDebug()<<receivedata[0].DataLen<<"";
            //                         qDebug()<<QString("%1").arg(receivedata[a].Data[b],8,16,QLatin1Char('0'))<<len<<receivedata[a].DataLen;
            QString debugStr0 = QString("%1").arg(receivedata.Data[0],8,16,QLatin1Char('0'));
            QString debugStr1 = QString("%1").arg(receivedata.Data[1],8,16,QLatin1Char('0'));
            QString debugStr2 = QString("%1").arg(receivedata.Data[2],8,16,QLatin1Char('0'));
            QString debugStr3 = QString("%1").arg(receivedata.Data[3],8,16,QLatin1Char('0'));
            QString debugStr4 = QString("%1").arg(receivedata.Data[4],8,16,QLatin1Char('0'));
            QString debugStr5 = QString("%1").arg(receivedata.Data[5],8,16,QLatin1Char('0'));
            ui->lineEdit_A_request->setText(debugStr0);
            ui->lineEdit_A_response->setText(debugStr1);
            ui->lineEdit_B_request->setText(debugStr2);
            ui->lineEdit_B_response->setText(debugStr3);
            ui->lineEdit_config_request->setText(debugStr4);
            ui->lineEdit_config_response->setText(debugStr5);
            data.append(debugStr0);
            data.append(debugStr1);
            data.append(debugStr2);
            data.append(debugStr3);
            data.append(debugStr4);
            data.append(debugStr5);


        }
    }

    for(int i=0;i<data.size();i++)
    {
        //                    qDebug() <<data.at(i)<<"data.at(i)";
        QString datas= data.at(i);
        datas.toUInt(0,16);
        //                    qDebug()<<datas;
    }

    if(len!=-1)
    {
        return receivedata;
    }

}
VCI_CAN_OBJ ControlCanDllForm::Receive_info()
{
    VCI_CAN_OBJ receivedata;

    int len;
    len=VCI_Receive(_nDeviceType, _nDeviceInd, _nCANInd,&receivedata,2500,200);

    for(int a=0;a<len;a++)
    {
        for(int b=0;b<receivedata.DataLen;b++)
        {

            QString debugStr8=receivedata.Data[0];
            debugStr8.toInt();
            //                         qDebug()<<receivedata.Data[b]<<"";
            //                         qDebug()<<QString("%1").arg(receivedata[a].Data[b],8,16,QLatin1Char('0'))<<len<<receivedata[a].DataLen;
            QString debugStr0 = QString("%1").arg(receivedata.Data[0],8,16,QLatin1Char('0'));
            QString debugStr1 = QString("%1").arg(receivedata.Data[1],8,16,QLatin1Char('0'));
            QString debugStr2 = QString("%1").arg(receivedata.Data[2],8,16,QLatin1Char('0'));
            QString debugStr3 = QString("%1").arg(receivedata.Data[3],8,16,QLatin1Char('0'));
            QString debugStr4 = QString("%1").arg(receivedata.Data[4],8,16,QLatin1Char('0'));
            QString debugStr5 = QString("%1").arg(receivedata.Data[5],8,16,QLatin1Char('0'));
            QString debugStr6 = QString("%1").arg(receivedata.Data[6],8,16,QLatin1Char('0'));
            QString debugStr7 = QString("%1").arg(receivedata.Data[7],8,16,QLatin1Char('0'));
//            qDebug()<<debugStr0<<debugStr1<<debugStr2<<debugStr3<<debugStr4<<debugStr5<<debugStr6<<debugStr7<<"receive";

        }
    }

    return receivedata;
}
//VCI_CAN_OBJ ControlCanDllForm::Receive_config_Parameter()
//{
//    VCI_CAN_OBJ receivedata;

//    int len;
//    len=VCI_Receive(_nDeviceType, _nDeviceInd, _nCANInd,&receivedata,2500,200);

//    for(int a=0;a<len;a++)
//    {
//        for(int b=0;b<receivedata.DataLen;b++)
//        {

//            QString debugStr8=receivedata.Data[0];
//            debugStr8.toInt();
//            //                         qDebug()<<receivedata.Data[b]<<"";
//            //                         qDebug()<<QString("%1").arg(receivedata[a].Data[b],8,16,QLatin1Char('0'))<<len<<receivedata[a].DataLen;
//            QString debugStr0 = QString("%1").arg(receivedata.Data[0],8,16,QLatin1Char('0'));
//            QString debugStr1 = QString("%1").arg(receivedata.Data[1],8,16,QLatin1Char('0'));
//            QString debugStr2 = QString("%1").arg(receivedata.Data[2],8,16,QLatin1Char('0'));
//            QString debugStr3 = QString("%1").arg(receivedata.Data[3],8,16,QLatin1Char('0'));
//            QString debugStr4 = QString("%1").arg(receivedata.Data[4],8,16,QLatin1Char('0'));
//            QString debugStr5 = QString("%1").arg(receivedata.Data[5],8,16,QLatin1Char('0'));
//            QString debugStr6 = QString("%1").arg(receivedata.Data[6],8,16,QLatin1Char('0'));
//            QString debugStr7 = QString("%1").arg(receivedata.Data[7],8,16,QLatin1Char('0'));
////            qDebug()<<debugStr0<<debugStr1<<debugStr2<<debugStr3<<debugStr4<<debugStr5<<debugStr6<<debugStr7<<"receive";

//        }
//    }

//    return receivedata;
//}
QString ControlCanDllForm::FindUsbDevice()//暂时没用
{
    QString ProductSn[5];
    VCI_BOARD_INFO1 vbi;
    int num=VCI_FindUsbDevice(&vbi);
    QString strtemp,str;
    for(int i=0;i<num;i++)
    {
        str="";
        for(int j=0;j<4;j++)
        {

            strtemp.append("%i").arg(vbi.str_Usb_Serial[i][j]);

            str+=strtemp;
        }
        ProductSn[i]="USBCAN-"+str;

        return ProductSn[i];
    }

}
bool ControlCanDllForm::sendData(int index,int value)//A路B路数据查询发送
{
    //       index=0;
    QString id_text= data.at(index);//启动报文返回的ID

    qDebug()<<id_text<<"id_text"<<data.at(0)<<data.at(1)<<data.at(2)<<data.at(3)<<data.at(4)<<data.at(5);
    BYTE byte_arry[15]={0x00,
                        0x01,
                        0x02,
                        0x03,
                        0x04,
                        0x10,
                        0x20,
                        0x21,
                        0x22,
                        0x23,
                        0x24,
                        0x25,
                        0x26,
                        0x27,
                        0x28,};


    DWORD dwRel;
    VCI_CAN_OBJ vco[48];
    for(int i=0;i<48;i++)
    {
        vco[i].ID =  id_text.toUInt(0,16);
        vco[i].RemoteFlag = 0;
        vco[i].ExternFlag = 0;
        vco[i].DataLen = 6;

        vco[i].Data[0] = 0x00;
        vco[i].Data[1] = 0x00;
        vco[i].Data[2] = 0x00;
        vco[i].Data[3] = 0x00;
        vco[i].Data[4] = byte_arry[value];//反馈类型
        vco[i].Data[5] = 0x00;


    }

    dwRel = VCI_Transmit(_nDeviceType, _nDeviceInd, _nCANInd, vco,_size_num);
    //    qDebug()<<dwRel<<"p_vco"<<_nDeviceType<<_nDeviceInd<< _nCANInd<< vco[0].ID<<vco[0].DataLen<<_size_num;
    //        qDebug()<<dwRel<<"VCI_Transmit"<<_nDeviceType<<_nDeviceInd<< _nCANInd<< _p_vco[0].ID<<_p_vco[0].DataLen<<_size_num;
    return dwRel;


}
//参数配置
bool ControlCanDllForm::send_Config_Data(int index, int value_command_type,int value2,int value)
{
    QString id_text= data.at(index);//ID
    qDebug()<< data.at(index)<< "QString id_text=";
//    qDebug()<<id_text<<"id_text"<<data.at(0)<<data.at(1)<<data.at(2)<<data.at(3)<<data.at(4)<<data.at(5);
    BYTE byte_arry_command_type[]={
                        0x00,//系统命令0
                        0x01,//写入参数1
                        0x02,//读取参数2
                        0x03,//霍尔侦测3
                             };

    BYTE system_command_Parameter_address[]=//系统命令
    {
        0x00,
        0x01,
        0x02,
    };
    BYTE write_read_Parameter_address[]=//写入参数//读取参数
    {
        0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x10,0x11,/*int*/0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,/*float*/0x1B,0x1C,
        0x1D,0x1E,0x1F,0x30,/*int*/0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,
        0x41,0x42,/*float*/0x50,/*int*/0x51,0x52,0x53,0x54,0x55,0x56,/*float*/0x60,/*int*/0x61,0x62,0x63,0x64,0x65,0x66,/*float*/


    };
    BYTE hall_test[]=//霍尔侦测
    {
        0x01,
        0x02,
        0x03,
        0x04,
    };
    DWORD dwRel;
    VCI_CAN_OBJ vco[48];
    for(int i=0;i<48;i++)
    {
        vco[i].ID =  id_text.toUInt(0,16);
        vco[i].RemoteFlag = 0;
        vco[i].ExternFlag = 0;
        vco[i].DataLen = 6;

        vco[i].Data[0] = 0x00;
        vco[i].Data[1] = 0x00;
        vco[i].Data[2] = 0x00;
        vco[i].Data[3] = 0x00;

        if(value_command_type==0)
        {
         vco[i].Data[4] = system_command_Parameter_address[value2];
        }
        if(value_command_type==1)
        {
         vco[i].Data[4] = write_read_Parameter_address[value2];
        }
        if(value_command_type==2)
        {
         vco[i].Data[4] = write_read_Parameter_address[value2];
        }
        if(value_command_type==3)
        {
         vco[i].Data[4] = hall_test[value2];
        }
        vco[i].Data[5] = byte_arry_command_type[value];


    }

    dwRel = VCI_Transmit(_nDeviceType, _nDeviceInd, _nCANInd, vco,_size_num);
    //    qDebug()<<dwRel<<"p_vco"<<_nDeviceType<<_nDeviceInd<< _nCANInd<< vco[0].ID<<vco[0].DataLen<<_size_num;
    //        qDebug()<<dwRel<<"VCI_Transmit"<<_nDeviceType<<_nDeviceInd<< _nCANInd<< _p_vco[0].ID<<_p_vco[0].DataLen<<_size_num;
    return dwRel;
}
//byte转INT
int ControlCanDllForm::bytesToInt(byte* bytes,int size)
   {

    int addr = bytes[0] & 0xFF;
       addr |= (bytes[1] & 0x00FF);
       addr |= (bytes[2] & 0x0000FF);
       addr |= (bytes[3] & 0x000000FF);
        return addr;

    }

void ControlCanDllForm::Data_Back(int index)
{


    for(int i=0;i<15;i++)
    {
        switch (i) {
        case 0:
        {
            if(sendData(index,0))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                QByteArray b;
                for(int i=0;i<4;i++)
                {
                    b.insert(i,receivedata.Data[i]);
                }

                ui->lineEdit_0->setText(tr("%1").arg(b.toDouble()));
                Sleep(200);
            }
            break;
        }
        case 1:
        {
            if(sendData(index,1))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                int value= bytesToInt(receivedata.Data);

                 qDebug()<<value<<"value"<<receivedata.Data[0];
//                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
//                float *p = (float*)pMem;

                ui->lineEdit_1->setText(tr("%1").arg(value));
                Sleep(200);
            }
            break;
        }
        case 2:
        {
            if(sendData(index,2))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                //                 int int_value=  bytesToInt(receivedata.Data,0);



                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
//                QByteArray b;
//                for(int i=0;i<4; ++i){
//                    b.insert(i,receivedata.Data[i]);
//                }
//                qDebug()<<"----b:"<<b.toHex()<<b.toFloat()<<b.toDouble()<<b.toHex().toDouble()<<b.toFloat()<<b.toHex().toFloat()<<b.toLongLong();
                float *p = (float*)pMem;
                qDebug()<<"----["<<*p<<"]----------"<<receivedata.Data[0]<<receivedata.Data[1]<<receivedata.Data[2]<<receivedata.Data[3];
                //                qDebug()<<*p<<"*p"<<receivedata.Data[0]<<receivedata.Data[1]<<receivedata.Data[2]<<receivedata.Data[3];
                //                 QByteArray int_value=receivedata.Data;


                                ui->lineEdit_2->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }
        case 3:
        {
            if(sendData(index,3))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
                float *p = (float*)pMem;
                ui->lineEdit_3->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }
        case 4:
        {
            if(sendData(index,4))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
                float *p = (float*)pMem;
                ui->lineEdit_4->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }
        case 5:
        {
            if(sendData(index,5))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                qDebug()<<receivedata.Data<<"DATA";
//                int value=bytesToInt(receivedata.Data);
                BYTE mask=0x80;
//                QByteArray b;


                      if(((receivedata.Data[0]<<0)&mask)==1)
                      {
                          ui->lineEdit_00->setText("GVDD 过压报警 ");
//                          ui->listWidget_warning->addItem("GVDD Over voltage alarm");
                      }
                      else {
                          ui->lineEdit_00->setText("true ");
//                          ui->listWidget_warning->addItem("GVDD Over voltage alarm");
                      }
                      if(((receivedata.Data[0]<<1)&mask)==1)
                      {
                         ui->lineEdit_01->setText(QStringLiteral("C 相下桥臂过流 "));
                      }
                      else {
                          ui->lineEdit_01->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[0]<<2)&mask)==1)
                      {
                         ui->lineEdit_02->setText(QStringLiteral("B 相下桥臂过流 "));
                      }
                      else {
                          ui->lineEdit_02->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[0]<<3)&mask)==1)
                      {
                         ui->lineEdit_03->setText(QStringLiteral("A 相下桥臂过流 "));
                      }
                      else {
                          ui->lineEdit_03->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[0]<<4)&mask)==1)
                      {
                         ui->lineEdit_04->setText(QStringLiteral("C 相上桥臂过流 "));
                      }
                      else {
                          ui->lineEdit_04->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[0]<<5)&mask)==1)
                      {
                         ui->lineEdit_05->setText(QStringLiteral("B 相上桥臂过流 "));
                      }
                      else {
                          ui->lineEdit_05->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[0]<<6)&mask)==1)
                      {
                         ui->lineEdit_06->setText(QStringLiteral("A 相上桥臂过流  "));
                      }
                      else {
                          ui->lineEdit_06->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[0]<<7)&mask)==1)
                      {
                         ui->lineEdit_07->setText(QStringLiteral("温度过高报警 "));
                      }
                      else {
                          ui->lineEdit_07->setText(QStringLiteral("正常 "));
                      }
//                  qDebug()<<b.toHex()<<"b.toHex()"<<value<<ss;


                      if(((receivedata.Data[1]<<0)&mask)==1)
                      {
                          ui->lineEdit_08->setText(QStringLiteral("PVDD 欠压报警  "));
                      }
                      else {
                          ui->lineEdit_08->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[1]<<1)&mask)==1)
                      {
                         ui->lineEdit_09->setText(QStringLiteral("GVDD 欠压报 "));
                      }
                      else {
                          ui->lineEdit_09->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[1]<<2)&mask)==1)
                      {
                         ui->lineEdit_010->setText(QStringLiteral("驱动器硬件错误  "));
                      }
                      else {
                          ui->lineEdit_010->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[1]<<3)&mask)==1)
                      {
                         ui->lineEdit_011->setText(QStringLiteral("驱动器被拍下急停  "));
                      }
                      else {
                          ui->lineEdit_011->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[1]<<4)&mask)==1)
                      {
                         ui->lineEdit_012->setText(QStringLiteral("固件参数尚未烧录  "));
                      }
                      else {
                          ui->lineEdit_012->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[1]<<5)&mask)==1)
                      {
                         ui->lineEdit_013->setText(QStringLiteral("无霍尔初始化定位失败  "));
                      }
                      else {
                          ui->lineEdit_013->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[1]<<6)&mask)==1)
                      {
                         ui->lineEdit_014->setText(QStringLiteral(" 驱动芯片连接故障   "));
                      }
                      else {
                          ui->lineEdit_014->setText(QStringLiteral("正常 "));
                      }
                      if(((receivedata.Data[1]<<7)&mask)==1)
                      {
                         ui->lineEdit_015->setText(QStringLiteral("霍尔错误报警 "));
                      }
                      else {
                          ui->lineEdit_015->setText(QStringLiteral("正常 "));
                      }


//             ui->lineEdit_5->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }
        case 6:
        {
            if(sendData(index,6))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                int value=bytesToInt(receivedata.Data);
//                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
//                float *p = (float*)pMem;
                ui->lineEdit_6->setText(tr("%1").arg(value));
                Sleep(200);
            }
            break;
        }
        case 7:
        {
            if(sendData(index,7))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
                float *p = (float*)pMem;
                ui->lineEdit_7->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }
        case 8:
        {
            if(sendData(index,8))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
                float *p = (float*)pMem;
                ui->lineEdit_8->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }
        case 9:
        {
            if(sendData(index,9))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
                float *p = (float*)pMem;
                ui->lineEdit_9->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }
        case 10:
        {
            if(sendData(index,10))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
                float *p = (float*)pMem;
                ui->lineEdit_10->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }
        case 11:
        {
            if(sendData(index,11))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
                float *p = (float*)pMem;
                ui->lineEdit_11->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }
        case 12:
        {
            if(sendData(index,12))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
                float *p = (float*)pMem;
                ui->lineEdit_12->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }
        case 13:
        {
            if(sendData(index,13))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
                float *p = (float*)pMem;
                ui->lineEdit_13->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }
        case 14:
        {
            if(sendData(index,14))
            {
                VCI_CAN_OBJ receivedata= Receive_info();
                unsigned char pMem[] = {receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
                float *p = (float*)pMem;
                ui->lineEdit_14->setText(tr("%1").arg(*p));
                Sleep(200);
            }
            break;
        }

        default:
            break;
        }

    }


}

int ControlCanDllForm::system_config_data_back(int index)
{


          if(send_Config_Data(index,0,2,0))
            {
             VCI_CAN_OBJ receivedata=Receive_info();
             QString data_str=QString("%1").arg(receivedata.Data[4],8,16,QLatin1Char('0'));
             int dat_value= data_str.toInt();
            for(int j=0;j<receivedata.DataLen;j++)
            {
                if(dat_value==0)
                    qDebug()<<QStringLiteral("ok");
                if(dat_value==1)
                    qDebug()<<QStringLiteral("Command send timeout");
                if(dat_value==2)
                    qDebug()<<QStringLiteral("Check the error");
                if(dat_value==3)
                    qDebug()<<QStringLiteral("Unpack the failure");
                if(dat_value==4)
                    qDebug()<<QStringLiteral("Command read is not supported in hall detection.");
            }

            BYTE BYTES[4]={receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
            int values=bytesToInt(BYTES,4);
            qDebug()<<values<<"data_value";
            return values;
         }


}
void ControlCanDllForm::write_configdata_back(int index)
{
    for(int i=0;i<56;i++)
    {
     switch (i)
       {
       case 0:
          {
           if(send_Config_Data(index,1,0,1))
           {
               VCI_CAN_OBJ receivedata=Receive_info();
               BYTE BYTES[4]={receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
               int values=bytesToInt(BYTES,4);
//               varMap.insert(0x01,values);
//              qDebug()<<values<<"xxxxxxxx1"<<varMap.value(0x01).toInt() ;
           }

         break;
         }
       case 1:
     {
         if(send_Config_Data(index,1,1,1))
         {
             VCI_CAN_OBJ receivedata=Receive_info();
             BYTE BYTES[4]={receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
             int values=bytesToInt(BYTES,4);
//             varMap.insert(0x02,values);
//            qDebug()<<values<<"xxxxxxxx2"<<varMap.value(0x02).toInt() ;
         }

       break;
       }
     }

   }
}
QMap<BYTE,QVariant> ControlCanDllForm::read_configdata_back(int index)
{
    for(int i=0;i<9;i++)
    {

           if(send_Config_Data(index,2,i,2))
           {
               VCI_CAN_OBJ receivedata=Receive_info();
               BYTE BYTES[4]={receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
               int values=bytesToInt(BYTES,4);
               varMap.insert(i,values);
               QString debugStr0 = QString("%1").arg(receivedata.Data[0],8,16,QLatin1Char('0'));
               QString debugStr1 = QString("%1").arg(receivedata.Data[1],8,16,QLatin1Char('0'));
               QString debugStr2 = QString("%1").arg(receivedata.Data[2],8,16,QLatin1Char('0'));
               QString debugStr3 = QString("%1").arg(receivedata.Data[3],8,16,QLatin1Char('0'));
          qDebug()<<values<<"xxxxxxxx1"<<varMap.value(i).toInt()<<debugStr0<<debugStr1<<debugStr2<<debugStr3 ;
              Sleep(200);
           }

   }
    for(int i=9;i<18;i++)
    {
        if(send_Config_Data(index,2,i,2))
        {
            VCI_CAN_OBJ receivedata=Receive_info();
            BYTE BYTES[4]={receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
            float *p = (float*)BYTES;
            varMap.insert(i,*p);
            QString debugStr0 = QString("%1").arg(receivedata.Data[0],8,16,QLatin1Char('0'));
            QString debugStr1 = QString("%1").arg(receivedata.Data[1],8,16,QLatin1Char('0'));
            QString debugStr2 = QString("%1").arg(receivedata.Data[2],8,16,QLatin1Char('0'));
            QString debugStr3 = QString("%1").arg(receivedata.Data[3],8,16,QLatin1Char('0'));
       qDebug()<<*p<<"xxxxxxxx1"<<varMap.value(i).toFloat()<<debugStr0<<debugStr1<<debugStr2<<debugStr3 ;
           Sleep(200);
        }
    }
    for(int i=18;i<24;i++)
    {
        if(send_Config_Data(index,2,i,2))
        {
            VCI_CAN_OBJ receivedata=Receive_info();
            BYTE BYTES[4]={receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
            int values=bytesToInt(BYTES,4);
            varMap.insert(i,values);
            QString debugStr0 = QString("%1").arg(receivedata.Data[0],8,16,QLatin1Char('0'));
            QString debugStr1 = QString("%1").arg(receivedata.Data[1],8,16,QLatin1Char('0'));
            QString debugStr2 = QString("%1").arg(receivedata.Data[2],8,16,QLatin1Char('0'));
            QString debugStr3 = QString("%1").arg(receivedata.Data[3],8,16,QLatin1Char('0'));
          qDebug()<<values<<"xxxxxxxx1"<<varMap.value(i).toInt()<<debugStr0<<debugStr1<<debugStr2<<debugStr3 ;
           Sleep(200);
        }
    }
    for(int i=24;i<42;i++)
    {
        if(send_Config_Data(index,2,i,2))
        {
            VCI_CAN_OBJ receivedata=Receive_info();
            BYTE BYTES[4]={receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
            float *p = (float*)BYTES;
            varMap.insert(i,*p);
            QString debugStr0 = QString("%1").arg(receivedata.Data[0],8,16,QLatin1Char('0'));
            QString debugStr1 = QString("%1").arg(receivedata.Data[1],8,16,QLatin1Char('0'));
            QString debugStr2 = QString("%1").arg(receivedata.Data[2],8,16,QLatin1Char('0'));
            QString debugStr3 = QString("%1").arg(receivedata.Data[3],8,16,QLatin1Char('0'));
       qDebug()<<*p<<"xxxxxxxx1"<<varMap.value(i).toFloat()<<debugStr0<<debugStr1<<debugStr2<<debugStr3 ;
           Sleep(200);
        }
    }
    if(send_Config_Data(index,2,42,2))
    {
        VCI_CAN_OBJ receivedata=Receive_info();
        BYTE BYTES[4]={receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
        int values=bytesToInt(BYTES,4);
        varMap.insert(42,values);
        QString debugStr0 = QString("%1").arg(receivedata.Data[0],8,16,QLatin1Char('0'));
        QString debugStr1 = QString("%1").arg(receivedata.Data[1],8,16,QLatin1Char('0'));
        QString debugStr2 = QString("%1").arg(receivedata.Data[2],8,16,QLatin1Char('0'));
        QString debugStr3 = QString("%1").arg(receivedata.Data[3],8,16,QLatin1Char('0'));
          qDebug()<<values<<"xxxxxxxx1"<<varMap.value(42).toInt()<<debugStr0<<debugStr1<<debugStr2<<debugStr3 ;
       Sleep(200);
    }
    for(int i=43;i<49;i++)
    {
        if(send_Config_Data(index,2,i,2))
        {
            VCI_CAN_OBJ receivedata=Receive_info();
            BYTE BYTES[4]={receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
            float *p = (float*)BYTES;
            varMap.insert(i,*p);
            QString debugStr0 = QString("%1").arg(receivedata.Data[0],8,16,QLatin1Char('0'));
            QString debugStr1 = QString("%1").arg(receivedata.Data[1],8,16,QLatin1Char('0'));
            QString debugStr2 = QString("%1").arg(receivedata.Data[2],8,16,QLatin1Char('0'));
            QString debugStr3 = QString("%1").arg(receivedata.Data[3],8,16,QLatin1Char('0'));
       qDebug()<<*p<<"xxxxxxxx1"<<varMap.value(i).toFloat()<<debugStr0<<debugStr1<<debugStr2<<debugStr3 ;
           Sleep(200);
        }
    }
    if(send_Config_Data(index,2,49,2))
    {
        VCI_CAN_OBJ receivedata=Receive_info();
        BYTE BYTES[4]={receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
        int values=bytesToInt(BYTES,4);
        varMap.insert(49,values);
        QString debugStr0 = QString("%1").arg(receivedata.Data[0],8,16,QLatin1Char('0'));
        QString debugStr1 = QString("%1").arg(receivedata.Data[1],8,16,QLatin1Char('0'));
        QString debugStr2 = QString("%1").arg(receivedata.Data[2],8,16,QLatin1Char('0'));
        QString debugStr3 = QString("%1").arg(receivedata.Data[3],8,16,QLatin1Char('0'));
          qDebug()<<values<<"xxxxxxxx1"<<varMap.value(49).toInt()<<debugStr0<<debugStr1<<debugStr2<<debugStr3 ;
       Sleep(200);
    }
    for(int i=50;i<56;i++)
    {
        if(send_Config_Data(index,2,i,2))
        {
            VCI_CAN_OBJ receivedata=Receive_info();
            BYTE BYTES[4]={receivedata.Data[0],receivedata.Data[1],receivedata.Data[2],receivedata.Data[3]};
            float *p = (float*)BYTES;
            varMap.insert(i,*p);
            QString debugStr0 = QString("%1").arg(receivedata.Data[0],8,16,QLatin1Char('0'));
            QString debugStr1 = QString("%1").arg(receivedata.Data[1],8,16,QLatin1Char('0'));
            QString debugStr2 = QString("%1").arg(receivedata.Data[2],8,16,QLatin1Char('0'));
            QString debugStr3 = QString("%1").arg(receivedata.Data[3],8,16,QLatin1Char('0'));
       qDebug()<<*p<<"xxxxxxxx1"<<varMap.value(i).toFloat()<<debugStr0<<debugStr1<<debugStr2<<debugStr3 ;
           Sleep(200);
        }
    }
    return varMap;
}
void ControlCanDllForm::on_pushButton_send_clicked()
{
    QString id= ui->lineEdit_ID->text();
    Transmit(id.toInt(0,16));
    Receive_info();

}



void ControlCanDllForm::on_pushButton_start_probuffer_clicked()
{
    if(StartCAN())
    {
        QString id= ui->lineEdit_START_buffer->text();
        Transmit(id.toInt(0,16));
        Receive();
    }


    //    ui->pushButton_start_probuffer->setEnabled(false);

}

void ControlCanDllForm::on_pushButton_A_request_clicked()
{

    Data_Back(0);

}

void ControlCanDllForm::on_pushButton_B_request_clicked()
{
    Data_Back(2);
}

void ControlCanDllForm::on_pushButton_config_request_clicked()
{
     Parameter_configForm * _configForm =new Parameter_configForm;
    _configForm->getdata(system_config_data_back(4));
    QMap<BYTE,QVariant> _varMap=read_configdata_back(4);
    _configForm->setVariantMap(_varMap);
    qDebug()<< varMap.value(42).toInt()<<"xx";
    _configForm->show();
    Sleep(2000);
    ui->pushButton_A_request->setEnabled(true);
    ui->pushButton_B_request->setEnabled(true);
}

void ControlCanDllForm::on_pushButton_error_clicked()
{
//    sendData()
}
