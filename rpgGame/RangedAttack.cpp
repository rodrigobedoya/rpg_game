#include "RangedAttack.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include <typeinfo>
#include "Game.h"d
#include "GameSettings.h"

extern Game * NameInProgress;
extern GameSettings * Settings;

RangedAttack::RangedAttack():
    QObject(),
    QGraphicsPixmapItem(),
    speed(10),
    animationColumn(Settings->rangedAttackStartingAnimationColumn()),
    animationRow(Settings->rangedAttackStartingAnimationRow()),
    baseMap(":/Sprites/fireballTest.png"),
    counterToMove(0),
    ableToMove(false),
    explosionMap(":/Sprites/Breath.png")
{
    QPixmap Pixmap = baseMap.copy(baseMap.width()/4*animationColumn,baseMap.height()/4*animationRow,baseMap.width()/4,baseMap.height()/4);
    setPixmap(Pixmap);

    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);

    QTimer * animationTimer = new QTimer();
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(animate()));
    animationTimer->start(80);
}

void RangedAttack::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0; i < colliding_items.size();i++)
    {
        if(typeid(*(colliding_items[i])) == typeid(Enemy))
        {
            NameInProgress->XP->increase();

            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            delete colliding_items[i];
            delete this;
            return;
        }
    }

    if(!ableToMove)
    {
        counterToMove++;
    }
    if(counterToMove==10)
    {
        ableToMove = true;
    }
    if(ableToMove)
    {
        switch(direction)
        {
            case 0:
                setPos(x()-speed,y());
                if(pos().x() + pixmap().width() < 0){
                    scene()->removeItem(this);
                    delete this;
                }
                break;
            case 1:
                setPos(x(),y()-speed);
                if(pos().y() + pixmap().height() < 0){
                    scene()->removeItem(this);
                    delete this;
                }
                break;
            case 2:
                setPos(x()+speed,y());
                if(pos().x() - pixmap().height() > scene()->width()){
                    scene()->removeItem(this);
                    delete this;
                }
                break;
            case 3:
                setPos(x(),y()+speed);
                if(pos().y() + pixmap().height() > scene()->height()){
                    scene()->removeItem(this);
                    delete this;
                }
                break;
        }
    }
}

void RangedAttack::setDirection(int newDirection)
{
    direction = newDirection;
    switch(direction)
    {
        case(0):
            setRotation(180);
            break;
        case(2):
            setRotation(0);
            break;
        case(1):
            setRotation(270);
            break;
        case(3):
            setRotation(90);
    }
}

void RangedAttack::animate()
{

    if(animationColumn == 3)
    {
        animationColumn = 0;
        if(animationRow == 3)
        {
            animationRow = 0;
        }
        else{
            animationRow++;
        }
    }
    else{
        animationColumn++;
    }

    QPixmap currentImage = baseMap.copy(baseMap.width()/4*animationColumn,baseMap.height()/4*animationRow,baseMap.width()/4,baseMap.height()/4);
    setPixmap(currentImage);
}
