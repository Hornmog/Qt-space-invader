#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>

Bullet::Bullet()
{    
    setRect(0,0,10,50);

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

Bullet::~Bullet() {
    qDebug() << "Bullet removed";
    scene()->removeItem(this);
}


void Bullet::move()
{
    setPos(x(),y()-10);
    if((pos().y() + rect().height() < 0)){
        delete this;
    }
}

void Bullet::onHit() {
    delete this;
}
