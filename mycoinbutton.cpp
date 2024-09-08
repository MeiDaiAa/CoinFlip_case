#include "mycoinbutton.h"
#include <QPixmap>
#include <QIcon>
#include <QDebug>



MyCoinButton::MyCoinButton(QString str)
{
    QPixmap pix;
    pix.load(str);
    pix = pix.scaled(pix.width() * 2, pix.height() * 2);

    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));


    time1 = new QTimer(this);
    time2 = new QTimer(this);

    connect(time1, &QTimer::timeout, [=](){
        QString str= QString(":/res/Coin000%1").arg(min++);

        QPixmap pix5;
        if(!pix5.load(str))
        {
            qDebug() << "图片加载失败：mycoinbutton";
            return;
        }
         pix5 = pix5.scaled(pix5.width() * 2, pix5.height() * 2);

         this->setFixedSize(pix5.width(), pix5.height());
         this->setStyleSheet("QPushButton{border:0px}");
         this->setIcon(pix5);
         this->setIconSize(QSize(pix5.width(), pix5.height()));

        if(this->min > this->max)
        {
            isAnimation = false;
            this->min = 1;
            time1->stop();
        }
    });
    connect(time2, &QTimer::timeout, [=](){
        QString str = QString(":/res/Coin000%8").arg(max--);

        QPixmap pix5;
       if(!pix5.load(str))
       {
           qDebug() << "图片加载失败：mycoinbutton";
           return;
       }
        pix5 = pix5.scaled(pix5.width() * 2, pix5.height() * 2);

        this->setFixedSize(pix5.width(), pix5.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix5);
        this->setIconSize(QSize(pix5.width(), pix5.height()));

        if(this->max < this->min)
        {
            isAnimation = false;
            this->max = 8;
            time2->stop();
        }
    });

}

void MyCoinButton::changeFlag()
{
    if(this->flag) //如果是正面，执行下列代码
    {
        this->isAnimation = true;
        time1->start(30);
        this->flag = false;
        qDebug() <<"changeflag:" <<  this->flag;
    }
    else //反面执行下列代码
    {
        this->isAnimation = true;
        time2->start(30);
        this->flag = true;
        qDebug() <<"changeflag:" << this->flag;
    }
}


//在动画期间鼠标点击不响应
void MyCoinButton::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation == true || this->isWin == true)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}

