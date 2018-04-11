#ifndef BASETABBAR_H
#define BASETABBAR_H
#include <QTabBar>

class BaseTabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit BaseTabBar(QWidget *parent=0);
    ~BaseTabBar();
    QSize tabSizeHint(int index) const;
    void setTabWidth(int value);
    void setTabHeight(int value);

private:
    int height;

};

#endif // BASETABBAR_H
