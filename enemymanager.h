#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <QObject>
#include <QGraphicsRectItem>
#include "ScoreBar.h"
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

signals:
    void onEnemyCountChange(int enemyDeaths);
    void changeDifficulty(int difficulty);
    void allEnemiesDefeated();
    void enemyOnBase();
    void logKeyPressed(bool);

public slots:
    void onTimer();

private:
    void createEnemy();

    int enemyCount = 0;
    int score = 0;
    QGraphicsScene *scene;
    ScoreBar *scoreBar;
    int difficulty = 1;
    int const levelDifficultyStep = 5;
    int upForNextDiff = levelDifficultyStep; 
    int const maxEnemyAlive = 4;
    int const totalEnemiesToKill = 20;
    int totalEnemiesSpawned = 0;
};

#endif // ENEMYMANAGER_H
