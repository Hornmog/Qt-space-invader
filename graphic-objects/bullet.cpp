#include "bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "consts.h"
#include "timer.h"

Bullet::Bullet(int speed, int side, QString imagePath) : AnimatedObject(nullptr, imagePath, 21, 40)
{
    setSize(20,50);
    this->side = side;

//    if(side == 1){
//         imagePath = ImagePaths::bullet;
//    }
//    else if(side == 2){
//         imagePath = ImagePaths::enemyBullet;
//    }
    this->setZValue(ScenePriority::bullet);

    this->speed = speed;

    Timer * timer = new Timer();
    connect(timer, &Timer::timeout, this, &Bullet::move);

    timer->start(period_ms);
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

void Bullet::onHit() {
    delete this;
}
