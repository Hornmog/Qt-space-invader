#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <QObject>
#include <QGraphicsRectItem>
#include "ScoreBar.h"

class Enemy;

class EnemyManager : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    EnemyManager(QGraphicsScene *scene, ScoreBar *scoreBar);
    void onEnemyRemoval(Enemy* enemy);
signals:
    void onEnemyCountChange(int enemyDeaths);

public slots:
    void onTimer();
private:
    void createEnemy();
    int getScore();

    int enemyCount = 0;
    int score = 0;
    QGraphicsScene *scene;
    ScoreBar *scoreBar;
};

#endif // ENEMYMANAGER_H
