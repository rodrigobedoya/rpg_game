#include "ExperiencePoints.h"
#include <QFont>
#include "GameSettings.h"

extern GameSettings * Settings;

ExperiencePoints::ExperiencePoints(QGraphicsTextItem *parent):
    QGraphicsTextItem(parent),
    exp(Settings->xpStartingExperiencePoints())
{
    setPlainText(QString("Exp:") + QString::number(exp));
    setDefaultTextColor(Settings->xpColor());
    setFont(Settings->xpFont());
}

void ExperiencePoints::increase()
{
    exp++;
    setPlainText(QString("Exp:") + QString::number(exp));
}

int ExperiencePoints::getExp()
{
    return exp;
}

