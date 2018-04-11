#include "parameter_configform.h"
#include "ui_parameter_configform.h"

Parameter_configForm::Parameter_configForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Parameter_configForm)
{
    ui->setupUi(this);
    Parameter_config_data();

}

Parameter_configForm::~Parameter_configForm()
{

    delete ui;
}
void Parameter_configForm::Parameter_config_data()
{

    QStringList header;
    header<<"参数"<<"数据";
    ui->tableWidget_parameter_list->setHorizontalHeaderLabels(header);

    ui->tableWidget_parameter_list->setRowCount(10); //设置行数为10
    ui->tableWidget_parameter_list->setColumnCount(2); //设置列数为2
    ui->tableWidget_parameter_list->setColumnWidth(0, 10);//第一列宽度
    ui->tableWidget_parameter_list->setColumnWidth(1, 10);
    ui->tableWidget_parameter_list->verticalHeader()->setDefaultSectionSize(25);//设置行高
    ui->tableWidget_parameter_list->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选择行为时每次选择一行
    ui->tableWidget_parameter_list->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->tableWidget_parameter_list->setSelectionMode(QAbstractItemView::SingleSelection);//不可多选
    ui->tableWidget_parameter_list->setAlternatingRowColors(true);//隔行变色
    ui->tableWidget_parameter_list->verticalHeader()->setVisible(false);//设置垂直头不可见
    ui->tableWidget_parameter_list->horizontalHeader()->setStretchLastSection(true);/*设置表格是否充满，即行末不留空*/

}

void Parameter_configForm::on_pushButton_enable_status_clicked()
{

   if(value_==1)
   {
       ui->lineEdit_enable_status->setText(("Enabled"));
       ui->lineEdit_enable_status->setEnabled(false);
   }
   if(value_==0)
   {
      ui->lineEdit_enable_status->setText("Disabled");
      ui->lineEdit_enable_status->setEnabled(false);
   }


  init_command_config();

}

QMap<BYTE, QVariant> Parameter_configForm::getVariantMap() const
{
    return VariantMap;
}

void Parameter_configForm::setVariantMap(const QMap<BYTE, QVariant> &value)
{
    VariantMap = value;
}
int  Parameter_configForm::getdata(int value)
{
    value_=value;
    qDebug()<<value_<<"value";
    return value;
}

void Parameter_configForm::init_command_config()
{
     for(int i=0;i<VariantMap.size();i++)
     {
         ui->tableWidget_parameter_list->setItem(1,0,new QTableWidgetItem(QString(tr("%1").arg("cccc"))));
         ui->tableWidget_parameter_list->setItem(2,0,new QTableWidgetItem(QString(tr("%1").arg("cccc"))));


    }

}
