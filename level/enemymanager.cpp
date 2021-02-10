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
    connect(keyManager, &KeyManager::logKeyPressed, this, &EnemyManager::logKeyPressed);
}

void EnemyManager::startSpawningEnemies()
{
    createEnemy();
    connect(timer, &Timer::timeout, this, &EnemyManager::onSpawnTimer);
    timer->start(spawnRate);
}

QJsonObject EnemyManager::returnEnemiesKilled()
{
    QJsonObject info = QJsonObject();
    info[JsonNames::enemiesKilled] = QString::number(score);
    return info;
}

void EnemyManager::onKillByHero()
{
    score++;
    emit onEnemyCountChange(score);

    enemyCount--;
    upForNextDiff--;

    if(upForNextDiff <= 0){
        difficulty++;
        upForNextDiff = levelDifficultyStep;
    }

    if (score == totalEnemiesToKill){
        emit allEnemiesDefeated();
    }    
}


void EnemyManager::onSpawnTimer()
{
    if(enemyCount < maxEnemyAlive && score < totalEnemiesToKill - enemyCount){
        createEnemy();
    }
}

void EnemyManager::createEnemy()
{
    Enemy* enemy = new Enemy(this, ImagePaths::enemy, totalEnemiesSpawned);
    enemy->setDifficulty(difficulty);
    enemy->addToScene(scene);
    enemyCount++;
    totalEnemiesSpawned++;
}
