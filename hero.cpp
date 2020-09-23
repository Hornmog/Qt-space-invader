#include "hero.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "Bullet.h"

void Hero::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << "key pressed";
    if (event->key() == Qt::Key_Left){
        if(pos().x() > 0){
            setPos(x()-10,y());
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(pos().x() + rect().width() < scene()->width()){
            setPos(x()+10,y());
        }
    }

    else if (event->key() == Qt::Key_Space){
        Bullet * bullet = new Bullet;
        bullet->setPos(x(),y());
        scene()->addItem(bullet);
    }

}
