#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QPainter>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = 0);

    //自己写构造函数
    MyPushButton(QString normalImg, QString pressImg = "");

    //自己写按键的动画特效
    void zoom1();

    QString normalImage;
    QString pressImage;
    QPixmap pix3;
    QPainter painter();

    //制作鼠标按下和松开的两种不同图片
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
