#include "enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>

Enemy::Enemy(EnemyManager *manager)
{
    width = 50;
    height = 50;
    speed = 5;
    bulletSpeed = -10;
    shootDelay = 3000;

    this->manager = manager;
    setRect(0,0,width,height);

    setUpDelay(shootDelay);
}

Enemy::~Enemy(){
    manager->onEnemyRemoval(this);
    scene()->removeItem(this);
}

void Enemy::onTimer(){
    this->move();

    if(shootAvl){
        createBullet();
    }

    if(this->removalCheck()){
        delete this;
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

