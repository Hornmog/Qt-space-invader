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

};

#endif // MYRECT_H
