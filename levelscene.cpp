#include "levelscene.h"
#include <QMenuBar>
#include <QPixmap>
#include <QPainter>
#include "mypushbutton.h"
#include <QMouseEvent>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QSound>

LevelScene::LevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置主界面的基本信息
    this->resize(640, 1176);
    this->setFixedSize(640, 1176);
    this->setWindowTitle("翻金币");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //准备音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav", this);
    QSound *backSound = new QSound(":/res/BackButtonSound.wav", this);

    //添加菜单栏选项
    QMenuBar *bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu *startMenu = bar->addMenu("开始");
    QAction *quitAct = startMenu->addAction("退出");

    //链接退出选项
    connect(quitAct, &QAction::triggered, [=](){this->close();});

    //设置返回按钮
    MyPushButton *back_btn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    back_btn->setParent(this);
    back_btn->move(this->width() - back_btn->width() - 20, this->height() * 0.75);
    //链接返回按钮
    connect(back_btn, &MyPushButton::clicked, [=](){
        backSound->play();
        QTimer::singleShot(200, this, [=](){
            this->hide();
            emit sceneBack();
        });
    });


    playScene = NULL;
    for(int i = 0; i < 20; i++)
    {
        //设置每个关卡按钮
        MyPushButton *level = new MyPushButton(":/res/LevelIcon.png");
        level->setParent(this);
        level->move(55 + (i %4) * 140, 210 +(i / 4) * 140);

        //设置关卡数字
        QLabel *label = new QLabel(QString().number(i + 1));
        label->setParent(this);
        /////////////////////////重要//////
        label->setFixedSize(level->width(), level->height());
        //设置字体水平垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setFont(QFont("华文琥珀", 20));
        label->move(55 + (i %4) * 140, 210 +(i / 4) * 140);
        //设置鼠标事件穿透label
        label->setAttribute(Qt::WA_TransparentForMouseEvents);


        //链接游戏界面和按钮
        connect(level, &MyPushButton::clicked, [=](){
            chooseSound->play();
            this->playScene = new PlayScene(i + 1);
            this->playScene->setGeometry(this->geometry());
            this->hide();
            this->playScene->show();
//////////////////////监听信号必须在connect的里面 否者下面的监听的playsecec是指向空的/////////////
            connect(this->playScene, &PlayScene::chooseSceneBack, [=](){
                this->setGeometry(this->playScene->geometry());
                delete this->playScene;
                this->playScene = NULL;
                this->show();
            });
        });
    }


}

//设置背景界面
void LevelScene::paintEvent(QPaintEvent *)
{
    QPixmap pix2;
    pix2.load(":/res/LevelSceneBg.png");

    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix2);

    pix2.load(":/res/Title.png");
    pix2 = pix2.scaled(pix2.width() * 2, pix2.height() * 2);

    painter.drawPixmap(this->width() / 2 - pix2.width() / 2, 30, pix2.width(), pix2.height(), pix2);

}





