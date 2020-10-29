#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include "enemymanager.h"
#include "consts.h"
#include "spaceship.h"

class Enemy: public SpaceShip{
    Q_OBJECT
public:
    Enemy(EnemyManager* manager, QString imagePath, int count);
    ~Enemy() override;
    int type() const override{return TypeIndex::enemy;}

public slots:
    void onTimer() override;
    void groupCheckTextInfo() override;
    void setDifficulty(int difficulty);

private:
    const float baseBulletSpeed = -0.2 * period_ms;
    EnemyManager* manager;
    int count;
    int difficulty;

    void move();
    void positiveRemoval(int hitType);

signals:
    void enemyOnBase();
};

#endif // ENEMY_H
