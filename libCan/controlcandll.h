#ifndef CONTROLCANDLL_H
#define CONTROLCANDLL_H

#include "lib/ControlCAN.h"
#include <QString>
#include "CanFrame/HelpByteArray.h"
//#include "ControlCanDllForm.h"
class ControlCanDll
{

public:
    ControlCanDll();
    static ControlCanDll*init();
//    bool init_Device(int can_one,VCI_INIT_CONFIG text_two,VCI_CAN_OBJ text_three,int num);
    VCI_INIT_CONFIG init_config();
//    VCI_CAN_OBJ* init_Device_can_obj();
    _VCI_CAN_OBJ init_Device_can_obj2();

    int init_can_num(int num);
    void initMenber();
    bool OpenDevice();
    bool CloseDevice();
    bool InitCAN();
    bool StartCAN();
    bool Transmit(UINT id);
    VCI_CAN_OBJ Receive();

    bool ReadBoardInfo();
    QString  FindUsbDevice();
private:
    int  _nDeviceType ; /* USBCAN-2A或USBCAN-2C或CANalyst-II */
    int  _nDeviceInd; /* 第1个设备 */
    int   _nCANInd;//第一条通道
    int _size_num=1;

//    VCI_CAN_OBJ *_p_vco=new  VCI_CAN_OBJ[_size_num];
    VCI_INIT_CONFIG _vic;
//    VCI_CAN_OBJ *p_vco=new VCI_CAN_OBJ;
    struct _VCI_CAN_OBJ p_vco;
    //---
    static ControlCanDll *pControlCanDll;
signals:
    void sigControlCanDllType(int type,const QString &str);
};

#endif // CONTROLCANDLL_H
