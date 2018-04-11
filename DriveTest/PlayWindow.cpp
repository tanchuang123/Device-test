#include "PlayWindow.h"
#include "ui_PlayWindow.h"

PlayWindow::PlayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);
    ui->pushButton_save_ini->setEnabled(false);
    connect(ui->lineEdit_ini,SIGNAL(textChanged(QString)),this,SLOT(open_button()));
    ui->toolButton_color->setEnabled(false);
    // Some Initializations
    serialOpenStatus = false;//串口打开状态

    timerScan = new QTimer(this);//定时器扫描
    connect(timerScan,SIGNAL(timeout()),this,SLOT(ScanSerialPorts()));

    timerReceive = new QTimer(this);//接收
    connect(timerReceive,SIGNAL(timeout()),this,SLOT(ReadSerialBuffer()));

    timerReflesh = new QTimer(this);//刷新
    connect(timerReflesh,SIGNAL(timeout()),this,SLOT(Reflesh()));

    mySerialPort = new QSerialPort(this);//串行端口

    storeLength = ui->spinBox_storeLength->text().toLong();//存储数据长度

//    InitPlotTheme();//绘图界面初始化


    //每SCAN_INTERVAL毫秒扫描一次串口
    timerScan->start(SCAN_INTERVAL);//3秒

}

PlayWindow::~PlayWindow()
{
    delete ui;
}

void PlayWindow::open_button()
{

    ui->pushButton_save_ini->setEnabled(true);
}

void PlayWindow::on_pushButton_save_ini_clicked()
{
   QString ininame= ui->lineEdit_ini->text();


   ui->widget_chartView->setIniName(ininame);
   ui->pushButton_save_ini->setEnabled(false);
}

void PlayWindow::on_pushButton_connect_clicked()//连接端口
{
    if(!PlayWindow::serialOpenStatus && !ui->comboBox_portName->currentText().isEmpty())
        {

            mySerialPort->setPortName(ui->comboBox_portName->currentText());
            mySerialPort->open(QIODevice::ReadWrite);//打开端口

            QSerialPortInfo *my_serialInfo = new QSerialPortInfo(mySerialPort->portName());//串行端口索引
            qDebug()<<"Current PortName:"<<my_serialInfo->portName();
            qDebug()<<"Description:"<<my_serialInfo->description();
            qDebug()<<"Manufacturer:"<<my_serialInfo->manufacturer();

            ui->textEdit_serialInfo->setEnabled(false);
            ui->textEdit_serialInfo->append(my_serialInfo->portName()+'\n'+my_serialInfo->description()+'\n'+my_serialInfo->manufacturer());//显示状态数据

            mySerialPort->setBaudRate(ui->comboBox_baudRate->currentText().toInt());       //设定波特率
            mySerialPort->setDataBits((QSerialPort::DataBits)ui->comboBox_dataBits->currentText().toInt());    //设定数据位
            mySerialPort->setStopBits((QSerialPort::StopBits)ui->comboBox_stopBits->currentText().toInt());    //设定停止位
            switch(ui->comboBox_parity->currentIndex())//数据校验
            {
            case 0:mySerialPort->setParity(QSerialPort::NoParity);qDebug()<<"NoParity";break;
            case 1:mySerialPort->setParity(QSerialPort::OddParity);qDebug()<<"OddParity";break;
            case 2:mySerialPort->setParity(QSerialPort::EvenParity);qDebug()<<"EvenParity";break;
            }       //设定校验

            //设置完成

            timerReceive->start(READ_INTERVAL); //每10毫秒读一次

            ui->pushButton_connect->setText("Disconnect");

            ui->label_status->setText("ON");
            QPalette pe;
            pe.setColor(QPalette::WindowText,Qt::green);
            ui->label_status->setPalette(pe);

            //设置交互

            PlayWindow::serialOpenStatus = true;//设置状态
            timerScan->stop();//扫描停止

            timerReflesh->start(REFLASH_INTERVAL);//开始刷新
        }
        else
        {
            closeCallBack();//关闭
        }
}

/*
 * 绘图界面的初始化
 */
