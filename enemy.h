#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include "enemymanager.h"
#include "Cons.h"

class Enemy: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Enemy(EnemyManager* manager);
    ~Enemy();
    int type() const override{
        return Keys::enemyIndex;
    }

    int speed = 5;
    int width = 50;
    int height = 50;
    int shoot_interval = 3000;

public slots:
    void onTimer();
    void createBullet();


private:
    EnemyManager* manager;

    bool removalCheck();
    void move();
};

#endif // ENEMY_H
