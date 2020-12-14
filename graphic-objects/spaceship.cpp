#include "spaceship.h"
#include "graphic-objects/bullet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include "keymanager.h"
#include "checktext.h"
#include "clock.h"

SpaceShip::SpaceShip(QObject *parent, QString imagePath) : AnimatedObject(parent, imagePath)
{
    checkText = new CheckText();
    setUpCheckText();
    this->setZValue(ScenePriority::spaceship);

    mainTimer = new Timer();
    connect(mainTimer, &QTimer::timeout, this, &SpaceShip::onTimer);
    mainTimer->start(period_ms);

}

void SpaceShip::shootIsAvl()
{
    shootAvl = true;
}

QGraphicsItem* SpaceShip::collisionCheck(int typeIndex)
{
    auto items = this->collidingItems();
    for (QGraphicsItem* item: qAsConst(items)) {
        if(item->type() == typeIndex){
            return item;
        }
    }
    return nullptr;
}

int SpaceShip::bulletCollisionCheck()
{
     auto item = collisionCheck(TypeIndex::bullet);
     if(item != nullptr) {
        Bullet* bullet = static_cast<Bullet*>(item);
        int bulletSide = bullet->side;
        bullet->onHit();
        return bulletSide;
    }
    return Side::nobody;
}

void SpaceShip::createBullet(int side)
{
    QString imagePath;
    if (side == 2){
        imagePath = ImagePaths::enemyBullet;
    } else if(side == 1){
        imagePath = ImagePaths::bullet;
    }

    Bullet *bullet = new Bullet(bulletSpeed, side, imagePath);
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
        timerBullet = new Timer();
        connect(timerBullet,SIGNAL(timeout()),this,SLOT(shootIsAvl()));
        timerBullet->start(shootDelay);
    } else {
        timerBullet->setInterval(shootDelay);
    }
}

void SpaceShip::setUpCheckText()
{
    QFont font = QFont("Times", 10);
    QColor color = QColor("white");
    checkText->setFont(font);
    checkText->setDefaultTextColor(color);
    checkText->setPlainText(QString::number(0));
    checkText->setZValue(ScenePriority::text);
    checkText->hide();

}

void SpaceShip::setCheckText(QString string)
{
    checkText->setPlainText(string);
}

void SpaceShip::toggleCheckText(bool show)
{
    checkText->setVisible(show);

}
