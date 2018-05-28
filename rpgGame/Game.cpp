#include "Game.h"

#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include <QImage>
#include "GameSettings.h"

extern GameSettings * Settings;

Game::Game(QWidget *parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(Settings->scenePosition().x(),Settings->scenePosition().y(),Settings->sceneWidth(),Settings->sceneHeight());
    setBackgroundBrush(QBrush(Settings->backgroundImage()));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(Settings->sceneWidth(),Settings->sceneHeight());

    player = new Player();

    //position player in the middle
    player->setPos(scene->width()/2 - player->pixmap().width()/2, scene->height()/2 - player->pixmap().height()/2);

    //make it able to respond to keys
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //add player to the screen
    scene->addItem(player);

    //create and add experience
    XP = new ExperiencePoints();
    scene->addItem(XP);

    //create and add health
    HP = new Health();
    scene->addItem(HP);

    //timer for spawning of enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(Settings->enemySpawnTimer()); //every 2.5 seconds spawn an enemy

    show();
}


