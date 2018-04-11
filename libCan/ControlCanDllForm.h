#ifndef CONTROLCANDLLFORM_H
#define CONTROLCANDLLFORM_H

#include <QWidget>
#include "controlcandll.h"
#include "lib/ControlCAN.h"
#include "message/messagedialog.h"
#include "parameter_configform.h"
#include <QtDebug>
#include <QStringList>

typedef struct DataBuffer
{
    UINT id;
    BYTE data[6];
    BYTE	DataLen;

}databuffer;
namespace Ui {
class ControlCanDllForm;
}

class ControlCanDllForm : public QWidget
{
    Q_OBJECT

public:
    static ControlCanDllForm*init();
    explicit ControlCanDllForm(QWidget *parent = 0);
    ~ControlCanDllForm();
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
    VCI_CAN_OBJ  Receive_info();
    VCI_CAN_OBJ Receive_config_Parameter();
    bool ReadBoardInfo();
    QString  FindUsbDevice();

    bool sendData(int index,int value );
//    QStringList Feedback_type();
    void Data_Back(int index);
    int system_config_data_back(int index);
    void write_configdata_back(int index);
    QMap<BYTE,QVariant> read_configdata_back(int index);
    int bytesToInt(byte* bytes,int size = 4);
    bool send_Config_Data(int index, int value_command_type,int value2,int value);
private slots:
    void on_pushButton_send_clicked();
    

//    void on_pushButton_START_CAN_clicked();

    void on_pushButton_start_probuffer_clicked();

    void on_pushButton_A_request_clicked();

    void on_pushButton_B_request_clicked();

    void on_pushButton_config_request_clicked();

    void on_pushButton_error_clicked();

private:
    Ui::ControlCanDllForm *ui;
//    Parameter_configForm * _configForm;
    int  _nDeviceType ; /* USBCAN-2A或USBCAN-2C或CANalyst-II */
    int  _nDeviceInd; /* 第1个设备 */
    int   _nCANInd;//第一条通道
    int _size_num=1;
    QStringList data;
    QStringList _feedback_type;
//    VCI_CAN_OBJ *_p_vco=new  VCI_CAN_OBJ[_size_num];
    VCI_INIT_CONFIG _vic;
//    VCI_CAN_OBJ *p_vco=new VCI_CAN_OBJ;
    struct _VCI_CAN_OBJ p_vco;
    //---
   static ControlCanDllForm *pControlCanDllForm;
   messageDialog *dialog = Q_NULLPTR;
//    VCI_CAN_OBJ receivedata;
   QMap<BYTE,QVariant> varMap;

   char* data_byte0;

   char* data_byte1;

   char* data_byte2;

   char* data_byte3;

   char* data_byte4;

   char* data_byte5;

   char* data_byte6;

   char* data_byte7;

   char* data_byte8;

   char* data_byte9;

   char* data_byte10;

   char* data_byte11;

   char* data_byte12;

   char* data_byte13;

   char* data_byte14;

   char* data_byte15;

};

#endif // CONTROLCANDLLFORM_H
