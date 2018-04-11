#ifndef CONFIGURATION
#define CONFIGURATION

#include <QWidget>

#include "controlcandll.h"

typedef struct Parameter{
    int	AccCode_value;//验收码。SJA1000的帧过滤验收码
    int	AccMask_value;//屏蔽码
    int	Reserved_value;//保留。
    int	Filter_value;//滤波方式，允许设置为0-3
    int	kbs_value;//波特率定时器 0（BTR0）。
    int nCANInd_value;//通道
    int	Mode_value;//模式。=0表示正常模式（相当于正常节点），=1表示只听模式（只接收，不影响总线），=2表示自发自收模式（环回模式）

    int	ID_value;//帧ID。32位变量，数据格式为靠右对齐
    int	TimeStamp_value;//设备接收到某一帧的时间标识。时间标示从CAN卡上电开始计时，计时单位为0.1ms
    int	TimeFlag_value;//是否使用时间标识，为1时TimeStamp有效，TimeFlag和TimeStamp只在此帧为接收帧时有意义
    int	SendType_value;//发送帧类型。
//    =0时为正常发送（发送失败会自动重发，重发最长时间为1.5-3秒）；
//    =1时为单次发送（只发送一次，不自动重发）；
//    其它值无效。
//    （二次开发，建议SendType=1，提高发送的响应速度）
    int	RemoteFlag_value;//是否是远程帧
    int	ExternFlag_value;//是否是扩展帧
    int	DataLen_value;//数据长度 DLC (<=8)，即CAN帧Data有几个字节。约束了后面Data[8]中的有效字节
//    int	Data[8];//CAN帧的数据。由于CAN规定了最大是8个字节，所以这里预留了8个字节的空间，受 DataLen约束。如DataLen定义为3，即Data[0]、Data[1]、Data[2]是有效的。
//    int num;//发送的总帧数
}VCI_INIT,*PVCI_INIT;
namespace Ui {
class ConFiguration;
}

class ConFiguration : public QWidget
{
    Q_OBJECT

public:
    explicit ConFiguration(QWidget *parent = 0);
    ~ConFiguration();
    void init();
private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancle_clicked();

private:
    Ui::ConFiguration *ui;

    VCI_INIT_CONFIG vci_config;
    int _size_num=48;
//    VCI_CAN_OBJ vci_obj[48];
    VCI_CAN_OBJ *p_vci_obj=new VCI_CAN_OBJ[_size_num];
    VCI_INIT VCI;
};

#endif // CONFIGURATION
