#include "enemycommander.h"
#include "graphic-objects/enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <iostream>
#include <cstdlib>
#include "consts.h"

EnemyCommander::EnemyCommander(QGraphicsScene* scene, KeyManager* keyManager)
{
    this->scene = scene;
    connect(keyManager, &KeyManager::logKeyPressed, this, &EnemyCommander::logKeyPressed);
}

void EnemyCommander::startSpawningEnemies()
{
    createEnemy();
    connect(timer, &QTimer::timeout, this, &EnemyCommander::onSpawnTimer);
    timer->start(spawnRate);
}

QJsonObject EnemyCommander::returnEnemiesKilled()
{
    QJsonObject info = QJsonObject();
    info[JsonNames::enemiesKilled] = QString::number(score);
    return info;
}

void EnemyCommander::onKillOfEnemyByHero()
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


void EnemyCommander::onSpawnTimer()
{
    if(enemyCount < maxEnemyAlive && score < totalEnemiesToKill - enemyCount){
        createEnemy();
    }
}

void EnemyCommander::createEnemy()
{
    Enemy* enemy = new Enemy(this, totalEnemiesSpawned);
    enemy->setDifficulty(difficulty);
    enemy->addToScene(scene);
    enemyCount++;
    totalEnemiesSpawned++;
}
