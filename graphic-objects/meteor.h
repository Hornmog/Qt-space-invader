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
    void addToScene(QGraphicsScene *scene) override;

private:
//    enum MovingFrom{left, right};
//    MovingFrom movingFrom;
    void move();
    void groupCheckTextInfo() override;
    void onTimer() override;
    void selfDestroy();
    CoordPair currPos = CoordPair(0,0);
    CoordPair size = CoordPair(0,0);

public slots:

};

#endif // METEOR_H
