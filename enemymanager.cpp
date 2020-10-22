#include "enemymanager.h"
#include "graphic-objects/enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include "scorebar.h"
#include <iostream>
#include <cstdlib>
#include "consts.h"

EnemyManager::EnemyManager(QGraphicsScene* scene, ScoreBar* scoreBar, KeyManager* keyManager)
{
    this->scene = scene;
    this->scoreBar = scoreBar;

    connect(keyManager, SIGNAL(logKeyPressed(bool)), this, SIGNAL(logKeyPressed(bool)));    
}

void EnemyManager::startSpawningEnemies()
{
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onSpawnTimer()));
    timer->start(spawnRate);
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
    if (score == totalEnemiesToKill){
        allEnemiesDefeated();
    }

    onEnemyDestruction(enemy);
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
    int offset = 100;
    // 0...800
    // 100...700
    // 0...(800-2*100)
    enemy->setPos(int(std::rand() % (int(scene->width()) - 2*offset) + offset), 0);  
    enemyCount++;
    totalEnemiesSpawned++;
    changeDifficulty(difficulty);
}
