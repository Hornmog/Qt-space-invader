#include "enemymanager.h"
#include "graphic-objects/enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <iostream>
#include <cstdlib>
#include "consts.h"

EnemyManager::EnemyManager(QGraphicsScene* scene, KeyManager* keyManager)
{
    this->scene = scene;

    connect(keyManager, SIGNAL(logKeyPressed(bool)), this, SIGNAL(logKeyPressed(bool)));    
}

void EnemyManager::startSpawningEnemies()
{
    createEnemy();
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onSpawnTimer()));
    timer->start(spawnRate);
}

QJsonObject EnemyManager::returnEnemiesKilled()
{
    QJsonObject info = QJsonObject();
    info[JsonNames::enemiesKilled] = QString::number(score);
    return info;
}

void EnemyManager::onEnemyDestruction(Enemy* enemy)
{
    enemyCount--;
    upForNextDiff--;

    if(upForNextDiff <= 0){
        difficulty++;
        upForNextDiff = levelDifficultyStep;
        changeDifficulty(difficulty);
    }  


}

void EnemyManager::onKillByHero(Enemy *enemy)
{
    score++;
    onEnemyCountChange(score);
    onEnemyDestruction(enemy);
    if (score == totalEnemiesToKill){
        allEnemiesDefeated();
    }    
}

void EnemyManager::onKillByNonHero(Enemy *enemy)
{
    onEnemyDestruction(enemy);
}



void EnemyManager::onSpawnTimer()
{
    if(enemyCount < maxEnemyAlive && score < totalEnemiesToKill - enemyCount){
        createEnemy();
    }

}

void EnemyManager::createEnemy()
{
    Enemy* enemy = new Enemy(this, ImagePaths::enemyImagePath, totalEnemiesSpawned);
    scene->addItem(enemy);
    int offset = enemy->width;
    enemy->setPos(QRandomGenerator::global()->bounded(offset, scene->width() - offset), 0);
    enemyCount++;
    totalEnemiesSpawned++;
    changeDifficulty(difficulty);
}
