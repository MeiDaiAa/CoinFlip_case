#include "mypushbutton.h"
#include <QPixmap>
#include <QIcon>
#include <QDebug>
#include <QPropertyAnimation>//动画效果头文件
#include <QPainter>

//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent){}
//自己写构造函数
MyPushButton::MyPushButton(QString normalImg, QString pressImg/* = ""*/)//初始化变量在声明和实现中只能有一次！！
{
    this->normalImage = normalImg;
    this->pressImage = pressImg;

    QPixmap pix1;
    bool ret;
    ret = pix1.load(this->normalImage);
    if(!ret)
    {
        qDebug() << "图片加载出错：mypushbutton";
    }

    //将pixmap 图片等比例放大
    pix1 = pix1.scaled(pix1.width() * 2, pix1.height() * 2);

    //设置图片的固定尺寸
    this->setFixedSize(pix1.width(), pix1.height());
    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix1);
    //设置图标大小
    this->setIconSize(QSize(pix1.width(), pix1.height()));
}

//自己写按键的动画特效
void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    //创建动画的持续时间
    animation->setDuration(200);
    //设置动画的起始位置
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    //设置动画的结束位置
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置动画的运动方式
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画QAbstractAnimation::DeleteWhenStopped 代表动画执行结束之后直接删除动画对象
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

//制作鼠标按下和松开的两种不同图片
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImage != "")
    {

        if(!this->pix3.load(this->pressImage))
        {
            qDebug() << "加载图片失败：mypushbotton";
        }

        pix3 = pix3.scaled(pix3.width() * 2, pix3.height() * 2);

        this->setFixedSize(this->width(), this->height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix3);
        this->setIconSize(QSize(pix3.width(), pix3.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImage != "")
    {

        if(!this->pix3.load(this->normalImage))
        {
            qDebug() << "加载图片失败：mypushbotton";
        }

        pix3 = pix3.scaled(pix3.width() * 2, pix3.height() * 2);

        this->setFixedSize(this->width(), this->height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix3);
        this->setIconSize(QSize(pix3.width(), pix3.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}

