//void PlayWindow::InitPlotTheme()
//{
//    // set some pens, brushes and backgrounds:
//    historyPlot = ui->widget_chartView_plotHistory;
//    historyPlot->xAxis->setBasePen(QPen(Qt::white, 1));
//    historyPlot->yAxis->setBasePen(QPen(Qt::white, 1));
//    historyPlot->xAxis->setTickPen(QPen(Qt::white, 1));
//    historyPlot->yAxis->setTickPen(QPen(Qt::white, 1));
//    historyPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
//    historyPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
//    historyPlot->xAxis->setTickLabelColor(Qt::white);
//    historyPlot->yAxis->setTickLabelColor(Qt::white);
//    historyPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    historyPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    historyPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    historyPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    historyPlot->xAxis->grid()->setSubGridVisible(true);
//    historyPlot->yAxis->grid()->setSubGridVisible(true);
//    historyPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
//    historyPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
//    historyPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
//    historyPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
//    QLinearGradient plotGradient;
//    plotGradient.setStart(0, 0);
//    plotGradient.setFinalStop(0, 350);
//    plotGradient.setColorAt(0, QColor(80, 80, 80));
//    plotGradient.setColorAt(1, QColor(50, 50, 50));
//    historyPlot->setBackground(plotGradient);
//    QLinearGradient axisRectGradient;
//    axisRectGradient.setStart(0, 0);
//    axisRectGradient.setFinalStop(0, 350);
//    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
//    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
//    historyPlot->axisRect()->setBackground(axisRectGradient);
//    historyPlot->replot();

//    realtimePlot = ui->widget_chartView_plotRealTime;
//    realtimePlot->xAxis->setBasePen(QPen(Qt::white, 1));
//    realtimePlot->yAxis->setBasePen(QPen(Qt::white, 1));
//    realtimePlot->xAxis->setTickPen(QPen(Qt::white, 1));
//    realtimePlot->yAxis->setTickPen(QPen(Qt::white, 1));
//    realtimePlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
//    realtimePlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
//    realtimePlot->xAxis->setTickLabelColor(Qt::white);
//    realtimePlot->yAxis->setTickLabelColor(Qt::white);
//    realtimePlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    realtimePlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    realtimePlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    realtimePlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    realtimePlot->xAxis->grid()->setSubGridVisible(true);
//    realtimePlot->yAxis->grid()->setSubGridVisible(true);
//    realtimePlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
//    realtimePlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
//    realtimePlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
//    realtimePlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
////    QLinearGradient plotGradient;
//    plotGradient.setStart(0, 0);
//    plotGradient.setFinalStop(0, 350);
//    plotGradient.setColorAt(0, QColor(80, 80, 80));
//    plotGradient.setColorAt(1, QColor(50, 50, 50));
//    realtimePlot->setBackground(plotGradient);
////    QLinearGradient axisRectGradient;
//    axisRectGradient.setStart(0, 0);
//    axisRectGradient.setFinalStop(0, 350);
//    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
//    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
//    realtimePlot->axisRect()->setBackground(axisRectGradient);
//    realtimePlot->replot();

//    realtimeGraph = realtimePlot->addGraph();
//    historyGraph = historyPlot->addGraph();
//}


/*
 * 停止时执行，释放串口，停止定时器，设置用户交互
 */
void PlayWindow::closeCallBack()
{
    if(timerReceive->isActive())
        timerReceive->stop();

    if(timerReflesh->isActive())
        timerReflesh->stop();

    if(mySerialPort->isOpen())
        mySerialPort->close();

    //关闭串口，停止定时器

    ui->pushButton_connect->setText("Connection");

    ui->label_status->setText("OFF");
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::black);
    ui->label_status->setPalette(pe);

    ui->textEdit_serialInfo->clear();
    //设置UI

    PlayWindow::serialOpenStatus = false;
    timerScan->start(SCAN_INTERVAL);
}

/*
 * 扫描可用串口，每秒执行一次，将现有的串口列在可选列表中
 */
void PlayWindow::ScanSerialPorts()
{
    if(!PlayWindow::serialOpenStatus)
    {
        ui->comboBox_portName->clear();
        // 这里是MainWindow的构造函数，在这个地方读取可用的串口信息，跟安卓的MainActivity类似
        foreach (const QSerialPortInfo &Info, QSerialPortInfo::availablePorts())    //逐个读取串口
        {
            QSerialPort serial;
            serial.setPort(Info);

            if(serial.open(QIODevice::ReadWrite))       //如果可以以读写方式打开串口
            {
                ui->comboBox_portName->addItem(Info.portName());    //把每个可用的串口加到选择列表中
                serial.close();     //尝试打开成功，先关上，等着人为打开
            }
        }
    }
}


/*
 * 读取缓冲区数据
 * 写入rawData
 * 定时器每中断一次，读取一次
 */
void PlayWindow::ReadSerialBuffer()
{
    if(PlayWindow::serialOpenStatus)
    {

        bufferData = mySerialPort->readAll(); //读取串口数据到bufferData中

        if(!bufferData.isNull())
        {
            sampleSpeed = bufferData.length()*500/READ_INTERVAL;
            ProtocolDecode(bufferData);//协议解析
        }
    }
    else{
        closeCallBack();
    }
}

