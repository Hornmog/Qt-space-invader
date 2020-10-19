#include "spaceship.h"
#include "graphic-objects/bullet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include "keymanager.h"

SpaceShip::SpaceShip(QObject *parent, QString imagePath) : QObject(parent)
{
    QPixmap pixmap(imagePath);
    this->setPixmap(pixmap.scaled(width,height));
    this->setZValue(ScenePriority::spaceship);

    checkText = new QGraphicsTextItem(this);
    setUpCheckText();

    QTimer * mainTimer = new QTimer();
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(onTimer()));

    mainTimer->start(onTimerPeriod);

}

void SpaceShip::shootIsAvl()
{
    shootAvl = true;
}

int SpaceShip::removalCheck()
{
    auto items = collidingItems();
    for (QGraphicsItem* item: items) {
        if(item->type() == Keys::bulletIndex){
            Bullet* bullet = static_cast<Bullet*>(item);

            int bulletSide = bullet->side;
            bullet->onHit();

            return bulletSide;
        }
    }
    return Side::nobody;
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
