#ifndef BASETABWIDGET_H
#define BASETABWIDGET_H
#include <QTabWidget>
#include "TabBar/BaseTabBar.h"
class BaseTabWidget : public QTabWidget
{
    Q_OBJECT


public:
    enum animation_Direction
    {
        animationTop,
        animationRight,
        animationBottom,
        animationLeft,
        animationTopLeft,
        animationTopRight,
        animationBottomRight,
        animationBottomLeft,
        animationCenter
    };
    BaseTabWidget(QWidget* =0);
    ~BaseTabWidget();

    void resizeEvent(QResizeEvent *);
    void setTabBarHeight(int value);
    void addTabWidget(QString text);
    int countNow();
private slots:
    void deleteWidget(int index);
    void switchScreen(int index);

private:
    void cloudAntimation(animation_Direction direction);

private:
    QPixmap pixmap;
    int preindex;
    int index_;
    BaseTabBar *bar;
};

#endif // BASETABWIDGET_H
