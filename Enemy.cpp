#include "enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>


Enemy::Enemy()
{
    setRect(0,0,50,50);


    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));

    timer->start(50);

}

void Enemy::onTimer(){
    this->move();

    if(this->removalCheck()){
        removal();
    }

}

bool Enemy::removalCheck(){
    auto items = collidingItems();
    for (QGraphicsItem* item: items) {
        if(item->type() == Keys::bulletIndex){
            Bullet* bullet = static_cast<Bullet*>(item);
            bullet->onHit();
            qDebug() << "collision with bullet occured";
            return true;
        }
    }
    return false;
    //for item in list:
}

void Enemy::removal(){
    scene()->removeItem(this);
    delete this;
}

void Enemy::move()
{
    if(pos().x() >= 750 || pos().x() < 0){
        qDebug() << "Changed";
        speed *= -1;
    }
    setPos(pos().x()+speed, pos().y());


}


