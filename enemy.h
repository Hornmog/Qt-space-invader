#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include "Cons.h"

class Enemy: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Enemy();
    int type() const override{
        return Keys::enemyIndex;
    }
public slots:
    void onTimer();
    bool removalCheck();
    void removal();
    void move();
private:
    int speed = 5;
};

#endif // ENEMY_H
