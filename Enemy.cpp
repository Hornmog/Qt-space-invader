#include "enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <cmath>
#include "Const.h"

Enemy::Enemy(EnemyManager *manager, QString imagePath) : SpaceShip(manager, imagePath)
{
    bulletSpeed = -10;
    shootDelay = baseShootDelay;
    side = 2;

    xSpeed = int(std::rand() % 21 - 10);
    ySpeed = int(std::rand() % 3 + 1);

    this->manager = manager;

    setUpDelay(shootDelay);

    connect(manager,SIGNAL(changeDifficulty(int)),this,SLOT(setDifficulty(int)));
    connect(this, SIGNAL(enemyOnBase()),manager, SIGNAL(enemyOnBase()));
}

Enemy::~Enemy(){ 
    scene()->removeItem(this);
}

void Enemy::onTimer(){
    this->move();

    if(shootAvl){
        createBullet(2);
    }

    int hitType = this->removalCheck();
    if(hitType == 2){
        manager->onSameSideKill(this);
        delete this;
    }
    else if(hitType == 1){
        manager->onEnemyDestruction(this);
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
    if(x() >= scene()->width() || x() < 0){
        xSpeed *= -1;
    }
    if(y() >= scene()->height() - this->boundingRect().height()){
        enemyOnBase();
    }

    setPos(x() + xSpeed, y() + ySpeed);


}

