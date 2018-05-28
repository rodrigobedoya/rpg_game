#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include <QGraphicsPixmapItem>
#include <QFont>
#include <QColor>
#include <QImage>
#include <QKeyEvent>

class GameSettings
{
public:
    GameSettings();

    int enemyStartingAnimationRow();
    int enemyStartingAnimationColumn();
    QPixmap enemyBaseMap();
    int enemyBaseMapTotalColumns();
    int enemyBaseMapTotalRows();
    int enemyWidth();
    int enemyHeight();
    int enemySpeed1();
    int enemySpeed2();
    QPixmap enemyPixmap();

    int xpStartingExperiencePoints();
    QColor xpColor();
    QFont xpFont();

    int hpStartingHealthPoints();
    QColor hpColor();
    QFont hpFont();

    QPoint scenePosition();
    int sceneWidth();
    int sceneHeight();
    QImage backgroundImage();
    int enemySpawnTimer();

    QPixmap rangedAttackBaseMap();
    int rangedAttackWidth();
    int rangedAttackHeight();
    int rangedAttackStartingAnimationColumn();
    int rangedAttackStartingAnimationRow();
    int rangedAttackSpeed();
    QPixmap rangedAttackPixmap();
private:
    int eStartingAnimationRow;
    int eStartingAnimationColumn;
    QPixmap eBaseMap;
    int eBaseMapTotalColumns;
    int eBaseMapTotalRows;
    int eWidth;
    int eHeight;
    int eSpeed1;
    int eSpeed2;
    QPixmap ePixmap;

    int xStartingExperiencePoints;
    QColor xColor;
    QFont xFont;

    int hStartingHealthPoints;
    QColor hColor;
    QFont hFont;

    QPoint scPosition;
    int scWidth;
    int scHeight;
    QImage bckgroundImage;
    int eSpawnTimer;

    QPixmap raBaseMap;
    int raWidth;
    int raHeight;
    int raStartingAnimationColumn;
    int raStartingAnimationRow;
    int raSpeed;
    QPixmap raPixmap;
/*
    QKeyEvent leftKey;
    QKeyEvent upKey;
    QKeyEvent rightKey;
    QKeyEvent downKey;
    QKeyEvent shootKey;
    QKeyEvent attackKey;
    //QKeyEvent runKey;


    /*
    int pSpeed;
    QPixmap pBaseMap;
    QPixmap pSecondMap;
    int pBaseMapTotalColumns;
    int pBaseMaptTotalRows;
    int pBaseMapUsedColumns;
    int pBaseMapUsedRows;
    int pWidth;
    int pHeight;
    int pStartingAnimationRow;
    int pStartingAnimationColumn;
    QPoint pStartingPosition;
    int pStartingRangedAttackAnimationRow;
    int pStartingRangedAttackAnimationColumn;
    int pStartingMeleeAtackAnimationRow;
    int pStartingMeleeAtackAnimationColumn;
    int pRangedAttackDurationTimer;
    int pRangedAttackAnimationTimer;
    int pMovementAnimationTimer;
    int pCheckMovement;
    int pMeleeAttackAnimationTimer;
    int pMeleeAttackDurationTimer;
    int pStartingFacingDirection;*/
};

#endif // GAMESETTINGS_H
