#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class LevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelScene(QWidget *parent = 0);
        //设置背景界面
    void paintEvent(QPaintEvent *);

    PlayScene *playScene;

signals:
    void sceneBack();

public slots:
};

#endif // LEVELSCENE_H
