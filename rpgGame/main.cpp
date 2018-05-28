#include <QApplication>
#include "Game.h"
#include "GameSettings.h"

Game * NameInProgress;
GameSettings * Settings;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Settings = new GameSettings();
    NameInProgress = new Game();
    NameInProgress->show();

    return a.exec();
}

