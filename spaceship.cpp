#include "spaceship.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

SpaceShip::SpaceShip(QObject *parent, QString imagePath) : QObject(parent)
{
    QPixmap pixmap(imagePath);
    qDebug() << pixmap << " -- pixmap";
    this->setPixmap(pixmap.scaled(width,height));
    this->setZValue(ScenePriority::spaceship);

    QTimer * mainTimer = new QTimer();
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(onTimer()));

    mainTimer->start(50);
}

void SpaceShip::shootIsAvl()
{
    shootAvl = true;
}

int SpaceShip::removalCheck() //1 - opposite side hit, 2 - same team hit, 0 - no hit
{
    auto items = collidingItems();
    for (QGraphicsItem* item: items) {
        if(item->type() == Keys::bulletIndex){
            Bullet* bullet = static_cast<Bullet*>(item);
            bool sameSide = bullet->side == this->side;
            bullet->onHit();

            if (!sameSide){
                return 1;
            }
            else{
                return 2;
            }

        }
    }
    return 0;
    //for item in list:
}

void SpaceShip::createBullet(int side)
{
    Bullet *bullet = new Bullet(bulletSpeed, side);
    // TODO: why do we need to add bullet length?
    int basePositionX = x()+(width/2);
    if(bulletSpeed > 0){
        bullet->setPos(basePositionX, y()          - bullet->getBulletLength() - 1);
    }
    else{
        bullet->setPos(basePositionX, y() + height + bullet->getBulletLength() + 1);
    }

    scene()->addItem(bullet);
    shootAvl = false;
}

void SpaceShip::setUpDelay(int shootDelay)
{
    if(timerBullet == nullptr) {
        timerBullet = new QTimer();
        connect(timerBullet,SIGNAL(timeout()),this,SLOT(shootIsAvl()));
        timerBullet->start(shootDelay);
    } else {
        timerBullet->setInterval(shootDelay);
    }
}
