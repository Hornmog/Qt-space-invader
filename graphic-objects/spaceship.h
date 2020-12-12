#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsRectItem>
#include "keymanager.h"
#include "consts.h"
#include "timer.h"
#include "coordpair.h"
#include "checktext.h"
#include "animatedobject.h"

class SpaceShip : public AnimatedObject
{
    Q_OBJECT
public:
    explicit SpaceShip(QObject *parent = nullptr, QString imagePath = nullptr);

    int side;
    static const int width = 100;
    static const int height = 100;

public slots:
    virtual void onTimer() = 0;
    void toggleCheckText(bool show);

signals:

protected:
    void createBullet(int side = 1);
    QGraphicsItem* collisionCheck(int typeIndex);
    int bulletCollisionCheck();

    void setUpDelay(int delay);
    void setUpCheckText();
    void setCheckText(QString string);

    virtual void groupCheckTextInfo() = 0;

    CoordPair speed = CoordPair(0,0);
    CoordPair prevSpeed = CoordPair(0,0);
    int bulletSpeed;
    int shootDelay;
    const int baseShootDelay = 5000;
    bool shootAvl = true;
    CheckText *checkText;
    Timer* mainTimer;

private:
    Timer* timerBullet = nullptr;

private slots:
    void shootIsAvl();
};

#endif // SPACESHIP_H
