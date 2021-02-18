#include "enemy.h"
#include "bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <cmath>
#include "consts.h"
#include <QRandomGenerator>
#include <QThread>

Enemy::Enemy(EnemyCommander *manager, int count) : SpaceShip(manager)
{
    active = true;
    animator = new Animator(this, this, ImagePaths::enemy, this->width, this->height);
    bulletSpeed = baseBulletSpeed;
    shootDelay = baseShootDelay;
    side = Side::enemy;

    CoordPair diff(0.2 * period_ms, 0.02 * period_ms);

    speed.x = QRandomGenerator::global()->bounded(diff.x * 2 + 1) - diff.x;
    speed.y = QRandomGenerator::global()->bounded(diff.y * 2 + 1) + diff.y;

    this->setPos(QRandomGenerator::global()->bounded(width, sceneWidth - width), - height);

    this->manager = manager;
    this->count = count;

    connect(this, &Enemy::enemyOnBase,manager, &EnemyCommander::enemyOnBase);
    connect(manager, &EnemyCommander::logKeyPressed, this, &SpaceShip::toggleCheckText);
}

Enemy::~Enemy(){
}

void Enemy::addToScene(QGraphicsScene *scene)
{
    SpaceShip::addToScene(scene);
}

void Enemy::onTimer(){
    groupCheckTextInfo();

    this->move();
    checkText->setPos(x(),y());

    if(!active){
        return;
    }
    if(shootAvl){
        createBullet();
    }

    int hitBy = this->bulletCollisionCheck();
    if(hitBy == Side::hero){
        manager->onKillOfEnemyByHero();
        delState();
        //delete this;
    }
}

void Enemy::groupCheckTextInfo()
{
    QString output = "";
    output += "Count : " + QString::number(count) + "\n";
    output += "Diff  : " + QString::number(difficulty) + "\n";
    output += "Bull speed : " + QString::number(bulletSpeed) + "\n";
    output += "SpeedX: " + QString::number(speed.x) + " speedY: " + QString::number(speed.y) + "\n";
    checkText->setPlainText(output);
}

void Enemy::setDifficulty(int difficulty)
{
    this->difficulty = difficulty;

    shootDelay = baseShootDelay * pow(0.9, difficulty - 1);
    setUpDelay(shootDelay);
    bulletSpeed = baseBulletSpeed / pow(0.9, difficulty - 1);
}

void Enemy::onDamage()
{
    manager->onKillOfEnemyByHero();
    delState();
    //delete this;
}


void Enemy::move()
{
    if(x() >= scene()->width() - this->boundingRect().width() || x() < 0){
        speed.x *= -1;
    }
    if(y() >= scene()->height() - this->boundingRect().height()){
        emit enemyOnBase();
        delete this;
    }

    setPos(x() + speed.x, y() + speed.y);

    groupCheckTextInfo();
}

void Enemy::setUpDelay(int shootDelay)
{
    if(timerBullet == nullptr) {
        timerBullet = new Timer();
        connect(timerBullet,SIGNAL(timeout()),this,SLOT(shootIsAvl()));
        timerBullet->start(shootDelay);
    } else {
        timerBullet->setInterval(shootDelay);
    }
}

void Enemy::delState()
{
    active = false;
    curType = TypeIndex::ruiningEnemy;
    speed.x = speed.x / 2;
    speed.y = speed.y / 2;
    QThread::currentThread()->setPriority(QThread::HighPriority);
    animator->setTemporaryAnimation(ImagePaths::enemyDes);
    qDebug() << ImagePaths::enemyDes;
    Timer::singleShot(ImagePaths::enemyDesDur, this, &Enemy::deleteLater);
}

