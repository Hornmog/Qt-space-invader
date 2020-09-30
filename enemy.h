#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include "enemymanager.h"
#include "Cons.h"
#include "spaceship.h"

class Enemy: public SpaceShip{
    Q_OBJECT
public:
    Enemy(EnemyManager* manager);
    ~Enemy();
    int type() const override{
        return Keys::enemyIndex;
    }

public slots:
    void onTimer();

private:
    EnemyManager* manager;
    void move();
};

#endif // ENEMY_H
