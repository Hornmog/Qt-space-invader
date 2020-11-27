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
    width = 150, height = 150;

    CoordPair diff(0.2 * period_ms, 0.02 * period_ms);

    speed.x = QRandomGenerator::global()->bounded(diff.x * 2 + 1) - diff.x;
    speed.y = QRandomGenerator::global()->bounded(diff.y * 2 + 1) + diff.y;


    this->manager = manager;
    this->count = count;

    setUpDelay(shootDelay);

    connect(manager, SIGNAL(changeDifficulty(int)), this, SLOT(setDifficulty(int)));
    connect(manager, SIGNAL(startAll()), this, SLOT(resume()));
    connect(manager, SIGNAL(stopAll()), this, SLOT(pause()));
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
    output += "Speed: x: " + QString::number(speed.x) + " y: " + QString::number(speed.y) + "\n";
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
    delete this;
}

