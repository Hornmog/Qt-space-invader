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

public slots:
    void onTimer();


private:
    EnemyManager* manager;
    int speed = 5;

    bool removalCheck();
    void move();
};

#endif // ENEMY_H
