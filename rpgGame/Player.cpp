#include <QKeyEvent>
#include "RangedAttack.h"
#include <QGraphicsScene>
#include <QTimer>
#include "Enemy.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QBrush>

Player::Player():
    //movement booleans
    key_MoveLeft_Pressed(false),
    key_MoveUp_Pressed(false),
    key_MoveRight_Pressed(false),
    key_MoveDown_Pressed(false),
    key_Shoot_Pressed(false),
    key_Attack_Pressed(false),
    movementKeyPressed(false),

    //player settings
    facingDirection(3),
    normalSpeed(2),
    speed(normalSpeed),
    runningSpeed(3),
    running(false),
    baseMap(":/Sprites/playerSprites.png"),
    animationRow(10),
    animationColumn(0),
    width(65),
    height(80),
    secondMap(baseMap),

    //position control
    oldPosition(0,0),
    newPosition(0,0),

    //key functions booleans
    moving(false),
    attacking(false),

    //starting sprites' values for ranged and melee attack animations
    rangedAttackAnimationColumn(0),
    rangedAttackAnimationRow(2),
    meleeAttackAnimationColumn(0),
    meleeAttackAnimationRow(14)
{
    //SET PLAYER PIXMAP
    secondMap = baseMap.copy(0,0,baseMap.width()-baseMap.width()/13,baseMap.height()-baseMap.height()/21);
    QPixmap map = secondMap.copy(secondMap.width()/12*animationColumn,secondMap.height()/20*animationRow,secondMap.width()/12,secondMap.height()/20);
    //the two QPixmap statements above are basically the same as the one below, but since it divides by prime numbers
    // 13 and 21 there's always a small quantity that is left behind in the division, causing the cropped images to split
    setPixmap(map);

    //MOVEMENT ANIMATION
    //set movement animation timer
    QTimer * animationTimer = new QTimer();
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(animate())); //connect to animate slot function
    animationTimer->start(100); //set time between each sprite during animation

    //CHECK IF CHARACTER IS MOVING
    //set timer for checking if character is moving
    QTimer * checkMovementTimer = new QTimer();
    connect(checkMovementTimer,SIGNAL(timeout()),this,SLOT(checkMovement())); //connect to checkMovement slot function
    checkMovementTimer->start(50); //check every n mlliseconds

    //RANGED ATTACK ANIMATION
    //set duration of ranged attack
    rangedAttackDuration = new QTimer;
    connect(rangedAttackDuration,SIGNAL(timeout()),this,SLOT(limitPlayerMovement())); //connect to slot function
    //set timer for time between sprite change in animation
    rangedAttackAnimationTimer = new QTimer;
    connect(rangedAttackAnimationTimer,SIGNAL(timeout()),this,SLOT(rangedAttackAnimation())); //connect to slot function

    //MELEE ATTACK ANIMATION
    meleeAttackDuration = new QTimer;
    connect(meleeAttackDuration,SIGNAL(timeout()),this,SLOT(limitMeleePlayerMovement())); //connect to slot function
    meleeAttackAnimationTimer = new QTimer;
    connect(meleeAttackAnimationTimer,SIGNAL(timeout()),this,SLOT(meleeAttackAnimation())); //connect to slot function

    //CHECK IF MOVEMENT KEY IS PRESSED
    //set timer
    checkKeyPressedTimer = new QTimer;
    connect(checkKeyPressedTimer,SIGNAL(timeout()),this,SLOT(keyPressedEvents())); //connect to slot function
    checkKeyPressedTimer->start(20); //check every n miliseconds
}

//CHECK IF A KEY IS PRESSED