/*
 * 解析传输协议
 * 写入rawData
 */
int PlayWindow::ProtocolDecode(QByteArray array)
{
    int currentInt;
    char HighBit,LowBit;

    if(array[0]&0xC0 == 0x00)   //高2位为00
    {
        if(tailTemp == NULL){
            qDebug()<<"Missing Highbit";
            return 1;
        }
        else
            array.prepend(tailTemp);//prepend()在原字符串的开头插入另一个字符串
    }   //将备份的高位接在数组前面


    tailTemp = NULL;    //清空高位备份

    if(array[array.length()]&0xC0 == HIGH_PREFIX)   //高2位为11
    {


            tailTemp = array[array.length()];
            array.remove(array.length(),1);//删除数组最后一位
    }       //处理数组末端


    for(QByteArray::size_type index = 0; index < array.length(); index++)
    {

        char c = array[index]&0xC0;
        if(c == (char)HIGH_PREFIX)
        {
            HighBit = array[index]&0x3F;    //高位提取低6位
            if((array[index+1]&0xC0) == 0x00)
            {
                LowBit = array[index+1]&0x3F;   //低位提取低6位
                currentInt = (HighBit<<6 | LowBit)&0x0FFF;  //拼合成为12位数

                if(rawData.length() >= storeLength)
                {
                    rawData.removeFirst();
                }

                rawData.push_back(currentInt);
            }
            else{
                return 2;
            }
        }
    }
    return 0;
}

/*
 * 显示实时数据
 */
void PlayWindow::PlotRealtimeData()
{
    long plotQuantity = ui->spinBox_realtimePlotLength->text().toLong();//实时数据
    QVector<double> realtimeData;

    for(QVector<int>::size_type index = 0; index < rawData.length(); index++)
    {
        double currentData = (double)rawData.at(index);
        realtimeData.push_back(currentData);
    }

    if(plotQuantity < realtimeData.length())
        realtimeData.remove(0,realtimeData.length()-plotQuantity-1);  //裁剪显示数据

    QVector<double> x(realtimeData.length() + 1);
    for(int i = 0; i <= realtimeData.length(); i++)
        x[i] = i;

//    realtimeGraph->setData(x,realtimeData);
//    realtimeGraph->setPen(QPen(QColor(200,200,120),2));

//    realtimePlot->xAxis->setRange(0,realtimeData.length());
//    realtimePlot->yAxis->setRange(0,4096);

//    realtimePlot->replot();

}


/*
 * 清空缓存
 */
void PlayWindow::on_pushButton_clearCache_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "Warning", "Confirm clear?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
         rawData.clear();
         ui->label_samplesCount->setText("0");
         ui->progressBar_acquisitionProgress->setValue(0);
         qDebug()<<"清空缓存";
    }
}

/*
 * 刷新屏幕，更新存储深度等参数
 */
void PlayWindow::Reflesh()
{
    realtimeShowLength = ui->spinBox_realtimePlotLength->text().toLong();

    if(rawData.length()>storeLength)
        rawData.remove(0,rawData.length()-storeLength);

    float progess = (float)rawData.length() / storeLength;
    ui->progressBar_acquisitionProgress->setValue(progess*ui->progressBar_acquisitionProgress->maximum());
    ui->label_samplesCount->setText(QString("%1").arg(rawData.length()));


    ui->label_sampleSpeed->setText(QString("%1").arg(sampleSpeed));

    if(ui->checkBox_showRealtime->isChecked()){
        PlotRealtimeData();
    }
    else if(!ui->checkBox_showRealtime->isChecked()){
//        realtimeGraph->clearData();
//        realtimePlot->replot();
    }
}

void PlayWindow::on_pushButton_resetStoreLength_clicked()
{
    storeLength = ui->spinBox_storeLength->text().toLong();
}

void PlayWindow::on_toolButton_color_clicked()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("toolButton_color" == senderName) {
           ui->widget_chartView->setAutoFillBackground(true);//必须有这条语句
           ui->widget_chartView->setPalette(QPalette(color));


//           QPalette pal =lineEdit->QPalette();
//           pal->setColor(QPalette::Text,QColor(255,0,0);
//           ui->widget_chartView->setPalette(QPalette::Text,color);
//            QPalette palette;
//            palette.setColor(QPalette::Background, QColor(192,253,123,100)); // 最后一项为透明度

//            ui->widget_chartView->setPalette(palette);
//            this->setBackgroundColor(color);
//            ui->backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
//    setupForm();
    update();
}

void PlayWindow::on_add_tabWidget_clicked()
{
    ui->tabWidget_tab->addTabWidget("xxx");
    ui->widget_chartView->AddSeries();
}





