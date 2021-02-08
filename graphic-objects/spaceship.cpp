#include "spaceship.h"
#include "graphic-objects/bullet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include "keymanager.h"
#include "checktext.h"
#include "utils/clock.h"

SpaceShip::SpaceShip(QObject *parent, QString imagePath) : AnimatedObject(), MovingObject()
    //: AnimatedObject(parent, imagePath)
{
    setZValue(1);
    setZValue(ScenePriority::spaceship);
}

void SpaceShip::shootIsAvl()
{
    shootAvl = true;
}

void SpaceShip::createBullet()
{
    Bullet *bullet = new Bullet(bulletSpeed, this->side);
    // TODO: why do we need to add bullet length?
    int basePositionX = x()+(width/2);

    // I think we could move it to Bullet(). We use "side" there anyway.
    // Maybe even the imagePath logic from above can be there.
    // It was moved out before, however; do you remember why?
    // If it's just about bassing the additionaly computed value to the base class,
    // it shouldn't be a problem; e.g. see
    // https://stackoverflow.com/questions/10260760/c-calling-a-base-class-constructor-with-a-computed-argument
    if(bulletSpeed > 0){
        bullet->setPos(basePositionX, y()          - bullet->getBulletLength() - 1);
    }
    else{
        bullet->setPos(basePositionX, y() + height + bullet->getBulletLength() + 1);
    }

    scene()->addItem(bullet);
    shootAvl = false;
}

