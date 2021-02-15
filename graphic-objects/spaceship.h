#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "keymanager.h"
#include "consts.h"
#include "utils/timer.h"
#include "utils/coordpair.h"
#include "checktext.h"
#include "animatedobject.h"
#include "movingobject.h"

class SpaceShip : public MovingObject
{

    Q_OBJECT
public:
    explicit SpaceShip(QObject *parent = nullptr);
signals:

protected:
    void createBullet();

    CoordPair prevSpeed = CoordPair(0,0);
    float bulletSpeed;
    const int baseShootDelay = 2500;
    bool shootAvl = false;
    int shootDelay;
    bool active = false;

private:

protected:
    Animator *animator;
    int width = 100, height = 100;
    // w and h are to determined in derived objects

private slots:
    void shootIsAvl();
};

#endif // SPACESHIP_H
