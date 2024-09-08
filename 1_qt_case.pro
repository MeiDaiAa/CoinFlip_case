#-------------------------------------------------
#
# Project created by QtCreator 2024-09-06T13:15:36
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 1_qt_case
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mypushbutton.cpp \
    levelscene.cpp \
    playscene.cpp \
    mycoinbutton.cpp \
    dataconfig.cpp

HEADERS  += mainwindow.h \
    mypushbutton.h \
    levelscene.h \
    playscene.h \
    mycoinbutton.h \
    dataconfig.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    res/BackButtonSound.wav \
    res/ConFlipSound.wav \
    res/LevelWinSound.wav \
    res/TapButtonSound.wav \
    res/BackButton.png \
    res/BackButtonSelected.png \
    res/BoardNode.png \
    res/Coin0001.png \
    res/Coin0002.png \
    res/Coin0003.png \
    res/Coin0004.png \
    res/Coin0005.png \
    res/Coin0006.png \
    res/Coin0007.png \
    res/Coin0008.png \
    res/LevelCompletedDialogBg.png \
    res/LevelIcon.png \
    res/MenuSceneBg.png \
    res/MenuSceneStartButton.png \
    res/OtherSceneBg.png \
    res/PlayLevelSceneBg.png \
    res/Title.png
