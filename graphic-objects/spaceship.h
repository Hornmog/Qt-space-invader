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

class SpaceShip : public AnimatedObject, public MovingObject
{
    Q_OBJECT

public:
    explicit SpaceShip(QObject *parent = nullptr, QString imagePath = nullptr);

public slots:
    void toggleCheckText();
signals:

protected:
    void createBullet();

    CoordPair prevSpeed = CoordPair(0,0);
    float bulletSpeed;
    const int baseShootDelay = 2500;
    bool shootAvl = false;
    int shootDelay;

private:


private slots:
    void shootIsAvl();
};

#endif // SPACESHIP_H
