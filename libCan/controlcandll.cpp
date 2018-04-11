#include "ControlCanDll.h"
#include <QtDebug>
#include <QTextEdit>
ControlCanDll * ControlCanDll::pControlCanDll = Q_NULLPTR;

ControlCanDll::ControlCanDll()
{
    //    init_Device();
    initMenber();
    init_config();
}
ControlCanDll *ControlCanDll::init()
{
    if(!pControlCanDll){
        pControlCanDll = new ControlCanDll;
    }
    return pControlCanDll;
}
VCI_INIT_CONFIG ControlCanDll::init_config()
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

//VCI_CAN_OBJ* ControlCanDll::init_Device_can_obj()
//{

//    for(int i=0;i<48;i++)
//    {

//        _p_vco[i].ID =0x701;//帧ID。32位变量，数据格式为靠右对齐
//        _p_vco[i].RemoteFlag =0;//是否是远程帧
//        _p_vco[i].ExternFlag =0;//是否是扩展帧
//        _p_vco[i].DataLen = 8;
//        _p_vco[i].SendType=0;//发送类型
//        _p_vco[i].Data[0]=0x01;
//        //     qDebug()<<_vco[i].ID<<_vco[i].RemoteFlag<<_vco[i].ExternFlag;
//        for(int j = 0;j<8;j++)
//        {

//            //        _p_vco[i].Data[j]=1;
//        }

//    }
//    //    qDebug()<<"canid"<<nCANInd<<"vic.AccCode"<<vic.AccCode<<vic.AccMask;
//    //    qDebug()<<"dwRel"<<nDeviceType<<"nDeviceType"<<nDeviceInd<<"nDeviceInd";
//    return _p_vco;
//}

_VCI_CAN_OBJ ControlCanDll::init_Device_can_obj2()
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
void ControlCanDll::initMenber()
{
    _nDeviceType = 4; /* USBCAN-2A或USBCAN-2C或CANalyst-II */
    _nDeviceInd = 0; /* 第1个设备 */
    _nCANInd=0;
}
bool ControlCanDll::OpenDevice()
{

    DWORD status_open;
    status_open = VCI_OpenDevice(_nDeviceType, _nDeviceInd, 0);
    //    qDebug()<<status_open<<"dwRelxxxxxx"<<nDeviceType<<"nDeviceType"<<nDeviceInd<<"nDeviceInd";
    if(status_open != 1)
    {
        //    MessageBox(_T("打开设备失败!"), _T("警告"), MB_OK|MB_ICONQUESTION);
       qDebug()<<"VCI_OpenDevice fault!"<<status_open;

        return false;
    }
    else {
         qDebug()<<"VCI_OpenDevice sucessful!"<<status_open;
        return true;
    }
}
bool ControlCanDll::CloseDevice()
{

    DWORD status_close;
    status_close = VCI_CloseDevice(_nDeviceType, _nDeviceInd);
    if(status_close != 1)
    {
        //    MessageBox(("关闭设备失败!"), ("警告"), MB_OK|MB_ICONQUESTION);
        qDebug()<<"error"<<"";
        return false;
    }
    else
    {
        qDebug()<<"close sucessful";
        return true;
    }
}
bool ControlCanDll::InitCAN()
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
      qDebug() <<dwRel<<"dwrel initcan"<<_nDeviceType<<_nDeviceInd<<_nCANInd;

    if(dwRel !=1)
    {

        CloseDevice();
       qDebug()<<"VCI_InitCAN fault"<<dwRel;
        return false;
    }
    else
    {
        qDebug()<<"VCI_InitCAN sucessful"<<dwRel;
        return true;
    }
}
bool ControlCanDll::ReadBoardInfo()//获取设备信息
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
bool ControlCanDll::StartCAN()
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

            qDebug()<<"VCI_StartCAN sucessful"<<dwRel<<"nCANInd"<<_nCANInd;
            return true;
        }

    }

}
bool ControlCanDll::Transmit(UINT id)//发送数据
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
    qDebug()<<dwRel<<"p_vco"<<_nDeviceType<<_nDeviceInd<< _nCANInd<< vco[0].ID<<vco[0].DataLen<<_size_num;
    //        qDebug()<<dwRel<<"VCI_Transmit"<<_nDeviceType<<_nDeviceInd<< _nCANInd<< _p_vco[0].ID<<_p_vco[0].DataLen<<_size_num;
    return dwRel;

}
VCI_CAN_OBJ  ControlCanDll::Receive()
{
    QTextEdit *textedit=new QTextEdit();

    VCI_CAN_OBJ receivedata[2500];

    int len;
        len=VCI_Receive(_nDeviceType, _nDeviceInd, _nCANInd,receivedata,2500,200);

                 for(int a=0;a<len;a++)
                 {
                     for(int b=0;b<receivedata[a].DataLen;b++)
                     {
                         qDebug()<<receivedata[0].Data[b]<<"";
                         qDebug()<<QString("%1").arg(receivedata[a].Data[b],8,16,QLatin1Char('0'))<<len<<receivedata[a].DataLen;
                         QString debugStr = QString("%1").arg(receivedata[a].Data[b],8,16,QLatin1Char('0'));
                         textedit->append(debugStr);
                         textedit->show();
//                          qDebug()<<debugStr;
//                          emit sigControlCanDllType(0,debugStr);
                     }
                 }


                 if(len!=-1)
                 {
                     return receivedata[0];
                 }
//                 else {
//                     return false;
//                 }
}

QString ControlCanDll::FindUsbDevice()
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
