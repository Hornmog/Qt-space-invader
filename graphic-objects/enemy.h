#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include "level/enemycommander.h"
#include "consts.h"
#include "spaceship.h"

class Enemy: public SpaceShip{
    Q_OBJECT
public:
    Enemy(EnemyCommander* manager, int count);
    ~Enemy() override;
    int type() const override{return curType;}
    virtual void addToScene(QGraphicsScene* scene) override;

public slots:
    void onTimer() override;
    void groupCheckTextInfo() override;
    void setDifficulty(int difficulty);
    void onDamage() override;

private:
    void move();
    void setUpDelay(int delay);
    void delState();
    const float baseBulletSpeed = -0.2 * period_ms;
    EnemyCommander* manager;
    Timer* timerBullet = nullptr;
    int curType = TypeIndex::enemy;
    int count;
    int difficulty;

private slots:

signals:
    void enemyOnBase();
};

#endif // ENEMY_H
