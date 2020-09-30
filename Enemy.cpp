#include "enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>


//TODO: add Person class that Enemy and Hero inherit from.
// Common function: removalCheck, shootIsAvl, createBullet
Enemy::Enemy(EnemyManager *manager)
{
    width = 50;
    height = 50;
    speed = 5;
    bulletSpeed = -10;
    shootDelay = 3000;

    this->manager = manager;
    setRect(0,0,width,height);


    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));

    timer->start(50);

    QTimer * timer_bullet = new QTimer();
    connect(timer_bullet,SIGNAL(timeout()),this,SLOT(shootIsAvl()));

    timer_bullet->start(shootDelay);

}

Enemy::~Enemy(){
    manager->onEnemyRemoval(this);
    scene()->removeItem(this);
}

void Enemy::onTimer(){
    this->move();

    if(this->removalCheck()){
        delete this;
    }

    else if(shootAvl){
        createBullet();
    }
}


void Enemy::move()
{
    if(pos().x() >= 750 || pos().x() < 0){
        qDebug() << pos().x();
        speed *= -1;
    }
    setPos(pos().x()+speed, pos().y());


}

