#include "spaceship.h"
#include "graphic-objects/bullet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include "keymanager.h"
#include "checktext.h"
#include "utils/clock.h"

bool SpaceShip::checkTextVisible = false;

SpaceShip::SpaceShip(QObject *parent, QString imagePath) : AnimatedObject(parent, imagePath)
{
    checkText = new CheckText();
    setUpCheckText();
    this->setZValue(ScenePriority::spaceship);

    mainTimer = new Timer();
    connect(mainTimer, &QTimer::timeout, this, &SpaceShip::onTimer);
    mainTimer->start(period_ms);

}

SpaceShip::~SpaceShip()
{
    delete checkText;
}

void SpaceShip::addToScene(QGraphicsScene *scene)
{
    scene->addItem(this);
    scene->addItem(checkText);

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
        bullet->deleteSelf();
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

void SpaceShip::setUpCheckText()
{

    QFont font = QFont("Impact", 16, QFont::Bold);
    QColor color = QColor(255, 100, 108);
    checkText->setFont(font);
    checkText->setDefaultTextColor(color);
    checkText->setPlainText(QString::number(0));
    checkText->setZValue(ScenePriority::text);
    checkText->setVisible(checkTextVisible);
}


void SpaceShip::toggleCheckText()
{
    qDebug() << "Check Text visible 1: " << checkTextVisible;
    checkText->setVisible(checkTextVisible);
    qDebug() << "Check Text visible 2: " << checkText->isVisible();

}
