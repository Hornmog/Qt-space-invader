#include "enemy.h"
#include "bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <cmath>
#include "consts.h"

Enemy::Enemy(EnemyManager *manager, QString imagePath, int count) : SpaceShip(manager, imagePath)
{
    bulletSpeed = -10;
    shootDelay = baseShootDelay;
    side = Side::enemy;

    xSpeed = int(std::rand() % 21 - 10);
    ySpeed = int(std::rand() % 3 + 1);


    this->manager = manager;
    this->count = count;

    setUpDelay(shootDelay);

    connect(manager,SIGNAL(changeDifficulty(int)),this,SLOT(setDifficulty(int)));
    connect(this, SIGNAL(enemyOnBase()),manager, SIGNAL(enemyOnBase()));
    connect(manager, SIGNAL(logKeyPressed(bool)), this, SLOT(toggleCheckText(bool)));
}

Enemy::~Enemy(){ 
    scene()->removeItem(this);
}

void Enemy::onTimer(){
    this->move();

    if(shootAvl){
        createBullet(side);
    }

    int hitBy = this->removalCheck();
    if(hitBy != Side::nobody){
        positiveRemoval(hitBy);
    }
}

void Enemy::groupCheckTextInfo()
{
    QString output = "";
    output += "Count : " + QString::number(count) + "\n";
    output += "Diff  : " + QString::number(difficulty) + "\n";
    output += "Bull speed : " + QString::number(bulletSpeed) + "\n";
    output += "Speed: x: " + QString::number(xSpeed) + " y: " + QString::number(ySpeed) + "\n";
    setCheckText(output);
}

void Enemy::setDifficulty(int difficulty)
{
    this->difficulty = difficulty;

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

    groupCheckTextInfo();
}

void Enemy::positiveRemoval(int hitBy)
{
    if(hitBy == Side::hero){
        manager->onKillByHero(this);
    }
    else if(hitBy == Side::enemy){
        manager->onKillByNonHero(this);
    }
    delete this;
}

