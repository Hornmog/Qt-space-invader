#include "spaceship.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

SpaceShip::SpaceShip(QObject *parent, QString imagePath) : QObject(parent)
{
    qDebug() << "Spaceship constructor called";
    qDebug() << "Image path: " << imagePath;
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

void SpaceShip::createBullet(int bulletType)
{
    Bullet *bullet = new Bullet(bulletSpeed, bulletType);
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
