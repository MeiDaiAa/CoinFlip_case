#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QPixmap>
#include <mypushbutton.h>
#include "levelscene.h"
#include <QTimer>
#include <QSound>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置主界面的基本信息
    this->resize(640, 1176);
    this->setFixedSize(640, 1176);
    this->setWindowTitle("翻金币");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //准备音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav", this);
    QSound *backMusic = new QSound(":/res/Leval_Polkka_01.wav", this);
    backMusic->setLoops(-1);
    backMusic->play();

    QTimer timer(this);

    //开始菜单栏退出选项链接
    connect(ui->actionQuit, &QAction::triggered, [=](){this->close();});

    //创建主界面的开始按键
    MyPushButton *start_btn = new MyPushButton(":/res/MenuSceneStartButton.png");
    //将开始按键设置在主界面中
    start_btn->setParent(this);
    start_btn->move((this->width() - start_btn->width()) / 2, this->height() * 0.55);

    //将按键绑定动画
    connect(start_btn, &MyPushButton::clicked, [=](){start_btn->zoom1();});

    //创建难度选择界面
    LevelScene *levelScene = new LevelScene;

    //将开始按键与难度选择界面绑定
    connect(start_btn, &MyPushButton::clicked, [=](){
        startSound->play();
        //设置延时执行，让动画更流畅
        QTimer::singleShot(270,this, [=](){
            this->hide();
            levelScene->setGeometry(this->geometry());
            levelScene->show();
        });
    });

    //接收选关卡的返回信号
    connect(levelScene, &LevelScene::sceneBack, [=](){
        this->setGeometry(levelScene->geometry());
        this->show();
    });

}

//用绘图事件画出主界面的背景
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/res/MenuSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);

    pixmap.load(":/res/Title.png");
    painter.drawPixmap(20,40, pixmap.width(), pixmap.height(), pixmap);
}




















MainWindow::~MainWindow()
{
    delete ui;
}
