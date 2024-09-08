#include "playscene.h"
#include <QMenuBar>
#include <QPixmap>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "dataconfig.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int level/*QWidget *parent*/)  /*:(parent)*/
{
    this->gameLevel = level;
    //设置主界面的基本信息
    this->resize(640, 1176);
    this->setFixedSize(640, 1176);
    this->setWindowTitle("翻金币");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    QSound *backSound = new QSound(":/res/BackButtonSound.wav", this);
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav");
    QSound *winSound = new QSound(":/res/LevelWinSound.wav");

    //设置成功图片
    QPixmap pix6;
    if(!pix6.load(":/res/LevelCompletedDialogBg.png"))
    {
        qDebug() << "图片加载出错:pix6";
    }
    pix6 = pix6.scaled(pix6.width() * 2, pix6.height() * 2);
    QLabel *success = new QLabel;
    success->setParent(this);
    success->setFixedSize(pix6.width(), pix6.height());
    success->setPixmap(pix6);
    success->move(this->width() / 2 - pix6.width() / 2, -pix6.height());


    //设置关卡难度显示
    QLabel *label3 = new QLabel;
    label3->setParent(this);
    label3->setFont(QFont("Algerian", 30));
    QString str = QString("LEVEL %1").arg(this->gameLevel);
    label3->move(0, 100);
    label3->setText(str);

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
            emit this->chooseSceneBack();
        });
    });


    dataConfig config;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->gameArray[i][j] = config.mData[this->gameLevel][i][j];
        }
    }


    //////////////////////////////////设置游戏主界面//////////////////////////////////
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //设置金币的背景
            MyPushButton *coinBg = new MyPushButton(":/res/BoardNode.png");
            coinBg->setParent(this);
            coinBg->move(120 + i*100,400+j*100);

            //////////////////////初始化金币///////////////////

            QString img;
            if(this->gameArray[i][j] == 1)
            {
                img = ":/res/Coin0001.png";
            }
            else
            {
                img = ":/res/Coin0008.png";
            }

            MyCoinButton *coin = new MyCoinButton(img);
            coin->setParent(this);
            coin->move(123 + i*100,406+j*100);
            coin->posX = i;
            coin->posY = j;
            coin->flag = gameArray[i][j];

            this->coinbtn[i][j] = coin;

            ///翻金币
            connect(coin, &MyCoinButton::clicked, [=](){
                flipSound->play();
                for(int j = 0; j < 4; j++)
                {
                    for(int k = 0; k < 4; k++)
                    {
                        coinbtn[j][k]->isWin = true;
                    }
                }

                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 1 ? 0 : 1;
                qDebug() << "flag" << this->coinbtn[i][j]->flag;


                QTimer::singleShot(100, this, [=](){
                    if(coin->posX + 1 <= 3)
                    {
                        coinbtn[coin->posX + 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX + 1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] == 1 ? 0 : 1;
                    }
                    if(coin->posX - 1 >= 0)
                    {
                        coinbtn[coin->posX - 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY]  == 1 ? 0 : 1;
                    }
                    if(coin->posY+ 1 <= 3 )
                    {
                        coinbtn[coin->posX][coin->posY + 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY + 1] = this->gameArray[coin->posX][coin->posY + 1] == 1 ? 0 : 1;
                    }
                    if(coin->posY - 1 >= 0)
                    {
                        coinbtn[coin->posX][coin->posY - 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY - 1] =  this->gameArray[coin->posX][coin->posY - 1] == 1 ? 0 : 1;
                    }

                    for(int j = 0; j < 4; j++)
                    {
                        for(int k = 0; k < 4; k++)
                        {
                            coinbtn[j][k]->isWin = false;
                        }
                    }

                    this->isWin = true;
                    for(int j = 0; j < 4; j++)
                    {
                        for(int k = 0; k < 4; k++)
                        {
                            if(coinbtn[j][k]->flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true)
                    {
                        qDebug() << "win";
                        for(int j = 0; j < 4; j++)
                        {
                            for(int k = 0; k < 4; k++)
                            {
                                coinbtn[j][k]->isWin = true;
                            }
                        }
                        winSound->play();
                        QPropertyAnimation *animation = new QPropertyAnimation(success, "geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(success->x(), success->y(), success->width(), success->height()));
                        animation->setEndValue(QRect(success->x(), this->height() * 0.1, success->width(), success->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });
            });

        }
    }






}














//设置背景界面
void PlayScene::paintEvent(QPaintEvent *)
{
    QPixmap pix2;
    pix2.load(":/res/LevelSceneBg.png");

    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix2);

    pix2.load(":/res/Title.png");
    pix2 = pix2.scaled(pix2.width() * 2, pix2.height() * 2);

    painter.drawPixmap(this->width() / 2 - pix2.width() / 2, 30, pix2.width(), pix2.height(), pix2);

    pix2.load(":/res/LevelCompletedDialogBg.png");
    pix2 = pix2.scaled(pix2.width() * 2, pix2.height() * 2);
    painter.drawPixmap(this->width()/ 2 - pix2.width() / 2, -pix2.width(), pix2.width(), pix2.height(), pix2);

}
