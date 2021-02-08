#ifndef METEOR_H
#define METEOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "utils/coordpair.h"
#include "utils/timer.h"

class Meteor : public QGraphicsPixmapItem
{
public:
    Meteor();

private:
    void addToScene(QGraphicsScene* scene);

    CoordPair speed = CoordPair(0,0);
    CoordPair innitPos = CoordPair(0,0);
    CoordPair size = CoordPair(0,0);
    Timer* mainTimer;

public slots:
    void toggleCheckText();

};

#endif // METEOR_H