void Player::keyPressEvent(QKeyEvent *event)
{
    //when a player is attacking, halt any new keyboard input for as long as the attack animation lasts
    if(!attacking)
    {
        //NON-MOVEMENT KEYS CONTROL
        if(!running)
        {
            //Use ranged attack
            if(event->key() == Qt::Key_J){
                attacking=true; //stop future keyboard inputs
                rangedAttackAnimationColumn = 0;  //set first sprite of animation
                rangedAttackDuration->start(1260);  // set duartion of ranged attack animation
                rangedAttackAnimationTimer->start(180);  //set time between each sprite during animation
            }

            //Use melee atatck
            if(event->key() == Qt::Key_K){
                attacking = true;  //stop future keyboard inputs
                meleeAttackAnimationColumn = 0;  //set first sprite of animation
                meleeAttackDuration->start(720);  //set duration of melee attack animation
                meleeAttackAnimationTimer->start(120);  // set time bewteen each sprite of animation
            }
        }

        //START RUNNING
        if(event->key() == Qt::Key_Shift)
        {
            speed = runningSpeed;
            running = true;
        }

        //MOVEMENT KEYS CONTROL

        //you'll notice the code of this keys is quite different from the ones above
        //that is because keyboards don't inmediatley realize a key is being held down
        //there's a small delay before it starts considering it as being pressed down
        //which can be fatal in games
        //therefore, these function will only tell us if a key was pressed down
        //the booleans will then be used in a slot connected to a timer
        //which will check every n seconds if the boolean is true
        //thus, when we press another key we make the other booleans false
        //so as to stop such movement slot functions which check for their respective booleans
        //if we didn't do this, the program wouldn't break
        //but it would combine movement functions
        //so pressing up and right keys at the same time would move the player diagonaly in the northeast direction
        //whhereas pressing up and down would cancel both movement functions and so forth...
        //since we don't have sprite animations for diagonal movement, we are disabling this compound movement
        //note that when we say up or right, we aren't talking about the arrow keys but rather the selected keys on GameSettings

        //SIDENOTE:
        //suppose you press the left key first, the player will start moving left
        //then, while still holding down left, you press the up key
        //naturally, the player will stop moving left and start moving up
        //but if you then release the up key, mind you while still holding the left key this whole time
        //the player won't start moving left
        //that is unless you release and press the left key again
        //this happens with any key combination
        //in order to redo the first's keys action you must press it down again
        //you can though perfectly press another key with no problem

        if(event->key() == Qt::Key_A)
        {
            //tell the program left key is being pressed
            key_MoveLeft_Pressed = true;

            //stop any process involving other movement keys
            key_MoveRight_Pressed = false;
            key_MoveDown_Pressed = false;
            key_MoveUp_Pressed = false;
        }
        if(event->key() == Qt::Key_D)
        {
            //tell the program right key is being pressed
            key_MoveRight_Pressed = true;

            //stop any process involving other movement keys
            key_MoveLeft_Pressed = false;
            key_MoveDown_Pressed = false;
            key_MoveUp_Pressed = false;
        }
        if(event->key() == Qt::Key_W)
        {
            //tell the program up key is being pressed
            key_MoveUp_Pressed = true;

            //stop any process involving other movement keys
            key_MoveRight_Pressed = false;
            key_MoveDown_Pressed = false;
            key_MoveLeft_Pressed = false;
        }
        if(event->key() == Qt::Key_S)
        {
            //tell the program down key is being pressed
            key_MoveDown_Pressed = true;

            //stop any process involving other movement keys
            key_MoveRight_Pressed = false;
            key_MoveLeft_Pressed = false;
            key_MoveUp_Pressed = false;
        }
    }
}

//CHECK IF A KEY STOPS BEING PRESSED
//just useful for movement keys

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
        key_MoveLeft_Pressed = false;
    }
    if(event->key() == Qt::Key_D)
    {
        key_MoveRight_Pressed =false;
    }
    if(event->key() == Qt::Key_W)
    {
        key_MoveUp_Pressed = false;
    }
    if(event->key() == Qt::Key_S)
    {
        key_MoveDown_Pressed = false;
    }


    //STOP RUNNING
    if(event->key() == Qt::Key_Shift)
    {
        speed = normalSpeed;
        running = false;
    }

}

//--------------
//SLOT FUNCTIONS
//--------------

//MANAGE MOVEMENT FUNCTIONS

