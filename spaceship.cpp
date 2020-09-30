#include "spaceship.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

SpaceShip::SpaceShip(QObject *parent) : QObject(parent)
{

}

void SpaceShip::shootIsAvl()
{
    shootAvl = true;
    //qDebug() << shootAvl;

}

bool SpaceShip::removalCheck()
{
    auto items = collidingItems();
    for (QGraphicsItem* item: items) {
        if(item->type() == Keys::bulletIndex){
            Bullet* bullet = static_cast<Bullet*>(item);
            bullet->onHit();
            qDebug() << "collision with bullet occured";
            return true;
        }
    }
    return false;
    //for item in list:
}

void SpaceShip::createBullet()
{
    Bullet *bullet = new Bullet(bulletSpeed);
    // TODO: why do we need to add bullet length?
    if(bulletSpeed > 0){
        bullet->setPos(x()+(width/2),y()-bullet->getBulletLength()-1);
    }
    else{
        bullet->setPos(x()+(width/2),y()+height+bullet->getBulletLength() +1);
    }

    scene()->addItem(bullet);
    shootAvl = false;
}
