#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include "Game.h"
#include <QList>
#include "GameSettings.h"

extern Game * NameInProgress;
extern GameSettings * Settings;

Enemy::Enemy():
    QObject(),
    QGraphicsPixmapItem(),
    animationColumn(Settings->enemyStartingAnimationColumn()),
    animationRow(Settings->enemyStartingAnimationRow()),
    speed(Settings->enemySpeed1())
{
    setPixmap(Settings->enemyPixmap());

    int random_number = rand() % 500;
    setPos(NameInProgress->scene->width(),random_number);

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);

    QTimer * animationTimer = new QTimer();
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(animate()));
    animationTimer->start(500);
}

void Enemy::move()
{
    if(collidesWithItem(NameInProgress->player))
    {
        NameInProgress->HP->decrease();
        delete this;
        return;
    }
    setPos(x()-speed,y());
    if(pos().x() + pixmap().width() < 0){
        scene()->removeItem(this);
        delete this;
    }
}

void Enemy::animate()
{
    if(animationColumn == 2){
        animationColumn = 1;
        speed=Settings->enemySpeed1();
    }
    else{
        speed=Settings->enemySpeed2();
        animationColumn++;
    }

    QPixmap currentImage = Settings->enemyBaseMap().copy(Settings->enemyBaseMap().width()/Settings->enemyBaseMapTotalColumns()*animationColumn,Settings->enemyBaseMap().height()/Settings->enemyBaseMapTotalRows()*animationRow,Settings->enemyBaseMap().width()/Settings->enemyBaseMapTotalColumns(),Settings->enemyBaseMap().height()/Settings->enemyBaseMapTotalRows());
    currentImage = currentImage.scaled(Settings->enemyWidth(),Settings->enemyHeight(),Qt::IgnoreAspectRatio);
    setPixmap(currentImage);
}
