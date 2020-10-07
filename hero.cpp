#include "hero.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "Bullet.h"
#include <QTimer>

Hero::Hero(QString imagePath) : SpaceShip(nullptr, imagePath)
{
    shootDelay = 1000;
    bulletSpeed = 10;
    xSpeed = 10;
    ySpeed = 10;

    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    setUpDelay(shootDelay);
}

void Hero::onTimer()
{
    if(removalCheck()){
        heroKilled();
    }
}

void Hero::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << "key pressed";
    if (event->key() == Qt::Key_Left){
        if(pos().x() > 0){
            setPos(x()-xSpeed,y());
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(pos().x() + this->boundingRect().width() < scene()->width()){
            setPos(x()+xSpeed,y());
        }
    }
    else if (event->key() == Qt::Key_Up){
        if(pos().y() > 0){
            setPos(x(), y() - ySpeed);
        }
    }
    else if (event->key() == Qt::Key_Down){
        if(pos().y() + this->boundingRect().height() < scene()->height()){
            setPos(x(), y() + ySpeed);
        }
    }

    else if (event->key() == Qt::Key_Space && shootAvl){
        createBullet();

        //qDebug() << shootAvl;
    }

}

