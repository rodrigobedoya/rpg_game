#-------------------------------------------------
#
# Project created by QtCreator 2018-04-29T04:30:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rpgGame
TEMPLATE = app


SOURCES += main.cpp \
    Player.cpp \
    Enemy.cpp \
    Game.cpp \
    ExperiencePoints.cpp \
    RangedAttack.cpp \
    Health.cpp \
    GameSettings.cpp

HEADERS  += \
    Player.h \
    Enemy.h \
    Game.h \
    ExperiencePoints.h \
    RangedAttack.h \
    Health.h \
    GameSettings.h

RESOURCES += \
    Resources.qrc
