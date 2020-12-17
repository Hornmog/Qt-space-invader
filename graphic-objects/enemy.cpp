#include "enemy.h"
#include "bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <cmath>
#include "consts.h"
#include <QRandomGenerator>

Enemy::Enemy(EnemyManager *manager, QString imagePath, int count) : SpaceShip(manager, imagePath)
{
    bulletSpeed = baseBulletSpeed;
    shootDelay = baseShootDelay;
    side = Side::enemy;

    CoordPair diff(0.2 * period_ms, 0.02 * period_ms);

    speed.x = QRandomGenerator::global()->bounded(diff.x * 2 + 1) - diff.x;
    speed.y = QRandomGenerator::global()->bounded(diff.y * 2 + 1) + diff.y;


    this->manager = manager;
    this->count = count;

    setUpDelay(shootDelay);

    connect(manager, &EnemyManager::changeDifficulty, this, &Enemy::setDifficulty);
    connect(this, &Enemy::enemyOnBase,manager, &EnemyManager::enemyOnBase);
    connect(manager, &EnemyManager::logKeyPressed, this, &SpaceShip::toggleCheckText);
}

Enemy::~Enemy(){
    // Do we need to do this, or can the scene deal with it automatically?
    scene()->removeItem(this);
}

void Enemy::onTimer(){
    this->move();
    checkText->setPos(x(),y());

    if(shootAvl){
        createBullet(side);
    }

    int hitBy = this->bulletCollisionCheck();
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
    output += "SpeedX: " + QString::number(speed.x) + " speedY: " + QString::number(speed.y) + "\n";
    setCheckText(output);
}

void Enemy::setDifficulty(int difficulty)
{
    this->difficulty = difficulty;

    shootDelay = baseShootDelay * pow(0.8, difficulty-1);
    setUpDelay(shootDelay);
    bulletSpeed = baseBulletSpeed * difficulty;
}

void Enemy::onHeroCollision()
{
    positiveRemoval(Side::hero);
}


void Enemy::move()
{
    if(x() >= scene()->width() || x() < 0){
        speed.x *= -1;
    }
    if(y() >= scene()->height() - this->boundingRect().height()){
        emit enemyOnBase();
    }

    setPos(x() + speed.x, y() + speed.y);

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
}

