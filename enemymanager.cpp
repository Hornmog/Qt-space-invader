#include "enemymanager.h"
#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include "ScoreBar.h"
#include <iostream>
#include <cstdlib>

EnemyManager::EnemyManager(QGraphicsScene *scene, ScoreBar *scoreBar)
{
    this->scene = scene;
    this->scoreBar = scoreBar;
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));

    timer->start(2000);
}

void EnemyManager::onEnemyRemoval(Enemy* enemy)
{
    enemyCount--;
    score++;
    onEnemyCountChange(score);
}

void EnemyManager::onTimer()
{
    if(enemyCount < 3){
        createEnemy();
    }

}

void EnemyManager::createEnemy()
{
    Enemy * enemy = new Enemy(this);
    enemy->setRect(0,0,100,100);
    scene->addItem(enemy);
    enemy->setPos(int(std::rand() % 500 + 100), 0);
    enemyCount++;

}

int EnemyManager::getScore()
{
    return score;
}
