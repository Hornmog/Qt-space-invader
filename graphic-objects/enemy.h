#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include "level/enemymanager.h"
#include "consts.h"
#include "spaceship.h"

class Enemy: public SpaceShip{
    Q_OBJECT
public:
    Enemy(EnemyManager* manager, QString imagePath, int count);
    ~Enemy() override;
    int type() const override{return TypeIndex::enemy;}
    virtual void addToScene(QGraphicsScene* scene) override;

public slots:
    void onTimer() override;
    void groupCheckTextInfo() override;
    void setDifficulty(int difficulty);
    void onHeroCollision();

private:
    void move();
    void setUpDelay(int delay);
    const float baseBulletSpeed = -0.2 * period_ms;
    EnemyManager* manager;
    Timer* timerBullet = nullptr;
    int count;
    int difficulty;

signals:
    void enemyOnBase();
};

#endif // ENEMY_H
