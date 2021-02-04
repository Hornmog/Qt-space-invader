#include "bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "consts.h"
#include "utils/timer.h"

Bullet::Bullet(float speed, Side side) : AnimatedObject(nullptr, Bullet::getPath(side), 21, 40)
{
    setSize(20,50);
    this->side = side;

    this->setZValue(ScenePriority::bullet);

    this->speed = speed;

    Timer * timer = new Timer();
    connect(timer, &Timer::timeout, this, &Bullet::move);

    timer->start(period_ms);
}

QString Bullet::getPath(Side side)
{
    if (side == Side::enemy){
        return ImagePaths::enemyBullet;
    } else if(side == Side::hero){
        return ImagePaths::bullet;
    } else {
        throw "No bullet image defined for the side " + QString::number(side);
    }
}

Bullet::~Bullet() {
    scene()->removeItem(this);
}


void Bullet::move()
{
    setPos(x(),y() - speed);
    if((pos().y() + this->boundingRect().height() < 0 || pos().y() > scene()->height())){
        delete this;                                         //when bullet leaves view, it is destroyed
    }
}

void Bullet::deleteSelf() {
    delete this;
}
