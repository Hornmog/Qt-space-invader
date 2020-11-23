#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <QObject>
#include <QGraphicsRectItem>
#include "keymanager.h"
#include <QJsonObject>

class Enemy;

class EnemyManager : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    EnemyManager(QGraphicsScene* scene, KeyManager* keyManager);
    void onEnemyDestruction(Enemy* enemy);
    void onKillByHero(Enemy* enemy);
    void onKillByNonHero(Enemy* enemy);
    void startSpawningEnemies();
    void setTotalEnemiesToKill(int num) {totalEnemiesToKill = num;}
    void resume();
    void pause();
    QJsonObject returnEnemiesKilled();

signals:
    void onEnemyCountChange(int enemyDeaths);
    void changeDifficulty(int difficulty);
    void allEnemiesDefeated();
    void enemyOnBase();
    void logKeyPressed(bool);
    void stopAll();
    void startAll();

public slots:
    void onSpawnTimer();

private:
    void createEnemy();

    QTimer* timer;
    int spawnRate = 2000;
    int enemyCount = 0;
    int score = 0;
    QGraphicsScene *scene;
    int difficulty = 1;
    int const levelDifficultyStep = 5;
    int upForNextDiff = levelDifficultyStep; 
    int const maxEnemyAlive = 3;
    int totalEnemiesToKill = 3;
    int totalEnemiesSpawned = 0;
};

#endif // ENEMYMANAGER_H
