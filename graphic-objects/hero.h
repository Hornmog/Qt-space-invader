#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QGraphicsObject>
#include "spaceship.h"
#include "consts.h"
#include "keymanager.h"


class Hero: public SpaceShip{
    Q_OBJECT
public:
    Hero(QString imagePath = nullptr, KeyManager* keyManager = nullptr);
    int type() const override {return TypeIndex::hero;}


signals:
    void heroKilled();

public slots:
    void onTimer() override;
    void groupCheckTextInfo() override;
    void heroKeyPressed(int key);
    void heroKeyReleased(int key);

private:
    KeyManager* keyManager;
    int calculateXMovement();
    bool checkScreenBorders(int distance);
    int accelNumberOfCycles;
    int accelCyclesLeft;
    float accel;
    bool rightKeyPressed;
    bool leftKeyPressed;

    struct MovementX {
        static const int maxVelocity = 200;         //pixels per second
        static const int accel = 1000;
        static const int friction = 50;
    };

};

#endif // MYRECT_H
