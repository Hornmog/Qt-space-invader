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

    xSpeed = int(std::rand() % 21 - 10);
    ySpeed = int(std::rand() % 3 + 1);

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
        xSpeed *= -1;
    }

    setPos(pos().x()+xSpeed, pos().y()+ySpeed);


}

