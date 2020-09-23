#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <QObject>
#include <QGraphicsRectItem>

class Enemy;

class EnemyManager : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    EnemyManager(QGraphicsScene *scene);
    void onEnemyRemoval(Enemy* enemy);

public slots:
    void onTimer();
private:
    void createEnemy();
    int enemyCount = 0;
    QGraphicsScene *scene;
};

#endif // ENEMYMANAGER_H
