#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <QObject>
#include <QGraphicsRectItem>
#include "scorebar.h"
#include "keymanager.h"

class Enemy;

class EnemyManager : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    EnemyManager(QGraphicsScene* scene, ScoreBar* scoreBar, KeyManager* keyManager);
    void onEnemyDestruction(Enemy* enemy);
    void onKillByHero(Enemy* enemy);
    void onKillByNonHero(Enemy* enemy);
    void startSpawningEnemies();

signals:
    void onEnemyCountChange(int enemyDeaths);
    void changeDifficulty(int difficulty);
    void allEnemiesDefeated();
    void enemyOnBase();
    void logKeyPressed(bool);

public slots:
    void onSpawnTimer();

private:
    void createEnemy();

    int spawnRate = 2000;
    int enemyCount = 0;
    int score = 0;
    QGraphicsScene *scene;
    ScoreBar *scoreBar;
    int difficulty = 1;
    int const levelDifficultyStep = 5;
    int upForNextDiff = levelDifficultyStep; 
    int const maxEnemyAlive = 3;
    int const totalEnemiesToKill = 3;
    int totalEnemiesSpawned = 0;
};

#endif // ENEMYMANAGER_H
