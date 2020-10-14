#include "hero.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "Bullet.h"
#include <QTimer>
#include "keymanager.h"

Hero::Hero(QString imagePath, KeyManager* keyManager) : SpaceShip(nullptr, imagePath)
{
    shootDelay = 1000;
    bulletSpeed = 10;
    xSpeed = 10;     //Speed is a step with which hero moves upon keyPressEvent
    ySpeed = 10;
    side = Side::hero;

    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    //this->setFocus();

    setUpDelay(shootDelay);

    this->keyManager = keyManager;
    connect(keyManager, SIGNAL(heroKeyPressed(int)), this, SLOT(heroKeyPressed(int)));
}

void Hero::onTimer()
{
    if(removalCheck() != Side::nobody){
        heroKilled();
    }
}

void Hero::heroKeyPressed(int key)
{
    //qDebug() << "key pressed";
    if (key == Qt::Key_Left){
        if(pos().x() > 0){
            setPos(x()-xSpeed,y());
        }
    }
    else if (key == Qt::Key_Right){
        if(pos().x() + this->boundingRect().width() < scene()->width()){
            setPos(x()+xSpeed,y());
        }
    }
    else if (key == Qt::Key_Up){
        if(pos().y() > 0){
            setPos(x(), y() - ySpeed);
        }
    }
    else if (key == Qt::Key_Down){
        if(pos().y() + this->boundingRect().height() < scene()->height()){
            setPos(x(), y() + ySpeed);
        }
    }

    else if (key == Qt::Key_Space && shootAvl){
        createBullet(1);

        //qDebug() << shootAvl;
    }

}

