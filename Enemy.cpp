#include "enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>


Enemy::Enemy(EnemyManager *manager)
{
    this->manager = manager;
    setRect(0,0,width,height);


    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));

    timer->start(50);

    QTimer * timer_bullet = new QTimer();
    connect(timer_bullet,SIGNAL(timeout()),this,SLOT(createBullet()));

    timer_bullet->start(shoot_interval);

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



void Enemy::move()
{
    if(pos().x() >= 750 || pos().x() < 0){
        qDebug() << pos().x();
        speed *= -1;
    }
    setPos(pos().x()+speed, pos().y());


}

void Enemy::createBullet()
{
    Bullet *bullet = new Bullet();
    bullet->speed = -10;
    bullet->setPos(x()+(width/2),y()+height+60);
    scene()->addItem(bullet);
}


