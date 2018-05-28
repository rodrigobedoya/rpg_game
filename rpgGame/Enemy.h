#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Player.h"

class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy();
public slots:
    void move();
    void animate();
private:
    int animationColumn;
    int animationRow;
    int speed;
};

#endif // ENEMY_H
