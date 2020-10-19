#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QGraphicsObject>
#include "spaceship.h"

#include "keymanager.h"


class Hero: public SpaceShip{
    Q_OBJECT
public:
    Hero(QString imagePath = nullptr, KeyManager* keyManager = nullptr);


signals:
    void heroKilled();

public slots:
    void onTimer() override;
    void groupCheckTextInfo() override;
    void heroKeyPressed(int key);

private:
    KeyManager* keyManager;
    int calculateXMovement();
    float xVelocity;
    int accelNumberOfCycles;
    int accelCyclesLeft;

    struct MovementX {
        static const int maxVelocity = 200;         //pixels per second
        static const int accel = 1000;
        static const int friction = 50;
        static const int accelTime = 250;
    };

};

#endif // MYRECT_H