void Player::keyPressedEvents()
{
    if(!attacking) //if player is attacking, it won't move
    {
        //check movement booleans
        if(key_MoveLeft_Pressed)
        {
            animationRow = 9; //make player face left when moving
            rangedAttackAnimationRow = 1; //make player face left when using ranged attack
            meleeAttackAnimationRow = 13; //make player face left when using melee attack
            //stop player from going out of the screen through the right
            if(pos().x() > 0)
            {
                setPos(x()-speed,y());
                newPosition = QPoint(newPosition.x()-speed,newPosition.y());
            }
            facingDirection = 0;
        }

        if(key_MoveRight_Pressed)
        {
            animationRow = 11;
            rangedAttackAnimationRow = 3;
            meleeAttackAnimationRow = 15;
            if(pos().x()+pixmap().width() < scene()->width())
            {
                setPos(x()+speed,y());
                newPosition = QPoint(newPosition.x()+speed,newPosition.y());
            }
            facingDirection = 2;
        }

       if(key_MoveUp_Pressed)
       {
           animationRow = 8;
           rangedAttackAnimationRow = 0;
           meleeAttackAnimationRow = 12;
           if(pos().y() > 0)
           {
               setPos(x(),y()-speed);
               newPosition = QPoint(newPosition.x(),newPosition.y()-speed);
           }
           facingDirection = 1;
       }

       if(key_MoveDown_Pressed)
       {
           animationRow = 10;
           rangedAttackAnimationRow = 2;
           meleeAttackAnimationRow = 14;
           if(pos().y()+pixmap().height() < scene()->height())
           {
               setPos(x(),y()+speed);
               newPosition = QPoint(newPosition.x(),newPosition.y()+speed);
           }
           facingDirection = 3;
       }
    }
}


void Player::spawn()
{
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}

void Player::animate()
{
    if(moving)
    {
        if(animationColumn == 8)
        {
            animationColumn = 0;
        }
        else
        {
            animationColumn++;
        }
        QPixmap currentImage = secondMap.copy(secondMap.width()/12*animationColumn,secondMap.height()/20*animationRow,secondMap.width()/12,secondMap.height()/20);
        setPixmap(currentImage);
    }
    else if(!attacking)
    {
         animationColumn = 0;
         QPixmap currentImage = secondMap.copy(secondMap.width()/12*animationColumn,secondMap.height()/20*animationRow,secondMap.width()/12,secondMap.height()/20);
         setPixmap(currentImage);
    }
}

void Player::checkMovement()
{
    if(oldPosition == newPosition)
    {
        moving = false;
    }
    else {
        moving = true;
    }
    oldPosition = newPosition;
}

void Player::limitPlayerMovement()
{
    attacking=false;
    rangedAttackAnimationTimer->stop();
    rangedAttackDuration->stop();
    animationColumn = 0;
}

void Player::limitMeleePlayerMovement()
{
    attacking = false;
    meleeAttackAnimationTimer->stop();
    meleeAttackDuration->stop();
    animationColumn = 0;
}

void Player::rangedAttackAnimation()
{
    if(rangedAttackAnimationColumn == 3)
    {
        RangedAttack * rangedAttack = new RangedAttack();


        rangedAttack->setDirection(facingDirection);
        switch(facingDirection)
        {
            case 0:
                rangedAttack->setPos(x()-rangedAttack->pixmap().width(),y()+pixmap().height()/2-rangedAttack->pixmap().height()/2);
                break;
            case 1:
                rangedAttack->setPos(x()+pixmap().width()/2-rangedAttack->pixmap().width()/2,y()-rangedAttack->pixmap().height());
                break;
            case 2:
                rangedAttack->setPos(x()+pixmap().width()/2,y()+pixmap().height()/2-rangedAttack->pixmap().height()/2);
                break;
            case 3:
                rangedAttack->setPos(x()+pixmap().width()/2-rangedAttack->pixmap().width()/2,y()+pixmap().height());
                break;
        }
        scene()->addItem(rangedAttack);
    }
    if(rangedAttackAnimationColumn == 6)
    {
        rangedAttackAnimationColumn = 0;
    }
    else
    {
        rangedAttackAnimationColumn++;
    }
    QPixmap currentImage = secondMap.copy(secondMap.width()/12*rangedAttackAnimationColumn,secondMap.height()/20*rangedAttackAnimationRow,secondMap.width()/12,secondMap.height()/20);
    setPixmap(currentImage);

}


void Player::meleeAttackAnimation()
{
    if(meleeAttackAnimationColumn == 5)
    {
        meleeAttackAnimationColumn = 0;
    }
    else
    {
        meleeAttackAnimationColumn++;
    }
    QPixmap currentImage = secondMap.copy(secondMap.width()/12*meleeAttackAnimationColumn,secondMap.height()/20*meleeAttackAnimationRow,secondMap.width()/12,secondMap.height()/20);
    setPixmap(currentImage);
}

