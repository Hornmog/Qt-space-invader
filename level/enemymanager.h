#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <QObject>
#include <QGraphicsRectItem>
#include "keymanager.h"
#include <QJsonObject>
#include "utils/timer.h"

class Enemy;

class EnemyManager : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    EnemyManager(QGraphicsScene* scene, KeyManager* keyManager);
    void onKillByHero();
    void startSpawningEnemies();
    void setTotalEnemiesToKill(int num) {totalEnemiesToKill = num;}
    QJsonObject returnEnemiesKilled();

    int score = 0;

signals:
    void onEnemyCountChange(int enemyDeaths);
    void allEnemiesDefeated();
    void enemyOnBase();
    void logKeyPressed();

public slots:
    void onSpawnTimer();

private:
    void createEnemy();

    Timer* timer = new Timer();
    int spawnRate = 2000;
    int enemyCount = 0;

    QGraphicsScene *scene;
    int difficulty = 1;
    int const levelDifficultyStep = 5;
    int upForNextDiff = levelDifficultyStep; 
    int const maxEnemyAlive = 3;
    int totalEnemiesToKill = 3;
    int totalEnemiesSpawned = 0;
};

#endif // ENEMYMANAGER_H
