#ifndef MYCOINBUTTON_H
#define MYCOINBUTTON_H

#include <QPushButton>
#include <QTimer>

class MyCoinButton : public QPushButton
{
    Q_OBJECT
public:
    MyCoinButton(QString str);


    int posX;
    int posY;
    bool flag;

    int min = 1;
    int max = 8;

    //翻转动画计时器
    QTimer *time1;
    QTimer *time2;
    void changeFlag();

    bool isAnimation = false;
    bool isWin = false;


    void mousePressEvent(QMouseEvent *e);


signals:

public slots:
};

#endif // MYCOINBUTTON_H
