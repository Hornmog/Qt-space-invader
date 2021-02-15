#ifndef METEOR_H
#define METEOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "movingobject.h"
#include "utils/coordpair.h"
#include "utils/timer.h"

class Meteor : public MovingObject
{
public:
    Meteor();

private:
    enum MovingFrom{left, right};
    MovingFrom movingFrom;
    void move();

    CoordPair Pos = CoordPair(0,0);
    CoordPair size = CoordPair(0,0);

public slots:

};

#endif // METEOR_H
