#ifndef EXPERIENCEPOINTS_H
#define EXPERIENCEPOINTS_H
#include <QGraphicsTextItem>


class ExperiencePoints: public QGraphicsTextItem
{
public:
    ExperiencePoints(QGraphicsTextItem * parent = 0);
    void increase();
    int getExp();
private:
    int exp;
};

#endif // EXPERIENCEPOINTS_H
