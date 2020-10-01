#include "enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <cmath>

Enemy::Enemy(EnemyManager *manager)
{
    width = 100;
    height = 100;
    speed = 5;
    bulletSpeed = -10;
    shootDelay = baseShootDelay;
    ImagePath = ":/images/enemy.png";

    QPixmap Pixmap(ImagePath);
    this->setPixmap(Pixmap.scaled(width,height));

    this->manager = manager;

    setUpDelay(shootDelay);

    connect(manager,SIGNAL(changeDifficulty(int)),this,SLOT(setDifficulty(int)));
}

Enemy::~Enemy(){
    manager->onEnemyRemoval(this);
    scene()->removeItem(this);
}

void Enemy::onTimer(){
    this->move();

    if(shootAvl){
        createBullet(2);
    }

    if(this->removalCheck()){
        delete this;
    }
}

void Enemy::setDifficulty(int difficulty)
{
    shootDelay = baseShootDelay * pow(0.8, difficulty-1);
    setUpDelay(shootDelay);
    bulletSpeed = baseBulletSpeed * difficulty;
}


void Enemy::move()
{
    if(pos().x() >= 750 || pos().x() < 0){
        qDebug() << pos().x();
        speed *= -1;
    }
    setPos(pos().x()+speed, pos().y());


}

