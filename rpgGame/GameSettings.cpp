#include "GameSettings.h"

GameSettings::GameSettings():
    eStartingAnimationRow(0),
    eStartingAnimationColumn(1),
    eBaseMap(":/Sprites/enemyTest.png"),
    eBaseMapTotalColumns(3),
    eBaseMapTotalRows(4),
    eWidth(140),
    eHeight(130),
    eSpeed1(4),
    eSpeed2(2),
    ePixmap(":/Sprites/enemyTest.png"),

    xStartingExperiencePoints(0),
    xColor(Qt::blue),
    xFont(QFont("courier",18)),

    hStartingHealthPoints(10),
    hColor(Qt::green),
    hFont(QFont("courier",18)),

    scPosition(0,0),
    scWidth(800),
    scHeight(600),
    bckgroundImage(":/Sprites/backgroundTest.png"),
    eSpawnTimer(2500),

    raBaseMap(":/Sprites/fireballTest.png"),
    raWidth(80),
    raHeight(40),
    raStartingAnimationColumn(0),
    raStartingAnimationRow(3),
    raSpeed(10),
    raPixmap(":/Sprites/fireballTest.png")
/*
    leftKey(Qt::Key_A),
    upKey(Qt::Key_W),
    rightKey(Qt::Key_D),
    downKey(Qt::Key_S),
    shootKey(Qt::Key_J),
    attackKey(Qt::Key_K)*/
{
    ePixmap = eBaseMap.copy(eBaseMap.width()/eBaseMapTotalColumns*eStartingAnimationColumn,eBaseMap.height()/eBaseMapTotalRows*eStartingAnimationRow,eBaseMap.width()/eBaseMapTotalColumns,eBaseMap.height()/eBaseMapTotalRows);
    bckgroundImage = bckgroundImage.scaled(scWidth, scHeight,Qt::IgnoreAspectRatio);
}

int GameSettings::enemyStartingAnimationRow(){return eStartingAnimationRow;}
int GameSettings::enemyStartingAnimationColumn(){return eStartingAnimationColumn;}
QPixmap GameSettings::enemyBaseMap(){return eBaseMap;}
int GameSettings::enemyBaseMapTotalColumns(){return eBaseMapTotalColumns;}
int GameSettings::enemyBaseMapTotalRows(){return eBaseMapTotalRows;}
int GameSettings::enemyWidth(){return eWidth;}
int GameSettings::enemyHeight(){return eHeight;}
int GameSettings::enemySpeed1(){return eSpeed1;}
int GameSettings::enemySpeed2(){return eSpeed2;}
QPixmap GameSettings::enemyPixmap(){return ePixmap;}

int GameSettings::xpStartingExperiencePoints(){return xStartingExperiencePoints;}
QColor GameSettings::xpColor(){return xColor;}
QFont GameSettings::xpFont(){return xFont;}

int GameSettings::hpStartingHealthPoints(){return hStartingHealthPoints;}
QColor GameSettings::hpColor(){return hColor;}
QFont GameSettings::hpFont(){return hFont;}

QPoint GameSettings::scenePosition(){return scPosition;}
int GameSettings::sceneWidth(){return scWidth;}
int GameSettings::sceneHeight(){return scHeight;}
QImage GameSettings::backgroundImage(){return bckgroundImage;}
int GameSettings::enemySpawnTimer(){return eSpawnTimer;}

QPixmap GameSettings::rangedAttackBaseMap(){return raBaseMap;}
int GameSettings::rangedAttackWidth(){return raWidth;}
int GameSettings::rangedAttackHeight(){return raHeight;}
int GameSettings::rangedAttackStartingAnimationColumn(){return raStartingAnimationColumn;}
int GameSettings::rangedAttackStartingAnimationRow(){return raStartingAnimationRow;}
int GameSettings::rangedAttackSpeed(){return raSpeed;}
