#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    ///////这是修改之后的代码////////////////////
///newBranch
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
