#include "TabBar/BaseTabBar.h"
#include <QtDebug>
BaseTabBar::BaseTabBar(QWidget *parent)
    :QTabBar(parent)
    ,height(35)
{

}
BaseTabBar::~BaseTabBar()
{

}
QSize BaseTabBar::tabSizeHint(int index) const
{
    if(index != count()-1)//标签页索引0开始
    {

       return QSize(width()/count(), height);
    }
    else
    {
       return QSize(width() - width()/count() * (count()-1), height );
    }
}
void BaseTabBar::setTabWidth(int value)
{
     setFixedWidth(value - 2);//限定窗体的宽度
}
void BaseTabBar::setTabHeight(int value)
{
    height = value;//限定窗体的高度
//    qDebug()<<"value22"<<value;
}

