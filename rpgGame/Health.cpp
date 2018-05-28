#include "Health.h"
#include <QFont>
#include "GameSettings.h"

extern GameSettings * Settings;

Health::Health(QGraphicsTextItem * parent):
    QGraphicsTextItem(parent),
    hp(Settings->hpStartingHealthPoints())
{
    setPos(x(),y()+25);
    setPlainText(QString("Health:") + QString::number(hp));
    setDefaultTextColor(Settings->hpColor());
    setFont(Settings->hpFont());
}

void Health::decrease()
{
    hp--;
    setPlainText(QString("Health:")+QString::number(hp));
}

int Health::getHP()
{
    return hp;
}

