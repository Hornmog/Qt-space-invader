#include "Enemy.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "Cons.h"

Enemy::Enemy()
{
    setRect(0,0,50,50);

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));

    timer->start(50);

}

void Enemy::onTimer(){
    this->removalCheck();
}

bool Enemy::removalCheck(){
    auto items = collidingItems();
    for (QGraphicsItem* item: items) {
        if()
    }
    //for item in list:
}

void Enemy::removal(){

}
