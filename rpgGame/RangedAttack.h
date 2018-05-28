#ifndef RANGEDATTACK_H
#define RANGEDATTACK_H
#include <QGraphicsPixmapItem>
#include <QObject>

class RangedAttack: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    RangedAttack();
    void setDirection(int newDirection);
public slots:
    void move();
    void animate();
private:
    int direction;
    int speed;

    QPixmap baseMap;
    int width;
    int height;
    int animationRow;
    int animationColumn;

    int counterToMove;
    bool ableToMove;

    QPixmap explosionMap;

};

#endif // RANGEDATTACK_H
