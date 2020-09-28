#include "hero.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "Bullet.h"
#include <QTimer>

Hero::Hero()
{
    this->setRect(0,0,width,height);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(shootIsAvl()));

    timer->start(1000);
}

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

    else if (event->key() == Qt::Key_Space && shootAvl){
        Bullet * bullet = new Bullet;
        bullet->setPos(x()+(width/2),y()-20);
        scene()->addItem(bullet);
        shootAvl = 0;
        //qDebug() << shootAvl;
    }

}

void Hero::shootIsAvl()
{
    shootAvl = 1;
    //qDebug() << shootAvl;
}
