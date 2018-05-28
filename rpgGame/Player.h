#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPoint>
#include <QTimer>

class Player: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Player();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    bool key_MoveLeft_Pressed;
    bool key_MoveUp_Pressed;
    bool key_MoveRight_Pressed;
    bool key_MoveDown_Pressed;
    bool key_Shoot_Pressed;
    bool key_Attack_Pressed;

    bool movementKeyPressed;

    int facingDirection;
    int normalSpeed;
    int speed;
    int runningSpeed;
    bool running;
    QPixmap baseMap;
    QPixmap secondMap;
    int width;
    int height;
    int animationRow;
    int animationColumn;
    QPoint oldPosition;
    QPoint newPosition;
    bool moving;
    bool attacking;
    int rangedAttackAnimationRow;
    int rangedAttackAnimationColumn;
    QTimer * rangedAttackDuration;
    QTimer * rangedAttackAnimationTimer;

    int meleeAttackAnimationRow;
    int meleeAttackAnimationColumn;
    QTimer * meleeAttackDuration;
    QTimer * meleeAttackAnimationTimer;

    QTimer * checkKeyPressedTimer;

public slots:
    void spawn();
    void animate();
    void checkMovement();
    void limitPlayerMovement();
    void rangedAttackAnimation();
    void limitMeleePlayerMovement();
    void meleeAttackAnimation();
    void keyPressedEvents();
};

#endif // PLAYER_H

