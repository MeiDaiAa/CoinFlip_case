#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoinbutton.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    /*explicit*/ PlayScene(/*QWidget *parent = 0*/int level);

    //设置背景界面
void paintEvent(QPaintEvent *);

MyCoinButton *coinbtn[4][4];

//记录当前关卡的二维数组
    int gameArray[4][4];

    bool isWin = false;


int gameLevel;

signals:
    void chooseSceneBack();
public slots:
};

#endif // PLAYSCENE_H
